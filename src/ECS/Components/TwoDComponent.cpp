/*
** EPITECH PROJECT, 2021
** TwoDComponent.cpp
** File description:
** TwoDComponent.cpp
*/

#include "TwoDComponent.hpp"

Indie::TwoDComponent::TwoDComponent(std::string PathImage, float sizeX, float sizeY, Vector2 pos) : _Pos(pos)
{
    _Background = LoadImage((exec_path + (PathImage)).c_str());
    ImageResize(&_Background, sizeX, sizeY);
    _Texture = LoadTextureFromImage(_Background);
    _drawable = true;
    _color = {255, 255, 255, 255};
    _active = true;
}

Indie::TwoDComponent::~TwoDComponent()
{
    ::UnloadTexture(_Texture);
    ::UnloadImage(_Background);
}

void Indie::TwoDComponent::draw()
{
    if (_drawable == true)
        DrawTexture(_Texture, _Pos.x, _Pos.y, _color);
}

void Indie::TwoDComponent::setDrawable(bool drawable)
{
    _drawable = drawable;
}

void Indie::TwoDComponent::update(double time)
{
    if (_active && _color.a < 255) {
        _color.a += 1;
    }
    else {
        _color.a -= 1;
        if (_color.a == 0)
            entity->destroy();
    }

}

void Indie::TwoDComponent::setAlpha(int alpha)
{
    _color.a = alpha;
}

void Indie::TwoDComponent::setPos(Vector2 pos)
{
    _Pos = pos;
}

void Indie::TwoDComponent::setInactive()
{
    _active = false;
}

Image Indie::TwoDComponent::getImage()
{
    return _Background;
}

void Indie::TwoDComponent::setSize(float x, float y)
{
    ::UnloadTexture(_Texture);
    ::ImageResize(&_Background, x, y);
    _Texture = ::LoadTextureFromImage(_Background);
}
