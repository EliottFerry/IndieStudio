/*
** EPITECH PROJECT, 2021
** CreateNewGame.cpp
** File description:
** CreateNewGame.cpp
*/

#include "CreateNewGame.hpp"

Indie::CreateNewGame::CreateNewGame(Indie::SceneManager& manager) : Indie::AScene::AScene(manager), _nbGamePad(0), _beginCreated(-1), _selectedChamp(1), _selectedChampP1(NB_PERSO + PANCARTE + 2), _validSelectedChamp(0)
{
    Vector2 posImage = { 0, 0 };
    _SizeWindow.x = Indie::Window::Instance().getWindowSize().x;
    _SizeWindow.y = Indie::Window::Instance().getWindowSize().y;
    auto &background(entityManager.addEntity());
    background.addComponent<Indie::TwoDComponent>("Assets/Newgame/table3.png", _SizeWindow.x, _SizeWindow.y, posImage);
    _background = entityManager.getTwoDComponent();
    auto& cam(entityManager.addEntity());
    cam.addComponent<Indie::CameraComponent>();
    _cam = &entityManager.getCamera();
    _cam->getComponent<Indie::CameraComponent>().SetEverythingCamera({ 6.5f, 0.0f, 5.0f }, { 0.0f, 1.0f, -70.0f }, { 6.5f, 15.0f, 15.0f });
    createPancarteWithtext();
    addNewPlayer({ 0, 0, 0 }, _Player);
    if (GetGamepadName(0) != NULL) {
        addNewPlayer({ 11.8, 0.0, 0.0 }, _PlayerP1);
        _nbGamePad++;
        _beginCreated = 0;
    }
}

Indie::CreateNewGame::~CreateNewGame()
{
}

bool Indie::CreateNewGame::update(double time)
{
    _cam->getComponent<Indie::CameraComponent>().update(time);
    _time += time;
    _timeChamp += time;
    if (_time > 0.01) {
        if (manageSelectedKey() == false)
            return false;
        checkGamePad();
        //animateAllPlayer();
        changeChampionKeyboard();
        if (_timeChamp > 0.08) {
            changeChampionGamepad();
            _timeChamp = 0.0;
        }
        _time = 0.0;
    }
    entityManager.refresh();
    entityManager.update(time);
    return false;
}

void Indie::CreateNewGame::draw()
{
    _background.front().get().draw();
    _cam->getComponent<Indie::CameraComponent>().Begin3DCameraMod();
    entityManager.draw();
    Indie::Audio::Instance().draw();
    EndMode3D();
}

void Indie::CreateNewGame::addNewPlayer(Vector3 initPosPlayer, std::list<std::reference_wrapper<Indie::Entity>>& player)
{
    Vector3 scale = { 0.02f, 0.02f, 0.02f };
    float RotAng = -90.0f;
    Vector3 RotAx = { 1.0f, 0.0f, 0.0f };
    Vector3 pos = { 1.6f + initPosPlayer.x, 0.1f + initPosPlayer.y, 1.0f + initPosPlayer.z};
    if (_PlayerP1.empty() && !_Player.empty())
        pos = { 0.5f + initPosPlayer.x, 0.1f + initPosPlayer.y, 1.0f + initPosPlayer.z};
    createAndchangePlayer(pos, "knight", player);
    auto& Arrows(entityManager.addEntity());
    Arrows.addComponent<Indie::ModelComponent>();
    _Buttons = entityManager.getModel();
    scale = { 0.3f, 0.3f, 0.3f };
    RotAng = -60.0f;
    RotAx = { 1.0f, 0.0f, 0.0f };
    pos = { -2.0f + initPosPlayer.x, 0.0f + initPosPlayer.y, -1.0f + initPosPlayer.z };
    _Buttons.back().get().getComponent<Indie::ModelComponent>().setEverything("Assets/Fleche/flecheps.obj", pos, RotAx, scale, RotAng);
    auto& Arrows1(entityManager.addEntity());
    Arrows1.addComponent<Indie::ModelComponent>();
    _Buttons = entityManager.getModel();
    RotAng = -60.0f;
    RotAx = { 1.0f, 0.0f, 0.0f };
    pos = { 4.0f + initPosPlayer.x, 0.0f + initPosPlayer.y, -1.0f + initPosPlayer.z};
    _Buttons.back().get().getComponent<Indie::ModelComponent>().setEverything("Assets/Fleche/fleche.obj", pos, RotAx, scale, RotAng);
}

