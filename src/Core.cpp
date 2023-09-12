/*
** EPITECH PROJECT, 2021
** B-YEP-400-NCY-4-1-indiestudio-jean.gauthier-damioli
** File description:
** Core
*/

#include "Core.hpp"
#include "ECS/ECS.hpp"
#include "ECS/Components.hpp"

Indie::Core::Core()
{
}

Indie::Core::~Core()
{
}

void Indie::Core::AddNewPlayer()
{

}

int Indie::Core::start()
{
    Indie::SceneManager Game;

    try {
        Game.ScenePush<Indie::initScene>();
        while (mainWindow.isOpen()) {
            if (Game.update(mainWindow.getElapsedTime()))
                return 0;
            Game.draw();
        }
    } catch (const std::exception &e) {
        std::cerr << "Error : " << e.what() << std::endl;
        return 84;
    }
    Game.clear();
    mainWindow.getEvent().closeMainWindow();
    return 0;
}