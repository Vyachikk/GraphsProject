#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace GraphsProject;

struct leaks {
	~leaks() { 
		if (_CrtDumpMemoryLeaks()) {
			System::Windows::Forms::MessageBox::Show("Обнаружены утечки памяти!", "Утечки памяти");
		}
	}
};

[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MainForm);

	leaks checker;
	return 0;
}

System::Void MainForm::addVertexButton_Click(System::Object^ sender, System::EventArgs^ e) {
	addNode = !addNode;
	addVertexButton->Text = addNode ? "Отменить добавление" : "Добавление вершин";
	addLinkButton->Enabled = !addNode; // Включаем/выключаем кнопку добавления связей в зависимости от режима
	deleteButton->Enabled = !addNode; // Включаем/выключаем кнопку удаления вершин в зависимости от режима
}

System::Void MainForm::addLinkButton_Click(System::Object^ sender, System::EventArgs^ e) {
	addLink = !addLink;
	addLinkButton->Text = addLink ? "Отменить добавление" : "Добавление связей";
	addVertexButton->Enabled = !addLink; // Включаем/выключаем кнопку добавления вершин в зависимости от режима
	deleteButton->Enabled = !addLink; // Включаем/выключаем кнопку удаления вершин в зависимости от режима
}

System::Void MainForm::deleteButton_Click(System::Object^ sender, System::EventArgs^ e) {
	deleteElements = !deleteElements;
	deleteButton->Text = deleteElements ? "Отменить удаление" : "Удаление элементов";
	addVertexButton->Enabled = !deleteElements; // Включаем/выключаем кнопку добавления вершин в зависимости от режима
	addLinkButton->Enabled = !deleteElements; // Включаем/выключаем кнопку добавления связей в зависимости от режима
}

System::Void MainForm::mainCanvas_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	if (addNode) {
		AddNode(e->X, e->Y);
	}
	else if (addLink) {
		AddEdge(e->X, e->Y);
	}
	else if (deleteElements) {
		DeleteElement(e->X, e->Y);
	}
	mainCanvas->Invalidate();
}

System::Void MainForm::mainCanvas_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	Graphics^ g = e->Graphics;

	// Рисуем рёбра
	for each (ManagedEdgeWrapper ^ edge in graph_->GetEdges()) {
		ManagedNodeWrapper^ sourceNode = edge->GetSource();
		ManagedNodeWrapper^ destinationNode = edge->GetDestination();

		Point startPoint(sourceNode->GetX() + sourceNode->GetSize() / 2, sourceNode->GetY() + sourceNode->GetSize() / 2);
		Point endPoint(destinationNode->GetX() + destinationNode->GetSize() / 2, destinationNode->GetY() + destinationNode->GetSize() / 2);

		Color edgeColor = edge->GetColor();
		Color edgeSelectedColor = edge->GetSelectedColor();

		Pen^ pen = gcnew Pen(edge->GetSelection() ? edgeSelectedColor : edgeColor, edge->GetSize());
		DrawArrow(g, pen, startPoint, endPoint, edge->GetSize() + 5, destinationNode->GetSize());
		delete pen;

		// Рисуем вес ребра рядом с ним
		String^ weight = edge->GetWeight().ToString();
		SizeF stringSize = g->MeasureString(weight, gcnew System::Drawing::Font(SystemFonts::DefaultFont->FontFamily, 12));
		PointF textPosition((float)(startPoint.X + endPoint.X) / 2 - stringSize.Width / 2, (float)(startPoint.Y + endPoint.Y) / 2 - stringSize.Height / 2);

		// Добавляем белый фон под текстом
		RectangleF backgroundRect(textPosition, stringSize);
		g->FillRectangle(Brushes::White, backgroundRect);

		g->DrawString(weight, gcnew System::Drawing::Font(SystemFonts::DefaultFont->FontFamily, 12), Brushes::Black, textPosition);
	}

	// Рисуем узлы
	for each (ManagedNodeWrapper ^ node in graph_->GetNodes()) {
		Color nodeColor = node->GetColor();
		Color nodeSelectedColor = node->GetSelectedColor();

		SolidBrush^ brush = gcnew SolidBrush(node->GetSelection() ? nodeSelectedColor : nodeColor);
		g->FillEllipse(brush, node->GetX(), node->GetY(), node->GetSize(), node->GetSize());
		delete brush;

		// Рисуем имя вершины рядом с ней
		String^ nodeName = gcnew String(node->GetName());
		SizeF stringSize = g->MeasureString(nodeName, SystemFonts::DefaultFont);
		PointF textPosition((float)node->GetX() + node->GetSize() + 5, (float)node->GetY() + (node->GetSize() - stringSize.Height) / 2);
		g->DrawString(nodeName, SystemFonts::DefaultFont, Brushes::Black, textPosition);
	}
}

