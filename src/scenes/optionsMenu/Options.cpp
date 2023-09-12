/*
** EPITECH PROJECT, 2021
** Option
** File description:
** The file to handle the option scene
*/

#include "Options.hpp"
#include "../mainMenu/Menu.hpp"

Indie::Options::Options(Indie::SceneManager& manager) : Indie::AScene::AScene(manager), _backSelected(false), _nbButtonCreated(0)
{
    inputsChanged = false;
    volumeChanged = false;
    float sizeWindowX = Indie::Window::Instance().getWindowSize().x;
    float sizeWindowY = Indie::Window::Instance().getWindowSize().y;
    sizeWindow = { sizeWindowX, sizeWindowY };
    Vector2 posText = { 0.0f, 0.0f };
    auto &background(entities.addEntity());
    background.addComponent<Indie::TwoDComponent>("Assets/Options/background.png", sizeWindowX, sizeWindowY, posText);
    _background = entities.getTwoDComponent();
    createCenteredButton(BUTTON_RETOUR, BUTTON_RETOUR, 0, sizeWindowY / 20);
    createCenteredButton((BUTTON_RESOLUTION + BUTTON_RETOUR), BUTTON_RESOLUTION, 25, (sizeWindowY / 2) + (sizeWindowY / 15));
    createCenteredButton((BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_RETOUR), BUTTON_VOLUME, 10, (sizeWindowY) - (sizeWindowY / 15));
    createCenteredButton((BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_FPS + BUTTON_RETOUR), BUTTON_FPS, 25, sizeWindowY + (sizeWindowY / 4));
    createCenteredButton((BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_FPS + BUTTON_INPUTS + BUTTON_RETOUR), BUTTON_INPUTS, 25, sizeWindowY + (sizeWindowY / 1.7f));
    createCenteredText(sizeWindowX / 27.42f, sizeWindowY / 10 - 50, "Options", BLACK);
    createCenteredText(sizeWindowX / 27.42f, sizeWindowY / 5, "Resolution", BLACK);
    createCenteredText(sizeWindowX / 27.42f, sizeWindowY / 2.5f, "Volume", BLACK);
    createCenteredText(sizeWindowX / 27.42f, sizeWindowY / 2.1f, std::to_string(Indie::Window::Instance().getWindowVolume()), BLACK);
    createCenteredText(sizeWindowX / 27.42f, sizeWindowY / 1.8f, "Framerate", BLACK);
    createCenteredText(sizeWindowX / 27.42f, sizeWindowY / 1.4f, "Inputs", BLACK);
    _allButtons = entities.getButton();
    _textInButtons = entities.getText();
}

void Indie::Options::createTextInButton(std::string text, int size, Color color, Vector2 posText)
{
    float sizeWindowX = Indie::Window::Instance().getWindowSize().x;
    float sizeWindowY = Indie::Window::Instance().getWindowSize().y;
    auto &textEntity(entities.addEntity());
    textEntity.addComponent<Indie::TextComponent>( ("Assets/FFF_Tusj.ttf"), text, posText, size, color);
    textEntity.getComponent<Indie::TextComponent>().setPosition(posText);
}

void Indie::Options::createCenteredText(int size, float y, std::string text, Color color)
{
    Vector2 posText = { 0.0f, 0.0f };
    float sizeWindowX = Indie::Window::Instance().getWindowSize().x;
    float sizeWindowY = Indie::Window::Instance().getWindowSize().y;
    auto &textEntity(entities.addEntity());
    textEntity.addComponent<Indie::TextComponent>( ("Assets/FFF_Tusj.ttf"), text, posText, size, color);
    posText = { (sizeWindowX / 2) - (textEntity.getComponent<Indie::TextComponent>().mesureText().x / 2), y };
    textEntity.getComponent<Indie::TextComponent>().setPosition(posText);
}

void Indie::Options::createSingleButton(float x, float y)
{
    float sizeWindowX = Indie::Window::Instance().getWindowSize().x;
    float sizeWindowY = Indie::Window::Instance().getWindowSize().y;
    Vector2 posButton = {x, y};
    auto &button(entities.addEntity());
    createTextInButton(_textButtons[0], 30, DARKBLUE, posButton);
}

