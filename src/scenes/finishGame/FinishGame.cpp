/*
** EPITECH PROJECT, 2021
** FinishGame.cpp
** File description:
** FinishGame.cpp
*/

#include "FinishGame.hpp"

Indie::FinishGame::FinishGame(Indie::SceneManager& manager, std::map<int, std::string> namePlayers, int _nbPlayer) : Indie::AScene::AScene(manager), _exit(false)
{
    Vector2 posText = { 0, 0 };
    _SizeWindow.x = Indie::Window::Instance().getWindowSize().x;
    _SizeWindow.y = Indie::Window::Instance().getWindowSize().y;
    auto &background(entity.addEntity());
    background.addComponent<Indie::TwoDComponent>("Assets/Newgame/table3.png", _SizeWindow.x, _SizeWindow.y, posText);
    _background = entity.getTwoDComponent();
    auto& cam(entity.addEntity());
    cam.addComponent<Indie::CameraComponent>();
    _cam = &entity.getCamera();
    _cam->getComponent<Indie::CameraComponent>().SetEverythingCamera({ 6.5f, 0.0f, 5.0f }, { 0.0f, 1.0f, -70.0f }, { 6.5f, 15.0f, 15.0f });
    Vector3 RotAx = { 0.0f, 0.0f, 0.0f };
    Vector3 pos = { 1.6f, -10.0f, 0.0f};
    auto &text1(entity.addEntity());
    std::string textToPrint = namePlayers[0] + ", Player 1 lost the game !";
    if (_nbPlayer == 1) {
        pos = { -4.0f, -10.0f, 0.0f};
        textToPrint = namePlayers[0] + ", Player 1 and " + namePlayers[1] + ", Player 2 lost the game !";
    } text1.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", textToPrint, pos, RotAx, 250, RAYWHITE);
    _Text = entity.getText();
    Vector3 posplayer = { 7.0f, -3.0f, 1.0f};
    if (_nbPlayer > 0)
        posplayer = { 3.0f, -3.0f, 1.0f};
    createAndchangePlayer(namePlayers[0], posplayer);
    if (_nbPlayer > 0) {
        posplayer = { 10.0f, -3.0f, 1.0f};
        createAndchangePlayer(namePlayers[1], posplayer);
    }
    Indie::Audio::Instance().setVolume(((float)Indie::Window::Instance().getWindowVolume() / 1000));
    if (Indie::Audio::Instance().getState() == 1) {
        Indie::Audio::Instance().stopPlayingGameMusic();
        Indie::Audio::Instance().startPlayingMenuMusic();
        Indie::Audio::Instance().setState(0);
    }
    Indie::Audio::Instance().startPlayingMenuMusic();
    auto &creditButton(entity.addEntity());
    Vector2 posText1 = { _SizeWindow.x / 12, _SizeWindow.y / 20};
    creditButton.addComponent<Indie::ButtonComponent>((_SizeWindow.x / 12), (_SizeWindow.y / 15), posText1, true, std::function<void()>(std::bind(&FinishGame::menuButton, this)), true);
    posText1 = { (_SizeWindow.x / 12), _SizeWindow.y / 20};
    creditButton.addComponent<Indie::TextComponent>(("Assets/FFF_Tusj.ttf"), "Menu", posText1, _SizeWindow.x / 64, RAYWHITE);
    posText1 = {(_SizeWindow.x / 12) - (creditButton.getComponent<Indie::TextComponent>().mesureText().x / 2), _SizeWindow.y / 20};
    creditButton.getComponent<Indie::TextComponent>().setPosition(posText1);
    _buttons = entity.getButton();
}

Indie::FinishGame::FinishGame(Indie::SceneManager& manager, std::string nameWiner, int _nbPlayerWiner) : Indie::AScene::AScene(manager), _exit(false)
{
    Vector2 posText = { 0, 0 };
    _SizeWindow.x = Indie::Window::Instance().getWindowSize().x;
    _SizeWindow.y = Indie::Window::Instance().getWindowSize().y;
    auto &background(entity.addEntity());
    background.addComponent<Indie::TwoDComponent>("Assets/Newgame/table3.png", _SizeWindow.x, _SizeWindow.y, posText);
    _background = entity.getTwoDComponent();
    auto& cam(entity.addEntity());
    cam.addComponent<Indie::CameraComponent>();
    _cam = &entity.getCamera();
    _cam->getComponent<Indie::CameraComponent>().SetEverythingCamera({ 6.5f, 0.0f, 5.0f }, { 0.0f, 1.0f, -70.0f }, { 6.5f, 15.0f, 15.0f });
    Vector3 RotAx = { 0.0f, 0.0f, 0.0f };
    Vector3 pos = { 1.0f, -10.0f, 0.0f};
    auto &text1(entity.addEntity());
    std::string textToPrint = nameWiner + " (Player " + std::to_string(_nbPlayerWiner) + ") win the game !";
    text1.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", textToPrint, pos, RotAx, 250, RAYWHITE);
    _Text = entity.getText();
    Vector3 posPlayer = { 7.0f, -3.0f, 1.0f};
    createAndchangePlayer(nameWiner, posPlayer);
    Indie::Audio::Instance().setVolume(((float)Indie::Window::Instance().getWindowVolume() / 1000));
    if (Indie::Audio::Instance().getState() == 1) {
        Indie::Audio::Instance().stopPlayingGameMusic();
        Indie::Audio::Instance().startPlayingMenuMusic();
        Indie::Audio::Instance().setState(0);
    }
    Indie::Audio::Instance().startPlayingMenuMusic();
    auto &creditButton(entity.addEntity());
    Vector2 posText1 = { _SizeWindow.x / 12, _SizeWindow.y / 20};
    creditButton.addComponent<Indie::ButtonComponent>((_SizeWindow.x / 12), (_SizeWindow.y / 15), posText1, true, std::function<void()>(std::bind(&FinishGame::menuButton, this)), true);
    posText1 = { (_SizeWindow.x / 12), _SizeWindow.y / 20};
    creditButton.addComponent<Indie::TextComponent>(("Assets/FFF_Tusj.ttf"), "Menu", posText1, _SizeWindow.x / 64, RAYWHITE);
    posText1 = {(_SizeWindow.x / 12) - (creditButton.getComponent<Indie::TextComponent>().mesureText().x / 2), _SizeWindow.y / 20};
    creditButton.getComponent<Indie::TextComponent>().setPosition(posText1);
    _buttons = entity.getButton();
}