System::Void MainForm::mainCanvas_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	if (!addNode && !addLink && !deleteElements) {
		Object^ element = FindClickedElement(Point(e->X, e->Y), graph_->GetNodes(), graph_->GetEdges());
		if (element != nullptr) {
			clickedElement = element;
			if (ManagedNodeWrapper^ clickedNode = dynamic_cast<ManagedNodeWrapper^>(element)) {
				UpdateElementData(clickedNode);
				movingNode = clickedNode;
				vertices_comboBox->SelectedItem = clickedNode->GetName();
			}
			else if (ManagedEdgeWrapper^ clickedEdge = dynamic_cast<ManagedEdgeWrapper^>(element)) {
				UpdateElementData(clickedEdge);
				links_comboBox->SelectedItem = clickedEdge->GetSource()->GetName() + " -> " + clickedEdge->GetDestination()->GetName();
			}
		}
	}
}

System::Void MainForm::mainCanvas_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	int canvasWidth = mainCanvas->Width;
	int canvasHeight = mainCanvas->Height;

	for each (ManagedEdgeWrapper ^ edge in graph_->GetEdges()) {
		bool isMouseOverEdge = IsMouseOverEdge(e->Location, edge);
		if (isMouseOverEdge != edge->GetSelection()) {
			edge->SetSelection(isMouseOverEdge);
		}
	}

	for each (ManagedNodeWrapper ^ node in graph_->GetNodes()) {
		bool isMouseOverNode = (e->X >= node->GetX() && e->X <= node->GetX() + node->GetSize() &&
			e->Y >= node->GetY() && e->Y <= node->GetY() + node->GetSize());
		if (isMouseOverNode != node->GetSelection()) {
			node->SetSelection(isMouseOverNode);
		}
	}

	if (!addNode && !addLink && movingNode != nullptr) {
		int newX = e->X - movingNode->GetSize() / 2;
		int newY = e->Y - movingNode->GetSize() / 2;

		// Проверяем, не выходит ли вершина за пределы mainCanvas
		newX = Math::Max(0, Math::Min(newX, canvasWidth - movingNode->GetSize()));
		newY = Math::Max(0, Math::Min(newY, canvasHeight - movingNode->GetSize()));

		movingNode->SetX(newX);
		movingNode->SetY(newY);

		for each (ManagedEdgeWrapper ^ edge in graph_->GetEdges()) {
			if (edge->GetSource() == movingNode) {
				edge->GetSource()->SetX(newX);
				edge->GetSource()->SetY(newY);
			}
			else if (edge->GetDestination() == movingNode) {
				edge->GetDestination()->SetX(newX);
				edge->GetDestination()->SetY(newY);
			}
		}
	}

	mainCanvas->Invalidate();
}

System::Void MainForm::mainCanvas_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	movingNode = nullptr;
}