void Indie::Options::createCenteredButton(int maxButton, int buttonType, int spacing, float y)
{
    float sizeWindowX = Indie::Window::Instance().getWindowSize().x;
    float sizeWindowY = Indie::Window::Instance().getWindowSize().y;
    for (float posXButton = 0; maxButton != _nbButtonCreated; _nbButtonCreated++, posXButton++) {
        if (maxButton == 1) {
            Vector2 posButton = { sizeWindowX / 20, y};
            auto &button(entities.addEntity());
            button.addComponent<Indie::ButtonComponent>((sizeWindowX / 12), (sizeWindowY / 15), posButton, true, _functionResolution[_nbButtonCreated], true);
            Vector2 posText = { sizeWindowX / 20, y };
            createTextInButton(_textButtons[_nbButtonCreated], static_cast<int>(sizeWindowX / 76.8f), DARKBLUE, posText);
        }
        else {
            Vector2 posButton = { ((sizeWindowX) - ((sizeWindowX / 12) * buttonType + ((buttonType - 1) * sizeWindowX / spacing))) + (posXButton == 0 ? 0.0f : (((sizeWindowX / 12) + sizeWindowX / spacing) * (posXButton)) * 2), y};
            auto &button(entities.addEntity());
            button.addComponent<Indie::ButtonComponent>((sizeWindowX / 12), (sizeWindowY / 15), posButton, true, _functionResolution[_nbButtonCreated], true);
            Vector2 posText = { ((((sizeWindowX) - ((sizeWindowX / 12) * buttonType + ((buttonType - 1) * sizeWindowX / spacing))) + (posXButton == 0 ? 0.0f : (((sizeWindowX / 12) + sizeWindowX / spacing) * (posXButton)) * 2)) / 2), (y / 2) + ((sizeWindowY / 12) / 5)};
            createTextInButton(_textButtons[_nbButtonCreated], static_cast<int>(sizeWindowX / 76.8f), DARKBLUE, posText);
        }
    }
}

void Indie::Options::setFramerate(int framerate)
{
    Indie::Window::Instance().setWindowFramerate(framerate);
}

void Indie::Options::setVolume(int volume)
{
    volumeChanged = true;
    Indie::Window::Instance().setWindowVolume(volume);
}

void Indie::Options::fullScreen()
{
    Indie::Window::Instance().setWindowFullScreen();
}

void Indie::Options::screenSizeFHD()
{
    Indie::Window::Instance().setWindowResolution(1920, 1080);
}

void Indie::Options::screenSizeHD()
{
    Indie::Window::Instance().setWindowResolution(1280, 720);
}

void Indie::Options::screenSizeHDP()
{
    Indie::Window::Instance().setWindowResolution(1600, 900);
}

void Indie::Options::screenSizeWQHD()
{
    Indie::Window::Instance().setWindowResolution(2560, 1440);
}

void Indie::Options::changeAction()
{
    inputsChanged = true;
    for (std::unordered_map<std::string, bool>::iterator a = isChanging.begin(); a != isChanging.end(); a++)
        if (a->second == true)
            return;
    Indie::Event::Instance().setInputs("Action", Indie::Event::NO_INPUTS);
    _textButtons[BUTTON_BEFORE_INPUTS + 4] = Indie::Parsing::Instance().keyMap[Indie::Event::Instance().getMapInputs()["Action"]];
    isChanging["Action"] = true;
}

void Indie::Options::changeUp()
{

    inputsChanged = true;
    for (std::unordered_map<std::string, bool>::iterator a = isChanging.begin(); a != isChanging.end(); a++)
        if (a->second == true)
            return;
    Indie::Event::Instance().setInputs("Up", Indie::Event::NO_INPUTS);
    _textButtons[BUTTON_BEFORE_INPUTS + 1] = Indie::Parsing::Instance().keyMap[Indie::Event::Instance().getMapInputs()["Up"]];
    isChanging["Up"] = true;
}

void Indie::Options::changeDown()
{
    inputsChanged = true;
    for (std::unordered_map<std::string, bool>::iterator a = isChanging.begin(); a != isChanging.end(); a++)
        if (a->second == true)
            return;
    Indie::Event::Instance().setInputs("Down", Indie::Event::NO_INPUTS);
    _textButtons[BUTTON_BEFORE_INPUTS] = Indie::Parsing::Instance().keyMap[Indie::Event::Instance().getMapInputs()["Down"]];
    isChanging["Down"] = true;
}

