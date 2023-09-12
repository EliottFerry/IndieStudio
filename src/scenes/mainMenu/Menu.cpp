/*
** EPITECH PROJECT, 2021
** Menu.cpp
** File description:
** Menu.cpp
*/

#include "Menu.hpp"

Indie::Menu::Menu(Indie::SceneManager& manager) : Indie::AScene::AScene(manager), menu(0), _goingToCredits(false)
{
    _SizeWindow.x = Indie::Window::Instance().getWindowSize().x;
    _SizeWindow.y = Indie::Window::Instance().getWindowSize().y;
    auto &tavern(entity.addEntity());
    tavern.addComponent<Indie::ModelComponent>();
    tavern.getComponent<Indie::ModelComponent>().setEverything("Assets/Taverne/Tavern.obj", { 0.0f, 0.0f, 0.0f }, { 0 } ,{ 5.0f, 5.0f, 5.0f }, 0.0f);
    auto &tavern1(entity.addEntity());
    tavern1.addComponent<Indie::ModelComponent>();
    tavern1.getComponent<Indie::ModelComponent>().setEverything("Assets/buton_font1/untitled.obj", { 0.7f, 1.8f, 2.0f }, { 0.0f, 0.0f, 0.0f } ,{ 1.0f, 1.0f, 1.0f }, 0.0f);
    tavern1.getComponent<Indie::ModelComponent>().transformModel({ 0.0f, 29.0f, 59.7f});
    auto &pancarte2(entity.addEntity());
    pancarte2.addComponent<Indie::ModelComponent>();
    pancarte2.getComponent<Indie::ModelComponent>().setEverything("Assets/buton_font1/untitled.obj", { 1.26f, 1.3f, -1.4f }, { 0.0f, 0.0f, 0.0f } ,{ 1.0f, 1.0f, 1.0f }, 0.0f);
    pancarte2.getComponent<Indie::ModelComponent>().transformModel({ 0.0f, 38.5f, 0.0f});
    pancarte2.addComponent<Indie::ModelComponent>();
    pancarte2.getComponent<Indie::ModelComponent>().setEverything("Assets/buton_font1/untitled.obj", { -1.35f, 1.3f, -1.5f }, { 0.0f, 0.0f, 0.0f } ,{ 1.0f, 1.0f, 1.0f }, 0.0f);
    pancarte2.getComponent<Indie::ModelComponent>().transformModel({ 0.0f, 38.5f, 0.0f});
    auto &cam(entity.addEntity());
    cam.addComponent<Indie::CameraComponent>();
    _cam = &entity.getCamera();
    _cam->getComponent<Indie::CameraComponent>().SetEverythingCamera({ 0.0f, 1.4f, 1.0f }, { 0.0f, 379.0f, 0.0f }, { -0.3f, 1.4f, 0.65f });
    auto &text(entity.addEntity());
    auto &text1(entity.addEntity());
    posText = { 0.9f, 2.0f, 1.8f };
    Vector3 rotate = { 3.0f, 0.0f, 0.0f };
    actualText = "Play";
    text.addComponent<Indie::TextComponent>( ("Assets/FFF_Tusj.ttf"), actualText, posText, rotate, 150, RAYWHITE);
    actualText = "Load game";
    text1.addComponent<Indie::TextComponent>( ("Assets/FFF_Tusj.ttf"), actualText1, posText, rotate, 150, RAYWHITE);
    _Text = entity.getText();
    _playSelected = 0;
    auto &pancarte(entity.addEntity());
    pancarte.addComponent<Indie::ModelComponent>();
    pancarte.getComponent<Indie::ModelComponent>().setEverything("Assets/buton_font1/untitled.obj", { 0.7f, 1.4f, 2.0f }, { 0.0f, 0.0f, 0.0f } ,{ 1.0f, 1.0f, 1.0f }, 0.0f);
    pancarte.getComponent<Indie::ModelComponent>().transformModel({ 0.0f, 29.0f, 59.7f});
    pancarte.getComponent<Indie::ModelComponent>().setDrawable(false);
    auto &controller(entity.addEntity());
    Vector2 control = {0.346f * _SizeWindow.x, 0.028f * _SizeWindow.y};
    controller.addComponent<Indie::TwoDComponent>("Assets/HowToPlay/parchemin.png", 0.302f * _SizeWindow.x, 0.907f * _SizeWindow.y, control);
    _Image = entity.getTwoDComponent();
    _Image.front().get().getComponent<Indie::TwoDComponent>().setDrawable(true);
    Indie::Audio::Instance().setVolume(((float)Indie::Window::Instance().getWindowVolume() / 1000));
    if (Indie::Audio::Instance().getState() == 1) {
        Indie::Audio::Instance().stopPlayingGameMusic();
        Indie::Audio::Instance().startPlayingMenuMusic();
        Indie::Audio::Instance().setState(0);
    }
    _model = entity.getModel();
    Indie::Audio::Instance().startPlayingMenuMusic();
    auto &creditButton(entity.addEntity());
    Vector2 posText1 = { _SizeWindow.x / 12, _SizeWindow.y / 20};
    creditButton.addComponent<Indie::ButtonComponent>((_SizeWindow.x / 12), (_SizeWindow.y / 15), posText1, true, std::function<void()>(std::bind(&Menu::creditButton, this)), true);
    posText1 = { (_SizeWindow.x / 12), _SizeWindow.y / 20};
    creditButton.addComponent<Indie::TextComponent>(("Assets/FFF_Tusj.ttf"), "Credits", posText1, _SizeWindow.x / 64, RAYWHITE);
    posText1 = {(_SizeWindow.x / 12) - (creditButton.getComponent<Indie::TextComponent>().mesureText().x / 2), _SizeWindow.y / 20};
    creditButton.getComponent<Indie::TextComponent>().setPosition(posText1);
    _buttons = entity.getButton();
}

