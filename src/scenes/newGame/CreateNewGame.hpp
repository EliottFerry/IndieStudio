/*
** EPITECH PROJECT, 2021
** CreateNewGame.hpp
** File description:
** CreateNewGame.hpp
*/

#ifndef CREATENEWGAME_HPP
#define CREATENEWGAME_HPP

#define NB_PERSO 8
#define PANCARTE 1

#include <iostream>
#include "raylib.h"
#include "../AScene.hpp"
#include "../SceneManager.hpp"
#include "../../ECS/Components.hpp"
#include "../../ECS/ECS.hpp"
#include "../inGame/Game.hpp"
#include "../mainMenu/Menu.hpp"

namespace Indie {

    class CreateNewGame : public Indie::AScene {
        public:
            CreateNewGame(Indie::SceneManager& manager);
            ~CreateNewGame();
            bool update(double time) override;
            void draw() override;
            /*! The function to add a new player, by giving his position, and a list of entity. */
            void addNewPlayer(Vector3, std::list<std::reference_wrapper<Indie::Entity>>&);
            /*! The function to animate all the player. */
            void animateAllPlayer();
            /*! The function to check if a gamepad is plugged in.*/
            void checkGamePad();
            /*! The function to change the selected champion with the keyboard. */
            void changeChampionKeyboard();
            /*! The function to change the selected champion with the controller. */
            void changeChampionGamepad();
            /*! The function to load all the player model. */
            void createAndchangePlayer(Vector3, std::string, std::list<std::reference_wrapper<Indie::Entity>>&);
            /*! The function to set a specific button drawable. */
            void setDrawableThisButton(int, bool);
            /*! The function to check if the player have selected his character. */
            bool manageSelectedKey();
            /*! The function to create the pancarte with the text in it. */
            void createPancarteWithtext();
            /*! The function to create a brand new player. As parameter, it take his position, his name, a list of entity, the path to his model, his texture, his animation, his scale and his name. */
            void createNewPlayer(Vector3, std::string, std::list<std::reference_wrapper<Indie::Entity>>&, std::string, std::string, std::string, Vector3, std::string);
        protected:
        private:
            /*! The camera entity of the scene. */
            Entity* _cam = 0;
            /*! The list of entity for the keyboard player. */
            std::list<std::reference_wrapper<Indie::Entity>> _Player;
            /*! The list of entity for the controller player. */
            std::list<std::reference_wrapper<Indie::Entity>> _PlayerP1;
            /*! The background of the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _background;
            /*! The list of all the button entity in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _Buttons;
            /*! List of all the text entity in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _Text;
            /*! The size of the window. */
            Vector2 _SizeWindow;
            /*! The manager of all the entity in the scene. */
            EntityManager entityManager;
            /*! The manager for all the button entity in the scene. */
            ManageButtons _buttonsManager;
            /*! the time passed in the scene. */
            double _time = 0.0;
            /*! the time passed since last switch of champion. */
            double _timeChamp = 0.0;
            /*! The number of gamepad plugged in. */
            int _nbGamePad;
            /*! The currently selected champ from the keyboard player. */
            int _selectedChamp;
            /*! The currently selected champ from the controller player. */
            int _selectedChampP1;
            /*! Is the sselected champ valided. */
            int _validSelectedChamp;
            /*! Is the champ already drawed. */
            bool _alreadyDraw;
            /*! Store the name of the player 1 */
            std::string _player1;
            /*! Store the name of the player 2 */
            std::string _player2;
            /*! Store the selected player for the 2 players. */
            std::map<int, std::string> _SelectedCharacters { { 0, "" },
                                                             { 1, "" }};
            /*! See if the controller is already plugged in. */
            int _beginCreated;
    };

};

#endif /* !CREATENEWGAME_HPP */
