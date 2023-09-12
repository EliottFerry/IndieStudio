/*
** EPITECH PROJECT, 2021
** Option
** File description:
** The file to implement the scene for the option
*/

#ifndef OPTION_HPP
#define OPTION_HPP

#include "../AScene.hpp"
#include "../SceneManager.hpp"
#include "../../ECS/Components.hpp"
#include "../../encapsulation/ManageButtons.hpp"
#include "../../parsing/Parsing.hpp"
#include <unordered_map>

#define BUTTON_RETOUR 1
#define BUTTON_RESOLUTION 5
#define BUTTON_VOLUME 2
#define BUTTON_FPS 4
#define BUTTON_INPUTS 5
#define BUTTON_BEFORE_INPUTS 12

namespace Indie {
    class Options : public AScene {
        private:
            /*! Used to loop in all the button to set the right function to the right button. */
            int _nbButtonCreated;
            /*! A boolean to check if the back button has been pressed. */
            bool _backSelected;
            /*! A boolean to check if the volume has been changed, to update only the right texts. */
            bool volumeChanged;
            /*! A boolean to check if the inputs has been changed, to update only the right texts. */
            bool inputsChanged;
            /*! The size of the window in the scene. */
            Vector2 sizeWindow;
            /*! The list who store all the buttons entity of the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _allButtons;
            /*! The list who store all the text contained in the buttons of the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _textInButtons;
            /*! The list who store the background of the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _background;
            /*! The enum to get the changed input. */
            enum changedInputs {
                DOWN,
                UP,
                LEFT,
                RIGHT,
                ACTION,
            };
            /*! A map to set which input is currently changing. */
            std::unordered_map<std::string, bool> isChanging {
                { "Action", false },
                { "Right", false },
                { "Left", false },
                { "Up", false },
                { "Down", false },
            };
            /*! The vector who store the text that we will draw in the buttons.*/
            std::vector<std::string> _textButtons {
                "Back",
                "1280x720",
                "1600x900",
                "1920x1080",
                "2560x1440",
                "Fullscreen",
                "Volume Down",
                "Volume Up",
                "30FPS",
                "60FPS",
                "120FPS",
                "144FPS",
                Indie::Parsing::Instance().keyMap[Indie::Event::Instance().getMapInputs()["Down"]],
                Indie::Parsing::Instance().keyMap[Indie::Event::Instance().getMapInputs()["Up"]],
                Indie::Parsing::Instance().keyMap[Indie::Event::Instance().getMapInputs()["Left"]],
                Indie::Parsing::Instance().keyMap[Indie::Event::Instance().getMapInputs()["Right"]],
                Indie::Parsing::Instance().keyMap[Indie::Event::Instance().getMapInputs()["Action"]],
            };
            /*! The vector of function who store all the function that we will call when we press the button. */
            std::vector<std::function<void()>> _functionResolution {
                std::bind(&Options::backToMenu, this),
                std::bind(&Options::screenSizeHD, this),
                std::bind(&Options::screenSizeHDP, this),
                std::bind(&Options::screenSizeFHD, this),
                std::bind(&Options::screenSizeWQHD, this),
                std::bind(&Options::fullScreen, this),
                std::bind(&Options::setVolume, this, -5),
                std::bind(&Options::setVolume, this, 5),
                std::bind(&Options::setFramerate, this, 30),
                std::bind(&Options::setFramerate, this, 60),
                std::bind(&Options::setFramerate, this, 120),
                std::bind(&Options::setFramerate, this, 144),
                std::bind(&Options::changeDown, this),
                std::bind(&Options::changeUp, this),
                std::bind(&Options::changeLeft, this),
                std::bind(&Options::changeRight, this),
                std::bind(&Options::changeAction, this),
            };
            /*! The button manager, to handle the button action. */
            ManageButtons _buttonManager;
            /*! The entity manager, to handle all the entity. */
            EntityManager entities;

            /*! The function to change the volume of the window. */
            void setVolume(int volume);
            /*! The function to set the framerate of the window. */
            void setFramerate(int framerate);
            /*! The function to enable/disable the fullscreen. */
            void fullScreen();
            /*! The function to set the resolution to 1920x1080*/
            void screenSizeFHD();
            /*! The function to set the resolution to 1280x720*/
            void screenSizeHD();
            /*! The function to set the resolution to 1600x900*/
            void screenSizeHDP();
            /*! The function to set the resolution to 2560x1440*/
            void screenSizeWQHD();
            /*! The function to change the action button. */
            void changeAction();
            /*! The function to change the up button. */
            void changeUp();
            /*! The function to change the down button. */
            void changeDown();
            /*! The function to change the left button. */
            void changeLeft();
            /*! The function to change the right button. */
            void changeRight();
            /*! The button to go back in the main menu. */
            void backToMenu();
            /*! The function to create a non-centered button. */
            void createSingleButton(float x, float y);
            /*! The function to create a defined number of centered button. */
            void createCenteredButton(int maxButton, int buttonType, int spacing, float y);
            /*! The function to create a defined number of centered text. */
            void createCenteredText(int size, float y, std::string text, Color color);
            /*! The function to create the text inside a button. */
            void createTextInButton(std::string text, int size, Color color, Vector2 y);
            /*! The function to resize all buttons when we resize the window. */
            void resizeButton();
            /*! The function to resize and re-set all the text when we resize the window. */
            void resizeText(int begin, int end, int pos);
            /*! The function to get the new input, and change it in the event class. */
            void changeMyInputs();
        public:
            Options(Indie::SceneManager& manager);
            ~Options();
            /*! Update the scene. */
            bool update(double time) override;
            /*! Draw the scene. */
            void draw() override;

    };
}

#endif /* !OPTION_HPP */
