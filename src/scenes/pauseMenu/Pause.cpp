/*
** EPITECH PROJECT, 2021
** Pause.cpp
** File description:
** Pause.cpp
*/

#include "Pause.hpp"

Indie::Pause::Pause(Indie::SceneManager& manager, EntityManager& entity, std::vector<Vector3> _tmpwall, int nbPlayers) : Indie::AScene::AScene(manager)
{
    _SizeWindow.x = Indie::Window::Instance().getWindowSize().x;
    _SizeWindow.y = Indie::Window::Instance().getWindowSize().y;
    Vector2 posText = { 0, 0};
    _tmpwallpos = _tmpwall;
    if (nbPlayers == 0) {
        _statsPosTmp.push_back({ entity.getPlayer().front().get().getComponent < Indie::Player>().getPosition() });
        for (auto& tmp : entity.getBombermanAI())
            _statsPosTmp.push_back({tmp.get().getComponent<Indie::BombermanAI>().getPosition()});
        _aliveTmp.push_back(entity.getPlayer().front().get().getComponent<Indie::Player>().isAlive());
        for (auto& tmp : entity.getBombermanAI())
            _aliveTmp.push_back(tmp.get().getComponent<Indie::BombermanAI>().isAlive());
    }
    else {
        for (auto& tmp : entity.getPlayer()) {
            _statsPosTmp.push_back({ tmp.get().getComponent<Indie::Player>().getPosition() });
        }
        for (auto& tmp : entity.getBombermanAI())
            _statsPosTmp.push_back({ tmp.get().getComponent<Indie::BombermanAI>().getPosition() });
        for (auto& tmp : entity.getPlayer())
            _aliveTmp.push_back(tmp.get().getComponent<Indie::Player>().isAlive());
        for (auto& tmp : entity.getBombermanAI())
            _aliveTmp.push_back(tmp.get().getComponent<Indie::BombermanAI>().isAlive());
    }
    for (auto& tmp : entity.getPlayer())
        for (int i = 0; i != tmp.get().getComponent<Indie::Player>().getStats().size(); i++)
            _statsplayers.push_back(tmp.get().getComponent < Indie::Player>().getStats()[i]);
    for (auto& tmp : entity.getBombermanAI())
        for (int i = 0; i != tmp.get().getComponent<Indie::BombermanAI>().getStats().size(); i++)
            _statsplayers.push_back(tmp.get().getComponent < Indie::BombermanAI>().getStats()[i]);
    for (auto& tmp : entity.getPlayer())
        _champName.push_back(tmp.get().getComponent<Indie::Player>().getChamp());
    for (auto& tmp : entity.getBombermanAI())
        _champName.push_back(tmp.get().getComponent < Indie::BombermanAI>().getChamp());
    _aliveTmp.push_back(nbPlayers);
    auto &background(entityManager.addEntity());
    auto &tity(entityManager.addEntity());
    background.addComponent<Indie::TwoDComponent>("Assets/LoadImage/tmp.png", _SizeWindow.x, _SizeWindow.y, posText);
    posText = { (_SizeWindow.x / 2), (_SizeWindow.y / 10) * 2 };
    tity.addComponent<Indie::TextComponent>( ("Assets/FFF_Tusj.ttf"), "Pause", posText, 80, BLACK);
    posText = { posText.x - tity.getComponent<Indie::TextComponent>().mesureText().x / 2, (_SizeWindow.y / 10) * 2 };
    tity.getComponent<Indie::TextComponent>().setPosition(posText);
    drawButtonWithText();
    _background = entityManager.getTwoDComponent();
    _Text = entityManager.getText();
}

Indie::Pause::~Pause()
{
}

bool Indie::Pause::update(double time)
{
    static bool loaded = false;

    _buttonManager.resetActiveButton(_buttons);
    entityManager.refresh();
    entityManager.update(time);
    _buttonManager.setActiveButton(_buttons, 4);
    if (_exit == true)
        return true;
    if (_IsItQuit == false)
        _manager.removeScene();
    if (::IsKeyReleased(KEY_ESCAPE) && loaded) 
        _IsItQuit = false;
    loaded = true;
    return false;
}

void Indie::Pause::draw()
{
    ::ClearBackground(RAYWHITE);
    Indie::Audio::Instance().draw();
    entityManager.draw();
}

std::vector<std::string> Indie::Pause::splitStr(std::string str, char separate)
{
    std::vector<std::string> splitS;
    std::string word = "";

    for (auto x : str) {
        if (x == ';') {
            splitS.push_back(word);
            word = "";
        } else
            word = word + x;
    }
    return (splitS);
}

void Indie::Pause::changeValueAndScene()
{
    int b = 0;

    for (auto tmp : _buttons) {
        if (tmp.get().getComponent<Indie::ButtonComponent>().isSelected() == 1) {
            if (b == 0)
                _IsItQuit = false;
            if (b == 1)
                _manager.ScenePush<Indie::Options>();
            if (b == 2)
                _manager.ScenePush<Indie::CreateSave>(_statsPosTmp, _aliveTmp, _tmpwallpos, _champName, _statsplayers);
            if (b == 3)
                _exit = true;
        }
        b++;
    }
}

void Indie::Pause::drawButtonWithText()
{
    Vector2 posText1;
    Vector2 posText2;
    std::vector<std::string> str = { "Resume", "Options", "Save", "Quit" };
    for (int i = 0; i <= MAX_BUT; i++) {
        auto& tity(entityManager.addEntity());
        posText1 = { (_SizeWindow.x / 6) * 2 * 2, (_SizeWindow.y / 10) * (5 + (i - 1)) * 2 };
        tity.addComponent<Indie::ButtonComponent>((_SizeWindow.x / 6) * 2, (_SizeWindow.y / 10), posText1, true, std::function<void()>(std::bind(&Pause::changeValueAndScene, this)), true);
        posText1 = { posText1.x / 2 + (_SizeWindow.x / 6), (_SizeWindow.y / 10) * (4 + i) + 10 };
        tity.addComponent<Indie::TextComponent>( ("Assets/FFF_Tusj.ttf"), str[i], posText1, 50, RAYWHITE);
        posText1 = { posText1.x - tity.getComponent<Indie::TextComponent>().mesureText().x / 2, (_SizeWindow.y / 10) * (4 + i) + ((_SizeWindow.y / 10) / 2 - (tity.getComponent<Indie::TextComponent>().mesureText().y / 2)) };
        tity.getComponent<Indie::TextComponent>().setPosition(posText1);
        _buttons = entityManager.getButton();
    }
}