void Indie::Options::changeLeft()
{
    inputsChanged = true;
    for (std::unordered_map<std::string, bool>::iterator a = isChanging.begin(); a != isChanging.end(); a++)
        if (a->second == true)
            return;
    Indie::Event::Instance().setInputs("Left", Indie::Event::NO_INPUTS);
    _textButtons[BUTTON_BEFORE_INPUTS + 2] = Indie::Parsing::Instance().keyMap[Indie::Event::Instance().getMapInputs()["Left"]];
    isChanging["Left"] = true;
}

void Indie::Options::changeRight()
{
    inputsChanged = true;
    for (std::unordered_map<std::string, bool>::iterator a = isChanging.begin(); a != isChanging.end(); a++)
        if (a->second == true)
            return;
    Indie::Event::Instance().setInputs("Right", Indie::Event::NO_INPUTS);
    _textButtons[BUTTON_BEFORE_INPUTS + 3] = Indie::Parsing::Instance().keyMap[Indie::Event::Instance().getMapInputs()["Right"]];
    isChanging["Right"] = true;
}

void Indie::Options::backToMenu()
{
    _backSelected = true;
}

void Indie::Options::resizeText(int begin, int end, int pos)
{
    float sizeWindowX = Indie::Window::Instance().getWindowSize().x;
    float sizeWindowY = Indie::Window::Instance().getWindowSize().y;
    int nbText = 0;
    int posXText = 0 + pos;
    std::vector<float> posName = {
        sizeWindowY / 10 - 50,
        sizeWindowY / 5,
        sizeWindowY / 2.5f,
        sizeWindowY / 2.1f,
        sizeWindowY / 1.8f,
        sizeWindowY / 1.4f
    };
    std::vector<std::string> stringName = {
        "Options",
        "Resolution",
        "Volume",
        std::to_string(Indie::Window::Instance().getWindowVolume()),
        "Framerate",
        "Inputs",
    };

    for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _textInButtons.begin(); i != _textInButtons.end(); i++, nbText++, posXText++) {
        while (nbText < begin) {
            nbText++;
            i++;
        }
        if (nbText >= end)
            break;
        if (nbText < BUTTON_RETOUR) {
            Vector2 posText = { (sizeWindowX / 20), (sizeWindowY / 20)};
            i->get().getComponent<Indie::TextComponent>().setPosition(posText);
            i->get().getComponent<Indie::TextComponent>().setSize(static_cast<int>(sizeWindowX / 76.8f));
        }
        else if (nbText >= BUTTON_RETOUR && nbText < BUTTON_RETOUR + BUTTON_RESOLUTION) {
            if (nbText == BUTTON_RETOUR)
                posXText = 0;
            Vector2 posText = { ((((sizeWindowX) - ((sizeWindowX / 12) * BUTTON_RESOLUTION + ((BUTTON_RESOLUTION - 1) * sizeWindowX / 25))) + (posXText == 0 ? 0.0f : (((sizeWindowX / 12) + sizeWindowX / 25) * (posXText)) * 2)) / 2), (((sizeWindowY / 2) + (sizeWindowY / 15)) / 2) + ((sizeWindowY / 12) / 5)};
            i->get().getComponent<Indie::TextComponent>().setPosition(posText);
            i->get().getComponent<Indie::TextComponent>().setSize(static_cast<int>(sizeWindowX / 76.8f));
        }
        else if (nbText >= BUTTON_RESOLUTION + BUTTON_RETOUR && nbText < BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_RETOUR) {
            if (nbText == BUTTON_RESOLUTION + BUTTON_RETOUR)
                posXText = 0;
            Vector2 posText = { ((((sizeWindowX) - ((sizeWindowX / 12) * BUTTON_VOLUME + ((BUTTON_VOLUME - 1) * sizeWindowX / 10))) + (posXText == 0 ? 0.0f : (((sizeWindowX / 12) + sizeWindowX / 10) * (posXText)) * 2)) / 2), ((sizeWindowY - (sizeWindowY / 15)) / 2) + ((sizeWindowY / 12) / 5)};
            i->get().getComponent<Indie::TextComponent>().setPosition(posText);
            i->get().getComponent<Indie::TextComponent>().setSize(static_cast<int>(sizeWindowX / 76.8f));
        }
        else if (nbText >= BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_RETOUR && nbText < BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_FPS + BUTTON_RETOUR) {
            if (nbText == BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_RETOUR)
                posXText = 0;
            Vector2 posText = { ((((sizeWindowX) - ((sizeWindowX / 12) * BUTTON_FPS + ((BUTTON_FPS - 1) * sizeWindowX / 25))) + (posXText == 0 ? 0.0f : (((sizeWindowX / 12) + sizeWindowX / 25) * (posXText)) * 2)) / 2), ((sizeWindowY + (sizeWindowY / 4)) / 2) + ((sizeWindowY / 12) / 5)};
            i->get().getComponent<Indie::TextComponent>().setPosition(posText);
            i->get().getComponent<Indie::TextComponent>().setSize(static_cast<int>(sizeWindowX / 76.8f));
        }
        else if (nbText >= BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_FPS + BUTTON_RETOUR && nbText < BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_FPS + BUTTON_INPUTS + BUTTON_RETOUR) {
            if (nbText == BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_FPS + BUTTON_RETOUR)
                posXText = 0;
            Vector2 posText = { ((((sizeWindowX) - ((sizeWindowX / 12) * BUTTON_INPUTS + ((BUTTON_INPUTS - 1) * sizeWindowX / 25))) + (posXText == 0 ? 0.0f : (((sizeWindowX / 12) + sizeWindowX / 25) * (posXText)) * 2)) / 2), ((sizeWindowY + (sizeWindowY / 1.7f)) / 2) + ((sizeWindowY / 12) / 5)};
            i->get().getComponent<Indie::TextComponent>().setText(_textButtons[BUTTON_BEFORE_INPUTS + posXText]);
            i->get().getComponent<Indie::TextComponent>().setPosition(posText);
            i->get().getComponent<Indie::TextComponent>().setSize(static_cast<int>(sizeWindowX / 76.8f));
        }
        else {
            if (nbText == BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_FPS + BUTTON_RETOUR + BUTTON_INPUTS) {
                i->get().getComponent<Indie::TextComponent>().setSize(static_cast<int>(sizeWindowX / 27.42f));
                posXText = 0;
            }
            else
                i->get().getComponent<Indie::TextComponent>().setSize(static_cast<int>(sizeWindowX / 38.4f));
            Vector2 posText = { (sizeWindowX / 2) - (i->get().getComponent<Indie::TextComponent>().mesureText().x / 2), posName[posXText]};
            i->get().getComponent<Indie::TextComponent>().setPosition(posText);
            i->get().getComponent<Indie::TextComponent>().setText(stringName[posXText]);
        }
    }
}

