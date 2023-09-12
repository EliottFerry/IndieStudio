/*
** EPITECH PROJECT, 2021
** ManageButtons
** File description:
** The file to implement the managing function for the buttons
*/

#ifndef MANAGEBUTTONS_HPP
#define MANAGEBUTTONS_HPP

#include <string>
#include <fstream>
#include <iostream>
#include "raylib.h"
#include "../ECS/Components.hpp"

namespace Indie {
    class ManageButtons {
        public:
            ManageButtons();
            ~ManageButtons();
            /*! Set all the button to the inactive states. */
            void resetActiveButton(std::list<std::reference_wrapper<Indie::Entity>> _buttons);
            /*! Set the active button by managing keyboard inputs. */
            void setActiveButton(std::list<std::reference_wrapper<Indie::Entity>> _buttons, int _maxButtons);
        protected:
        private:
            int _selectedButton;
    };
}

#endif /* !MANAGEBUTTONS_HPP */
