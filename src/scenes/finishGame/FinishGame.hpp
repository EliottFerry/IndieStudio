/*
** EPITECH PROJECT, 2021
** FinishGame.hpp
** File description:
** FinishGame.hpp
*/

#ifndef FINISHGAME_HPP
#define FINISHGAME_HPP

#include <iostream>
#include "raylib.h"
#include "../AScene.hpp"
#include "../SceneManager.hpp"
#include "../inGame/Game.hpp"
#include "../../ECS/Components.hpp"
#include "../../ECS/ECS.hpp"
#include "../../encapsulation/ManageButtons.hpp"

namespace Indie {

    class FinishGame : public Indie::AScene {
        public:
            FinishGame(Indie::SceneManager& manager, std::map<int, std::string> namePlayers, int _nbPlayer);
            FinishGame(Indie::SceneManager& manager, std::string nameWiner, int _nbPlayerWiner);
            ~FinishGame();
            bool update(double time) override;
            void draw() override;
            /*! Generic function to set wich character is selected. */
            void createAndchangePlayer(std::string, Vector3 pos);
            /*! Generic function to create a new player. */
            void createNewPlayer(Vector3, std::string, std::string, std::string, std::string, Vector3);
            /*! Function to see if the button to go to the menu is click. */
            void menuButton();

        protected:
        private:
            double _time = 0.0;
            Entity* _cam = 0;
            EntityManager entity;
            Vector2 _SizeWindow;
            ManageButtons _buttonsManagers;
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

#endif /* !FINISHGAME_HPP */
