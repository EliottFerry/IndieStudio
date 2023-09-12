/*
** EPITECH PROJECT, 2021
** initScene
** File description:
** The file to handle the init scene
*/

#include "initScene.hpp"
#include "../mainMenu/Menu.hpp"

Indie::initScene::initScene(Indie::SceneManager& manager): Indie::AScene::AScene(manager), _switched(false), _currentText(0)
{
    float sizeWindowX = Indie::Window::Instance().getWindowSize().x;
    float sizeWindowY = Indie::Window::Instance().getWindowSize().y;
    auto &ourName(entities.addEntity());
    Vector2 posText = {0.0f, 0.0f};
    ourName.addComponent<Indie::TextComponent>("Assets/ka1.ttf", "Shepa innov", posText, 60, RAYWHITE);
    posText = {sizeWindowX / 2 - (ourName.getComponent<Indie::TextComponent>().mesureText().x / 2), sizeWindowY / 2.0f};
    ourName.getComponent<Indie::TextComponent>().setPosition(posText);
    ourName.getComponent<Indie::TextComponent>().setAlpha(0.01f);
    auto &madeWith(entities.addEntity());
    madeWith.addComponent<Indie::TextComponent>("Assets/ka1.ttf", "Made with", posText, 60, RAYWHITE);
    madeWith.getComponent<Indie::TextComponent>().setPosition(Vector2{sizeWindowX / 2 - (madeWith.getComponent<Indie::TextComponent>().mesureText().x / 2), sizeWindowY / 1.5f});
    madeWith.getComponent<Indie::TextComponent>().setAlpha(0.01f);
    auto &pressAnyKey(entities.addEntity());
    pressAnyKey.addComponent<Indie::TextComponent>("Assets/ka1.ttf", "Press any key to continue...", posText, 20, RAYWHITE);
    posText = { sizeWindowX - pressAnyKey.getComponent<Indie::TextComponent>().mesureText().x, (sizeWindowY) - 50 };
    pressAnyKey.getComponent<Indie::TextComponent>().setPosition(posText);
    pressAnyKey.getComponent<Indie::TextComponent>().setAlpha(0.01f);
    auto &rayLogo(entities.addEntity());
    rayLogo.addComponent<Indie::TwoDComponent>("Assets/initScene/logoRaylib.png", sizeWindowX / 7.5f, sizeWindowY / 4.21f, Vector2 {0.0f, 0.0f});
    Image posImage = rayLogo.getComponent<Indie::TwoDComponent>().getImage();
    Vector2 posLogo = {sizeWindowX / 2 - (posImage.width / 2), sizeWindowY / 1.35f};
    rayLogo.getComponent<Indie::TwoDComponent>().setPos(posLogo);
    rayLogo.getComponent<Indie::TwoDComponent>().setAlpha(0.01f);
    auto &ourLogo(entities.addEntity());
    ourLogo.addComponent<Indie::TwoDComponent>("Assets/initScene/logo (1).png", sizeWindowX / 7.5f, sizeWindowY / 4.21f, Vector2 {0.0f, 0.0f});
    posImage = ourLogo.getComponent<Indie::TwoDComponent>().getImage();
    posLogo = {sizeWindowX / 2 - (posImage.width / 2), sizeWindowY / 4.0f};
    ourLogo.getComponent<Indie::TwoDComponent>().setPos(posLogo);
    ourLogo.getComponent<Indie::TwoDComponent>().setAlpha(0.01f);
    _texts = entities.getText();
    _logos = entities.getTwoDComponent();
}

bool Indie::initScene::update(double time)
{
    float sizeWindowX = Indie::Window::Instance().getWindowSize().x;
    float sizeWindowY = Indie::Window::Instance().getWindowSize().y;
    if (::GetKeyPressed() != 0) {
        for (auto &i : _texts)
            i.get().getComponent<Indie::TextComponent>().setInactive();
        for (auto &i : _logos)
            i.get().getComponent<Indie::TwoDComponent>().setInactive();
    }
    entities.refresh();
    entities.update(time);
    _logos = entities.getTwoDComponent();
    _texts = entities.getText();

    if (_currentText == 0)
        if (_texts.front().get().getComponent<Indie::TextComponent>().getAlpha() <= 0.01f) {
            _currentText = 1;
            auto &text(entities.addEntity());
            Vector2 posText = {(sizeWindowX / 2), (sizeWindowY / 2)};
            text.addComponent<Indie::TextComponent>("Assets/ka1.ttf", "Smash Bomber", posText , 100, RAYWHITE);
            posText = { (sizeWindowX / 2 - (text.getComponent<Indie::TextComponent>().mesureText().x / 2)), sizeWindowY / 2};
            text.getComponent<Indie::TextComponent>().setPosition(posText);
            text.getComponent<Indie::TextComponent>().setAlpha(0.01f);
            auto &pressAnyKey(entities.addEntity());
            pressAnyKey.addComponent<Indie::TextComponent>("Assets/ka1.ttf", "Press any key to continue...", posText, 20, RAYWHITE);
            posText = { sizeWindowX - pressAnyKey.getComponent<Indie::TextComponent>().mesureText().x, (sizeWindowY) - 50 };
            pressAnyKey.getComponent<Indie::TextComponent>().setPosition(posText);
            pressAnyKey.getComponent<Indie::TextComponent>().setAlpha(0.01f);
            _texts = entities.getText();
        }
    if (_logos.empty() && _texts.empty() && !_switched) {
        _switched = true;
        _manager.ScenePush<Indie::Menu>();
    }
    return false;
}

void Indie::initScene::draw()
{
    ClearBackground(BLACK);
    if (!_switched) {
        entities.draw();
    }
}

Indie::initScene::~initScene()
{
}