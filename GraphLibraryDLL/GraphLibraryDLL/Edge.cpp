#include "pch.h"
#include "Edge.h"

Edge::Edge(Node* source, Node* destination, int weight, int size, COLORREF color)
    : source_(source), destination_(destination), weight_(weight) {
    size_ = size;
    color_ = color;
}

Node* Edge::getSource() const {
    return source_;
}

void Edge::setSource(Node* value) {
    source_ = value;
}

Node* Edge::getDestination() const {
    return destination_;
}

void Edge::setDestination(Node* value) {
    destination_ = value;
}

int Edge::getWeight() const {
    return weight_;
}

void Edge::setWeight(int value) {
    weight_ = value;
}