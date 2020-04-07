#pragma once

#include "AboutBox.h"
#include "Wrapper.h"
#include "Reader.h"
#include "Writer.h"
#include <filesystem>
#include <msclr/marshal_cppstd.h>

namespace file_sys = std::filesystem;

// ReSharper disable CppRedundantQualifier
// ReSharper disable CppRedundantParentheses
namespace usf4_ce {

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
		System::Windows::Forms::ToolStripDropDownButton^  toolStripDropDownButton3;
		System::Windows::Forms::ToolStripMenuItem^  steamToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  originStoreToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  MergeSubmodelsToolStripMenuItem;
		System::Windows::Forms::ToolStripTextBox^  toolStripTextBox1;
		System::Windows::Forms::ToolStripMenuItem^  replaceSkelToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  starPoseFixToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ refFrametoolStripMenuItem;

		System::Windows::Forms::SplitContainer^  BaseSplitContainer;
		System::Windows::Forms::SplitContainer^  TopSplitContainer;
		System::Windows::Forms::SplitContainer^  BottomSplitContainer;

		System::Windows::Forms::TrackBar^  trackBar1;

		System::Windows::Forms::StatusStrip^ statusStrip1;
		System::Windows::Forms::ToolStrip^ toolStrip1;
		System::Windows::Forms::ToolStripDropDownButton^ toolStripDropDownButton1;
		System::Windows::Forms::ToolStripDropDownButton^ toolStripDropDownButton2;
		System::Windows::Forms::ToolStripMenuItem^ aboutToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;

		System::Windows::Forms::Timer^ timer1;
		System::Windows::Forms::Button^ button1;
		System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel1;
		System::ComponentModel::IContainer^ components;
		System::Windows::Forms::ContextMenuStrip^ saveEMA_contextMenuStrip;
		System::Windows::Forms::ToolStripMenuItem^ saveAsToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ backupOriginalFileToolStripMenuItem;
		System::Windows::Forms::ContextMenuStrip^ animationContextMenuStrip1;
		System::Windows::Forms::ToolStripMenuItem^ exportDataToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ replaceDataToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ backupEMAToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ deleteToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ saveToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ addAnimationToolStripMenuItem;

		// Double click fix.
		System::Windows::Forms::TreeView^ treeView1; // Comment this.
		//NewTreeView^  treeView1;

	public:
		String^ steam_path = {};
		String^ emo_path = {};
		wrapper^ m_D3DWrap;

