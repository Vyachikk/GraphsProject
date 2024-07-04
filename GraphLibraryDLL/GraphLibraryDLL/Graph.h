#ifndef GRAPH_H
#define GRAPH_H

#pragma once
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <limits>
#include "Node.h"
#include "Edge.h"

// Класс графа
class __declspec(dllexport) Graph {
public:
    Graph();
    ~Graph();

    void addNode(Node* node);
    void addEdge(Edge* edge);
    std::vector<Node*> getNodes() const;
    std::vector<Edge*> getEdges() const;

    Node* getNode(const std::string& name) const;
    Edge* getEdge(Node* start, Node* destination) const;

    void removeNode(Node* node);
    void removeEdge(Edge* edge);

    std::vector<Node*> DijkstraShortestPath(Node* source, Node* destination);
    std::vector<Node*> AStarShortestPath(Node* source, Node* destination);
    std::vector<Node*> BFS(Node* source, Node* destination);

    std::vector<Edge*> EqualRangeEdges(int weight);
    std::vector<Node*> SetIntersectionNodes(const std::vector<Node*>& nodes1, const std::vector<Node*>& nodes2);

private:
    std::vector<Node*> nodes_;
    std::vector<Edge*> edges_;
    std::map<Node*, std::vector<Edge*>*> adjacencyList_; // Список смежности
};

#endif // GRAPH_H