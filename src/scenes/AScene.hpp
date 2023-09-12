/*
** EPITECH PROJECT, 2021
** AScene.hpp
** File description:
** AScene.hpp
*/

#ifndef ASCENE_HPP
#define ASCENE_HPP

#include "IScene.hpp"
#include <iostream>
#include <filesystem>
namespace Indie {

    class SceneManager;

    class AScene : public Indie::IScene {
        public:
            AScene(Indie::SceneManager& manager);
            virtual ~AScene() = default;
            virtual bool update(double _Time) = 0;
            virtual void draw() = 0;
        protected:
            Indie::SceneManager& _manager;
        private:
    };

};

#endif /* !ASCENE_HPP */