void Indie::CreateNewGame::animateAllPlayer()
{
    int i = 0;

    for (auto& tmp : _Player) {
        if (i == _selectedChamp || i + 100 == _selectedChamp)
            tmp.get().getComponent<Indie::ModelComponent>().Animated();
        i++;
    }
    i = 0;
    for (auto& tmp : _PlayerP1) {
        if (i == _selectedChampP1 || i + 100 == _selectedChampP1)
            tmp.get().getComponent<Indie::ModelComponent>().Animated();
        i++;
    }
}

void Indie::CreateNewGame::checkGamePad()
{
    int i = 0;

    if (GetGamepadName(0) == NULL && _nbGamePad > 0) {
        for (auto& tmp : _Buttons) {
            if (i > NB_PERSO + PANCARTE + 1)
                tmp.get().getComponent<Indie::ModelComponent>().setDrawable(false);
            i++;
        }
        _selectedChampP1 = 2 + NB_PERSO + PANCARTE;
        _alreadyDraw = false;
    } if (GetGamepadName(0) != NULL && _nbGamePad == 0) {
        addNewPlayer({ 12.0, 0.0, 0.0 }, _PlayerP1);
        _nbGamePad++;
    } if (GetGamepadName(0) != NULL && _nbGamePad == 1 && _alreadyDraw == false) {
        for (auto& tmp : _Buttons) {
            if (i > NB_PERSO + PANCARTE + 1 && (_selectedChampP1 == i || i == _Buttons.size() - 1 || i == _Buttons.size() - 2))
                tmp.get().getComponent<Indie::ModelComponent>().setDrawable(true);
            i++;
        }
        _alreadyDraw = true;
    }
}

void Indie::CreateNewGame::changeChampionKeyboard()
{
    int i = 0;
    if (_selectedChamp < 100) {
        setDrawableThisButton(NB_PERSO + PANCARTE, true);
        setDrawableThisButton(NB_PERSO + PANCARTE + 1, true);
    } else
        return;
    if (::IsKeyPressed(KEY_RIGHT)) {
        i = 0;
        _selectedChamp++;
        if (_selectedChamp == NB_PERSO + PANCARTE)
            _selectedChamp = PANCARTE;
        for (auto& tmp : _Player) {
            tmp.get().getComponent<Indie::ModelComponent>().setDrawable(false);
            if (i == _selectedChamp)
                tmp.get().getComponent<Indie::ModelComponent>().setDrawable(true);
            i++;
        }
        setDrawableThisButton(NB_PERSO + PANCARTE + 1, false);
    } else if (::IsKeyPressed(KEY_LEFT)) {
        _selectedChamp--;
        if (_selectedChamp < PANCARTE)
            _selectedChamp = NB_PERSO + PANCARTE - 1;
        for (auto& tmp : _Player) {
            tmp.get().getComponent<Indie::ModelComponent>().setDrawable(false);
            if (i == _selectedChamp)
                tmp.get().getComponent<Indie::ModelComponent>().setDrawable(true);
            i++;
        }
        setDrawableThisButton(NB_PERSO + PANCARTE, false);
    }
    if (_selectedChamp == PANCARTE)
        _player1 = "Knight";
    else if (_selectedChamp == PANCARTE + 1)
        _player1 = "Blitz";
    else if (_selectedChamp == PANCARTE + 2)
        _player1 = "Plant";
    else if (_selectedChamp == PANCARTE + 3)
        _player1 = "Carlo";
    else if (_selectedChamp == PANCARTE + 4)
        _player1 = "Crash";
    else if (_selectedChamp == PANCARTE + 5)
        _player1 = "Krusty";
    else if (_selectedChamp == PANCARTE + 6)
        _player1 = "Ralph";
    else if (_selectedChamp == PANCARTE + 7)
        _player1 = "Spongebob";
}

