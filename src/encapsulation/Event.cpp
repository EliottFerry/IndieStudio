/*
** EPITECH PROJECT, 2021
** Indie
** File description:
** The .cpp file, to create all the function in the Event class
*/

#include "Event.hpp"
#include <iostream>

Indie::Event::Event()
{
}

void Indie::Event::closeMainWindow()
{
    CloseWindow();
}

std::map<std::string, int> Indie::Event::getMapInputs()
{
    return mapInputs;
}

void Indie::Event::setInputs(std::string pos, int input)
{
    mapInputs[pos] = input;
}

Indie::Event::~Event()
{
}
