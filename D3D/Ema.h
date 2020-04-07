// https://sourceforge.net/projects/sf4viewer/

#pragma once

#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <fstream>

#define M_PI 3.141592653589793238462643

template<class Real>
void leftHandToEulerAnglesXYZ(const Real m[16], Real& rfXAngle, Real& rfYAngle, Real& rfZAngle)
{
	// +-           -+   +-                                      -+
	// | r00 r01 r02 |   |  cy*cz  cz*sx*sy-cx*sz  cx*cz*sy+sx*sz |
	// | r10 r11 r12 | = |  cy*sz  cx*cz+sx*sy*sz -cz*sx+cx*sy*sz |
	// | r20 r21 r22 |   | -sy     cy*sx           cx*cy          |
	// +-           -+   +-                                      -+

	if (m[8] < Real(1.0))
	{
		if (m[8] > -Real(1.0))
		{
			// y_angle = asin(-r20)
			// z_angle = atan2(r10,r00)
			// x_angle = atan2(r21,r22)
			rfYAngle = Real(asin(-double(m[8])));
			rfZAngle = atan2(m[4], m[0]);
			rfXAngle = atan2(m[9], m[10]);
			return;//EA_UNIQUE
		}
		else
		{
			// y_angle = +pi/2
			// x_angle - z_angle = atan2(r01,r02)
			// WARNING.  The solution is not unique.  Choosing x_angle = 0.
			rfYAngle = Real(0.5 * M_PI);
			rfZAngle = -atan2(m[1], m[2]);
			rfXAngle = Real(0.0);
			return;//EA_NOT_UNIQUE_DIF
		}
	}
	else
	{
		// y_angle = -pi/2
		// x_angle + z_angle = atan2(-r01,-r02)
		// WARNING.  The solution is not unique.  Choosing x_angle = 0;
		rfYAngle = -Real(0.5 * M_PI);
		rfZAngle = atan2(-m[1], -m[2]);
		rfXAngle = Real(0.0);
		return;//EA_NOT_UNIQUE_SUM
	}
}

inline void decomposeMatrix(float rotation[3], float scale[3], float translation[3], const float matrix[16], float rotationQuaternion[4])
{
	if (matrix == nullptr)
		return;

	D3DXMATRIX originalMatrix(matrix);
	D3DXQUATERNION q;
	D3DXVECTOR3 originalScale;
	D3DXVECTOR3 originalTrans;
	D3DXMatrixDecompose(&originalScale, &q, &originalTrans, &originalMatrix);

	memcpy(translation, static_cast<float*>(originalTrans), 3 * sizeof(float));
	memcpy(scale, static_cast<float*>(originalScale), 3 * sizeof(float));
	memcpy(rotationQuaternion, static_cast<float*>(q), 4 * sizeof(float));

	D3DXMATRIX m;
	D3DXMatrixTranspose(&m, &originalMatrix);
	leftHandToEulerAnglesXYZ<float>(m, rotation[0], rotation[1], rotation[2]);

	rotation[0] *= float(180. / M_PI);
	rotation[1] *= float(180. / M_PI);
	rotation[2] *= float(180. / M_PI);
}

inline void composeMatrixQuat(const D3DXQUATERNION & rotation, float scale[3], float translation[3], float matrix[16])
{
	if (matrix == nullptr)
		return;

	D3DXMATRIX translationMatrix, scalingMatrix, rotationMatrix;
	D3DXMatrixTranslation(&translationMatrix, translation[0], translation[1], translation[2]);
	D3DXMatrixScaling(&scalingMatrix, scale[0], scale[1], scale[2]);
	D3DXMatrixRotationQuaternion(&rotationMatrix, &rotation);

	//store result
	auto fullMatrix = scalingMatrix * rotationMatrix * translationMatrix;
	memcpy(matrix, static_cast<float*>(fullMatrix), 16 * sizeof(float));
}

//Pitch->X axis, Yaw->Y axis, Roll->Z axis
inline void eulerToQuaternionXYZ(float fPitch, float fYaw, float fRoll, float quaternion[4])
{
	const auto fSinPitch(sin(fPitch*0.5F));
	const auto fCosPitch(cos(fPitch*0.5F));
	const auto fSinYaw(sin(fYaw*0.5F));
	const auto fCosYaw(cos(fYaw*0.5F));
	const auto fSinRoll(sin(fRoll*0.5F));
	const auto fCosRoll(cos(fRoll*0.5F));
	const auto fCosPitchCosYaw(fCosPitch*fCosYaw);
	const auto fSinPitchSinYaw(fSinPitch*fSinYaw);
	quaternion[0] = fSinRoll * fCosPitchCosYaw - fCosRoll * fSinPitchSinYaw;
	quaternion[1] = fCosRoll * fSinPitch * fCosYaw + fSinRoll * fCosPitch * fSinYaw;
	quaternion[2] = fCosRoll * fCosPitch * fSinYaw - fSinRoll * fSinPitch * fCosYaw;
	quaternion[3] = fCosRoll * fCosPitchCosYaw + fSinRoll * fSinPitchSinYaw;
}

struct EMAAnimationHeader{
	unsigned short duration;
	unsigned short cmdOffsetCount;
	unsigned long valueCount;
	unsigned long zero;
	unsigned long nameOffset;
	unsigned long valuesOffset;
};
struct EMAAnimationCommandHeader{
	unsigned short boneIndex;
	unsigned char transformType;//0 -> translation, 1 -> rotation, 2->scale
	unsigned char flags;//4bits : ? / 2bits: transform component ( a record has 0, the next 1, then 2 )
	unsigned short stepCount;
	unsigned short indicesOffset;
};
struct EMASkelettonHeader{
	unsigned short nodeCount;
	unsigned short unknown0x02;
	unsigned short ikDataCount;//small number
	unsigned short unknown0x06;//0
	unsigned long skeletonStartOffset;
	unsigned long skeletonNameAddressOffset;
	// 0x10
	unsigned long unknown0x10;
	unsigned long unknown0x14;//0
	unsigned long unknown0x18;//address for bunch of FF's
	unsigned long matrixOffset;
	// 0x20
	unsigned long ikDataOffset;
};
struct EMASkelettonNodeTemp{
	unsigned short parent;//FFFF if root
	unsigned short child1;
	unsigned short child2;//FFFF if none
	unsigned short child3;//FFFF if none
	unsigned short child4;//FFFF if none
	unsigned short flags;
	float unknown4;//0
	float matrix[16];
};
struct EMASkelettonNode{
	unsigned short parent;//FFFF if root
	unsigned short child1;
	unsigned short sibling;//FFFF if none
	unsigned short flags;

	float unknownScale;

	unsigned short number;

	unsigned long update_flags;

	float matrix[16];
	float translation[3];
	float scale[3];
	float rotation[3];
	float rotationQuaternion[4];

	//runtime values (filled after a EAMData::setupFrame() call)
	float animatedMatrix[16];
	float animatedTranslation[3];
	float animatedScale[3];
	float animatedRotation[3];
	float animatedRotationQuaternion[4];

	bool animatedAbsoluteRotationFlag;
	bool animatedAbsoluteScaleFlag;
	bool animatedAbsoluteTranslationFlag;

	bool animationProcessingDone;
};
struct EMASkeletonIKData{
	unsigned short method;
	unsigned short dataSize;
	unsigned char data[0x20];
};

