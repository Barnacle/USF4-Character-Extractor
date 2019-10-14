#pragma once

namespace SSF4ce {
	using namespace System;
	using namespace IO;

	typedef unsigned short ushort;
	typedef unsigned long ulong;

	value struct EMGReturn
	{
		byte*		DDSid;			// Array of submodel's texture ids.
		ushort		SubmodelCount;	// Submodels in EMG.
		ushort*		IndexCount;		// Array of Indexes amount of each submodel.
		ushort*		NodesCount;		// Array of Nodes amount of each submodel.
		ushort		VertexCount;	// Amount of vertices.
		ushort		VertexSize;		// Size of vertex.
		ushort**	IndiceArray;	// Array of indeces blocks.
		ushort**	NodesArray;		// Array of Nodes.
		byte*		VertexArray;	// Array of vertices blocks.
	};

	// FileName, EMG position in EMO
	inline EMGReturn ReadEMG(String^ FileName, int EMGposition)
	{
		EMGReturn return_value;

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

		const auto offsets = new ushort[texture_count];
		for (auto i = 0; i < texture_count; i++)
			offsets[i] = ushort(br->ReadUInt32());

		const auto id = new byte[texture_count];
		for (auto i = 0; i < texture_count; i++)
		{
			fs->Position = EMGposition + 16 + offsets[i] + 5;
			id[i] = byte(br->ReadChar());
		}

		const auto DDSid = new byte[submodel_count];

		//==================================================================
		// Indeces and nodes
		//==================================================================
		const auto index_count = new ushort[submodel_count]; // Array of Indexes amount of each submodel.
		const auto indices_array = new ushort*[submodel_count];

		const auto nodes_count = new ushort[submodel_count];
		const auto nodes_array = new ushort*[submodel_count];

		for (ushort i = 0; i < submodel_count; i++)
		{
			fs->Position = EMGposition + 16 + submeshes_list_offset + i * 4; // Looking for submesh address in a list of submeshes
			fs->Position = EMGposition + 16 + br->ReadUInt32() + 16; // 16 bytes #EMG + offset of submesh + 16 bytes of trash
			DDSid[i] = id[byte(br->ReadUInt16())]; // Texture ID.
			index_count[i] = ushort(br->ReadUInt16()); // Ammount of indeces.
			nodes_count[i] = ushort(br->ReadUInt16()); // Ammount of nodes.
			
			fs->Position = fs->Position + 32; // skipping name (32 bytes).

			indices_array[i] = new ushort[index_count[i]];

			// Filling array with submesh indeces.
			for (auto a = 0; a < index_count[i]; a++)
			{
				indices_array[i][a] = ushort(br->ReadUInt16());
			}

			nodes_array[i] = new ushort[nodes_count[i]];

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
		const auto vertex_array = new byte[vertex_count * vertex_size]; // Array of vertex data
		for (auto i = 0; i < vertex_count * vertex_size; i++)
		{
			vertex_array[i] = byte(br->ReadByte());
		}

		br->Close();
		fs->Close();

		return_value.DDSid = DDSid;
		return_value.SubmodelCount = submodel_count;
		return_value.IndexCount	= index_count;
		return_value.NodesCount	= nodes_count;
		return_value.VertexCount = vertex_count;
		return_value.VertexSize	= vertex_size;
		return_value.IndiceArray = indices_array;
		return_value.NodesArray	= nodes_array;
		return_value.VertexArray = vertex_array;
		return return_value;
	}

	//==================================================================

	value struct EMBReturn
	{
		ushort DDScount;	// DDS ammount in EMB.
		ulong* DDSsize;		// Size of each DDS.
		byte** DDSArray;	// DDS itself.
	};

	inline EMBReturn ReadEMB(String^ FileName)
	{
		EMBReturn return_value;

		auto fs = File::OpenRead(FileName);
		auto br = gcnew BinaryReader(fs);

		// Кол-во DDS.
		fs->Position = 12;
		const ushort DDScount = br->ReadInt16();

		//
		const auto DDSoffset = new ulong[DDScount];
		const auto DDSsize = new ulong[DDScount];
		const auto DDSArray = new byte*[DDScount];

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
			DDSArray[i] = new byte[DDSsize[i]];

			fs->Position = 32 + DDSoffset[i];

			for (ulong a = 0; a < DDSsize[i]; a++)
			{
				DDSArray[i][a] = byte(br->ReadByte());
			}
		}

		br->Close();
		fs->Close();

		return_value.DDScount = DDScount;
		return_value.DDSsize = DDSsize;
		return_value.DDSArray = DDSArray;		
		return return_value;
	}

