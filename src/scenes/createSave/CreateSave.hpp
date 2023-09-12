/*
** EPITECH PROJECT, 2021
** CreateSave.hpp
** File description:
** CreateSave.hpp
*/

#ifndef CREATESAVE_HPP
#define CREATESAVE_HPP

#define MAX_BUTTON 5
#define MAX_CHAR 9
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
#include <ctime>
#include "../pauseMenu/Pause.hpp"
namespace Indie {

    class CreateSave : public Indie::AScene {
    public:
        CreateSave(Indie::SceneManager& manager, std::vector<Vector3>, std::vector<int>, std::vector<Vector3>, std::vector<std::string>, std::vector<float>);
        ~CreateSave();
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
        /*! Set all the button to create the CreateSave buttons. */
        void drawButtonWithText();
        /*! Set all the value in the save files. */
        bool manageSave(int b);

        /*! Go back to the menu scene. */
        void backButton();
    protected:
    private:
        int _selectedButton;
        /*! The manager of all the entity of the scene. */
        EntityManager entityManager;
        /*! The manager of all the button in the scene. */
        ManageButtons _buttonsManager;
        /*! The list who store all the text in the scene. */
        std::list<std::reference_wrapper<Indie::Entity>> _Text;
        /*! The list who store the background of the scene. */
        std::list<std::reference_wrapper<Indie::Entity>> _background;
        /*! The list who store the all the button of the scene. */
        std::list<std::reference_wrapper<Indie::Entity>> _buttons;
        /*! The list who store all the box in the scene. */
        std::list<std::reference_wrapper<Indie::Entity>> _box;
        /*! The vector who store the save file who as been parsed. */
        std::vector<std::vector<std::string>> _SavedGame;
        /*! The vector who store the save file who as not been parsed */
        std::vector<std::string> _SavedGameUnparsed;
        /*! The vector who store the position. */
        std::vector<Vector3> _statsPos;
        /*! The vector who store the position of the walls. */
        std::vector<Vector3> _wallPos;
        /*! The vector who store the name of the player. */
        std::vector<std::string> _champName;
        /*! The vector who store the stats of the players. */
        std::vector<float> _stats;
        /*! The vector who store if the player saved is alive or not. */
        std::vector<int> _alive;
        /*! The size of the window. */
        Vector2 _SizeWindow;
        /*! The name of the save */
        std::string _saveName;
        /*! The score of the saved file  */
        std::string _score;
        /*! The date when the save has been created. */
        std::string _time;
        /*! Set if the file a been saved correctly. */
        bool _save = false;
        /*! Set to true if the window needs to be left. */
        bool _IsItQuit;
    };

};
#endif /* !CreateSave_HPP */