System::Void MainForm::colorPicker_Button_Click(System::Object^ sender, System::EventArgs^ e) {
	ColorDialog^ colorDialog = gcnew ColorDialog();

	if (colorDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		Color selectedColor = colorDialog->Color;
		colorPicker_Button->BackColor = selectedColor;

		if (clickedElement != nullptr) {
			ManagedNodeWrapper^ clickedNode = dynamic_cast<ManagedNodeWrapper^>(clickedElement);
			ManagedEdgeWrapper^ clickedEdge = dynamic_cast<ManagedEdgeWrapper^>(clickedElement);
			if (clickedNode != nullptr) {
				COLORREF colorRef = RGB(selectedColor.R, selectedColor.G, selectedColor.B);
				clickedNode->SetColor(colorRef);
			}
			else if (clickedEdge != nullptr) {
				COLORREF colorRef = RGB(selectedColor.R, selectedColor.G, selectedColor.B);
				clickedEdge->SetColor(colorRef);
			}
			mainCanvas->Invalidate();
		}
	}
	delete colorDialog; // Освобождаем ресурсы ColorDialog
}

System::Void MainForm::Name_textBox_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) 
{
	if (clickedElement != nullptr && e->KeyCode == Keys::Enter) {
		ManagedNodeWrapper^ clickedNode = dynamic_cast<ManagedNodeWrapper^>(clickedElement);
		ManagedEdgeWrapper^ clickedEdge = dynamic_cast<ManagedEdgeWrapper^>(clickedElement);

		if (clickedNode != nullptr) {
			for each (ManagedNodeWrapper ^ node in graph_->GetNodes())
			{
				if (node->GetName() == Name_textBox->Text)
				{
					MessageBox::Show("Вершина с таким именем уже существует!");
					return;
				}
			}
			clickedNode->SetName(Name_textBox->Text);
		}
		else if (clickedEdge != nullptr) {
			try {
				clickedEdge->SetWeight(System::Convert::ToInt32(Name_textBox->Text));
			}
			catch (System::FormatException^) {
			}
		}
		clickedElement = nullptr;
		UpdateComboBoxes();
	}
}

System::Void MainForm::Size_numeric_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (clickedElement != nullptr) {
		ManagedNodeWrapper^ clickedNode = dynamic_cast<ManagedNodeWrapper^>(clickedElement);
		ManagedEdgeWrapper^ clickedEdge = dynamic_cast<ManagedEdgeWrapper^>(clickedElement);

		if (clickedNode != nullptr) {
			clickedNode->SetSize(System::Convert::ToInt32(Size_numeric->Value));
		}
		else if (clickedEdge != nullptr) {
			try {
				clickedEdge->SetSize(System::Convert::ToInt32(Size_numeric->Value));
			}
			catch (System::FormatException^) {
			}
		}
		mainCanvas->Invalidate();
	}
}

System::Void MainForm::comboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	ComboBox^ comboBox = dynamic_cast<ComboBox^>(sender);
	if (comboBox != nullptr)
	{
		String^ selectedValue = dynamic_cast<String^>(comboBox->SelectedItem);
		if (selectedValue != nullptr)
		{
			array<String^>^ parts = selectedValue->Split(gcnew array<String^> { " -> " }, StringSplitOptions::None);

			if (parts->Length == 2)
			{
				String^ sourceName = parts[0];
				String^ destinationName = parts[1];

				ManagedNodeWrapper^ sourceNode = graph_->GetNode(sourceName);
				ManagedNodeWrapper^ destinationNode = graph_->GetNode(destinationName);

				ManagedEdgeWrapper^ edge = graph_->GetEdge(sourceNode, destinationNode);
				UpdateElementData(edge);
			}
			else
			{
				String^ sourceName = parts[0];
				ManagedNodeWrapper^ sourceNode = graph_->GetNode(sourceName);

				UpdateElementData(sourceNode);
			}
		}
	}
}

