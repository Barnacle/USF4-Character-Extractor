#pragma once

#include "AboutBox.h"
#include "Wrapper.h"
#include "Reader.h"
#include <filesystem>
#include <msclr/marshal_cppstd.h>

namespace file_sys = std::filesystem;

namespace SSF4ce {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	//
	using namespace System::IO;
	using namespace System::Text;
	using namespace System::Globalization;
	using namespace Microsoft::Win32;

	// Double click fix.
	// Uncomment this before final release and replace TreeView^ with NewTreeView^.
	/*public ref class NewTreeView : public TreeView
	{
	protected:
		virtual void WndProc(Message% m) override
		{
		if (m.Msg == WM_LBUTTONDBLCLK)
			return;
		else
		TreeView::WndProc(m);
		}
	};*/

	/// <summary>
	/// Summary for main
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::ToolStripDropDownButton^  toolStripDropDownButton3;
	private: System::Windows::Forms::ToolStripMenuItem^  steamToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  originStoreToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  MergeSubmodelsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  replaceSkelToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  starPoseFixToolStripMenuItem;
	private: System::Windows::Forms::SplitContainer^  BaseSplitContainer;
	private: System::Windows::Forms::SplitContainer^  TopSplitContainer;
	private: System::Windows::Forms::SplitContainer^  BottomSplitContainer;


	private: System::Windows::Forms::TrackBar^  trackBar1;

	public:
		Wrapper^ m_D3DWrap;
	private: System::Windows::Forms::ToolStripMenuItem^ refFrametoolStripMenuItem;
	public:
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog();

		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//			
			m_D3DWrap = gcnew Wrapper();
			m_D3DWrap->WrapInit(TopSplitContainer->Panel2->Handle.ToInt32(), TopSplitContainer->Panel2->Width, TopSplitContainer->Panel2->Height);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	protected:
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripDropDownButton^  toolStripDropDownButton1;
	private: System::Windows::Forms::ToolStripDropDownButton^  toolStripDropDownButton2;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;



	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Button^  button1;	
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::ComponentModel::IContainer^  components;


