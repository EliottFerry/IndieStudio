/*
** EPITECH PROJECT, 2021
** Menu.hpp
** File description:
** Menu.hpp
*/

#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include "raylib.h"
#include "../AScene.hpp"
#include "../SceneManager.hpp"
#include "../../encapsulation/ManageButtons.hpp"
#include "../../ECS/Components.hpp"
#include "../../ECS/ECS.hpp"
#include "../loadSave/LoadSave.hpp"
#include "../loadingMenu/Loading.hpp"
#include "../optionsMenu/Options.hpp"
#include "../newGame/CreateNewGame.hpp"
#include "../creditScene/Credit.hpp"
#include "ChangePath.hpp"

extern std::string exec_path;

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB -> Not supported at this moment
    #define GLSL_VERSION            100
#endif

namespace Indie {

    class Menu : public Indie::AScene {
        public:
            /*! Creator of the menu, will create basic camera and tavern model for the menu */
            Menu(Indie::SceneManager& manager);

            ~Menu();
            bool update(double time) override;
            void draw() override;
            void setEntity(EntityManager _entity);
            /*! Go to the menu at the left of the camera position */
            void MovementMenuLeft();
            /*! Go to the next menu at the right of the camera position */
            void MovementMenuRight();
            /*! function wich change the scene when you clic on enter */
            bool changeScene();
            /*! function wich draw the text of the pancarte */
            void update3DTextSelect();
            /*! function wich change the button to choose if you want to load a game or to create a new game */
            void changeSelectedButton();

        protected:
        private:
            void eraseEntity();
            /*! The function to call when the credit button is pressed. */
            void creditButton();
            /*! The manager for all the entity in the scene. */
            EntityManager entity;
            ManageButtons _buttonManager;
            /*! The list of all the model entity in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _model;
            /*! The list of all the text entity in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _Text;
            /*! The list of all the image entity in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _Image;
            /*! The list of all the Audio entity in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _Audio;
            /*! The list of all the Button entity in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _buttons;
            /*! The camera entity of the scene. */
            Entity *_cam = 0;
            /*! The time passed in the scene. */
            double _time = 0.0;
            /*! In which menu are we */
            int menu = 0;
            /*! set at false if the camera is not in a movement, and at true if the camera move */
            bool InMovement = false;
            std::string actualText;
            std::string actualText1;
            /*! The position of the text. */
            Vector3 posText;
            /*! The size of the window. */
            Vector2 _SizeWindow;
            /*! Check if the player have selected the play button. */
            int _playSelected;
            /*! If this is true, we leave this scene to go in the credit scene. */
            bool _goingToCredits;
            int _oldPlaySelected;
            float i = -0.5f;
            float j = -1.83f;
            float k = -1.57f;
            int look = 0;
    };

};

#endif /* !MENU_HPP */
