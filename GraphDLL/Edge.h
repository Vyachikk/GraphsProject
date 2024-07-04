#ifndef EDGE_H
#define EDGE_H

#include "GraphElement.h"
#include "Node.h"
#include <vector>

    // �����, �������������� ����� ����� ��������� �����
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
    Node* source_; // ������� ������ ����� �����
    Node* destination_; // ������� ����� ����� �����
    int weight_; // ��� (�������) �����
};

#endif // EDGE_H