void Indie::CreateNewGame::changeChampionGamepad()
{
    int i = 0;
    if (GetGamepadName(0) != NULL && _selectedChampP1 < 100) {
        setDrawableThisButton(_Buttons.size() - 1, true);
        setDrawableThisButton(_Buttons.size() - 2, true);
    } else if (_selectedChampP1 >= 100)
        return;
    if (_nbGamePad == 1 && GetGamepadAxisMovement(0, 0) == 1) {
        _selectedChampP1++;
        if (_selectedChampP1 > _PlayerP1.size() - 1)
            _selectedChampP1 = 2 + PANCARTE + NB_PERSO;
        for (auto& tmp : _PlayerP1) {
            if (i > NB_PERSO + PANCARTE + 1) {
                tmp.get().getComponent<Indie::ModelComponent>().setDrawable(false);
                if (i == _selectedChampP1)
                    tmp.get().getComponent<Indie::ModelComponent>().setDrawable(true);
            }
            i++;
        }
        setDrawableThisButton(_Buttons.size() - 1, false);
    } else if (_nbGamePad == 1 && GetGamepadAxisMovement(0, 0) == -1) {
        _selectedChampP1--;
        if (_selectedChampP1 < NB_PERSO + PANCARTE + 2)
            _selectedChampP1 = _PlayerP1.size() - 1;
        for (auto& tmp : _PlayerP1) {
            if (i > NB_PERSO + PANCARTE + 1) {
                tmp.get().getComponent<Indie::ModelComponent>().setDrawable(false);
                if (i == _selectedChampP1)
                    tmp.get().getComponent<Indie::ModelComponent>().setDrawable(true);
            }
            i++;
        }
        setDrawableThisButton(_Buttons.size() - 2, false);
    }
    if (_selectedChampP1 ==  2 + NB_PERSO + PANCARTE)
        _player2 = "Knight";
    else if (_selectedChampP1 == 3 + NB_PERSO + PANCARTE)
        _player2 = "Blitz";
    else if (_selectedChampP1 == 4 + NB_PERSO + PANCARTE)
        _player2 = "Plant";
    else if (_selectedChampP1 == 5 + NB_PERSO + PANCARTE)
        _player2 = "Carlo";
    else if (_selectedChampP1 == 6 + NB_PERSO + PANCARTE)
        _player2 = "Crash";
    else if (_selectedChampP1 == 7 + NB_PERSO + PANCARTE)
        _player2 = "Krusty";
    else if (_selectedChampP1 == 8 + NB_PERSO + PANCARTE)
        _player2 = "Ralph";
    else if (_selectedChampP1 == 9 + NB_PERSO + PANCARTE)
        _player2 = "Spongebob";
}

void Indie::CreateNewGame::setDrawableThisButton(int nbButt, bool drawable)
{
    int i = 0;

    for (auto& tmp : _Buttons) {
        if (i == nbButt)
            tmp.get().getComponent<Indie::ModelComponent>().setDrawable(drawable);
        i++;
    }
}

bool Indie::CreateNewGame::manageSelectedKey()
{
    if (::IsKeyPressed(KEY_ENTER) && _selectedChamp < 100) {
        _validSelectedChamp++;
        _selectedChamp += 100;
        _SelectedCharacters[0] = _player1;
        setDrawableThisButton(NB_PERSO + PANCARTE, false);
        setDrawableThisButton(NB_PERSO + PANCARTE + 1, false);
        return true;
    } if (IsGamepadButtonDown(0, 7) && _selectedChampP1 < 100) {
        _validSelectedChamp++;
        _selectedChampP1 += 100;
        _SelectedCharacters[1] = _player2;
        setDrawableThisButton(_Buttons.size() - 2, false);
        setDrawableThisButton(_Buttons.size() - 1, false);
    } if (::IsKeyPressed(KEY_ENTER) && _selectedChamp >= 100 && (_selectedChampP1 >= 100 || GetGamepadName(0) == NULL))
        _manager.ScenePush<Indie::Loading>("Play", _nbGamePad, _SelectedCharacters);
    if (::IsKeyPressed(KEY_B)) {
        _manager.removeNbScene(2);
        return false;
    } if (_validSelectedChamp == _nbGamePad + 1) {
        _Text.back().get().getComponent<Indie::TextComponent>().setSize(200);
        _Text.back().get().getComponent<Indie::TextComponent>().setDrawable(true);
        setDrawableThisButton(0, true);
    } else
        setDrawableThisButton(0, false);
    if (::IsKeyDown(KEY_ESCAPE) && _selectedChamp > 100) {
        _selectedChamp -= 100;
        _validSelectedChamp--;
        _Text.back().get().getComponent<Indie::TextComponent>().setDrawable(false);
    }
    if (IsGamepadButtonDown(0, 6) && _selectedChampP1 > 100) {
        _selectedChampP1 -= 100;
        _validSelectedChamp--;
        _Text.back().get().getComponent<Indie::TextComponent>().setDrawable(false);
    }
    return true;
}