Indie::Menu::~Menu()
{
}

void Indie::Menu::eraseEntity()
{
    _model = entity.getModel();
    for (auto &c : _model)
        c.get().getComponent<Indie::ModelComponent>().clearRam();
}

void Indie::Menu::creditButton()
{
    _goingToCredits = true;
}

bool Indie::Menu::update(double time)
{
    _cam->getComponent<Indie::CameraComponent>().update(time);
    _buttonManager.resetActiveButton(_buttons);
    _time += time;
    if (_time > 0.01 && !_goingToCredits) {
        if (_cam->getComponent<Indie::CameraComponent>().AdvanceInPath() == false && InMovement)
            InMovement = false;
        changeSelectedButton();
        update3DTextSelect();
        if (::IsKeyPressed(KEY_ENTER) || (_oldPlaySelected > 0 && _playSelected == 1 && !InMovement)) {
            if (changeScene())
                return true;
            else
                return false;
        }
        if (menu == 1 && InMovement == false) {
            if (_SizeWindow.x != Indie::Window::Instance().getWindowSize().x || _SizeWindow.y != Indie::Window::Instance().getWindowSize().y) {
                _SizeWindow.x = Indie::Window::Instance().getWindowSize().x;
                _SizeWindow.y = Indie::Window::Instance().getWindowSize().y;
                Vector2 pos = {0.346f * _SizeWindow.x, 0.028f * _SizeWindow.y};
                _Image.front().get().getComponent<Indie::TwoDComponent>().setPos(pos);
                _Image.front().get().getComponent<Indie::TwoDComponent>().setSize(0.302f * _SizeWindow.x, 0.907f * _SizeWindow.y);
            }
            _Image.front().get().getComponent<Indie::TwoDComponent>().setDrawable(true);
        } else
            _Image.front().get().getComponent<Indie::TwoDComponent>().setDrawable(false);
        _time = 0.0;
    }
    if (_goingToCredits) {
        _goingToCredits = false;
        _manager.ScenePush<Indie::Credit>();
        return false;
    }
    entity.update(time);
    return false;
}

