#include "MainForm.h"
#include <string>
#include "Graphlib.h"

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

// ��������� �����
ref struct GraphicEdge {
    int source;
    int destination;
    int rating;
    bool isSelected;
};

// ��������� ����������� �������
ref struct GraphicVertex {
    String^ name;
    Point position;
    array<GraphicEdge^>^ edges;
    bool isSelected;
};

// ��������� ��� �������� ������������ �����
ref struct GraphicGraph {
    List<GraphicVertex^>^ vertices;
};

// �������� ������������ �����
GraphicGraph^ CreateGraphicGraph() {
    GraphicGraph^ graph = gcnew GraphicGraph();
    graph->vertices = gcnew List<GraphicVertex^>();
    return graph;
}

void AddVertex(Graph* graph, std::string name, GraphicGraph^ graphicGraph) {
    // �������� ������� ������� � ����� ������ � �����
    if (findVertexIndex(graph, name) != -1) {
        MessageBox::Show("������: ������� � ����� ������ ��� ����������!");
        return;
    }

    // ����� ������� ���������� ������� � ������� ����
    addVertex(graph, name);

    // �������� ����������� �������
    GraphicVertex^ graphicVertex = gcnew GraphicVertex();
    graphicVertex->name = gcnew String(name.c_str()); // �������������� std::string � String^
    graphicVertex->position = Point(50, 50);
    graphicGraph->vertices->Add(graphicVertex);
}