struct EMAData
{
	struct EMAAnimationCommandStep
	{
		unsigned short timing;
		unsigned int index;
		unsigned int tangentIndex;
	};
	enum ETransformType
	{
		E_TRANSLATION = 0
		, E_ROTATION
		, E_SCALING
		, E_NOP = -1
	};
	typedef std::vector<EMAAnimationCommandStep> CommandSequence;
	struct Commands
	{
		CommandSequence steps;
		bool absolute;
	};
	typedef std::map<unsigned char, Commands> CommandsPerComponent;
	typedef std::map<ETransformType, CommandsPerComponent> CommandsPerComponentPerType;
	typedef std::map<unsigned short, CommandsPerComponentPerType> CommandsPerComponentPerTypePerBone;
	struct EMAAnimation
	{
		std::string name;
		unsigned short duration;
		std::vector<float> values;
		CommandsPerComponentPerTypePerBone commandsPerComponentPerTypePerBone;
	};
public:
	typedef std::map<unsigned short, EMASkelettonNode> SkelettonNodePerNumberMap;
	typedef std::vector<EMASkeletonIKData> SkeletonIKData;
	EMAAnimationHeader m_animationHeader;
	unsigned long m_nodeCount;
	SkelettonNodePerNumberMap m_skelettonNodes;
	std::map<unsigned short, std::string> m_skelettonNodeNames;
	float m_matrix[16];

	SkeletonIKData m_ikData;
	std::vector<EMAAnimation> m_animations;
	std::map<std::string, unsigned int> m_animationIndexPerName;
	std::vector<std::string> m_animationNames;

	~EMAData()
	{
		freeData();
	}

	void freeData()
	{
		m_nodeCount = 0;
		m_skelettonNodes.clear();
		m_skelettonNodeNames.clear();
		m_animations.clear();
		m_animationIndexPerName.clear();
		m_animationNames.clear();
	}

	std::vector<std::string> const& getAnimationNames() const
	{
		return m_animationNames;
	}

	unsigned short getAnimationDuration(std::string const& name) const
	{
		auto it = m_animationIndexPerName.find(name);
		return (m_animationIndexPerName.end() != it) ? (it->second<m_animations.size()) ? m_animations[it->second].duration : 0 : 0;
	}

	void setupPaletteNames(std::map<std::string, unsigned short> & matrixNames)
	{
		for (auto itNode = m_skelettonNodeNames.begin(); itNode != m_skelettonNodeNames.end(); itNode++)
		{
			matrixNames.insert(std::map<std::string, unsigned short>::value_type(itNode->second, itNode->first));
		}
	}

	void setupFrame(std::string const& name, float frame)
	{
		const std::map<std::string, unsigned int>::const_iterator it = m_animationIndexPerName.find(name);

		const auto animationIndex = m_animationIndexPerName.end() != it ? it->second : ~0;

		auto currentAnimation = animationIndex<m_animations.size() ? &m_animations[animationIndex] : nullptr;

		const auto integerFrame = ceil(frame);
		const auto frameFixed = currentAnimation == nullptr ? 0 : (int)integerFrame % currentAnimation->duration - (integerFrame - frame);
		for (auto itNode = m_skelettonNodes.begin(); itNode != m_skelettonNodes.end(); itNode++)
		{
			auto& node = itNode->second;

			decomposeMatrix(node.rotation, node.scale, node.translation, node.matrix, node.rotationQuaternion);

			node.animationProcessingDone = false;
			node.animatedAbsoluteRotationFlag = false;
			node.animatedAbsoluteScaleFlag = false;
			node.animatedAbsoluteTranslationFlag = false;
			memset(node.animatedRotation, 0, 3 * sizeof(float));
			memset(node.animatedScale, 0, 3 * sizeof(float));
			memset(node.animatedTranslation, 0, 3 * sizeof(float));
			memset(node.animatedRotationQuaternion, 0, 4 * sizeof(float));
			memset(node.animatedMatrix, 0, 16 * sizeof(float));

			// rotation
			node.animatedRotationQuaternion[3] = 1.0;
			// scale
			node.animatedScale[0] = 1.0;
			node.animatedScale[1] = 1.0;
			node.animatedScale[2] = 1.0;
			// matrix
			node.animatedMatrix[0] = 1.0;
			node.animatedMatrix[5] = 1.0;
			node.animatedMatrix[10] = 1.0;
			node.animatedMatrix[15] = 1.0;
			// flags
			node.update_flags = 0;

			if (currentAnimation != 0)
			{
				CommandsPerComponentPerTypePerBone::const_iterator boneCommandsIt = currentAnimation->commandsPerComponentPerTypePerBone.find(node.number);
				if (currentAnimation->commandsPerComponentPerTypePerBone.end() != boneCommandsIt)
				{
					auto const& commandsPerComponentPerType = boneCommandsIt->second;

					// translation
					if (getTransform(*currentAnimation, boneCommandsIt->second, E_TRANSLATION, frameFixed, node.animatedTranslation, node.animatedAbsoluteTranslationFlag))
					{
						if (node.animatedAbsoluteTranslationFlag)
							node.update_flags |= 0x00010000;
						else
							node.update_flags |= 0x00000001;
					}

					// rotation
					if (getTransform(*currentAnimation, boneCommandsIt->second, E_ROTATION, frameFixed, node.animatedRotation, node.animatedAbsoluteRotationFlag))
					{
						eulerToQuaternionXYZ(
							node.animatedRotation[1] * float(M_PI / 180.),
							node.animatedRotation[2] * float(M_PI / 180.),
							node.animatedRotation[0] * float(M_PI / 180.),
							node.animatedRotationQuaternion);

						if (node.animatedAbsoluteRotationFlag)
							node.update_flags |= 0x00020000;
						else
							node.update_flags |= 0x00000002;
					}

					// scale
					if (getTransform(*currentAnimation, boneCommandsIt->second, E_SCALING, frameFixed, node.animatedScale, node.animatedAbsoluteScaleFlag))
					{
						if (node.animatedAbsoluteScaleFlag)
							node.update_flags |= 0x00040000;
						else
							node.update_flags |= 0x00000004;
					}
				}
			}

			// translation
			if (node.update_flags & 0x00010001)
			{
				memcpy(node.translation, node.animatedTranslation, 3 * sizeof(float));
			}
			else
			{
				memcpy(node.animatedTranslation, node.translation, 3 * sizeof(float));
			}

			// rotation
			if (node.update_flags & 0x00020002)
			{
				memcpy(node.rotation, node.animatedRotation, 3 * sizeof(float));
				memcpy(node.rotationQuaternion, node.animatedRotationQuaternion, 4 * sizeof(float));
			}
			else
			{
				memcpy(node.animatedRotation, node.rotation, 3 * sizeof(float));
				memcpy(node.animatedRotationQuaternion, node.rotationQuaternion, 4 * sizeof(float));
			}

			// scale
			if (node.update_flags & 0x00040004)
			{
				memcpy(node.scale, node.animatedScale, 3 * sizeof(float));
			}
			else
			{
				memcpy(node.animatedScale, node.scale, 3 * sizeof(float));
			}

			// transform matrix
			composeMatrixQuat(D3DXQUATERNION(node.animatedRotationQuaternion), node.animatedScale, node.animatedTranslation, node.animatedMatrix);
			memcpy(node.matrix, node.animatedMatrix, 16 * sizeof(float));
		}
	}

	template<typename F>
	F hermiteInterpolation(F P1, F T1, F P2, F T2, F s)
	{
		F s2 = s*s;
		F s3 = s*s*s;
		F h1 = 2 * s3 - 3 * s2 + 1;          // calculate basis function 1
		F h2 = -2 * s3 + 3 * s2;              // calculate basis function 2
		F h3 = s3 - 2 * s2 + s;          // calculate basis function 3
		F h4 = s3 - s2;              // calculate basis function 4
		return  h1*P1 +                    // multiply and sum all funtions
			h2*P2 +                    // together to build the interpolated
			h3*T1 +                    // point along the curve.
			h4*T2;
	}

