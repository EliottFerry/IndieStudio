/*
** EPITECH PROJECT, 2021
** Game.cpp
** File description:
** Game.cpp
*/

#include "Game.hpp"

Indie::Game::Game(Indie::SceneManager& manager, int nbPlayers, std::map<int, std::string> _SelectedCharacters) : Indie::AScene::AScene(manager), _Winners(0)
{
    std::srand(time(NULL));
    Vector2 posText = { 0, 0 };
    _SizeWindow.x = Indie::Window::Instance().getWindowSize().x;
    _SizeWindow.y = Indie::Window::Instance().getWindowSize().y;
    auto& background(entity.addEntity());
    background.addComponent<Indie::TwoDComponent>("Assets/Newgame/table3.png", _SizeWindow.x, _SizeWindow.y, posText);
    _background = entity.getTwoDComponent();
    auto& map(entity.addEntity());
    map.addComponent<Indie::Model2DComponent>("Assets/cubicmap.png", "Assets/MAP/NewMap.png");
    auto& cam(entity.addEntity());
    cam.addComponent<Indie::CameraComponent>();
    _cam = &entity.getCamera();
    _cam->getComponent<Indie::CameraComponent>().SetEverythingCamera({ 6.5f, 0.0f, 5.0f }, { 0.0f, 1.0f, -70.0f }, { 6.5f, 15.0f, 15.0f });
    create3DMap("Assets/MAP/map");
    _NbPlayers = nbPlayers;
    createNewPlayer(_SelectedCharacters);
    _SelectedPlayers = _SelectedCharacters;
    InitPowerUpModel();
    if (Indie::Audio::Instance().getState() == 0) {
        Indie::Audio::Instance().stopPlayingMenuMusic();
        Indie::Audio::Instance().startPlayingGameMusic();
        Indie::Audio::Instance().setState(1);
    }
    auto& text(entity.addEntity());
    Vector3 Txt = { 5.9f, 10.0f, 10.8f };
    Vector3 rotate = { 3.0f, 0.0f, 0.0f };
    std::string actualText = "3 !";
    text.addComponent<Indie::TextComponent>(("Assets/FFF_Tusj.ttf"), actualText, Txt, rotate, 150, RAYWHITE);
    _texts = entity.getText();
    CreateScoreBoard();
    _ActualTime = std::to_string(_GameTime / 60) + " : " + std::to_string(_GameTime % 60);
}

Indie::Game::~Game()
{
}

void Indie::Game::InitPowerUpModel()
{
    Model powerUpMod = ::LoadModel((exec_path + "Assets/animations/item/power_up.iqm").c_str());
    Model powerUpMod2 = ::LoadModel((exec_path + "Assets/animations/item/power_up.iqm").c_str());
    Model powerUpMod3 = ::LoadModel((exec_path + "Assets/animations/item/power_up.iqm").c_str());
    Model powerUpMod4 = ::LoadModel((exec_path + "Assets/animations/item/power_up.iqm").c_str());
    ModelComponent bombUpModel;
    bombUpModel.setModel(powerUpMod);
    bombUpModel.setTexture("Assets/animations/item/bomb_up.png");
    bombUpModel.AddAnimation("Idle", "Assets/animations/item/power_up_animation.iqm");
    ModelComponent speedUpModel;
    speedUpModel.setModel(powerUpMod2);
    speedUpModel.setTexture("Assets/animations/item/speed_up.png");
    speedUpModel.AddAnimation("Idle", "Assets/animations/item/power_up_animation.iqm");
    ModelComponent fireUpModel;
    fireUpModel.setModel(powerUpMod3);
    fireUpModel.setTexture("Assets/animations/item/fire_up.png");
    fireUpModel.AddAnimation("Idle", "Assets/animations/item/power_up_animation.iqm");
    ModelComponent strenghtUpModel;
    strenghtUpModel.setModel(powerUpMod4);
    strenghtUpModel.setTexture("Assets/animations/item/strenght_up.png");
    strenghtUpModel.AddAnimation("Idle", "Assets/animations/item/power_up_animation.iqm");
    _PowerUpAvailable.insert(std::pair<std::string, ModelComponent>("BombUp", bombUpModel));
    _PowerUpAvailable.insert(std::pair<std::string, ModelComponent>("SpeedUp", speedUpModel));
    _PowerUpAvailable.insert(std::pair<std::string, ModelComponent>("FireUp", fireUpModel));
    _PowerUpAvailable.insert(std::pair<std::string, ModelComponent>("StrenghtUp", strenghtUpModel));
}

