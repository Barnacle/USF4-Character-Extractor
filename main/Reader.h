#pragma once

namespace SSF4ce {
	using namespace System;
	using namespace System::IO;

	typedef unsigned short ushort;
	typedef unsigned long ulong;
	typedef unsigned char Byte;

	value struct EMGReturn
	{
		Byte*		DDSid;			// Массив id прикреплённых текстур к подмешам.
		ushort		SubmodelCount;	// Кол-во подмешей в EMG.
		ushort*		IndexCount;		// Массив кол-в индексов каждого подмеша.
		ushort*		NodesCount;		// Массив кол-в костей каждого подмеша.
		ushort		VertexCount;	// Кол-во вертексов.
		ushort		VertexSize;		// Размер блока вертексов.
		ushort**	IndiceArray;	// Массив лент треугольников.
		ushort**	NodesArray;		// Массив костей.
		Byte*		VertexArray;	// Массив блоков вертексов.
	};

	EMGReturn ReadEMG(String^ FileName, int EMGposition) // Входящие данные: имя файла, позиция EMG в EMO
	{
		EMGReturn retval;

		FileStream^ fs = File::OpenRead(FileName);
		BinaryReader^ br = gcnew BinaryReader(fs);
		
		fs->Position = EMGposition + 16; // 16 - Сдвиг на заголовок EMG.

		fs->Position = fs->Position + 4; //EMGHeader1->Number711 = (ushort)br->ReadUInt32(); 
		ushort TextureCount = (ushort)br->ReadUInt32();			// Кол-во привязанных текстур к подмоделям.
		fs->Position = fs->Position + 4; //EMGHeader1->Something = (ushort)br->ReadUInt32();
		ushort TextureOffset = (ushort)br->ReadUInt32();		// Позиция списка сдвигов текстур.

		ushort VertexCount = (ushort)br->ReadUInt16();			// Кол-во вертексов.
		ushort VertexSize = (ushort)br->ReadUInt16();			// Размер блока вертексов.
		ulong  VertexOffset = (ulong)br->ReadUInt32();			// Позиция вертексов в файле.
		fs->Position = fs->Position + 2; //EMGHeader1->Empty = (ushort)br->ReadUInt16(); // Пустые 2 байта. (strips?)
		ushort SubmodelCount = (ushort)br->ReadUInt16();		// Кол-во подмешей в EMG.
		ushort SubMesheListOffset = (ushort)br->ReadUInt16();	// Сдвиг на список адресов подмешей.

		//==================================================================
		// Текстуры.
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
		// Индексы и кости
		//==================================================================
		ushort *IndexCount = new ushort[SubmodelCount]; // Массив кол-в индексов подмешей.
		ushort **IndiceArray = new ushort*[SubmodelCount]; // 

		ushort *NodesCount = new ushort[SubmodelCount];
		ushort **NodesArray = new ushort*[SubmodelCount];

		for (ushort i = 0; i < SubmodelCount; i++)
		{
			fs->Position = EMGposition + 16 + SubMesheListOffset + i * 4; // Ищется адрес подмеша из строки списка подмешей.
			fs->Position = EMGposition + 16 + br->ReadUInt32() + 16; // 16 байт #EMG + читается сдвиг подмеша + 16 байт хрени
			DDSid[i] = id[(Byte)br->ReadUInt16()]; // ID текстуры.
			IndexCount[i] = (ushort)br->ReadUInt16(); // Кол-во индексов.
			NodesCount[i] = (ushort)br->ReadUInt16(); // Кол-во костей.
			
			fs->Position = fs->Position + 32; // пропуск названия из 32-х байтов.

			IndiceArray[i] = new ushort[IndexCount[i]];

			// Заполнение массива индексами подмеша.
			for (int a = 0; a < IndexCount[i]; a++)
			{
				IndiceArray[i][a] = (ushort)br->ReadUInt16();
			}

			NodesArray[i] = new ushort[NodesCount[i]];

			// Заполнение массива костями.
			for (Byte a = 0; a < NodesCount[i]; a++)
			{
				NodesArray[i][a] = (ushort)br->ReadUInt16();
			}
		}

		//==================================================================
		// Вертексы
		//==================================================================
		fs->Position = EMGposition + 16 + VertexOffset; // Адрес вертексов
		Byte* VertexArray = new Byte[VertexCount * VertexSize]; // Массив данных о вертексах
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
		ushort DDScount;	// Кол-во dds в EMB.
		ulong* DDSsize;		// Размеры каждого dds.
		Byte** DDSArray;	// Сами dds.
	};

