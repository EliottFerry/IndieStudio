/*
** EPITECH PROJECT, 2021
** Loading.hpp
** File description:
** Loading.hpp
*/

#ifndef LOADING_HPP
#define LOADING_HPP

#include <iostream>
#include "raylib.h"
#include "../AScene.hpp"
#include "../SceneManager.hpp"
#include "../inGame/Game.hpp"
#include "../../ECS/Components.hpp"
#include "../../ECS/ECS.hpp"
#include "../loadSave/LoadSave.hpp"

namespace Indie {

    class Loading : public Indie::AScene {
        public:
            Loading(Indie::SceneManager& manager, std::string nextScene);
            Loading(Indie::SceneManager& manager, std::string nextScene, int nbPlayers, std::map<int, std::string> _SelectedCharacters);
            ~Loading();
            bool update(double time) override;
            void draw() override;
        protected:
        private:
            int framesCounter;
            /*! The string who store the text to draw. */
            std::string loadingText;
            /*! The entity manager for all the entity in the scene. */
            EntityManager entityManager;
            /*! The list who store all the text entities. */
            std::list<std::reference_wrapper<Indie::Entity>> _Text;
            /*! Store the next scene to load. */
            std::string _nextScene;
            /*! Transfert number of players. */
            int _nbPlayers;
            /*! Transfert assets of players. */
            std::map<int, std::string> _SelectedPlayers;
    };

};

#endif /* !LOADING_HPP */