	//==================================================================

	value struct SkeletonReturn
	{
		ushort	NodesCount;
		char**	NodeName;
		short*	ParentNodeArray;
		byte**	Matrix4x4;
	};

	inline SkeletonReturn ReadSkeleton(String^ FileName, byte offset) // EMO - 16, EMA - 12
	{
		SkeletonReturn return_value;

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
		const auto nodes_names_offsets = new unsigned int[nodes_count]; // Reading.
		for (auto i = 0; i < nodes_count; i++)
			nodes_names_offsets[i] = br->ReadUInt32();

		const auto node_name = new char*[nodes_count];

		for (auto i = 0; i < nodes_count; i++)
		{
			fs->Position = skeletal_info_offset + nodes_names_offsets[i];

			ushort size = 1; // Length of name for array creation.
			while (br->ReadChar() != 0)
				size++;

			node_name[i] = new char[size];

			fs->Position = fs->Position - size; // Position return.

			for (auto a = 0; a < size; a++) // Reading to array.
				node_name[i][a] = char(br->ReadChar());
		}

		//==================================================================

		fs->Position = skeletal_info_offset + start_offset; // Nodes.

		const auto ParentNodeArray = new short[nodes_count];
		const auto Matrix4x4 = new byte*[nodes_count];

		for (auto i = 0; i < nodes_count; i++)
		{
			const auto temp = br->ReadUInt16();
			if (temp == 65535)	// FFFF - root.
				ParentNodeArray[i] = -1;	
			else
				ParentNodeArray[i] = temp;

			fs->Position = fs->Position + 14; // Skipping to position about matrix.

			Matrix4x4[i] = new byte[64];
			for (ushort a = 0; a < 64; a++)
				Matrix4x4[i][a] = br->ReadByte();
		}

		br->Close();
		fs->Close();

		return_value.NodesCount = nodes_count;
		return_value.NodeName = node_name;
		return_value.ParentNodeArray = ParentNodeArray;
		return_value.Matrix4x4 = Matrix4x4;
		return return_value;
	}

	//==================================================================

	value struct EMAReturn
	{
		ushort AnimationCount;
		char** AnimationName;

		ushort* Duration;
		ushort** NodeIndex;
		byte** NodeTransformType;
		byte** TransformFlag;
		ushort** NodeStepCount;
		ushort* cmdOffsetCount;		
		ushort*** Frame;		
		float*** NodeValue;
		float*** NodeTangentValue;		
	};

