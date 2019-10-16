#pragma once

namespace SSF4ce {
	using namespace System;
	using namespace IO;

	typedef unsigned short ushort;
	typedef unsigned long ulong;

	ref struct EMG_Data
	{
		array<byte>^ DDSid;					// Array of submodel's texture ids.
		ushort SubmodelCount;				// Submodels in EMG.
		array<ushort>^ IndexCount;			// Array of Indexes amount of each submodel.
		array<ushort>^ NodesCount;			// Array of Nodes amount of each submodel.
		ushort VertexCount;					// Amount of vertices.
		ushort VertexSize;					// Size of vertex.
		array<array<ushort>^>^ IndiceArray;	// Array of indeces blocks.
		array<array<ushort>^>^ NodesArray;	// Array of Nodes.
		array<byte>^ VertexArray;			// Array of vertices blocks.
	};

	// FileName, EMG position in EMO
	inline EMG_Data^ ReadEMG(String^ FileName, int EMGposition)
	{
		auto return_value = gcnew EMG_Data();

		auto fs = File::OpenRead(FileName);
		auto br = gcnew BinaryReader(fs);
		
		fs->Position = EMGposition + 16; // 16 - offset EMG header.

		fs->Position = fs->Position + 4; //EMGHeader1->Number711 = (ushort)br->ReadUInt32(); 
		const auto texture_count = ushort(br->ReadUInt32());			// Amount of Submodel's textures.
		fs->Position = fs->Position + 4; //EMGHeader1->Something = (ushort)br->ReadUInt32();
		const auto texture_offset = ushort(br->ReadUInt32());			// Position of "Texture offsets" list.

		const auto vertex_count = ushort(br->ReadUInt16());				// Amount of vertices.
		const auto vertex_size = ushort(br->ReadUInt16());				// Size of vertex.
		const auto vertex_offset = ulong(br->ReadUInt32());				// Position of vertexes in file.
		fs->Position = fs->Position + 2; //EMGHeader1->Empty = (ushort)br->ReadUInt16(); // Empty 2 bytes. (strips?)
		const auto submodel_count = ushort(br->ReadUInt16());			// Submodels in EMG.
		const auto submeshes_list_offset = ushort(br->ReadUInt16());	// Offset to list of addresses of submeshes.

		//==================================================================
		// Textures.
		//==================================================================
		fs->Position = EMGposition + 16 + texture_offset;

		auto offsets = gcnew array<ushort>(texture_count);
		for (auto i = 0; i < texture_count; i++)
			offsets[i] = ushort(br->ReadUInt32());

		auto id = gcnew array <byte>(texture_count);
		for (auto i = 0; i < texture_count; i++)
		{
			fs->Position = EMGposition + 16 + offsets[i] + 5;
			id[i] = byte(br->ReadChar());
		}

		auto DDSid = gcnew array<byte>(submodel_count);

		//==================================================================
		// Indeces and nodes
		//==================================================================
		auto index_count = gcnew array<ushort>(submodel_count); // Array of Indexes amount of each submodel.
		auto indices_array = gcnew array<array<ushort>^>(submodel_count);

		auto nodes_count = gcnew array<ushort>(submodel_count);
		auto nodes_array = gcnew array<array<ushort>^>(submodel_count);

		for (ushort i = 0; i < submodel_count; i++)
		{
			fs->Position = EMGposition + 16 + submeshes_list_offset + i * 4; // Looking for submesh address in a list of submeshes
			fs->Position = EMGposition + 16 + br->ReadUInt32() + 16; // 16 bytes #EMG + offset of submesh + 16 bytes of trash
			DDSid[i] = id[byte(br->ReadUInt16())]; // Texture ID.
			index_count[i] = ushort(br->ReadUInt16()); // Ammount of indeces.
			nodes_count[i] = ushort(br->ReadUInt16()); // Ammount of nodes.
			
			fs->Position = fs->Position + 32; // skipping name (32 bytes).

			indices_array[i] = gcnew array<ushort>(index_count[i]);

			// Filling array with submesh indeces.
			for (auto a = 0; a < index_count[i]; a++)
			{
				indices_array[i][a] = ushort(br->ReadUInt16());
			}

			nodes_array[i] = gcnew array<ushort>(nodes_count[i]);

			// Filling array with nodes.
			for (auto a = 0; a < nodes_count[i]; a++)
			{
				nodes_array[i][a] = ushort(br->ReadUInt16());
			}
		}

		//==================================================================
		// Vertices
		//==================================================================
		fs->Position = EMGposition + 16 + vertex_offset; // Address of vertices
		auto vertex_array = gcnew array<byte>(vertex_count * vertex_size); // Array of vertex data
		for (auto i = 0; i < vertex_count * vertex_size; i++)
		{
			vertex_array[i] = byte(br->ReadByte());
		}

		br->Close();
		fs->Close();

		return_value->DDSid = DDSid;
		return_value->SubmodelCount = submodel_count;
		return_value->IndexCount	= index_count;
		return_value->NodesCount	= nodes_count;
		return_value->VertexCount	= vertex_count;
		return_value->VertexSize	= vertex_size;
		return_value->IndiceArray	= indices_array;
		return_value->NodesArray	= nodes_array;
		return_value->VertexArray	= vertex_array;
		return return_value;
	}

