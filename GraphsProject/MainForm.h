#pragma once
#include <vector>
#include <Windows.h>

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
		ref struct LineInfo {
			int circleIndex1; // Индекс первого круга
			int circleIndex2; // Индекс второго круга

			LineInfo(int index1, int index2) {
				circleIndex1 = index1;
				circleIndex2 = index2;
			}
		};

		GraphicGraph^ graphicGraph;
		Graph* graph;

		List<LineInfo^>^ linesList = gcnew List<LineInfo^>(); // Список для хранения информации о линиях
		List<Point>^ circlePositions;
		List<bool>^ isSelected;
		bool drawCircles;
		bool isDragging;
		bool isConnecting;
		int selectedCircleIndex1 = -1;
		int selectedCircleIndex2 = -1;
		int selectedLinkIndex = -1;
		Point lastMousePosition;

	public:
		MainForm(void)
		{
			graphicGraph = gcnew GraphicGraph();
			graph = new Graph();

			drawCircles = false;
			isDragging = false;
			isConnecting = false;
			circlePositions = gcnew List<Point>();
			isSelected = gcnew List<bool>();
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

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel4;
	private: System::Windows::Forms::Button^ importButton;

	private: System::Windows::Forms::Button^ exportButton;

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;
	private: System::Windows::Forms::Button^ addLinkButton;

	private: System::Windows::Forms::Button^ addVertexButton;

	private: System::Windows::Forms::ComboBox^ findPathMethod_comboBox;
	private: System::Windows::Forms::Button^ findPathButton;

	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Button^ deleteButton;

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::ComboBox^ startPoint_comboBox;
	private: System::Windows::Forms::ComboBox^ endPoint_comboBox;

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel5;
	private: System::Windows::Forms::PictureBox^ mainCanvas;

	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;

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
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->startPoint_comboBox = (gcnew System::Windows::Forms::ComboBox());
			this->endPoint_comboBox = (gcnew System::Windows::Forms::ComboBox());
			this->findPathButton = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->importButton = (gcnew System::Windows::Forms::Button());
			this->exportButton = (gcnew System::Windows::Forms::Button());
			this->mainCanvas = (gcnew System::Windows::Forms::PictureBox());
			this->tableLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->tableLayoutPanel5->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
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
			this->flowLayoutPanel1->Controls->Add(this->tableLayoutPanel5);
			this->flowLayoutPanel1->Controls->Add(this->tableLayoutPanel4);
			this->flowLayoutPanel1->Location = System::Drawing::Point(1045, 52);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(312, 633);
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
			this->addLinkButton->Text = L"Добавить связь";
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
			this->addVertexButton->Text = L"Добавить вершину";
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
			this->deleteButton->Text = L"Удалить вершину/связь";
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
			this->vertices_comboBox->Items->AddRange(gcnew cli::array< System::Object^  >(7) { L"A", L"B", L"C", L"D", L"E", L"F", L"G" });
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
			this->tableLayoutPanel2->Controls->Add(this->label5, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->startPoint_comboBox, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->endPoint_comboBox, 1, 1);
			this->tableLayoutPanel2->Location = System::Drawing::Point(3, 256);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 32)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(306, 135);
			this->tableLayoutPanel2->TabIndex = 9;
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(3, 87);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(120, 16);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Начальная точка";
			// 
			// label5
			// 
			this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(156, 87);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(111, 16);
			this->label5->TabIndex = 1;
			this->label5->Text = L"Конечная точка";
			// 
			// startPoint_comboBox
			// 
			this->startPoint_comboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->startPoint_comboBox->FormattingEnabled = true;
			this->startPoint_comboBox->Location = System::Drawing::Point(3, 106);
			this->startPoint_comboBox->Name = L"startPoint_comboBox";
			this->startPoint_comboBox->Size = System::Drawing::Size(147, 24);
			this->startPoint_comboBox->TabIndex = 2;
			// 
			// endPoint_comboBox
			// 
			this->endPoint_comboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->endPoint_comboBox->FormattingEnabled = true;
			this->endPoint_comboBox->Location = System::Drawing::Point(156, 106);
			this->endPoint_comboBox->Name = L"endPoint_comboBox";
			this->endPoint_comboBox->Size = System::Drawing::Size(147, 24);
			this->endPoint_comboBox->TabIndex = 3;
			// 
			// findPathButton
			// 
			this->findPathButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->findPathButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->findPathButton->Location = System::Drawing::Point(3, 397);
			this->findPathButton->Name = L"findPathButton";
			this->findPathButton->Size = System::Drawing::Size(306, 40);
			this->findPathButton->TabIndex = 5;
			this->findPathButton->Text = L"Выполнить поиск пути";
			this->findPathButton->UseVisualStyleBackColor = true;
			this->findPathButton->Click += gcnew System::EventHandler(this, &MainForm::findPathButton_Click);
			// 
			// tableLayoutPanel5
			// 
			this->tableLayoutPanel5->ColumnCount = 1;
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel5->Controls->Add(this->label6, 0, 0);
			this->tableLayoutPanel5->Controls->Add(this->textBox1, 0, 1);
			this->tableLayoutPanel5->Controls->Add(this->textBox2, 0, 3);
			this->tableLayoutPanel5->Controls->Add(this->label7, 0, 2);
			this->tableLayoutPanel5->Location = System::Drawing::Point(3, 443);
			this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
			this->tableLayoutPanel5->RowCount = 4;
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel5->Size = System::Drawing::Size(309, 129);
			this->tableLayoutPanel5->TabIndex = 10;
			// 
			// label6
			// 
			this->label6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(3, 16);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(94, 16);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Имя вершины";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(3, 35);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(303, 22);
			this->textBox1->TabIndex = 2;
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->Location = System::Drawing::Point(3, 99);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(303, 22);
			this->textBox2->TabIndex = 3;
			// 
			// label7
			// 
			this->label7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(3, 80);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(72, 16);
			this->label7->TabIndex = 1;
			this->label7->Text = L"Вес связи";
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->tableLayoutPanel4->ColumnCount = 2;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel4->Controls->Add(this->importButton, 1, 0);
			this->tableLayoutPanel4->Controls->Add(this->exportButton, 0, 0);
			this->tableLayoutPanel4->Location = System::Drawing::Point(3, 578);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 1;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(306, 57);
			this->tableLayoutPanel4->TabIndex = 1;
			// 
			// importButton
			// 
			this->importButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->importButton->Location = System::Drawing::Point(156, 3);
			this->importButton->Name = L"importButton";
			this->importButton->Size = System::Drawing::Size(147, 51);
			this->importButton->TabIndex = 1;
			this->importButton->Text = L"Импорт";
			this->importButton->UseVisualStyleBackColor = true;
			// 
			// exportButton
			// 
			this->exportButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->exportButton->Location = System::Drawing::Point(3, 3);
			this->exportButton->Name = L"exportButton";
			this->exportButton->Size = System::Drawing::Size(147, 51);
			this->exportButton->TabIndex = 0;
			this->exportButton->Text = L"Экспорт";
			this->exportButton->UseVisualStyleBackColor = true;
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
			this->tableLayoutPanel5->ResumeLayout(false);
			this->tableLayoutPanel5->PerformLayout();
			this->tableLayoutPanel4->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mainCanvas))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private:

		System::Void addVertexButton_Click(System::Object^ sender, System::EventArgs^ e) {
			AddVertex(graph, "A", graphicGraph);
		}

		System::Void mainCanvas_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
			if (drawCircles) {
				Graphics^ g = e->Graphics;

				// Рисуем графические вершины (круги)
				for each (GraphicVertex ^ vertex in graphicGraph->vertices) {
					Point center(vertex->position.X - 15, vertex->position.Y - 15);
					SolidBrush^ brush = gcnew SolidBrush(Color::Red);
					if (vertex->isSelected)
						brush = gcnew SolidBrush(Color::DarkRed);
					g->FillEllipse(brush, center.X, center.Y, 30, 30);
					delete brush;
				}

				// Рисуем графические рёбра (стрелки)
				Pen^ pen = gcnew Pen(Color::Black, 3);
				Drawing::Drawing2D::AdjustableArrowCap^ arrowCap = gcnew Drawing::Drawing2D::AdjustableArrowCap(5, 5);
				pen->CustomEndCap = arrowCap;

				for each (GraphicVertex ^ vertex in graphicGraph->vertices) {
					for each (GraphicEdge ^ edge in vertex->edges) {
						Point start(vertex->position.X, vertex->position.Y);
						Point end(graphicGraph->vertices[edge->destination]->position.X, graphicGraph->vertices[edge->destination]->position.Y);
						g->DrawLine(pen, start, end);
					}
				}

				delete pen;
				delete arrowCap;
			}
		}


		System::Void mainCanvas_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			if (!isConnecting) {
				isDragging = false;

				if (drawCircles) {
					for (int i = 0; i < circlePositions->Count; i++) {
						System::Drawing::Rectangle circleBounds(circlePositions[i].X, circlePositions[i].Y, 30, 30);
						if (circleBounds.Contains(e->Location)) {
							isDragging = true;
							selectedCircleIndex1 = i;
							lastMousePosition = e->Location;
							// Сбросить выделение всех кругов
							for (int j = 0; j < isSelected->Count; j++) {
								isSelected[j] = false;
							}
							// Выделить выбранный круг
							isSelected[selectedCircleIndex1] = true;
							break;
						}
						else
						{
							clearSelections();
						}
					}

					for each (LineInfo ^ line in linesList) {
						Point center1(circlePositions[line->circleIndex1].X + 15, circlePositions[line->circleIndex1].Y + 15);
						Point center2(circlePositions[line->circleIndex2].X + 15, circlePositions[line->circleIndex2].Y + 15);

						double distance = DistancePointToLine(e->Location, center1, center2);
						if (distance < 5.0) { // Пороговое значение для определения клика по линии
							selectedLinkIndex = linesList->IndexOf(line);
							mainCanvas->Invalidate();
							break;
						}
					}
				}
			}
			mainCanvas->Invalidate();
		}

		System::Void mainCanvas_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			if (isConnecting) {
				for (int circleIndex = 0; circleIndex < circlePositions->Count; circleIndex++) {
					System::Drawing::Rectangle circleBounds(circlePositions[circleIndex].X, circlePositions[circleIndex].Y, 30, 30);
					if (circleBounds.Contains(e->Location)) {
						if (selectedCircleIndex1 == -1) {
							selectedCircleIndex1 = circleIndex;
							isSelected[selectedCircleIndex1] = true;
							break;
						}
						else if (selectedCircleIndex1 != circleIndex) {
							selectedCircleIndex2 = circleIndex;

							// Проверяем, существует ли уже линия между выбранными кругами
							bool lineExists = false;
							for (int i = 0; i < linesList->Count; i++) {
								LineInfo^ line = linesList[i];
								if ((line->circleIndex1 == selectedCircleIndex1 && line->circleIndex2 == selectedCircleIndex2)) {
									lineExists = true;
									break;
								}
							}

							if (lineExists) {
								MessageBox::Show("Связь уже существует");
							}
							else {
								linesList->Add(gcnew LineInfo(selectedCircleIndex1, selectedCircleIndex2));
							}

							isConnecting = false; // Завершаем процесс соединения
							break;
						}
					}
				}
			}
			mainCanvas->Invalidate();
		}

		System::Void mainCanvas_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			if (isDragging) {
				int deltaX = e->X - lastMousePosition.X;
				int deltaY = e->Y - lastMousePosition.Y;
				lastMousePosition = e->Location;

				// Получаем новое положение круга
				int newX = circlePositions[selectedCircleIndex1].X + deltaX;
				int newY = circlePositions[selectedCircleIndex1].Y + deltaY;

				// Проверяем, не выходит ли новое положение за пределы pictureBox
				if (newX >= 0 && newX <= mainCanvas->Width - 30 && newY >= 0 && newY <= mainCanvas->Height - 30) {
					circlePositions[selectedCircleIndex1] = Point(newX, newY);
					mainCanvas->Invalidate();
				}
			}
		}

		System::Void mainCanvas_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			isDragging = false;
		}

		System::Void addLinkButton_Click(System::Object^ sender, System::EventArgs^ e) {
			if (circlePositions->Count < 2) {
				MessageBox::Show("You need at least two circles to draw a link.");
				return;
			}

			isConnecting = true;

			clearSelections();

			MessageBox::Show("Select two circles to draw a link between them.");
		}

		System::Void deleteButton_Click(System::Object^ sender, System::EventArgs^ e) {
			if (selectedCircleIndex1 != -1) {
				// Удаляем выбранный круг
				circlePositions->RemoveAt(selectedCircleIndex1);
				isSelected->RemoveAt(selectedCircleIndex1);

				// Создаем временный список для хранения индексов связей, связанных с этим кругом
				List<int>^ linksToRemove = gcnew List<int>();

				// Помечаем связи, которые нужно удалить
				for (int i = 0; i < linesList->Count; i++) {
					if (linesList[i]->circleIndex1 == selectedCircleIndex1 || linesList[i]->circleIndex2 == selectedCircleIndex1) {
						linksToRemove->Add(i);
					}
				}

				// Удаляем связи из основного списка
				for (int i = linksToRemove->Count - 1; i >= 0; i--) {
					linesList->RemoveAt(linksToRemove[i]);
				}

				selectedCircleIndex1 = -1; // Сброс индекса выбранного круга
			}
			else if (selectedLinkIndex != -1) {
				// Удаляем выбранную связь
				linesList->RemoveAt(selectedLinkIndex);
				selectedLinkIndex = -1; // Сброс индекса выбранной связи
			}
			else MessageBox::Show("Вы не выбрали элемент для удаления");

			mainCanvas->Invalidate(); // Перерисовываем холст
		}



		System::Void findPathButton_Click(System::Object^ sender, System::EventArgs^ e) {
			MessageBox::Show("ShortestPath: A -> B -> C. weight: 9");
		}

		void clearSelections() {
			for (int i = 0; i < isSelected->Count; i++) {
				isSelected[i] = false;
				mainCanvas->Invalidate();
			}
			selectedCircleIndex1 = -1;
			selectedCircleIndex2 = -1;

			selectedLinkIndex = -1;
		}

		// Определение расстояния от линии до клика мышью
		double DistancePointToLine(Point point, Point lineStart, Point lineEnd) {
			double A = point.X - lineStart.X;
			double B = point.Y - lineStart.Y;
			double C = lineEnd.X - lineStart.X;
			double D = lineEnd.Y - lineStart.Y;

			double dot = A * C + B * D;
			double len_sq = C * C + D * D;
			double param = dot / len_sq;

			double xx, yy;

			if (param < 0) {
				xx = lineStart.X;
				yy = lineStart.Y;
			}
			else if (param > 1) {
				xx = lineEnd.X;
				yy = lineEnd.Y;
			}
			else {
				xx = lineStart.X + param * C;
				yy = lineStart.Y + param * D;
			}

			double dx = point.X - xx;
			double dy = point.Y - yy;
			return Math::Sqrt(dx * dx + dy * dy);
		}
	};
}
