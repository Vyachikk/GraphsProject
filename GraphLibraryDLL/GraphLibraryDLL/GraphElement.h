#ifndef GRAPH_ELEMENT_H
#define GRAPH_ELEMENT_H

#include <Windows.h>

// Базовый абстрактный класс с общими свойствами для элементов графа
class GraphElement {
public:
    COLORREF getColor() const;
    void setColor(COLORREF value);

    COLORREF getSelectedColor();

    bool getSelection() const;
    void setSelection(bool value);

    int getSize() const;
    void setSize(int value);

protected:
    COLORREF color_; // Цвет элемента
    COLORREF selectedColor_; // Цвет выбранного элемента
    bool selected_;
    int size_;

    COLORREF calculateSelectedColor(COLORREF color);
};

#endif // GRAPH_ELEMENT_H