	// Double click fix.
	private: System::Windows::Forms::TreeView^  treeView1; // Comment this.
	//private: NewTreeView^  treeView1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::TreeNode^ treeNode1 = (gcnew System::Windows::Forms::TreeNode(L"Mesh"));
			System::Windows::Forms::TreeNode^ treeNode2 = (gcnew System::Windows::Forms::TreeNode(L"Skins"));
			System::Windows::Forms::TreeNode^ treeNode3 = (gcnew System::Windows::Forms::TreeNode(L"Animations"));
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripDropDownButton1 = (gcnew System::Windows::Forms::ToolStripDropDownButton());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripDropDownButton3 = (gcnew System::Windows::Forms::ToolStripDropDownButton());
			this->steamToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->originStoreToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MergeSubmodelsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->replaceSkelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripTextBox1 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->starPoseFixToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripDropDownButton2 = (gcnew System::Windows::Forms::ToolStripDropDownButton());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->BaseSplitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->TopSplitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->BottomSplitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->refFrametoolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->statusStrip1->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BaseSplitContainer))->BeginInit();
			this->BaseSplitContainer->Panel1->SuspendLayout();
			this->BaseSplitContainer->Panel2->SuspendLayout();
			this->BaseSplitContainer->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TopSplitContainer))->BeginInit();
			this->TopSplitContainer->Panel1->SuspendLayout();
			this->TopSplitContainer->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BottomSplitContainer))->BeginInit();
			this->BottomSplitContainer->Panel1->SuspendLayout();
			this->BottomSplitContainer->Panel2->SuspendLayout();
			this->BottomSplitContainer->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 540);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(784, 22);
			this->statusStrip1->TabIndex = 0;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(39, 17);
			this->toolStripStatusLabel1->Text = L"Ready";
			this->toolStripStatusLabel1->Visible = false;
			// 
			// toolStrip1
			// 
			this->toolStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolStripDropDownButton1,
					this->toolStripDropDownButton3, this->toolStripDropDownButton2
			});
			this->toolStrip1->Location = System::Drawing::Point(0, 0);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(784, 25);
			this->toolStrip1->Stretch = true;
			this->toolStrip1->TabIndex = 1;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripDropDownButton1
			// 
			this->toolStripDropDownButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripDropDownButton1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->openToolStripMenuItem,
					this->exitToolStripMenuItem
			});
			this->toolStripDropDownButton1->Name = L"toolStripDropDownButton1";
			this->toolStripDropDownButton1->ShowDropDownArrow = false;
			this->toolStripDropDownButton1->Size = System::Drawing::Size(29, 22);
			this->toolStripDropDownButton1->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exitToolStripMenuItem_Click);
			// 
			// toolStripDropDownButton3
			// 
			this->toolStripDropDownButton3->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripDropDownButton3->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->steamToolStripMenuItem,
					this->originStoreToolStripMenuItem, this->MergeSubmodelsToolStripMenuItem, this->replaceSkelToolStripMenuItem, this->toolStripTextBox1,
					this->starPoseFixToolStripMenuItem, this->refFrametoolStripMenuItem
			});
			this->toolStripDropDownButton3->Name = L"toolStripDropDownButton3";
			this->toolStripDropDownButton3->ShowDropDownArrow = false;
			this->toolStripDropDownButton3->Size = System::Drawing::Size(53, 22);
			this->toolStripDropDownButton3->Text = L"Settings";
			// 
			// steamToolStripMenuItem
			// 
			this->steamToolStripMenuItem->Checked = true;
			this->steamToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->steamToolStripMenuItem->Name = L"steamToolStripMenuItem";
			this->steamToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->steamToolStripMenuItem->Text = L"Steam folder";
			this->steamToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::steamToolStripMenuItem_Click);
			// 
			// originStoreToolStripMenuItem
			// 
			this->originStoreToolStripMenuItem->Checked = true;
			this->originStoreToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->originStoreToolStripMenuItem->Name = L"originStoreToolStripMenuItem";
			this->originStoreToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->originStoreToolStripMenuItem->Text = L"Origin coord. store";
			this->originStoreToolStripMenuItem->Visible = false;
			this->originStoreToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::originStoreToolStripMenuItem_Click);
			// 
			// MergeSubmodelsToolStripMenuItem
			// 
			this->MergeSubmodelsToolStripMenuItem->Name = L"MergeSubmodelsToolStripMenuItem";
			this->MergeSubmodelsToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->MergeSubmodelsToolStripMenuItem->Text = L"Merge submodels";
			this->MergeSubmodelsToolStripMenuItem->ToolTipText = L"By texture id";
			this->MergeSubmodelsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MergeSubmodelsToolStripMenuItem_Click);
			// 
			// replaceSkelToolStripMenuItem
			// 
			this->replaceSkelToolStripMenuItem->Name = L"replaceSkelToolStripMenuItem";
			this->replaceSkelToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->replaceSkelToolStripMenuItem->Text = L"Replace skeleton";
			this->replaceSkelToolStripMenuItem->ToolTipText = L"Quick fix for a T-Pose chars, not for a Star-Pose ones";
			this->replaceSkelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::replaceSkelToolStripMenuItem_Click);
			// 
			// toolStripTextBox1
			// 
			this->toolStripTextBox1->Name = L"toolStripTextBox1";
			this->toolStripTextBox1->Size = System::Drawing::Size(100, 23);
			this->toolStripTextBox1->Text = L"72";
			this->toolStripTextBox1->TextBoxTextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->toolStripTextBox1->ToolTipText = L"Scale";
			// 
			// starPoseFixToolStripMenuItem
			// 
			this->starPoseFixToolStripMenuItem->Name = L"starPoseFixToolStripMenuItem";
			this->starPoseFixToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->starPoseFixToolStripMenuItem->Text = L"Star-Pose Fix";
			this->starPoseFixToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::starPoseFixToolStripMenuItem_Click);
			// 
			// toolStripDropDownButton2
			// 
			this->toolStripDropDownButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripDropDownButton2->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutToolStripMenuItem });
			this->toolStripDropDownButton2->Name = L"toolStripDropDownButton2";
			this->toolStripDropDownButton2->ShowDropDownArrow = false;
			this->toolStripDropDownButton2->Size = System::Drawing::Size(36, 22);
			this->toolStripDropDownButton2->Text = L"Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(107, 22);
			this->aboutToolStripMenuItem->Text = L"About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::aboutToolStripMenuItem_Click);
			// 
			// treeView1
			// 
			this->treeView1->CheckBoxes = true;
			this->treeView1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->treeView1->Enabled = false;
			this->treeView1->Location = System::Drawing::Point(0, 0);
			this->treeView1->Name = L"treeView1";
			treeNode1->Name = L"Node0";
			treeNode1->Text = L"Mesh";
			treeNode2->Name = L"Node1";
			treeNode2->Text = L"Skins";
			treeNode3->Name = L"Node2";
			treeNode3->Text = L"Animations";
			this->treeView1->Nodes->AddRange(gcnew cli::array< System::Windows::Forms::TreeNode^  >(3) { treeNode1, treeNode2, treeNode3 });
			this->treeView1->Size = System::Drawing::Size(187, 466);
			this->treeView1->TabIndex = 0;
			this->treeView1->AfterCheck += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::treeView1_AfterCheck);
			this->treeView1->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::treeView1_AfterSelect);
			// 
			// button1
			// 
			this->button1->Enabled = false;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(0, 0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(186, 43);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Extract";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 30;
			this->timer1->Tick += gcnew System::EventHandler(this, &MainForm::timer1_Tick);
			// 
			// BaseSplitContainer
			// 
			this->BaseSplitContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->BaseSplitContainer->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->BaseSplitContainer->IsSplitterFixed = true;
			this->BaseSplitContainer->Location = System::Drawing::Point(0, 25);
			this->BaseSplitContainer->Name = L"BaseSplitContainer";
			this->BaseSplitContainer->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// BaseSplitContainer.Panel1
			// 
			this->BaseSplitContainer->Panel1->Controls->Add(this->TopSplitContainer);
			// 
			// BaseSplitContainer.Panel2
			// 
			this->BaseSplitContainer->Panel2->Controls->Add(this->BottomSplitContainer);
			this->BaseSplitContainer->Size = System::Drawing::Size(784, 515);
			this->BaseSplitContainer->SplitterDistance = 466;
			this->BaseSplitContainer->TabIndex = 3;
			// 
			// TopSplitContainer
			// 
			this->TopSplitContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->TopSplitContainer->Location = System::Drawing::Point(0, 0);
			this->TopSplitContainer->Name = L"TopSplitContainer";
			// 
			// TopSplitContainer.Panel1
			// 
			this->TopSplitContainer->Panel1->Controls->Add(this->treeView1);
			// 
			// TopSplitContainer.Panel2
			// 
			this->TopSplitContainer->Panel2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::TopSplitContainer_Panel2_MouseDown);
			this->TopSplitContainer->Panel2->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::TopSplitContainer_Panel2_MouseMove);
			this->TopSplitContainer->Panel2->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::TopSplitContainer_Panel2_MouseUp);
			this->TopSplitContainer->Size = System::Drawing::Size(784, 466);
			this->TopSplitContainer->SplitterDistance = 187;
			this->TopSplitContainer->TabIndex = 0;
			this->TopSplitContainer->SplitterMoved += gcnew System::Windows::Forms::SplitterEventHandler(this, &MainForm::TopSplitContainer_SplitterMoved);
			// 
			// BottomSplitContainer
			// 
			this->BottomSplitContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->BottomSplitContainer->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->BottomSplitContainer->IsSplitterFixed = true;
			this->BottomSplitContainer->Location = System::Drawing::Point(0, 0);
			this->BottomSplitContainer->Name = L"BottomSplitContainer";
			// 
			// BottomSplitContainer.Panel1
			// 
			this->BottomSplitContainer->Panel1->Controls->Add(this->button1);
			// 
			// BottomSplitContainer.Panel2
			// 
			this->BottomSplitContainer->Panel2->Controls->Add(this->trackBar1);
			this->BottomSplitContainer->Size = System::Drawing::Size(784, 45);
			this->BottomSplitContainer->SplitterDistance = 187;
			this->BottomSplitContainer->TabIndex = 0;
			// 
			// trackBar1
			// 
			this->trackBar1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->trackBar1->Enabled = false;
			this->trackBar1->Location = System::Drawing::Point(0, 0);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(593, 45);
			this->trackBar1->TabIndex = 1;
			this->trackBar1->Visible = false;
			// 
			// refFrametoolStripMenuItem
			// 
			this->refFrametoolStripMenuItem->Name = L"refFrametoolStripMenuItem";
			this->refFrametoolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->refFrametoolStripMenuItem->Text = L"Reference Frame";
			this->refFrametoolStripMenuItem->ToolTipText = L"Add Ref. pose frame to animation as \"time 0\"";
			this->refFrametoolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::refFrametoolStripMenuItem_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 562);
			this->Controls->Add(this->BaseSplitContainer);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->statusStrip1);
			this->MinimumSize = System::Drawing::Size(800, 600);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"USF4 Character Extractor PC";
			this->SizeChanged += gcnew System::EventHandler(this, &MainForm::MainForm_SizeChanged);
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->BaseSplitContainer->Panel1->ResumeLayout(false);
			this->BaseSplitContainer->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BaseSplitContainer))->EndInit();
			this->BaseSplitContainer->ResumeLayout(false);
			this->TopSplitContainer->Panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TopSplitContainer))->EndInit();
			this->TopSplitContainer->ResumeLayout(false);
			this->BottomSplitContainer->Panel1->ResumeLayout(false);
			this->BottomSplitContainer->Panel2->ResumeLayout(false);
			this->BottomSplitContainer->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BottomSplitContainer))->EndInit();
			this->BottomSplitContainer->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			Application::Exit();
}
private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			AboutBox^ AboutBox1 = gcnew AboutBox;
			AboutBox1->ShowDialog();
}
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 m_D3DWrap->WrapRender();
}
private: System::Void TopSplitContainer_Panel2_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 m_D3DWrap->WrapOnMouseMove((short)Control::MousePosition.X, (short)Control::MousePosition.Y, e->Button == System::Windows::Forms::MouseButtons::Right);
}
private: System::Void TopSplitContainer_Panel2_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 m_D3DWrap->WrapOnMouseButtonUp();
}
private: System::Void TopSplitContainer_Panel2_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 m_D3DWrap->WrapOnMouseButtonDown((short)Control::MousePosition.X, (short)Control::MousePosition.Y);
}
private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			if (steamToolStripMenuItem->Checked)
			{
				try{
					auto rk = Registry::CurrentUser->OpenSubKey("Software\\Valve\\Steam", false);
					auto steam_path = rk->GetValue("SteamPath")->ToString();
					rk->Close();

					if (steam_path)
					{
						steam_path = steam_path->Replace("/", "\\");
						steam_path += "\\SteamApps\\common\\Super Street Fighter IV - Arcade Edition\\resource\\battle\\chara";
						openFileDialog1->InitialDirectory = steam_path;
					}
				}
				catch(...){}
			}		
			openFileDialog1->Filter = "SF4 model|*obj.emo";
			openFileDialog1->Title = "Select model";

			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				treeView1->Nodes[0]->Nodes->Clear();
				treeView1->Nodes[1]->Nodes->Clear();
				treeView1->Nodes[2]->Nodes->Clear();

				auto fs = File::OpenRead(openFileDialog1->FileName);
				auto br = gcnew BinaryReader(fs);

				// Reading first 4 bytes, which are #EMO id
				if (String::Compare(Encoding::UTF8->GetString(br->ReadBytes(4)), "#EMO", true) == 0) // if 0, then skip
				{
					//==================================================================
					// Mesh
					//==================================================================

					//auto skeleton_data = ReadSkeleton(openFileDialog1->FileName, 16);

					// Data about nodes, sending in dx.
					
					//==================================================================

					fs->Position = 32; // Skipping 32 bytes to position about EMG ammount.
					const ushort EMG_count = br->ReadInt16(); 

					//==================================================================

					fs->Position = 32 + 4; // // Position of "offsets list" of EMG names offsets.
					unsigned int EMG_namesOffsets_Offset = br->ReadInt32(); // Reading.
					fs->Position = 32 + EMG_namesOffsets_Offset; // // Position of "offsets list" of EMG names.
					auto EMG_namesOffsets = gcnew array<unsigned int>(EMG_count); // Reading.
					for (auto i = 0; i < EMG_count; i++)
					{
						EMG_namesOffsets[i] = br->ReadUInt32();
					}

					auto EMG_names = gcnew array<String^>(EMG_count);
					for (auto i = 0; i < EMG_count; i++)
					{
						fs->Position = 32 + EMG_namesOffsets[i];

						auto sb = gcnew StringBuilder;
						while (br->ReadChar() != 0)
						{
							fs->Position--;
							sb->Append(br->ReadChar());
						}							

						EMG_names[i] = sb->ToString();
					}		

					//==================================================================

					fs->Position = 32 + 8; // Position of "offsets list" of every EMG.

					auto EMG_offsets = gcnew array<unsigned int>(EMG_count);
					auto EMG_data = gcnew array<EMG_Data^>(EMG_count);

					m_D3DWrap->WrapCreateBuffers(EMG_count); // Creating array of buffers.

					for (ushort i = 0; i < EMG_count; i++)
					{
						EMG_offsets[i] = br->ReadInt32(); // Filling array with list.
						EMG_data[i] = ReadEMG(openFileDialog1->FileName, 32 + EMG_offsets[i] + 16); // Filling array with data about each EMG.

						pin_ptr<byte> pDDSid = &EMG_data[i]->DDSid[0];
						byte* npDDSid = pDDSid;

						pin_ptr<ushort> pIndexCount = &EMG_data[i]->IndexCount[0];
						ushort* npIndexCount = pIndexCount;

						pin_ptr<byte> pVertexArray = &EMG_data[i]->VertexArray[0];
						byte* npVertexArray = pVertexArray;

						using Runtime::InteropServices::GCHandle;
						using Runtime::InteropServices::GCHandleType;

						auto pins = gcnew array<GCHandle>(EMG_data[i]->IndiceArray->Length);
						for (auto a = 0, i_max = pins->Length; a != i_max; a++)
							pins[a] = GCHandle::Alloc(EMG_data[i]->IndiceArray[a], GCHandleType::Pinned);

						try
						{
							auto arrays = gcnew array<ushort*>(pins->Length);
							for (auto a = 0, i_max = arrays->Length; a != i_max; a++)
								arrays[a] = static_cast<ushort*>(pins[a].AddrOfPinnedObject().ToPointer());

							// pin outer array<ushort*>^
							const pin_ptr<ushort*> pin = &arrays[0];

							m_D3DWrap->WrapLoadEMG(i, EMG_data[i]->SubmodelCount, npDDSid, npIndexCount,
								EMG_data[i]->VertexCount, EMG_data[i]->VertexSize, pin, npVertexArray);
						}
						catch (...)
						{
							// unpin each contained array<ushort>^
							for each (GCHandle pin in pins)
								pin.Free();
						}

						delete EMG_data[i];
						treeView1->Nodes[0]->Nodes->Add(gcnew TreeNode((i + 1) + ". " + EMG_names[i]));
						treeView1->Nodes[0]->Nodes[i]->Checked = true;
					}

					button1->Enabled = true;
					treeView1->Enabled = true;	
					treeView1->Nodes[0]->Checked = true;
					treeView1->Nodes[0]->Expand();

					//==================================================================
					// Textures
					//==================================================================

					array<Char>^ trim_chars = { 'o', 'b', 'e', 'm', 'j', '.' };
					const auto path = Path::GetDirectoryName(openFileDialog1->FileName);
					auto name = Path::GetFileName(openFileDialog1->FileName)->TrimEnd(trim_chars);
					
					if (!File::Exists(path + "\\" + name + "_01.col.emb"))
					{						
						//m_D3DWrap->WrapLoadDDS(0, 0, 0);
					}						
					else
					{
						fs = File::OpenRead(path + "\\" + name + "_01.col.emb");
						auto br2 = gcnew BinaryReader(fs);

						if (String::Compare(Encoding::UTF8->GetString(br2->ReadBytes(4)), "#EMB", true) == 0) // If 0, continue reading.
						{
							treeView1->Nodes[1]->Checked = true;

							for (char i = 0; i < 22; i++)
							{
								String^ node_name;
								if (i < 9)
									node_name = name + "_0" + (i + 1) + ".col.emb";
								else
									node_name = name + "_" + (i + 1) + ".col.emb";

								if (File::Exists(path + "\\" + node_name))
								{
									treeView1->Nodes[1]->Nodes->Add(gcnew TreeNode(node_name));
									treeView1->Nodes[1]->Nodes[treeView1->Nodes[1]->LastNode->Index]->Checked = true;
								}
							}

							auto EMB_data = ReadEMB(path + "\\" + name + "_01.col.emb");

							pin_ptr<ulong> pDDSsize = &EMB_data->DDSsize[0];
							ulong* npDDSsize = pDDSsize;

							using Runtime::InteropServices::GCHandle;
							using Runtime::InteropServices::GCHandleType;

							auto pins = gcnew array<GCHandle>(EMB_data->DDSArray->Length);
							for (auto i = 0, i_max = pins->Length; i != i_max; ++i)
								pins[i] = GCHandle::Alloc(EMB_data->DDSArray[i], GCHandleType::Pinned);

							try
							{
								auto arrays = gcnew array<byte*>(pins->Length);
								for (auto i = 0, i_max = arrays->Length; i != i_max; ++i)
									arrays[i] = static_cast<byte*>(pins[i].AddrOfPinnedObject().ToPointer());

								// pin outer array<int*>^
								const pin_ptr<byte*> pin = &arrays[0];

								m_D3DWrap->WrapLoadDDS(EMB_data->DDScount, npDDSsize, pin);
							}
							catch (...)
							{
								// unpin each contained array<int>^
								for each (GCHandle pin in pins)
									pin.Free();
							}

							delete EMB_data;
							treeView1->Nodes[1]->Expand();
						}								
					}

					// Normal map
					if (!File::Exists(path + "\\" + name + ".nml.emb"))
					{
						//
					}
					else
					{
						fs = File::OpenRead(path + "\\" + name + ".nml.emb");
						auto br2 = gcnew BinaryReader(fs);

						if (String::Compare(Encoding::UTF8->GetString(br2->ReadBytes(4)), "#EMB", true) == 0) // If 0, continue reading.
						{
							treeView1->Nodes[1]->Nodes->Add(gcnew TreeNode("Normal map"));
							treeView1->Nodes[1]->Nodes[treeView1->Nodes[1]->LastNode->Index]->Checked = true;
						}

						br2->Close();
					}

					//==================================================================
					// Animations
					//==================================================================

					array<Char>^ trim_chars2 = { '_', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
					const auto name2 = name->TrimEnd(trim_chars2);

					auto files = Directory::GetFiles(path);
					for(auto index = 0; index < files->Length; index++)
					{
						auto file = files[index];
						if(file->EndsWith(".ema"))
						{
							OpenAnimFile(path, getFileName(file, true));
						}
					}
				}
				else
				{
					MessageBox::Show("Not a EMO", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				}	

				br->Close();
				fs->Close();
			}
}

