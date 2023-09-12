/*
** EPITECH PROJECT, 2021
** ButtonComponent
** File description:
** The file to implement all the function for a button
*/

#include "ButtonComponent.hpp"

Indie::ButtonComponent::ButtonComponent(float x, float y, Vector2 pos, bool drawable, std::function<void()> function, bool border) : _posButton(pos), _doAction(false), _drawable(drawable), _color(MAROON), _isSelected(false), _Border(border), _isOvered(false)
{
    _buttonBound.x = _posButton.x / 2.0f;
    _buttonBound.y = _posButton.y / 2.0f;
    _buttonBound.width = x;
    _buttonBound.height = y;
    _Rec = { _posButton.x / 2, _posButton.y / 2, _buttonBound.width, _buttonBound.height };
    _action = function;
}

void Indie::ButtonComponent::checkOvered()
{
    Vector2 mousePos = ::GetMousePosition();
    if (::CheckCollisionPointRec(mousePos, _buttonBound))
        _isOvered = true;
    else
        _isOvered = false;
}

void Indie::ButtonComponent::update(double time)
{
    Vector2 mousePos = ::GetMousePosition();
    _color = GRAY;
    checkOvered();
    if (::CheckCollisionPointRec(mousePos, _buttonBound) || _isSelected) {
        _isSelected = true;
        _color = DARKGRAY;
        if (::IsMouseButtonDown(MOUSE_BUTTON_LEFT) || (_isSelected && ::IsKeyDown(KEY_ENTER))) {
            _color = BEIGE;
        }
        if (::IsMouseButtonReleased(MOUSE_BUTTON_LEFT) ||  (_isSelected && ::IsKeyReleased(KEY_ENTER))) {
            _doAction = true;
        }
    }
    if (_doAction == true) {
        _action();
        _doAction = false;
    }
}

bool Indie::ButtonComponent::isSelected()
{
    return _isSelected;
}

bool Indie::ButtonComponent::isOvered()
{
    return _isOvered;
}

void Indie::ButtonComponent::draw()
{
    if (_drawable)
        ::DrawRectangle(_posButton.x / 2, _posButton.y / 2, _buttonBound.width, _buttonBound.height, _color);
    if (_Border)
        ::DrawRectangleRoundedLines(_Rec, 0, 0, 1, RAYWHITE);
}

void Indie::ButtonComponent::setSelected(bool selected)
{
    _isSelected = selected;
}

void Indie::ButtonComponent::resizeButton(float x, float y, Vector2 pos)
{
    _posButton = pos;
    _buttonBound.x = _posButton.x / 2.0f;
    _buttonBound.y = _posButton.y / 2.0f;
    _buttonBound.width = x;
    _buttonBound.height = y;
    _Rec = { _posButton.x / 2, _posButton.y / 2, _buttonBound.width, _buttonBound.height };
}

Indie::ButtonComponent::~ButtonComponent()
{
}
