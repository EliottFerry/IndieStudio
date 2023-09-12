/*
** EPITECH PROJECT, 2021
** Game.hpp
** File description:
** Game.hpp
*/

#ifndef GAME_HPP
#define GAME_HPP

#define MAX_POWERUP 4

#include <iostream>
#include <fstream>
#include <iterator>
#include <list>
#include <string>
#include "raylib.h"
#include "../AScene.hpp"
#include "../SceneManager.hpp"
#include "../../ECS/Components.hpp"
#include "../../ECS/ECS.hpp"
#include "../pauseMenu/Pause.hpp"
#include "../finishGame/FinishGame.hpp"
#include "../newGame/CreateNewGame.hpp"
#include "../equalityScene/Equality.hpp"

namespace Indie {

    class Game : public Indie::AScene {
        public:
            /*! Creator of the map game, will create basic camera and map for the game */
            Game(Indie::SceneManager& manager, int nbPlayers, std::map<int, std::string> _SelectedCharacters);
            Game(Indie::SceneManager& manager);
            Game(Indie::SceneManager& manager, std::vector<Vector3> ppos, std::vector<Vector3> wpos, int nbPlayers, std::map<int, std::string> _SelectedCharacters, std::vector<std::string>, std::vector<std::vector<float>>);
            ~Game();

            /*! Update the map */
            bool update(double time) override;

            /*! Draw the map */
            void draw() override;

            /*!  Create 3D model for the breakable wall */
            void create3DMap(std::string _file);

            /*!  Get the map of 3D object */
            std::vector<Indie::ModelComponent> get3DMap();
            void createNewPlayer(std::map<int, std::string> _SelectedCharacters);
            void createNewPlayer(std::map<int, std::string> _SelectedCharacters, size_t size);

            /*! Create a new player */
            void create3DMap(std::vector<Vector3> wallposition);
            void spawningPowerUps(std::list<std::reference_wrapper<Indie::Entity>>::iterator wall);
            void changeScene();
        protected:
        private:
            void getExplosionAndBomb();

            void ManageExplosion();

            void InitPowerUpModel();

            void CheckPowerUpTaken();

            void countDown();

            void ShowScoreBoard();

            void CreateScoreBoard();

            EntityManager entity;
            std::list<std::reference_wrapper<Indie::Entity>> _Player;
            std::list<std::reference_wrapper<Indie::Entity>> _AI;
            std::list<std::reference_wrapper<Indie::Entity>> _Wall;
            std::list<std::reference_wrapper<Indie::Entity>> _PowerUps;
            std::list<std::reference_wrapper<Indie::Entity>> _texts;
            std::list<std::reference_wrapper<Indie::Entity>> _scoreBoard;
            std::list<std::reference_wrapper<Indie::Entity>> _image;
            std::vector<Indie::ModelComponent> _wall;
            std::vector<std::vector<Vector3>> _bomb;
            std::vector<std::pair<int, int>> _capacity;
            std::map<std::string, ModelComponent> _PowerUpAvailable;
            Entity* _cam = 0;
            double _time = 0.0;
            std::vector<Vector3> _posWall;
            int menu = 0;
            std::vector<std::vector<Vector3>> _explo;
            bool InMovement = false;
            std::string BigBrainMove = "";
            int _Omegabrain;
            std::list<std::reference_wrapper<Indie::Entity>> _background;
            Vector2 _SizeWindow;
            int _Winners;
            int _NbPlayers;
            float globalTime = 0.0f;
            std::vector<std::vector<float>> _statOfEv;
            enum {
                BOMB_UP = 1,
                SPEED_UP,
                WALL_PASS,
                EXPLO_UP,
            };
            std::map<int, std::string> _SelectedPlayers;
            int state = 0;
            int _GameTime = 179;
            float _GameTimePassed = 0;
            std::string _ActualTime;
    };

};

#endif /* !GAME_HPP */
