#pragma once
#include <Windows.h>
#include "Graph.h"

namespace GraphsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		Graph^ graph_;

		bool addNode;
		bool addLink;
		bool deleteElements;

		Node^ firstSelectedNode;
		Node^ secondSelectedNode;
		Node^ movingNode;

		Point lastMousePosition;
	public:

		MainForm(void)
		{
			addNode = false;
			addLink = false;
			deleteElements = false;

			firstSelectedNode = nullptr;
			secondSelectedNode = nullptr;

			movingNode = nullptr;

			graph_ = gcnew Graph();
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::ComboBox^ vertices_comboBox;

	private: System::Windows::Forms::ComboBox^ links_comboBox;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;
	private: System::Windows::Forms::Button^ addLinkButton;

	private: System::Windows::Forms::Button^ addVertexButton;

	private: System::Windows::Forms::ComboBox^ findPathMethod_comboBox;
	private: System::Windows::Forms::Button^ findPathButton;

	private: System::Windows::Forms::PictureBox^ mainCanvas;

	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Button^ deleteButton;

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::Label^ label1;

	private: System::Windows::Forms::ComboBox^ startPoint_comboBox;
	private: System::Windows::Forms::ComboBox^ endPoint_comboBox;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;

	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ nodeName_textBox;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ edgeWeight_textBox;


	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::TextBox^ nodeSize_textBox;
	private: System::Windows::Forms::TextBox^ edgeThickness_textBox;


	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Button^ colorPicker_Button;

	private: System::Windows::Forms::ColorDialog^ colorDialog1;

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->addLinkButton = (gcnew System::Windows::Forms::Button());
			this->addVertexButton = (gcnew System::Windows::Forms::Button());
			this->deleteButton = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->vertices_comboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->links_comboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->findPathMethod_comboBox = (gcnew System::Windows::Forms::ComboBox());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->startPoint_comboBox = (gcnew System::Windows::Forms::ComboBox());
			this->endPoint_comboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->findPathButton = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->nodeName_textBox = (gcnew System::Windows::Forms::TextBox());
			this->edgeWeight_textBox = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->nodeSize_textBox = (gcnew System::Windows::Forms::TextBox());
			this->edgeThickness_textBox = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->colorPicker_Button = (gcnew System::Windows::Forms::Button());
			this->mainCanvas = (gcnew System::Windows::Forms::PictureBox());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->tableLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tableLayoutPanel5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mainCanvas))->BeginInit();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				76.61765F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				23.38235F)));
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel1, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->mainCanvas, 0, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(12, 12);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1360, 737);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->flowLayoutPanel1->Controls->Add(this->tableLayoutPanel3);
			this->flowLayoutPanel1->Controls->Add(this->deleteButton);
			this->flowLayoutPanel1->Controls->Add(this->label2);
			this->flowLayoutPanel1->Controls->Add(this->vertices_comboBox);
			this->flowLayoutPanel1->Controls->Add(this->label3);
			this->flowLayoutPanel1->Controls->Add(this->links_comboBox);
			this->flowLayoutPanel1->Controls->Add(this->label4);
			this->flowLayoutPanel1->Controls->Add(this->findPathMethod_comboBox);
			this->flowLayoutPanel1->Controls->Add(this->tableLayoutPanel2);
			this->flowLayoutPanel1->Controls->Add(this->findPathButton);
			this->flowLayoutPanel1->Controls->Add(this->groupBox1);
			this->flowLayoutPanel1->Location = System::Drawing::Point(1045, 91);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(312, 555);
			this->flowLayoutPanel1->TabIndex = 2;
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 2;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel3->Controls->Add(this->addLinkButton, 1, 0);
			this->tableLayoutPanel3->Controls->Add(this->addVertexButton, 0, 0);
			this->tableLayoutPanel3->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 1;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(306, 54);
			this->tableLayoutPanel3->TabIndex = 0;
			// 
			// addLinkButton
			// 
			this->addLinkButton->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->addLinkButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->addLinkButton->Location = System::Drawing::Point(156, 4);
			this->addLinkButton->Name = L"addLinkButton";
			this->addLinkButton->Size = System::Drawing::Size(147, 47);
			this->addLinkButton->TabIndex = 1;
			this->addLinkButton->Text = L"Добавление связей";
			this->addLinkButton->UseVisualStyleBackColor = true;
			this->addLinkButton->Click += gcnew System::EventHandler(this, &MainForm::addLinkButton_Click);
			// 
			// addVertexButton
			// 
			this->addVertexButton->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->addVertexButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->addVertexButton->Location = System::Drawing::Point(3, 4);
			this->addVertexButton->Name = L"addVertexButton";
			this->addVertexButton->Size = System::Drawing::Size(147, 47);
			this->addVertexButton->TabIndex = 0;
			this->addVertexButton->Text = L"Добавление вершин";
			this->addVertexButton->UseVisualStyleBackColor = true;
			this->addVertexButton->Click += gcnew System::EventHandler(this, &MainForm::addVertexButton_Click);
			// 
			// deleteButton
			// 
			this->deleteButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->deleteButton->Location = System::Drawing::Point(3, 63);
			this->deleteButton->Name = L"deleteButton";
			this->deleteButton->Size = System::Drawing::Size(303, 49);
			this->deleteButton->TabIndex = 8;
			this->deleteButton->Text = L"Удаление элементов";
			this->deleteButton->UseVisualStyleBackColor = true;
			this->deleteButton->Click += gcnew System::EventHandler(this, &MainForm::deleteButton_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(3, 115);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(66, 16);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Вершины";
			// 
			// vertices_comboBox
			// 
			this->vertices_comboBox->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->vertices_comboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->vertices_comboBox->FormattingEnabled = true;
			this->vertices_comboBox->Location = System::Drawing::Point(3, 134);
			this->vertices_comboBox->Name = L"vertices_comboBox";
			this->vertices_comboBox->Size = System::Drawing::Size(306, 24);
			this->vertices_comboBox->TabIndex = 4;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(3, 161);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(47, 16);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Связи";
			// 
			// links_comboBox
			// 
			this->links_comboBox->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->links_comboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->links_comboBox->FormattingEnabled = true;
			this->links_comboBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"A - B", L"B - C", L"G - F", L"F - E", L"A - D" });
			this->links_comboBox->Location = System::Drawing::Point(3, 180);
			this->links_comboBox->Name = L"links_comboBox";
			this->links_comboBox->Size = System::Drawing::Size(306, 24);
			this->links_comboBox->TabIndex = 3;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(3, 207);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(132, 16);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Метод поиска пути";
			// 
			// findPathMethod_comboBox
			// 
			this->findPathMethod_comboBox->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->findPathMethod_comboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->findPathMethod_comboBox->FormattingEnabled = true;
			this->findPathMethod_comboBox->Location = System::Drawing::Point(3, 226);
			this->findPathMethod_comboBox->Name = L"findPathMethod_comboBox";
			this->findPathMethod_comboBox->Size = System::Drawing::Size(306, 24);
			this->findPathMethod_comboBox->TabIndex = 2;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->startPoint_comboBox, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->endPoint_comboBox, 1, 1);
			this->tableLayoutPanel2->Controls->Add(this->label5, 1, 0);
			this->tableLayoutPanel2->Location = System::Drawing::Point(3, 256);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 32)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(306, 54);
			this->tableLayoutPanel2->TabIndex = 9;
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(3, 6);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(120, 16);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Начальная точка";
			// 
			// startPoint_comboBox
			// 
			this->startPoint_comboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->startPoint_comboBox->FormattingEnabled = true;
			this->startPoint_comboBox->Location = System::Drawing::Point(3, 25);
			this->startPoint_comboBox->Name = L"startPoint_comboBox";
			this->startPoint_comboBox->Size = System::Drawing::Size(147, 24);
			this->startPoint_comboBox->TabIndex = 2;
			// 
			// endPoint_comboBox
			// 
			this->endPoint_comboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->endPoint_comboBox->FormattingEnabled = true;
			this->endPoint_comboBox->Location = System::Drawing::Point(156, 25);
			this->endPoint_comboBox->Name = L"endPoint_comboBox";
			this->endPoint_comboBox->Size = System::Drawing::Size(147, 24);
			this->endPoint_comboBox->TabIndex = 3;
			// 
			// label5
			// 
			this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(156, 6);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(111, 16);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Конечная точка";
			// 
			// findPathButton
			// 
			this->findPathButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->findPathButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->findPathButton->Location = System::Drawing::Point(3, 316);
			this->findPathButton->Name = L"findPathButton";
			this->findPathButton->Size = System::Drawing::Size(306, 40);
			this->findPathButton->TabIndex = 5;
			this->findPathButton->Text = L"Выполнить поиск пути";
			this->findPathButton->UseVisualStyleBackColor = true;
			this->findPathButton->Click += gcnew System::EventHandler(this, &MainForm::findPathButton_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->tableLayoutPanel5);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox1->Location = System::Drawing::Point(3, 362);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(312, 190);
			this->groupBox1->TabIndex = 10;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Свойства элемента";
			// 
			// tableLayoutPanel5
			// 
			this->tableLayoutPanel5->ColumnCount = 2;
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel5->Controls->Add(this->label6, 0, 0);
			this->tableLayoutPanel5->Controls->Add(this->label7, 1, 0);
			this->tableLayoutPanel5->Controls->Add(this->nodeName_textBox, 0, 1);
			this->tableLayoutPanel5->Controls->Add(this->edgeWeight_textBox, 1, 1);
			this->tableLayoutPanel5->Controls->Add(this->label8, 0, 2);
			this->tableLayoutPanel5->Controls->Add(this->label9, 1, 2);
			this->tableLayoutPanel5->Controls->Add(this->nodeSize_textBox, 0, 3);
			this->tableLayoutPanel5->Controls->Add(this->edgeThickness_textBox, 1, 3);
			this->tableLayoutPanel5->Controls->Add(this->label10, 0, 4);
			this->tableLayoutPanel5->Controls->Add(this->colorPicker_Button, 1, 4);
			this->tableLayoutPanel5->Location = System::Drawing::Point(6, 19);
			this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
			this->tableLayoutPanel5->RowCount = 5;
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel5->Size = System::Drawing::Size(297, 165);
			this->tableLayoutPanel5->TabIndex = 11;
			// 
			// label6
			// 
			this->label6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(3, 17);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(94, 16);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Имя вершины";
			// 
			// label7
			// 
			this->label7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(151, 17);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(72, 16);
			this->label7->TabIndex = 1;
			this->label7->Text = L"Вес связи";
			// 
			// nodeName_textBox
			// 
			this->nodeName_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->nodeName_textBox->Location = System::Drawing::Point(3, 36);
			this->nodeName_textBox->MaxLength = 64;
			this->nodeName_textBox->Name = L"nodeName_textBox";
			this->nodeName_textBox->Size = System::Drawing::Size(141, 22);
			this->nodeName_textBox->TabIndex = 2;
			// 
			// edgeWeight_textBox
			// 
			this->edgeWeight_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->edgeWeight_textBox->Location = System::Drawing::Point(151, 36);
			this->edgeWeight_textBox->MaxLength = 64;
			this->edgeWeight_textBox->Name = L"edgeWeight_textBox";
			this->edgeWeight_textBox->Size = System::Drawing::Size(141, 22);
			this->edgeWeight_textBox->TabIndex = 3;
			// 
			// label8
			// 
			this->label8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(3, 83);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(118, 16);
			this->label8->TabIndex = 4;
			this->label8->Text = L"Размер вершины";
			// 
			// label9
			// 
			this->label9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(151, 83);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(106, 16);
			this->label9->TabIndex = 5;
			this->label9->Text = L"Толщина связи";
			// 
			// nodeSize_textBox
			// 
			this->nodeSize_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->nodeSize_textBox->Location = System::Drawing::Point(3, 102);
			this->nodeSize_textBox->MaxLength = 64;
			this->nodeSize_textBox->Name = L"nodeSize_textBox";
			this->nodeSize_textBox->Size = System::Drawing::Size(141, 22);
			this->nodeSize_textBox->TabIndex = 6;
			// 
			// edgeThickness_textBox
			// 
			this->edgeThickness_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->edgeThickness_textBox->Location = System::Drawing::Point(151, 102);
			this->edgeThickness_textBox->MaxLength = 64;
			this->edgeThickness_textBox->Name = L"edgeThickness_textBox";
			this->edgeThickness_textBox->Size = System::Drawing::Size(141, 22);
			this->edgeThickness_textBox->TabIndex = 7;
			// 
			// label10
			// 
			this->label10->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(3, 140);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(142, 16);
			this->label10->TabIndex = 8;
			this->label10->Text = L"Цвет";
			this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// colorPicker_Button
			// 
			this->colorPicker_Button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->colorPicker_Button->Location = System::Drawing::Point(151, 135);
			this->colorPicker_Button->Name = L"colorPicker_Button";
			this->colorPicker_Button->Size = System::Drawing::Size(143, 27);
			this->colorPicker_Button->TabIndex = 9;
			this->colorPicker_Button->UseVisualStyleBackColor = true;
			// 
			// mainCanvas
			// 
			this->mainCanvas->Location = System::Drawing::Point(3, 3);
			this->mainCanvas->Name = L"mainCanvas";
			this->mainCanvas->Size = System::Drawing::Size(1036, 731);
			this->mainCanvas->TabIndex = 3;
			this->mainCanvas->TabStop = false;
			this->mainCanvas->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::mainCanvas_Paint);
			this->mainCanvas->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::mainCanvas_MouseClick);
			this->mainCanvas->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::mainCanvas_MouseDown);
			this->mainCanvas->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::mainCanvas_MouseMove);
			this->mainCanvas->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::mainCanvas_MouseUp);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1384, 761);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Name = L"MainForm";
			this->Text = L"Graphs";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->tableLayoutPanel5->ResumeLayout(false);
			this->tableLayoutPanel5->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mainCanvas))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	public:
		System::Void addVertexButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void mainCanvas_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
		System::Void mainCanvas_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void mainCanvas_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void mainCanvas_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void mainCanvas_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void addLinkButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void deleteButton_Click(System::Object^ sender, System::EventArgs^ e);

		System::Void findPathButton_Click(System::Object^ sender, System::EventArgs^ e) {
			
		}

		Node^ FindClickedNode(Point clickLocation, List<Node^>^ nodes);
		Edge^ FindClickedEdge(Point clickLocation, List<Edge^>^ edges);

		bool IsMouseOverEdge(Point clickLocation, Edge^ edge);
		double PointToSegmentSquaredDistance(Point p, Point start, Point end);
		double PointToPointSquaredDistance(Point p1, Point p2);
	};
}
