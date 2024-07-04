#pragma once

#include <msclr/marshal_cppstd.h>
#include "../GraphDLL/Node.h"

using namespace System;
using namespace System::Drawing;

// Оболочка для неуправляемого класса Node
public ref class ManagedNodeWrapper
{
public:
    ManagedNodeWrapper(String^ name, int x, int y, int size, COLORREF color);
    ManagedNodeWrapper(Node* node);
    ~ManagedNodeWrapper();

    Node* GetNativePointer();

    String^ GetName();
    void SetName(String^ newName);
    int GetX();
    void SetX(int value);
    int GetY();
    void SetY(int value);
    int GetSize();
    void SetSize(int value);
    Color GetColor();
    void SetColor(COLORREF value);
    Color GetSelectedColor();
    bool GetSelection();
    void SetSelection(bool value);

private:
    Node* node_;
};
