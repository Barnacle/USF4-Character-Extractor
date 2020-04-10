#pragma once

#include "Reader.h"

namespace usf4_ce {
	using namespace System;
	using namespace IO;

	inline void write_skeleton_data(ema_struct^ ema_data, full_ema_skeleton_struct^ ema_skeleton, FileStream^ fs, BinaryWriter^ w);

	inline bool write_ema(ema_struct^ input_ema, full_ema_skeleton_struct^ ema_skeleton, String^ output_file)
	{
		auto ema_data = gcnew ema_struct();

		ema_data->header->animation_count = input_ema->header->animation_count;

		ema_data->animation_offsets = gcnew array<UInt32>(ema_data->header->animation_count);

		ema_data->animation = gcnew array<ema_animation^>(ema_data->header->animation_count);
		for (auto anim = 0; anim < ema_data->animation->Length; anim++)
		{
			ema_data->animation[anim] = gcnew ema_animation;

			////////////////////////
			// TEST REMOVE THIS
			ema_data->animation[anim]->duration = input_ema->animation[anim]->duration;
			ema_data->animation[anim]->cmd_offset_count = input_ema->animation[anim]->cmd_offset_count;
			ema_data->animation[anim]->unknown = input_ema->animation[anim]->unknown;

			ema_data->animation[anim]->values = input_ema->animation[anim]->values;

			ema_data->animation[anim]->name = input_ema->animation[anim]->name;
			////////////////////////
			ema_data->animation[anim]->cmd_offsets = gcnew array<UInt32>(ema_data->animation[anim]->cmd_offset_count);			

			ema_data->animation[anim]->node = gcnew array<ema_animation_node^>(ema_data->animation[anim]->cmd_offset_count);
			for (auto node_index = 0; node_index < ema_data->animation[anim]->node->Length; node_index++)
			{
				ema_data->animation[anim]->node[node_index] = gcnew ema_animation_node;

				//////
				ema_data->animation[anim]->node[node_index]->index = input_ema->animation[anim]->node[node_index]->index;
				ema_data->animation[anim]->node[node_index]->transform_type = input_ema->animation[anim]->node[node_index]->transform_type;
				ema_data->animation[anim]->node[node_index]->transform_flag = input_ema->animation[anim]->node[node_index]->transform_flag;
				ema_data->animation[anim]->node[node_index]->step_count = input_ema->animation[anim]->node[node_index]->step_count;

				ema_data->animation[anim]->node[node_index]->value_indexes = input_ema->animation[anim]->node[node_index]->value_indexes;
				//////


				ema_data->animation[anim]->node[node_index]->frame = gcnew array<UInt16>(ema_data->animation[anim]->node[node_index]->step_count);
				ema_data->animation[anim]->node[node_index]->value = gcnew array<float>(ema_data->animation[anim]->node[node_index]->step_count);
				ema_data->animation[anim]->node[node_index]->tangent_value = gcnew array<float>(ema_data->animation[anim]->node[node_index]->step_count);


				//////
				for(auto b=0; b< ema_data->animation[anim]->node[node_index]->step_count; b++)
				{
					ema_data->animation[anim]->node[node_index]->frame[b] = input_ema->animation[anim]->node[node_index]->frame[b];
					//ema1->anim_infos[ai_index]->node[node_index]->node_value[b] = input_ema->node_value[ai_index][node_index][b];
					//ema1->anim_infos[ai_index]->node[node_index]->node_tangent_value[b] = input_ema->node_tangent_value[ai_index][node_index][b];
				}
				//////
			}
		}



		//==============================================================================
		//==============================================================================

		FileStream^ fs;
		BinaryWriter^ w;

		try
		{
			File::Delete(output_file);
			fs = gcnew FileStream(output_file, FileMode::Create);
			w = gcnew BinaryWriter(fs);
		}
		catch (...)
		{
			return false;
		}

		//==============================================================================

		// Header
		w->Write(ema_data->header->id);
		w->Write(ema_data->header->header_size);
		w->Write(ema_data->header->unknown1);
		w->Write(ema_data->header->skeleton_offset);
		w->Write(ema_data->header->animation_count);
		w->Write(ema_data->header->unknown4);
		w->Write(ema_data->header->unknown5);
		w->Write(ema_data->header->unknown6);
		w->Write(ema_data->header->unknown7);
		w->Write(ema_data->header->unknown8);
		w->Write(ema_data->header->unknown9);
		w->Write(ema_data->header->unknown10);

		//==============================================================================

		// Anim offsets; Zero offsets for now
		for(auto i = 0; i < ema_data->animation_offsets->Length; i++)
		{
			w->Write(ema_data->animation_offsets[i]);
		}

		// Animations
		auto anim_name_offsets_temp = gcnew array<UINT64>(ema_data->animation->Length);
		for (auto anim_info_index = 0; anim_info_index < ema_data->animation->Length; anim_info_index++)
		{
			ema_data->animation_offsets[anim_info_index] = UINT32(fs->Position);
			
			w->Write(ema_data->animation[anim_info_index]->duration);
			w->Write(ema_data->animation[anim_info_index]->cmd_offset_count);
			ema_data->animation[anim_info_index]->value_count = UINT32(fs->Position); // Saving temp current position
			w->Write(ema_data->animation[anim_info_index]->value_count);
			w->Write(ema_data->animation[anim_info_index]->unknown);
			anim_name_offsets_temp[anim_info_index] = fs->Position; // Saving temp current position
			w->Write(ema_data->animation[anim_info_index]->name_offset);
			ema_data->animation[anim_info_index]->values_offset = UINT32(fs->Position); // Saving temp current position
			w->Write(ema_data->animation[anim_info_index]->values_offset);

			for (auto a = 0; a < ema_data->animation[anim_info_index]->cmd_offsets->Length; a++)
			{
				ema_data->animation[anim_info_index]->cmd_offsets[a] = UINT32(fs->Position); // Saving temp current position
				w->Write(ema_data->animation[anim_info_index]->cmd_offsets[a]);
			}

			std::vector<float> values_vector;

			for (auto node_index = 0; node_index < ema_data->animation[anim_info_index]->node->Length; node_index++)
			{
				const auto begin_offset = fs->Position;

				w->Write(ema_data->animation[anim_info_index]->node[node_index]->index);
				w->Write(byte(ema_data->animation[anim_info_index]->node[node_index]->transform_type));
				w->Write(byte(ema_data->animation[anim_info_index]->node[node_index]->transform_flag));
				w->Write(ema_data->animation[anim_info_index]->node[node_index]->step_count);
				const UINT32 indices_offset_temp = UINT32(fs->Position); // Saving temp current position. Don't remove this temp value!
				w->Write(ema_data->animation[anim_info_index]->node[node_index]->indices_offset);

				for(auto frame_index = 0; frame_index < ema_data->animation[anim_info_index]->node[node_index]->step_count; frame_index++)
				{
					if(ema_data->animation[anim_info_index]->node[node_index]->transform_flag & 0x20)
						w->Write(ema_data->animation[anim_info_index]->node[node_index]->frame[frame_index]);
					else
						w->Write(byte(ema_data->animation[anim_info_index]->node[node_index]->frame[frame_index]));
				}

				// Calculating real offset
				const auto indices_offset = fs->Position - begin_offset;
				const auto cmd_offset = fs->Position - ema_data->animation_offsets[anim_info_index] - indices_offset;

				for (auto index = 0; index < ema_data->animation[anim_info_index]->node[node_index]->step_count; index++)
				{
					if (ema_data->animation[anim_info_index]->node[node_index]->transform_flag & 0x40)
					{
						UINT32 value = 0;
						UINT value_index = 0;

						auto node_value = ema_data->animation[anim_info_index]->node[node_index]->value[index];
						auto node_tangent_value = ema_data->animation[anim_info_index]->node[node_index]->tangent_value[index];

						values_vector.push_back(node_value);
						value_index = values_vector.size() - 1; // std::find(values_vector.begin(), values_vector.end(), node_value) - values_vector.begin();

						value = value_index;
						if (node_tangent_value != 0)
						{
							values_vector.push_back(node_tangent_value);
							value += 0x40000000;
						}

						//w->Write(UINT32(value));
						w->Write(UINT32(ema_data->animation[anim_info_index]->node[node_index]->value_indexes[index]));
					}
					else
					{
						UINT32 value = 0;
						UINT value_index = 0;

						auto node_value = ema_data->animation[anim_info_index]->node[node_index]->value[index];
						auto node_tangent_value = ema_data->animation[anim_info_index]->node[node_index]->tangent_value[index];

						values_vector.push_back(node_value);
						value_index = values_vector.size() - 1; // std::find(values_vector.begin(), values_vector.end(), node_value) - values_vector.begin();

						value = value_index;
						if (node_tangent_value != 0)
						{
							values_vector.push_back(node_tangent_value);
							value += 0x4000;
						}

						w->Write(UINT16(ema_data->animation[anim_info_index]->node[node_index]->value_indexes[index]));
						//w->Write(UINT16(value));
					}
				}

				// Replacing with a real index
				fs->Position = indices_offset_temp;
				ema_data->animation[anim_info_index]->node[node_index]->indices_offset = UINT16(indices_offset);
				w->Write(ema_data->animation[anim_info_index]->node[node_index]->indices_offset);
				fs->Position = fs->Length;

				// Replacing with a real index
				fs->Position = ema_data->animation[anim_info_index]->cmd_offsets[node_index];
				ema_data->animation[anim_info_index]->cmd_offsets[node_index] = UINT32(cmd_offset);
				w->Write(ema_data->animation[anim_info_index]->cmd_offsets[node_index]);
				fs->Position = fs->Length;
			}

			/*ema1->anim_infos[anim_info_index]->values = gcnew array<float>(values_vector.size());
			for (auto i = 0; i < ema1->anim_infos[anim_info_index]->values->Length; i++)
			{
				ema1->anim_infos[anim_info_index]->values[i] = values_vector[i];
			}*/

			fs->Position = ema_data->animation[anim_info_index]->value_count;
			ema_data->animation[anim_info_index]->value_count = ema_data->animation[anim_info_index]->values->Length;
			w->Write(ema_data->animation[anim_info_index]->value_count);
			fs->Position = fs->Length;

			const auto values_offset = UINT32(fs->Position);
			fs->Position = ema_data->animation[anim_info_index]->values_offset;
			ema_data->animation[anim_info_index]->values_offset = values_offset - ema_data->animation_offsets[anim_info_index];
			w->Write(ema_data->animation[anim_info_index]->values_offset);
			fs->Position = values_offset;

			for (auto i = 0; i < ema_data->animation[anim_info_index]->values->Length; i++)
			{
				w->Write(float(ema_data->animation[anim_info_index]->values[i]));
			}
		}

		// Anim offsets; real offsets
		fs->Position = ema_data->header->header_size;
		for (auto i = 0; i < ema_data->animation_offsets->Length; i++)
		{
			w->Write(ema_data->animation_offsets[i]);
		}
		fs->Position = fs->Length;

		//==============================================================================

		write_skeleton_data(ema_data, ema_skeleton, fs, w);

		//==============================================================================

		// Anim names
		const auto empty_buffer = gcnew array<Byte>(10);
		w->Write(empty_buffer);
		for (auto i = 0; i < ema_data->animation->Length; i++)
		{
			const auto name_offset = fs->Position - 10 - ema_data->animation_offsets[i];

			auto buffer = gcnew array<Byte>(ema_data->animation[i]->name->Length + 2);
			for(auto a = 0; a <= ema_data->animation[i]->name->Length; a++)
			{
				if (a == 0)
					buffer[a] = byte(ema_data->animation[i]->name->Length);
				else
					buffer[a] = byte(ema_data->animation[i]->name[a-1]);
			}
			w->Write(buffer);

			// Updating name offsets
			fs->Position = anim_name_offsets_temp[i];
			w->Write(UINT32(name_offset));
			fs->Position = fs->Length;
		}

		// update ema header
		fs->Position = 0;
		w->Write(ema_data->header->id);
		w->Write(ema_data->header->header_size);
		w->Write(ema_data->header->unknown1);
		w->Write(ema_data->header->skeleton_offset);
		fs->Position = fs->Length;

		w->Close();
		fs->Close();

		delete ema_data;

		return true;
	}