Indie::Game::Game(Indie::SceneManager& manager, std::vector<Vector3> ppos, std::vector<Vector3> wpos, int nbPlayers, std::map<int, std::string> _SelectedCharacters, std::vector<std::string> _alive, std::vector<std::vector<float>> _stats) : Indie::AScene::AScene(manager), _Winners(0)
{
    Vector2 posText = { 0, 0 };

    std::srand(time(NULL));
    _SizeWindow.x = Indie::Window::Instance().getWindowSize().x;
    _SizeWindow.y = Indie::Window::Instance().getWindowSize().y;
    auto& background(entity.addEntity());
    background.addComponent<Indie::TwoDComponent>("Assets/Newgame/table3.png", _SizeWindow.x, _SizeWindow.y, posText);
    _background = entity.getTwoDComponent();
    auto& map(entity.addEntity());
    map.addComponent<Indie::Model2DComponent>("Assets/cubicmap.png", "Assets/MAP/NewMap.png");
    auto& cam(entity.addEntity());
    cam.addComponent<Indie::CameraComponent>();
    _cam = &entity.getCamera();
    _NbPlayers = nbPlayers;
    _cam->getComponent<Indie::CameraComponent>().SetEverythingCamera({ 6.5f, 0.0f, 5.0f }, { 0.0f, 1.0f, -70.0f }, { 6.5f, 15.0f, 15.0f });
    create3DMap(wpos);
    InitPowerUpModel();
    createNewPlayer(_SelectedCharacters, _SelectedCharacters.size());
    if (_NbPlayers == 0) {
        _Player.front().get().getComponent<Indie::Player>().SetPosition({ ppos.front().x, ppos.front().y, ppos.front().z });
        _Player.front().get().getComponent<Indie::Player>().setStats(_stats.front()[0], _stats.front()[1], _stats.front()[2], _stats.front()[3]);
        int i = 1;
        for (auto& tmp : entity.getBombermanAI()) {
            tmp.get().getComponent<Indie::BombermanAI>().setStats(_stats[i][0], _stats[i][1], _stats[i][2], _stats[i][3]);
            tmp.get().getComponent<Indie::BombermanAI>().setPosition({ ppos[i].x, ppos[i].y, ppos[i].z });
            if (_alive[i] == "0")
                tmp.get().getComponent<Indie::BombermanAI>().isDead();
            i++;
        }
    }
    else {
        int j = 0;
        for (auto& tmp : entity.getPlayer()) {
            tmp.get().getComponent<Indie::Player>().setStats(_stats[j][0], _stats[j][1], _stats[j][2], _stats[j][3]);
            tmp.get().getComponent<Indie::Player>().SetPosition({ ppos[j].x, ppos[j].y, ppos[j].z });
            if (_alive[j] == "0")
                tmp.get().getComponent<Indie::Player>().isDead();
            j++;
        }
        int i = 2;
        for (auto& tmp : entity.getBombermanAI()) {
            tmp.get().getComponent<Indie::BombermanAI>().setStats(_stats[i][0], _stats[i][1], _stats[i][2], _stats[i][3]);
            tmp.get().getComponent<Indie::BombermanAI>().setPosition({ ppos[i].x, ppos[i].y, ppos[i].z });
            if (_alive[i] == "0")
                tmp.get().getComponent<Indie::BombermanAI>().isDead();
            i++;
        }

    }

    if (Indie::Audio::Instance().getState() == 0) {
        Indie::Audio::Instance().stopPlayingMenuMusic();
        Indie::Audio::Instance().startPlayingGameMusic();
        Indie::Audio::Instance().setState(1);
    }
    auto& text(entity.addEntity());
    Vector3 Txt = { 5.9f, 10.0f, 10.8f };
    Vector3 rotate = { 3.0f, 0.0f, 0.0f };
    std::string actualText = "3 !";
    text.addComponent<Indie::TextComponent>(("Assets/FFF_Tusj.ttf"), actualText, Txt, rotate, 150, RAYWHITE);
    _texts = entity.getText();
    _ActualTime = std::to_string(_GameTime / 60) + " : " + std::to_string(_GameTime % 60);
}

bool Indie::Game::update(double time)
{
    Rectangle tmp;
    size_t w = 0;
    int i = 0;

    _time += time;
    globalTime += time;
    _GameTimePassed += time;
    if (_GameTimePassed > 1.0 && state == 4) {
        _GameTime -= 1;
        _ActualTime = std::to_string(_GameTime / 60) + " : " + std::to_string(_GameTime % 60);
        _texts.front().get().getComponent<Indie::TextComponent>().setText(_ActualTime);
        _GameTimePassed = 0.0;
    }
    if (_time > 0.04) {
        if (globalTime > 10.0f) {
            _Player = entity.getPlayer();
            _Wall = entity.getBreakWalls();
            if (!_AI.empty())
                _AI = entity.getBombermanAI();
            _PowerUps = entity.getPowerUps();
            getExplosionAndBomb();
            if (_Winners > 0) {
                changeScene();
                return false;
            }

            ManageExplosion();
            for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _Player.begin(); i != _Player.end(); i++)
                i->get().getComponent<Indie::Player>().setBrickWall(_posWall);
            for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _AI.begin(); i != _AI.end(); i++)
                i->get().getComponent<Indie::BombermanAI>().setBrickWall(_posWall);
            CheckPowerUpTaken();
            ShowScoreBoard();
            _time = 0.0;
            for (auto& c : _bomb)
                c.clear();
            _bomb.clear();
            _explo.clear();
        }
        else {
            countDown();
        }
    }
    entity.update(time);
    entity.refresh();
    if (globalTime > 10.0f) {
        if (::IsKeyDown(KEY_ESCAPE)) {
            TakeScreenshot((exec_path + ("Assets/LoadImage/tmp.png")).c_str());
            _manager.ScenePush<Indie::Pause>(entity, _posWall, _NbPlayers);
        }
        if (::IsKeyDown(KEY_B)) {
            _manager.removeScene();
        }
    }
    else if (::GetKeyPressed() != 0 && globalTime < 8.0f)
        globalTime = 8.0f;
    return false;
}