void Indie::Options::resizeButton()
{
    float sizeWindowX = Indie::Window::Instance().getWindowSize().x;
    float sizeWindowY = Indie::Window::Instance().getWindowSize().y;
    int nbButton = 0;
    int posXButton = 0;

    _background.front().get().getComponent<Indie::TwoDComponent>().setSize(sizeWindowX, sizeWindowY);
    for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _allButtons.begin(); i != _allButtons.end(); i++, nbButton++, posXButton++) {
        if (nbButton < BUTTON_RETOUR) {
            Vector2 posButton = { (sizeWindowX / 20), (sizeWindowY / 20)};
            i->get().getComponent<Indie::ButtonComponent>().resizeButton((sizeWindowX / 12), (sizeWindowY / 15), posButton);
        }
        else if (nbButton >= BUTTON_RETOUR && nbButton < (BUTTON_RESOLUTION + BUTTON_RETOUR)) {
            if (nbButton == BUTTON_RETOUR)
                posXButton = 0;
            Vector2 posButton = { ((sizeWindowX) - ((sizeWindowX / 12) * BUTTON_RESOLUTION + ((BUTTON_RESOLUTION - 1) * sizeWindowX / 25))) + (posXButton == 0 ? 0.0f : (((sizeWindowX / 12) + sizeWindowX / 25) * (posXButton)) * 2), (sizeWindowY / 2) + (sizeWindowY / 15)};
            i->get().getComponent<Indie::ButtonComponent>().resizeButton((sizeWindowX / 12), (sizeWindowY / 15), posButton);
        }
        else if (nbButton >= BUTTON_RESOLUTION + BUTTON_RETOUR && nbButton < (BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_RETOUR)) {
            if (nbButton == BUTTON_RESOLUTION + BUTTON_RETOUR)
                posXButton = 0;
            Vector2 posButton = { ((sizeWindowX) - ((sizeWindowX / 12) * BUTTON_VOLUME + ((BUTTON_VOLUME - 1) * sizeWindowX / 10))) + (posXButton == 0 ? 0.0f : (((sizeWindowX / 12) + sizeWindowX / 10) * (posXButton)) * 2), sizeWindowY - (sizeWindowY / 15)};
            i->get().getComponent<Indie::ButtonComponent>().resizeButton((sizeWindowX / 12), (sizeWindowY / 15), posButton);
        }
        else if (nbButton >= (BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_RETOUR) && nbButton < (BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_FPS + BUTTON_RETOUR)) {
            if (nbButton == (BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_RETOUR))
                posXButton = 0;
            Vector2 posButton = { ((sizeWindowX) - ((sizeWindowX / 12) * BUTTON_FPS + ((BUTTON_FPS - 1) * sizeWindowX / 25))) + (posXButton == 0 ? 0.0f : (((sizeWindowX / 12) + sizeWindowX / 25) * (posXButton)) * 2), sizeWindowY + (sizeWindowY / 4)};
            i->get().getComponent<Indie::ButtonComponent>().resizeButton((sizeWindowX / 12), (sizeWindowY / 15), posButton);
        }
        else if (nbButton >= (BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_FPS + BUTTON_RETOUR) && nbButton < (BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_FPS + BUTTON_INPUTS + BUTTON_RETOUR)) {
            if (nbButton == (BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_FPS + BUTTON_RETOUR))
                posXButton = 0;
            Vector2 posButton = { ((sizeWindowX) - ((sizeWindowX / 12) * BUTTON_INPUTS + ((BUTTON_INPUTS - 1) * sizeWindowX / 25))) + (posXButton == 0 ? 0.0f : (((sizeWindowX / 12) + sizeWindowX / 25) * (posXButton)) * 2), sizeWindowY + (sizeWindowY / 1.7f)};
            i->get().getComponent<Indie::ButtonComponent>().resizeButton((sizeWindowX / 12), (sizeWindowY / 15), posButton);
        }
    }
}

