/*
** EPITECH PROJECT, 2021
** PowerUpComponent
** File description:
** The fil eto implement powerup
*/

#include "PowerUpComponent.hpp"

Indie::PowerUpComponent::PowerUpComponent(std::string name) : Indie::ModelComponent::ModelComponent(name)
{
    SetScale(Vector3 {0.3f, 0.3f, 0.3f});
    SetRotationAngle(180.0f);
}

void Indie::PowerUpComponent::update(double time)
{
}

void Indie::PowerUpComponent::draw()
{
    Animated();
    if (getDrawable())
        DrawModelEx(getModel(), getPos(), GetRotationAxis(), GetRotationAngle(), getScale(), WHITE);
}

Indie::PowerUpComponent::~PowerUpComponent()
{
}

void Indie::PowerUpComponent::setModelComponent(ModelComponent modelToSet)
{
    setModel(modelToSet.getModel());
    setTexture(modelToSet.getTexture());
    setAnimation(modelToSet.getAnimation());
    PlayAnimation("Idle");
}