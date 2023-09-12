/*
** EPITECH PROJECT, 2021
** Credit.cpp
** File description:
** Credit.cpp
*/

#include "Credit.hpp"

Indie::Credit::Credit(Indie::SceneManager& manager) : Indie::AScene::AScene(manager)
{
    _SizeWindow.x = Indie::Window::Instance().getWindowSize().x;
    _SizeWindow.y = Indie::Window::Instance().getWindowSize().y;
    Vector2 tmp = { _SizeWindow.x / 2, 70 };
    auto &text(entity.addEntity());
    text.addComponent<Indie::TextComponent>( ("Assets/FFF_Tusj.ttf"), "Thank you for playing Smash Bomber", tmp, 70, RAYWHITE);
    _Text = entity.getText();
    tmp = {(Indie::Window::Instance().getWindowSize().x / 2 - _Text.back().get().getComponent<Indie::TextComponent>().mesureText().x / 2), Indie::Window::Instance().getWindowSize().y / 10 };
    _Text.back().get().getComponent<Indie::TextComponent>().setPosition(tmp);
    Vector2 posImage = { (Indie::Window::Instance().getWindowSize().x / 22), Indie::Window::Instance().getWindowSize().y / 4 };
    auto &background(entity.addEntity());
    background.addComponent<Indie::TwoDComponent>("Assets/Credits/groupeindie.png", _SizeWindow.x / 2.2, _SizeWindow.y / 2, posImage);
    _Image = entity.getTwoDComponent();
    auto &text1(entity.addEntity());
    tmp = { (Indie::Window::Instance().getWindowSize().x / 22) * 14, (Indie::Window::Instance().getWindowSize().y / 10) * 3 };
    text1.addComponent<Indie::TextComponent>( ("Assets/FFF_Tusj.ttf"), "Programmers and game designer", tmp, 40, RAYWHITE);
    _Text = entity.getText();
    tmp = { (Indie::Window::Instance().getWindowSize().x / 22) * 17 - (_Text.back().get().getComponent<Indie::TextComponent>().mesureText().x / 2), (Indie::Window::Instance().getWindowSize().y / 10) * 3 };
    _Text.back().get().getComponent<Indie::TextComponent>().setPosition(tmp);
    putNameDev("Jean GAUTHIER-DAMIOLI", 7);
    putNameDev("Thomas MOREAU", 8);
    putNameDev("Tom WEDERICH", 9);
    putNameDev("Pierre FRICKER", 10);
    putNameDev("Eliott FERRY", 11);
    putNameDev("Pierre BRUN", 12);
    auto &text2(entity.addEntity());
    tmp = { (Indie::Window::Instance().getWindowSize().x / 2), (Indie::Window::Instance().getWindowSize().y / 10) * 9 };
    text2.addComponent<Indie::TextComponent>( ("Assets/FFF_Tusj.ttf"), "Made with Raylib                SHEPA INNOV             Copyright 2021", tmp, 30, RAYWHITE);
    _Text = entity.getText();
    tmp = { (Indie::Window::Instance().getWindowSize().x / 2) - (_Text.back().get().getComponent<Indie::TextComponent>().mesureText().x / 2), (Indie::Window::Instance().getWindowSize().y / 10) * 9 };
    _Text.back().get().getComponent<Indie::TextComponent>().setPosition(tmp);
    Indie::Audio::Instance().setVolume(((float)Indie::Window::Instance().getWindowVolume() / 1000));
    if (Indie::Audio::Instance().getState() == 1) {
        Indie::Audio::Instance().stopPlayingGameMusic();
        Indie::Audio::Instance().startPlayingMenuMusic();
        Indie::Audio::Instance().setState(0);
    }
    Indie::Audio::Instance().startPlayingMenuMusic();
}

Indie::Credit::~Credit()
{
}

bool Indie::Credit::update(double time)
{
    entity.refresh();
    entity.update(time);
    return false;
}

void Indie::Credit::draw()
{
    ClearBackground(BLACK);
    Indie::Audio::Instance().draw();
    entity.draw();
    if (::IsKeyReleased(KEY_ESCAPE))
        _manager.removeScene();
}

void Indie::Credit::putNameDev(std::string name, int nb)
{
    auto &text1(entity.addEntity());
    Vector2 tmp = { (Indie::Window::Instance().getWindowSize().x / 22) * 17, (Indie::Window::Instance().getWindowSize().y / 20) * nb };
    text1.addComponent<Indie::TextComponent>( ("Assets/FFF_Tusj.ttf"), name, tmp, 40, RAYWHITE);
    _Text = entity.getText();
    tmp = { (Indie::Window::Instance().getWindowSize().x / 22) * 17 - (_Text.back().get().getComponent<Indie::TextComponent>().mesureText().x / 2), (Indie::Window::Instance().getWindowSize().y / 20) * nb };
    _Text.back().get().getComponent<Indie::TextComponent>().setPosition(tmp);
}