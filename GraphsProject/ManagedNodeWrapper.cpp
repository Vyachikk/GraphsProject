#include "ManagedNodeWrapper.h"

ManagedNodeWrapper::ManagedNodeWrapper(String^ name, int x, int y, int size, COLORREF color)
{
    node_ = new Node(msclr::interop::marshal_as<std::string>(name), x, y, size, color);
}

ManagedNodeWrapper::ManagedNodeWrapper(Node* node)
{
    node_ = node;
}

ManagedNodeWrapper::~ManagedNodeWrapper()
{
    delete node_;
}

Node* ManagedNodeWrapper::GetNativePointer()
{
    return node_;
}

String^ ManagedNodeWrapper::GetName()
{
    return gcnew String(node_->getName().c_str());
}

void ManagedNodeWrapper::SetName(String^ newName)
{
    node_->setName(msclr::interop::marshal_as<std::string>(newName));
}

int ManagedNodeWrapper::GetX()
{
    return node_->getX();
}

void ManagedNodeWrapper::SetX(int value)
{
    node_->setX(value);
}

int ManagedNodeWrapper::GetY()
{
    return node_->getY();
}

void ManagedNodeWrapper::SetY(int value)
{
    node_->setY(value);
}

int ManagedNodeWrapper::GetSize()
{
    return node_->getSize();
}

void ManagedNodeWrapper::SetSize(int value)
{
    node_->setSize(value);
}

Color ManagedNodeWrapper::GetColor()
{
    // Получаем значения красного, зеленого и синего компонентов из COLORREF
    BYTE red = GetRValue(node_->getColor());
    BYTE green = GetGValue(node_->getColor());
    BYTE blue = GetBValue(node_->getColor());

    // Создаем и возвращаем объект Color
    return Color::FromArgb(red, green, blue);
}

Color ManagedNodeWrapper::GetSelectedColor()
{
    // Получаем значения красного, зеленого и синего компонентов из COLORREF
    BYTE red = GetRValue(node_->getSelectedColor());
    BYTE green = GetGValue(node_->getSelectedColor());
    BYTE blue = GetBValue(node_->getSelectedColor());

    // Создаем и возвращаем объект Color
    return Color::FromArgb(red, green, blue);
}


void ManagedNodeWrapper::SetColor(COLORREF value)
{
    node_->setColor(value);
}

bool ManagedNodeWrapper::GetSelection()
{
    return node_->getSelection();
}

void ManagedNodeWrapper::SetSelection(bool value)
{
    node_->setSelection(value);
}