void Indie::Game::spawningPowerUps(std::list<std::reference_wrapper<Indie::Entity>>::iterator wall)
{
    int isSpawing = rand() % 1 + 1;
    if (isSpawing == 1) {
        auto& newPowerUp(entity.addEntity());
        int powerupType = rand() % MAX_POWERUP + 1;
        Vector3 wallPos = wall->get().getComponent<Indie::ModelComponent>().getPos();
        switch (powerupType)
        {
        case BOMB_UP:
            newPowerUp.addComponent<Indie::BombUp>();
            newPowerUp.getComponent<Indie::BombUp>().setModelComponent(_PowerUpAvailable.at("BombUp"));
            newPowerUp.getComponent<Indie::BombUp>().SetPos(Vector3{ wallPos.x, wallPos.y + 1.0f, wallPos.z + 0.8f });
            _PowerUps = entity.getPowerUps();
            break;
        case SPEED_UP:
            newPowerUp.addComponent<Indie::SpeedUp>();
            newPowerUp.getComponent<Indie::SpeedUp>().setModelComponent(_PowerUpAvailable.at("SpeedUp"));
            newPowerUp.getComponent<Indie::SpeedUp>().SetPos(Vector3{ wallPos.x, wallPos.y + 1.0f, wallPos.z + 0.8f });
            _PowerUps = entity.getPowerUps();
            break;
        case WALL_PASS:
            newPowerUp.addComponent<Indie::StrenghtUp>();
            newPowerUp.getComponent<Indie::StrenghtUp>().setModelComponent(_PowerUpAvailable.at("StrenghtUp"));
            newPowerUp.getComponent<Indie::StrenghtUp>().SetPos(Vector3{ wallPos.x, wallPos.y + 1.0f, wallPos.z + 0.8f });
            _PowerUps = entity.getPowerUps();
            break;
        case EXPLO_UP:
            newPowerUp.addComponent<Indie::ExploUp>();
            newPowerUp.getComponent<Indie::ExploUp>().setModelComponent(_PowerUpAvailable.at("FireUp"));
            newPowerUp.getComponent<Indie::ExploUp>().SetPos(Vector3{ wallPos.x, wallPos.y + 1.0f, wallPos.z + 0.8f });
            _PowerUps = entity.getPowerUps();
            break;
        };
    }
}

void Indie::Game::ManageExplosion()
{
    for (auto const& w : _explo) {
        for (auto const& x : w) {
            for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _Wall.begin(); i != _Wall.end(); i++) {
                if (i->get().hasComponent<Indie::BreakableWall>()) {
                    if (i->get().getComponent<Indie::ModelComponent>().getPos().x == x.x && i->get().getComponent<Indie::ModelComponent>().getPos().z == x.z) {
                        spawningPowerUps(i);
                        i->get().destroy();
                    }
                }
            }
            for (std::vector<Vector3>::iterator bricks = _posWall.begin(); bricks != _posWall.end(); ++bricks) {
                if (bricks->x == x.x && bricks->z == x.z) {
                    _posWall.erase(bricks);
                    bricks = _posWall.begin();
                }
            }
            for (auto const& p : _bomb)
                for (auto const& kaboum : p) {
                    if (kaboum.x == x.x && kaboum.z == x.z) {
                        for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _Player.begin(); i != _Player.end(); i++) {
                            i->get().getComponent<Indie::Player>().makeExplodeBomb(kaboum);
                        }
                    }
                }
            for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _Player.begin(); i != _Player.end(); i++) {
                if (round(i->get().getComponent<Indie::Player>().getPosition().x) == x.x && round(i->get().getComponent<Indie::Player>().getPosition().z) == x.z)
                    i->get().getComponent<Indie::Player>().isDead();
            }
            for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _AI.begin(); i != _AI.end(); i++)
                if (round(i->get().getComponent<Indie::BombermanAI>().getPosition().x) == x.x && round(i->get().getComponent<Indie::BombermanAI>().getPosition().z) == x.z)
                    i->get().getComponent<Indie::BombermanAI>().isDead();
        }
    }
}

void Indie::Game::draw()
{
    _background.back().get().draw();
    _texts = entity.getText();
    for (auto const &t : _image)
        t.get().getComponent<Indie::TwoDComponent>().draw();
    for (auto const &t : _texts)
        t.get().getComponent<Indie::TextComponent>().draw();
    _cam->getComponent<Indie::CameraComponent>().Begin3DCameraMod();
    entity.draw();
    Indie::Audio::Instance().draw();
    EndMode3D();
}

void Indie::Game::create3DMap(std::vector<Vector3> wallposition)
{
    std::string tmp;
    Model _mod = LoadModel((exec_path + ("Assets/bricks/Bricks.obj")).c_str());

    for (int i = 0; i != wallposition.size(); i++) {
        auto& wall(entity.addEntity());
        wall.addComponent<Indie::BreakableWall>();
        wall.addComponent<Indie::ModelComponent>();
        wall.getComponent<Indie::ModelComponent>().setModel(_mod);
        wall.getComponent<Indie::ModelComponent>().SetPos({ wallposition[i].x, wallposition[i].y, wallposition[i].z });
        _posWall.push_back({ wallposition[i].x, wallposition[i].y, wallposition[i].z });
        wall.getComponent<Indie::ModelComponent>().SetScale({ 0.008f, 0.01f, 0.0070f });
        wall.getComponent<Indie::ModelComponent>().SetRotationAngle(0.0f);
        wall.getComponent<Indie::ModelComponent>().SetRotationAxis({ 0 });
    }
    _Wall = entity.getBreakWalls();
}

