/*
** EPITECH PROJECT, 2021
** SceneManager.cpp
** File description:
** SceneManager.cpp
*/

#include "SceneManager.hpp"
#include <iostream>
#include "raylib.h"

Indie::SceneManager::SceneManager() : Indie::AScene::AScene(_manager)
{
}

bool Indie::SceneManager::update(double time)
{
    /*! check if the stack of the scenes is not empty */
    if (Scenes.empty())
        return false;

    /*! call the function to display the current scene */
    return Scenes.top()->update(time);
}

void Indie::SceneManager::draw()
{
    /*! check if the stack of the scenes is not empty */
    if (Scenes.empty())
        return;

    ClearBackground(RAYWHITE);

    /*! call the function to draw the current scene */
    BeginDrawing();
    Scenes.top()->draw();
    EndDrawing();
}