void Indie::CreateNewGame::createAndchangePlayer(Vector3 pos, std::string name, std::list<std::reference_wrapper<Indie::Entity>>& player)
{
    Vector3 scale = { 0.02f, 0.02f, 0.02f };
    float RotAng = -90.0f;
    Vector3 RotAx = { 1.0f, 0.0f, 0.0f };

    createNewPlayer(pos, name, player, "Assets/Champion/Knight/Knight.iqm", "Assets/Champion/Knight/KnightTexture.png", "Assets/Champion/Knight/Idle.iqm", scale, "knight");
    scale = { 0.7f, 0.7f, 0.7f };
    createNewPlayer(pos, name, player, "Assets/Champion/Blitzcrank/blitz_mesh.iqm", "Assets/Champion/Blitzcrank/Blitztank_Texture_edit3.png", "Assets/Champion/Blitzcrank/blitz_idle_animation.iqm", scale, "blitz");
    scale = { 0.5f, 0.5f, 0.5f };
    createNewPlayer(pos, name, player, "Assets/Champion/Plant/plant.iqm", "Assets/Champion/Plant/textures/plant_texture.png", "Assets/Champion/Plant/idle.iqm", scale, "plant");
    scale = { 0.2f, 0.2f, 0.2f };
    createNewPlayer(pos, name, player, "Assets/Champion/Carlo/Carlo.iqm", "Assets/Champion/Carlo/squidward.png", "Assets/Champion/Carlo/Carlo_idle.iqm", scale, "carlo");
    scale = { 0.02f, 0.02f, 0.02f };
    createNewPlayer(pos, name, player, "Assets/Champion/Crash/Crash.iqm", "Assets/Champion/Crash/color_pallete_baseColor.png", "Assets/Champion/Crash/Crash_idle.iqm", scale, "crash");
    scale = { 1.4f, 1.4f, 1.4f };
    createNewPlayer(pos, name, player, "Assets/Champion/Krusty/Krusty.iqm", "Assets/Champion/Krusty/char_swatches_lit_bmp.png", "Assets/Champion/Krusty/Krusty_idle.iqm", scale, "krusty");
    scale = { 2.0f, 2.0f, 2.0f };
    createNewPlayer(pos, name, player, "Assets/Champion/Ralph/Ralph.iqm", "Assets/Champion/Ralph/char_swatches_lit_bmp.png", "Assets/Champion/Ralph/Ralph_idle.iqm", scale, "ralph");
    scale = { 0.3f, 0.3f, 0.3f };
    createNewPlayer(pos, name, player, "Assets/Champion/Spongebob/Spongebob.iqm", "Assets/Champion/Spongebob/chr_sb05.png", "Assets/Champion/Spongebob/Spongebob_idle.iqm", scale, "spongebob");
}

void Indie::CreateNewGame::createNewPlayer(Vector3 pos, std::string name, std::list<std::reference_wrapper<Indie::Entity>>& player, std::string model, std::string texture, std::string animation, Vector3 scale, std::string nameSelect)
{
    float RotAng = -90.0f;
    Vector3 RotAx = { 1.0f, 0.0f, 0.0f };

    auto& Player(entityManager.addEntity());
    Player.addComponent<Indie::ModelComponent>();
    player = entityManager.getModel();
    player.back().get().getComponent<Indie::ModelComponent>().setEverything(model, pos, RotAx, scale, RotAng);
    player.back().get().getComponent<Indie::ModelComponent>().setTexture(texture);
    player.back().get().getComponent<Indie::ModelComponent>().AddAnimation("Idle", animation);
    player.back().get().getComponent<Indie::ModelComponent>().PlayAnimation("Idle");
    if (name != nameSelect)
        player.back().get().getComponent<Indie::ModelComponent>().setDrawable(false);
}

void Indie::CreateNewGame::createPancarteWithtext()
{
    auto& Valid(entityManager.addEntity());
    Valid.addComponent<Indie::ModelComponent>();
    _Buttons = entityManager.getModel();
    Vector3 scale = { 20.0f, 20.0f, 20.0f };
    float RotAng = -90.0f;
    Vector3 RotAx = { 1.0f, 0.0f, 0.0f };
    Vector3 pos = { 8.0f, -15.0f, 1.0f};
    _Buttons.back().get().getComponent<Indie::ModelComponent>().setEverything("Assets/buton_font1/untitled.obj", pos, RotAx, scale, RotAng);
    setDrawableThisButton(_Buttons.size() - 1, false);
    auto &text1(entityManager.addEntity());
    RotAx = { 0.0f, 0.0f, 0.0f };
    pos = { 3.5f, -9.0f, 0.0f};
    text1.addComponent<Indie::TextComponent>( ("Assets/FFF_Tusj.ttf"), "Start the game", pos, RotAx, 150, BEIGE);
    _Text = entityManager.getText();
    _Text.back().get().getComponent<Indie::TextComponent>().setSize(200);
    _Text.back().get().getComponent<Indie::TextComponent>().setDrawable(false);
}