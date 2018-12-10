#pragma once

namespace SSF4ce {
	using namespace System;
	using namespace System::IO;

	typedef unsigned short ushort;
	typedef unsigned long ulong;
	typedef unsigned char Byte;

	value struct EMGReturn
	{
		Byte*		DDSid;			// ������ id ������������ ������� � ��������.
		ushort		SubmodelCount;	// ���-�� �������� � EMG.
		ushort*		IndexCount;		// ������ ���-� �������� ������� �������.
		ushort*		NodesCount;		// ������ ���-� ������ ������� �������.
		ushort		VertexCount;	// ���-�� ���������.
		ushort		VertexSize;		// ������ ����� ���������.
		ushort**	IndiceArray;	// ������ ���� �������������.
		ushort**	NodesArray;		// ������ ������.
		Byte*		VertexArray;	// ������ ������ ���������.
	};

	EMGReturn ReadEMG(String^ FileName, int EMGposition) // �������� ������: ��� �����, ������� EMG � EMO
	{
		EMGReturn retval;

		FileStream^ fs = File::OpenRead(FileName);
		BinaryReader^ br = gcnew BinaryReader(fs);
		
		fs->Position = EMGposition + 16; // 16 - ����� �� ��������� EMG.

		fs->Position = fs->Position + 4; //EMGHeader1->Number711 = (ushort)br->ReadUInt32(); 
		ushort TextureCount = (ushort)br->ReadUInt32();			// ���-�� ����������� ������� � ����������.
		fs->Position = fs->Position + 4; //EMGHeader1->Something = (ushort)br->ReadUInt32();
		ushort TextureOffset = (ushort)br->ReadUInt32();		// ������� ������ ������� �������.

		ushort VertexCount = (ushort)br->ReadUInt16();			// ���-�� ���������.
		ushort VertexSize = (ushort)br->ReadUInt16();			// ������ ����� ���������.
		ulong  VertexOffset = (ulong)br->ReadUInt32();			// ������� ��������� � �����.
		fs->Position = fs->Position + 2; //EMGHeader1->Empty = (ushort)br->ReadUInt16(); // ������ 2 �����. (strips?)
		ushort SubmodelCount = (ushort)br->ReadUInt16();		// ���-�� �������� � EMG.
		ushort SubMesheListOffset = (ushort)br->ReadUInt16();	// ����� �� ������ ������� ��������.

		//==================================================================
		// ��������.
		//==================================================================
		fs->Position = EMGposition + 16 + TextureOffset;

		ushort* Offsets = new ushort[TextureCount];
		for (ushort i = 0; i < TextureCount; i++)
			Offsets[i] = (ushort)br->ReadUInt32();			

		Byte* id = new Byte[TextureCount];
		for (ushort i = 0; i < TextureCount; i++)
		{
			fs->Position = EMGposition + 16 + Offsets[i] + 5;
			id[i] = (Byte)br->ReadChar();
		}

		Byte* DDSid = new Byte[SubmodelCount];

		//==================================================================
		// ������� � �����
		//==================================================================
		ushort *IndexCount = new ushort[SubmodelCount]; // ������ ���-� �������� ��������.
		ushort **IndiceArray = new ushort*[SubmodelCount]; // 

		ushort *NodesCount = new ushort[SubmodelCount];
		ushort **NodesArray = new ushort*[SubmodelCount];

		for (ushort i = 0; i < SubmodelCount; i++)
		{
			fs->Position = EMGposition + 16 + SubMesheListOffset + i * 4; // ������ ����� ������� �� ������ ������ ��������.
			fs->Position = EMGposition + 16 + br->ReadUInt32() + 16; // 16 ���� #EMG + �������� ����� ������� + 16 ���� �����
			DDSid[i] = id[(Byte)br->ReadUInt16()]; // ID ��������.
			IndexCount[i] = (ushort)br->ReadUInt16(); // ���-�� ��������.
			NodesCount[i] = (ushort)br->ReadUInt16(); // ���-�� ������.
			
			fs->Position = fs->Position + 32; // ������� �������� �� 32-� ������.

			IndiceArray[i] = new ushort[IndexCount[i]];

			// ���������� ������� ��������� �������.
			for (int a = 0; a < IndexCount[i]; a++)
			{
				IndiceArray[i][a] = (ushort)br->ReadUInt16();
			}

			NodesArray[i] = new ushort[NodesCount[i]];

			// ���������� ������� �������.
			for (Byte a = 0; a < NodesCount[i]; a++)
			{
				NodesArray[i][a] = (ushort)br->ReadUInt16();
			}
		}

		//==================================================================
		// ��������
		//==================================================================
		fs->Position = EMGposition + 16 + VertexOffset; // ����� ���������
		Byte* VertexArray = new Byte[VertexCount * VertexSize]; // ������ ������ � ���������
		for (int i = 0; i < VertexCount * VertexSize; i++)
		{
			VertexArray[i] = (Byte)br->ReadByte();
		}

		br->Close();
		fs->Close();

		retval.DDSid = DDSid;
		retval.SubmodelCount = SubmodelCount;
		retval.IndexCount	= IndexCount;
		retval.NodesCount	= NodesCount;
		retval.VertexCount	= VertexCount;
		retval.VertexSize	= VertexSize;
		retval.IndiceArray	= IndiceArray;
		retval.NodesArray	= NodesArray;
		retval.VertexArray	= VertexArray;
		return retval;
	}

