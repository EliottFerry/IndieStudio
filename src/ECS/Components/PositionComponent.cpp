/*
** EPITECH PROJECT, 2021
** Compoenets
** File description:
** File to create all the function of the component hpp file
*/

#include "PositionComponent.hpp"

void Indie::PositionComponent::init()
{
    _pos.x = 0;
    _pos.y = 0;
    _pos.z = 0;
}

Vector3 Indie::PositionComponent::getPos()
{
    return _pos;
}

void Indie::PositionComponent::setPos(float x, float y, float z)
{
    _pos.x = x;
    _pos.y = y;
    _pos.z = z;
}

Indie::PositionComponent::PositionComponent()
{
}

Indie::PositionComponent::~PositionComponent()
{
}
