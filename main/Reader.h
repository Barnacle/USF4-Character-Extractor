#pragma once

namespace usf4_ce {
	using namespace System;
	using namespace IO;

	typedef unsigned short ushort;
	typedef unsigned long ulong;

	ref struct emg_header sealed
	{
		UINT32 number711;
		UINT32 texture_count;	// Amount of Submodel's textures.
		UINT32 something;
		UINT32 texture_offset;	// Position of "Texture offsets" list.
		UINT16 vertex_count;	// Amount of vertices.
		UINT16 vertex_size;		// Size of vertex.
		UINT32 vertex_offset;	// Position of vertexes in file.
		UINT16 trianlge_strip;	// 1 if true, simple triangle list otherwise 
		UINT16 submodel_count;	// Submodels in EMG.
		UINT32 submeshes_list_offset;	// Offset to list of addresses of submeshes.
	};

	ref struct emg_struct sealed
	{
		emg_header^ header = gcnew emg_header();

		array<byte>^ dds_id;					// Array of submodel's texture ids.		
		array<UINT16>^ index_count;				// Array of Indexes amount of each submodel.
		array<UINT16>^ nodes_count;				// Array of Nodes amount of each submodel.
		array<array<UINT16>^>^ indices_array;	// Array of indeces blocks.
		array<array<UINT16>^>^ nodes_array;		// Array of Nodes.
		array<byte>^ vertex_array;				// Array of vertices blocks.
	};

	// FileName, EMG position in EMO
	inline emg_struct^ read_emg(String^ file_name, const int emg_position)
	{
		const auto emg_data = gcnew emg_struct();

		auto fs = File::OpenRead(file_name);
		auto br = gcnew BinaryReader(fs);

		fs->Position = emg_position + 16; // 16 - offset EMG header.

		emg_data->header->number711 = br->ReadUInt32();
		emg_data->header->texture_count = br->ReadUInt32();
		emg_data->header->something = br->ReadUInt32();
		emg_data->header->texture_offset = br->ReadUInt32();
		emg_data->header->vertex_count = br->ReadUInt16();
		emg_data->header->vertex_size = br->ReadUInt16();
		emg_data->header->vertex_offset = br->ReadUInt32();
		emg_data->header->trianlge_strip = br->ReadUInt16();
		emg_data->header->submodel_count = br->ReadUInt16();
		emg_data->header->submeshes_list_offset = br->ReadUInt32();

		//==================================================================
		// Textures.
		//==================================================================
		fs->Position = emg_position + 16 + emg_data->header->texture_offset;

		auto offsets = gcnew array<UINT32>(emg_data->header->texture_count);
		for (UINT32 i = 0; i < emg_data->header->texture_count; i++)
			offsets[i] = br->ReadUInt32();

		auto id = gcnew array <byte>(emg_data->header->texture_count);
		for (UINT32 i = 0; i < emg_data->header->texture_count; i++)
		{
			fs->Position = emg_position + 16 + offsets[i] + 5;
			id[i] = byte(br->ReadChar());
		}

		emg_data->dds_id = gcnew array<byte>(emg_data->header->submodel_count);

		//==================================================================
		// Indeces and nodes
		//==================================================================
		emg_data->index_count = gcnew array<UINT16>(emg_data->header->submodel_count); // Array of Indexes amount of each submodel.
		emg_data->indices_array = gcnew array<array<UINT16>^>(emg_data->header->submodel_count);

		emg_data->nodes_count = gcnew array<UINT16>(emg_data->header->submodel_count);
		emg_data->nodes_array = gcnew array<array<UINT16>^>(emg_data->header->submodel_count);

		for (auto i = 0; i < emg_data->header->submodel_count; i++)
		{
			fs->Position = emg_position + 16 + emg_data->header->submeshes_list_offset + i * 4; // Looking for submesh address in a list of submeshes
			fs->Position = emg_position + 16 + br->ReadUInt32() + 16; // 16 bytes #EMG + offset of submesh + 16 bytes of trash
			emg_data->dds_id[i] = id[byte(br->ReadUInt16())]; // Texture ID.
			emg_data->index_count[i] = br->ReadUInt16(); // Ammount of indeces.
			emg_data->nodes_count[i] = br->ReadUInt16(); // Ammount of nodes.

			fs->Position = fs->Position + 32; // skipping name (32 bytes).

			emg_data->indices_array[i] = gcnew array<UINT16>(emg_data->index_count[i]);

			// Filling array with submesh indeces.
			for (auto a = 0; a < emg_data->index_count[i]; a++)
			{
				emg_data->indices_array[i][a] = br->ReadUInt16();
			}

			emg_data->nodes_array[i] = gcnew array<UINT16>(emg_data->nodes_count[i]);

			// Filling array with nodes.
			for (auto a = 0; a < emg_data->nodes_count[i]; a++)
			{
				emg_data->nodes_array[i][a] = br->ReadUInt16();
			}
		}

		//==================================================================
		// Vertices
		//==================================================================
		fs->Position = emg_position + 16 + emg_data->header->vertex_offset; // Address of vertices
		emg_data->vertex_array = gcnew array<byte>(emg_data->header->vertex_count * emg_data->header->vertex_size); // Array of vertex data
		for (auto i = 0; i < emg_data->header->vertex_count * emg_data->header->vertex_size; i++)
		{
			emg_data->vertex_array[i] = byte(br->ReadByte());
		}

		br->Close();
		fs->Close();

		return emg_data;
	}