System::Void MainForm::findPathButton_Click(System::Object^ sender, System::EventArgs^ e) {
	int methodIndex = System::Convert::ToInt32(findPathMethod_comboBox->SelectedValue);

	ManagedNodeWrapper^ sourceNode = graph_->GetNode(startPoint_comboBox->Text);
	ManagedNodeWrapper^ destinationNode = graph_->GetNode(endPoint_comboBox->Text);

	if (sourceNode == destinationNode) {
		MessageBox::Show("Выберите две разных вершины!");
		return;
	}

	List<ManagedNodeWrapper^>^ findedPath;

	switch (methodIndex) {
	case 0: findedPath = graph_->DijkstraShortestPath(sourceNode, destinationNode); break;
	case 1: findedPath = graph_->AStarShortestPath(sourceNode, destinationNode); break;
	case 2: findedPath = graph_->BFS(sourceNode, destinationNode); break;
	}

	String^ path = findedPath->Count > 1 ? GetPathString(findedPath) : "Путь не найден!";
	MessageBox::Show(path, "Найденный путь");
}

System::Void MainForm::equalRange_Button_Click(System::Object^ sender, System::EventArgs^ e)
{
	List<ManagedEdgeWrapper^>^ equalEdges = gcnew List<ManagedEdgeWrapper^>();
	if (graph_->GetEdges() != nullptr)
	{
		equalEdges = graph_->EqualRangeEdges(System::Convert::ToInt32(EdgeWeigh_Numeric->Value));
	}

	String^ edges;
	if (equalEdges->Count)
	{
		for each (ManagedEdgeWrapper ^ edge in equalEdges)
		{
			edges += edge->GetSource()->GetName() + " -> " + edge->GetDestination()->GetName() + "\n";
		}
		MessageBox::Show(edges);
	}
	else MessageBox::Show("Нет таких рёбер!");
	
}

Object^ MainForm::FindClickedElement(Point clickLocation, List<ManagedNodeWrapper^>^ nodes, List<ManagedEdgeWrapper^>^ edges)
{
	for each (ManagedNodeWrapper ^ node in nodes) {
		System::Drawing::Rectangle nodeRectangle(node->GetX(), node->GetY(), node->GetSize(), node->GetSize());
		if (nodeRectangle.Contains(clickLocation)) {
			return node;
		}
	}

	for each (ManagedEdgeWrapper ^ edge in edges) {
		if (IsMouseOverEdge(clickLocation, edge)) {
			return edge;
		}
	}

	return nullptr;
}

bool MainForm::IsMouseOverEdge(Point clickLocation, ManagedEdgeWrapper^ edge) 
{
	Point start = Point(edge->GetSource()->GetX() + edge->GetSource()->GetSize() / 2, edge->GetSource()->GetY() + edge->GetSource()->GetSize() / 2);
	Point end = Point(edge->GetDestination()->GetX() + edge->GetDestination()->GetSize() / 2, edge->GetDestination()->GetY() + edge->GetDestination()->GetSize() / 2);

	double sqDist = PointToSegmentSquaredDistance(clickLocation, start, end);
	int toleranceSquared = 50; // Погрешность при выделении связи

	return sqDist <= toleranceSquared;
}

double MainForm::PointToSegmentSquaredDistance(Point p, Point start, Point end) 
{
	double l2 = PointToPointSquaredDistance(start, end);
	if (l2 == 0) return PointToPointSquaredDistance(p, start);

	double t = ((p.X - start.X) * (end.X - start.X) + (p.Y - start.Y) * (end.Y - start.Y)) / l2;
	t = Math::Max(0.0, Math::Min(1.0, t));
	Point projection(start.X + t * (end.X - start.X), start.Y + t * (end.Y - start.Y));
	return PointToPointSquaredDistance(p, projection);
}

double MainForm::PointToPointSquaredDistance(Point p1, Point p2) {
	int dx = p2.X - p1.X;
	int dy = p2.Y - p1.Y;
	return dx * dx + dy * dy;
}