	//==================================================================

	ref struct EMB_Data
	{
		ushort DDScount;	// DDS ammount in EMB.
		array<ulong>^ DDSsize;		// Size of each DDS.
		array<array<byte>^>^ DDSArray;	// DDS itself.
	};

	inline EMB_Data^ ReadEMB(String^ FileName)
	{
		const auto return_value = gcnew EMB_Data();

		auto fs = File::OpenRead(FileName);
		auto br = gcnew BinaryReader(fs);

		// Кол-во DDS.
		fs->Position = 12;
		const ushort DDScount = br->ReadInt16();

		//
		auto DDSoffset = gcnew array<ulong>(DDScount);
		auto DDSsize = gcnew array<ulong>(DDScount);
		auto DDSArray = gcnew array<array<byte>^>(DDScount);

		// List of offsets to DDS and sizes.
		fs->Position = 32;
		for (ulong i = 0; i < DDScount; i++)
		{
			DDSoffset[i] = br->ReadInt32() + (i * 2 * 4); // + DDSsize
			DDSsize[i] = br->ReadInt32();
		}				

		//
		for (ulong i = 0; i < DDScount; i++)
		{
			DDSArray[i] = gcnew array<byte>(DDSsize[i]);

			fs->Position = 32 + DDSoffset[i];

			for (ulong a = 0; a < DDSsize[i]; a++)
			{
				DDSArray[i][a] = byte(br->ReadByte());
			}
		}

		br->Close();
		fs->Close();

		return_value->DDScount = DDScount;
		return_value->DDSsize = DDSsize;
		return_value->DDSArray = DDSArray;
		return return_value;
	}

	//==================================================================

	ref struct Skeleton_Data
	{
		ushort	NodesCount;
		array<String^>^ NodeName;
		array<short>^ ParentNodeArray;
		array<array<byte>^>^ Matrix4x4;
	};

	inline Skeleton_Data^ ReadSkeleton(String^ FileName, byte offset) // EMO - 16, EMA - 12
	{
		const auto return_value = gcnew Skeleton_Data();

		auto fs = File::OpenRead(FileName);
		auto br = gcnew BinaryReader(fs);

		fs->Position = offset; // Skipping to position about nodes.
		const auto skeletal_info_offset = br->ReadUInt32();

		fs->Position = skeletal_info_offset; // Skipping to data about nodes.
		const auto nodes_count = br->ReadUInt16(); // Nodes amount.

		fs->Position = fs->Position + 6; // Skipping 4 bytes.
		const ushort start_offset = br->ReadUInt32(); // Header size.
		const ushort names_offsets_offset = br->ReadUInt32(); // Offset to offsets about node names.

		//==================================================================

		fs->Position = skeletal_info_offset + names_offsets_offset; // Offsets to names.
		auto nodes_names_offsets = gcnew array<unsigned int>(nodes_count); // Reading.
		for (auto i = 0; i < nodes_count; i++)
			nodes_names_offsets[i] = br->ReadUInt32();

		auto node_name = gcnew array<String^>(nodes_count);

		for (auto i = 0; i < nodes_count; i++)
		{
			fs->Position = skeletal_info_offset + nodes_names_offsets[i];

			ushort size = 1; // Length of name for array creation.
			while (br->ReadChar() != 0)
				size++;
			const auto buffer = new char[size];

			fs->Position = fs->Position - size; // Position return.

			for (auto a = 0; a < size; a++) // Reading to array.
				buffer[a] = char(br->ReadChar());

			node_name[i] = gcnew String(buffer);
			delete[] buffer;
		}

		//==================================================================

		fs->Position = skeletal_info_offset + start_offset; // Nodes.

		auto ParentNodeArray = gcnew array<short>(nodes_count);
		auto Matrix4x4 = gcnew array<array<byte>^>(nodes_count);

		for (auto i = 0; i < nodes_count; i++)
		{
			const auto temp = br->ReadUInt16();
			if (temp == 65535)	// FFFF - root.
				ParentNodeArray[i] = -1;	
			else
				ParentNodeArray[i] = temp;

			fs->Position = fs->Position + 14; // Skipping to position about matrix.

			Matrix4x4[i] = gcnew array<byte>(64);
			for (ushort a = 0; a < 64; a++)
				Matrix4x4[i][a] = br->ReadByte();
		}

		br->Close();
		fs->Close();

		return_value->NodesCount = nodes_count;
		return_value->NodeName = node_name;
		return_value->ParentNodeArray = ParentNodeArray;
		return_value->Matrix4x4 = Matrix4x4;
		return return_value;
	}