void Indie::Game::create3DMap(std::string _file)
{
    _file = exec_path + (_file);
    std::ifstream file(_file);
    std::string tmp;
    Vector3 _pos = { 0.0f, 0.0f, 0.0f };
    Model _mod = LoadModel((exec_path + ("Assets/bricks/Bricks.obj")).c_str());

    auto &wall(entity.addEntity());
    wall.addComponent<Indie::BreakableWall>();
    wall.addComponent<Indie::ModelComponent>();
    wall.getComponent<Indie::ModelComponent>().setModel(_mod);
    wall.getComponent<Indie::ModelComponent>().SetPos( {-5000.0f, 1000.0f, 0.0f });
    wall.getComponent<Indie::ModelComponent>().SetScale({ 0.008f, 0.01f, 0.0070f });
    if (file.is_open()) {
        for (int i = 0; std::getline(file, tmp); i++) {
            for (int x = 0; tmp[x]; x++) {
                _pos.x += 1.0f;
                if (tmp[x] == '2') {
                    if (std::rand() % 3 != 0) {
                        auto& wall(entity.addEntity());
                        wall.addComponent<Indie::BreakableWall>();
                        wall.addComponent<Indie::ModelComponent>();
                        wall.getComponent<Indie::ModelComponent>().setModel(_mod);
                        wall.getComponent<Indie::ModelComponent>().SetPos(_pos);
                        _posWall.push_back(_pos);
                        wall.getComponent<Indie::ModelComponent>().SetScale({ 0.008f, 0.01f, 0.0070f });
                        wall.getComponent<Indie::ModelComponent>().SetRotationAngle(0.0f);
                        wall.getComponent<Indie::ModelComponent>().SetRotationAxis({ 0 });
                    }
                }
            }
            _pos.x = -1.0f;
            _pos.z += 1.0;
        }
        _Wall = entity.getBreakWalls();
    }
    else {
        throw std::runtime_error("Cannot correctly load the map.");
    }
}

std::vector<Indie::ModelComponent> Indie::Game::get3DMap()
{
    return _wall;
}

void Indie::Game::createNewPlayer(std::map<int, std::string> _SelectedCharacters)
{
    int i = 1;
    std::string p = "p";
    auto& Player(entity.addEntity());
    Player.addComponent<Indie::Player>();
    _Player = entity.getPlayer();
    _Player.front().get().getComponent<Indie::Player>().createNewPlayer(_SelectedCharacters[0]);
    _Player.front().get().getComponent<Indie::Player>().setPlayerColision("Assets/cubicmap.png");
    _Player.front().get().getComponent<Indie::Player>().setBrickWall(_posWall);
    _Player.front().get().getComponent<Indie::Player>().SetGamepad(0, 1);
    _Player.front().get().getComponent<Indie::Player>().setName(p += std::to_string(i));
    i++;
    if (GetGamepadName(0) != NULL && !_SelectedCharacters[1].empty()) {
        auto& Player2(entity.addEntity());
        Player2.addComponent<Indie::Player>();
        _Player = entity.getPlayer();
        _Player.back().get().getComponent<Indie::Player>().createNewPlayer(_SelectedCharacters[1]);
        _Player.back().get().getComponent<Indie::Player>().SetPosition({ 12.5f, 0.1f, 11.0f });
        _Player.back().get().getComponent<Indie::Player>().setPlayerColision("Assets/cubicmap.png");
        _Player.back().get().getComponent<Indie::Player>().setBrickWall(_posWall);
        _Player.back().get().getComponent<Indie::Player>().SetGamepad(0, 2);
        p = "p";
        _Player.back().get().getComponent<Indie::Player>().setName(p += std::to_string(i));
        i++;
    }
    Vector3 tmp = _Player.front().get().getComponent<Indie::Player>().getPosition();

    if (_NbPlayers == 0) {
        auto& bot(entity.addEntity());
        bot.addComponent<Indie::BombermanAI>();
        _AI = entity.getBombermanAI();
        _AI.front().get().getComponent<Indie::BombermanAI>().CreateChamp("Blitz");
        _AI.front().get().getComponent<Indie::BombermanAI>().setPosition({ 12.5f, 0.1f, 11.0f });
        _AI.front().get().getComponent<Indie::BombermanAI>().setMap("Assets/cubicmap.png");
        _AI.front().get().getComponent<Indie::BombermanAI>().setPlayerToFocus(tmp);
        p = "p";
        _AI.front().get().getComponent<Indie::BombermanAI>().setName(p += std::to_string(i));
        i++;
    }
    auto &bot2(entity.addEntity());
    bot2.addComponent<Indie::BombermanAI>();
    _AI = entity.getBombermanAI();
    _AI.back().get().getComponent<Indie::BombermanAI>().CreateChamp("Knight");
    _AI.back().get().getComponent<Indie::BombermanAI>().setPosition({ 12.5f, 0.1f, 1.0f });
    _AI.back().get().getComponent<Indie::BombermanAI>().setMap("Assets/cubicmap.png");
    _AI.back().get().getComponent<Indie::BombermanAI>().setPlayerToFocus(tmp);
    p = "p";
    _AI.back().get().getComponent<Indie::BombermanAI>().setName(p += std::to_string(i));
    i++;

    auto &bot3(entity.addEntity());
    bot3.addComponent<Indie::BombermanAI>();
    _AI = entity.getBombermanAI();
    _AI.back().get().getComponent<Indie::BombermanAI>().CreateChamp("Plant");
    _AI.back().get().getComponent<Indie::BombermanAI>().setPosition({ 1.5f, 0.1f, 11.0f });
    _AI.back().get().getComponent<Indie::BombermanAI>().setMap("Assets/cubicmap.png");
    _AI.back().get().getComponent<Indie::BombermanAI>().setPlayerToFocus(tmp);
    p = "p";
    _AI.back().get().getComponent<Indie::BombermanAI>().setName(p += std::to_string(i));
    i++;
}