	bool getTransform(EMAAnimation const& currentAnimation, CommandsPerComponentPerType const& commandsPerComponentPerType, EMAData::ETransformType type, float frame, float values[3], bool& globalValueFlag)
	{
		auto animated = false;
		const auto itCommandsPerType = commandsPerComponentPerType.find(type);
		if (itCommandsPerType != commandsPerComponentPerType.end())
		{
			auto const& commandsPerComponent(itCommandsPerType->second);
			for (auto itCommandsPerComponent = commandsPerComponent.begin(); itCommandsPerComponent != commandsPerComponent.end(); ++itCommandsPerComponent)
			{
				if (itCommandsPerComponent->first >= 3)
				{
					continue;
				}

				auto const& commands(itCommandsPerComponent->second);
				auto const& commandSequence(commands.steps);
				//there is always a step 0 at first (so we have a new step 0 when there is no animation)
				auto itStep = commandSequence.begin();
				auto itPrevStep = itStep;
				++itStep;
				for (; itStep != commandSequence.end(); itPrevStep = itStep, ++itStep)
				{
					if (float(itStep->timing) >= frame)
					{
						const auto s = (frame - float(itPrevStep->timing)) / float(itStep->timing - itPrevStep->timing);    // scale goes from 0 to 1
						const auto P1 = currentAnimation.values[itPrevStep->index];
						const auto P2 = currentAnimation.values[itStep->index];
						const auto T1 = itPrevStep->tangentIndex == ~0 ? 0.f : currentAnimation.values[itPrevStep->tangentIndex];
						const auto T2 = itStep->tangentIndex == ~0 ? 0.f : currentAnimation.values[itStep->tangentIndex];
						values[itCommandsPerComponent->first] = hermiteInterpolation(P1, T1, P2, T2, s);
						globalValueFlag |= commands.absolute;
						animated = true;
						break;
					}
				}
			}
		}
		return animated;
	}

	static std::string readZeroTerminatedString(std::istream& file)
	{
		std::string s;
		char c;
		for (;;)
		{
			file.read(reinterpret_cast<char*>(&c), sizeof (char));
			if (c)
			{
				s.push_back(c);
			}
			else
			{
				break;
			}
		}
		return s;
	}

	bool readAnimation(EMAAnimation& currentAnimation, std::istream& file, unsigned long animationBlockOffset)
	{
		currentAnimation.commandsPerComponentPerTypePerBone.clear();
		currentAnimation.values.clear();

		file.seekg(animationBlockOffset, std::ios::beg);
		file.read(reinterpret_cast<char*>(&m_animationHeader), sizeof (EMAAnimationHeader));

		std::vector<unsigned long> cmdOffsets;
		cmdOffsets.resize(m_animationHeader.cmdOffsetCount);
		file.read(reinterpret_cast<char*>(&cmdOffsets.front()), sizeof (unsigned long)* m_animationHeader.cmdOffsetCount);

		//second half of the animation (float values)
		file.seekg(animationBlockOffset + m_animationHeader.valuesOffset, std::ios::beg);
		currentAnimation.values.resize(m_animationHeader.valueCount);
		file.read(reinterpret_cast<char*>(&currentAnimation.values.front()), sizeof (float)* m_animationHeader.valueCount);

		currentAnimation.duration = m_animationHeader.duration;

		//animation name
		file.seekg(animationBlockOffset + m_animationHeader.nameOffset + 10, std::ios::beg);

		unsigned char stringLen;
		file.read(reinterpret_cast<char*>(&stringLen), sizeof (unsigned char));

		char* str = new char[stringLen + 1];
		str[stringLen] = 0;
		file.read(reinterpret_cast<char*>(str), sizeof (char)* stringLen);
		currentAnimation.name = str;

		for (unsigned long i = 0; i<m_animationHeader.cmdOffsetCount; i++)
		{
			const int currentOffset = cmdOffsets[i] + animationBlockOffset;
			//int currentSize = ((i+1)<m_animationHeader.cmdOffsetCount ? cmdOffsets[i+1] : m_animationHeader.valuesOffset)-cmdOffsets[i];
			file.seekg(currentOffset, std::ios::beg);
			EMAAnimationCommandHeader commandHeader;
			file.read(reinterpret_cast<char*>(&commandHeader), sizeof (EMAAnimationCommandHeader));

			auto transformType =
				commandHeader.transformType == 0 ? E_TRANSLATION
				: commandHeader.transformType == 1 ? E_ROTATION
				: commandHeader.transformType == 2 ? E_SCALING
				: E_NOP;
			unsigned char transformComponent = commandHeader.flags & 0x03;
			auto& commandsPerComponentPerType = currentAnimation.commandsPerComponentPerTypePerBone[commandHeader.boneIndex];
			auto& commandsPerComponent = commandsPerComponentPerType[transformType];
			auto& commands = commandsPerComponent[transformComponent];
			auto& commandSequence(commands.steps);
			commands.absolute = (commandHeader.flags & 0x10) != 0;

			commands.steps.resize(commandHeader.stepCount);

			unsigned int readBytes = 0;
			if (commandHeader.flags & 0x20)
			{
				for (auto itStep = commandSequence.begin(); itStep != commandSequence.end(); ++itStep)
				{
					unsigned short timing16;
					file.read(reinterpret_cast<char*>(&timing16), sizeof (unsigned short));
					readBytes += sizeof (unsigned short);
					itStep->timing = timing16;
				}
			}
			else
			{
				for (auto itStep = commandSequence.begin(); itStep != commandSequence.end(); ++itStep)
				{
					unsigned char timing8;
					file.read(reinterpret_cast<char*>(&timing8), sizeof (unsigned char));
					readBytes += sizeof (unsigned char);
					itStep->timing = timing8;
				}
			}

			if (readBytes<commandHeader.indicesOffset)
			{
				file.seekg(commandHeader.indicesOffset + currentOffset, std::ios::beg);
			}

			if (commandHeader.flags & 0x40)
			{
				for (auto itStep = commandSequence.begin(); itStep != commandSequence.end(); ++itStep)
				{
					unsigned long index;
					file.read(reinterpret_cast<char*>(&index), sizeof (unsigned long));
					itStep->index = index & 0x3FFFFFFF;
					const unsigned char highOrderBits = index >> 30 & 0x03;
					itStep->tangentIndex = highOrderBits == 0 ? ~0 : (itStep->index + highOrderBits);
				}
			}
			else
			{
				for (auto itStep = commandSequence.begin(); itStep != commandSequence.end(); ++itStep)
				{
					unsigned short index16;
					file.read(reinterpret_cast<char*>(&index16), sizeof (unsigned short));
					itStep->index = index16 & 0x3FFF;
					const unsigned char highOrderBits = index16 >> 14 & 0x03;
					itStep->tangentIndex = highOrderBits == 0 ? ~0 : itStep->index + highOrderBits;
				}
			}
		}
		return true;
	}

