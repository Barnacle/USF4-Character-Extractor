#pragma once

#include "Reader.h"

namespace usf4_ce {
	using namespace System;
	using namespace IO;
	using namespace Globalization;

	inline void write_smd(String^ emo_path, String^ name, String^ output_file, wrapper^ m_D3DWrap, TreeView^ treeView1, String^ model_scale, bool replace_skeleton, bool starpose_fix, bool merge)
	{
		auto fs = File::OpenRead(emo_path);
		auto br = gcnew BinaryReader(fs);
		auto sw = gcnew StreamWriter(output_file);

		auto path = Path::GetDirectoryName(emo_path);
		auto scale = UINT16::Parse(model_scale);

		sw->WriteLine("version 1");

		//==================================================================
		// Nodes tree.
		//==================================================================

		auto skeleton_data = read_skeleton(emo_path, 16);

		sw->WriteLine("nodes");

		for (UINT16 i = 0; i < skeleton_data->nodes_count; i++) // 
		{
			auto node_name = skeleton_data->node_name[i];
			sw->WriteLine(i + " " + "\"" + node_name + "\"" + " " + skeleton_data->parent_node_array[i]); //" \"root\"  child+1
		}

		sw->WriteLine("end");

		//==================================================================
		// Position of nodes.
		//==================================================================
		sw->WriteLine("skeleton");
		sw->WriteLine("time 0");

		float structure[500][6];
		std::string names[500];
		if (replace_skeleton == true) // If animation is not selected, exporting original skeleton.
		{
			array<Char>^ trim_chars2 = { '_', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
			auto name2 = name->TrimEnd(trim_chars2);

			auto anim_name = gcnew String(path + "\\" + name2 + ".obj.ema");
			m_D3DWrap->setup_ema(anim_name, 0);
			m_D3DWrap->update_ema(structure, names, "NONE", 0);
		}

		using Runtime::InteropServices::GCHandle;
		using Runtime::InteropServices::GCHandleType;

		auto pins = gcnew array<GCHandle>(skeleton_data->matrix_4x4->Length);
		for (auto a = 0, i_max = pins->Length; a != i_max; ++a)
			pins[a] = GCHandle::Alloc(skeleton_data->matrix_4x4[a], GCHandleType::Pinned);

		auto arrays = gcnew array<byte*>(pins->Length);
		for (auto a = 0, i_max = arrays->Length; a != i_max; ++a)
			arrays[a] = static_cast<byte*>(pins[a].AddrOfPinnedObject().ToPointer());

		// pin outer array<int*>^
		pin_ptr<byte*> pin = &arrays[0];

		for (UINT16 i = 0; i < skeleton_data->nodes_count; i++) // 
		{
			auto en_us = gcnew CultureInfo("en-US");

			auto tx = *reinterpret_cast<float*>(pin[i] + 48); // 12
			auto ty = *reinterpret_cast<float*>(pin[i] + 56); // 14
			auto tz = -*reinterpret_cast<float*>(pin[i] + 52); // 13

			auto rx = atan2(-*reinterpret_cast<float*>(pin[i] + 36), *reinterpret_cast<float*>(pin[i] + 20)); // 9, 5
			auto ry = -atan2(-*reinterpret_cast<float*>(pin[i] + 8), *reinterpret_cast<float*>(pin[i])); // 2, 0						 
			auto rz = asin(*reinterpret_cast<float*>(pin[i] + 4)); // 1

			if (replace_skeleton == true) // If not checked, exporting original skeleton.
			{
				auto node_name = skeleton_data->node_name[i]; // Name of current node.	

				array<Char>^ trim_chars2 = { '_', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
				auto name2 = name->TrimEnd(trim_chars2);
				auto skeleton_data2 = read_skeleton(path + "\\" + name2 + ".obj.ema", 12);

				for (UINT16 nodes = 0; nodes < skeleton_data2->nodes_count; nodes++) // Replacing values of current node with values of reference skeleton from animation.
				{
					auto name_temp(names[nodes]);
					auto name_clr = gcnew String(name_temp.c_str());

					if (name_clr == node_name)
					{
						tx = structure[nodes][0];
						ty = structure[nodes][1];
						tz = structure[nodes][2];
						rx = structure[nodes][3];
						rz = structure[nodes][4];

						if (starpose_fix)
						{
							if (name_clr == "RLegRoot" || name_clr == "RLegDir")
								ry = -float(0.610842);
							else if (name_clr == "LLegRoot" || name_clr == "LLegDir")
								ry = float(0.610842);
							else
								ry = structure[nodes][5];
						}
						else
							ry = structure[nodes][5];
					}
				}
			}
			else
			{
				if (i == 0) // Need to rotate.
					rx = float(1.570796);
			}

			sw->WriteLine(i + " "
				+ (-tx * scale).ToString("F6", en_us) + " "
				+ (ty * scale).ToString("F6", en_us) + " "
				+ (tz * scale).ToString("F6", en_us) + " "

				+ rx.ToString("F6", en_us) + " "
				+ (-rz).ToString("F6", en_us) + " "
				+ (-ry).ToString("F6", en_us));
		}
		delete skeleton_data;
		sw->WriteLine("end");

		//==================================================================
		// Triangles
		//==================================================================
		fs->Position = 32; // Skipping 32 bytes to position about EMG ammount.
		UINT16 emg_count = br->ReadInt16();
		fs->Position = 32 + 8; // Position of "offsets list" of every EMG.

		auto emg_offsets = gcnew array<int>(emg_count);
		auto emg_data = gcnew array<emg_struct^>(emg_count);

		sw->WriteLine("triangles");

		for (auto current_emg = 0; current_emg < emg_count; current_emg++)
		{
			emg_offsets[current_emg] = br->ReadInt32(); // Filling array with list.
			emg_data[current_emg] = read_emg(emo_path, 32 + emg_offsets[current_emg] + 16); // Filling array with data about each EMG.

			if (treeView1->Nodes[0]->Nodes[current_emg]->Checked)
			{
				for (auto current_submodel = 0; current_submodel < emg_data[current_emg]->header->submodel_count; current_submodel++)
				{
					UINT32 faces;
					if (emg_data[current_emg]->header->trianlge_strip)
						faces = emg_data[current_emg]->index_count[current_submodel] - 2;
					else
						faces = emg_data[current_emg]->index_count[current_submodel] / 3;

					for (UINT16 i = 0; i < faces; i++)
					{
						auto en_us = gcnew CultureInfo("en-US");

						int a, b, c;

						String^ texture = {};
						if (merge)
							texture = name + "_" + (emg_data[current_emg]->dds_id[current_submodel] + 1) + ".dds";
						else
							texture = current_emg + "_" + name + "_" + (emg_data[current_emg]->dds_id[current_submodel] + 1) + ".dds";


						if (emg_data[current_emg]->header->trianlge_strip)
						{
							if (i % 2 == 0)
							{
								a = emg_data[current_emg]->indices_array[current_submodel][i + 0];
								b = emg_data[current_emg]->indices_array[current_submodel][i + 1];
								c = emg_data[current_emg]->indices_array[current_submodel][i + 2];

								if (a != b && b != c) // skipping degenerate triangle
								{
									sw->WriteLine(texture);

									for (char x = 2; x > -1; x--)
									{
										int index = emg_data[current_emg]->indices_array[current_submodel][i + x];
										pin_ptr<byte> pVertexArray = &emg_data[current_emg]->vertex_array[0];

										sw->Write("0 "
											// PosX PosY PosZ
											+ (-*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray))* scale).ToString("F6", en_us) + " "
											+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 4)* scale).ToString("F6", en_us) + " "
											+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 8)* scale).ToString("F6", en_us) + " "
											// NormX NormY NormZ
											+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 12)).ToString("F6", en_us) + " "
											+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 16)).ToString("F6", en_us) + " "
											+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 20)).ToString("F6", en_us) + " "
											// U V
											+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 24)).ToString("F6", en_us) + " "
											+ (-*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 28)).ToString("F6", en_us) + " ");

										byte BoneID[4];
										for (byte num = 0; num < 4; num++)
											BoneID[num] = *reinterpret_cast<byte*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 48 + num);
										float weight[3];
										for (byte num = 0; num < 3; num++)
											weight[num] = *reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 52 + (num * 4));

										if (weight[0] != 0 && weight[1] == 0) // if 1
											sw->WriteLine("1 " + emg_data[current_emg]->nodes_array[current_submodel][BoneID[0]].ToString() + " 1");
										else if (weight[0] != 0 && weight[1] != 0 && weight[2] == 0) // if 2
											sw->WriteLine("2 " + emg_data[current_emg]->nodes_array[current_submodel][BoneID[0]].ToString() + " "
												+ weight[0].ToString("F6", en_us) + " "
												+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[1]].ToString() + " "
												+ weight[1].ToString("F6", en_us));
										else if (weight[0] + weight[1] + weight[2] > 0.999) // if 3
											sw->WriteLine("3 " + emg_data[current_emg]->nodes_array[current_submodel][BoneID[0]].ToString() + " "
												+ weight[0].ToString("F6", en_us) + " "
												+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[1]].ToString() + " "
												+ weight[1].ToString("F6", en_us) + " "
												+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[2]].ToString() + " "
												+ weight[2].ToString("F6", en_us));
										else // if 4
											sw->WriteLine("4 " + emg_data[current_emg]->nodes_array[current_submodel][BoneID[0]].ToString() + " "
												+ weight[0].ToString("F6", en_us) + " "
												+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[1]].ToString() + " "
												+ weight[1].ToString("F6", en_us) + " "
												+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[2]].ToString() + " "
												+ weight[2].ToString("F6", en_us) + " "
												+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[3]].ToString() + " "
												+ (1 - (weight[0] + weight[1] + weight[2])).ToString("F6", en_us));
									}
								}
							}
							else
							{
								a = emg_data[current_emg]->indices_array[current_submodel][i + 2];
								b = emg_data[current_emg]->indices_array[current_submodel][i + 1];
								c = emg_data[current_emg]->indices_array[current_submodel][i + 0];

								if (a != b && b != c)
								{
									sw->WriteLine(texture);

									for (char x = 0; x < 3; x++)
									{
										int index = emg_data[current_emg]->indices_array[current_submodel][i + x];
										pin_ptr<byte> pVertexArray = &emg_data[current_emg]->vertex_array[0];

										sw->Write("0 "
											// PosX PosY PosZ
											+ (-*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray))* scale).ToString("F6", en_us) + " "
											+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 4)* scale).ToString("F6", en_us) + " "
											+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 8)* scale).ToString("F6", en_us) + " "
											// NormX NormY NormZ
											+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 12)).ToString("F6", en_us) + " "
											+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 16)).ToString("F6", en_us) + " "
											+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 20)).ToString("F6", en_us) + " "
											// U V
											+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 24)).ToString("F6", en_us) + " "
											+ (-*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 28)).ToString("F6", en_us) + " ");

										byte BoneID[4];
										for (byte num = 0; num < 4; num++)
											BoneID[num] = *reinterpret_cast<byte*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 48 + num);
										float weight[3];
										for (byte num = 0; num < 3; num++)
											weight[num] = *reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 52 + (num * 4));

										if (weight[0] != 0 && weight[1] == 0)
											sw->WriteLine("1 " + emg_data[current_emg]->nodes_array[current_submodel][BoneID[0]].ToString() + " 1");
										else if (weight[0] != 0 && weight[1] != 0 && weight[2] == 0)
											sw->WriteLine("2 " + emg_data[current_emg]->nodes_array[current_submodel][BoneID[0]].ToString() + " "
												+ weight[0].ToString("F6", en_us) + " "
												+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[1]].ToString() + " "
												+ weight[1].ToString("F6", en_us));
										else if (weight[0] + weight[1] + weight[2] > 0.999)
											sw->WriteLine("3 " + emg_data[current_emg]->nodes_array[current_submodel][BoneID[0]].ToString() + " "
												+ weight[0].ToString("F6", en_us) + " "
												+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[1]].ToString() + " "
												+ weight[1].ToString("F6", en_us) + " "
												+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[2]].ToString() + " "
												+ weight[2].ToString("F6", en_us));
										else
											sw->WriteLine("4 " + emg_data[current_emg]->nodes_array[current_submodel][BoneID[0]].ToString() + " "
												+ weight[0].ToString("F6", en_us) + " "
												+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[1]].ToString() + " "
												+ weight[1].ToString("F6", en_us) + " "
												+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[2]].ToString() + " "
												+ weight[2].ToString("F6", en_us) + " "
												+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[3]].ToString() + " "
												+ (1 - (weight[0] + weight[1] + weight[2])).ToString("F6", en_us));
									}
								}
							}
						}
						else
						{
							sw->WriteLine(texture);

							a = emg_data[current_emg]->indices_array[current_submodel][i * 3 + 0];
							b = emg_data[current_emg]->indices_array[current_submodel][i * 3 + 1];
							c = emg_data[current_emg]->indices_array[current_submodel][i * 3 + 2];

							if (a != b && b != c) // skipping degenerate triangle
							{
								for (char x = 2; x > -1; x--)
								{
									int index = emg_data[current_emg]->indices_array[current_submodel][i * 3 + x];
									pin_ptr<byte> pVertexArray = &emg_data[current_emg]->vertex_array[0];

									sw->Write("0 "
										// PosX PosY PosZ
										+ (-*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray))* scale).ToString("F6", en_us) + " "
										+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 4)* scale).ToString("F6", en_us) + " "
										+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 8)* scale).ToString("F6", en_us) + " "
										// NormX NormY NormZ
										+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 12)).ToString("F6", en_us) + " "
										+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 16)).ToString("F6", en_us) + " "
										+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 20)).ToString("F6", en_us) + " "
										// U V
										+ (*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 24)).ToString("F6", en_us) + " "
										+ (-*reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 28)).ToString("F6", en_us) + " ");

									byte BoneID[4];
									for (byte num = 0; num < 4; num++)
										BoneID[num] = *reinterpret_cast<byte*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 48 + num);
									float weight[3];
									for (byte num = 0; num < 3; num++)
										weight[num] = *reinterpret_cast<float*>(index * emg_data[current_emg]->header->vertex_size + int(pVertexArray) + 52 + (num * 4));

									if (weight[0] != 0 && weight[1] == 0)
										sw->WriteLine("1 " + emg_data[current_emg]->nodes_array[current_submodel][BoneID[0]].ToString() + " 1");
									else if (weight[0] != 0 && weight[1] != 0 && weight[2] == 0)
										sw->WriteLine("2 " + emg_data[current_emg]->nodes_array[current_submodel][BoneID[0]].ToString() + " "
											+ weight[0].ToString("F6", en_us) + " "
											+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[1]].ToString() + " "
											+ weight[1].ToString("F6", en_us));
									else if (weight[0] + weight[1] + weight[2] > 0.999)
										sw->WriteLine("3 " + emg_data[current_emg]->nodes_array[current_submodel][BoneID[0]].ToString() + " "
											+ weight[0].ToString("F6", en_us) + " "
											+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[1]].ToString() + " "
											+ weight[1].ToString("F6", en_us) + " "
											+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[2]].ToString() + " "
											+ weight[2].ToString("F6", en_us));
									else
										sw->WriteLine("4 " + emg_data[current_emg]->nodes_array[current_submodel][BoneID[0]].ToString() + " "
											+ weight[0].ToString("F6", en_us) + " "
											+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[1]].ToString() + " "
											+ weight[1].ToString("F6", en_us) + " "
											+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[2]].ToString() + " "
											+ weight[2].ToString("F6", en_us) + " "
											+ emg_data[current_emg]->nodes_array[current_submodel][BoneID[3]].ToString() + " "
											+ (1 - (weight[0] + weight[1] + weight[2])).ToString("F6", en_us));
								}
							}
						}
					}
				}
			}

			delete emg_data[current_emg];
		}

		sw->Write("end");

		sw->Close();
		br->Close();
		fs->Close();
	}

	inline void write_anim(String^ emo_path, String^ ema_name, String^ in_output_path, String^ output_smd_file, int index, wrapper^ m_D3DWrap, ema_animation^ raw_anim, String^ model_scale, bool b_ref_frame)
	{
		const auto en_us = gcnew CultureInfo("en-US");
		const auto scale = ushort::Parse(model_scale);
		auto path = Path::GetDirectoryName(emo_path);
		const auto anim_name = gcnew String(path + "\\" + ema_name);
		const auto output_path = Path::GetDirectoryName(in_output_path);
		Directory::CreateDirectory(output_path + "\\" + ema_name);

		m_D3DWrap->setup_ema(anim_name, 0);		

		auto sw = gcnew StreamWriter(output_path + "\\" + ema_name + "\\" + output_smd_file + ".smd");

		sw->WriteLine("version 1");

		//==================================================================
		// Nodes tree.
		//==================================================================					 

		auto skeleton_data = read_skeleton(path + "\\" + ema_name, 12);

		sw->WriteLine("nodes");

		for (auto i = 0; i < skeleton_data->nodes_count; i++) // 
		{
			if (raw_anim != nullptr)
			{
				// Looking for nodes in current anim. If skel. node is not existing in anim, then skip it.
				auto exist = false;
				for (auto a = 0; a < raw_anim->node->Length; a++)
				{
					if (raw_anim->node[a]->name == skeleton_data->node_name[i])
						exist = true;
				}
				if (!exist && i != 0)
					continue;
			}

			sw->WriteLine(i + " " + "\"" + skeleton_data->node_name[i] + "\"" + " " + skeleton_data->parent_node_array[i]); //" \"root\"  child+1
		}

		sw->WriteLine("end");

		//==================================================================
		// Nodes position.
		//==================================================================

		String^ RLegRootRef = {};
		String^ LLegRootRef = {};
		String^ LArmRootRef = {};
		String^ RArmRootRef = {};

		sw->WriteLine("skeleton");

		auto ema_data = read_ema(path + "\\" + ema_name);

		const auto animation_name = gcnew String(ema_data->animation[index]->name);

		float structure[500][6];
		std::string names[500];


		// Should be here.
		m_D3DWrap->update_ema(structure, names, "ref", 0); 
		for (auto i = 0; i < skeleton_data->nodes_count; i++)
		{
			auto temp = i + " " + (-structure[i][0] * scale).ToString("F6", en_us) + " " + (structure[i][1] * scale).ToString("F6", en_us) + " " + (structure[i][2] * scale).ToString("F6", en_us) + " ";
			temp += structure[i][3].ToString("F6", en_us) + " " + (-structure[i][4]).ToString("F6", en_us) + " " + (-structure[i][5]).ToString("F6", en_us);

			const auto name_clr = gcnew String(names[i].c_str());
			if (name_clr == "RLegRoot")
				RLegRootRef = temp;
			else if (name_clr == "LLegRoot")
				LLegRootRef = temp;
			else if (name_clr == "LArmRoot")
				LArmRootRef = temp;
			else if (name_clr == "RArmRoot")
				RArmRootRef = temp;
		}

		// Reference frame.
		if (b_ref_frame)
		{
			sw->WriteLine("time 0");

			for (auto i = 0; i < skeleton_data->nodes_count; i++)
			{
				const auto name_clr = gcnew String(names[i].c_str());

				if (raw_anim != nullptr)
				{
					// Looking for nodes in current anim. If skel. node is not existing in anim, then skip it.
					auto exist = false;
					for (auto a = 0; a < raw_anim->node->Length; a++)
					{
						if (raw_anim->node[a]->name == name_clr)
							exist = true;
					}
					if (!exist && i != 0)
						continue;
				}

				if (i == 0)
					sw->WriteLine("0 0 0 0 0 0 0"); //1.570796 3.141592
				else
				{
					sw->Write(i + " " + (-structure[i][0] * scale).ToString("F6", en_us) + " " + (structure[i][1] * scale).ToString("F6", en_us) + " " + (structure[i][2] * scale).ToString("F6", en_us) + " ");
					sw->WriteLine(structure[i][3].ToString("F6", en_us) + " " + (-structure[i][4]).ToString("F6", en_us) + " " + (-structure[i][5]).ToString("F6", en_us));
				}
			}
		}

		// Actual animation.
		for (auto time = 0; time < ema_data->animation[index]->duration; time++)
		{
			m_D3DWrap->update_ema(structure, names, animation_name, time);

			sw->WriteLine("time " + (time + Convert::ToInt16(b_ref_frame)));

			for (auto i = 0; i < skeleton_data->nodes_count; i++)
			{
				const auto name_clr = gcnew String(names[i].c_str());

				if (raw_anim != nullptr)
				{
					// Looking for nodes in current anim. If skel. node is not existing in anim, then skip it.
					auto exist = false;
					for (auto a = 0; a < raw_anim->node->Length; a++)
					{
						if (raw_anim->node[a]->name == name_clr)
							exist = true;
					}
					if (!exist && i != 0)
						continue;
				}

				if (!name_clr->Equals("camera") && i == 0 && time == 0)
					sw->WriteLine("0 0 0 0 0 0 0"); //1.570796 3.141592
				else if (name_clr->Equals("camera") || i != 0)
				{
					if (raw_anim != nullptr)
					{
						sw->Write(i + " " + (-structure[i][0] * scale).ToString("F6", en_us) + " " + (structure[i][1] * scale).ToString("F6", en_us) + " " + (structure[i][2] * scale).ToString("F6", en_us) + " ");
						sw->WriteLine(structure[i][3].ToString("F6", en_us) + " " + (-structure[i][4]).ToString("F6", en_us) + " " + (-structure[i][5]).ToString("F6", en_us));
					}
					else
					{
						if (time != 0 && (name_clr == "RLegRoot" || name_clr == "LLegRoot" || name_clr == "LArmRoot" || name_clr == "RArmRoot"))
						{ /*Empty*/ }
						else
						{
							if (name_clr == "RLegRoot" && !b_ref_frame)
								sw->WriteLine(RLegRootRef);
							else if (name_clr == "LLegRoot" && !b_ref_frame)
								sw->WriteLine(LLegRootRef);
							else if (name_clr == "LArmRoot" && !b_ref_frame)
								sw->WriteLine(LArmRootRef);
							else if (name_clr == "RArmRoot" && !b_ref_frame)
								sw->WriteLine(RArmRootRef);
							else
							{
								sw->Write(i + " " + (-structure[i][0] * scale).ToString("F6", en_us) + " " + (structure[i][1] * scale).ToString("F6", en_us) + " " + (structure[i][2] * scale).ToString("F6", en_us) + " ");
								sw->WriteLine(structure[i][3].ToString("F6", en_us) + " " + (-structure[i][4]).ToString("F6", en_us) + " " + (-structure[i][5]).ToString("F6", en_us));
							}
						}
					}
				}
			}
		}

		delete skeleton_data;
		delete ema_data;
		sw->WriteLine("end");
		sw->Close();
	}

}
