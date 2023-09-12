/*
** EPITECH PROJECT, 2021
** ManageButton
** File description:
** The file to implement all the fuction for the button managing
*/

#include "ManageButtons.hpp"

Indie::ManageButtons::ManageButtons() : _selectedButton(0)
{
}

void Indie::ManageButtons::resetActiveButton(std::list<std::reference_wrapper<Indie::Entity>> _buttons)
{
    int currentButton = 0;
    for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _buttons.begin(); i != _buttons.end(); i++, currentButton++)
        i->get().getComponent<Indie::ButtonComponent>().setSelected(false);
}

void Indie::ManageButtons::setActiveButton(std::list<std::reference_wrapper<Indie::Entity>> _buttons, int _maxButtons)
{
    int currentButton = 0;

    for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _buttons.begin(); i != _buttons.end(); i++, currentButton++) {
        if (i->get().getComponent<Indie::ButtonComponent>().isOvered()) {
            _selectedButton = currentButton;
            resetActiveButton(_buttons);
            i->get().getComponent<Indie::ButtonComponent>().setSelected(true);
        }
    }
    currentButton = 0;
    if (::IsKeyPressed(KEY_DOWN)) {
        resetActiveButton(_buttons);
        if (_selectedButton >= _maxButtons - 1) {
            _selectedButton = 0;
        }
        else
            _selectedButton++;
    }
    if (::IsKeyPressed(KEY_UP)) {
        resetActiveButton(_buttons);
        if (_selectedButton <= 0) {
            _selectedButton = _maxButtons - 1;
        }
        else {
            _selectedButton--;
        }
    }
    for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _buttons.begin(); i != _buttons.end(); i++, currentButton++) {
        if (currentButton == _selectedButton) {
            i->get().getComponent<Indie::ButtonComponent>().setSelected(true);
        }
        else {
            i->get().getComponent<Indie::ButtonComponent>().setSelected(false);
        }
    }
}


Indie::ManageButtons::~ManageButtons()
{
}