	bool load(std::string emaFileName, unsigned long emaBlockOffset)
	{
		freeData();

		std::ifstream file(emaFileName.c_str(), std::ios::in | std::ios::binary);
		if (file.bad())
		{
			return false;
		}
		char tokenEMA[5];
		tokenEMA[4] = 0;
		file.seekg(emaBlockOffset, std::ios::beg);
		file.read(reinterpret_cast<char*>(reinterpret_cast<unsigned char*>(tokenEMA)), sizeof (unsigned char)* 4);
		if (strcmp("#EMA", tokenEMA) != 0)
		{
			file.close();
			return false;
		}

		//#EMA -> base skeleton pose

		file.seekg(emaBlockOffset + 6, std::ios::beg);
		unsigned short headerSize;
		file.read(reinterpret_cast<char*>(&headerSize), sizeof (unsigned short));

		file.seekg(emaBlockOffset + 12, std::ios::beg);
		unsigned long skeletonOffset;
		file.read(reinterpret_cast<char*>(&skeletonOffset), sizeof (unsigned long));

		file.seekg(emaBlockOffset + 16, std::ios::beg);
		unsigned short animationCount;
		file.read(reinterpret_cast<char*>(&animationCount), sizeof (unsigned short));

		std::vector<unsigned long> animationDataAddresses;
		animationDataAddresses.resize(animationCount);
		file.seekg(emaBlockOffset + headerSize, std::ios::beg);
		file.read(reinterpret_cast<char*>(&animationDataAddresses.front()), sizeof (unsigned long)*animationCount);

		if(skeletonOffset != 0)
		{
			auto skeletonAdress = emaBlockOffset + skeletonOffset;

			file.seekg(skeletonAdress, std::ios::beg);
			EMASkelettonHeader skelettonHeader{};
			file.read(reinterpret_cast<char*>(&skelettonHeader), sizeof(EMASkelettonHeader));

			m_nodeCount = skelettonHeader.nodeCount;

			std::vector<unsigned long> skeletonNameAddresses;
			skeletonNameAddresses.resize(m_nodeCount);
			file.seekg(skeletonAdress + skelettonHeader.skeletonNameAddressOffset, std::ios::beg);
			file.read(reinterpret_cast<char*>(&skeletonNameAddresses.front()), sizeof(unsigned long) * m_nodeCount);

			for (unsigned int i = 0; i < m_nodeCount; i++)
			{
				file.seekg(skeletonAdress + skeletonNameAddresses[i], std::ios::beg);
				m_skelettonNodeNames.insert(std::map<unsigned short, std::string>::value_type(i, readZeroTerminatedString(file)));
			}

			//Nodes
			file.seekg(skeletonAdress + skelettonHeader.skeletonStartOffset, std::ios::beg);
			for (unsigned int i = 0; i < m_nodeCount; i++)
			{
				EMASkelettonNodeTemp skelettonNodeTemp{};
				file.read(reinterpret_cast<char*>(&skelettonNodeTemp), sizeof(EMASkelettonNodeTemp));

				EMASkelettonNode skelettonNode{};
				skelettonNode.number = i;
				skelettonNode.parent = skelettonNodeTemp.parent;
				skelettonNode.child1 = skelettonNodeTemp.child1;
				skelettonNode.sibling = skelettonNodeTemp.child2;
				skelettonNode.flags = skelettonNodeTemp.flags;
				skelettonNode.unknownScale = skelettonNodeTemp.unknown4;
				memcpy(skelettonNode.matrix, skelettonNodeTemp.matrix, 16 * sizeof(float));

				decomposeMatrix(skelettonNode.rotation, skelettonNode.scale, skelettonNode.translation, skelettonNode.matrix, skelettonNode.rotationQuaternion);

				m_skelettonNodes.insert(SkelettonNodePerNumberMap::value_type(i, skelettonNode));
			}

			//Matrix
			if (skelettonHeader.matrixOffset != 0)
			{
				file.seekg(skeletonAdress + skelettonHeader.matrixOffset, std::ios::beg);
				file.read(reinterpret_cast<char*>(m_matrix), sizeof(float) * 16);
				// [m00 m01 m02]
				// [m10 m11 m12]
				// [m20 m21 m22]
				// heading = Math.atan2(-m.m20,m.m00);
				// bank = Math.atan2(-m.m12,m.m11);
				// attitude = Math.asin(m.m10);
				float translation[] = { -m_matrix[12], m_matrix[14], m_matrix[13] };
				auto rx = atan2(-m_matrix[2], m_matrix[0]);
				auto ry = atan2(-m_matrix[9], m_matrix[5]);
				auto rz = asin(m_matrix[1]);
			}
			else
			{
				memset(m_matrix, 0, 16 * sizeof(float));
				m_matrix[0] = m_matrix[5] = m_matrix[10] = m_matrix[15] = 1.f;
			}

			// read ik information
			if (0 < skelettonHeader.ikDataCount && 0 != skelettonHeader.ikDataOffset)
			{
				file.seekg(skeletonAdress + skelettonHeader.ikDataOffset, std::ios::beg);

				m_ikData.resize(skelettonHeader.ikDataCount);

				for (unsigned int i = 0; i < skelettonHeader.ikDataCount; i++)
				{
					file.read(reinterpret_cast<char*>(&m_ikData[i].method), sizeof(unsigned short));
					file.read(reinterpret_cast<char*>(&m_ikData[i].dataSize), sizeof(unsigned short));
					memset(m_ikData[i].data, 0, 0x20);
					file.read(reinterpret_cast<char*>(m_ikData[i].data), sizeof(unsigned char) * min((m_ikData[i].dataSize - 4), 0x20));
				}
			}
		}
		else
		{
			m_skelettonNodeNames.insert(std::map<unsigned short, std::string>::value_type(0, "camera"));
			EMASkelettonNode skelettonNode{};
			m_skelettonNodes.insert(SkelettonNodePerNumberMap::value_type(0, skelettonNode));
		}

		// read animations
		m_animations.resize(animationCount);
		for (unsigned int i = 0; i < animationCount; ++i)
		{
			auto animationBlockOffset = emaBlockOffset + animationDataAddresses[i];
			readAnimation(m_animations[i], file, animationBlockOffset);
			m_animationIndexPerName.insert(std::map<std::string, unsigned int>::value_type(m_animations[i].name, i));
			m_animationNames.push_back(m_animations[i].name);
		}

		file.close();

		return true;
	}
};

class EMARenderer
{
	EMAData emaData;
public:
	EMARenderer()
	= default;

	bool setup(std::string emaFileName, unsigned long emaBlockOffset)
	{
		const auto ok = emaData.load(emaFileName, emaBlockOffset);
		return ok;
	}

	std::vector<std::string> const& getAnimationNames() const
	{
		return emaData.getAnimationNames();
	}
	unsigned short getAnimationDuration(std::string const& name) const
	{
		return emaData.getAnimationDuration(name);
	}
	void setupPaletteNames(std::map<std::string, unsigned short> & matrixNames)
	{
		emaData.setupPaletteNames(matrixNames);
	}

	void updateDeviceObjects(std::string const& animationName, float frame, float(&structure)[500][6], std::string(&names)[500])
	{
		std::map<int, D3DXMATRIX> matrixPalette;
		setupMatrixPalette(animationName, frame, matrixPalette);
		auto& skelettonNodes = emaData.m_skelettonNodes;

		for (EMAData::SkelettonNodePerNumberMap::const_iterator it = skelettonNodes.begin(); it != skelettonNodes.end(); it++)
		{
			auto const& node = it->second;

			std::map<int, D3DXMATRIX>::const_iterator itNodeMatrix = matrixPalette.find(node.number);
			std::map<int, D3DXMATRIX>::const_iterator itParentNodeMatrix = matrixPalette.find(node.parent);

			auto id = itNodeMatrix->first;

			if (itNodeMatrix == matrixPalette.end() || itParentNodeMatrix == matrixPalette.end())
			{
				continue;
			}

			auto MatrixWorld(itNodeMatrix->second);
			auto MatrixParent(itParentNodeMatrix->second);

			D3DXMATRIX MatrixParentInverse;
			D3DXMatrixInverse(&MatrixParentInverse, 0, &MatrixParent);

			std::map<unsigned short, std::string>::const_iterator itRefSkeletonNodeName = emaData.m_skelettonNodeNames.find(node.number);
			names[id] = itRefSkeletonNodeName->second;

			D3DXMATRIX LocalMatrix;

			if (names[id] != "camera")
				LocalMatrix = MatrixWorld * MatrixParentInverse;
			else
				LocalMatrix = MatrixWorld;

			D3DXVECTOR3 translation, rotation, scale;
			D3DXQUATERNION rotation_quaternion;
			decomposeMatrix(rotation, scale, translation, LocalMatrix, rotation_quaternion);

			structure[id][0] = translation.x;
			structure[id][1] = translation.y;
			structure[id][2] = translation.z;
			structure[id][3] = rotation.x * float(M_PI / 180.);
			structure[id][4] = rotation.y * float(M_PI / 180.);
			structure[id][5] = rotation.z * float(M_PI / 180.);
		};
	}