	EMBReturn ReadEMB(String^ FileName)
	{
		EMBReturn retval;

		FileStream^ fs = File::OpenRead(FileName);
		BinaryReader^ br = gcnew BinaryReader(fs);

		// Кол-во DDS.
		fs->Position = 12;
		ushort DDScount = br->ReadInt16();

		//
		ulong *DDSoffset = new ulong[DDScount];
		ulong *DDSsize = new ulong[DDScount];
		Byte **DDSArray = new Byte*[DDScount];

		// Список сдвигов на DDS и их размеры.
		fs->Position = 32;
		for (ulong i = 0; i < DDScount; i++)
		{
			DDSoffset[i] = br->ReadInt32() + (i * 2 * 4); // + учёт DDSsize
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

		fs->Position = offset; // Пропуск на позицию о костях.
		unsigned int SkeletalInfoOffset = br->ReadUInt32();

		fs->Position = SkeletalInfoOffset; // Переход на позицию данных о костях.
		ushort NodesCount = br->ReadUInt16(); // Кол-во нодов.

		fs->Position = fs->Position + 6; // Пропуск 4 байт.
		ushort StartOffset = br->ReadUInt32(); // Размер заголовка блока.
		ushort NamesOffsetsOffset = br->ReadUInt32(); // Сдвиг на список сдвигов о названиях нодов.

		//==================================================================

		fs->Position = SkeletalInfoOffset + NamesOffsetsOffset; // Сдвиги на названия.
		unsigned int* NodesNamesOffsets = new unsigned int[NodesCount]; // Чтение.
		for (ushort i = 0; i < NodesCount; i++)
			NodesNamesOffsets[i] = br->ReadUInt32();

		char** NodeName = new char*[NodesCount];

		for (ushort i = 0; i < NodesCount; i++)
		{
			fs->Position = SkeletalInfoOffset + NodesNamesOffsets[i];

			ushort size = 1; // Длинна названия для создания массива.
			while (br->ReadChar() != 0)
				size++;

			NodeName[i] = new char[size];

			fs->Position = fs->Position - size; // Возврат позиции.

			for (ushort a = 0; a < size; a++) // Чтение в массив.
				NodeName[i][a] = (char)br->ReadChar();
		}

		//==================================================================

		fs->Position = SkeletalInfoOffset + StartOffset; // Кости.

		short* ParentNodeArray = new short[NodesCount];
		Byte** Matrix4x4 = new Byte*[NodesCount];

		for (ushort i = 0; i < NodesCount; i++)
		{
			ushort temp = br->ReadUInt16();
			if (temp == 65535)					// FFFF - коренной.
				ParentNodeArray[i] = -1;	
			else
				ParentNodeArray[i] = temp;

			fs->Position = fs->Position + 14; // Пропуск на позицию о матрице.

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

		fs->Position = 6; // Заголовок. 
		ushort HeaderSize = br->ReadUInt16();

		fs->Position = 16; // кол-во анимаций.
		ushort AnimationCount = br->ReadUInt16();

		fs->Position = HeaderSize; // сдвиги на анимации
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

			Duration[i]			= br->ReadUInt16();		// Длительность анимации.
			cmdOffsetCount[i]	= br->ReadUInt16();		// cmdOffsetCount
			ulong ValueCount	= br->ReadUInt32();		// valueCount
			ulong temp4			= br->ReadUInt32();		// zero
			ulong NameOffset	= br->ReadUInt32();		// Сдвиг на название.
			ulong ValuesOffset	= br->ReadUInt32();		// valuesOffset

			//==================================================================
			fs->Position = AnimationOffsets[i] + NameOffset + 11; // 11 - хлам.
			ushort size = 1; // Длинна названия для создания массива.
			while (br->ReadChar() != 0)
				size++;
			AnimationName[i] = new char[size];
			fs->Position = fs->Position - size; // Возврат позиции.
			for (ushort a = 0; a < size; a++) // Чтение в массив.
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

				NodeIndex[i][cmdOffset] = br->ReadUInt16(); // индекс кости.
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