	//==================================================================

	ref struct EMA_Data
	{
		ushort AnimationCount;
		array<String^>^ AnimationName;

		array<ushort>^ Duration;
		array<array<ushort>^>^ NodeIndex;
		array<array<byte>^>^ NodeTransformType;
		array<array<byte>^>^ TransformFlag;
		array<array<ushort>^>^ NodeStepCount;
		array<ushort>^ cmdOffsetCount;
		array<array<array<ushort>^>^>^ Frame;
		array<array<array<float>^>^>^ NodeValue;
		array<array<array<float>^>^>^ NodeTangentValue;
	};

	inline EMA_Data^ ReadEMA(String^ FileName)
	{
		const auto return_value = gcnew EMA_Data();

		auto fs = File::OpenRead(FileName);
		auto br = gcnew BinaryReader(fs);

		fs->Position = 6; // Header. 
		const auto header_size = br->ReadUInt16();

		fs->Position = 16; // Ammount of animations.
		const auto animation_count = br->ReadUInt16();

		fs->Position = header_size; // Animations offsets
		auto animation_offsets = gcnew array<ulong>(animation_count);
		for (auto i = 0; i < animation_count; i++)
			animation_offsets[i] = br->ReadUInt32(); //

		auto animation_name = gcnew array<String^>(animation_count);

		auto duration = gcnew array<ushort>(animation_count);
		auto node_index = gcnew array<array<ushort>^>(animation_count);
		auto cmd_offset_count = gcnew array<ushort>(animation_count);
		auto node_step_count = gcnew array<array<ushort>^>(animation_count);
		auto frame = gcnew array<array<array<ushort>^>^>(animation_count);
		auto node_transform_type = gcnew array<array<byte>^>(animation_count);
		auto node_value = gcnew array<array<array<float>^>^>(animation_count);
		auto node_tangent_value = gcnew array<array<array<float>^>^>(animation_count);
		auto transform_flag = gcnew array<array<byte>^>(animation_count);

		for (auto i = 0; i < animation_count; i++)
		{
			fs->Position = animation_offsets[i];

			duration[i] = br->ReadUInt16();					// Animation duration.
			cmd_offset_count[i] = br->ReadUInt16();			// cmdOffsetCount
			const ulong value_count	= br->ReadUInt32();		// valueCount
			br->ReadUInt32();								// zero
			const ulong name_offset = br->ReadUInt32();		// Offset to name.
			const ulong values_offset = br->ReadUInt32();	// valuesOffset

			//==================================================================
			fs->Position = animation_offsets[i] + name_offset + 11; // 11 - trash.
			ushort size = 1; // Length of name for array creation.
			while (br->ReadChar() != 0)
				size++;
			const auto buffer = new char[size];
			fs->Position = fs->Position - size; // Position return.
			for (auto a = 0; a < size; a++) // Reading in array.
				buffer[a] = char(br->ReadChar());
			animation_name[i] = gcnew String(buffer);
			delete[] buffer;
			//==================================================================

			fs->Position = animation_offsets[i] + values_offset;
			auto values = gcnew array<float>(value_count);
			for (ulong value = 0; value < value_count; value++)
				values[value] = br->ReadSingle();

			//==================================================================

			fs->Position = animation_offsets[i] + 20;
			auto cmd_offsets = gcnew array<ulong>(cmd_offset_count[i]);
			for (auto cmd_offset = 0; cmd_offset < cmd_offset_count[i]; cmd_offset++)
				cmd_offsets[cmd_offset] = br->ReadUInt32();

			node_index[i] = gcnew array<ushort>(cmd_offset_count[i]);
			node_step_count[i] = gcnew array<ushort>(cmd_offset_count[i]);
			frame[i] = gcnew array<array<ushort>^>(cmd_offset_count[i]);
			node_transform_type[i] = gcnew array<byte>(cmd_offset_count[i]);
			node_value[i] = gcnew array<array<float>^>(cmd_offset_count[i]);
			node_tangent_value[i] = gcnew array<array<float>^>(cmd_offset_count[i]);
			transform_flag[i] = gcnew array<byte>(cmd_offset_count[i]);

			for (ulong cmd_offset = 0; cmd_offset < cmd_offset_count[i]; cmd_offset++)
			{
				fs->Position = animation_offsets[i] + cmd_offsets[cmd_offset];

				node_index[i][cmd_offset] = br->ReadUInt16(); // index of node.
				node_transform_type[i][cmd_offset] = char(br->ReadChar()); // 0 -> translation, 1 -> rotation, 2->scale
				transform_flag[i][cmd_offset] = char(br->ReadChar()); // 0 - x, 1 - y, 2 - z
				node_step_count[i][cmd_offset] = br->ReadUInt16(); //(stepCount))
				const auto indices_offset = br->ReadUInt16(); //(indicesOffset));

				frame[i][cmd_offset] = gcnew array<ushort>(node_step_count[i][cmd_offset]);
				node_value[i][cmd_offset] = gcnew array<float>(node_step_count[i][cmd_offset]);
				node_tangent_value[i][cmd_offset] = gcnew array<float>(node_step_count[i][cmd_offset]);

				for (ushort a = 0; a < node_step_count[i][cmd_offset]; a++)
				{
					if (transform_flag[i][cmd_offset] & 0x20)
						frame[i][cmd_offset][a] = br->ReadUInt16();
					else
						frame[i][cmd_offset][a] = ushort(br->ReadByte());						
				}

				fs->Position = animation_offsets[i] + cmd_offsets[cmd_offset] + indices_offset;

				for (ushort a = 0; a < node_step_count[i][cmd_offset]; a++)
				{
					if (transform_flag[i][cmd_offset] & 0x40)
					{
						const ulong index = br->ReadUInt32();
						const unsigned int value_index = index & 0x3FFFFFFF;
						node_value[i][cmd_offset][a] = values[value_index];

						const byte high_order_bits = index >> 30 & 0x03;
						const auto tangent_index = high_order_bits == 0 ? ~0 : value_index + high_order_bits;
						if (tangent_index != ~0)
							node_tangent_value[i][cmd_offset][a] = values[tangent_index];
					}						
					else
					{
						const auto index = br->ReadUInt16();
						const unsigned int value_index = index & 0x3FFF;
						node_value[i][cmd_offset][a] = values[value_index];

						const byte high_order_bits = index >> 14 & 0x03;
						const auto tangent_index = high_order_bits == 0 ? ~0 : value_index + high_order_bits;
						if (tangent_index != ~0)
							node_tangent_value[i][cmd_offset][a] = values[tangent_index];
					}
				}
			}
		}			

		br->Close();
		fs->Close();

		return_value->AnimationCount = animation_count;
		return_value->AnimationName = animation_name;

		return_value->Duration = duration;
		return_value->NodeIndex = node_index;
		return_value->NodeTransformType = node_transform_type;
		return_value->TransformFlag = transform_flag;
		return_value->NodeStepCount = node_step_count;
		return_value->cmdOffsetCount = cmd_offset_count;
		return_value->Frame = frame;
		return_value->NodeValue = node_value;
		return_value->NodeTangentValue = node_tangent_value;
		
		return return_value;
	}
}