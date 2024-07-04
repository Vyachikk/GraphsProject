#include "pch.h"
#include "Node.h"

Node::Node(std::string& name, int x, int y, int size, COLORREF color)
    : name_(name), x_(x), y_(y) {
    size_ = size;
    color_ = color;
}

const std::string& Node::getName() const {
    return name_;
}

void Node::setName(const std::string& newName) {
    name_ = newName;
}

int Node::getX() const {
    return x_;
}

void Node::setX(int value) {
    x_ = value;
}

int Node::getY() const {
    return y_;
}

void Node::setY(int value) {
    y_ = value;
}