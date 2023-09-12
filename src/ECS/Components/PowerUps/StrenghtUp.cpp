/*
** EPITECH PROJECT, 2021
** StrenghtUp
** File description:
** THe file to implement wallpass powerup
*/

#include "StrenghtUp.hpp"

Indie::StrenghtUp::StrenghtUp() : Indie::PowerUpComponent::PowerUpComponent("StrenghtUp"), _isStrenghtUping(false)
{
    this->setDrawable(true);
}

Indie::StrenghtUp::StrenghtUp(Indie::ModelComponent _model) : Indie::PowerUpComponent::PowerUpComponent("StrenghtUp"), _isStrenghtUping(false), isPickedUp(false)
{

}

bool Indie::StrenghtUp::getStatUp()
{
    return _isStrenghtUping;
}

Indie::StrenghtUp::~StrenghtUp()
{
}
