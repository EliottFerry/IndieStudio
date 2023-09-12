/*
** EPITECH PROJECT, 2021
** Pause.hpp
** File description:
** Pause.hpp
*/

#ifndef PAUSE_HPP
#define PAUSE_HPP

#define MAX_BUT 3

#include <string>
#include <fstream>
#include <iostream>
#include "raylib.h"
#include "../AScene.hpp"
#include "../SceneManager.hpp"
#include "../../ECS/Components.hpp"
#include "../../ECS/ECS.hpp"
#include "../../encapsulation/Window.hpp"
#include "../../encapsulation/ManageButtons.hpp"
#include "../inGame/Game.hpp"
#include "../loadSave/LoadSave.hpp"
#include "../optionsMenu/Options.hpp"
#include "../createSave/CreateSave.hpp"
namespace Indie {

    class Pause : public Indie::AScene {
        public:
            Pause(Indie::SceneManager& manager, EntityManager& entity, std::vector<Vector3> poswall, int nbPlayers);
            ~Pause();
            bool update(double time) override;
            void draw() override;
            /*! Split a string into a vector. */
            std::vector<std::string> splitStr(std::string str, char separate);
            /*! The function to load the right scene when clicking on a button. */
            void changeValueAndScene();
            /*! The function to create all the button and text needed. */
            void drawButtonWithText();
        protected:
        private:
            /*! The manager for all the entity in the scene. */
            EntityManager entityManager;
            /*! The manager for all the button in the scene. */
            ManageButtons _buttonManager;
            /*! The list of all the text entity in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _Text;
            /*! The background of the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _background;
            /*! The list of all the button entity in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _buttons;
            /*! The save file. */
            std::vector<std::vector<std::string>> _SavedGame;
            /*! Store the name of all the champion in the game. */
            std::vector<std::string> _champName;
            /*! The position of the player. */
            std::vector<Vector3> _statsPosTmp;
            /*! The position of the breakable wall. */
            std::vector<Vector3> _tmpwallpos;
            /*! The vector of all the player alive. */
            std::vector<int> _aliveTmp;
            /*! The size of the window. */
            Vector2 _SizeWindow;
            /*! Returning to the game. */
            bool _IsItQuit = true;
            /*! Exit the game. */
            bool _exit = false;
            /*! Stats of the players. */
            std::vector<float> _statsplayers;
    };

};
#endif /* !PAUSE_HPP */
