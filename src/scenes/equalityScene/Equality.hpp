/*
** EPITECH PROJECT, 2021
** Equality.hpp
** File description:
** Equality.hpp
*/

#ifndef EQUALITY_HPP
#define EQUALITY_HPP

#include <iostream>
#include "raylib.h"
#include "../AScene.hpp"
#include "../SceneManager.hpp"
#include "../../ECS/Components.hpp"
#include "../../ECS/ECS.hpp"

namespace Indie {

    class Equality : public Indie::AScene {
        public:
            Equality(Indie::SceneManager& manager, std::map<int, std::string> namePlayers, int _nbPlayer);
            ~Equality();
            bool update(double time) override;
            void draw() override;
            void createAndchangePlayer(std::string, Vector3 pos);
            void createNewPlayer(Vector3, std::string, std::string, std::string, std::string, Vector3);
            void menuButton();

        protected:
        private:
            double _time = 0.0;
            Entity* _cam = 0;
            EntityManager entity;
            Vector2 _SizeWindow;
            /*! The list of all the text entity in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _Text;
            /*! The list of all the player entity in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _Player;
            /*! The list of all the image entity in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _background;
            /*! The list of all the buttons entity in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _buttons;
            bool _exit;
    };

};

#endif /* !EQUALITY_HPP */