void Indie::Menu::draw()
{
    ClearBackground(DARKBROWN);
    Indie::Audio::Instance().draw();
    _cam->getComponent<Indie::CameraComponent>().Begin3DCameraMod();
    entity.draw();
    if (!InMovement) {
        if (::IsKeyPressed(KEY_LEFT))
            MovementMenuLeft();
        if (::IsKeyPressed(KEY_RIGHT))
            MovementMenuRight();
    }
    EndMode3D();
    _Image.front().get().draw();
    _buttons.front().get().draw();
}

void Indie::Menu::MovementMenuLeft()
{
    if (menu == 0) {
        _playSelected = 0;
        _cam->getComponent<Indie::CameraComponent>().AddPathPoint({ 1.0f, 1.4f, 0.65f }, { 0.0f, 379.0f, 0.0f }, { -0.3f, 1.4f, 0.65f }, { 0.1f, 0.01f, 0.01f });
        menu++;
    } else if (menu == 1) {
        _playSelected = 0;
        _cam->getComponent<Indie::CameraComponent>().AddPathPoint({ 10.5f, 1.4f, -9.0f }, { 0.0f, 379.0f, 0.0f }, { -0.3f, 1.4f, -0.1f }, { 0.1f, 0.02f, 0.01f });
        menu++;
    } else if (menu == 2) {
        _playSelected = 0;
        _cam->getComponent<Indie::CameraComponent>().AddPathPoint({ 10.5f, 1.4f, -15.0f }, { 0.0f, 379.0f, 0.0f }, { -2.5f, 1.4f, -0.2f }, { 0.1f, 0.03f, 0.03f });
        menu++;
    } else if (menu == 3) {
        _playSelected = 0;
        _cam->getComponent<Indie::CameraComponent>().AddPathPoint({ 0.0f, 1.4f, 1.0f }, { 0.0f, 379.0f, 0.0f }, { -0.3f, 1.4f, 0.65f }, { 0.3f, 0.02f, 0.02f });
        menu = 0;
    } InMovement = true;
}

void Indie::Menu::MovementMenuRight()
{
    if (menu == 0) {
        _playSelected = 0;
        _cam->getComponent<Indie::CameraComponent>().AddPathPoint({ 10.5f, 1.4f, -15.0f }, { 0.0f, 379.0f, 0.0f }, { -2.5f, 1.4f, -0.2f }, { 0.08f, 0.02f, 0.02f });
        menu = 3;
    } else if (menu == 1) {
        _playSelected = 0;
        _cam->getComponent<Indie::CameraComponent>().AddPathPoint({ 0.0f, 1.4f, 1.0f }, { 0.0f, 379.0f, 0.0f }, { -0.3f, 1.4f, 0.65f }, { 0.3f, 0.02f, 0.02f });
        menu--;
    } else if (menu == 2) {
        _playSelected = 0;
        _cam->getComponent<Indie::CameraComponent>().AddPathPoint({ 1.0f, 1.4f, 0.65f }, { 0.0f, 379.0f, 0.0f }, { -0.3f, 1.4f, 0.65f }, { 0.3f, 0.02f, 0.02f });
        menu--;
    } else if (menu == 3) {
        _playSelected = 0;
        _cam->getComponent<Indie::CameraComponent>().AddPathPoint({ 10.5f, 1.4f, -9.0f }, { 0.0f, 379.0f, 0.0f }, { -0.3f, 1.4f, -0.1f }, { 0.1f, 0.03f, 0.03f });
        menu--;
    } InMovement = true;
}

bool Indie::Menu::changeScene()
{
    if (menu == 0 && _playSelected == 0) {
        _oldPlaySelected = 0;
        _playSelected = 1;
        _model.back().get().getComponent<Indie::ModelComponent>().setDrawable(true);
        return false;
    }
    if (menu == 0 && _playSelected == 1) {
        _oldPlaySelected = 1;
        if (look == 0) {
                _cam->getComponent<Indie::CameraComponent>().AddPathPoint({ -1.0f, 0.45f, 2.65f }, { 0.0f, 379.0f, 0.0f }, { -1.55f, 1.2f, 2.62f }, { 0.1f, 0.03f, 0.03f });
                InMovement = true;
                look = 1;
        } else {
            eraseEntity();
            _manager.ScenePush<Indie::Loading>("NewGame");
        }
    }
    if (menu == 0 && _playSelected == 2)
        _manager.ScenePush<Indie::Loading>("LoadSave");
    if (menu == 2)
        _manager.ScenePush<Indie::Loading>("Option");
    if (menu == 3)
        return true;
    return false;
}

