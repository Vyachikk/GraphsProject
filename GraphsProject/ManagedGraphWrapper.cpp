#include "ManagedGraphWrapper.h"

ManagedGraphWrapper::ManagedGraphWrapper()
{
    graph_ = new Graph();
}

ManagedGraphWrapper::~ManagedGraphWrapper()
{
    graph_->~Graph();
}

void ManagedGraphWrapper::AddNode(String^ name, int x, int y, int size, COLORREF color)
{
    graph_->addNode(new Node(msclr::interop::marshal_as<std::string>(name), x, y, size, color));
}

void ManagedGraphWrapper::AddEdge(String^ sourceName, String^ destName, int weight, int size, COLORREF color)
{
    Node* source = graph_->getNode(msclr::interop::marshal_as<std::string>(sourceName));
    Node* dest = graph_->getNode(msclr::interop::marshal_as<std::string>(destName));
    if (source && dest)
    {
        graph_->addEdge(new Edge(source, dest, weight, size, color));
    }
}

List<ManagedEdgeWrapper^>^ ManagedGraphWrapper::GetEdges() {
    List<ManagedEdgeWrapper^>^ edgesList = gcnew List<ManagedEdgeWrapper^>();

    for (Edge* edge : graph_->getEdges()) {
        edgesList->Add(gcnew ManagedEdgeWrapper(edge));
    }

    return edgesList;
}

void ManagedGraphWrapper::removeEdge(ManagedEdgeWrapper^ edge)
{
    // Получаем нативный указатель на объект ребра
    Edge* nativeEdge = edge->GetNativePointer();
    // Вызываем метод removeEdge у нативного объекта Graph
    graph_->removeEdge(nativeEdge);
    // Освобождаем память, выделенную под управляемую оболочку ребра
    delete edge;
}

void ManagedGraphWrapper::removeNode(ManagedNodeWrapper^ node)
{
    Node* nativeNode = node->GetNativePointer();
    graph_->removeNode(nativeNode);
    delete node;
}

ManagedEdgeWrapper^ ManagedGraphWrapper::GetEdge(ManagedNodeWrapper^ start, ManagedNodeWrapper^ destination)
{
    Edge* edge = graph_->getEdge(start->GetNativePointer(), destination->GetNativePointer());
    if (edge != nullptr) {
        return gcnew ManagedEdgeWrapper(edge);
    }
    else {
        return nullptr;
    }
}

ManagedNodeWrapper^ ManagedGraphWrapper::GetNode(String^ name)
{
    Node* node = graph_->getNode(msclr::interop::marshal_as<std::string>(name));
    if (node != nullptr) {
        return gcnew ManagedNodeWrapper(node);
    }
    else {
        return nullptr;
    }
}

List<ManagedNodeWrapper^>^ ManagedGraphWrapper::GetNodes() {
    List<ManagedNodeWrapper^>^ nodesList = gcnew List<ManagedNodeWrapper^>();

    for (Node* node : graph_->getNodes()) {
        nodesList->Add(gcnew ManagedNodeWrapper(node));
    }

    return nodesList;
}

List<String^>^ ManagedGraphWrapper::GetNodeNames()
{
    List<String^>^ names = gcnew List<String^>();
    std::vector<Node*> nodes = graph_->getNodes();
    for (Node* node : nodes)
    {
        names->Add(gcnew String(node->getName().c_str()));
    }
    return names;
}

List<ManagedNodeWrapper^>^ ManagedGraphWrapper::DijkstraShortestPath(ManagedNodeWrapper^ source, ManagedNodeWrapper^ destination)
{
    std::vector<Node*> path = graph_->DijkstraShortestPath(source->GetNativePointer(), destination->GetNativePointer());
    List<ManagedNodeWrapper^>^ managedPath = gcnew List<ManagedNodeWrapper^>(path.size());
    for (Node* node : path) {
        managedPath->Add(gcnew ManagedNodeWrapper(node));
    }

    return managedPath;
}

List<ManagedNodeWrapper^>^ ManagedGraphWrapper::AStarShortestPath(ManagedNodeWrapper^ source, ManagedNodeWrapper^ destination)
{
    std::vector<Node*> path = graph_->AStarShortestPath(source->GetNativePointer(), destination->GetNativePointer());
    List<ManagedNodeWrapper^>^ managedPath = gcnew List<ManagedNodeWrapper^>(path.size());
    for (Node* node : path) {
        managedPath->Add(gcnew ManagedNodeWrapper(node));
    }

    return managedPath;
}

List<ManagedNodeWrapper^>^ ManagedGraphWrapper::BFS(ManagedNodeWrapper^ source, ManagedNodeWrapper^ destination)
{
    std::vector<Node*> path = graph_->BFS(source->GetNativePointer(), destination->GetNativePointer());
    List<ManagedNodeWrapper^>^ managedPath = gcnew List<ManagedNodeWrapper^>(path.size());
    for (Node* node : path) {
        managedPath->Add(gcnew ManagedNodeWrapper(node));
    }

    return managedPath;
}

List<ManagedEdgeWrapper^>^ ManagedGraphWrapper::EqualRangeEdges(int weight)
{
    std::vector<Edge*> edges = graph_->EqualRangeEdges(weight);
    List<ManagedEdgeWrapper^>^ managedEdges = gcnew List<ManagedEdgeWrapper^>(edges.size());
    for (Edge* edge : edges) {
        managedEdges->Add(gcnew ManagedEdgeWrapper(edge));
    }
    return managedEdges;
}

List<ManagedNodeWrapper^>^ ManagedGraphWrapper::SetIntersectionNodes(List<ManagedNodeWrapper^>^ nodes1, List<ManagedNodeWrapper^>^ nodes2)
{
    std::vector<Node*> nativeNodes1, nativeNodes2;
    for each (ManagedNodeWrapper ^ node in nodes1) {
        nativeNodes1.push_back(node->GetNativePointer());
    }
    for each (ManagedNodeWrapper ^ node in nodes2) {
        nativeNodes2.push_back(node->GetNativePointer());
    }

    std::vector<Node*> intersection = graph_->SetIntersectionNodes(nativeNodes1, nativeNodes2);
    List<ManagedNodeWrapper^>^ managedIntersection = gcnew List<ManagedNodeWrapper^>(intersection.size());
    for (Node* node : intersection) {
        managedIntersection->Add(gcnew ManagedNodeWrapper(node));
    }
    return managedIntersection;
}