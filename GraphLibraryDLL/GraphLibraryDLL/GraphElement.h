#ifndef GRAPH_ELEMENT_H
#define GRAPH_ELEMENT_H

#include <Windows.h>

// ������� ����������� ����� � ������ ���������� ��� ��������� �����
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
    COLORREF color_; // ���� ��������
    COLORREF selectedColor_; // ���� ���������� ��������
    bool selected_;
    int size_;

    COLORREF calculateSelectedColor(COLORREF color);
};

#endif // GRAPH_ELEMENT_H