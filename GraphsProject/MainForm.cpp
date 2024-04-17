#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace GraphsProject;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MainForm);

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

	for each (Edge ^ edge in graph_->getEdges()) {
		Point startPoint(edge->Source->X + edge->Source->Size / 2, edge->Source->Y + edge->Source->Size / 2);
		Point endPoint(edge->Destination->X + edge->Destination->Size / 2, edge->Destination->Y + edge->Destination->Size / 2);

		Color EdgeColor = Color::FromArgb(GetRValue(edge->Color), GetGValue(edge->Color), GetBValue(edge->Color));
		Color EdgeSelectedColor = Color::FromArgb(GetRValue(edge->SelectedColor), GetGValue(edge->SelectedColor), GetBValue(edge->SelectedColor));

		Pen^ pen = edge->Selection ? gcnew Pen(EdgeSelectedColor) : gcnew Pen(EdgeColor);

		pen->Width = edge->Thickness;

		DrawArrow(g, pen, startPoint, endPoint, edge->Thickness + 5, edge->Destination->Size);

		delete pen;
	}

	for each (Node ^ node in graph_->getNodes()) {
		Color nodeColor = Color::FromArgb(GetRValue(node->Color), GetGValue(node->Color), GetBValue(node->Color));
		Color nodeSelectedColor = Color::FromArgb(GetRValue(node->SelectedColor), GetGValue(node->SelectedColor), GetBValue(node->SelectedColor));

		SolidBrush^ brush = gcnew SolidBrush(node->Selection ? nodeSelectedColor : nodeColor);

		g->FillEllipse(brush, (int)node->X, (int)node->Y, node->Size, node->Size);
		delete brush;
	}
}

System::Void MainForm::mainCanvas_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	if (!addNode && !addLink && !deleteElements) {
		Object^ element = FindClickedElement(Point(e->X, e->Y), graph_->getNodes(), graph_->getEdges());
		if (element != nullptr) {
			clickedElement = element;
			if (Node^ clickedNode = dynamic_cast<Node^>(element)) {
				UpdateElementData(clickedNode);
				movingNode = clickedNode;
				vertices_comboBox->SelectedItem = clickedNode->Name;
			}
			else if (Edge^ clickedEdge = dynamic_cast<Edge^>(element)) {
				UpdateElementData(clickedEdge);
				links_comboBox->SelectedItem = clickedEdge->Source->Name + " -> " + clickedEdge->Destination->Name;
			}
		}
	}
}

System::Void MainForm::mainCanvas_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	for each (Edge ^ edge in graph_->getEdges()) {
		bool isMouseOverEdge = IsMouseOverEdge(e->Location, edge);
		if (isMouseOverEdge != edge->Selection) {
			edge->Selection = isMouseOverEdge;
		}
	}

	for each (Node ^ node in graph_->getNodes()) {
		bool isMouseOverNode = (e->X >= node->X && e->X <= node->X + node->Size &&
			e->Y >= node->Y && e->Y <= node->Y + node->Size);
		if (isMouseOverNode != node->Selection) {
			node->Selection = isMouseOverNode;
		}
	}

	if (!addNode && !addLink && movingNode != nullptr) {
		int newX = e->X - movingNode->Size / 2;
		int newY = e->Y - movingNode->Size / 2;

		movingNode->X = newX;
		movingNode->Y = newY;

		for each (Edge ^ edge in graph_->getEdges()) {
			if (edge->Source == movingNode) {
				edge->Source->X = newX;
				edge->Source->Y = newY;
			}
			else if (edge->Destination == movingNode) {
				edge->Destination->X = newX;
				edge->Destination->Y = newY;
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
			Node^ clickedNode = dynamic_cast<Node^>(clickedElement);
			Edge^ clickedEdge = dynamic_cast<Edge^>(clickedElement);
			COLORREF colorRef = RGB(selectedColor.R, selectedColor.G, selectedColor.B);
			if (clickedNode != nullptr)
				clickedNode->Color = colorRef;
			else if (clickedEdge != nullptr)
				clickedEdge->Color = colorRef;
			mainCanvas->Invalidate();
		}
	}
}

System::Void MainForm::Name_textBox_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (clickedElement != nullptr) {
		Node^ clickedNode = dynamic_cast<Node^>(clickedElement);
		Edge^ clickedEdge = dynamic_cast<Edge^>(clickedElement);

		if (clickedNode != nullptr) {
			clickedNode->Name = Name_textBox->Text;
		}
		else if (clickedEdge != nullptr) {
			try {
				clickedEdge->Weight = System::Convert::ToInt32(Name_textBox->Text);
			}
			catch (System::FormatException^) {
			}
		}
	}
}

