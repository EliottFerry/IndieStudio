/*
** EPITECH PROJECT, 2021
** B-YEP-400-NCY-4-1-indiestudio-jean.gauthier-damioli
** File description:
** Core
*/

#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "raylib.h"
#include "encapsulation/Window.hpp"
#include "parsing/Parsing.hpp"
#include "scenes/SceneManager.hpp"
#include "scenes/IncludeScene.hpp"

#ifndef CORE_HPP_
#define CORE_HPP_

namespace Indie
{
    class Core {
        public:
            Core();
            ~Core();
            int start();
            void AddNewPlayer();
        protected:
        private:
            Indie::Window &mainWindow = Indie::Window::Instance();
            Indie::Event &event = Indie::Event::Instance();
    };
}

#endif /* !CORE_HPP_ */