void Indie::Game::createNewPlayer(std::map<int, std::string> _SelectedCharacters, size_t size)
{
    auto& Player(entity.addEntity());
    Player.addComponent<Indie::Player>();
    _Player = entity.getPlayer();
    _Player.front().get().getComponent<Indie::Player>().createNewPlayer(_SelectedCharacters[0]);
    _Player.front().get().getComponent<Indie::Player>().setPlayerColision("Assets/cubicmap.png");
    _Player.front().get().getComponent<Indie::Player>().setBrickWall(_posWall);
    _Player.front().get().getComponent<Indie::Player>().SetGamepad(0, 1);
    if (GetGamepadName(0) != NULL && !_SelectedCharacters[1].empty()) {
        auto& Player2(entity.addEntity());
        Player2.addComponent<Indie::Player>();
        _Player = entity.getPlayer();
        _Player.back().get().getComponent<Indie::Player>().createNewPlayer(_SelectedCharacters[1]);
        _Player.back().get().getComponent<Indie::Player>().SetPosition({ 12.5f, 0.1f, 11.0f });
        _Player.back().get().getComponent<Indie::Player>().setPlayerColision("Assets/cubicmap.png");
        _Player.back().get().getComponent<Indie::Player>().setBrickWall(_posWall);
        _Player.back().get().getComponent<Indie::Player>().SetGamepad(0, 2);
    }
    Vector3 tmp = _Player.front().get().getComponent<Indie::Player>().getPosition();

    for (size_t i = 1; i != size; i++) {
        if (_NbPlayers == 0) {
            auto& bot(entity.addEntity());
            bot.addComponent<Indie::BombermanAI>();
            _AI = entity.getBombermanAI();
        }
    }
    int i = 1;
    for (auto& tmpai : _AI) {
        tmpai.get().getComponent<Indie::BombermanAI>().CreateChamp(_SelectedCharacters[i]);
        tmpai.get().getComponent<Indie::BombermanAI>().setMap("Assets/cubicmap.png");
        tmpai.get().getComponent<Indie::BombermanAI>().setPlayerToFocus(tmp);
        i++;
    }
}

void Indie::Game::getExplosionAndBomb()
{
    std::vector<Vector3> AllPlayerPosition;

    for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _Player.begin(); i != _Player.end(); i++) {
        _explo.push_back(i->get().getComponent<Indie::Player>().GetExploZone());
        _bomb.push_back(i->get().getComponent<Indie::Player>().getBombPosition());
        _capacity.push_back(i->get().getComponent<Indie::Player>().getCapacity());
        AllPlayerPosition.push_back(i->get().getComponent<Indie::Player>().getPosition());
        if (i->get().getComponent<Indie::Player>().destroy_after_death()) {
            i->get().destroy();
            _Player.erase(i);
            if (_Player.empty()) {
                _Winners = 1;
                return;
            }
            i = _Player.begin();
        }
    }
    if (!_AI.empty()) {
        for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _AI.begin(); i != _AI.end(); i++) {
            _explo.push_back(i->get().getComponent<Indie::BombermanAI>().GetExploZone());
            _bomb.push_back(i->get().getComponent<Indie::BombermanAI>().getBombPosition());
            _capacity.push_back(i->get().getComponent<Indie::BombermanAI>().getCapacity());
            AllPlayerPosition.push_back(i->get().getComponent<Indie::BombermanAI>().getPosition());
            if (i->get().getComponent<Indie::BombermanAI>().destroy_after_death()) {
                i->get().destroy();
                _AI.erase(i);
                if (_AI.empty() && _Player.size() == 1) {
                    _Winners = 2;
                    return;
                }
                i = _AI.begin();
            }
        }
        std::vector<std::pair<int, int>>::iterator itcapa = _capacity.begin();
        for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _AI.begin(); i != _AI.end(); i++) {
            i->get().getComponent<Indie::BombermanAI>().clearAI();
            i->get().getComponent<Indie::BombermanAI>().AddEspectedExlosion(_bomb, _capacity);
            i->get().getComponent<Indie::BombermanAI>().AddCurrentExplosion(_explo);
            i->get().getComponent<Indie::BombermanAI>().getPositionOfOtherPlayer(AllPlayerPosition);
        }
    }
    if (_AI.empty() && _Player.size() == 1) {
        _Winners = 2;
        return;
    } if (!_AI.empty() && _Player.size() == 1 && _GameTime <= 0) {
        _Winners = 3;
        return;
    } if (!_AI.empty() && _Player.size() == 2 && _GameTime <= 0) {
        _Winners = 4;
        return;
    }
    _capacity.clear();
    AllPlayerPosition.clear();
}

