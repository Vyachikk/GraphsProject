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

// Структура ребра
ref struct GraphicEdge {
    int source;
    int destination;
    int rating;
    bool isSelected;
};

// Структура графической вершины
ref struct GraphicVertex {
    String^ name;
    Point position;
    array<GraphicEdge^>^ edges;
    bool isSelected;
};

// Структура для хранения графического графа
ref struct GraphicGraph {
    List<GraphicVertex^>^ vertices;
};

// Создание графического графа
GraphicGraph^ CreateGraphicGraph() {
    GraphicGraph^ graph = gcnew GraphicGraph();
    graph->vertices = gcnew List<GraphicVertex^>();
    return graph;
}

void AddVertex(Graph* graph, std::string name, GraphicGraph^ graphicGraph) {
    // Проверка наличия вершины с таким именем в графе
    if (findVertexIndex(graph, name) != -1) {
        MessageBox::Show("Ошибка: Вершина с таким именем уже существует!");
        return;
    }

    // Вызов функции добавления вершины в обычный граф
    addVertex(graph, name);

    // Создание графической вершины
    GraphicVertex^ graphicVertex = gcnew GraphicVertex();
    graphicVertex->name = gcnew String(name.c_str()); // Преобразование std::string в String^
    graphicVertex->position = Point(50, 50);
    graphicGraph->vertices->Add(graphicVertex);
}