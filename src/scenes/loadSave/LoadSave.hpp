/*
** EPITECH PROJECT, 2021
** LoadSave.hpp
** File description:
** LoadSave.hpp
*/

#ifndef LOADSAVE_HPP
#define LOADSAVE_HPP

#define MAX_BUTTON 5

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

namespace Indie {

    class LoadSave : public Indie::AScene {
        public:
            LoadSave(Indie::SceneManager& manager);
            ~LoadSave();
            /*! Update the current scene. */
            bool update(double time) override;
            /*! Draw the current scene. */
            void draw() override;
            /*! Store all the save in a vector. */
            void searchSaved();
            /*! Split the save string in words. */
            std::vector<std::string> splitStr(std::string str, char separate);
            /*! Empty function :thinking:. */
            void changeValueAndScene();
            /*! Set all the button to create the loadSave buttons. */
            void drawButtonWithText();
            void manageSave(int b);
            /*! Split a string to a Vector3. */
            Vector3 splitStrToVector(std::string str, char separate);
            /*! Function to call when he back button is pressed */
            void backButton();
            /*! Split a string to a vector of float. */
            std::vector<float> splitStrToFloat(std::string str, char separate); 
        protected:
        private:
            int _selectedButton;
            /*! The manager for all the entity in the scene. */
            EntityManager entityManager;
            /*! The manager for all the button in the scene. */
            ManageButtons _buttonsManager;
            /*! The list for all the text entity in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _Text;
            /*! The background of the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _background;
            /*! The list of all the button entity in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _buttons;
            /*! The data of the save file. */
            std::vector<std::vector<std::string>> _SavedGame;
            /*! The size of the window. */
            Vector2 _SizeWindow;

            /*! Players position.*/
            std::vector<Vector3> ppos;
            /*! Walls position.*/
            std::vector<Vector3> wpos;
            /*! Is the scene left. */
            bool _IsItQuit;
    };

};
#endif /* !LOADSAVE_HPP */
