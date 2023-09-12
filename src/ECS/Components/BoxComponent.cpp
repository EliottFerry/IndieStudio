/*
** EPITECH PROJECT, 2021
** BoxComponent
** File description:
** The file to implement all the function for a Box
*/

#include "BoxComponent.hpp"

Indie::BoxComponent::BoxComponent(float a, float b, float c, float d)
{
    float x = Indie::Window::Instance().getWindowSize().x;
    float y = Indie::Window::Instance().getWindowSize().y;
    textbox = {(x - c)/ 2, (y - d) / 2, c, d};
    _drawable = false;
}

void Indie::BoxComponent::checkOvered()
{
    Vector2 mousePos = ::GetMousePosition();
    if (::CheckCollisionPointRec(mousePos, _BoxBound))
        _isOvered = true;
    else
        _isOvered = false;
}

void Indie::BoxComponent::update(double time)
{

    _color = GRAY;
    checkOvered();
   
    if (_doAction == true) {
        _action();
        _doAction = false;
    }
}

Vector2 Indie::BoxComponent::getPosition()
{
    Vector2 tmp = { textbox.x, textbox.y };
    return (tmp);
}

bool Indie::BoxComponent::isSelected()
{
    return _isSelected;
}

bool Indie::BoxComponent::isDrawn()
{
    return _drawable;
}

bool Indie::BoxComponent::isOvered()
{
    return _isOvered;
}

void Indie::BoxComponent::draw()
{
    if (_drawable == true)
        ::DrawRectangleRec(textbox, WHITE);
}

void Indie::BoxComponent::mustDraw()
{
    if (_drawable == false)
        _drawable = true;
    else
        _drawable = false;
}

void Indie::BoxComponent::setSelected(bool selected)
{
    _isSelected = selected;
}

char Indie::BoxComponent::getChar(void)
{
    return (::GetCharPressed());
}

void Indie::BoxComponent::resizeBox(float x, float y, Vector2 pos)
{
    _posBox = pos;
    _BoxBound.x = _posBox.x / 2.0f;
    _BoxBound.y = _posBox.y / 2.0f;
    _BoxBound.width = x;
    _BoxBound.height = y;
    _Rec = { _posBox.x / 2, _posBox.y / 2, _BoxBound.width, _BoxBound.height };
}

Indie::BoxComponent::~BoxComponent()
{
}
