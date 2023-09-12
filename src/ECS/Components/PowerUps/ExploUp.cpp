/*
** EPITECH PROJECT, 2021
** ExploUp
** File description:
** THe file to implement expoup power up
*/

#include "ExploUp.hpp"

Indie::ExploUp::ExploUp() : Indie::PowerUpComponent::PowerUpComponent("FireUp"), _addedStrenght(1), isPickedUp(false)
{
    this->setDrawable(true);
}

Indie::ExploUp::ExploUp(Indie::ModelComponent _model) : Indie::PowerUpComponent::PowerUpComponent("FireUp"), _addedStrenght(1), isPickedUp(false)
{

}

int Indie::ExploUp::getStatUp()
{
    return _addedStrenght;
}

Indie::ExploUp::~ExploUp()
{
}