System::Void MainForm::Size_numeric_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (clickedElement != nullptr) {
		Node^ clickedNode = dynamic_cast<Node^>(clickedElement);
		Edge^ clickedEdge = dynamic_cast<Edge^>(clickedElement);

		if (clickedNode != nullptr) {
			clickedNode->Size = System::Convert::ToInt32(Size_numeric->Value);
		}
		else if (clickedEdge != nullptr) {
			try {
				clickedEdge->Thickness = System::Convert::ToInt32(Size_numeric->Value);
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
				Node^ sourceNode = graph_->getNode(sourceName);
				Node^ destinationNode = graph_->getNode(destinationName);

				// Обновление данных для вершин
				if (comboBox == vertices_comboBox)
				{
					UpdateElementData(sourceNode);
				}
				// Обновление данных для ребер
				else if (comboBox == links_comboBox)
				{
					Edge^ edge = graph_->getEdge(sourceNode, destinationNode);
					UpdateElementData(edge);
				}
			}
		}
	}
}

Object^ MainForm::FindClickedElement(Point clickLocation, List<Node^>^ nodes, List<Edge^>^ edges) 
{
	for each (Node ^ node in nodes) {
		System::Drawing::Rectangle nodeRectangle(node->X, node->Y, node->Size, node->Size);
		if (nodeRectangle.Contains(clickLocation)) {
			return node;
		}
	}

	for each (Edge ^ edge in edges) {
		if (IsMouseOverEdge(clickLocation, edge)) {
			return edge;
		}
	}

	return nullptr;
}

bool MainForm::IsMouseOverEdge(Point clickLocation, Edge^ edge) 
{
	Point start = Point(edge->Source->X + edge->Source->Size / 2, edge->Source->Y + edge->Source->Size / 2);
	Point end = Point(edge->Destination->X + edge->Destination->Size / 2, edge->Destination->Y + edge->Destination->Size / 2);

	double sqDist = PointToSegmentSquaredDistance(clickLocation, start, end);
	int toleranceSquared = 100; // Погрешность при выделении связи

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
	if (Node^ node = dynamic_cast<Node^>(element))
	{
		Name_Label->Text = "Имя вершины";
		Size_Label->Text = "Размер вершины";
		Name_textBox->Text = node->Name;
		Size_numeric->Text = node->Size.ToString();
		colorPicker_Button->BackColor = Color::FromArgb(GetRValue(node->Color), GetGValue(node->Color), GetBValue(node->Color));
	}
	else if (Edge^ edge = dynamic_cast<Edge^>(element))
	{
		Name_Label->Text = "Вес ребра";
		Size_Label->Text = "Толщина ребра";
		Name_textBox->Text = edge->Weight.ToString();
		Size_numeric->Text = edge->Thickness.ToString();
		links_comboBox->SelectedItem = edge->Source->Name + " -> " + edge->Destination->Name;
		colorPicker_Button->BackColor = Color::FromArgb(GetRValue(edge->Color), GetGValue(edge->Color), GetBValue(edge->Color));
	}
}

void MainForm::AddNode(int x, int y) {
	List<String^>^ nodeNames = gcnew List<String^>();
	for each (Node ^ existingNode in graph_->getNodes()) {
		nodeNames->Add(existingNode->Name);
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
	Node^ node = gcnew Node(defaultName, x - defaultRadius / 2, y - defaultRadius / 2, defaultRadius, defaultColor);
	graph_->addNode(node);

	vertices_comboBox->Items->Add(node->Name);
}

void MainForm::AddEdge(int x, int y) {
	Object^ element = FindClickedElement(Point(x, y), graph_->getNodes(), graph_->getEdges());
	if (element != nullptr) {
		Node^ clickedNode = dynamic_cast<Node^>(element);
		Edge^ clickedEdge = dynamic_cast<Edge^>(element);
		if (clickedNode != nullptr && firstSelectedNode == nullptr) {
			firstSelectedNode = clickedNode;
		}
		else if (firstSelectedNode != nullptr && clickedNode != nullptr) {
			Edge^ edge = gcnew Edge(firstSelectedNode, clickedNode, 1, 3, RGB(150, 150, 150));
			graph_->addEdge(edge);
			links_comboBox->Items->Add(edge->Source->Name + " -> " + edge->Destination->Name);
			firstSelectedNode = nullptr;
		}
	}
}

void MainForm::DeleteElement(int x, int y) {
	Object^ element = FindClickedElement(Point(x, y), graph_->getNodes(), graph_->getEdges());
	if (element != nullptr) {
		Node^ clickedNode = dynamic_cast<Node^>(element);
		Edge^ clickedEdge = dynamic_cast<Edge^>(element);
		if (clickedNode != nullptr) {
			graph_->removeNode(clickedNode);
			vertices_comboBox->Items->Remove(clickedNode->Name);
		}
		else if (clickedEdge != nullptr) {
			graph_->removeEdge(clickedEdge);
			links_comboBox->Items->Remove(clickedEdge->Source->Name + " -> " + clickedEdge->Destination->Name);
		}
	}
}