	void setupMatrixPalette(std::string const& name, float frame, std::map<int, D3DXMATRIX> & matrixPalette)
	{
		auto& skelettonNodes = emaData.m_skelettonNodes;

		emaData.setupFrame(name, frame);

		for (auto it = skelettonNodes.begin(); it != skelettonNodes.end(); it++)
		{
			auto& node = it->second;
			update_node<true, false>(node.number);
		}

		for (unsigned long i = 0; i < emaData.m_ikData.size(); ++i)
		{
			updateIKData(i);
		}

		for (auto it = skelettonNodes.begin(); it != skelettonNodes.end(); it++)
		{
			auto& node = it->second;
			update_node<true, false>(node.number);

			matrixPalette.insert(std::map<int, D3DXMATRIX>::value_type(node.number, D3DXMATRIX(node.animatedMatrix)));
		}
	}

	template<bool initialize, bool update_parent>
	bool update_node(unsigned short nodeNumber)
	{
		auto& skelettonNodes = emaData.m_skelettonNodes;
		auto nodeIt = skelettonNodes.find(nodeNumber);
		if (skelettonNodes.end() != nodeIt)
		{
			auto& node = nodeIt->second;
			auto parentNumber = node.parent;

			const EMASkelettonNode * parent_node = nullptr;
			const EMAData::SkelettonNodePerNumberMap::const_iterator parentIt = skelettonNodes.find(parentNumber);
			if (skelettonNodes.end() != parentIt)
			{
				parent_node = &parentIt->second;
			}

			if (update_parent && parent_node)
			{
				update_node<initialize, update_parent>(parent_node->number);
			}

			auto update = false;

			if (initialize)
			{
				update = (update_parent || (node.flags & 0x00008004) == 0);
				update = update && ((node.update_flags & 0x80000000) == 0);
				update = update && ((parentNumber == 0xFFFF) || (parent_node && (parent_node->update_flags & 0x80000000)) != 0);
			}
			else
			{
				update = (parentNumber != 0xFFFF) && ((node.update_flags & 0x70000000) == 0);
			}

			if (!update)
			{
				if (!initialize)
				{
					update_node<initialize, update_parent>(node.sibling);
				}

				return ((node.update_flags & 0x80000000) != 0);
			}

			D3DXMATRIX matrix(node.matrix);

			D3DXVECTOR3 translation, rotation, scale;
			D3DXQUATERNION rotation_quaternion;

			decomposeMatrix(rotation, scale, translation, matrix, rotation_quaternion);

			// translation
			{
				if ((node.update_flags & 0x00010001) != 0)
					translation = node.translation;
				else
					translation = translation;

				if (parent_node && (node.update_flags & 0x00010000) == 0)
				{
					D3DXVec3TransformCoord(&translation, &translation, &D3DXMATRIX(parent_node->animatedMatrix));
				}
			}

			// rotation
			{
				if ((node.update_flags & 0x00020002) != 0)
					rotation_quaternion = D3DXQUATERNION(node.rotationQuaternion);
				else
					rotation_quaternion = rotation_quaternion;

				if (parent_node && (node.update_flags & 0x00020000) == 0)
				{
					rotation_quaternion *= D3DXQUATERNION(parent_node->animatedRotationQuaternion);
				}
			}

			// scale
			{
				if ((node.update_flags & 0x00040004) != 0)
					scale = D3DXVECTOR3(node.scale);
				else
					scale = D3DXVECTOR3(1, 1, 1);

				if (parent_node && (node.update_flags & 0x00040000) == 0)
				{
					scale.x *= parent_node->animatedScale[0];
					scale.y *= parent_node->animatedScale[1];
					scale.z *= parent_node->animatedScale[2];
				}
			}

			// matrix
			composeMatrixQuat(rotation_quaternion, scale, translation, matrix);

			memcpy(node.animatedScale, static_cast<float*>(scale), 3 * sizeof(float));
			memcpy(node.animatedTranslation, static_cast<float*>(translation), 3 * sizeof(float));
			memcpy(node.animatedRotationQuaternion, static_cast<float*>(rotation_quaternion), 4 * sizeof(float));
			memcpy(node.animatedMatrix, static_cast<float*>(matrix), 16 * sizeof(float));

			node.animationProcessingDone = true;
			node.update_flags |= 0x80000000;

			if (!initialize)
			{
				update_node<initialize, update_parent>(node.child1);
				update_node<initialize, update_parent>(node.sibling);
			}

			return true;
		}

		return false;
	}

	template<class T>
	T lerp(T const& _in1, T const& _in2, const float& _a)
	{
		return _in1 + (_in2 - _in1) * _a;
	}

	D3DXVECTOR4 var_xmm0;
	D3DXVECTOR4 var_xmm1;
	D3DXVECTOR4 var_xmm2;
	D3DXVECTOR4 var_xmm3;
	D3DXVECTOR4 var_xmm4;

	D3DXMATRIX * D3DXMatrixCreate(D3DXMATRIX * pM, D3DXVECTOR4 const* pV1, D3DXVECTOR4 const* pV2, D3DXVECTOR4 const* pV3, D3DXVECTOR4 const* pV4)
	{
		//
		pM->_11 = pV1->x;
		pM->_12 = pV1->y;
		pM->_13 = pV1->z;
		pM->_14 = pV1->w;

		//
		pM->_21 = pV2->x;
		pM->_22 = pV2->y;
		pM->_23 = pV2->z;
		pM->_24 = pV2->w;

		//
		pM->_31 = pV3->x;
		pM->_32 = pV3->y;
		pM->_33 = pV3->z;
		pM->_34 = pV3->w;

		//
		pM->_41 = pV4->x;
		pM->_42 = pV4->y;
		pM->_43 = pV4->z;
		pM->_44 = pV4->w;

		return pM;
	}

	D3DXVECTOR4* D3DXVec4Multiply(D3DXVECTOR4* pOut, D3DXVECTOR4 const* pVec1, D3DXVECTOR4 const* pVec2)
	{
		pOut->x = pVec1->x * pVec2->x;
		pOut->y = pVec1->y * pVec2->y;
		pOut->z = pVec1->z * pVec2->z;
		pOut->w = pVec1->w * pVec2->w;

		return pOut;
	}