static String^ getFileName(String^ filePath, bool withExtension)
{
	// Create a Path object from File Path
	const file_sys::path pathObj(msclr::interop::marshal_as<std::string>(filePath));

	// Check if file name is required without extension
	if (withExtension == false)
	{
		// Check if file has stem i.e. filename without extension
		if (pathObj.has_stem())
		{
			// return the stem (file name without extension) from path object
			return msclr::interop::marshal_as<String^>(pathObj.stem().string());
		}
		return "";
	}

	// return the file name with extension from path object
	return msclr::interop::marshal_as<String^>((pathObj.filename().string()));
}
Void OpenAnimFile(String^ path, String^ name)
{
	if (!File::Exists(path + "\\" + name))
	{
		//
	}
	else
	{
		auto fs = File::OpenRead(path + "\\" + name);
		auto br2 = gcnew BinaryReader(fs);

		if (String::Compare(Encoding::UTF8->GetString(br2->ReadBytes(4)), "#EMA", true) == 0) // If 0, continue reading.
		{
			EMA_Data^ EMA_data = {};
			try
			{
				EMA_data = ReadEMA(path + "\\" + name);

				treeView1->Nodes[2]->Checked = true;
				treeView1->Nodes[2]->Nodes->Add(gcnew TreeNode(name));
				treeView1->Nodes[2]->LastNode->Checked = true;

				for (ushort i = 0; i < EMA_data->AnimationCount; i++)
				{
					const auto animation_name = gcnew String(EMA_data->AnimationName[i]);
					treeView1->Nodes[2]->LastNode->Nodes->Add(gcnew TreeNode(i + 1 + ". " + animation_name));
					treeView1->Nodes[2]->LastNode->Nodes[i]->Checked = true;
				}

				delete EMA_data;
				treeView1->Nodes[2]->LastNode->Expand();
				treeView1->Nodes[2]->Expand();
			}
			catch (...)
			{
				delete EMA_data;
			}
		}

		br2->Close();
		fs->Close();
	}
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 treeView1->Enabled = false;

			 array<Char>^ trim_chars = { 'o', 'b', 'e', 'm', 'j', '.' };
			 auto path = Path::GetDirectoryName(openFileDialog1->FileName);
			 auto name = Path::GetFileName(openFileDialog1->FileName)->TrimEnd(trim_chars);

			 if (treeView1->Nodes[0]->Checked == true) // mesh
			 {
				 // SMD exporter
				 auto saveFileDialog1 = gcnew SaveFileDialog();
				 saveFileDialog1->FileName = name;
				 saveFileDialog1->Filter = "SMD model|*.smd";
				 saveFileDialog1->RestoreDirectory = true;

				 if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 auto fs = File::OpenRead(openFileDialog1->FileName);
					 auto br = gcnew BinaryReader(fs);
					 auto sw = gcnew StreamWriter(saveFileDialog1->FileName);

					 auto scale = ushort::Parse(toolStripTextBox1->Text);

					 sw->WriteLine("version 1");

					 //==================================================================
					 // Nodes tree.
					 //==================================================================

					 auto skeleton_data = ReadSkeleton(openFileDialog1->FileName, 16);

					 sw->WriteLine("nodes");					 

					 for (ushort i = 0; i < skeleton_data->NodesCount; i++) // 
					 {
						 auto node_name = skeleton_data->NodeName[i];
						 sw->WriteLine(i + " " + "\"" + node_name + "\"" + " " + skeleton_data->ParentNodeArray[i]); //" \"root\"  child+1
					 }						 

					 sw->WriteLine("end");

					 //==================================================================
					 // Position of nodes.
					 //==================================================================
					 sw->WriteLine("skeleton");
					 sw->WriteLine("time 0");		

					 float structure[500][6];
					 std::string names[500];
					 if (replaceSkelToolStripMenuItem->Checked == true) // If animation is not selected, exporting original skeleton.
					 {		
						 array<Char>^ trim_chars2 = { '_', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
						 auto name2 = name->TrimEnd(trim_chars2);

						 auto anim_name = gcnew String(path + "\\" + name2 + ".obj.ema");
						 m_D3DWrap->WrapSetup(anim_name, 0);
						 m_D3DWrap->WrapUpdate(structure, names, "NONE", 0);
					 }

					 using Runtime::InteropServices::GCHandle;
					 using Runtime::InteropServices::GCHandleType;

					 auto pins = gcnew array<GCHandle>(skeleton_data->Matrix4x4->Length);
					 for (auto a = 0, i_max = pins->Length; a != i_max; ++a)
						 pins[a] = GCHandle::Alloc(skeleton_data->Matrix4x4[a], GCHandleType::Pinned);

					 auto arrays = gcnew array<byte*>(pins->Length);
					 for (auto a = 0, i_max = arrays->Length; a != i_max; ++a)
						 arrays[a] = static_cast<byte*>(pins[a].AddrOfPinnedObject().ToPointer());

					 // pin outer array<int*>^
					 pin_ptr<byte*> pin = &arrays[0];

					 for (ushort i = 0; i < skeleton_data->NodesCount; i++) // 
					 {
						 auto en_us = gcnew CultureInfo("en-US");

						 auto tx = *reinterpret_cast<float*>(pin[i] + 48); // 12
						 auto ty = *reinterpret_cast<float*>(pin[i] + 56); // 14
						 auto tz = -*reinterpret_cast<float*>(pin[i] + 52); // 13

						 auto rx = atan2(-*reinterpret_cast<float*>(pin[i] + 36), *reinterpret_cast<float*>(pin[i] + 20)); // 9, 5
						 auto ry = -atan2(-*reinterpret_cast<float*>(pin[i] + 8), *reinterpret_cast<float*>(pin[i])); // 2, 0						 
						 auto rz = asin(*reinterpret_cast<float*>(pin[i] + 4)); // 1

						 if (replaceSkelToolStripMenuItem->Checked == true) // If not checked, exporting original skeleton.
						 {
							 auto node_name = skeleton_data->NodeName[i]; // Name of current node.	

							 array<Char>^ trim_chars2 = { '_', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
							 auto name2 = name->TrimEnd(trim_chars2);
							 auto skeleton_data2 = ReadSkeleton(path + "\\" + name2 + ".obj.ema", 12);

							 for (ushort nodes = 0; nodes < skeleton_data2->NodesCount; nodes++) // Replacing values of current node with values of reference skeleton from animation.
							 {
								 auto name_temp(names[nodes]);
								 auto nameclr = gcnew String(name_temp.c_str());

								 if (nameclr == node_name)
								 {
									 tx = structure[nodes][0];
									 ty = structure[nodes][1];
									 tz = structure[nodes][2];
									 rx = structure[nodes][3];
									 rz = structure[nodes][4];

									 if (starPoseFixToolStripMenuItem->Checked == true)
									 {
										 if (nameclr == "RLegRoot")
											 ry = -float(0.610842);
										 else if (nameclr == "LLegRoot")
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
							 + (-ry).ToString("F6", en_us) );
					 }
					 delete skeleton_data;
					 sw->WriteLine("end");

					 //==================================================================
					 // Triangles
					 //==================================================================
					 fs->Position = 32; // Skipping 32 bytes to position about EMG ammount.
					 ushort EMG_count = br->ReadInt16();
					 fs->Position = 32 + 8; // Position of "offsets list" of every EMG.

					 auto EMG_offsets = gcnew array<int>(EMG_count);
					 auto EMG_data = gcnew array<EMG_Data^>(EMG_count);
					 
					 sw->WriteLine("triangles");

					 for (auto current_EMG = 0; current_EMG < EMG_count; current_EMG++)
					 {
						 EMG_offsets[current_EMG] = br->ReadInt32(); // Filling array with list.
						 EMG_data[current_EMG] = ReadEMG(openFileDialog1->FileName, 32 + EMG_offsets[current_EMG] + 16); // Filling array with data about each EMG.

						 if (treeView1->Nodes[0]->Nodes[current_EMG]->Checked)
						 {
							 for (auto current_submodel = 0; current_submodel < EMG_data[current_EMG]->SubmodelCount; current_submodel++)
							 {
								 for (ushort i = 0; i < EMG_data[current_EMG]->IndexCount[current_submodel] - 2; i++)
								 {
									 auto en_us = gcnew CultureInfo("en-US");

									 int a, b, c;

									 String^ texture;
									 if (MergeSubmodelsToolStripMenuItem->Checked)
										 texture = name + "_" + (EMG_data[current_EMG]->DDSid[current_submodel] + 1) + ".dds";
									 else
										 texture = current_EMG + "_" + name + "_" + (EMG_data[current_EMG]->DDSid[current_submodel] + 1) + ".dds";

									 if (i % 2 == 0)
									 {
										 a = EMG_data[current_EMG]->IndiceArray[current_submodel][i + 0];
										 b = EMG_data[current_EMG]->IndiceArray[current_submodel][i + 1];
										 c = EMG_data[current_EMG]->IndiceArray[current_submodel][i + 2];

										 if (a != b && b != c) // skipping degenerate triangle
										 {
											 sw->WriteLine(texture);

											 for (char x = 2; x > -1; x--)
											 {
												 int index = EMG_data[current_EMG]->IndiceArray[current_submodel][i + x];
												 pin_ptr<byte> pVertexArray = &EMG_data[current_EMG]->VertexArray[0];

												 sw->Write("0 "
													 // PosX PosY PosZ
													 + (-*reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray)) * scale).ToString("F6", en_us) + " "
													 + (*reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray) + 4) * scale).ToString("F6", en_us) + " "
													 + (*reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray) + 8) * scale).ToString("F6", en_us) + " "
													 // NormX NormY NormZ
													 + (*reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray) + 12)).ToString("F6", en_us) + " "
													 + (*reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray) + 16)).ToString("F6", en_us) + " "
													 + (*reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray) + 20)).ToString("F6", en_us) + " "
													 // U V
													 + (*reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray) + 24)).ToString("F6", en_us) + " "
													 + (-*reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray) + 28)).ToString("F6", en_us) + " ");
												 
												 byte BoneID[4];
												 for (byte num = 0; num < 4; num++)
													 BoneID[num] = *reinterpret_cast<byte*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray) + 48 + num);
												 float weight[3];
												 for (byte num = 0; num < 3; num++)
													 weight[num] = *reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray) + 52 + (num * 4));

												 if (weight[0] != 0 && weight[1] == 0) // if 1
													 sw->WriteLine("1 " + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[0]].ToString() + " 1");
												 else if (weight[0] != 0 && weight[1] != 0 && weight[2] == 0) // if 2
													 sw->WriteLine("2 " + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[0]].ToString() + " "
													 + weight[0].ToString("F6", en_us) + " "
													 + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[1]].ToString() + " "
													 + weight[1].ToString("F6", en_us));
												 else if (weight[0] + weight[1] + weight[2] > 0.999) // if 3
													 sw->WriteLine("3 " + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[0]].ToString() + " "
													 + weight[0].ToString("F6", en_us) + " "
													 + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[1]].ToString() + " "
													 + weight[1].ToString("F6", en_us) + " "
													 + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[2]].ToString() + " "
													 + weight[2].ToString("F6", en_us));
												 else // if 4
													 sw->WriteLine("4 " + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[0]].ToString() + " "
													 + weight[0].ToString("F6", en_us) + " "
													 + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[1]].ToString() + " "
													 + weight[1].ToString("F6", en_us) + " "
													 + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[2]].ToString() + " "
													 + weight[2].ToString("F6", en_us) + " "
													 + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[3]].ToString() + " "
													 + (1 - (weight[0] + weight[1] + weight[2])).ToString("F6", en_us));
											 }
										 }
									 }
									 else
									 {
										 a = EMG_data[current_EMG]->IndiceArray[current_submodel][i + 2];
										 b = EMG_data[current_EMG]->IndiceArray[current_submodel][i + 1];
										 c = EMG_data[current_EMG]->IndiceArray[current_submodel][i + 0];

										 if (a != b && b != c)
										 {
											 sw->WriteLine(texture);

											 for (char x = 0; x < 3; x++)
											 {
												 int index = EMG_data[current_EMG]->IndiceArray[current_submodel][i + x];
												 pin_ptr<byte> pVertexArray = &EMG_data[current_EMG]->VertexArray[0];

												 sw->Write("0 "
													 // PosX PosY PosZ
													 + (-*reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray)) * scale).ToString("F6", en_us) + " "
													 + (*reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray) + 4) * scale).ToString("F6", en_us) + " "
													 + (*reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray) + 8) * scale).ToString("F6", en_us) + " "
													 // NormX NormY NormZ
													 + (*reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray)  + 12)).ToString("F6", en_us) + " "
													 + (*reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray) + 16)).ToString("F6", en_us) + " "
													 + (*reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray) + 20)).ToString("F6", en_us) + " "
													 // U V
													 + (*reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray) + 24)).ToString("F6", en_us) + " "
													 + (-*reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray) + 28)).ToString("F6", en_us) + " ");

												 byte BoneID[4];
												 for (byte num = 0; num < 4; num++)
													 BoneID[num] = *reinterpret_cast<byte*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray) + 48 + num);
												 float weight[3];
												 for (byte num = 0; num < 3; num++)
													 weight[num] = *reinterpret_cast<float*>(index * EMG_data[current_EMG]->VertexSize + int(pVertexArray) + 52 + (num * 4));

												 if (weight[0] != 0 && weight[1] == 0)
													 sw->WriteLine("1 " + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[0]].ToString() + " 1");
												 else if (weight[0] != 0 && weight[1] != 0 && weight[2] == 0)
													 sw->WriteLine("2 " + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[0]].ToString() + " "
													 + weight[0].ToString("F6", en_us) + " "
													 + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[1]].ToString() + " "
													 + weight[1].ToString("F6", en_us));
												 else if (weight[0] + weight[1] + weight[2] > 0.999)
													 sw->WriteLine("3 " + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[0]].ToString() + " "
													 + weight[0].ToString("F6", en_us) + " "
													 + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[1]].ToString() + " "
													 + weight[1].ToString("F6", en_us) + " "
													 + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[2]].ToString() + " "
													 + weight[2].ToString("F6", en_us));
												 else 
													 sw->WriteLine("4 " + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[0]].ToString() + " "
													 + weight[0].ToString("F6", en_us) + " "
													 + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[1]].ToString() + " "
													 + weight[1].ToString("F6", en_us) + " "
													 + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[2]].ToString() + " "
													 + weight[2].ToString("F6", en_us) + " "
													 + EMG_data[current_EMG]->NodesArray[current_submodel][BoneID[3]].ToString() + " "
													 + (1 - (weight[0] + weight[1] + weight[2])).ToString("F6", en_us));
											 }
										 }
									 }
								 }
							 }
						 }

						 delete EMG_data[current_EMG];
					 }
					 
					 sw->Write("end");

					 sw->Close();
					 br->Close();
					 fs->Close();

					 MessageBox::Show("Mesh extracted", "Done", MessageBoxButtons::OK);
				 }
			 }

			 if(treeView1->Nodes[1]->Checked == true) // textures
			 {
				 auto saveFileDialog1 = gcnew SaveFileDialog();
				 saveFileDialog1->FileName = name;
				 saveFileDialog1->Filter = "DDS Texture|*.dds";
				 saveFileDialog1->RestoreDirectory = true;

				 if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {		 
					 for (auto node = 0; node < treeView1->Nodes[1]->LastNode->Index; node++)
					 {
						 if (treeView1->Nodes[1]->Nodes[node]->Checked)
						 {
							 auto temp = path + "\\" + treeView1->Nodes[1]->Nodes[node]->Text;
							 auto EMB_data = ReadEMB(temp);

							 auto temp_name = treeView1->Nodes[1]->Nodes[node]->Text;
							 auto name2 = temp_name->Split('.');
							 auto name_arr = name2[0]->Split('_');

							 for (auto i = 0; i < EMB_data->DDScount; i++)
							 {
								 auto output_path = Path::GetDirectoryName(saveFileDialog1->FileName);
								 auto fs = gcnew FileStream(output_path + "\\" + name_arr[0] + "_" + name_arr[1] + "_" + (i+1) + "_" + name_arr[2] + ".dds", FileMode::Create, FileAccess::ReadWrite);
								 auto br = gcnew BinaryWriter(fs);

								 for (ulong a = 0; a < EMB_data->DDSsize[i]; a++)
									 br->Write(EMB_data->DDSArray[i][a]);

								 br->Close();
								 fs->Close();
							 }

							 delete EMB_data;
						 }
					 }					 

					 // Normal map.
					 if (treeView1->Nodes[1]->Nodes[treeView1->Nodes[1]->LastNode->Index]->Checked)
					 {
						 auto EMB_data = ReadEMB(path + "\\" + name + ".nml.emb");

						 for (auto i = 0; i < EMB_data->DDScount; i++)
						 {
							 auto output_path = Path::GetDirectoryName(saveFileDialog1->FileName);
							 auto fs = gcnew FileStream(output_path + "\\" + name + "_" + i + ".nml.dds", FileMode::Create, FileAccess::ReadWrite);
							 auto br = gcnew BinaryWriter(fs);

							 for (ulong a = 0; a < EMB_data->DDSsize[i]; a++)
								 br->Write(EMB_data->DDSArray[i][a]);

							 br->Close();
							 fs->Close();
						 }

						 delete EMB_data;
					 }					
					 MessageBox::Show("Textures extracted", "Done", MessageBoxButtons::OK);
				 }
			 }

			 if(treeView1->Nodes[2]->Checked == true) // animations
			 {
				 auto saveFileDialog1 = gcnew SaveFileDialog();
				 array<Char>^ trim_chars2 = { '_', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
				 auto name2 = name->TrimEnd(trim_chars2);
				 saveFileDialog1->FileName = name2 + "_anim";
				 saveFileDialog1->Filter = "SMD animation|*.smd";
				 saveFileDialog1->RestoreDirectory = true;

				 if (saveFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
				 {
					 auto animFiles_enum = treeView1->Nodes[2]->Nodes->GetEnumerator();

					 while (animFiles_enum->MoveNext())
					 {
						 auto fileNode = safe_cast<TreeNode^>(animFiles_enum->Current);
						 if (fileNode->Checked)
						 {
							 ushort animation_id;
							 auto my_enum = treeView1->Nodes[2]->Nodes[fileNode->Index]->Nodes->GetEnumerator();

							 auto anim_name = gcnew String(path + "\\" + fileNode->Text);
							 m_D3DWrap->WrapSetup(anim_name, 0);

							 while (my_enum->MoveNext())
							 {
								 auto node = safe_cast<TreeNode^>(my_enum->Current);
								 if (node->Checked)
								 {
									 animation_id = node->Index;

									 auto output_path = Path::GetDirectoryName(saveFileDialog1->FileName);

									 Directory::CreateDirectory(output_path + "\\" + fileNode->Text);

									 auto sw = gcnew StreamWriter(output_path + "\\" + fileNode->Text + "\\" + node->Text + ".smd");

									 auto en_us = gcnew CultureInfo("en-US");

									 auto scale = ushort::Parse(toolStripTextBox1->Text);

									 sw->WriteLine("version 1");

									 //==================================================================
									 // Nodes tree.
									 //==================================================================					 

									 auto skeleton_data = ReadSkeleton(path + "\\" + fileNode->Text, 12);

									 sw->WriteLine("nodes");

									 for (ushort i = 0; i < skeleton_data->NodesCount; i++) // 
									 {
										 auto node_name = skeleton_data->NodeName[i];
										 sw->WriteLine(i + " " + "\"" + node_name + "\"" + " " + skeleton_data->ParentNodeArray[i]); //" \"root\"  child+1
									 }

									 sw->WriteLine("end");

									 //==================================================================
									 // Nodes position.
									 //==================================================================

									 sw->WriteLine("skeleton");

									 auto EMA_data = ReadEMA(path + "\\" + fileNode->Text);

									 auto animation_name = gcnew String(EMA_data->AnimationName[animation_id]);
									 int duration = EMA_data->Duration[animation_id];

									 float structure[500][6];
									 std::string names[500];

									 // Reference frame.
									 if (refFrametoolStripMenuItem->Checked == true)
									 {
										 m_D3DWrap->WrapUpdate(structure, names, "ref", 0);
										 sw->WriteLine("time 0");
										 for (auto i = 0; i < skeleton_data->NodesCount; i++)
										 {
											 if (i == 0)
												 sw->WriteLine("0 0 0 0 0 0 0"); //1.570796 3.141592
											 else if (i != 0)
											 {
												 sw->Write(i + " " + (-structure[i][0] * scale).ToString("F6", en_us) + " " + (structure[i][1] * scale).ToString("F6", en_us) + " " + (structure[i][2] * scale).ToString("F6", en_us) + " ");
												 sw->WriteLine(structure[i][3].ToString("F6", en_us) + " " + (-structure[i][4]).ToString("F6", en_us) + " " + (-structure[i][5]).ToString("F6", en_us));
											 }
										 }
									 }

									 // Actual animation.
									 for (ushort time = 0; time < duration; time++)
									 {
										 sw->WriteLine("time " + (time + refFrametoolStripMenuItem->Checked == true ? 1 : 0));
										 m_D3DWrap->WrapUpdate(structure, names, animation_name, time);
										 for (auto i = 0; i < skeleton_data->NodesCount; i++)
										 {
											 auto nameclr = gcnew String(names[i].c_str());

											 if (!nameclr->Equals("camera") && i == 0 && time == 0)
												 sw->WriteLine("0 0 0 0 0 0 0"); //1.570796 3.141592
											 else if (nameclr->Equals("camera") || i != 0)
											 {
												 if (nameclr == "RLegRoot" || nameclr == "LLegRoot" || nameclr == "LArmRoot" || nameclr == "RArmRoot")
												 { }
												 else
												 {
													 sw->Write(i + " " + (-structure[i][0] * scale).ToString("F6", en_us) + " " + (structure[i][1] * scale).ToString("F6", en_us) + " " + (structure[i][2] * scale).ToString("F6", en_us) + " ");
													 sw->WriteLine(structure[i][3].ToString("F6", en_us) + " " + (-structure[i][4]).ToString("F6", en_us) + " " + (-structure[i][5]).ToString("F6", en_us));
												 }
											 }
										 }
									 }

									 delete skeleton_data;
									 delete EMA_data;
									 sw->WriteLine("end");
									 sw->Close();
								 }
							 }
						 }
					 }

					 MessageBox::Show("Animations extracted", "Done", MessageBoxButtons::OK);
				 }
			 }

			 treeView1->Enabled = true;
}
// Updates all child tree nodes recursively.
void CheckAllChildNodes(TreeNode^ treeNode, bool nodeChecked)
{
	auto myEnum = treeNode->Nodes->GetEnumerator();
	while (myEnum->MoveNext())
	{
		const auto node = safe_cast<TreeNode^>(myEnum->Current);
		node->Checked = nodeChecked;
		if (node->Nodes->Count > 0)
		{
			// If the current node has child nodes, call the CheckAllChildsNodes method recursively.
			this->CheckAllChildNodes(node, nodeChecked);
		}
	}
}
void CheckParent(TreeNode^ treeNode)
{
	if (treeNode->Parent != nullptr)
	{
		auto i = 0; // Counting selected nodes.
		auto my_enum = treeNode->Parent->Nodes->GetEnumerator();
		while (my_enum->MoveNext())
		{
			const auto node = safe_cast<TreeNode^>(my_enum->Current);
			if (node->Checked)
				i++;
		}
		if (i == 0) // If 0, then uncheck parent.
		{
			treeNode->Parent->Checked = false;
			CheckParent(treeNode->Parent);
		}
		else
		{
			treeNode->Parent->Checked = true;
			CheckParent(treeNode->Parent);
		}
	}
}
private: System::Void treeView1_AfterCheck(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 //==================================================================
			 treeView1->BeginUpdate();
			 if (e->Action != TreeViewAction::Unknown)
			 {
				 if (e->Node->Nodes->Count > 0)
				 {
					 /* Calls the CheckAllChildNodes method, passing in the current
						 Checked value of the TreeNode whose checked state changed. */
					 this->CheckAllChildNodes(e->Node, e->Node->Checked);
				 }

				 CheckParent(e->Node);

				 //if (e->Node->Parent != nullptr)
				 //{
					// auto i = 0; // Counting selected nodes.
					// auto my_enum = e->Node->Parent->Nodes->GetEnumerator();
					// while (my_enum->MoveNext())
					// {
					//	 const auto node = safe_cast<TreeNode^>(my_enum->Current);
					//	 if (node->Checked)
					//		 i++;
					// }
					// if (i == 0) // If 0, then uncheck parent.
					//	 e->Node->Parent->Checked = false;
					// else
					//	 e->Node->Parent->Checked = true;
				 //}
			 }	
			 treeView1->EndUpdate();
			 //==================================================================

			 if (e->Action != TreeViewAction::Unknown)
			 {
				 if (e->Node->Name == "Node0") // If "Mesh" node checked.
				 {
					 if (e->Node->Checked) // Show full model.
					 {
						 auto fs = File::OpenRead(openFileDialog1->FileName);
						 auto br = gcnew BinaryReader(fs);

						 fs->Position = 32; // Skipping 32 bytes to position about EMG ammount.
						 ushort EMGcount = br->ReadInt16();
						 fs->Position = 32 + 8; // Position of "offsets list" of every EMG.

						 auto EMG_offsets = gcnew array<unsigned int>(EMGcount);
						 auto EMG_data = gcnew array<EMG_Data^>(EMGcount);

						 m_D3DWrap->WrapCreateBuffers(EMGcount); // Creating array of buffers.

						 for (byte i = 0; i < EMGcount; i++)
						 {
							 EMG_offsets[i] = br->ReadInt32(); // Filling array with list.
							 EMG_data[i] = ReadEMG(openFileDialog1->FileName, 32 + EMG_offsets[i] + 16); // Filling array with data about each EMG.

							 pin_ptr<byte> pDDSid = &EMG_data[i]->DDSid[0];
							 byte* npDDSid = pDDSid;

							 pin_ptr<ushort> pIndexCount = &EMG_data[i]->IndexCount[0];
							 ushort* npIndexCount = pIndexCount;

							 pin_ptr<byte> pVertexArray = &EMG_data[i]->VertexArray[0];
							 byte* npVertexArray = pVertexArray;

							 using Runtime::InteropServices::GCHandle;
							 using Runtime::InteropServices::GCHandleType;

							 auto pins = gcnew array<GCHandle>(EMG_data[i]->IndiceArray->Length);
							 for (auto a = 0, i_max = pins->Length; a != i_max; ++a)
								 pins[a] = GCHandle::Alloc(EMG_data[i]->IndiceArray[a], GCHandleType::Pinned);

							 try
							 {
								 auto arrays = gcnew array<ushort*>(pins->Length);
								 for (auto a = 0, i_max = arrays->Length; a != i_max; ++a)
									 arrays[a] = static_cast<ushort*>(pins[a].AddrOfPinnedObject().ToPointer());

								 // pin outer array<ushort*>^
								 const pin_ptr<ushort*> pin = &arrays[0];

								 m_D3DWrap->WrapLoadEMG(i, EMG_data[i]->SubmodelCount, npDDSid, npIndexCount,
									 EMG_data[i]->VertexCount, EMG_data[i]->VertexSize, pin, npVertexArray);
							 }
							 catch (...)
							 {
								 // unpin each contained array<ushort>^
								 for each (GCHandle pin in pins)
									 pin.Free();
							 }

							 delete EMG_data[i];
						 }
					 }
					 else // Remove full model.
					 {
						 m_D3DWrap->WrapCreateBuffers(0);
					 }
				 }

				 // Show parts of model
				 if (e->Node->Parent != nullptr && e->Node->Parent->Name == "Node0")
				 {
					 const auto fs = File::OpenRead(openFileDialog1->FileName);
					 auto br = gcnew BinaryReader(fs);

					 fs->Position = 32; // Skipping 32 bytes to position about EMG ammount.
					 ushort EMG_count = br->ReadInt16();
					 fs->Position = 32 + 8; // Position of "offsets list" of every EMG.

					 auto EMG_offsets = gcnew array<int>(EMG_count);
					 auto EMG_data = gcnew array<EMG_Data^>(EMG_count);
					 
					 // Counting amount of buffers, creating array of checks.
					 ushort buffer_count = 0;
					 auto arr = gcnew array<bool>(EMG_count);
					 auto my_enum = e->Node->Parent->Nodes->GetEnumerator();
					 while (my_enum->MoveNext())
					 {
						 const auto node = safe_cast<TreeNode^>(my_enum->Current);						 
						 if (node->Checked)
						 {
							 buffer_count++;
							 arr[node->Index] = true;
						 }
						 else
							 arr[node->Index] = false;							 
					 }

					 m_D3DWrap->WrapCreateBuffers(buffer_count); // Creating array of buffers.

					 // Filling arrays simmilar to checks.
					 auto sendcount = 0;
					 for (byte i = 0; i < EMG_count; i++)
					 {
						 EMG_offsets[i] = br->ReadInt32(); // Filling array with list.
						 
						 if (arr[i] == true)
						 {
							 EMG_data[i] = ReadEMG(openFileDialog1->FileName, 32 + EMG_offsets[i] + 16); // Filling array with data about each EMG.

							 pin_ptr<byte> pDDSid = &EMG_data[i]->DDSid[0];
							 byte* npDDSid = pDDSid;

							 pin_ptr<ushort> pIndexCount = &EMG_data[i]->IndexCount[0];
							 ushort* npIndexCount = pIndexCount;

							 pin_ptr<byte> pVertexArray = &EMG_data[i]->VertexArray[0];
							 byte* npVertexArray = pVertexArray;

							 using Runtime::InteropServices::GCHandle;
							 using Runtime::InteropServices::GCHandleType;

							 auto pins = gcnew array<GCHandle>(EMG_data[i]->IndiceArray->Length);
							 for (auto a = 0, i_max = pins->Length; a != i_max; ++a)
								 pins[a] = GCHandle::Alloc(EMG_data[i]->IndiceArray[a], GCHandleType::Pinned);

							 try
							 {
								 auto arrays = gcnew array<ushort*>(pins->Length);
								 for (auto a = 0, i_max = arrays->Length; a != i_max; ++a)
									 arrays[a] = static_cast<ushort*>(pins[a].AddrOfPinnedObject().ToPointer());

								 // pin outer array<ushort*>^
								 const pin_ptr<ushort*> pin = &arrays[0];

								 m_D3DWrap->WrapLoadEMG(sendcount, EMG_data[i]->SubmodelCount, npDDSid, npIndexCount,
									 EMG_data[i]->VertexCount, EMG_data[i]->VertexSize, pin, npVertexArray);
							 }
							 catch (...)
							 {
								 // unpin each contained array<ushort>^
								 for each (GCHandle pin in pins)
									 pin.Free();
							 }

							 sendcount++;
							 delete EMG_data[i];
						 }
					 }
				 }				 
			 }			

			 // "Extract" button.
			 if (!treeView1->Nodes[0]->Checked && !treeView1->Nodes[1]->Checked 
				 && !treeView1->Nodes[2]->Checked)
			  button1->Enabled = false;
			 else
			  button1->Enabled = true;
}
private: System::Void treeView1_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 if (e->Action != TreeViewAction::Unknown)
			 {
				 if (e->Node->Name == "Node1")
				 {
					 
				 }

				 if (e->Node->Parent != nullptr && e->Node->Parent->Name == "Node1")
				 {
					 if (e->Node->Index != e->Node->Parent->LastNode->Index)
					 {
						 auto Path = Path::GetDirectoryName(openFileDialog1->FileName);
						 Path += "\\" + e->Node->Text;

						 auto EMB_data = ReadEMB(Path);
						 pin_ptr<ulong> pDDSsize = &EMB_data->DDSsize[0];
						 ulong* npDDSsize = pDDSsize;

						 using Runtime::InteropServices::GCHandle;
						 using Runtime::InteropServices::GCHandleType;

						 auto pins = gcnew array<GCHandle>(EMB_data->DDSArray->Length);
						 for (auto a = 0, i_max = pins->Length; a != i_max; ++a)
							 pins[a] = GCHandle::Alloc(EMB_data->DDSArray[a], GCHandleType::Pinned);

						 try
						 {
							 auto arrays = gcnew array<byte*>(pins->Length);
							 for (auto a = 0, i_max = arrays->Length; a != i_max; ++a)
								 arrays[a] = static_cast<byte*>(pins[a].AddrOfPinnedObject().ToPointer());

							 // pin outer array<int*>^
							 const pin_ptr<byte*> pin = &arrays[0];

							 m_D3DWrap->WrapLoadDDS(EMB_data->DDScount, npDDSsize, pin);
						 }
						 catch (...)
						 {
							 // unpin each contained array<int>^
							 for each (GCHandle pin in pins)
								 pin.Free();
						 }

						 delete EMB_data;
					 }
				 }
			 }
}
private: System::Void steamToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (steamToolStripMenuItem->Checked)
				 steamToolStripMenuItem->Checked = false;
			 else
				 steamToolStripMenuItem->Checked = true;
}
private: System::Void originStoreToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (originStoreToolStripMenuItem->Checked)
				 originStoreToolStripMenuItem->Checked = false;
			 else
				 originStoreToolStripMenuItem->Checked = true;
}
private: System::Void MergeSubmodelsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (MergeSubmodelsToolStripMenuItem->Checked)
				 MergeSubmodelsToolStripMenuItem->Checked = false;
			 else
				 MergeSubmodelsToolStripMenuItem->Checked = true;
}
private: System::Void replaceSkelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (replaceSkelToolStripMenuItem->Checked)
				 replaceSkelToolStripMenuItem->Checked = false;
			 else
				 replaceSkelToolStripMenuItem->Checked = true;
}
private: System::Void starPoseFixToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (starPoseFixToolStripMenuItem->Checked)
				 starPoseFixToolStripMenuItem->Checked = false;
			 else
				 starPoseFixToolStripMenuItem->Checked = true;
}
private: System::Void refFrametoolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			if (refFrametoolStripMenuItem->Checked)
				refFrametoolStripMenuItem->Checked = false;
			else
				refFrametoolStripMenuItem->Checked = true;
}
private: System::Void TopSplitContainer_SplitterMoved(System::Object^  sender, System::Windows::Forms::SplitterEventArgs^  e) {
	m_D3DWrap->WrapResize(TopSplitContainer->Panel2->Width, TopSplitContainer->Panel2->Height);
}
private: System::Void MainForm_SizeChanged(System::Object^  sender, System::EventArgs^  e) {
	m_D3DWrap->WrapResize(TopSplitContainer->Panel2->Width, TopSplitContainer->Panel2->Height);
}
};
}