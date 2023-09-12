/*
** EPITECH PROJECT, 2021
** LoadSave.cpp
** File description:
** LoadSave.cpp
*/

#include "LoadSave.hpp"

Indie::LoadSave::LoadSave(Indie::SceneManager& manager) : Indie::AScene::AScene(manager), _IsItQuit(false)
{
    _SizeWindow.x = Indie::Window::Instance().getWindowSize().x;
    _SizeWindow.y = Indie::Window::Instance().getWindowSize().y;
    Vector2 posText = { 0, 0 };
    auto &background(entityManager.addEntity());
    auto &tity(entityManager.addEntity());
    background.addComponent<Indie::TwoDComponent>("Assets/LoadImage/backgroundLoadSave.png", _SizeWindow.x, _SizeWindow.y, posText);
    posText = { (_SizeWindow.x / 2 - 250), (_SizeWindow.y / 10) * 2 };
    tity.addComponent<Indie::TextComponent>( ("Assets/FFF_Tusj.ttf"), "Choose your save", posText, 60, BLACK);
    searchSaved();
    drawButtonWithText();
    _background = entityManager.getTwoDComponent();
    _Text = entityManager.getText();
}

Indie::LoadSave::~LoadSave()
{
}

bool Indie::LoadSave::update(double time)
{
    entityManager.refresh();
    entityManager.update(time);
    _buttonsManager.setActiveButton(_buttons, MAX_BUTTON);
    if (_IsItQuit) {
        _manager.removeNbScene(2);
    }
    return false;
}

void Indie::LoadSave::draw()
{
    ClearBackground(RAYWHITE);
    Indie::Audio::Instance().draw();
    entityManager.draw();
}

void Indie::LoadSave::searchSaved()
{
    std::ifstream file(exec_path + ("saved/save.txt"));
    std::string tmp;
    int i = 0;

    if (file.is_open())
        for (i = 0; std::getline(file, tmp); i++) {
            _SavedGame.push_back(splitStr(tmp, ';'));
        }
}

std::vector<std::string> Indie::LoadSave::splitStr(std::string str, char separate)
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


void Indie::LoadSave::manageSave(int b)
{
    if (_SavedGame[b].size() < 6)
        return;
    std::vector<std::string> _alive;
    int nbplayers;
    std::vector<std::vector<float>> _stats;
    int nb_p = std::stoi(_SavedGame[b].at(5));
    int still_alive = 4 - nb_p;
    int actual_number = 10 - still_alive;

    for (int i = 6; i != actual_number; i++) {
        ppos.push_back(splitStrToVector(_SavedGame[b].at(i), ','));
    }
    for (int i = actual_number; i != (actual_number + nb_p); i++) {
        _stats.push_back(splitStrToFloat(_SavedGame[b].at(i), ','));
    }
    actual_number += nb_p;
    for (int i = actual_number; i != (actual_number + nb_p); i++)
        _alive.push_back((_SavedGame[b].at(i)));
    actual_number += nb_p;
    nbplayers = std::stoi(_SavedGame[b].at(actual_number));
    actual_number++;
    std::vector<std::string> champ;
    for (int i = actual_number; i != (actual_number + nb_p); i++) {
        champ.push_back(_SavedGame[b].at(i));
    }
    actual_number += nb_p;
    for (int i = actual_number; i != _SavedGame[b].size(); i++) {
        wpos.push_back(splitStrToVector(_SavedGame[b].at(i), ','));
    }
    std::map<int, std::string> selectedcharacters;
    for (int i = 0; i != nb_p; i++)
        selectedcharacters.insert({ i, champ[i] });
    _manager.ScenePush<Indie::Game>(ppos, wpos, nbplayers, selectedcharacters, _alive, _stats);
}

Vector3 Indie::LoadSave::splitStrToVector(std::string str, char separate)
{
    size_t position = str.find(separate);
    size_t init = 0;
    std::vector<std::string> splitS;
    Vector3 ValueToReturn;

    ValueToReturn.x = std::stof(str.substr(init, position - init));
    init = position + 1;
    ValueToReturn.y = std::stof(str.substr(init, position - init));
    str = str.substr(init, position - init);
    position = str.find(separate);
    init = position + 1;
    ValueToReturn.z = std::stof(str.substr(init, position - init));

    return ValueToReturn;
}