	//==================================================================

	value struct EMBReturn
	{
		ushort DDScount;	// ���-�� dds � EMB.
		ulong* DDSsize;		// ������� ������� dds.
		Byte** DDSArray;	// ���� dds.
	};

	EMBReturn ReadEMB(String^ FileName)
	{
		EMBReturn retval;

		FileStream^ fs = File::OpenRead(FileName);
		BinaryReader^ br = gcnew BinaryReader(fs);

		// ���-�� DDS.
		fs->Position = 12;
		ushort DDScount = br->ReadInt16();

		//
		ulong *DDSoffset = new ulong[DDScount];
		ulong *DDSsize = new ulong[DDScount];
		Byte **DDSArray = new Byte*[DDScount];

		// ������ ������� �� DDS � �� �������.
		fs->Position = 32;
		for (ulong i = 0; i < DDScount; i++)
		{
			DDSoffset[i] = br->ReadInt32() + (i * 2 * 4); // + ���� DDSsize
			DDSsize[i] = br->ReadInt32();
		}				

		//
		for (ulong i = 0; i < DDScount; i++)
		{
			DDSArray[i] = new Byte[DDSsize[i]];

			fs->Position = 32 + DDSoffset[i];

			for (ulong a = 0; a < DDSsize[i]; a++)
			{
				DDSArray[i][a] = (Byte)br->ReadByte();
			}
		}

		br->Close();
		fs->Close();

		retval.DDScount = DDScount;
		retval.DDSsize = DDSsize;
		retval.DDSArray = DDSArray;		
		return retval;
	}

	//==================================================================

	value struct SkeletonReturn
	{
		ushort	NodesCount;
		char**	NodeName;
		short*	ParentNodeArray;
		Byte**	Matrix4x4;
	};