		MainForm(): TopSplitContainer()
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//			
			m_D3DWrap = gcnew wrapper();
			m_D3DWrap->init(TopSplitContainer->Panel2->Handle.ToInt32(), TopSplitContainer->Panel2->Width, TopSplitContainer->Panel2->Height);
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

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent()
		{			
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::TreeNode^ treeNode1 = (gcnew System::Windows::Forms::TreeNode(L"Mesh"));
			System::Windows::Forms::TreeNode^ treeNode2 = (gcnew System::Windows::Forms::TreeNode(L"Skins"));
			System::Windows::Forms::TreeNode^ treeNode3 = (gcnew System::Windows::Forms::TreeNode(L"Animations"));
			this->saveEMA_contextMenuStrip = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->addAnimationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->backupOriginalFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->toolStripTextBox1 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->replaceSkelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->starPoseFixToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->refFrametoolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripDropDownButton2 = (gcnew System::Windows::Forms::ToolStripDropDownButton());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->BaseSplitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->TopSplitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->BottomSplitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->animationContextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->exportDataToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->replaceDataToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->backupEMAToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveEMA_contextMenuStrip->SuspendLayout();
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
			this->animationContextMenuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// saveEMA_contextMenuStrip
			// 
			this->saveEMA_contextMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->addAnimationToolStripMenuItem,
					this->saveToolStripMenuItem, this->saveAsToolStripMenuItem, this->backupOriginalFileToolStripMenuItem
			});
			this->saveEMA_contextMenuStrip->Name = L"contextMenuStrip1";
			this->saveEMA_contextMenuStrip->Size = System::Drawing::Size(180, 92);
			this->saveEMA_contextMenuStrip->Closing += gcnew System::Windows::Forms::ToolStripDropDownClosingEventHandler(this, &MainForm::saveAnim_contextMenuStrip_Closing);
			// 
			// addAnimationToolStripMenuItem
			// 
			this->addAnimationToolStripMenuItem->Name = L"addAnimationToolStripMenuItem";
			this->addAnimationToolStripMenuItem->Size = System::Drawing::Size(179, 22);
			this->addAnimationToolStripMenuItem->Text = L"Add Animation";
			this->addAnimationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::addAnimationToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(179, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Visible = false;
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveToolStripMenuItem_Click);
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(179, 22);
			this->saveAsToolStripMenuItem->Text = L"Save As...";
			this->saveAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveAsToolStripMenuItem_Click);
			// 
			// backupOriginalFileToolStripMenuItem
			// 
			this->backupOriginalFileToolStripMenuItem->Checked = true;
			this->backupOriginalFileToolStripMenuItem->CheckOnClick = true;
			this->backupOriginalFileToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->backupOriginalFileToolStripMenuItem->Name = L"backupOriginalFileToolStripMenuItem";
			this->backupOriginalFileToolStripMenuItem->Size = System::Drawing::Size(179, 22);
			this->backupOriginalFileToolStripMenuItem->Text = L"Backup Original File";
			this->backupOriginalFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::backupOriginalFileToolStripMenuItem_Click);
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
					this->originStoreToolStripMenuItem, this->MergeSubmodelsToolStripMenuItem, this->toolStripTextBox1, this->replaceSkelToolStripMenuItem,
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
			this->steamToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->steamToolStripMenuItem->Text = L"Steam folder";
			this->steamToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::steamToolStripMenuItem_Click);
			// 
			// originStoreToolStripMenuItem
			// 
			this->originStoreToolStripMenuItem->Checked = true;
			this->originStoreToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->originStoreToolStripMenuItem->Name = L"originStoreToolStripMenuItem";
			this->originStoreToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->originStoreToolStripMenuItem->Text = L"Origin coord. store";
			this->originStoreToolStripMenuItem->Visible = false;
			this->originStoreToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::originStoreToolStripMenuItem_Click);
			// 
			// MergeSubmodelsToolStripMenuItem
			// 
			this->MergeSubmodelsToolStripMenuItem->Name = L"MergeSubmodelsToolStripMenuItem";
			this->MergeSubmodelsToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->MergeSubmodelsToolStripMenuItem->Text = L"Merge submodels";
			this->MergeSubmodelsToolStripMenuItem->ToolTipText = L"By texture id";
			this->MergeSubmodelsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MergeSubmodelsToolStripMenuItem_Click);
			// 
			// toolStripTextBox1
			// 
			this->toolStripTextBox1->Name = L"toolStripTextBox1";
			this->toolStripTextBox1->Size = System::Drawing::Size(100, 23);
			this->toolStripTextBox1->Text = L"72";
			this->toolStripTextBox1->TextBoxTextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->toolStripTextBox1->ToolTipText = L"Scale";
			// 
			// replaceSkelToolStripMenuItem
			// 
			this->replaceSkelToolStripMenuItem->Name = L"replaceSkelToolStripMenuItem";
			this->replaceSkelToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->replaceSkelToolStripMenuItem->Text = L"Replace skeleton";
			this->replaceSkelToolStripMenuItem->ToolTipText = L"Quick fix for a T-Pose chars, not for a Star-Pose ones";
			this->replaceSkelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::replaceSkelToolStripMenuItem_Click);
			// 
			// starPoseFixToolStripMenuItem
			// 
			this->starPoseFixToolStripMenuItem->Name = L"starPoseFixToolStripMenuItem";
			this->starPoseFixToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->starPoseFixToolStripMenuItem->Text = L"Star-Pose Fix";
			this->starPoseFixToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::starPoseFixToolStripMenuItem_Click);
			// 
			// refFrametoolStripMenuItem
			// 
			this->refFrametoolStripMenuItem->Name = L"refFrametoolStripMenuItem";
			this->refFrametoolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->refFrametoolStripMenuItem->Text = L"Reference Frame";
			this->refFrametoolStripMenuItem->ToolTipText = L"Add Ref. pose frame to animation as \"time 0\"";
			this->refFrametoolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::refFrametoolStripMenuItem_Click);
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
			this->treeView1->Size = System::Drawing::Size(187, 442);
			this->treeView1->TabIndex = 0;
			this->treeView1->AfterCheck += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::treeView1_AfterCheck);
			this->treeView1->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::treeView1_AfterSelect);
			this->treeView1->NodeMouseClick += gcnew System::Windows::Forms::TreeNodeMouseClickEventHandler(this, &MainForm::treeView1_NodeMouseClick);
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
			this->BaseSplitContainer->SplitterDistance = 442;
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
			this->TopSplitContainer->Size = System::Drawing::Size(784, 442);
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
			this->BottomSplitContainer->Size = System::Drawing::Size(784, 69);
			this->BottomSplitContainer->SplitterDistance = 187;
			this->BottomSplitContainer->TabIndex = 0;
			// 
			// trackBar1
			// 
			this->trackBar1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->trackBar1->Enabled = false;
			this->trackBar1->Location = System::Drawing::Point(0, 0);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(593, 69);
			this->trackBar1->TabIndex = 1;
			this->trackBar1->Visible = false;
			// 
			// animationContextMenuStrip1
			// 
			this->animationContextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->exportDataToolStripMenuItem,
					this->replaceDataToolStripMenuItem, this->backupEMAToolStripMenuItem, this->deleteToolStripMenuItem
			});
			this->animationContextMenuStrip1->Name = L"animationContextMenuStrip1";
			this->animationContextMenuStrip1->Size = System::Drawing::Size(152, 92);
			this->animationContextMenuStrip1->Closing += gcnew System::Windows::Forms::ToolStripDropDownClosingEventHandler(this, &MainForm::animationContextMenuStrip1_Closing);
			// 
			// exportDataToolStripMenuItem
			// 
			this->exportDataToolStripMenuItem->Name = L"exportDataToolStripMenuItem";
			this->exportDataToolStripMenuItem->Size = System::Drawing::Size(151, 22);
			this->exportDataToolStripMenuItem->Text = L"Export Binary";
			this->exportDataToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exportDataToolStripMenuItem_Click);
			// 
			// replaceDataToolStripMenuItem
			// 
			this->replaceDataToolStripMenuItem->Name = L"replaceDataToolStripMenuItem";
			this->replaceDataToolStripMenuItem->Size = System::Drawing::Size(151, 22);
			this->replaceDataToolStripMenuItem->Text = L"Replace Binary";
			this->replaceDataToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::replaceDataToolStripMenuItem_Click);
			// 
			// backupEMAToolStripMenuItem
			// 
			this->backupEMAToolStripMenuItem->Name = L"backupEMAToolStripMenuItem";
			this->backupEMAToolStripMenuItem->Size = System::Drawing::Size(151, 22);
			this->backupEMAToolStripMenuItem->Text = L"Backup EMA";
			this->backupEMAToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::backupEMAToolStripMenuItem_Click);
			// 
			// deleteToolStripMenuItem
			// 
			this->deleteToolStripMenuItem->Name = L"deleteToolStripMenuItem";
			this->deleteToolStripMenuItem->Size = System::Drawing::Size(151, 22);
			this->deleteToolStripMenuItem->Text = L"Delete";
			this->deleteToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::deleteToolStripMenuItem_Click);
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
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->SizeChanged += gcnew System::EventHandler(this, &MainForm::MainForm_SizeChanged);
			this->saveEMA_contextMenuStrip->ResumeLayout(false);
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
			this->animationContextMenuStrip1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
			this->toolStripDropDownButton3->DropDown->Closing += gcnew ToolStripDropDownClosingEventHandler(this, &MainForm::contextMenuStrip_Closing);

			try {
				auto rk = Registry::CurrentUser->OpenSubKey("Software\\Valve\\Steam", false);
				steam_path = rk->GetValue("SteamPath")->ToString();
				steam_path = steam_path->Replace("/", "\\");
				steam_path += "\\SteamApps\\common\\Super Street Fighter IV - Arcade Edition\\resource\\battle\\chara";
				rk->Close();
			}
			catch (...) {}

			auto config = gcnew Xml::XmlDocument;

			const auto file = Directory::GetCurrentDirectory() + "\\config.cfg";

			if (File::Exists(file))
			{
				config->Load(file);
				auto root_elem = config->DocumentElement;
				auto d = root_elem->ChildNodes;

				for(auto i = 0; i < d->Count; i++)
				{
					if(d[i]->Name == "steam" && d[i]->InnerText != steamToolStripMenuItem->Checked.ToString())
					{
						steamToolStripMenuItem->Checked = false;
					}
					else if (d[i]->Name == "merge_submodel" && d[i]->InnerText != MergeSubmodelsToolStripMenuItem->Checked.ToString())
					{
						MergeSubmodelsToolStripMenuItem->Checked = true;
					}
					else if (d[i]->Name == "scale" && d[i]->InnerText != toolStripTextBox1->Text)
					{
						toolStripTextBox1->Text = d[i]->InnerText;
					}
					else if (d[i]->Name == "replace_skeleton" && d[i]->InnerText != replaceSkelToolStripMenuItem->Checked.ToString())
					{
						replaceSkelToolStripMenuItem->Checked = true;
					}
					else if (d[i]->Name == "star_fix" && d[i]->InnerText != starPoseFixToolStripMenuItem->Checked.ToString())
					{
						starPoseFixToolStripMenuItem->Checked = true;
					}
					else if (d[i]->Name == "ref_frame" && d[i]->InnerText != refFrametoolStripMenuItem->Checked.ToString())
					{
						refFrametoolStripMenuItem->Checked = true;
					}
					else if (d[i]->Name == "backup1" && d[i]->InnerText != backupOriginalFileToolStripMenuItem->Checked.ToString())
					{
						backupOriginalFileToolStripMenuItem->Checked = false;
					}
					else if (d[i]->Name == "backup2" && d[i]->InnerText != backupEMAToolStripMenuItem->Checked.ToString())
					{
						backupEMAToolStripMenuItem->Checked = true;
					}
				}
			}
		}

		System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
			auto config = gcnew Xml::XmlDocument;

			//auto xmlDeclaration = config->CreateXmlDeclaration("1.0", "UTF-8", nullptr);
			auto root = config->DocumentElement;
			//config->InsertBefore(xmlDeclaration, root);

			auto root_elem = config->CreateElement(String::Empty, "settings", String::Empty);
			config->AppendChild(root_elem);

			auto setting1 = config->CreateElement(String::Empty, "steam", String::Empty);
			setting1->AppendChild(config->CreateTextNode(steamToolStripMenuItem->Checked.ToString()));
			root_elem->AppendChild(setting1);

			auto setting2 = config->CreateElement(String::Empty, "merge_submodel", String::Empty);
			setting2->AppendChild(config->CreateTextNode(MergeSubmodelsToolStripMenuItem->Checked.ToString()));
			root_elem->AppendChild(setting2);

			auto setting3 = config->CreateElement(String::Empty, "scale", String::Empty);
			setting3->AppendChild(config->CreateTextNode(toolStripTextBox1->Text));
			root_elem->AppendChild(setting3);

			auto setting4 = config->CreateElement(String::Empty, "replace_skeleton", String::Empty);
			setting4->AppendChild(config->CreateTextNode(replaceSkelToolStripMenuItem->Checked.ToString()));
			root_elem->AppendChild(setting4);

			auto setting5 = config->CreateElement(String::Empty, "star_fix", String::Empty);
			setting5->AppendChild(config->CreateTextNode(starPoseFixToolStripMenuItem->Checked.ToString()));
			root_elem->AppendChild(setting5);

			auto setting6 = config->CreateElement(String::Empty, "ref_frame", String::Empty);
			setting6->AppendChild(config->CreateTextNode(refFrametoolStripMenuItem->Checked.ToString()));
			root_elem->AppendChild(setting6);

			auto setting7 = config->CreateElement(String::Empty, "backup1", String::Empty);
			setting7->AppendChild(config->CreateTextNode(backupOriginalFileToolStripMenuItem->Checked.ToString()));
			root_elem->AppendChild(setting7);

			auto setting8 = config->CreateElement(String::Empty, "backup2", String::Empty);
			setting8->AppendChild(config->CreateTextNode(backupEMAToolStripMenuItem->Checked.ToString()));
			root_elem->AppendChild(setting8);

			config->Save(Directory::GetCurrentDirectory() + "\\config.cfg");
		}

		System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			Application::Exit();
		}
		System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			auto AboutBox1 = gcnew AboutBox;
			AboutBox1->ShowDialog();
		}
		System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 m_D3DWrap->render();
		}
		System::Void TopSplitContainer_Panel2_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 m_D3DWrap->on_mouse_move(short(Control::MousePosition.X), short(Control::MousePosition.Y), e->Button == System::Windows::Forms::MouseButtons::Right);
		}
		System::Void TopSplitContainer_Panel2_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 m_D3DWrap->on_mouse_button_up();
		}
		System::Void TopSplitContainer_Panel2_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 m_D3DWrap->on_mouse_button_down(short(Control::MousePosition.X), short(Control::MousePosition.Y));
		}

		System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			auto openFileDialog1 = gcnew OpenFileDialog();
			openFileDialog1->RestoreDirectory = true;
			if (steamToolStripMenuItem->Checked && steam_path != String::Empty)
			{
				openFileDialog1->InitialDirectory = steam_path;
			}		
			openFileDialog1->Filter = "SF4 model|*obj.emo";
			openFileDialog1->Title = "Select model";

			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				treeView1->Nodes[0]->Nodes->Clear();
				treeView1->Nodes[1]->Nodes->Clear();
				treeView1->Nodes[2]->Nodes->Clear();

				emo_path = openFileDialog1->FileName;

				auto fs = File::OpenRead(emo_path);
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
					const ushort emg_count = br->ReadInt16(); 

					//==================================================================

					fs->Position = 32 + 4; // // Position of "offsets list" of EMG names offsets.
					unsigned int emg_names_offsets_offset = br->ReadInt32(); // Reading.
					fs->Position = 32 + emg_names_offsets_offset; // // Position of "offsets list" of EMG names.
					auto emg_names_offsets = gcnew array<unsigned int>(emg_count); // Reading.
					for (auto i = 0; i < emg_count; i++)
					{
						emg_names_offsets[i] = br->ReadUInt32();
					}

					auto emg_names = gcnew array<String^>(emg_count);
					for (auto i = 0; i < emg_count; i++)
					{
						fs->Position = 32 + emg_names_offsets[i];

						auto sb = gcnew StringBuilder;
						while (br->ReadChar() != 0)
						{
							fs->Position--;
							sb->Append(br->ReadChar());
						}							

						emg_names[i] = sb->ToString();
					}		

					//==================================================================

					fs->Position = 32 + 8; // Position of "offsets list" of every EMG.

					auto emg_offsets = gcnew array<unsigned int>(emg_count);
					auto emg_data = gcnew array<emg_struct^>(emg_count);

					m_D3DWrap->create_buffers(emg_count); // Creating array of buffers.

					for (ushort i = 0; i < emg_count; i++)
					{
						emg_offsets[i] = br->ReadInt32(); // Filling array with list.
						emg_data[i] = read_emg(openFileDialog1->FileName, 32 + emg_offsets[i] + 16); // Filling array with data about each EMG.

						pin_ptr<byte> pDDSid = &emg_data[i]->dds_id[0];
						byte* npDDSid = pDDSid;

						pin_ptr<ushort> pIndexCount = &emg_data[i]->index_count[0];
						ushort* npIndexCount = pIndexCount;

						pin_ptr<byte> pVertexArray = &emg_data[i]->vertex_array[0];
						byte* npVertexArray = pVertexArray;

						using Runtime::InteropServices::GCHandle;
						using Runtime::InteropServices::GCHandleType;

						auto pins = gcnew array<GCHandle>(emg_data[i]->indices_array->Length);
						for (auto a = 0, i_max = pins->Length; a != i_max; a++)
							pins[a] = GCHandle::Alloc(emg_data[i]->indices_array[a], GCHandleType::Pinned);

						try
						{
							auto arrays = gcnew array<ushort*>(pins->Length);
							for (auto a = 0, i_max = arrays->Length; a != i_max; a++)
								arrays[a] = static_cast<ushort*>(pins[a].AddrOfPinnedObject().ToPointer());

							// pin outer array<ushort*>^
							const pin_ptr<ushort*> pin = &arrays[0];

							m_D3DWrap->load_emg(i, emg_data[i]->submodel_count, npDDSid, npIndexCount,
								emg_data[i]->vertex_count, emg_data[i]->vertex_size, pin, npVertexArray);
						}
						catch (...)
						{
							// unpin each contained array<ushort>^
							for each (GCHandle pin in pins)
								pin.Free();
						}

						delete emg_data[i];
						treeView1->Nodes[0]->Nodes->Add(gcnew TreeNode((i + 1) + ". " + emg_names[i]));
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

							auto emb_data = read_emb(path + "\\" + name + "_01.col.emb");

							pin_ptr<ulong> pDDSsize = &emb_data->dds_size[0];
							ulong* npDDSsize = pDDSsize;

							using Runtime::InteropServices::GCHandle;
							using Runtime::InteropServices::GCHandleType;

							auto pins = gcnew array<GCHandle>(emb_data->dds_array->Length);
							for (auto i = 0, i_max = pins->Length; i != i_max; ++i)
								pins[i] = GCHandle::Alloc(emb_data->dds_array[i], GCHandleType::Pinned);

							try
							{
								auto arrays = gcnew array<byte*>(pins->Length);
								for (auto i = 0, i_max = arrays->Length; i != i_max; ++i)
									arrays[i] = static_cast<byte*>(pins[i].AddrOfPinnedObject().ToPointer());

								// pin outer array<int*>^
								const pin_ptr<byte*> pin = &arrays[0];

								m_D3DWrap->load_dds(emb_data->dds_count, npDDSsize, pin);
							}
							catch (...)
							{
								// unpin each contained array<int>^
								for each (GCHandle pin in pins)
									pin.Free();
							}

							delete emb_data;
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
					//const auto name2 = name->TrimEnd(trim_chars2);

					auto files = Directory::GetFiles(path);
					for(auto index = 0; index < files->Length; index++)
					{
						auto file = files[index];
						if(file->EndsWith(".ema"))
						{
							open_anim_file(path, getFileName(file, true));
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

		static String^ getFileName(String^ file_path, const bool with_extension)
		{
			// Create a Path object from File Path
			const file_sys::path path_obj(msclr::interop::marshal_as<std::string>(file_path));

			// Check if file name is required without extension
			if (with_extension == false)
			{
				// Check if file has stem i.e. filename without extension
				if (path_obj.has_stem())
				{
					// return the stem (file name without extension) from path object
					return msclr::interop::marshal_as<String^>(path_obj.stem().string());
				}
				return "";
			}

			// return the file name with extension from path object
			return msclr::interop::marshal_as<String^>((path_obj.filename().string()));
		}

		Void open_anim_file(String^ path, String^ name)
		{
			if (!File::Exists(path + "\\" + name))
			{
				//
			}
			else
			{
				auto fs = File::OpenRead(path + "\\" + name);
				auto br = gcnew BinaryReader(fs);

				if (String::Compare(Encoding::UTF8->GetString(br->ReadBytes(4)), "#EMA", true) == 0) // If 0, continue reading.
				{
					ema_struct^ ema_data = {};
					try
					{
						ema_data = read_ema(path + "\\" + name);

						treeView1->Nodes[2]->Checked = true;

						treeView1->Nodes[2]->Nodes->Add(gcnew TreeNode(name)); // Animation file
						treeView1->Nodes[2]->LastNode->ContextMenuStrip = saveEMA_contextMenuStrip;
						treeView1->Nodes[2]->LastNode->Checked = true;
						treeView1->Nodes[2]->LastNode->Tag = path + "\\" + name;

						for (ushort i = 0; i < ema_data->header->animation_count; i++) // Animations in file
						{
							const auto animation_name = gcnew String(ema_data->animation[i]->name);
							treeView1->Nodes[2]->LastNode->Nodes->Add(gcnew TreeNode(i + 1 + ". " + animation_name));
							treeView1->Nodes[2]->LastNode->Nodes[i]->Checked = true;
							treeView1->Nodes[2]->LastNode->Nodes[i]->ContextMenuStrip = animationContextMenuStrip1;
							treeView1->Nodes[2]->LastNode->Nodes[i]->Tag = animation_name;
						}

						delete ema_data;
						treeView1->Nodes[2]->LastNode->Expand();
						treeView1->Nodes[2]->Expand();
					}
					catch (...)
					{
						delete ema_data;
					}
				}

				br->Close();
				fs->Close();
			}
		}

		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			 treeView1->Enabled = false;

			 array<Char>^ trim_chars = { 'o', 'b', 'e', 'm', 'j', '.' };
			 auto path = Path::GetDirectoryName(emo_path);
			 auto name = Path::GetFileName(emo_path)->TrimEnd(trim_chars);

			 if (treeView1->Nodes[0]->Checked == true) // mesh
			 {
				 // SMD exporter
				 auto saveFileDialog1 = gcnew SaveFileDialog();
				 saveFileDialog1->FileName = name;
				 saveFileDialog1->Filter = "SMD model|*.smd";
				 saveFileDialog1->RestoreDirectory = true;

				 if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 auto fs = File::OpenRead(emo_path);
					 auto br = gcnew BinaryReader(fs);
					 auto sw = gcnew StreamWriter(saveFileDialog1->FileName);

					 auto scale = ushort::Parse(toolStripTextBox1->Text);

					 sw->WriteLine("version 1");

					 //==================================================================
					 // Nodes tree.
					 //==================================================================

					 auto skeleton_data = read_skeleton(emo_path, 16);

					 sw->WriteLine("nodes");					 

					 for (ushort i = 0; i < skeleton_data->nodes_count; i++) // 
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
					 if (replaceSkelToolStripMenuItem->Checked == true) // If animation is not selected, exporting original skeleton.
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

					 for (ushort i = 0; i < skeleton_data->nodes_count; i++) // 
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
							 auto node_name = skeleton_data->node_name[i]; // Name of current node.	

							 array<Char>^ trim_chars2 = { '_', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
							 auto name2 = name->TrimEnd(trim_chars2);
							 auto skeleton_data2 = read_skeleton(path + "\\" + name2 + ".obj.ema", 12);

							 for (ushort nodes = 0; nodes < skeleton_data2->nodes_count; nodes++) // Replacing values of current node with values of reference skeleton from animation.
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

									 if (starPoseFixToolStripMenuItem->Checked == true)
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
							 + (-ry).ToString("F6", en_us) );
					 }
					 delete skeleton_data;
					 sw->WriteLine("end");

					 //==================================================================
					 // Triangles
					 //==================================================================
					 fs->Position = 32; // Skipping 32 bytes to position about EMG ammount.
					 ushort emg_count = br->ReadInt16();
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
							 for (auto current_submodel = 0; current_submodel < emg_data[current_emg]->submodel_count; current_submodel++)
							 {
								 for (ushort i = 0; i < emg_data[current_emg]->index_count[current_submodel] - 2; i++)
								 {
									 auto en_us = gcnew CultureInfo("en-US");

									 int a, b, c;

									 String^ texture;
									 if (MergeSubmodelsToolStripMenuItem->Checked)
										 texture = name + "_" + (emg_data[current_emg]->dds_id[current_submodel] + 1) + ".dds";
									 else
										 texture = current_emg + "_" + name + "_" + (emg_data[current_emg]->dds_id[current_submodel] + 1) + ".dds";

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
													 + (-*reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray)) * scale).ToString("F6", en_us) + " "
													 + (*reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray) + 4) * scale).ToString("F6", en_us) + " "
													 + (*reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray) + 8) * scale).ToString("F6", en_us) + " "
													 // NormX NormY NormZ
													 + (*reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray) + 12)).ToString("F6", en_us) + " "
													 + (*reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray) + 16)).ToString("F6", en_us) + " "
													 + (*reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray) + 20)).ToString("F6", en_us) + " "
													 // U V
													 + (*reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray) + 24)).ToString("F6", en_us) + " "
													 + (-*reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray) + 28)).ToString("F6", en_us) + " ");
												 
												 byte BoneID[4];
												 for (byte num = 0; num < 4; num++)
													 BoneID[num] = *reinterpret_cast<byte*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray) + 48 + num);
												 float weight[3];
												 for (byte num = 0; num < 3; num++)
													 weight[num] = *reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray) + 52 + (num * 4));

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
													 + (-*reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray)) * scale).ToString("F6", en_us) + " "
													 + (*reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray) + 4) * scale).ToString("F6", en_us) + " "
													 + (*reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray) + 8) * scale).ToString("F6", en_us) + " "
													 // NormX NormY NormZ
													 + (*reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray)  + 12)).ToString("F6", en_us) + " "
													 + (*reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray) + 16)).ToString("F6", en_us) + " "
													 + (*reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray) + 20)).ToString("F6", en_us) + " "
													 // U V
													 + (*reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray) + 24)).ToString("F6", en_us) + " "
													 + (-*reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray) + 28)).ToString("F6", en_us) + " ");

												 byte BoneID[4];
												 for (byte num = 0; num < 4; num++)
													 BoneID[num] = *reinterpret_cast<byte*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray) + 48 + num);
												 float weight[3];
												 for (byte num = 0; num < 3; num++)
													 weight[num] = *reinterpret_cast<float*>(index * emg_data[current_emg]->vertex_size + int(pVertexArray) + 52 + (num * 4));

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
							 auto emb_data = read_emb(temp);

							 auto temp_name = treeView1->Nodes[1]->Nodes[node]->Text;
							 auto name2 = temp_name->Split('.');
							 auto name_arr = name2[0]->Split('_');

							 for (auto i = 0; i < emb_data->dds_count; i++)
							 {
								 auto output_path = Path::GetDirectoryName(saveFileDialog1->FileName);
								 auto fs = gcnew FileStream(output_path + "\\" + name_arr[0] + "_" + name_arr[1] + "_" + (i+1) + "_" + name_arr[2] + ".dds", FileMode::Create, FileAccess::ReadWrite);
								 auto bw = gcnew BinaryWriter(fs);

								 for (ulong a = 0; a < emb_data->dds_size[i]; a++)
									 bw->Write(emb_data->dds_array[i][a]);

								 bw->Close();
								 fs->Close();
							 }

							 delete emb_data;
						 }
					 }					 

					 // Normal map.
					 if (treeView1->Nodes[1]->Nodes[treeView1->Nodes[1]->LastNode->Index]->Checked)
					 {
						 auto emb_data = read_emb(path + "\\" + name + ".nml.emb");

						 for (auto i = 0; i < emb_data->dds_count; i++)
						 {
							 auto output_path = Path::GetDirectoryName(saveFileDialog1->FileName);
							 auto fs = gcnew FileStream(output_path + "\\" + name + "_" + i + ".nml.dds", FileMode::Create, FileAccess::ReadWrite);
							 auto bw = gcnew BinaryWriter(fs);

							 for (ulong a = 0; a < emb_data->dds_size[i]; a++)
								 bw->Write(emb_data->dds_array[i][a]);

							 bw->Close();
							 fs->Close();
						 }

						 delete emb_data;
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
					 auto anim_files_enum = treeView1->Nodes[2]->Nodes->GetEnumerator();

					 while (anim_files_enum->MoveNext())
					 {
						 auto file_node = safe_cast<TreeNode^>(anim_files_enum->Current);
						 if (file_node->Checked) // *.*.ema file
						 {
							 auto my_enum = treeView1->Nodes[2]->Nodes[file_node->Index]->Nodes->GetEnumerator();

							 auto anim_name = gcnew String(path + "\\" + file_node->Text);

							 while (my_enum->MoveNext())
							 {
								 auto tree_node = safe_cast<TreeNode^>(my_enum->Current);
								 if (tree_node->Checked) // Animation in *.*.ema file
								 {
									 m_D3DWrap->setup_ema(anim_name, 0);

									 auto output_path = Path::GetDirectoryName(saveFileDialog1->FileName);

									 Directory::CreateDirectory(output_path + "\\" + file_node->Text);

									 auto sw = gcnew StreamWriter(output_path + "\\" + file_node->Text + "\\" + tree_node->Text + ".smd");

									 auto en_us = gcnew CultureInfo("en-US");

									 auto scale = ushort::Parse(toolStripTextBox1->Text);

									 sw->WriteLine("version 1");

									 //==================================================================
									 // Nodes tree.
									 //==================================================================					 

									 auto skeleton_data = read_skeleton(path + "\\" + file_node->Text, 12);

									 sw->WriteLine("nodes");

									 for (ushort i = 0; i < skeleton_data->nodes_count; i++) // 
									 {
										 auto node_name = skeleton_data->node_name[i];
										 sw->WriteLine(i + " " + "\"" + node_name + "\"" + " " + skeleton_data->parent_node_array[i]); //" \"root\"  child+1
									 }

									 sw->WriteLine("end");

									 //==================================================================
									 // Nodes position.
									 //==================================================================

									 sw->WriteLine("skeleton");

									 auto ema_data = read_ema(path + "\\" + file_node->Text);

									 auto animation_name = gcnew String(ema_data->animation[tree_node->Index]->name);
									 int duration = ema_data->animation[tree_node->Index]->duration;

									 float structure[500][6];
									 std::string names[500];

									 auto RLegRoot = gcnew String("");
									 auto LLegRoot = gcnew String("");
									 auto LArmRoot = gcnew String("");
									 auto RArmRoot = gcnew String("");

									 // Reference frame.
									 m_D3DWrap->update_ema(structure, names, "ref", 0);

									 if (refFrametoolStripMenuItem->Checked == true)
										sw->WriteLine("time 0");

									 for (auto i = 0; i < skeleton_data->nodes_count; i++)
									 {
										 auto name_clr = gcnew String(names[i].c_str());

										 if (i == 0)
										 {
											 if (refFrametoolStripMenuItem->Checked == true)
												 sw->WriteLine("0 0 0 0 0 0 0"); //1.570796 3.141592
										 }
										 else if (i != 0)
										 {
											 if (refFrametoolStripMenuItem->Checked == true)
											 {
												 sw->Write(i + " " + (-structure[i][0] * scale).ToString("F6", en_us) + " " + (structure[i][1] * scale).ToString("F6", en_us) + " " + (structure[i][2] * scale).ToString("F6", en_us) + " ");
												 sw->WriteLine(structure[i][3].ToString("F6", en_us) + " " + (-structure[i][4]).ToString("F6", en_us) + " " + (-structure[i][5]).ToString("F6", en_us));
											 }
											 else
											 {
												 auto temp = i + " " + (-structure[i][0] * scale).ToString("F6", en_us) + " " + (structure[i][1] * scale).ToString("F6", en_us) + " " + (structure[i][2] * scale).ToString("F6", en_us) + " ";
												 temp += structure[i][3].ToString("F6", en_us) + " " + (-structure[i][4]).ToString("F6", en_us) + " " + (-structure[i][5]).ToString("F6", en_us);
												 if (name_clr == "RLegRoot")
													 RLegRoot = temp;
												 else if (name_clr == "LLegRoot")
													 LLegRoot = temp;
												 else if (name_clr == "LArmRoot")
													 LArmRoot = temp;
												 else if (name_clr == "RArmRoot")
													 RArmRoot = temp;
											 }
										 }
									 }

									 // Actual animation.
									 for (ushort time = 0; time < duration; time++)
									 {
										 auto ref_frame = 0;
										 if (refFrametoolStripMenuItem->Checked == true)
											 ref_frame = 1;

										 sw->WriteLine("time " + (time + ref_frame));
										 m_D3DWrap->update_ema(structure, names, animation_name, time);
										 for (auto i = 0; i < skeleton_data->nodes_count; i++)
										 {
											 auto name_clr = gcnew String(names[i].c_str());

											 if (!name_clr->Equals("camera") && i == 0 && time == 0)
												 sw->WriteLine("0 0 0 0 0 0 0"); //1.570796 3.141592
											 else if (name_clr->Equals("camera") || i != 0)
											 {
												 if (time != 0 && (name_clr == "RLegRoot" || name_clr == "LLegRoot" || name_clr == "LArmRoot" || name_clr == "RArmRoot"))
												 { /*Empty*/}
												 else
												 {
													 if (name_clr == "RLegRoot" && refFrametoolStripMenuItem->Checked != true)
														 sw->WriteLine(RLegRoot);
													 else if (name_clr == "LLegRoot" && refFrametoolStripMenuItem->Checked != true)
														 sw->WriteLine(LLegRoot);
													 else if (name_clr == "LArmRoot" && refFrametoolStripMenuItem->Checked != true)
														 sw->WriteLine(LArmRoot);
													 else if (name_clr == "RArmRoot" && refFrametoolStripMenuItem->Checked != true)
														 sw->WriteLine(RArmRoot);
													 else
													 {
														 sw->Write(i + " " + (-structure[i][0] * scale).ToString("F6", en_us) + " " + (structure[i][1] * scale).ToString("F6", en_us) + " " + (structure[i][2] * scale).ToString("F6", en_us) + " ");
														 sw->WriteLine(structure[i][3].ToString("F6", en_us) + " " + (-structure[i][4]).ToString("F6", en_us) + " " + (-structure[i][5]).ToString("F6", en_us));
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
						 }
					 }

					 MessageBox::Show("Animations extracted", "Done", MessageBoxButtons::OK);
				 }
			 }

			 treeView1->Enabled = true;
		}

		// Updates all child tree nodes recursively.
		void check_all_child_nodes(TreeNode^ treeNode, bool nodeChecked)
		{
			auto myEnum = treeNode->Nodes->GetEnumerator();
			while (myEnum->MoveNext())
			{
				const auto node = safe_cast<TreeNode^>(myEnum->Current);
				node->Checked = nodeChecked;
				if (node->Nodes->Count > 0)
				{
					// If the current node has child nodes, call the CheckAllChildsNodes method recursively.
					this->check_all_child_nodes(node, nodeChecked);
				}
			}
		}

		static void check_parent(TreeNode^ treeNode)
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
					check_parent(treeNode->Parent);
				}
				else
				{
					treeNode->Parent->Checked = true;
					check_parent(treeNode->Parent);
				}
			}
		}

		System::Void treeView1_AfterCheck(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 //==================================================================
			 treeView1->BeginUpdate();
			 if (e->Action != TreeViewAction::Unknown)
			 {
				 if (e->Node->Nodes->Count > 0)
				 {
					 /* Calls the CheckAllChildNodes method, passing in the current
						 Checked value of the TreeNode whose checked state changed. */
					 this->check_all_child_nodes(e->Node, e->Node->Checked);
				 }

				 check_parent(e->Node);

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
						 auto fs = File::OpenRead(emo_path);
						 auto br = gcnew BinaryReader(fs);

						 fs->Position = 32; // Skipping 32 bytes to position about EMG ammount.
						 ushort emg_count = br->ReadInt16();
						 fs->Position = 32 + 8; // Position of "offsets list" of every EMG.

						 auto emg_offsets = gcnew array<unsigned int>(emg_count);
						 auto emg_data = gcnew array<emg_struct^>(emg_count);

						 m_D3DWrap->create_buffers(emg_count); // Creating array of buffers.

						 for (byte i = 0; i < emg_count; i++)
						 {
							 emg_offsets[i] = br->ReadInt32(); // Filling array with list.
							 emg_data[i] = read_emg(emo_path, 32 + emg_offsets[i] + 16); // Filling array with data about each EMG.

							 pin_ptr<byte> pDDSid = &emg_data[i]->dds_id[0];
							 byte* npDDSid = pDDSid;

							 pin_ptr<ushort> pIndexCount = &emg_data[i]->index_count[0];
							 ushort* npIndexCount = pIndexCount;

							 pin_ptr<byte> pVertexArray = &emg_data[i]->vertex_array[0];
							 byte* npVertexArray = pVertexArray;

							 using Runtime::InteropServices::GCHandle;
							 using Runtime::InteropServices::GCHandleType;

							 auto pins = gcnew array<GCHandle>(emg_data[i]->indices_array->Length);
							 for (auto a = 0, i_max = pins->Length; a != i_max; ++a)
								 pins[a] = GCHandle::Alloc(emg_data[i]->indices_array[a], GCHandleType::Pinned);

							 try
							 {
								 auto arrays = gcnew array<ushort*>(pins->Length);
								 for (auto a = 0, i_max = arrays->Length; a != i_max; ++a)
									 arrays[a] = static_cast<ushort*>(pins[a].AddrOfPinnedObject().ToPointer());

								 // pin outer array<ushort*>^
								 const pin_ptr<ushort*> pin = &arrays[0];

								 m_D3DWrap->load_emg(i, emg_data[i]->submodel_count, npDDSid, npIndexCount,
									 emg_data[i]->vertex_count, emg_data[i]->vertex_size, pin, npVertexArray);
							 }
							 catch (...)
							 {
								 // unpin each contained array<ushort>^
								 for each (GCHandle pin in pins)
									 pin.Free();
							 }

							 delete emg_data[i];
						 }
					 }
					 else // Remove full model.
					 {
						 m_D3DWrap->create_buffers(0);
					 }
				 }

				 // Show parts of model
				 if (e->Node->Parent != nullptr && e->Node->Parent->Name == "Node0")
				 {
					 const auto fs = File::OpenRead(emo_path);
					 auto br = gcnew BinaryReader(fs);

					 fs->Position = 32; // Skipping 32 bytes to position about EMG ammount.
					 ushort emg_count = br->ReadInt16();
					 fs->Position = 32 + 8; // Position of "offsets list" of every EMG.

					 auto emg_offsets = gcnew array<int>(emg_count);
					 auto emg_data = gcnew array<emg_struct^>(emg_count);
					 
					 // Counting amount of buffers, creating array of checks.
					 ushort buffer_count = 0;
					 auto arr = gcnew array<bool>(emg_count);
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

					 m_D3DWrap->create_buffers(buffer_count); // Creating array of buffers.

					 // Filling arrays simmilar to checks.
					 auto sendcount = 0;
					 for (byte i = 0; i < emg_count; i++)
					 {
						 emg_offsets[i] = br->ReadInt32(); // Filling array with list.
						 
						 if (arr[i] == true)
						 {
							 emg_data[i] = read_emg(emo_path, 32 + emg_offsets[i] + 16); // Filling array with data about each EMG.

							 pin_ptr<byte> pDDSid = &emg_data[i]->dds_id[0];
							 byte* npDDSid = pDDSid;

							 pin_ptr<ushort> pIndexCount = &emg_data[i]->index_count[0];
							 ushort* npIndexCount = pIndexCount;

							 pin_ptr<byte> pVertexArray = &emg_data[i]->vertex_array[0];
							 byte* npVertexArray = pVertexArray;

							 using Runtime::InteropServices::GCHandle;
							 using Runtime::InteropServices::GCHandleType;

							 auto pins = gcnew array<GCHandle>(emg_data[i]->indices_array->Length);
							 for (auto a = 0, i_max = pins->Length; a != i_max; ++a)
								 pins[a] = GCHandle::Alloc(emg_data[i]->indices_array[a], GCHandleType::Pinned);

							 try
							 {
								 auto arrays = gcnew array<ushort*>(pins->Length);
								 for (auto a = 0, i_max = arrays->Length; a != i_max; ++a)
									 arrays[a] = static_cast<ushort*>(pins[a].AddrOfPinnedObject().ToPointer());

								 // pin outer array<ushort*>^
								 const pin_ptr<ushort*> pin = &arrays[0];

								 m_D3DWrap->load_emg(sendcount, emg_data[i]->submodel_count, npDDSid, npIndexCount,
									 emg_data[i]->vertex_count, emg_data[i]->vertex_size, pin, npVertexArray);
							 }
							 catch (...)
							 {
								 // unpin each contained array<ushort>^
								 for each (GCHandle pin in pins)
									 pin.Free();
							 }

							 sendcount++;
							 delete emg_data[i];
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

		System::Void treeView1_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 /*if (e->Action != TreeViewAction::Unknown)
			 {*/
				 if (e->Node->Name == "Node1")
				 {
					 
				 }

				 if (e->Node->Parent != nullptr && e->Node->Parent->Name == "Node1")
				 {
					 if (e->Node->Index != e->Node->Parent->LastNode->Index)
					 {
						 auto path = Path::GetDirectoryName(emo_path);
						 path += "\\" + e->Node->Text;

						 auto EMB_data = read_emb(path);
						 pin_ptr<ulong> pDDSsize = &EMB_data->dds_size[0];
						 ulong* npDDSsize = pDDSsize;

						 using Runtime::InteropServices::GCHandle;
						 using Runtime::InteropServices::GCHandleType;

						 auto pins = gcnew array<GCHandle>(EMB_data->dds_array->Length);
						 for (auto a = 0, i_max = pins->Length; a != i_max; ++a)
							 pins[a] = GCHandle::Alloc(EMB_data->dds_array[a], GCHandleType::Pinned);

						 try
						 {
							 auto arrays = gcnew array<byte*>(pins->Length);
							 for (auto a = 0, i_max = arrays->Length; a != i_max; ++a)
								 arrays[a] = static_cast<byte*>(pins[a].AddrOfPinnedObject().ToPointer());

							 // pin outer array<int*>^
							 const pin_ptr<byte*> pin = &arrays[0];

							 m_D3DWrap->load_dds(EMB_data->dds_count, npDDSsize, pin);
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
			 /*}*/
		}

		System::Void steamToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (steamToolStripMenuItem->Checked)
				 steamToolStripMenuItem->Checked = false;
			 else
				 steamToolStripMenuItem->Checked = true;
		}
		System::Void originStoreToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (originStoreToolStripMenuItem->Checked)
				 originStoreToolStripMenuItem->Checked = false;
			 else
				 originStoreToolStripMenuItem->Checked = true;
		}
		System::Void MergeSubmodelsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (MergeSubmodelsToolStripMenuItem->Checked)
				 MergeSubmodelsToolStripMenuItem->Checked = false;
			 else
				 MergeSubmodelsToolStripMenuItem->Checked = true;
		}
		System::Void replaceSkelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (replaceSkelToolStripMenuItem->Checked)
				 replaceSkelToolStripMenuItem->Checked = false;
			 else
				 replaceSkelToolStripMenuItem->Checked = true;
		}
		System::Void starPoseFixToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (starPoseFixToolStripMenuItem->Checked)
				 starPoseFixToolStripMenuItem->Checked = false;
			 else
				 starPoseFixToolStripMenuItem->Checked = true;
		}
		System::Void refFrametoolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			if (refFrametoolStripMenuItem->Checked)
				refFrametoolStripMenuItem->Checked = false;
			else
				refFrametoolStripMenuItem->Checked = true;
		}
		System::Void contextMenuStrip_Closing(System::Object^ sender, System::Windows::Forms::ToolStripDropDownClosingEventArgs^ e)
		{
			if (e->CloseReason == ToolStripDropDownCloseReason::ItemClicked)
				e->Cancel = true;
		}

		System::Void TopSplitContainer_SplitterMoved(System::Object^  sender, System::Windows::Forms::SplitterEventArgs^  e) {
			m_D3DWrap->resize(TopSplitContainer->Panel2->Width, TopSplitContainer->Panel2->Height);
		}
		System::Void MainForm_SizeChanged(System::Object^  sender, System::EventArgs^  e) {
			m_D3DWrap->resize(TopSplitContainer->Panel2->Width, TopSplitContainer->Panel2->Height);
		}

		TreeNode^ _currentNode = gcnew TreeNode();
		System::Void treeView1_NodeMouseClick(System::Object^ sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^ e) {
			_currentNode = e->Node;
			treeView1->SelectedNode = _currentNode;
		}

		[Serializable]
		ref struct anim_struct sealed
		{
			UINT32 struct_version = 1;

			String^ name;
			UINT16 duration;
			UINT16 cmd_offset_count;
			UINT32 unknown;

			array<ema_animation_node^>^ node;
			array<float>^ values;
		};

		System::Void addAnimationToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			saveEMA_contextMenuStrip->Close();

			auto openFileDialog1 = gcnew OpenFileDialog();
			if (steamToolStripMenuItem->Checked && steam_path != String::Empty)
			{
				openFileDialog1->InitialDirectory = steam_path;
			}
			openFileDialog1->RestoreDirectory = true;
			openFileDialog1->FileName = "";
			openFileDialog1->Filter = "Animation Data File|*.sf4anim";
			openFileDialog1->Title = "Select animation";

			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				if (backupOriginalFileToolStripMenuItem->Checked)
				{
					auto string_array = _currentNode->Tag->ToString()->Split('\\');
					const auto path = Path::GetDirectoryName(_currentNode->Tag->ToString());
					System::DateTime^ now = System::DateTime::Now;
					String^ backup_path = {};
					backup_path += (path + "\\Backup\\" + now->Day + "." + now->Month + "-" + now->Hour + "." + now->Minute + "." + now->Second + "_" + string_array[string_array->Length - 1]);

					Directory::CreateDirectory(path + "\\Backup\\");
					File::Copy(_currentNode->Tag->ToString(), backup_path, true);
				}

				auto fs = gcnew FileStream(openFileDialog1->FileName, FileMode::Open);
				auto br = gcnew BinaryReader(fs);

				auto formatter = gcnew Runtime::Serialization::Formatters::Binary::BinaryFormatter();
				const auto stream = gcnew MemoryStream(br->ReadBytes(UINT32(fs->Length)));
				anim_struct^ import_anim;
				try
				{
					import_anim = static_cast<anim_struct^>(formatter->Deserialize(stream));
				}
				catch (...)
				{
					br->Close();
					fs->Close();

					MessageBox::Show("Struct version mismatch.", "Fail", MessageBoxButtons::OK);

					return;
				}

				const auto empty_struct = gcnew anim_struct();
				if (import_anim->struct_version != empty_struct->struct_version)
				{
					br->Close();
					fs->Close();

					MessageBox::Show("Struct version mismatch.\nCurrent version: " + empty_struct->struct_version + "\nFile version: " + import_anim->struct_version, "Fail", MessageBoxButtons::OK);

					return;
				}

				const auto ema_data = read_ema(_currentNode->Tag->ToString());
				const auto skeleton_data = read_ema_skeleton(_currentNode->Tag->ToString());

				for (auto i = 0; i < ema_data->animation->Length; i++)
				{
					if(ema_data->animation[i]->name == Path::GetFileNameWithoutExtension(openFileDialog1->FileName))
					{
						br->Close();
						fs->Close();

						MessageBox::Show("Animation with this name already exits in the EMA.", "Fail", MessageBoxButtons::OK);

						return;
					}
				}

				// Replacing node indexes with a correct one from skeleton
				for (auto i = 0; i < import_anim->node->Length; i++)
				{
					auto node_index = 0;
					for (auto a = 0; a < skeleton_data->names->Length; a++)
					{
						if (skeleton_data->names[a] == import_anim->node[i]->name)
							node_index = a;
					}

					import_anim->node[i]->index = node_index;
				}

				ema_data->header->animation_count = ema_data->animation->Length + 1;
				auto animation_array = gcnew array<ema_animation^>(ema_data->header->animation_count);
				for(auto i = 0; i < ema_data->animation->Length; i++)
				{
					animation_array[i] = ema_data->animation[i];
				}
				ema_data->animation = animation_array;

				const auto last_index = animation_array->Length - 1;
				animation_array[last_index] = gcnew ema_animation();

				ema_data->animation[last_index]->name = Path::GetFileNameWithoutExtension(openFileDialog1->FileName);
				ema_data->animation[last_index]->duration = import_anim->duration;
				ema_data->animation[last_index]->cmd_offset_count = import_anim->cmd_offset_count;
				ema_data->animation[last_index]->unknown = import_anim->unknown;
				ema_data->animation[last_index]->node = import_anim->node;
				ema_data->animation[last_index]->values = import_anim->values;

				if (write_ema(ema_data, skeleton_data, _currentNode->Tag->ToString()))
					MessageBox::Show("EMA file saved", "Done", MessageBoxButtons::OK);
				else
					MessageBox::Show("Failed to create file.", "Fail", MessageBoxButtons::OK);

				br->Close();
				fs->Close();

				// Updating tree
				const auto path = Path::GetDirectoryName(_currentNode->Tag->ToString());
				treeView1->Nodes[2]->Nodes->Clear();
				auto files = Directory::GetFiles(path);
				for (auto index = 0; index < files->Length; index++)
				{
					auto file = files[index];
					if (file->EndsWith(".ema"))
					{
						open_anim_file(path, getFileName(file, true));
					}
				}
			}
		}

		System::Void saveToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			saveEMA_contextMenuStrip->Close();

			System::DateTime^ now = System::DateTime::Now;
			auto string_array = _currentNode->Tag->ToString()->Split('\\');
			const auto path = Path::GetDirectoryName(_currentNode->Tag->ToString());
			String^ backup_path = {};
			backup_path += (path + "\\Backup\\" + now->Day + "." + now->Month + "-" + now->Hour + "." + now->Minute + "." + now->Second + "_" + string_array[string_array->Length - 1]);

			if (backupOriginalFileToolStripMenuItem->Checked)
			{
				Directory::CreateDirectory(path + "\\Backup\\");
				File::Copy(_currentNode->Tag->ToString(), backup_path, true);
			}

			// saving
			const auto ema_data = read_ema(_currentNode->Tag->ToString());
			const auto skeleton_data = read_ema_skeleton(_currentNode->Tag->ToString());

			if (write_ema(ema_data, skeleton_data, _currentNode->Tag->ToString()))
				MessageBox::Show("Animation file saved", "Done", MessageBoxButtons::OK);
			else
				MessageBox::Show("Failed to create file.", "Fail", MessageBoxButtons::OK);

			delete ema_data;
			delete skeleton_data;

			// Updating tree
			treeView1->Nodes[2]->Nodes->Clear();
			auto files = Directory::GetFiles(path);
			for (auto index = 0; index < files->Length; index++)
			{
				auto file = files[index];
				if (file->EndsWith(".ema"))
				{
					open_anim_file(path, getFileName(file, true));
				}
			}
		}
	
		System::Void saveAsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			saveEMA_contextMenuStrip->Close();

			auto string_array = _currentNode->Tag->ToString()->Split('\\');
			const auto path = Path::GetDirectoryName(_currentNode->Tag->ToString());

			auto saveFileDialog1 = gcnew SaveFileDialog();			
			saveFileDialog1->FileName = string_array[string_array->Length-1];
			saveFileDialog1->Filter = "EMA animation|*.ema";
			saveFileDialog1->RestoreDirectory = true;

			if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				if (backupOriginalFileToolStripMenuItem->Checked)
				{
					System::DateTime^ now = System::DateTime::Now;
					String^ backup_path = {};
					backup_path += (path + "\\Backup\\" + now->Day + "." + now->Month + "-" + now->Hour + "." + now->Minute + "." + now->Second + "_" + string_array[string_array->Length - 1]);

					Directory::CreateDirectory(path + "\\Backup\\");
					File::Copy(_currentNode->Tag->ToString(), backup_path, true);
				}

				// saving
				const auto ema_data = read_ema(_currentNode->Tag->ToString());
				const auto skeleton_data = read_ema_skeleton(_currentNode->Tag->ToString());

				if (write_ema(ema_data, skeleton_data, saveFileDialog1->FileName))
					MessageBox::Show("EMA file saved", "Done", MessageBoxButtons::OK);
				else
					MessageBox::Show("Failed to create file.", "Fail", MessageBoxButtons::OK);

				delete ema_data;
				delete skeleton_data;

				// Updating tree
				treeView1->Nodes[2]->Nodes->Clear();
				auto files = Directory::GetFiles(path);
				for (auto index = 0; index < files->Length; index++)
				{
					auto file = files[index];
					if (file->EndsWith(".ema"))
					{
						open_anim_file(path, getFileName(file, true));
					}
				}
			}
		}

		System::Void backupOriginalFileToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

		}

		System::Void saveAnim_contextMenuStrip_Closing(System::Object^ sender, System::Windows::Forms::ToolStripDropDownClosingEventArgs^ e) {

			if (e->CloseReason == ToolStripDropDownCloseReason::ItemClicked)
				e->Cancel = true;
		}

		System::Void exportDataToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			animationContextMenuStrip1->Close();

			auto saveFileDialog1 = gcnew SaveFileDialog();
			saveFileDialog1->RestoreDirectory = true;
			saveFileDialog1->FileName = _currentNode->Tag->ToString();
			saveFileDialog1->Filter = "SF4 animation|*.sf4anim";

			if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				if (backupEMAToolStripMenuItem->Checked)
				{
					auto string_array = _currentNode->Parent->Tag->ToString()->Split('\\');
					const auto path = Path::GetDirectoryName(_currentNode->Parent->Tag->ToString());
					System::DateTime^ now = System::DateTime::Now;
					String^ backup_path = {};
					backup_path += (path + "\\Backup\\" + now->Day + "." + now->Month + "-" + now->Hour + "." + now->Minute + "." + now->Second + "_" + string_array[string_array->Length - 1]);

					Directory::CreateDirectory(path + "\\Backup\\");
					File::Copy(_currentNode->Parent->Tag->ToString(), backup_path, true);
				}

				const auto ema_data = read_ema(_currentNode->Parent->Tag->ToString());
				const auto skeleton_data = read_ema_skeleton(_currentNode->Parent->Tag->ToString());

				auto fs = gcnew FileStream(saveFileDialog1->FileName, FileMode::Create);
				auto bw = gcnew BinaryWriter(fs);

				auto index = _currentNode->Index;
				const auto export_anim = gcnew anim_struct();

				export_anim->name = ema_data->animation[index]->name;
				export_anim->duration = ema_data->animation[index]->duration;
				export_anim->cmd_offset_count = ema_data->animation[index]->cmd_offset_count;
				export_anim->unknown = ema_data->animation[index]->unknown;
				export_anim->node = ema_data->animation[index]->node;
				export_anim->values = ema_data->animation[index]->values;

				for(auto i = 0; i < export_anim->node->Length; i ++)
				{
					export_anim->node[i]->name = skeleton_data->names[export_anim->node[i]->index];
				}

				auto formatter = gcnew Runtime::Serialization::Formatters::Binary::BinaryFormatter();
				auto stream = gcnew MemoryStream();
				formatter->Serialize(stream, export_anim);

				bw->Write(stream->ToArray());

				bw->Close();
				fs->Close();

				MessageBox::Show("Animation data saved.", "Done", MessageBoxButtons::OK);
			}
		}
		
		System::Void replaceDataToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			animationContextMenuStrip1->Close();

			auto openFileDialog1 = gcnew OpenFileDialog();
			if (steamToolStripMenuItem->Checked && steam_path != String::Empty)
			{
				openFileDialog1->InitialDirectory = steam_path;
			}
			openFileDialog1->RestoreDirectory = true;
			openFileDialog1->FileName = "";
			openFileDialog1->Filter = "Animation Data File|*.sf4anim";
			openFileDialog1->Title = "Select animation";

			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				if (backupEMAToolStripMenuItem->Checked)
				{
					auto string_array = _currentNode->Parent->Tag->ToString()->Split('\\');
					const auto path = Path::GetDirectoryName(_currentNode->Parent->Tag->ToString());
					System::DateTime^ now = System::DateTime::Now;
					String^ backup_path = {};
					backup_path += (path + "\\Backup\\" + now->Day + "." + now->Month + "-" + now->Hour + "." + now->Minute + "." + now->Second + "_" + string_array[string_array->Length - 1]);

					Directory::CreateDirectory(path + "\\Backup\\");
					File::Copy(_currentNode->Parent->Tag->ToString(), backup_path, true);
				}

				auto fs = gcnew FileStream(openFileDialog1->FileName, FileMode::Open);
				auto br = gcnew BinaryReader(fs);

				auto formatter = gcnew Runtime::Serialization::Formatters::Binary::BinaryFormatter();
				const auto stream = gcnew MemoryStream(br->ReadBytes(UINT32(fs->Length)));
				anim_struct^ import_anim;
				try
				{
					import_anim = static_cast<anim_struct^>(formatter->Deserialize(stream));
				}
				catch(...)
				{
					br->Close();
					fs->Close();

					MessageBox::Show("Struct version mismatch.", "Fail", MessageBoxButtons::OK);

					return;
				}

				const auto empty_struct = gcnew anim_struct();
				if(import_anim->struct_version != empty_struct->struct_version)
				{
					br->Close();
					fs->Close();

					MessageBox::Show("Struct version mismatch.\nCurrent version: " + empty_struct->struct_version + "\nFile version: " + import_anim->struct_version, "Fail", MessageBoxButtons::OK);

					return;
				}

				const auto ema_data = read_ema(_currentNode->Parent->Tag->ToString());
				const auto skeleton_data = read_ema_skeleton(_currentNode->Parent->Tag->ToString());

				auto index = _currentNode->Index;

				// Replacing node indexes with a correct one from skeleton
				for (auto i = 0; i < import_anim->node->Length; i++)
				{
					auto node_index = 0;
					for(auto a = 0; a < skeleton_data->names->Length; a++)
					{
						if (skeleton_data->names[a] == import_anim->node[i]->name)
							node_index = a;
					}

					import_anim->node[i]->index = node_index;
				}

				//ema_data->animation[index]->name = import_anim->name;
				ema_data->animation[index]->duration = import_anim->duration;
				ema_data->animation[index]->cmd_offset_count = import_anim->cmd_offset_count;
				ema_data->animation[index]->unknown = import_anim->unknown;
				ema_data->animation[index]->node = import_anim->node;
				ema_data->animation[index]->values = import_anim->values;

				if (write_ema(ema_data, skeleton_data, _currentNode->Parent->Tag->ToString()))
					MessageBox::Show("EMA file saved", "Done", MessageBoxButtons::OK);
				else
					MessageBox::Show("Failed to create file.", "Fail", MessageBoxButtons::OK);

				br->Close();
				fs->Close();
			}
		}

		System::Void backupEMAToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			if (backupEMAToolStripMenuItem->Checked)
				backupEMAToolStripMenuItem->Checked = false;
			else
				backupEMAToolStripMenuItem->Checked = true;
		}
		
		System::Void deleteToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			animationContextMenuStrip1->Close();

			if (backupEMAToolStripMenuItem->Checked)
			{
				auto string_array = _currentNode->Parent->Tag->ToString()->Split('\\');
				const auto path = Path::GetDirectoryName(_currentNode->Parent->Tag->ToString());
				System::DateTime^ now = System::DateTime::Now;
				String^ backup_path = {};
				backup_path += (path + "\\Backup\\" + now->Day + "." + now->Month + "-" + now->Hour + "." + now->Minute + "." + now->Second + "_" + string_array[string_array->Length - 1]);

				Directory::CreateDirectory(path + "\\Backup\\");
				File::Copy(_currentNode->Parent->Tag->ToString(), backup_path, true);
			}

			const auto ema_data = read_ema(_currentNode->Parent->Tag->ToString());
			const auto skeleton_data = read_ema_skeleton(_currentNode->Parent->Tag->ToString());

			ema_data->animation[_currentNode->Index] = nullptr;

			ema_data->header->animation_count--;
			auto animation_array = gcnew array<ema_animation^>(ema_data->header->animation_count);

			auto arr_index = 0;
			for (auto i = 0; i < animation_array->Length; i++)
			{
				if (ema_data->animation[i] == nullptr)
					arr_index++;

				animation_array[i] = ema_data->animation[arr_index];

				arr_index++;
			}
			ema_data->animation = animation_array;

			if (write_ema(ema_data, skeleton_data, _currentNode->Parent->Tag->ToString()))
				MessageBox::Show("EMA file saved", "Done", MessageBoxButtons::OK);
			else
				MessageBox::Show("Failed to create file.", "Fail", MessageBoxButtons::OK);

			// Updating tree
			const auto path = Path::GetDirectoryName(_currentNode->Parent->Tag->ToString());
			treeView1->Nodes[2]->Nodes->Clear();
			auto files = Directory::GetFiles(path);
			for (auto index = 0; index < files->Length; index++)
			{
				auto file = files[index];
				if (file->EndsWith(".ema"))
				{
					open_anim_file(path, getFileName(file, true));
				}
			}
		}
		
		System::Void animationContextMenuStrip1_Closing(System::Object^ sender, System::Windows::Forms::ToolStripDropDownClosingEventArgs^ e) {
			if (e->CloseReason == ToolStripDropDownCloseReason::ItemClicked)
				e->Cancel = true;
		}

	};
}
// ReSharper restore CppRedundantParentheses
// ReSharper restore CppRedundantQualifier
