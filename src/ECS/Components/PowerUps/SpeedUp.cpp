/*
** EPITECH PROJECT, 2021
** SpeedUp
** File description:
** The file to implement the speedup powerup
*/

#include "SpeedUp.hpp"

Indie::SpeedUp::SpeedUp() : Indie::PowerUpComponent::PowerUpComponent("SpeedUp"), _addedSpeed(0.1f)
{
    this->setDrawable(true);
}

Indie::SpeedUp::SpeedUp(Indie::ModelComponent _model) : Indie::PowerUpComponent::PowerUpComponent("SpeedUp"), _addedSpeed(0.1f), isPickedUp(false)
{

}

float Indie::SpeedUp::getStatUp()
{
    return _addedSpeed;
}

Indie::SpeedUp::~SpeedUp()
{
}
