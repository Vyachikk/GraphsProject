#include "ManagedEdgeWrapper.h"

ManagedEdgeWrapper::ManagedEdgeWrapper(ManagedNodeWrapper^ source, ManagedNodeWrapper^ destination, int weight, int size, COLORREF color)
{
    edge_ = new Edge(source->GetNativePointer(), destination->GetNativePointer(), weight, size, color);
}

ManagedEdgeWrapper::ManagedEdgeWrapper(Edge* edge)
{
    edge_ = new Edge(edge->getSource(), edge->getDestination(), edge->getWeight(), edge->getSize(), edge->getColor());
}

ManagedEdgeWrapper::~ManagedEdgeWrapper()
{
    delete edge_;
}

Edge* ManagedEdgeWrapper::GetNativePointer()
{
    return edge_;
}

ManagedNodeWrapper^ ManagedEdgeWrapper::GetSource()
{
    return gcnew ManagedNodeWrapper(edge_->getSource());
}

void ManagedEdgeWrapper::SetSource(ManagedNodeWrapper^ value)
{
    edge_->setSource(value->GetNativePointer());
}

ManagedNodeWrapper^ ManagedEdgeWrapper::GetDestination()
{
    return gcnew ManagedNodeWrapper(edge_->getDestination());
}

void ManagedEdgeWrapper::SetDestination(ManagedNodeWrapper^ value)
{
    edge_->setDestination(value->GetNativePointer());
}

int ManagedEdgeWrapper::GetWeight()
{
    return edge_->getWeight();
}

void ManagedEdgeWrapper::SetWeight(int value)
{
    edge_->setWeight(value);
}

Color ManagedEdgeWrapper::GetColor()
{
    // Получаем значения красного, зеленого и синего компонентов из COLORREF
    BYTE red = GetRValue(edge_->getColor());
    BYTE green = GetGValue(edge_->getColor());
    BYTE blue = GetBValue(edge_->getColor());

    // Создаем и возвращаем объект Color
    return Color::FromArgb(red, green, blue);
}

Color ManagedEdgeWrapper::GetSelectedColor()
{
    // Получаем значения красного, зеленого и синего компонентов из COLORREF
    BYTE red = GetRValue(edge_->getSelectedColor());
    BYTE green = GetGValue(edge_->getSelectedColor());
    BYTE blue = GetBValue(edge_->getSelectedColor());

    // Создаем и возвращаем объект Color
    return Color::FromArgb(red, green, blue);
}

void ManagedEdgeWrapper::SetColor(COLORREF value)
{
    edge_->setColor(value);
}

int ManagedEdgeWrapper::GetSize()
{
    return edge_->getSize();
}

void ManagedEdgeWrapper::SetSize(int value)
{
    edge_->setSize(value);
}

bool ManagedEdgeWrapper::GetSelection()
{
    return edge_->getSelection();
}

void ManagedEdgeWrapper::SetSelection(bool value)
{
    edge_->setSelection(value);
}
