/*
** EPITECH PROJECT, 2021
** B-YEP-400-NCY-4-1-indiestudio-jean.gauthier-damioli
** File description:
** Score
*/

#include "Score.hpp"

Indie::Score::Score(std::string name)
{
    _name = name;
}

Indie::Score::~Score()
{
}

std::string Indie::Score::getName()
{
    return _name;
}