void Indie::Game::CheckPowerUpTaken()
{
    size_t powerUpIterator = 0;

    for (auto& Pup : _PowerUps) {
        if (Pup.get().hasComponent<Indie::BombUp>()) {
            for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _Player.begin(); i != _Player.end(); i++) {
                if (round(i->get().getComponent<Indie::Player>().getPosition().x) == floor(Pup.get().getComponent<Indie::BombUp>().getPos().x) && round(i->get().getComponent<Indie::Player>().getPosition().z) == floor(Pup.get().getComponent<Indie::BombUp>().getPos().z)) {
                    i->get().getComponent<Indie::Player>().addPowerUp(Pup.get().getComponent<Indie::BombUp>().GetName());
                    Pup.get().destroy();
                    break;
                }
            }
            for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _AI.begin(); i != _AI.end(); ++i)
                if (round(i->get().getComponent<Indie::BombermanAI>().getPosition().x) == floor(Pup.get().getComponent<Indie::BombUp>().getPos().x) && round(i->get().getComponent<Indie::BombermanAI>().getPosition().z) == floor(Pup.get().getComponent<Indie::BombUp>().getPos().z)) {
                    i->get().getComponent<Indie::BombermanAI>().addPowerUp(Pup.get().getComponent<Indie::BombUp>().GetName());
                    Pup.get().destroy();
                    break;
                }
        }
        if (Pup.get().hasComponent<Indie::ExploUp>()) {
            for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _Player.begin(); i != _Player.end(); i++) {
                if (round(i->get().getComponent<Indie::Player>().getPosition().x) == floor(Pup.get().getComponent<Indie::ExploUp>().getPos().x) && round(i->get().getComponent<Indie::Player>().getPosition().z) == floor(Pup.get().getComponent<Indie::ExploUp>().getPos().z)) {
                    i->get().getComponent<Indie::Player>().addPowerUp(Pup.get().getComponent<Indie::ExploUp>().GetName());
                    Pup.get().destroy();
                    break;
                }
            }
            for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _AI.begin(); i != _AI.end(); ++i)
                if (round(i->get().getComponent<Indie::BombermanAI>().getPosition().x) == floor(Pup.get().getComponent<Indie::ExploUp>().getPos().x) && round(i->get().getComponent<Indie::BombermanAI>().getPosition().z) == floor(Pup.get().getComponent<Indie::ExploUp>().getPos().z)) {
                    i->get().getComponent<Indie::BombermanAI>().addPowerUp(Pup.get().getComponent<Indie::ExploUp>().GetName());
                    Pup.get().destroy();
                    break;
                }
        }
        if (Pup.get().hasComponent<Indie::SpeedUp>()) {
            for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _Player.begin(); i != _Player.end(); i++) {
                if (round(i->get().getComponent<Indie::Player>().getPosition().x) == floor(Pup.get().getComponent<Indie::SpeedUp>().getPos().x) && round(i->get().getComponent<Indie::Player>().getPosition().z) == floor(Pup.get().getComponent<Indie::SpeedUp>().getPos().z)) {
                    i->get().getComponent<Indie::Player>().addPowerUp(Pup.get().getComponent<Indie::SpeedUp>().GetName());
                    Pup.get().destroy();
                    break;
                }
            }
            for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _AI.begin(); i != _AI.end(); ++i)
                if (round(i->get().getComponent<Indie::BombermanAI>().getPosition().x) == floor(Pup.get().getComponent<Indie::SpeedUp>().getPos().x) && floor(i->get().getComponent<Indie::BombermanAI>().getPosition().z) == floor(Pup.get().getComponent<Indie::SpeedUp>().getPos().z)) {
                    i->get().getComponent<Indie::BombermanAI>().addPowerUp(Pup.get().getComponent<Indie::SpeedUp>().GetName());
                    Pup.get().destroy();
                    break;
                }
        }
        if (Pup.get().hasComponent<Indie::StrenghtUp>()) {
            for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _Player.begin(); i != _Player.end(); i++) {
                if (round(i->get().getComponent<Indie::Player>().getPosition().x) == floor(Pup.get().getComponent<Indie::StrenghtUp>().getPos().x) && round(i->get().getComponent<Indie::Player>().getPosition().z) == floor(Pup.get().getComponent<Indie::StrenghtUp>().getPos().z)) {
                    i->get().getComponent<Indie::Player>().addPowerUp(Pup.get().getComponent<Indie::StrenghtUp>().GetName());
                    Pup.get().destroy();
                    break;
                }
            }
            for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _AI.begin(); i != _AI.end(); ++i)
                if (round(i->get().getComponent<Indie::BombermanAI>().getPosition().x) == floor(Pup.get().getComponent<Indie::StrenghtUp>().getPos().x) && round(i->get().getComponent<Indie::BombermanAI>().getPosition().z) == floor(Pup.get().getComponent<Indie::StrenghtUp>().getPos().z)) {
                    i->get().getComponent<Indie::BombermanAI>().addPowerUp(Pup.get().getComponent<Indie::StrenghtUp>().GetName());
                    Pup.get().destroy();
                    break;
                }
        }
        if (!_PowerUps.empty())
            powerUpIterator++;
    }
}

void Indie::Game::countDown()
{
    if (globalTime > 3.5f && state == 0) {
        _texts.front().get().getComponent<Indie::TextComponent>().setText("2 !");
        state = 1;
    }
    if (globalTime > 6.5f && state == 1) {
        _texts.front().get().getComponent<Indie::TextComponent>().setText("1 !");
        state = 2;
    }
    if (globalTime > 8.5f && state == 2) {
        Vector3 Txt = { 5.9f, 10.0f, 10.8f };
        _texts.front().get().getComponent<Indie::TextComponent>().setPosition3D(Txt);
        _texts.front().get().getComponent<Indie::TextComponent>().setText("GO !");
        state = 3;
    } if (globalTime > 9.5f && state == 3) {
        Vector3 newPos = { 5.5f, 8.0f, 5.8f };
        _texts.front().get().getComponent<Indie::TextComponent>().setText(_ActualTime);
        _texts.front().get().getComponent<Indie::TextComponent>().setPosition3D(newPos);
        for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _AI.begin(); i != _AI.end(); ++i)
            i->get().getComponent<Indie::BombermanAI>().setActive();
        for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _Player.begin(); i != _Player.end(); i++)
            i->get().getComponent<Indie::Player>().setActive();
        state = 4;
    }
}