	D3DXMATRIX * sub_504330(D3DXMATRIX * pM_ECX, D3DXVECTOR4 const* pV1_ESI, D3DXVECTOR4 const* pV2)
	{
		D3DXVECTOR4 var_60 = D3DXVECTOR4(0, 0, 0, 0);
		D3DXVECTOR4 var_50 = D3DXVECTOR4(0, 0, 0, 0);
		D3DXVECTOR4 var_40 = D3DXVECTOR4(0, 0, 0, 0);
		D3DXVECTOR4 var_30 = D3DXVECTOR4(0, 0, 0, 0);
		D3DXVECTOR4 var_20 = D3DXVECTOR4(0, 0, 0, 0);
		D3DXVECTOR4 var_10 = D3DXVECTOR4(0, 0, 0, 0);

		//
		//     var_xmm0 = D3DXVECTOR4(pV1_ESI->y, 0, 0, 0);
		//     float var_74 = 0.0f;
		//     float var_78 = pV1_ESI->x;
		//     float var_7C = pV1_ESI->z;

		var_60 = D3DXVECTOR4(pV1_ESI->y, pV1_ESI->z, pV1_ESI->x, 0);

		//
		//     var_xmm0 = D3DXVECTOR4(pV1_ESI->z, 0, 0, 0);
		//     float var_74 = 0.0f;
		//     float var_78 = pV1_ESI->y;
		//     float var_7C = pV1_ESI->x;

		var_30 = D3DXVECTOR4(pV1_ESI->z, pV1_ESI->x, pV1_ESI->y, 0);

		//
		var_50.z = 1.0f - pV2->y;
		//     var_xmm0 = D3DXVECTOR4(pV2->x, 0, 0, 0);
		//     float var_74 = pV2->x;
		//     float var_78 = pV2->x;
		//     float var_7C = pV2->x;

		var_10 = D3DXVECTOR4(pV2->x, pV2->x, pV2->x, pV2->x);

		//
		//     var_xmm0 = D3DXVECTOR4(pV2->y, 0, 0, 0);
		//     float var_74 = pV2->y;
		//     float var_78 = pV2->y;
		//     float var_7C = pV2->y;

		var_20 = D3DXVECTOR4(pV2->y, pV2->y, pV2->y, pV2->y);

		//
		//     var_xmm0 = D3DXVECTOR4(var_50.z, 0, 0, 0);
		//     float var_74 = var_50.z;
		//     float var_78 = var_50.z;
		//     float var_7C = var_50.z;

		var_50 = D3DXVECTOR4(var_50.z, var_50.z, var_50.z, var_50.z);

		//
		//     var_xmm0 = D3DXVECTOR4(pV2->x, 0, 0, 0);
		//     float var_74 = pV2->x;
		//     float var_78 = pV2->x;
		//     float var_7C = pV2->x;

		var_40 = D3DXVECTOR4(pV2->x, pV2->x, pV2->x, pV2->x);

		//    var_xmm1 = var_50;
		//    var_xmm2 = var_60;

		D3DXVec4Multiply(&var_xmm0, &var_50, &var_60);

		//    var_xmm2 = *pV1_ESI;

		D3DXVec4Multiply(&var_xmm2, &var_50, pV1_ESI);

		//    var_xmm1 = var_30;

		D3DXVec4Multiply(&var_xmm0, &var_xmm0, &var_30);

		D3DXVec4Multiply(&var_xmm1, pV1_ESI, &var_xmm2);

		D3DXVec4Add(&var_xmm1, &var_xmm1, &var_20);

		//    var_xmm2 = var_40;

		var_50 = var_xmm1;
		var_30 = var_xmm0;

		D3DXVec4Multiply(&var_xmm1, pV1_ESI, &var_40);
		D3DXVec4Add(&var_xmm1, &var_xmm1, &var_xmm0);

		var_40 = var_xmm1;

		D3DXVec4Multiply(&var_xmm0, pV1_ESI, &var_10);

		D3DXVec4Subtract(&var_60, &var_xmm0, &var_30);

		var_60 = -var_60;

		//
		pM_ECX->_11 = var_50.x;
		pM_ECX->_12 = var_40.z;
		pM_ECX->_13 = var_60.y;
		pM_ECX->_14 = 0.0f;

		//
		pM_ECX->_21 = var_60.z;
		pM_ECX->_22 = var_50.y;
		pM_ECX->_23 = var_40.x;
		pM_ECX->_24 = 0.0f;

		//
		pM_ECX->_31 = var_40.y;
		pM_ECX->_32 = var_60.x;
		pM_ECX->_33 = var_50.z;
		pM_ECX->_34 = 0.0f;

		//
		pM_ECX->_41 = 0.0f;
		pM_ECX->_42 = 0.0f;
		pM_ECX->_43 = 0.0f;
		pM_ECX->_44 = 1.0f;

		return pM_ECX;
	}

	bool updateIKData(unsigned long const& ikNumber)
	{
		auto bResult = false;
		if (ikNumber < emaData.m_ikData.size())
		{
			auto const& ikData = emaData.m_ikData.at(ikNumber);

			switch (ikData.method)
			{
			case 0x00:
			{
						 switch (ikData.data[0])
						 {
						 case 0x02:
						 {
									  processIKData0x00_02(ikData);
									  bResult = true;
						 } break;
						 }
			} break;
			case 0x01:
			{
						 processIKData0x01_00(ikData);
						 bResult = true;
			} break;
			}
		}

		return bResult;
	}

