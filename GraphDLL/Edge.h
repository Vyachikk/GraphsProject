#ifndef EDGE_H
#define EDGE_H

#include "GraphElement.h"
#include "Node.h"
#include <vector>

    // Класс, представляющий ребро между вершинами графа
class __declspec(dllexport) Edge : public GraphElement {
public:
    Edge(Node* source, Node* destination, int weight, int size, COLORREF color);

    Node* getSource() const;
    void setSource(Node* value);

    Node* getDestination() const;
    void setDestination(Node* value);

    int getWeight() const;
    void setWeight(int value);

private:
    Node* source_; // Вершина начала ребра графа
    Node* destination_; // Вершина конца ребра графа
    int weight_; // вес (рейтинг) ребра
};

#endif // EDGE_H