void Indie::Game::ShowScoreBoard()
{
    int secur = 0;
    int r = 2;
    for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _Player.begin(); i != _Player.end(); i++) {
        _statOfEv.push_back(i->get().getComponent<Indie::Player>().getBigBrainStats());
    }
    while (r < 5)
        for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _AI.begin(); i != _AI.end(); i++) {
            if (i->get().getComponent<Indie::BombermanAI>().getPName().find(std::to_string(r)) != std::string::npos)
                _statOfEv.push_back(i->get().getComponent<Indie::BombermanAI>().getBigBrainStats());
            else
                _statOfEv.push_back({0.0f, 0.0f, 0.0f, 0.0f});
            r++;
            if (r == 5)
                break;
        }
    for (std::list<std::reference_wrapper<Indie::Entity>>::iterator i = _scoreBoard.begin(); i != _scoreBoard.end(); i++) {
        if (i->get().hasComponent<Indie::Score>()) {
            if (BigBrainMove.find(i->get().getComponent<Indie::Score>().getName()) == std::string::npos) {
                if (_statOfEv.back().empty()) {
                    _statOfEv.pop_back();
                }
                if (_statOfEv.empty())
                    break;
                i->get().getComponent<Indie::TextComponent>().setText(std::to_string((int)_statOfEv.back().back()));
                _statOfEv.back().pop_back();
            }
        }
    }
    _statOfEv.clear();
}