	inline EMAReturn ReadEMA(String^ FileName)
	{
		EMAReturn return_value;

		auto fs = File::OpenRead(FileName);
		auto br = gcnew BinaryReader(fs);

		fs->Position = 6; // Header. 
		const auto header_size = br->ReadUInt16();

		fs->Position = 16; // Ammount of animations.
		const auto animation_count = br->ReadUInt16();

		fs->Position = header_size; // Animations offsets
		const auto animation_offsets = new ulong[animation_count];
		for (auto i = 0; i < animation_count; i++)
			animation_offsets[i] = br->ReadUInt32(); //

		const auto animation_name = new char*[animation_count];

		const auto duration = new ushort[animation_count];
		const auto node_index = new ushort*[animation_count];
		const auto cmd_offset_count = new ushort[animation_count];
		const auto node_step_count = new ushort*[animation_count];
		const auto frame = new ushort**[animation_count];
		const auto node_transform_type = new byte*[animation_count];
		const auto node_value = new float**[animation_count];
		const auto node_tangent_value = new float**[animation_count];
		const auto transform_flag = new byte*[animation_count];

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
			animation_name[i] = new char[size];
			fs->Position = fs->Position - size; // Position return.
			for (ushort a = 0; a < size; a++) // Reading in array.
				animation_name[i][a] = char(br->ReadChar());				
			//==================================================================

			fs->Position = animation_offsets[i] + values_offset;
			const auto Values = new float[value_count];
			for (ulong Value = 0; Value < value_count; Value++)
				Values[Value] = br->ReadSingle();

			//==================================================================

			fs->Position = animation_offsets[i] + 20;
			const auto cmd_offsets = new ulong[cmd_offset_count[i]];
			for (ulong cmd_offset = 0; cmd_offset < cmd_offset_count[i]; cmd_offset++)
				cmd_offsets[cmd_offset] = br->ReadUInt32();

			node_index[i] = new ushort[cmd_offset_count[i]];
			node_step_count[i] = new ushort[cmd_offset_count[i]];
			frame[i] = new ushort*[cmd_offset_count[i]];
			node_transform_type[i] = new Byte[cmd_offset_count[i]];
			node_value[i] = new float*[cmd_offset_count[i]];
			node_tangent_value[i] = new float*[cmd_offset_count[i]];
			transform_flag[i] = new Byte[cmd_offset_count[i]];

			for (ulong cmd_offset = 0; cmd_offset < cmd_offset_count[i]; cmd_offset++)
			{
				fs->Position = animation_offsets[i] + cmd_offsets[cmd_offset];

				node_index[i][cmd_offset] = br->ReadUInt16(); // index of node.
				node_transform_type[i][cmd_offset] = char(br->ReadChar()); // 0 -> translation, 1 -> rotation, 2->scale
				transform_flag[i][cmd_offset] = char(br->ReadChar()); // 0 - x, 1 - y, 2 - z
				node_step_count[i][cmd_offset] = br->ReadUInt16(); //(stepCount))
				const auto indices_offset = br->ReadUInt16(); //(indicesOffset));

				frame[i][cmd_offset] = new ushort[node_step_count[i][cmd_offset]];
				node_value[i][cmd_offset] = new float[node_step_count[i][cmd_offset]];
				node_tangent_value[i][cmd_offset] = new float[node_step_count[i][cmd_offset]];

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
						node_value[i][cmd_offset][a] = Values[value_index];

						const byte high_order_bits = index >> 30 & 0x03;
						const auto tangent_index = high_order_bits == 0 ? ~0 : value_index + high_order_bits;
						if (tangent_index != ~0)
							node_tangent_value[i][cmd_offset][a] = Values[tangent_index];
					}						
					else
					{
						const auto index = br->ReadUInt16();
						const unsigned int value_index = index & 0x3FFF;
						node_value[i][cmd_offset][a] = Values[value_index];

						const byte high_order_bits = index >> 14 & 0x03;
						const auto tangent_index = high_order_bits == 0 ? ~0 : value_index + high_order_bits;
						if (tangent_index != ~0)
							node_tangent_value[i][cmd_offset][a] = Values[tangent_index];
					}
				}
			}
		}			

		br->Close();
		fs->Close();

		return_value.AnimationCount = animation_count;
		return_value.AnimationName = animation_name;

		return_value.Duration = duration;
		return_value.NodeIndex = node_index;
		return_value.NodeTransformType = node_transform_type;
		return_value.TransformFlag = transform_flag;
		return_value.NodeStepCount = node_step_count;
		return_value.cmdOffsetCount = cmd_offset_count;		
		return_value.Frame = frame;		
		return_value.NodeValue = node_value;
		return_value.NodeTangentValue = node_tangent_value;
		
		return return_value;
	}
}