void Indie::Options::changeMyInputs()
{
    int numInput = 0;
    int input = 0;

    for (std::unordered_map<std::string, bool>::iterator a = isChanging.begin(); a != isChanging.end(); a++, numInput++) {
        if (a->second == true) {
            input = GetKeyPressed();
            if (input != 0) {
                inputsChanged = true;
                Indie::Event::Instance().setInputs(a->first, input);
                _textButtons[BUTTON_BEFORE_INPUTS + numInput] = Indie::Parsing::Instance().keyMap[Indie::Event::Instance().getMapInputs()[a->first]];
                a->second = false;
            }
        }
    }

}

bool Indie::Options::update(double time)
{
    float sizeWindowX = Indie::Window::Instance().getWindowSize().x;
    float sizeWindowY = Indie::Window::Instance().getWindowSize().y;
    if (_backSelected == true) {
        entities.clear();
        _manager.removeNbScene(2);
        return false;
    }
    _buttonManager.resetActiveButton(_allButtons);
    changeMyInputs();
    entities.refresh();
    entities.update(time);
    if (sizeWindow.x != sizeWindowX || sizeWindow.y != sizeWindowY) {
        sizeWindow = { sizeWindowX, sizeWindowY };
        resizeButton();
        resizeText(0, BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_FPS + BUTTON_INPUTS + BUTTON_RETOUR + 6, 0);
    }
    else if (volumeChanged) {
        resizeText(20, 21, 3);
        volumeChanged = false;
    }
    else if (inputsChanged) {
        resizeText(BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_FPS + BUTTON_RETOUR, BUTTON_RESOLUTION + BUTTON_VOLUME + BUTTON_FPS + BUTTON_RETOUR + BUTTON_INPUTS, 0);
        inputsChanged = false;
    }
    return (false);
}

void Indie::Options::draw()
{
    ::ClearBackground(WHITE);
    Indie::Audio::Instance().draw();
    entities.draw();
}

Indie::Options::~Options()
{
}