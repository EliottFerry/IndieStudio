/*
** EPITECH PROJECT, 2021
** BombUp
** File description:
** The file to implement the bomb up powerUp
*/

#include "BombUp.hpp"

Indie::BombUp::BombUp() : Indie::PowerUpComponent::PowerUpComponent("BombUp"), isPickedUp(false), _addedBomb(1)
{
    setDrawable(true);
}

Indie::BombUp::BombUp(Indie::ModelComponent _model) : Indie::PowerUpComponent::PowerUpComponent("BombUp"), isPickedUp(false), _addedBomb(1)
{

}

int Indie::BombUp::getStatUp()
{
    return _addedBomb;
}

Indie::BombUp::~BombUp()
{
}