	//==================================================================

	ref struct emb_struct sealed
	{
		ushort dds_count;				// DDS ammount in EMB.
		array<ulong>^ dds_size;			// Size of each DDS.
		array<array<byte>^>^ dds_array;	// DDS itself.
	};

	inline emb_struct^ read_emb(String^ file_name)
	{
		const auto emb_data = gcnew emb_struct();

		auto fs = File::OpenRead(file_name);
		auto br = gcnew BinaryReader(fs);

		// DDS amount.
		fs->Position = 12;
		emb_data->dds_count = br->ReadInt16();

		// Reading
		auto dds_offset = gcnew array<UINT32>(emb_data->dds_count);
		emb_data->dds_size = gcnew array<ulong>(emb_data->dds_count);
		emb_data->dds_array = gcnew array<array<byte>^>(emb_data->dds_count);

		// List of offsets to DDS and sizes.
		fs->Position = 32;
		for (UINT32 i = 0; i < emb_data->dds_count; i++)
		{
			dds_offset[i] = br->ReadInt32() + (i * 2 * 4); // + DDSsize
			emb_data->dds_size[i] = br->ReadInt32();
		}				

		//
		for (UINT32 i = 0; i < emb_data->dds_count; i++)
		{
			emb_data->dds_array[i] = gcnew array<byte>(emb_data->dds_size[i]);

			fs->Position = 32 + dds_offset[i];

			for (UINT32 a = 0; a < emb_data->dds_size[i]; a++)
			{
				emb_data->dds_array[i][a] = byte(br->ReadByte());
			}
		}

		br->Close();
		fs->Close();

		return emb_data;
	}

	//==================================================================

	ref struct skeleton_struct sealed
	{
		ushort	nodes_count;
		array<String^>^ node_name;
		array<short>^ parent_node_array;
		array<array<byte>^>^ matrix_4x4;
	};

	inline skeleton_struct^ read_skeleton(String^ file_name, const byte offset) // EMO - 16, EMA - 12
	{
		const auto skeleton = gcnew skeleton_struct();

		auto fs = File::OpenRead(file_name);
		auto br = gcnew BinaryReader(fs);

		fs->Position = offset; // Skipping to position about nodes.
		const auto skeletal_info_offset = br->ReadUInt32();

		if(skeletal_info_offset == 0)
		{
			br->Close();
			fs->Close();

			auto node_name = gcnew array<String^>(1);
			node_name[0] = "camera";

			auto parent_node_array = gcnew array<short>(1);
			parent_node_array[0] = short(0xffff);

			skeleton->nodes_count = 1;
			skeleton->node_name = node_name;
			skeleton->parent_node_array = parent_node_array;
			skeleton->matrix_4x4 = nullptr;
			return skeleton;
		}

		fs->Position = skeletal_info_offset; // Skipping to data about nodes.
		skeleton->nodes_count = br->ReadUInt16(); // Nodes amount.

		fs->Position = fs->Position + 6; // Skipping 4 bytes.
		const ushort start_offset = br->ReadUInt32(); // Header size.
		const ushort names_offsets_offset = br->ReadUInt32(); // Offset to offsets about node names.

		//==================================================================

		fs->Position = skeletal_info_offset + names_offsets_offset; // Offsets to names.
		auto nodes_names_offsets = gcnew array<UInt32>(skeleton->nodes_count);
		skeleton->node_name = gcnew array<String^>(skeleton->nodes_count);
		for (unsigned int i = 0; i < skeleton->nodes_count; i++)
		{
			nodes_names_offsets[i] = br->ReadUInt32();
			const auto saved_position = fs->Position;

			fs->Position = skeletal_info_offset + nodes_names_offsets[i];

			String^ str = {};
			byte ch;
			while (int(ch = byte(br->ReadChar())) != 0)
				str += Convert::ToChar(ch);

			skeleton->node_name[i] = str;

			fs->Position = saved_position;
		}

		//==================================================================

		fs->Position = skeletal_info_offset + start_offset; // Nodes.

		skeleton->parent_node_array = gcnew array<short>(skeleton->nodes_count);
		skeleton->matrix_4x4 = gcnew array<array<byte>^>(skeleton->nodes_count);

		for (auto i = 0; i < skeleton->nodes_count; i++)
		{
			const auto temp = br->ReadUInt16();
			if (temp == 65535)	// FFFF - root.
				skeleton->parent_node_array[i] = -1;
			else
				skeleton->parent_node_array[i] = temp;

			fs->Position = fs->Position + 14; // Skipping to position about matrix.

			skeleton->matrix_4x4[i] = gcnew array<byte>(64);
			for (ushort a = 0; a < 64; a++)
				skeleton->matrix_4x4[i][a] = br->ReadByte();
		}

		br->Close();
		fs->Close();

		return skeleton;
	}