	inline void write_skeleton_data(ema_struct^ ema_data, full_ema_skeleton_struct^ ema_skeleton, FileStream^ fs, BinaryWriter^ w)
	{
		if(ema_skeleton == nullptr)
			return;

		// Anim skeleton, temp header
		ema_data->header->skeleton_offset = UINT32(fs->Position);
		w->Write(ema_skeleton->header.nodeCount);
		w->Write(ema_skeleton->header.someNodeCount);
		w->Write(ema_skeleton->header.ikDataCount);
		w->Write(ema_skeleton->header.unknown0x06);
		w->Write(ema_skeleton->header.skeletonStartOffset);
		w->Write(ema_skeleton->header.skeletonNameAddressOffset);
		w->Write(ema_skeleton->header.someDataOffset);
		w->Write(ema_skeleton->header.someNodeAddressOffset);
		w->Write(ema_skeleton->header.unknownDataOffset);
		w->Write(ema_skeleton->header.matrixOffset);
		w->Write(ema_skeleton->header.ikDataOffset);
		w->Write(ema_skeleton->header.unknown1);
		w->Write(ema_skeleton->header.unknown2);
		w->Write(ema_skeleton->header.unknown3);
		w->Write(ema_skeleton->header.unknown4);
		w->Write(ema_skeleton->header.unknown5);
		w->Write(ema_skeleton->header.unknown6);
		w->Write(ema_skeleton->header.unknown7);

		//==============================================================================

		for (unsigned int i = 0; i < ema_skeleton->header.nodeCount; i++)
		{
			w->Write(ema_skeleton->nodes[i]->parent);
			w->Write(ema_skeleton->nodes[i]->child1);
			w->Write(ema_skeleton->nodes[i]->child2);
			w->Write(ema_skeleton->nodes[i]->child3);
			w->Write(ema_skeleton->nodes[i]->child4);
			w->Write(ema_skeleton->nodes[i]->flags);
			w->Write(ema_skeleton->nodes[i]->unknown4);

			for (auto a = 0; a < ema_skeleton->nodes[i]->matrix->Length; a++)
			{
				w->Write(ema_skeleton->nodes[i]->matrix[a]);
			}
		}

		//==============================================================================

		// Unknown Data
		ema_skeleton->header.unknownDataOffset = UINT32(fs->Position) - ema_data->header->skeleton_offset;
		w->Write(ema_skeleton->unknown_data);

		//==============================================================================

		// Zero offsets for now
		ema_skeleton->header.skeletonNameAddressOffset = UINT32(fs->Position) - ema_data->header->skeleton_offset;
		for (unsigned int i = 0; i < ema_skeleton->header.nodeCount; i++)
		{
			w->Write(UINT32(0));
		}

		for (auto i = 0; i < ema_skeleton->header.nodeCount; i++)
		{
			ema_skeleton->names_offsets[i] = UINT32(fs->Position) - ema_data->header->skeleton_offset;

			auto buffer = gcnew array<byte>(ema_skeleton->names[i]->Length + 1);
			for (auto a = 0; a < ema_skeleton->names[i]->Length; a++)
			{
				buffer[a] = byte(ema_skeleton->names[i][a]);
			}

			w->Write(buffer);
		}

		// Real offsets
		fs->Position = ema_data->header->skeleton_offset + ema_skeleton->header.skeletonNameAddressOffset;
		for (unsigned int i = 0; i < ema_skeleton->header.nodeCount; i++)
		{
			w->Write(ema_skeleton->names_offsets[i]);
		}
		fs->Position = fs->Length;

		//==============================================================================

		ema_skeleton->header.ikDataOffset = UINT32(fs->Position) - ema_data->header->skeleton_offset;
		for (auto i = 0; i < ema_skeleton->header.ikDataCount; i++)
		{
			w->Write(UINT16(ema_skeleton->ik_data[i]->method));
			w->Write(UINT16(ema_skeleton->ik_data[i]->data_size));

			for (auto a = 0; a < ema_skeleton->ik_data[i]->data->Length; a++)
			{
				w->Write(ema_skeleton->ik_data[i]->data[a]);
			}
		}

		// Some Data
		ema_skeleton->header.someDataOffset = UINT32(fs->Position) - ema_data->header->skeleton_offset;
		w->Write(ema_skeleton->some_data);

		// Zero offsets for now
		ema_skeleton->header.someNodeAddressOffset = UINT32(fs->Position) - ema_data->header->skeleton_offset;
		for (unsigned int i = 0; i < ema_skeleton->header.someNodeCount; i++)
		{
			w->Write(UINT32(0));
		}

		for (auto i = 0; i < ema_skeleton->header.someNodeCount; i++)
		{
			ema_skeleton->someNode_offsets[i] = UINT32(fs->Position) - ema_data->header->skeleton_offset;

			auto buffer = gcnew array<byte>(ema_skeleton->someNode_names[i]->Length + 1);
			for (auto a = 0; a < ema_skeleton->someNode_names[i]->Length; a++)
			{
				buffer[a] = byte(ema_skeleton->someNode_names[i][a]);
			}

			w->Write(buffer);
		}

		// Real offsets
		fs->Position = ema_data->header->skeleton_offset + ema_skeleton->header.someNodeAddressOffset;
		for (unsigned int i = 0; i < ema_skeleton->header.someNodeCount; i++)
		{
			w->Write(ema_skeleton->someNode_offsets[i]);
		}
		fs->Position = fs->Length;

		//==============================================================================

		// update skeleton header
		fs->Position = ema_data->header->skeleton_offset;
		w->Write(ema_skeleton->header.nodeCount);
		w->Write(ema_skeleton->header.someNodeCount);
		w->Write(ema_skeleton->header.ikDataCount);
		w->Write(ema_skeleton->header.unknown0x06);
		w->Write(ema_skeleton->header.skeletonStartOffset);
		w->Write(ema_skeleton->header.skeletonNameAddressOffset);
		w->Write(ema_skeleton->header.someDataOffset);
		w->Write(ema_skeleton->header.someNodeAddressOffset);
		w->Write(ema_skeleton->header.unknownDataOffset);
		w->Write(ema_skeleton->header.matrixOffset);
		w->Write(ema_skeleton->header.ikDataOffset);
		fs->Position = fs->Length;
	}
}
