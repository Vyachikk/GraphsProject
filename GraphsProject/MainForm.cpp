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
		String^ defaultName = "Node" + graph_->getNodes()->Count;
		double defaultRadius = 30;
		COLORREF defaultColor = RGB(255, 0, 0);

		Node^ node = gcnew Node(defaultName, e->X - defaultRadius / 2, e->Y - defaultRadius / 2, defaultRadius, defaultColor);
		graph_->addNode(node);
	}
	else if (addLink) {
		Node^ clickedNode = FindClickedNode(e->Location, graph_->getNodes());
		if (firstSelectedNode == nullptr) {
			firstSelectedNode = clickedNode;
		}
		else if (firstSelectedNode != clickedNode && clickedNode != nullptr) {
			Edge^ edge = gcnew Edge(firstSelectedNode, clickedNode, 1, 3, RGB(150, 150, 150));
			graph_->addEdge(edge);
			firstSelectedNode = nullptr;
		}
	}
	else if (deleteElements) {
		Node^ clickedNode = FindClickedNode(e->Location, graph_->getNodes());
		Edge^ clickedEdge = FindClickedEdge(e->Location, graph_->getEdges());
		if (clickedNode != nullptr)
			graph_->removeNode(clickedNode);
		else if (clickedEdge != nullptr)
			graph_->removeEdge(clickedEdge);
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
		g->DrawLine(pen, startPoint, endPoint);
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
	if (!addNode || !addLink)
		movingNode = FindClickedNode(Point(e->X, e->Y), graph_->getNodes());
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

Node^ MainForm::FindClickedNode(Point clickLocation, List<Node^>^ nodes) {
	Node^ clickedNode = nullptr;
	for each (Node ^ node in nodes){
		System::Drawing::Rectangle nodeRectangle(node->X, node->Y, node->Size, node->Size);
		if (nodeRectangle.Contains(clickLocation)){
			clickedNode = node;
			break;
		}
	}
	return clickedNode;
}

Edge^ MainForm::FindClickedEdge(Point clickLocation, List<Edge^>^ edges) {
	Edge^ clickedEdge = nullptr;
	for each (Edge ^ edge in edges){
		if (IsMouseOverEdge(clickLocation, edge)){
			clickedEdge = edge;
			break;
		}
	}
	return clickedEdge;
}

bool MainForm::IsMouseOverEdge(Point clickLocation, Edge^ edge) {
	Point start = Point(edge->Source->X + edge->Source->Size / 2, edge->Source->Y + edge->Source->Size / 2);
	Point end = Point(edge->Destination->X + edge->Destination->Size / 2, edge->Destination->Y + edge->Destination->Size / 2);

	double sqDist = PointToSegmentSquaredDistance(clickLocation, start, end);
	int toleranceSquared = 100; // Погрешность при выделении связи

	return sqDist <= toleranceSquared;
}

double MainForm::PointToSegmentSquaredDistance(Point p, Point start, Point end) {
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