	//==================================================================
	// EMA
	//==================================================================

	ref struct skeleton_header sealed
	{
		UInt16 nodeCount;
		UInt16 someNodeCount;
		UInt16 ikDataCount;//small number
		UInt16 unknown0x06;//0
		UInt32 skeletonStartOffset;
		UInt32 skeletonNameAddressOffset;
		// 0x10
		UInt32 someDataOffset;
		UInt32 someNodeAddressOffset;
		UInt32 unknownDataOffset;//address for bunch of FF's
		UInt32 matrixOffset;
		// 0x20
		UInt32 ikDataOffset;

		UInt32 unknown1;
		UInt32 unknown2;
		UInt32 unknown3;
		UInt32 unknown4;
		UInt32 unknown5;
		UInt32 unknown6;
		UInt32 unknown7;
	};

	ref struct ema_skeleton_node sealed
	{
		UInt16 parent;//FFFF if root
		UInt16 child1;
		UInt16 child2;//FFFF if none
		UInt16 child3;//FFFF if none
		UInt16 child4;//FFFF if none
		UInt16 flags;
		float unknown4;//0
		array<float>^ matrix = gcnew array<float>(16);
	};

	ref struct ema_skeleton_ik_data sealed
	{
		UInt16 method;
		UInt16 data_size;
		array<byte>^ data = gcnew array<byte>(32);
	};

	ref struct full_ema_skeleton_struct sealed
	{
		skeleton_header header;
		array<ema_skeleton_node^>^ nodes;
		array<byte>^ unknown_data;
		array<UINT32>^ names_offsets;
		array<String^>^ names;
		array<ema_skeleton_ik_data^>^ ik_data;
		array<byte>^ some_data;
		array<UINT32>^ someNode_offsets;
		array<String^>^ someNode_names;
	};

