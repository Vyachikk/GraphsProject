#ifndef NODE_H
#define NODE_H

#include <Windows.h> // ƒл€ COLORREF
#include "GraphElement.h"
#include <string>

//  ласс, представл€ющий вершину графа
class __declspec(dllexport) Node : public GraphElement {
public:
    Node(const std::string& name, int x, int y, int size, COLORREF color);

    const std::string& getName() const;
    void setName(const std::string& newName);

    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

private:
    std::string name_;
    int x_;
    int y_;
};

#endif // NODE_H