std::vector<float> Indie::LoadSave::splitStrToFloat(std::string str, char separate)
{
    size_t position = str.find(separate);
    size_t init = 0;
    std::vector<std::string> splitS;
    std::vector<float> ValueToReturn;

    ValueToReturn.push_back(std::stof(str.substr(init, position - init)));
    init = position + 1;
    ValueToReturn.push_back(std::stof(str.substr(init, position - init)));
    str = str.substr(init, position - init);
    position = str.find(separate);
    init = position + 1;
    ValueToReturn.push_back(std::stof(str.substr(init, position - init)));
    str = str.substr(init, position - init);
    position = str.find(separate);
    init = position + 1;
    ValueToReturn.push_back(std::stof(str.substr(init, position - init)));
    return ValueToReturn;
}

void Indie::LoadSave::changeValueAndScene()
{
    int b = 0;

    for (auto _tmp : _buttons) {
        _selectedButton = b;
        if (_tmp.get().getComponent<Indie::ButtonComponent>().isSelected() == 1) {
            manageSave(b);
        }
        b++;
    }
}

void Indie::LoadSave::backButton()
{
    _IsItQuit = true;
}

void Indie::LoadSave::drawButtonWithText()
{
    Vector2 posText1;
    Vector2 posText2;
    for (int i = 1; i <= 5; i++) {
        auto &tity(entityManager.addEntity());
        posText1 = { (_SizeWindow.x / 6), (_SizeWindow.y / 10) * (4 + (i - 1)) * 2 };
        tity.addComponent<Indie::ButtonComponent>((_SizeWindow.x / 6) * 5, (_SizeWindow.y / 10), posText1, true, std::function<void()>(std::bind(&LoadSave::changeValueAndScene, this)), true);
        posText1 = { posText1.x * (float)1.5, (_SizeWindow.y / 10) * (3 + i) + 10 };
        tity.addComponent<Indie::TextComponent>( ("Assets/FFF_Tusj.ttf"), "File " + _SavedGame[i - 1].at(0), posText1, _SizeWindow.x / 64, RAYWHITE);
        posText2 = { (_SizeWindow.x / 6) * (float)0.7, (_SizeWindow.y / 10) * (3 + i) + 10 };
        tity.addComponent<Indie::TwoDComponent>("Assets/LoadImage/" + _SavedGame[i - 1].at(2), 170, 100, posText2);
        posText1 = { posText1.x, (_SizeWindow.y / 10) * (3 + i) + 45 };
        tity.addComponent<Indie::TextComponent>( ("Assets/FFF_Tusj.ttf"), _SavedGame[i - 1].at(1), posText1, _SizeWindow.x / 64, RAYWHITE);
        posText1 = { posText1.x, (_SizeWindow.y / 10) * (3 + i) + 80 };
        if (_SavedGame[i - 1].at(3) != "0")
            tity.addComponent<Indie::TextComponent>( ("Assets/FFF_Tusj.ttf"), "Actual score : " + _SavedGame[i - 1].at(3), posText1, _SizeWindow.x / 64, RAYWHITE);
        posText1 = { (_SizeWindow.x / 6) * (float)4.5, (_SizeWindow.y / 10) * (3 + i) + 10 };
        if (_SavedGame[i - 1].at(4) != "NA")
            tity.addComponent<Indie::TextComponent>( ("Assets/FFF_Tusj.ttf"), _SavedGame[i - 1].at(4), posText1, _SizeWindow.x / 64, BLACK);
    }
    auto &backButton(entityManager.addEntity());
    posText1 = { _SizeWindow.x / 12, _SizeWindow.y / 20};
    backButton.addComponent<Indie::ButtonComponent>((_SizeWindow.x / 12), (_SizeWindow.y / 15), posText1, true, std::function<void()>(std::bind(&LoadSave::backButton, this)), true);
    posText1 = { (_SizeWindow.x / 12), _SizeWindow.y / 20};
    backButton.addComponent<Indie::TextComponent>(("Assets/FFF_Tusj.ttf"), "Back", posText1, _SizeWindow.x / 64, RAYWHITE);
    posText1 = {(_SizeWindow.x / 12) - (backButton.getComponent<Indie::TextComponent>().mesureText().x / 2), _SizeWindow.y / 20};
    backButton.getComponent<Indie::TextComponent>().setPosition(posText1);
    _buttons = entityManager.getButton();
}