	inline full_ema_skeleton_struct^ read_ema_skeleton(String^ file_name)
	{
		const auto ema_skeleton = gcnew full_ema_skeleton_struct();

		auto fs = File::OpenRead(file_name);
		auto br = gcnew BinaryReader(fs);

		fs->Position = 12; // Skipping to position about nodes.
		const auto skeletal_info_offset = br->ReadUInt32();

		if (skeletal_info_offset == 0)
		{
			br->Close();
			fs->Close();

			return nullptr;
		}

		fs->Position = skeletal_info_offset; // Skipping to data about nodes.

		ema_skeleton->header.nodeCount = br->ReadUInt16();
		ema_skeleton->header.someNodeCount = br->ReadUInt16();
		ema_skeleton->header.ikDataCount = br->ReadUInt16();
		ema_skeleton->header.unknown0x06 = br->ReadUInt16();
		ema_skeleton->header.skeletonStartOffset = br->ReadUInt32();
		ema_skeleton->header.skeletonNameAddressOffset = br->ReadUInt32();
		ema_skeleton->header.someDataOffset = br->ReadUInt32();
		ema_skeleton->header.someNodeAddressOffset = br->ReadUInt32();
		ema_skeleton->header.unknownDataOffset = br->ReadUInt32();
		ema_skeleton->header.matrixOffset = br->ReadUInt32();
		ema_skeleton->header.ikDataOffset = br->ReadUInt32();
		ema_skeleton->header.unknown1 = br->ReadUInt32();
		ema_skeleton->header.unknown2 = br->ReadUInt32();
		ema_skeleton->header.unknown3 = br->ReadUInt32();
		ema_skeleton->header.unknown4 = br->ReadUInt32();
		ema_skeleton->header.unknown5 = br->ReadUInt32();
		ema_skeleton->header.unknown6 = br->ReadUInt32();
		ema_skeleton->header.unknown7 = br->ReadUInt32();

		fs->Position = skeletal_info_offset + ema_skeleton->header.skeletonStartOffset;

		ema_skeleton->nodes = gcnew array<ema_skeleton_node^>(ema_skeleton->header.nodeCount);
		for (unsigned int i = 0; i < ema_skeleton->header.nodeCount; i++)
		{
			ema_skeleton->nodes[i] = gcnew ema_skeleton_node();
			ema_skeleton->nodes[i]->parent = br->ReadUInt16();
			ema_skeleton->nodes[i]->child1 = br->ReadUInt16();
			ema_skeleton->nodes[i]->child2 = br->ReadUInt16();
			ema_skeleton->nodes[i]->child3 = br->ReadUInt16();
			ema_skeleton->nodes[i]->child4 = br->ReadUInt16();
			ema_skeleton->nodes[i]->flags = br->ReadUInt16();
			ema_skeleton->nodes[i]->unknown4 = br->ReadSingle();

			for(auto a = 0; a < ema_skeleton->nodes[i]->matrix->Length; a++)
			{
				ema_skeleton->nodes[i]->matrix[a] = br->ReadSingle();
			}
		}


		ema_skeleton->unknown_data = gcnew array<byte>(ema_skeleton->header.skeletonNameAddressOffset - ema_skeleton->header.unknownDataOffset);
		fs->Position = skeletal_info_offset + ema_skeleton->header.unknownDataOffset;
		ema_skeleton->unknown_data = br->ReadBytes(ema_skeleton->header.skeletonNameAddressOffset - ema_skeleton->header.unknownDataOffset);


		fs->Position = skeletal_info_offset + ema_skeleton->header.skeletonNameAddressOffset;
		ema_skeleton->names_offsets = gcnew array<UInt32>(ema_skeleton->header.nodeCount);
		ema_skeleton->names = gcnew array<String^>(ema_skeleton->header.nodeCount);
		for (unsigned int i = 0; i < ema_skeleton->header.nodeCount; i++)
		{
			ema_skeleton->names_offsets[i] = br->ReadUInt32();
			const auto saved_position = fs->Position;

			fs->Position = skeletal_info_offset + ema_skeleton->names_offsets[i];

			String^ str = {};
			byte ch;
			while (int(ch = byte(br->ReadChar())) != 0)
				str += Convert::ToChar(ch);

			ema_skeleton->names[i] = str;

			fs->Position = saved_position;
		}

		if (ema_skeleton->header.ikDataCount > 0 && ema_skeleton->header.ikDataOffset != 0)
		{
			fs->Position = skeletal_info_offset + ema_skeleton->header.ikDataOffset;

			ema_skeleton->ik_data = gcnew array<ema_skeleton_ik_data^>(ema_skeleton->header.ikDataCount);

			for (auto i = 0; i < ema_skeleton->header.ikDataCount; i++)
			{
				ema_skeleton->ik_data[i] = gcnew ema_skeleton_ik_data();

				ema_skeleton->ik_data[i]->method = br->ReadUInt16();
				ema_skeleton->ik_data[i]->data_size = br->ReadUInt16();
				ema_skeleton->ik_data[i]->data = br->ReadBytes(sizeof(byte) * min((ema_skeleton->ik_data[i]->data_size - 4), 32));
			}
		}


		ema_skeleton->some_data = gcnew array<byte>(ema_skeleton->header.someNodeAddressOffset - ema_skeleton->header.someDataOffset);
		fs->Position = skeletal_info_offset + ema_skeleton->header.someDataOffset;
		ema_skeleton->some_data = br->ReadBytes(ema_skeleton->header.someNodeAddressOffset - ema_skeleton->header.someDataOffset);


		ema_skeleton->someNode_offsets = gcnew array<UINT32>(ema_skeleton->header.someNodeCount);
		ema_skeleton->someNode_names = gcnew array<String^>(ema_skeleton->header.someNodeCount);
		fs->Position = skeletal_info_offset + ema_skeleton->header.someNodeAddressOffset;
		for (auto i = 0; i < ema_skeleton->header.someNodeCount; i++)
		{
			ema_skeleton->someNode_offsets[i] = br->ReadUInt32();
			const auto saved_position = fs->Position;

			fs->Position = skeletal_info_offset + ema_skeleton->someNode_offsets[i];

			String^ str = {};
			byte ch;
			while (int(ch = byte(br->ReadChar())) != 0)
				str += Convert::ToChar(ch);

			ema_skeleton->someNode_names[i] = str;

			fs->Position = saved_position;
		}


		//==================================================================

		br->Close();
		fs->Close();

		return ema_skeleton;
	}

