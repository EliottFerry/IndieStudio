/*
** EPITECH PROJECT, 2021
** CreateSave.cpp
** File description:
** CreateSave.cpp
*/

#include "CreateSave.hpp"

Indie::CreateSave::CreateSave(Indie::SceneManager& manager, std::vector<Vector3> _statsPosTmp, std::vector<int> _aliveTmp, std::vector<Vector3> _walltmp, std::vector<std::string> _champ, std::vector<float> statsplayers) : Indie::AScene::AScene(manager), _IsItQuit(true)
{
    _SizeWindow.x = Indie::Window::Instance().getWindowSize().x;
    _SizeWindow.y = Indie::Window::Instance().getWindowSize().y;
    _statsPos = _statsPosTmp;
    _alive = _aliveTmp;
    _wallPos = _walltmp;
    _champName = _champ;
    _stats = statsplayers;
    Vector2 posText = { 0, 0 };
    auto& background(entityManager.addEntity());
    auto& tity(entityManager.addEntity());
    Vector2 tmp = { 1000, 1000 };
    background.addComponent<Indie::TwoDComponent>("Assets/LoadImage/backgroundLoadSave.png", _SizeWindow.x, _SizeWindow.y, posText);
    posText = { (_SizeWindow.x / 2 - 250), (_SizeWindow.y / 10) * 2 };
    tity.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "Choose a file to save", posText, 60, BLACK);
    searchSaved();
    drawButtonWithText();
    if (_IsItQuit == false)
        return;
    auto& box(entityManager.addEntity());
    box.addComponent<Indie::BoxComponent>(500, 180, 500, 500);
    auto& txt(entityManager.addEntity());
    txt.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "", posText, _SizeWindow.x / 64, BLACK);
    _background = entityManager.getTwoDComponent();
    _box = entityManager.getBox();
    _Text = entityManager.getText();
}

Indie::CreateSave::~CreateSave()
{
}

bool Indie::CreateSave::update(double time)
{
    int letterCount = 0;

    _buttonsManager.resetActiveButton(_buttons);
    entityManager.refresh();
    entityManager.update(time);
    if (_box.front().get().getComponent<Indie::BoxComponent>().isDrawn() == true && _save == false) {
        int key = GetCharPressed();
        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (letterCount < 9))
            {
                _saveName.push_back((char)key);
                letterCount++;
            }

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            if (_saveName.size() != 0) {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                _saveName.erase(_saveName.size() - 1);
            }
        }
        if (IsKeyPressed(KEY_ENTER))
            _save = true;
        _Text.back().get().getComponent<Indie::TextComponent>().setText(std::string(_saveName));

    }
    else if (!_box.front().get().getComponent<Indie::BoxComponent>().isDrawn())
        _buttonsManager.setActiveButton(_buttons, MAX_BUTTON);
    if (_IsItQuit == false)
        _manager.removeScene();
    return false;
}

void Indie::CreateSave::draw()
{
    ClearBackground(RAYWHITE);
    entityManager.draw();
}


void Indie::CreateSave::searchSaved()
{
    std::ifstream file(exec_path + ("saved/save.txt"));
    std::string tmp;
    int i = 0;

    if (file.is_open())
        for (i = 0; std::getline(file, tmp); i++) {
            _SavedGameUnparsed.push_back(tmp);
            _SavedGame.push_back(splitStr(tmp, ';'));
        }
}

std::vector<std::string> Indie::CreateSave::splitStr(std::string str, char separate)
{
    std::vector<std::string> splitS;
    std::string word = "";

    for (auto x : str) {
        if (x == ';') {
            splitS.push_back(word);
            word = "";
        }
        else
            word = word + x;
    }
    return (splitS);
}

bool Indie::CreateSave::manageSave(int b)
{
    std::ofstream file;
    std::string tmp2;
    int i = 0;
    std::vector<std::string> tmp1;
    std::string _newPathImg = "Assets/LoadImage/picture" + std::to_string(b) + ".png";
    std::string _nameImg = "picture" + std::to_string(b) + ".png";
    time_t now = time(0);
    std::string tmpwallpos = "";

    _score = '0';
    _time = (std::string)ctime(&now);
    _time.pop_back();
    for (int i = 0; i != _wallPos.size(); i++)
        tmpwallpos += std::to_string(_wallPos[i].x) + ", " + std::to_string(_wallPos[i].y) + ", " + std::to_string(_wallPos[i].z) + ";";
    if (remove((exec_path + (_newPathImg)).c_str()) != 0)
        if (rename((exec_path + ("Assets/LoadImage/tmp.png")).c_str(), (exec_path + (_newPathImg)).c_str()) != 0)
            manageSave(b);
    std::filesystem::copy((exec_path + ("Assets/LoadImage/tmp.png")).c_str(), (exec_path + (_newPathImg)).c_str());
    tmp2 += std::to_string(b) + ";" + _saveName + ";" + _nameImg + ";" + _score + ";" + _time + ";";
    tmp2 += std::to_string(_alive.size() - 1) + ";";
    for (auto& tmppos : _statsPos)
        tmp2 += std::to_string(tmppos.x) + ", " + std::to_string(tmppos.y) + ", " + std::to_string(tmppos.z) + ";";
    int x = 1;
    for (auto& tmpstats : _stats) {
        tmp2 += std::to_string(tmpstats);
        if (x % 4 == 0)
            tmp2 += ";";
        else
            tmp2 += ", ";
        x++;
    }
    for (auto& tmpalive : _alive)
        tmp2 += std::to_string(tmpalive) + ";";
    for (auto& tmpchamp : _champName)
        tmp2 += tmpchamp + ";";
    tmp2 += tmpwallpos;
    for (auto& tmp : _SavedGameUnparsed) {
        if (i != b) {
            tmp1.push_back(tmp);
        }
        else {
            tmp = tmp2;
            tmp1.push_back(tmp);
        }
        i++;
    }
    file.open(exec_path + ("saved/save.txt"));
    for (auto& subVec : tmp1) {
        for (auto& str : subVec) {
            file << str;
        }
        file << std::endl;
    }
    _IsItQuit = false;
    return false;
}