void MainForm::DrawArrow(Graphics^ g, Pen^ pen, PointF start, PointF end, float arrowSize, float nodeSize) {
	float dx = end.X - start.X;
	float dy = end.Y - start.Y;
	float length = Math::Sqrt(dx * dx + dy * dy);

	dx /= length;
	dy /= length;

	float offset = arrowSize;

	PointF lineEnd = PointF(end.X - dx * offset, end.Y - dy * offset);
	PointF arrowEnd = PointF(lineEnd.X - dx * nodeSize / 2, lineEnd.Y - dy * nodeSize / 2);
	PointF arrowPoint1 = PointF(arrowEnd.X - arrowSize * dx + arrowSize * dy, arrowEnd.Y - arrowSize * dy - arrowSize * dx);
	PointF arrowPoint2 = PointF(arrowEnd.X - arrowSize * dx - arrowSize * dy, arrowEnd.Y - arrowSize * dy + arrowSize * dx);
	PointF arrowPoint3 = lineEnd; // конец линии

	g->DrawLine(pen, start, lineEnd);

	array<PointF>^ arrowPoints = { lineEnd, arrowPoint1, arrowPoint2, arrowPoint3 };
	g->FillPolygon(gcnew SolidBrush(pen->Color), arrowPoints);
}

void MainForm::UpdateElementData(Object^ element)
{
	clickedElement = element;
	if (ManagedNodeWrapper^ node = dynamic_cast<ManagedNodeWrapper^>(element))
	{
		Name_Label->Text = "Имя вершины";
		Size_Label->Text = "Размер вершины";
		Name_textBox->Text = node->GetName();
		Size_numeric->Text = node->GetSize().ToString();
		colorPicker_Button->BackColor = node->GetColor();
	}
	else if (ManagedEdgeWrapper^ edge = dynamic_cast<ManagedEdgeWrapper^>(element))
	{
		Name_Label->Text = "Вес ребра";
		Size_Label->Text = "Толщина ребра";
		Name_textBox->Text = edge->GetWeight().ToString();
		Size_numeric->Text = edge->GetSize().ToString();
		links_comboBox->SelectedItem = edge->GetSource()->GetName() + " -> " + edge->GetDestination()->GetName();
		colorPicker_Button->BackColor = edge->GetColor();
	}
}

void MainForm::UpdateComboBoxes()
{
	List<String^>^ nodeNames = gcnew List<String^>();
	List<String^>^ edgePaths = gcnew List<String^>();

	// Создаем копии списков источников данных
	for each (ManagedNodeWrapper ^ node in graph_->GetNodes())
	{
		nodeNames->Add(node->GetName());
	}

	for each (ManagedEdgeWrapper ^ edge in graph_->GetEdges())
	{
		edgePaths->Add(edge->GetSource()->GetName() + " -> " + edge->GetDestination()->GetName());
	}

	// Устанавливаем копии списков источников данных для каждого comboBox
	vertices_comboBox->DataSource = gcnew List<String^>(nodeNames);
	startPoint_comboBox->DataSource = gcnew List<String^>(nodeNames);
	endPoint_comboBox->DataSource = gcnew List<String^>(nodeNames);
	links_comboBox->DataSource = gcnew List<String^>(edgePaths);

	findPathMethod_comboBox->SelectedIndex = 0;
}

void MainForm::AddNode(int x, int y) {
	List<String^>^ nodeNames = gcnew List<String^>();
	for each (ManagedNodeWrapper ^ existingNode in graph_->GetNodes()) {
		nodeNames->Add(existingNode->GetName());
	}
	int alphabetSize = 26;
	int index = nodeNames->Count;
	int iteration = index / alphabetSize;

	Char letter = (Char)('A' + (index % alphabetSize));
	String^ defaultName = "Node" + (iteration > 0 ? iteration.ToString() : "") + letter;

	while (nodeNames->Contains(defaultName)) {
		index++;
		iteration = index / alphabetSize;
		letter = (Char)('A' + (index % alphabetSize));
		defaultName = "Node" + (iteration > 0 ? iteration.ToString() : "") + letter;
	}

	double defaultRadius = 30;
	COLORREF defaultColor = RGB(255, 0, 0);
	graph_->AddNode(defaultName, x - defaultRadius / 2, y - defaultRadius / 2, defaultRadius, defaultColor);

	UpdateComboBoxes();
}

