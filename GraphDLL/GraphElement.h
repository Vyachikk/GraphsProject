#ifndef GRAPH_ELEMENT_H
#define GRAPH_ELEMENT_H

#include <Windows.h>

// ������� ����������� ����� � ������ ���������� ��� ��������� �����
class GraphElement {
public:
    COLORREF __declspec(dllexport) getColor() const;
    void __declspec(dllexport) setColor(COLORREF value);

    COLORREF __declspec(dllexport) getSelectedColor();

    bool __declspec(dllexport) getSelection() const;
    void __declspec(dllexport) setSelection(bool value);

    int __declspec(dllexport) getSize() const;
    void __declspec(dllexport) setSize(int value);

protected:
    COLORREF color_; // ���� ��������
    COLORREF selectedColor_; // ���� ���������� ��������
    bool selected_;
    int size_;

    COLORREF calculateSelectedColor(COLORREF color);
};

#endif // GRAPH_ELEMENT_H