void Indie::CreateSave::changeValueAndScene()
{
    int b = 0;
    
    _box.front().get().getComponent<Indie::BoxComponent>().mustDraw();
    _Text.back().get().getComponent<Indie::TextComponent>().setSize(16);
    Vector2 tmp = { _box.front().get().getComponent<Indie::BoxComponent>().getPosition().x, _box.front().get().getComponent<Indie::BoxComponent>().getPosition().y};
    _Text.back().get().getComponent<Indie::TextComponent>().setPosition(tmp);
    _Text.front().get().getComponent<Indie::TextComponent>().setText("Press Enter to save");
    tmp = { tmp.x, tmp.y + 200 };
    _Text.back().get().getComponent<Indie::TextComponent>().setPosition(tmp);

    if (_box.front().get().getComponent<Indie::BoxComponent>().isDrawn() == true)
        _Text.back().get().getComponent<Indie::TextComponent>().setDrawable(true);
    else
        _Text.back().get().getComponent<Indie::TextComponent>().setDrawable(false);
    for (auto _tmp : _buttons) {
        _selectedButton = b;
        if (_tmp.get().getComponent<Indie::ButtonComponent>().isSelected() == true && _save == true) {
            if (manageSave(b) == false)
                return;
        }
        b++;
    }
}

void Indie::CreateSave::backButton()
{
    _IsItQuit = false;
}

void Indie::CreateSave::drawButtonWithText()
{
    Vector2 posText1;
    Vector2 posText2;
    for (int i = 1; i <= 5; i++) {
        auto& tity(entityManager.addEntity());
        posText1 = { (_SizeWindow.x / 6), (_SizeWindow.y / 10) * (4 + (i - 1)) * 2 };
        tity.addComponent<Indie::ButtonComponent>((_SizeWindow.x / 6) * 5, (_SizeWindow.y / 10), posText1, true, std::function<void()>(std::bind(&CreateSave::changeValueAndScene, this)), true);
        posText1 = { posText1.x * (float)1.5, (_SizeWindow.y / 10) * (3 + i) + 10 };
        tity.addComponent<Indie::TextComponent>(("Assets/FFF_Tusj.ttf"), "File " + _SavedGame[i - 1].at(0), posText1, _SizeWindow.x / 64, RAYWHITE);
        posText2 = { (_SizeWindow.x / 6) * (float)0.7, (_SizeWindow.y / 10) * (3 + i) + 10 };
        tity.addComponent<Indie::TwoDComponent>("Assets/LoadImage/" + _SavedGame[i - 1].at(2), 170, 100, posText2);
        posText1 = { posText1.x, (_SizeWindow.y / 10) * (3 + i) + 45 };
        tity.addComponent<Indie::TextComponent>(("Assets/FFF_Tusj.ttf"), _SavedGame[i - 1].at(1), posText1, _SizeWindow.x / 64, RAYWHITE);
        posText1 = { posText1.x, (_SizeWindow.y / 10) * (3 + i) + 80 };
        if (_SavedGame[i - 1].at(3) != "0")
            tity.addComponent<Indie::TextComponent>(("Assets/FFF_Tusj.ttf"), "Actual score : " + _SavedGame[i - 1].at(3), posText1, _SizeWindow.x / 64, RAYWHITE);
        posText1 = { (_SizeWindow.x / 6) * (float)4.5, (_SizeWindow.y / 10) * (3 + i) + 10 };
        if (_SavedGame[i - 1].at(4) != "NA")
            tity.addComponent<Indie::TextComponent>(("Assets/FFF_Tusj.ttf"), _SavedGame[i - 1].at(4), posText1, _SizeWindow.x / 64, BLACK);
    }
    auto &backButton(entityManager.addEntity());
    posText1 = { _SizeWindow.x / 12, _SizeWindow.y / 20};
    backButton.addComponent<Indie::ButtonComponent>((_SizeWindow.x / 12), (_SizeWindow.y / 15), posText1, true, std::function<void()>(std::bind(&CreateSave::backButton, this)), true);
    posText1 = { (_SizeWindow.x / 12), _SizeWindow.y / 20};
    backButton.addComponent<Indie::TextComponent>(("Assets/FFF_Tusj.ttf"), "Back", posText1, _SizeWindow.x / 64, RAYWHITE);
    posText1 = {(_SizeWindow.x / 12) - (backButton.getComponent<Indie::TextComponent>().mesureText().x / 2), _SizeWindow.y / 20};
    backButton.getComponent<Indie::TextComponent>().setPosition(posText1);
    _buttons = entityManager.getButton();
}