void MainForm::AddEdge(int x, int y) {
	Object^ element = FindClickedElement(Point(x, y), graph_->GetNodes(), graph_->GetEdges());
	if (element != nullptr) {
		ManagedNodeWrapper^ clickedNode = dynamic_cast<ManagedNodeWrapper^>(element);
		ManagedEdgeWrapper^ clickedEdge = dynamic_cast<ManagedEdgeWrapper^>(element);
		if (clickedNode != nullptr && firstSelectedNode == nullptr) {
			firstSelectedNode = clickedNode;
		}
		else if (firstSelectedNode != nullptr && clickedNode != nullptr) {
			graph_->AddEdge(firstSelectedNode->GetName(), clickedNode->GetName(), 1, 3, RGB(150, 150, 150));
			firstSelectedNode = nullptr;
		}
	}
	UpdateComboBoxes();
}

void MainForm::DeleteElement(int x, int y) {
	Object^ element = FindClickedElement(Point(x, y), graph_->GetNodes(), graph_->GetEdges());
	if (element != nullptr) {
		ManagedNodeWrapper^ clickedNode = dynamic_cast<ManagedNodeWrapper^>(element);
		ManagedEdgeWrapper^ clickedEdge = dynamic_cast<ManagedEdgeWrapper^>(element);
		if (clickedNode != nullptr) {
			graph_->removeNode(clickedNode);
		}
		else if (clickedEdge != nullptr) {
			graph_->removeEdge(clickedEdge);
		}
	}
	UpdateComboBoxes();
}

String^ MainForm::GetPathString(List<ManagedNodeWrapper^>^ path) {
	String^ result;
	for (int i = 0; i < path->Count; i++) {
		result += path[i]->GetName();
		if (i < path->Count - 1) {
			ManagedEdgeWrapper^ connectingEdge = graph_->GetEdge(path[i], path[i + 1]);
			result += " --( " + connectingEdge->GetWeight() + " )--> ";
		}
	}
	return result;
}

void MainForm::GenerateRandomGraph()
{
	Random^ rand = gcnew Random();
	int canvasWidth = mainCanvas->Width;
	int canvasHeight = mainCanvas->Height;

	// Генерация случайных вершин
	int numNodes = rand->Next(5, 15); // Случайное количество вершин от 5 до 15
	for (int i = 0; i < numNodes; i++)
	{
		int x = rand->Next(20, canvasWidth - 20); // Случайная координата x
		int y = rand->Next(20, canvasHeight - 20); // Случайная координата y
		int size = rand->Next(20, 50); // Случайный размер вершины

		graph_->AddNode("Node" + i.ToString(), x, y, size, RGB(rand->Next(256), rand->Next(256), rand->Next(256)));
	}

	// Генерация случайных рёбер
	for each (ManagedNodeWrapper ^ node in graph_->GetNodes())
	{
		int numEdges = rand->Next(1, 4); // Случайное количество рёбер у каждой вершины от 1 до 3
		for (int i = 0; i < numEdges; i++)
		{
			ManagedNodeWrapper^ targetNode = graph_->GetNodes()[rand->Next(graph_->GetNodes()->Count)]; // Случайная вершина для соединения
			if (node != targetNode) // Проверка на совпадение вершин и наличие ребра
			{
				graph_->AddEdge(node->GetName(), targetNode->GetName(), rand->Next(1, 10), 1, RGB(rand->Next(256), rand->Next(256), rand->Next(256)));
			}
		}
	}

	// Обновление отображения на форме
	mainCanvas->Invalidate();
}