#pragma once

#include <msclr/marshal_cppstd.h>
#include "../GraphDLL/Graph.h"
#include "ManagedEdgeWrapper.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;

// Оболочка для неуправляемого класса Graph
public ref class ManagedGraphWrapper
{
public:
    ManagedGraphWrapper();
    ~ManagedGraphWrapper();

    void AddNode(String^ name, int x, int y, int size, COLORREF color);
    void AddEdge(String^ sourceName, String^ destName, int weight, int size, COLORREF color);

    void removeNode(ManagedNodeWrapper^ node);
    void removeEdge(ManagedEdgeWrapper^ edge);

    ManagedNodeWrapper^ GetNode(String^ name);
    ManagedEdgeWrapper^ GetEdge(ManagedNodeWrapper^ start, ManagedNodeWrapper^ destination);

    List<ManagedNodeWrapper^>^ DijkstraShortestPath(ManagedNodeWrapper^ source, ManagedNodeWrapper^ destination);
    List<ManagedNodeWrapper^>^ AStarShortestPath(ManagedNodeWrapper^ source, ManagedNodeWrapper^ destination);
    List<ManagedNodeWrapper^>^ BFS(ManagedNodeWrapper^ source, ManagedNodeWrapper^ destination);

    List<ManagedEdgeWrapper^>^ GetEdges();
    List<ManagedNodeWrapper^>^ GetNodes();

    List<ManagedEdgeWrapper^>^ EqualRangeEdges(int weight);
    List<ManagedNodeWrapper^>^ SetIntersectionNodes(List<ManagedNodeWrapper^>^ nodes1, List<ManagedNodeWrapper^>^ nodes2);

    List<String^>^ GetNodeNames();

private:
    Graph* graph_;
};