	void processIKData0x00_02(EMASkeletonIKData const& ikData)
	{
		auto& skelettonNodes = emaData.m_skelettonNodes;
		auto index0 = *(WORD*)(ikData.data + 0x02);
		auto nodeIt = skelettonNodes.find(index0);
		EMASkelettonNode * nodeP = nullptr;
		EMASkelettonNode * node0 = nullptr;
		if (skelettonNodes.end() != nodeIt)
		{
			node0 = &(nodeIt->second);

			// get parent node
			nodeIt = skelettonNodes.find(node0->parent);
			if (skelettonNodes.end() != nodeIt)
			{
				nodeP = &(nodeIt->second);
			}
		}

		auto index1 = *(WORD*)(ikData.data + 0x04);
		nodeIt = skelettonNodes.find(index1);
		EMASkelettonNode * node1 = nullptr;
		if (skelettonNodes.end() != nodeIt)
		{
			node1 = &(nodeIt->second);
		}

		auto index2 = *(WORD*)(ikData.data + 0x06);
		nodeIt = skelettonNodes.find(index2);
		EMASkelettonNode * node2 = nullptr;
		if (skelettonNodes.end() != nodeIt)
		{
			node2 = &nodeIt->second;
		}

		auto index3 = *(WORD*)(ikData.data + 0x08);
		nodeIt = skelettonNodes.find(index3);
		EMASkelettonNode * node3 = nullptr;
		if (skelettonNodes.end() != nodeIt)
		{
			node3 = &nodeIt->second;
		}

		auto index4 = *(WORD*)(ikData.data + 0x0A);
		nodeIt = skelettonNodes.find(index4);
		EMASkelettonNode * node4 = nullptr;
		if (skelettonNodes.end() != nodeIt)
		{
			node4 = &(nodeIt->second);
		}

		if (!nodeP || !node0 || !node1 || !node2 || !node3 || !node4)
		{
			return;
		}

		node3->update_flags |= 0x10000000;
		node4->update_flags |= 0x20000000;

		// sub_524390
		{
			auto var_F0 = D3DXVECTOR4(0, 0, 0, 0);
			auto var_D0 = D3DXVECTOR4(0, 0, 0, 0);
			auto var_C0 = D3DXVECTOR4(0, 0, 0, 0);
			auto var_B0 = D3DXVECTOR4(0, 0, 0, 0);
			auto var_A0 = D3DXVECTOR4(0, 0, 0, 1);

			auto var_140 = D3DXVECTOR4(0, 0, 0, 0);
			auto var_120 = D3DXVECTOR4(0, 0, 0, 0);
			auto var_100 = D3DXVECTOR4(0, 0, 0, 0);
			auto var_90 = D3DXVECTOR4(0, 0, 0, 0);

			// update bone index unknown0x08
			update_node<true, true>(node1->number);
			// update bone index unknown0x0A
			update_node<true, true>(node2->number);

			var_100 = D3DXVECTOR4(D3DXVECTOR3(node0->animatedTranslation), 1); // position unknown0x06
			var_120 = D3DXVECTOR4(D3DXVECTOR3(node3->animatedTranslation), 1); // position unknown0x0C
			var_140 = D3DXVECTOR4(D3DXVECTOR3(node4->animatedTranslation), 1); // position unknown0x0E

			D3DXVec4Subtract(&var_120, &var_120, &var_100);
			D3DXVec4Subtract(&var_140, &var_140, &var_100);

			D3DXVec3Cross(reinterpret_cast<D3DXVECTOR3*>(&var_F0), reinterpret_cast<D3DXVECTOR3*>(&var_140), reinterpret_cast<D3DXVECTOR3*>(&var_120));
			D3DXVec3Cross(reinterpret_cast<D3DXVECTOR3*>(&var_140), reinterpret_cast<D3DXVECTOR3*>(&var_F0), reinterpret_cast<D3DXVECTOR3*>(&var_120));

			if (ikData.data[1] & 0x01)
			{
				var_F0 = -var_F0;
				var_140 = -var_140;
			}

			D3DXVec4Normalize(&var_D0, &var_120);
			D3DXVec4Normalize(&var_C0, &var_140);
			D3DXVec4Normalize(&var_B0, &var_F0);

			var_A0 = var_100;

			var_xmm4 = D3DXVECTOR4(D3DXVec4Length(&var_120), 0, 0, 0);

			auto scale0x08 = D3DXVECTOR4(D3DXVECTOR3(node1->animatedScale), 1);
			auto scale0x0A = D3DXVECTOR4(D3DXVECTOR3(node2->animatedScale), 1);

			const auto xScale0x08 = scale0x08.x, unkScale0x08 = node1->unknownScale; // 1.0f;
			const auto xScale0x0A = scale0x0A.x, unkScale0x0A = node2->unknownScale; // 1.0f;

			var_xmm1 = D3DXVECTOR4((xScale0x08 * unkScale0x08), 0, 0, 0);
			var_xmm3 = D3DXVECTOR4(var_xmm4.x, var_xmm1.x, 0, 0);
			var_xmm2 = D3DXVECTOR4((xScale0x0A * unkScale0x0A), 0, 0, 0);

			auto var_104 = var_xmm1.x;
			var_xmm1 = D3DXVECTOR4(var_xmm1.x, var_xmm2.x, 0, 0);
			var_xmm2 = D3DXVECTOR4(var_xmm2.x, var_xmm4.x, 0, 0);

			// movaps var_100, xmm1
			var_100 = var_xmm1;

			// movaps xmm4, xmm3
			var_xmm4 = var_xmm3;

			// mulps xmm1, xmm1
			D3DXVec4Multiply(&var_xmm1, &var_xmm1, &var_xmm1);
			// mulps xmm4, xmm3
			D3DXVec4Multiply(&var_xmm4, &var_xmm4, &var_xmm3);
			// movaps var_90, xmm3
			var_90 = var_xmm3;
			// mulps xmm2, xmm2
			D3DXVec4Multiply(&var_xmm2, &var_xmm2, &var_xmm2);
			// addps xmm4, xmm1
			D3DXVec4Add(&var_xmm4, &var_xmm4, &var_xmm1);
			// movss xmm1, 0.5
			var_xmm1 = D3DXVECTOR4(0.5, 0, 0, 0);

			// movss xmm3, var_100.y
			var_xmm3 = D3DXVECTOR4(var_100.y, 0, 0, 0);
			var_xmm3.x *= var_90.y;
			// subps xmm4, xmm2
			D3DXVec4Subtract(&var_xmm4, &var_xmm4, &var_xmm2);
			// movss xmm2, var_100.x
			var_xmm2 = D3DXVECTOR4(var_100.x, 0, 0, 0);
			var_xmm2.x *= var_90.x;
			// shufps xmm1, xmm1, 0
			var_xmm1 = D3DXVECTOR4(0.5, 0.5, 0.5, 0.5);
			// mulps xmm4, xmm1
			D3DXVec4Multiply(&var_xmm4, &var_xmm4, &var_xmm1);
			// movaps var_120, xmm4
			var_120 = var_xmm4;
			// movss xmm1, var_120.x
			var_xmm1 = D3DXVECTOR4(var_120.x, 0, 0, 0);
			// movss xxm4, 1
			var_xmm4 = D3DXVECTOR4(1, 0, 0, 0);
			// divss xmm1, xmm2
			var_xmm1.x /= var_xmm2.x;
			// movss xmm2, var_120.y
			var_xmm2 = D3DXVECTOR4(var_120.y, 0, 0, 0);
			// divss xmm2, xmm3
			var_xmm2.x /= var_xmm3.x;
			// movss xxm3, -1
			var_xmm3 = D3DXVECTOR4(-1, 0, 0, 0);
			// movss var_120.x, xmm1
			var_120.x = var_xmm1.x;
			// movss var_120.y, xmm2
			var_120.y = var_xmm2.x;

			if (var_xmm3.x > var_xmm1.x)
			{
				var_120.x = var_xmm3.x;
			}
			else if (var_xmm4.x < var_xmm1.x)
			{
				var_120.x = var_xmm4.x;
			}

			if (var_xmm3.x > var_xmm2.x)
			{
				var_120.y = var_xmm3.x;
			}
			else if (var_xmm4.x < var_xmm2.x)
			{
				var_120.y = var_xmm4.x;
			}
			// movaps xmm1, var_120
			var_xmm1 = var_120;

			var_xmm0 = D3DXVECTOR4(1, 1, 0, 0); // D3DXVECTOR4(var_xmm4.x, var_xmm4.x);
			// mulps xmm1, xmm1
			D3DXVec4Multiply(&var_xmm1, &var_xmm1, &var_xmm1);
			// subps xmm0, xmm1
			D3DXVec4Subtract(&var_xmm0, &var_xmm0, &var_xmm1);
			//
			var_140 = D3DXVECTOR4(sqrtf(var_xmm0.x), sqrtf(var_xmm0.y), 0, 0);

			var_xmm0 = D3DXVECTOR4(0, 0, 0, 0);

			var_F0 = D3DXVECTOR4(0, 0, -1, 0);

			D3DXMATRIX var_80, var_40;
			// lea esi, var_F0
			// lea ecx, var_80
			sub_504330(&var_80, &var_F0, &D3DXVECTOR4(var_140.x, var_120.x, 0, 0));

			// lea esi, var_F0
			// lea ecx, var_40
			sub_504330(&var_40, &var_F0, &D3DXVECTOR4(-var_140.y, -var_120.y, 0, 0));

			D3DXMATRIX mat_D0;
			D3DXMatrixCreate(&mat_D0, &var_D0, &var_C0, &var_B0, &var_A0);
			D3DXMatrixMultiply(&var_80, &var_80, &mat_D0);

			D3DXMATRIX mat_bone0x08;

			// bone matrix = bone scale matrix * mat_80

			D3DXMatrixScaling(&mat_bone0x08, scale0x08.x, scale0x08.y, scale0x08.z);
			D3DXMatrixMultiply(&mat_bone0x08, &mat_bone0x08, &var_80);

			mat_D0 = var_80;

			var_100 = D3DXVECTOR4(var_104, 0, 0, 1);
			//     
			// mat_D0 position = bone matrix position
			mat_D0._41 = mat_bone0x08._41;
			mat_D0._42 = mat_bone0x08._42;
			mat_D0._43 = mat_bone0x08._43;
			mat_D0._44 = mat_bone0x08._44;

			D3DXVec4Transform(&var_100, &var_100, &mat_D0);
			// mat_D0 position = var_100
			mat_D0._41 = var_100.x;
			mat_D0._42 = var_100.y;
			mat_D0._43 = var_100.z;
			mat_D0._44 = var_100.w;

			D3DXMatrixMultiply(&var_40, &var_40, &mat_D0);

			D3DXMATRIX mat_bone0x0A;

			// bone matrix = bone scale matrix * mat_80

			D3DXMatrixScaling(&mat_bone0x0A, scale0x0A.x, scale0x0A.y, scale0x0A.z);
			D3DXMatrixMultiply(&mat_bone0x0A, &mat_bone0x0A, &var_40);

			var_100 = D3DXVECTOR4(unkScale0x0A, 0, 0, 1);

			D3DXVec4Transform(&var_100, &var_100, &mat_bone0x0A);

			D3DXQUATERNION rotation;

			// update position and quaternion information for bone index 0x08
			D3DXQuaternionRotationMatrix(&rotation, &var_80);

			leftHandToEulerAnglesXYZ(static_cast<float*>(var_80), node1->animatedRotation[0], node1->animatedRotation[1], node1->animatedRotation[2]);

			memcpy(node1->animatedTranslation, static_cast<float*>(mat_bone0x08.m[3]), 3 * sizeof(float));
			memcpy(node1->animatedRotationQuaternion, static_cast<float*>(rotation), 4 * sizeof(float));
			memcpy(node1->animatedMatrix, static_cast<float*>(mat_bone0x08), 16 * sizeof(float));
			// set flags for absolute translation and rotation
			node1->animationProcessingDone = true;
			node1->animatedAbsoluteRotationFlag = true;
			node1->animatedAbsoluteTranslationFlag = true;
			node1->update_flags &= 0xFFFFFFFC;
			node1->update_flags |= 0xC0003000;

			// update position and quaternion information for bone index 0x0A
			D3DXQuaternionRotationMatrix(&rotation, &var_40);

			leftHandToEulerAnglesXYZ(static_cast<float*>(var_40), node2->animatedRotation[0], node2->animatedRotation[1], node2->animatedRotation[2]);

			memcpy(node2->animatedTranslation, static_cast<float*>(mat_bone0x0A.m[3]), 3 * sizeof(float));
			memcpy(node2->animatedRotationQuaternion, static_cast<float*>(rotation), 4 * sizeof(float));
			memcpy(node2->animatedMatrix, static_cast<float*>(mat_bone0x0A), 16 * sizeof(float));
			// set flags for absolute translation and rotation
			node2->animationProcessingDone = true;
			node2->animatedAbsoluteRotationFlag = true;
			node2->animatedAbsoluteTranslationFlag = true;
			node2->update_flags &= 0xFFFFFFFC;
			node2->update_flags |= 0xC0003000;

			// update position for bone index 0x0C
			memcpy(node3->animatedTranslation, static_cast<float*>(var_100), 3 * sizeof(float));
			memcpy(node3->animatedMatrix + 0x0C, static_cast<float*>(var_100), 3 * sizeof(float));
			// set flags for absolute translation
			node3->animatedAbsoluteTranslationFlag = true;
			node3->update_flags &= 0xFFFFFFFE;
			node3->update_flags |= 0x00001000;
			memcpy(node3->translation, node3->animatedTranslation, 3 * sizeof(float));

			// update children of bone index 0x08
			update_node<false, false>(node1->child1);
			// update children of bone index 0x0A
			update_node<false, false>(node2->child1);
		}
	}
	void processIKData0x01_00(EMASkeletonIKData const& ikData)
	{
		// sub_525270
		{
			auto& skelettonNodes = emaData.m_skelettonNodes;
			auto nodeIt = skelettonNodes.find(*(WORD*)(ikData.data + 0x02));
			EMASkelettonNode * nodeP = nullptr;
			EMASkelettonNode * node0 = nullptr;
			if (skelettonNodes.end() != nodeIt)
			{
				node0 = &nodeIt->second;

				// get parent node
				nodeIt = skelettonNodes.find(node0->parent);
				if (skelettonNodes.end() != nodeIt)
				{
					nodeP = &(nodeIt->second);
				}
			}
			nodeIt = skelettonNodes.find(*(WORD*)(ikData.data + 0x04));
			EMASkelettonNode * node1 = nullptr;
			if (skelettonNodes.end() != nodeIt)
			{
				node1 = &nodeIt->second;
			}
			nodeIt = skelettonNodes.find(*(WORD*)(ikData.data + 0x06));
			EMASkelettonNode * node2 = nullptr;
			if (skelettonNodes.end() != nodeIt)
			{
				node2 = &nodeIt->second;
			}

			if (!nodeP || !node0 || !node1 || !node2)
			{
				return;
			}

			// update bone index unknown0x08
			update_node<true, true>(node1->number);
			// update bone index unknown0x0A
			update_node<true, true>(node2->number);
			// update bone index unknown0x06 parent
			update_node<true, true>(nodeP->number);

			D3DXVECTOR3 translation;
			// if flags & 0x01
			if (ikData.data[1] & 0x01)
			{
				// - boneTransform0x06.position = lerp(boneTransform0x08.position, boneTransform0x0A.position, float0x0C);
				translation = lerp(D3DXVECTOR3(node2->animatedTranslation), D3DXVECTOR3(node1->animatedTranslation), *(float*)(ikData.data + 0x0C));
			}
			else
			{
				// - boneTransform0x06.position = boneTransform0x06.position * boneTransform0x06.parentTransform;
				D3DXVec3TransformCoord(&translation, &D3DXVECTOR3(node0->translation), &D3DXMATRIX(nodeP->animatedMatrix));
			}

			D3DXQUATERNION rotation;
			// if flags & 0x02
			if (ikData.data[1] & 0x02)
			{
				// - boneTransform0x06.rotation = slerp(boneTransform0x08.rotation, boneTransform0x0A.rotation, float0x10);
				rotation = lerp(D3DXQUATERNION(node1->animatedRotationQuaternion), D3DXQUATERNION(node2->animatedRotationQuaternion), *(float*)(ikData.data + 0x10));
			}
			else
			{
				// - boneTransform0x06.rotation = boneTransform0x06.roation * boneTransform0x06.parent.rotation
				rotation = D3DXQUATERNION(node0->animatedRotationQuaternion) * D3DXQUATERNION(nodeP->animatedRotationQuaternion);
			}
			D3DXQuaternionNormalize(&rotation, &rotation);

			D3DXVECTOR3 scale;
			// if flags & 0x04
			if (ikData.data[1] & 0x04)
			{
				// - boneTransform0x06.scale = lerp(boneTransform0x08.scale, boneTransform0x0A.scale, float0x14);
				scale = lerp(D3DXVECTOR3(node2->animatedScale), D3DXVECTOR3(node1->animatedScale), *(float*)(ikData.data + 0x14));
			}
			else
			{
				// - boneTransform0x06.scale = boneTransform0x06.parent.scale
				scale = D3DXVECTOR3(nodeP->animatedScale);
			}

			D3DXMATRIX matrix;
			// update translation, rotation, and scale information for bone index 0x06
			composeMatrixQuat(rotation, scale, translation, matrix);

			leftHandToEulerAnglesXYZ(static_cast<float*>(matrix), node0->animatedRotation[0], node0->animatedRotation[1], node0->animatedRotation[2]);

			memcpy(node0->animatedScale, static_cast<float*>(scale), 3 * sizeof(float));
			memcpy(node0->animatedTranslation, static_cast<float*>(translation), 3 * sizeof(float));
			memcpy(node0->animatedRotationQuaternion, static_cast<float*>(rotation), 4 * sizeof(float));
			memcpy(node0->animatedMatrix, static_cast<float*>(matrix), 16 * sizeof(float));

			// set flags for absolute translation, rotation, and scale
			node0->animationProcessingDone = true;
			node0->animatedAbsoluteRotationFlag = true;
			node0->animatedAbsoluteTranslationFlag = true;
			node0->animatedAbsoluteScaleFlag = true;
			node0->update_flags &= 0xFFFFFFF8;
			node0->update_flags |= 0x80007000;
			memcpy(node0->rotation, node0->animatedRotation, 3 * sizeof(float));
			memcpy(node0->scale, node0->animatedScale, 3 * sizeof(float));
			memcpy(node0->translation, node0->animatedTranslation, 3 * sizeof(float));
			memcpy(node0->rotationQuaternion, node0->animatedRotationQuaternion, 4 * sizeof(float));

			// update children of bone index 0x06
			update_node<false, false>(node0->child1);
		}
	}
};