	//==================================================================

	[Serializable]
	ref struct ema_animation_node sealed
	{
		String^ name;
		UInt16 index;
		char transform_type;
		char transform_flag;
		UInt16 step_count;
		UInt16 indices_offset;

		array<UInt16>^ frame;
		array<float>^ value;
		array<float>^ tangent_value;

		array<UInt32>^ value_indexes;
	};

	ref struct ema_animation sealed
	{
		String^ name;
		UInt16 duration;
		UInt16 cmd_offset_count;
		UInt32 value_count;
		UINT32 unknown; // some locker? anim is not playing if 1
		UInt32 name_offset;
		UInt32 values_offset;

		array<UInt32>^ cmd_offsets;
		array<ema_animation_node^>^ node;
		array<float>^ values;
	};

	ref struct ema_header sealed
	{
		// ReSharper disable once CppNonInlineVariableDefinitionInHeaderFile
		static array<byte>^ id = gcnew array<byte>{ '#', 'E', 'M', 'A', 0xFE, 0xFF };
		UInt16 header_size = 0x20;
		UInt32 unknown1 = 1;
		UInt32 skeleton_offset;
		UInt16 animation_count;
		UInt16 unknown4 = 3;

		UInt16 unknown5;
		UInt16 unknown6;
		UInt16 unknown7;
		UInt16 unknown8;
		UInt16 unknown9;
		UInt16 unknown10;
	};

	ref struct ema_struct sealed
	{
		ema_header^ header = gcnew ema_header();
		array<UInt32>^ animation_offsets;
		array<ema_animation^>^ animation;
		array<String^>^ skeleton_node_names;
	};

