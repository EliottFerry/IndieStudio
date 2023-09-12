/*
** EPITECH PROJECT, 2021
** Loading.cpp
** File description:
** Loading.cpp
*/

#include "Loading.hpp"

Indie::Loading::Loading(Indie::SceneManager& manager, std::string nextScene) : Indie::AScene::AScene(manager), framesCounter(0), _nextScene(nextScene)
{
    Vector2 tmp = { 30.0f, Indie::Window::Instance().getWindowSize().y - 70 };
    loadingText = "Loading.";
    auto &text(entityManager.addEntity());
    text.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", loadingText.c_str(), tmp, 40, RAYWHITE);
    _Text = entityManager.getText();
}

Indie::Loading::Loading(Indie::SceneManager& manager, std::string nextScene, int nbPlayers, std::map<int, std::string> _SelectedCharacters) : Indie::AScene::AScene(manager), framesCounter(0), _nextScene(nextScene)
{
    _nbPlayers = nbPlayers;
    _SelectedPlayers = _SelectedCharacters;
    Vector2 tmp = { 30.0f, Indie::Window::Instance().getWindowSize().y - 70 };
    loadingText = "Loading.";
    auto &text(entityManager.addEntity());
    text.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", loadingText.c_str(), tmp, 40, RAYWHITE);
    _Text = entityManager.getText();
}

Indie::Loading::~Loading()
{
}

bool Indie::Loading::update(double time)
{
    framesCounter++;
    if (time > 0.01607 && (framesCounter / 20) % 2) {
        framesCounter = 0;
        loadingText.insert(loadingText.size(), ".");
        if (loadingText.compare(7, 4, "....") == 0)
            loadingText = "Loading";
            _Text.front().get().getComponent<Indie::TextComponent>().setText(loadingText);
    }
    entityManager.refresh();
    entityManager.update(time);
    if (_nextScene == "LoadSave")
        _manager.ScenePush<Indie::LoadSave>();
    if (_nextScene == "NewGame")
        _manager.ScenePush<Indie::CreateNewGame>();
    if (_nextScene == "Option")
        _manager.ScenePush<Indie::Options>();
    if (_nextScene == "Play")
        _manager.ScenePush<Indie::Game>(_nbPlayers, _SelectedPlayers);
    return false;
}

void Indie::Loading::draw()
{
    ClearBackground(BLACK);
    Indie::Audio::Instance().draw();
    entityManager.draw();
}