void Indie::Game::CreateScoreBoard()
{
    Vector2 positionSec = {_SizeWindow.x / 30, (_SizeWindow.y / 3) * 2};

    positionSec.x += 50.0f;
    positionSec.y += 50.0f;
    auto &p3b1(entity.addEntity());
    p3b1.addComponent<Indie::Score>("p3");
    p3b1.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "20", positionSec, 40, RAYWHITE);

    positionSec.y += 40.0f;
    auto &p3b2(entity.addEntity());
    p3b2.addComponent<Indie::Score>("p3");
    p3b2.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "1", positionSec, 40, RAYWHITE);

    positionSec.y += 40.0f;
    auto &p3b3(entity.addEntity());
    p3b3.addComponent<Indie::Score>("p3");
    p3b3.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "1", positionSec, 40, RAYWHITE);

    positionSec.y += 40.0f;
    auto &p3b4(entity.addEntity());
    p3b4.addComponent<Indie::Score>("p3");
    p3b4.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "1", positionSec, 40, RAYWHITE);

    positionSec = {(_SizeWindow.x / 14) * 12, _SizeWindow.y / 15};

    positionSec.x += 50.0f;
    positionSec.y += 50.0f;
    auto &p2b1(entity.addEntity());
    p2b1.addComponent<Indie::Score>("p2");
    p2b1.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "20", positionSec, 40, RAYWHITE);

    positionSec.y += 40.0f;
    auto &p2b2(entity.addEntity());
    p2b2.addComponent<Indie::Score>("p2");
    p2b2.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "1", positionSec, 40, RAYWHITE);

    positionSec.y += 40.0f;
    auto &p2b3(entity.addEntity());
    p2b3.addComponent<Indie::Score>("p2");
    p2b3.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "1", positionSec, 40, RAYWHITE);

    positionSec.y += 40.0f;
    auto &p2b4(entity.addEntity());
    p2b4.addComponent<Indie::Score>("p2");
    p2b4.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "1", positionSec, 40, RAYWHITE);

    positionSec = {(_SizeWindow.x / 14) * 12, (_SizeWindow.y / 3) * 2};

    positionSec.x += 50.0f;
    positionSec.y += 50.0f;
    auto &p4b1(entity.addEntity());
    p4b1.addComponent<Indie::Score>("p4");
    p4b1.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "20", positionSec, 40, RAYWHITE);

    positionSec.y += 40.0f;
    auto &p4b2(entity.addEntity());
    p4b2.addComponent<Indie::Score>("p4");
    p4b2.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "1", positionSec, 40, RAYWHITE);

    positionSec.y += 40.0f;
    auto &p4b3(entity.addEntity());
    p4b3.addComponent<Indie::Score>("p4");
    p4b3.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "1", positionSec, 40, RAYWHITE);

    positionSec.y += 40.0f;
    auto &p4b4(entity.addEntity());
    p4b4.addComponent<Indie::Score>("p4");
    p4b4.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "1", positionSec, 40, RAYWHITE);

    positionSec = {_SizeWindow.x / 40, _SizeWindow.y / 15};

    positionSec.x += 50.0f;
    positionSec.y += 50.0f;
    auto &p1b1(entity.addEntity());
    p1b1.addComponent<Indie::Score>("p1");
    p1b1.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "20", positionSec, 40, RAYWHITE);

    positionSec.y += 40.0f;
    auto &p1b2(entity.addEntity());
    p1b2.addComponent<Indie::Score>("p1");
    p1b2.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "1", positionSec, 40, RAYWHITE);

    positionSec.y += 40.0f;
    auto &p1b3(entity.addEntity());
    p1b3.addComponent<Indie::Score>("p1");
    p1b3.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "1", positionSec, 40, RAYWHITE);

    positionSec.y += 40.0f;
    auto &p1b4(entity.addEntity());
    p1b4.addComponent<Indie::Score>("p1");
    p1b4.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "1", positionSec, 40, RAYWHITE);

    _scoreBoard = entity.getScore();
    Vector2 position = {_SizeWindow.x / 40, _SizeWindow.y / 15};

    auto &p1(entity.addEntity());
    p1.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "player 1 :", position, 40, RAYWHITE);

    position.y += 50.0f;
    auto &img2(entity.addEntity());
    img2.addComponent<Indie::TwoDComponent>("Assets/animations/item/speed_up.png", 30.0f, 30.0f, position);

    position.y += 40.0f;
    auto &img4(entity.addEntity());
    img4.addComponent<Indie::TwoDComponent>("Assets/animations/item/strenght_up.png", 30.0f, 30.0f, position);
    _image = entity.getTwoDComponent();

    position.y += 40.0f;
    auto &img1(entity.addEntity());
    img1.addComponent<Indie::TwoDComponent>("Assets/animations/item/fire_up.png", 30.0f, 30.0f, position);

    position.y += 40.0f;
    auto &img3(entity.addEntity());
    img3.addComponent<Indie::TwoDComponent>("Assets/animations/item/bomb_up.png", 30.0f, 30.0f, position);

    position = {(_SizeWindow.x / 14) * 12, _SizeWindow.y / 15};
    auto &p2(entity.addEntity());
    p2.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "player 2 :", position, 40, RAYWHITE);
    position.x += 150;

    position.y += 50.0f;
    auto &img6(entity.addEntity());
    img6.addComponent<Indie::TwoDComponent>("Assets/animations/item/speed_up.png", 30.0f, 30.0f, position);

    position.y += 40.0f;
    auto &img8(entity.addEntity());
    img8.addComponent<Indie::TwoDComponent>("Assets/animations/item/strenght_up.png", 30.0f, 30.0f, position);
    _image = entity.getTwoDComponent();

    position.y += 40.0f;
    auto &img5(entity.addEntity());
    img5.addComponent<Indie::TwoDComponent>("Assets/animations/item/fire_up.png", 30.0f, 30.0f, position);

    position.y += 40.0f;
    auto &img7(entity.addEntity());
    img7.addComponent<Indie::TwoDComponent>("Assets/animations/item/bomb_up.png", 30.0f, 30.0f, position);
    
    position = {_SizeWindow.x / 30, (_SizeWindow.y / 3) * 2};
    auto &p3(entity.addEntity());
    p3.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "player 3 :", position, 40, RAYWHITE);

    position.y += 50.0f;
    auto &img10(entity.addEntity());
    img10.addComponent<Indie::TwoDComponent>("Assets/animations/item/speed_up.png", 30.0f, 30.0f, position);

    position.y += 40.0f;
    auto &img12(entity.addEntity());
    img12.addComponent<Indie::TwoDComponent>("Assets/animations/item/strenght_up.png", 30.0f, 30.0f, position);

    position.y += 40.0f;
    auto &img9(entity.addEntity());
    img9.addComponent<Indie::TwoDComponent>("Assets/animations/item/fire_up.png", 30.0f, 30.0f, position);

    position.y += 40.0f;
    auto &img11(entity.addEntity());
    img11.addComponent<Indie::TwoDComponent>("Assets/animations/item/bomb_up.png", 30.0f, 30.0f, position);

    position = {(_SizeWindow.x / 14) * 12, (_SizeWindow.y / 3) * 2};
    auto &p4(entity.addEntity());
    p4.addComponent<Indie::TextComponent>("Assets/FFF_Tusj.ttf", "player 4 :", position, 40, RAYWHITE);
    _texts = entity.getText();

    position.x += 150;
    position.y += 50.0f;
    auto &img14(entity.addEntity());
    img14.addComponent<Indie::TwoDComponent>("Assets/animations/item/speed_up.png", 30.0f, 30.0f, position);

    position.y += 40.0f;
    auto &img16(entity.addEntity());
    img16.addComponent<Indie::TwoDComponent>("Assets/animations/item/strenght_up.png", 30.0f, 30.0f, position);

    position.y += 40.0f;
    auto &img13(entity.addEntity());
    img13.addComponent<Indie::TwoDComponent>("Assets/animations/item/fire_up.png", 30.0f, 30.0f, position);

    position.y += 40.0f;
    auto &img15(entity.addEntity());
    img15.addComponent<Indie::TwoDComponent>("Assets/animations/item/bomb_up.png", 30.0f, 30.0f, position);
    
    _image = entity.getTwoDComponent();
}


void Indie::Game::changeScene()
{
    int i = 0;

    if (_Winners == 1)
        _manager.ScenePush<Indie::FinishGame>(_SelectedPlayers, _NbPlayers);
    if (_Winners == 2) {
        if (_SelectedPlayers[0] == _Player.back().get().getComponent<Indie::Player>().getName())
            i = 1;
        else
            i = 2;
        _manager.ScenePush<Indie::FinishGame>(_Player.back().get().getComponent<Indie::Player>().getName(), i);
    } if (_Winners == 3)
        _manager.ScenePush<Indie::Equality>(_SelectedPlayers, _NbPlayers);
    if (_Winners == 4)
        _manager.ScenePush<Indie::Equality>(_SelectedPlayers, _NbPlayers);
}