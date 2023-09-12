/*
** EPITECH PROJECT, 2021
** Player
** File description:
** Player game object, to handle all player actions
*/

#include "Player.hpp"
#include "raylib.h"
#include <iostream>

Indie::Player::Player()
{
    _posPlayer = { 0.0f, 1.0f, 2.0f };
    _hp = 1;
    _stats["radius"] = 1.0;
    _stats["speed"] = 1.0;
}

Vector3 Indie::Player::getPlayerPos()
{
    return (_posPlayer);
}

void Indie::Player::movePlayer()
{
    Vector3 oldPos = _posPlayer;
    if (::IsKeyDown(KEY_RIGHT))
        _posPlayer.x += (_stats["speed"] / 10);
    if (::IsKeyDown(KEY_LEFT))
        _posPlayer.x -= (_stats["speed"] / 10);
    if (::IsKeyDown(KEY_UP))
        _posPlayer.z += (_stats["speed"] / 10);
    if (::IsKeyDown(KEY_DOWN))
        _posPlayer.z -= (_stats["speed"] / 10);
}

void Indie::Player::SetPosition(Vector3 _position)
{
    _posPlayer = _position;
}

void Indie::Player::SetModel(Indie::Models _model)
{
    _skin = _model;
}

Indie::Player::~Player()
{
}

Indie::Models Indie::Player::GetSkin()
{
    return _skin;
}