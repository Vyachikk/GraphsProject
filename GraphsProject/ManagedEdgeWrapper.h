#pragma once

#include "ManagedNodeWrapper.h"
#include "../GraphDLL/Edge.h"

using namespace System;
using namespace System::Drawing;

// Оболочка для неуправляемого класса Edge
public ref class ManagedEdgeWrapper
{
public:
    ManagedEdgeWrapper(ManagedNodeWrapper^ source, ManagedNodeWrapper^ destination, int weight, int size, COLORREF color);
    ManagedEdgeWrapper(Edge* edge);
    ~ManagedEdgeWrapper();

    Edge* GetNativePointer();

    ManagedNodeWrapper^ GetSource();
    void SetSource(ManagedNodeWrapper^ value);
    ManagedNodeWrapper^ GetDestination();
    void SetDestination(ManagedNodeWrapper^ value);
    int GetWeight();
    void SetWeight(int value);
    Color GetColor();
    Color GetSelectedColor();
    void SetColor(COLORREF value);
    int GetSize();
    void SetSize(int value);
    bool GetSelection();
    void SetSelection(bool value);

private:
    Edge* edge_;
};