	inline ema_struct^ read_ema(String^ file_name)
	{
		const auto ema_data = gcnew ema_struct();

		auto fs = File::OpenRead(file_name);
		auto br = gcnew BinaryReader(fs);

		fs->Position = 6; // Header.
		const auto header_size = br->ReadUInt16();

		fs->Position = 16; // Ammount of animations.
		ema_data->header->animation_count = br->ReadUInt16();

		fs->Position = header_size; // Animations offsets
		auto animation_offsets = gcnew array<UINT32>(ema_data->header->animation_count);
		for (auto i = 0; i < ema_data->header->animation_count; i++)
			animation_offsets[i] = br->ReadUInt32(); //

		ema_data->animation = gcnew array<ema_animation^>(ema_data->header->animation_count);


		for (auto i = 0; i < ema_data->header->animation_count; i++)
		{
			fs->Position = animation_offsets[i];

			ema_data->animation[i] = gcnew ema_animation();

			ema_data->animation[i]->duration = br->ReadUInt16();
			ema_data->animation[i]->cmd_offset_count = br->ReadUInt16();
			ema_data->animation[i]->value_count	= br->ReadUInt32();
			ema_data->animation[i]->unknown = br->ReadUInt32();
			ema_data->animation[i]->name_offset = br->ReadUInt32();
			ema_data->animation[i]->values_offset = br->ReadUInt32();

			//==================================================================
			fs->Position = animation_offsets[i] + ema_data->animation[i]->name_offset + 11; // 11 - trash.
			ushort size = 1; // Length of name for array creation.
			while (br->ReadChar() != 0)
				size++;
			const auto buffer = new char[size];
			fs->Position = fs->Position - size; // Position return.
			for (auto a = 0; a < size; a++) // Reading in array.
				buffer[a] = char(br->ReadChar());
			ema_data->animation[i]->name = gcnew String(buffer);
			delete[] buffer;
			//==================================================================

			fs->Position = animation_offsets[i] + ema_data->animation[i]->values_offset;
			ema_data->animation[i]->values = gcnew array<float>(ema_data->animation[i]->value_count);
			for (UINT32 value = 0; value < ema_data->animation[i]->value_count; value++)
				ema_data->animation[i]->values[value] = br->ReadSingle();

			//==================================================================

			fs->Position = animation_offsets[i] + 20;
			ema_data->animation[i]->cmd_offsets = gcnew array<UINT32>(ema_data->animation[i]->cmd_offset_count);
			for (auto index = 0; index < ema_data->animation[i]->cmd_offset_count; index++)
				ema_data->animation[i]->cmd_offsets[index] = br->ReadUInt32();

			ema_data->animation[i]->node = gcnew array<ema_animation_node^>(ema_data->animation[i]->cmd_offset_count);

			for (auto cmd_offset = 0; cmd_offset < ema_data->animation[i]->cmd_offset_count; cmd_offset++)
			{
				fs->Position = animation_offsets[i] + ema_data->animation[i]->cmd_offsets[cmd_offset];

				ema_data->animation[i]->node[cmd_offset] = gcnew ema_animation_node();

				ema_data->animation[i]->node[cmd_offset]->index = br->ReadUInt16(); // index of node.
				ema_data->animation[i]->node[cmd_offset]->transform_type = char(br->ReadChar()); // 0 -> translation, 1 -> rotation, 2->scale
				ema_data->animation[i]->node[cmd_offset]->transform_flag = char(br->ReadChar()); // 0 - x, 1 - y, 2 - z
				ema_data->animation[i]->node[cmd_offset]->step_count = br->ReadUInt16(); //(stepCount))
				ema_data->animation[i]->node[cmd_offset]->indices_offset = br->ReadUInt16(); //(indicesOffset));

				ema_data->animation[i]->node[cmd_offset]->frame = gcnew array<ushort>(ema_data->animation[i]->node[cmd_offset]->step_count);
				ema_data->animation[i]->node[cmd_offset]->value = gcnew array<float>(ema_data->animation[i]->node[cmd_offset]->step_count);
				ema_data->animation[i]->node[cmd_offset]->tangent_value = gcnew array<float>(ema_data->animation[i]->node[cmd_offset]->step_count);
				ema_data->animation[i]->node[cmd_offset]->value_indexes = gcnew array<UINT32>(ema_data->animation[i]->node[cmd_offset]->step_count);

				for (ushort a = 0; a < ema_data->animation[i]->node[cmd_offset]->step_count; a++)
				{
					if (ema_data->animation[i]->node[cmd_offset]->transform_flag & 0x20)
						ema_data->animation[i]->node[cmd_offset]->frame[a] = br->ReadUInt16();
					else
						ema_data->animation[i]->node[cmd_offset]->frame[a] = ushort(br->ReadByte());
				}

				fs->Position = animation_offsets[i] + ema_data->animation[i]->cmd_offsets[cmd_offset] + ema_data->animation[i]->node[cmd_offset]->indices_offset;

				for (ushort a = 0; a < ema_data->animation[i]->node[cmd_offset]->step_count; a++)
				{
					if (ema_data->animation[i]->node[cmd_offset]->transform_flag & 0x40)
					{
						const UINT32 temp_index = br->ReadUInt32();
						ema_data->animation[i]->node[cmd_offset]->value_indexes[a] = temp_index;

						const UINT32 value_index = temp_index & 0x3FFFFFFF;
						ema_data->animation[i]->node[cmd_offset]->value[a] = ema_data->animation[i]->values[value_index];

						const byte high_order_bits = temp_index >> 30 & 0x03;
						const auto tangent_index = high_order_bits == 0 ? ~0 : value_index + high_order_bits;
						if (tangent_index != ~0)
							ema_data->animation[i]->node[cmd_offset]->tangent_value[a] = ema_data->animation[i]->values[tangent_index];
					}						
					else
					{
						const auto temp_index = br->ReadUInt16();
						ema_data->animation[i]->node[cmd_offset]->value_indexes[a] = temp_index;

						const UINT32 value_index = temp_index & 0x3FFF;
						ema_data->animation[i]->node[cmd_offset]->value[a] = ema_data->animation[i]->values[value_index];

						const byte high_order_bits = temp_index >> 14 & 0x03;
						const auto tangent_index = high_order_bits == 0 ? ~0 : value_index + high_order_bits;
						if (tangent_index != ~0)
							ema_data->animation[i]->node[cmd_offset]->tangent_value[a] = ema_data->animation[i]->values[tangent_index];
					}
				}
			}
		}			

		br->Close();
		fs->Close();

		return ema_data;
	}
}