	SkeletonReturn ReadSkeleton(String^ FileName, Byte offset) // EMO - 16, EMA - 12
	{
		SkeletonReturn retval;

		FileStream^ fs = File::OpenRead(FileName);
		BinaryReader^ br = gcnew BinaryReader(fs);

		fs->Position = offset; // ������� �� ������� � ������.
		unsigned int SkeletalInfoOffset = br->ReadUInt32();

		fs->Position = SkeletalInfoOffset; // ������� �� ������� ������ � ������.
		ushort NodesCount = br->ReadUInt16(); // ���-�� �����.

		fs->Position = fs->Position + 6; // ������� 4 ����.
		ushort StartOffset = br->ReadUInt32(); // ������ ��������� �����.
		ushort NamesOffsetsOffset = br->ReadUInt32(); // ����� �� ������ ������� � ��������� �����.

		//==================================================================

		fs->Position = SkeletalInfoOffset + NamesOffsetsOffset; // ������ �� ��������.
		unsigned int* NodesNamesOffsets = new unsigned int[NodesCount]; // ������.
		for (ushort i = 0; i < NodesCount; i++)
			NodesNamesOffsets[i] = br->ReadUInt32();

		char** NodeName = new char*[NodesCount];

		for (ushort i = 0; i < NodesCount; i++)
		{
			fs->Position = SkeletalInfoOffset + NodesNamesOffsets[i];

			ushort size = 1; // ������ �������� ��� �������� �������.
			while (br->ReadChar() != 0)
				size++;

			NodeName[i] = new char[size];

			fs->Position = fs->Position - size; // ������� �������.

			for (ushort a = 0; a < size; a++) // ������ � ������.
				NodeName[i][a] = (char)br->ReadChar();
		}

		//==================================================================

		fs->Position = SkeletalInfoOffset + StartOffset; // �����.

		short* ParentNodeArray = new short[NodesCount];
		Byte** Matrix4x4 = new Byte*[NodesCount];

		for (ushort i = 0; i < NodesCount; i++)
		{
			ushort temp = br->ReadUInt16();
			if (temp == 65535)					// FFFF - ��������.
				ParentNodeArray[i] = -1;	
			else
				ParentNodeArray[i] = temp;

			fs->Position = fs->Position + 14; // ������� �� ������� � �������.

			Matrix4x4[i] = new Byte[64];
			for (ushort a = 0; a < 64; a++)
				Matrix4x4[i][a] = br->ReadByte();
		}

		br->Close();
		fs->Close();

		retval.NodesCount = NodesCount;
		retval.NodeName = NodeName;
		retval.ParentNodeArray = ParentNodeArray;
		retval.Matrix4x4 = Matrix4x4;
		return retval;
	}

	//==================================================================

	value struct EMAReturn
	{
		ushort AnimationCount;
		char** AnimationName;

		ushort* Duration;
		ushort** NodeIndex;
		Byte** NodeTransformType;
		Byte** TransformFlag;
		ushort** NodeStepCount;
		ushort* cmdOffsetCount;		
		ushort*** Frame;		
		float*** NodeValue;
		float*** NodeTangentValue;		
	};