Indie::FinishGame::~FinishGame()
{
}

void Indie::FinishGame::menuButton()
{
    _exit = true;
}

bool Indie::FinishGame::update(double time)
{
    _cam->getComponent<Indie::CameraComponent>().update(time);
    _buttonsManagers.resetActiveButton(_buttons);
    _time += time;
    //if (time > 0.01) {
    //    _Player.back().get().getComponent<Indie::ModelComponent>().Animated();
    //}
    entity.refresh();
    entity.update(time);
    return false;
}

void Indie::FinishGame::draw()
{
    ClearBackground(BLACK);
    _background.front().get().draw();
    _buttons.back().get().draw();
    _cam->getComponent<Indie::CameraComponent>().Begin3DCameraMod();
    entity.draw();
    Indie::Audio::Instance().draw();
    EndMode3D();
    if (_exit)
        _manager.removeNbScene(3);
}

void Indie::FinishGame::createAndchangePlayer(std::string name, Vector3 pos)
{
    Vector3 scale = { 0.04f, 0.04f, 0.04f };
    float RotAng = -90.0f;
    Vector3 RotAx = { 1.0f, 0.0f, 0.0f };

    if ("Knight" == name)
        createNewPlayer(pos, name, "Assets/Champion/Knight/Knight.iqm", "Assets/Champion/Knight/KnightTexture.png", "Assets/Champion/Knight/Idle.iqm", scale);
    if ("Blitz"== name) {
        scale = { 1.4f, 1.4f, 1.4f };
        createNewPlayer(pos, name, "Assets/Champion/Blitzcrank/blitz_mesh.iqm", "Assets/Champion/Blitzcrank/Blitztank_Texture_edit3.png", "Assets/Champion/Blitzcrank/blitz_idle_animation.iqm", scale);
    } if ("Plant"== name) {
        scale = { 1.0f, 1.0f, 1.0f };
        createNewPlayer(pos, name, "Assets/Champion/Plant/plant.iqm", "Assets/Champion/Plant/textures/plant_texture.png", "Assets/Champion/Plant/idle.iqm", scale);
    } if ("Carlo"== name) {
        scale = { 0.4f, 0.4f, 0.4f };
        createNewPlayer(pos, name, "Assets/Champion/Carlo/Carlo.iqm", "Assets/Champion/Carlo/squidward.png", "Assets/Champion/Carlo/Carlo_idle.iqm", scale);
    } if ("Crash" == name) {
        scale = { 0.04f, 0.04f, 0.04f };
        createNewPlayer(pos, name, "Assets/Champion/Crash/Crash.iqm", "Assets/Champion/Crash/color_pallete_baseColor.png", "Assets/Champion/Crash/Crash_idle.iqm", scale);
    } if ("Krusty" == name) {
        scale = { 2.8f, 2.8f, 2.8f };
        createNewPlayer(pos, name, "Assets/Champion/Krusty/Krusty.iqm", "Assets/Champion/Krusty/char_swatches_lit_bmp.png", "Assets/Champion/Krusty/Krusty_idle.iqm", scale);
    } if ("Ralph" == name) {
        scale = { 4.0f, 4.0f, 4.0f };
        createNewPlayer(pos, name, "Assets/Champion/Ralph/Ralph.iqm", "Assets/Champion/Ralph/char_swatches_lit_bmp.png", "Assets/Champion/Ralph/Ralph_idle.iqm", scale);
    } if ("Spongebob" == name) {
        scale = { 0.6f, 0.6f, 0.6f };
        createNewPlayer(pos, name, "Assets/Champion/Spongebob/Spongebob.iqm", "Assets/Champion/Spongebob/chr_sb05.png", "Assets/Champion/Spongebob/Spongebob_idle.iqm", scale);
    }
}

void Indie::FinishGame::createNewPlayer(Vector3 pos, std::string name, std::string model, std::string texture, std::string animation, Vector3 scale)
{
    float RotAng = -90.0f;
    Vector3 RotAx = { 1.0f, 0.0f, 0.0f };

    auto& Player(entity.addEntity());
    Player.addComponent<Indie::ModelComponent>();
    _Player = entity.getModel();
    _Player.back().get().getComponent<Indie::ModelComponent>().setEverything(model, pos, RotAx, scale, RotAng);
    _Player.back().get().getComponent<Indie::ModelComponent>().setTexture(texture);
    _Player.back().get().getComponent<Indie::ModelComponent>().AddAnimation("Idle", animation);
    _Player.back().get().getComponent<Indie::ModelComponent>().PlayAnimation("Idle");
}