void Indie::Menu::update3DTextSelect()
{
    _Text.front().get().getComponent<Indie::TextComponent>().setColor(RAYWHITE);
    if (menu == 0 && _playSelected == 0) {
        posText = { 0.4f, -1.87f, -1.68f };
        actualText = "Play";
        _Text.front().get().getComponent<Indie::TextComponent>().setSize(30);
        _Text.front().get().getComponent<Indie::TextComponent>().setPosition3D(posText);
        _Text.front().get().getComponent<Indie::TextComponent>().setText(actualText);
    } else if (menu == 0 && (_playSelected == 1 || _playSelected == 2)) {
        posText = { 0.34f, -1.85f, -1.65f };
        actualText = "New game";
        if (_playSelected == 1) {
            _Text.front().get().getComponent<Indie::TextComponent>().setColor(BEIGE);
            _Text.back().get().getComponent<Indie::TextComponent>().setColor(RAYWHITE);
        } else {
            _Text.front().get().getComponent<Indie::TextComponent>().setColor(RAYWHITE);
            _Text.back().get().getComponent<Indie::TextComponent>().setColor(BEIGE);
        }
        _Text.front().get().getComponent<Indie::TextComponent>().setSize(16);
        _Text.front().get().getComponent<Indie::TextComponent>().setPosition3D(posText);
        _Text.front().get().getComponent<Indie::TextComponent>().setText(actualText);
        posText = { 0.32f, -1.85f, -1.28f };
        actualText1 = "Load game";
        _model.back().get().getComponent<Indie::ModelComponent>().setDrawable(true);
        _Text.back().get().getComponent<Indie::TextComponent>().setSize(16);
        _Text.back().get().getComponent<Indie::TextComponent>().setPosition3D(posText);
        _Text.back().get().getComponent<Indie::TextComponent>().setText(actualText1);
        _Text.back().get().getComponent<Indie::TextComponent>().setDrawable(true);
        if (::IsKeyReleased(KEY_ESCAPE)) {
            _model.back().get().getComponent<Indie::ModelComponent>().setDrawable(false);
            _Text.back().get().getComponent<Indie::TextComponent>().setDrawable(false);
            _playSelected = 0;
        }
    } else if (menu == 2) {
        actualText = "Settings";
        posText = { -0.5f, -1.83f, -1.57f };
        _Text.front().get().getComponent<Indie::TextComponent>().setSize(20);
        _Text.front().get().getComponent<Indie::TextComponent>().setPosition3D(posText);
        _Text.front().get().getComponent<Indie::TextComponent>().setText(actualText);
    } else if (menu == 3) {
        actualText = "Exit";
        posText = { -2.2f, 0.1f, -1.6f };
        _Text.front().get().getComponent<Indie::TextComponent>().setSize(30);
        _Text.front().get().getComponent<Indie::TextComponent>().setPosition3D(posText);
        _Text.front().get().getComponent<Indie::TextComponent>().setText(actualText);
    }
}

void Indie::Menu::changeSelectedButton()
{
    if (::IsKeyPressed(KEY_DOWN)) {
        _playSelected++;
        if (_playSelected == 3)
            _playSelected = 1;
    }
    if (::IsKeyPressed(KEY_UP)) {
        _playSelected--;
        if (_playSelected == 0)
            _playSelected = 2;
    }
    if (menu != 0) {
        _Text.back().get().getComponent<Indie::TextComponent>().setDrawable(false);
        _model.back().get().getComponent<Indie::ModelComponent>().setDrawable(false);
    }
}