	EMAReturn ReadEMA(String^ FileName)
	{
		EMAReturn retval;

		FileStream^ fs = File::OpenRead(FileName);
		BinaryReader^ br = gcnew BinaryReader(fs);

		fs->Position = 6; // ���������. 
		ushort HeaderSize = br->ReadUInt16();

		fs->Position = 16; // ���-�� ��������.
		ushort AnimationCount = br->ReadUInt16();

		fs->Position = HeaderSize; // ������ �� ��������
		ulong* AnimationOffsets = new ulong[AnimationCount];
		for (ushort i = 0; i < AnimationCount; i++)
			AnimationOffsets[i] = br->ReadUInt32(); //

		char** AnimationName = new char*[AnimationCount];

		ushort* Duration = new ushort[AnimationCount];
		ushort** NodeIndex = new ushort*[AnimationCount];
		ushort* cmdOffsetCount = new ushort[AnimationCount];
		ushort** NodeStepCount = new ushort*[AnimationCount];
		ushort*** Frame = new ushort**[AnimationCount];
		Byte** NodeTransformType = new Byte*[AnimationCount];
		float*** NodeValue = new float**[AnimationCount];
		float*** NodeTangentValue = new float**[AnimationCount];
		Byte** TransformFlag = new Byte*[AnimationCount];

		for (ushort i = 0; i < AnimationCount; i++)
		{
			fs->Position = AnimationOffsets[i];

			Duration[i]			= br->ReadUInt16();		// ������������ ��������.
			cmdOffsetCount[i]	= br->ReadUInt16();		// cmdOffsetCount
			ulong ValueCount	= br->ReadUInt32();		// valueCount
			ulong temp4			= br->ReadUInt32();		// zero
			ulong NameOffset	= br->ReadUInt32();		// ����� �� ��������.
			ulong ValuesOffset	= br->ReadUInt32();		// valuesOffset

			//==================================================================
			fs->Position = AnimationOffsets[i] + NameOffset + 11; // 11 - ����.
			ushort size = 1; // ������ �������� ��� �������� �������.
			while (br->ReadChar() != 0)
				size++;
			AnimationName[i] = new char[size];
			fs->Position = fs->Position - size; // ������� �������.
			for (ushort a = 0; a < size; a++) // ������ � ������.
				AnimationName[i][a] = (char)br->ReadChar();				
			//==================================================================

			fs->Position = AnimationOffsets[i] + ValuesOffset;
			float* Values = new float[ValueCount];
			for (ulong Value = 0; Value < ValueCount; Value++)
				Values[Value] = br->ReadSingle();

			//==================================================================

			fs->Position = AnimationOffsets[i] + 20;
			ulong* cmdOffsets = new ulong[cmdOffsetCount[i]];
			for (ulong cmdOffset = 0; cmdOffset < cmdOffsetCount[i]; cmdOffset++)
				cmdOffsets[cmdOffset] = br->ReadUInt32();

			NodeIndex[i] = new ushort[cmdOffsetCount[i]];
			NodeStepCount[i] = new ushort[cmdOffsetCount[i]];
			Frame[i] = new ushort*[cmdOffsetCount[i]];
			NodeTransformType[i] = new Byte[cmdOffsetCount[i]];
			NodeValue[i] = new float*[cmdOffsetCount[i]];
			NodeTangentValue[i] = new float*[cmdOffsetCount[i]];
			TransformFlag[i] = new Byte[cmdOffsetCount[i]];

			for (ulong cmdOffset = 0; cmdOffset < cmdOffsetCount[i]; cmdOffset++)
			{
				fs->Position = AnimationOffsets[i] + cmdOffsets[cmdOffset];

				NodeIndex[i][cmdOffset] = br->ReadUInt16(); // ������ �����.
				NodeTransformType[i][cmdOffset] = (char)br->ReadChar(); // 0 -> translation, 1 -> rotation, 2->scale
				TransformFlag[i][cmdOffset] = (char)br->ReadChar(); // 0 - x, 1 - y, 2 - z
				NodeStepCount[i][cmdOffset] = br->ReadUInt16(); //(stepCount))
				ushort IndicesOffset = br->ReadUInt16(); //(indicesOffset));

				Frame[i][cmdOffset] = new ushort[NodeStepCount[i][cmdOffset]];
				NodeValue[i][cmdOffset] = new float[NodeStepCount[i][cmdOffset]];
				NodeTangentValue[i][cmdOffset] = new float[NodeStepCount[i][cmdOffset]];

				for (ushort a = 0; a < NodeStepCount[i][cmdOffset]; a++)
				{
					if (TransformFlag[i][cmdOffset] & 0x20)
						Frame[i][cmdOffset][a] = br->ReadUInt16();
					else
						Frame[i][cmdOffset][a] = (ushort)br->ReadByte();						
				}

				fs->Position = AnimationOffsets[i] + cmdOffsets[cmdOffset] + IndicesOffset;

				for (ushort a = 0; a < NodeStepCount[i][cmdOffset]; a++)
				{
					if (TransformFlag[i][cmdOffset] & 0x40)
					{
						ulong index = br->ReadUInt32();
						unsigned int valueindex = (index & 0x3FFFFFFF);
						NodeValue[i][cmdOffset][a] = Values[valueindex];

						unsigned char highOrderBits = ((index >> 30) & 0x03);
						unsigned int tangentIndex = highOrderBits == 0 ? ~0 : (valueindex + highOrderBits);
						if (tangentIndex != ~0)
							NodeTangentValue[i][cmdOffset][a] = Values[tangentIndex];
					}						
					else
					{
						ushort index = br->ReadUInt16();
						unsigned int valueindex = (index & 0x3FFF);
						NodeValue[i][cmdOffset][a] = Values[valueindex];					

						unsigned char highOrderBits = ((index >> 14) & 0x03);
						unsigned int tangentIndex = highOrderBits == 0 ? ~0 : (valueindex + highOrderBits);
						if (tangentIndex != ~0)
							NodeTangentValue[i][cmdOffset][a] = Values[tangentIndex];
					}
				}
			}
		}			

		br->Close();
		fs->Close();

		retval.AnimationCount = AnimationCount;
		retval.AnimationName = AnimationName;

		retval.Duration = Duration;
		retval.NodeIndex = NodeIndex;
		retval.NodeTransformType = NodeTransformType;
		retval.TransformFlag = TransformFlag;
		retval.NodeStepCount = NodeStepCount;
		retval.cmdOffsetCount = cmdOffsetCount;		
		retval.Frame = Frame;		
		retval.NodeValue = NodeValue;
		retval.NodeTangentValue = NodeTangentValue;
		
		return retval;
	}
}