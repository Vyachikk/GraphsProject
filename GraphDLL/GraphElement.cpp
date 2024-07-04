#include "pch.h"
#include "GraphElement.h"

COLORREF GraphElement::getColor() const {
    return color_;
}

void GraphElement::setColor(COLORREF value) {
    color_ = value;
}

COLORREF GraphElement::getSelectedColor() {
    return calculateSelectedColor(color_);
}

bool GraphElement::getSelection() const {
    return selected_;
}

void GraphElement::setSelection(bool value) {
    selected_ = value;
}

int GraphElement::getSize() const {
    return size_;
}

void GraphElement::setSize(int value) {
    size_ = value;
}

// ���������� selectedColor_ ��� ��������
COLORREF GraphElement::calculateSelectedColor(COLORREF color)
{
    BYTE red = GetRValue(color);
    BYTE green = GetGValue(color);
    BYTE blue = GetBValue(color);

    // ������ selectedColor �� 30% ������ ��������� �����
    red = (BYTE)(red * 0.7);
    green = (BYTE)(green * 0.7);
    blue = (BYTE)(blue * 0.7);

    return RGB(red, green, blue);
}