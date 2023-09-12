/*
** EPITECH PROJECT, 2021
** Player
** File description:
** File to implement function for player components
*/

#include "Player.hpp"
#include "raylib.h"
#include "../../encapsulation/Event.hpp"

Indie::Player::~Player()
{
}

void Indie::Player::init()
{

}

void Indie::Player::SetPosition(Vector3 _position)
{
    _model.SetPosition(_position);
}

void Indie::Player::createNewPlayer(std::string _Champ)
{
    _champ = _Champ;
    _model.CreateNewChamp(_Champ);
}

std::string Indie::Player::getChamp()
{
    return (_champ);
}

void Indie::Player::setBricksPosition(std::vector<Vector3> _posWall)
{
    if (!alive)
        return;
    _model.setBricksPosition(_posWall);
}

void Indie::Player::SetGamepad(int control, int player)
{
    gamepad = control;
    player_num = player;
}

void Indie::Player::setPlayerColision(std::string _PathToMap)
{
    _model.setPlayerColision(_PathToMap);
}

void Indie::Player::setBrickWall(std::vector<Vector3> _posWall)
{
    if (!alive)
        return;
    _model.setBrickWall(_posWall);
}

Vector3 Indie::Player::getPosition()
{
    return _model.getPos();
}

void Indie::Player::makeMovement(double time)
{
    if (!alive)
        return;
    Vector3 oldPos = _model.getPos();

    bool IsGamepadButtonPressed(int gamepad, int button);
    int GetGamepadButtonPressed(void);

    if (player_num == 1) {
        if (::IsKeyDown(Indie::Event::Instance().getMapInputs()["Right"]))
            _model.RightMove(oldPos, time);
        else if (::IsKeyDown(Indie::Event::Instance().getMapInputs()["Left"]))
            _model.LeftMove(oldPos, time);
        else if (::IsKeyDown(Indie::Event::Instance().getMapInputs()["Up"]))
            _model.UpMove(oldPos, time);
        else if (::IsKeyDown(Indie::Event::Instance().getMapInputs()["Down"])) {
            _model.DownMove(oldPos, time);
        } else {
            _model.PlayAnimation("Idle");
        }
    }
    if (player_num != 1) {
        if (GetGamepadAxisMovement(gamepad, 1) == -1)
            _model.UpMove(oldPos, time);
        else if (GetGamepadAxisMovement(gamepad, 1) == 1)
            _model.DownMove(oldPos, time);
        else if (GetGamepadAxisMovement(gamepad, 0) >= -1 && GetGamepadAxisMovement(gamepad, 0) < 0)
            _model.LeftMove(oldPos, time);
        else if (GetGamepadAxisMovement(gamepad, 0) <= 1 && GetGamepadAxisMovement(gamepad, 0) > 0)
            _model.RightMove(oldPos, time);
        else {
            _model.PlayAnimation("Idle");
        }
    }
}

std::pair <int, int> Indie::Player::getCapacity()
{
    std::pair<int, int> cap;

    cap.first = _model.getStrenght();
    cap.second = _model.getRange();
    return cap;
}

void Indie::Player::addPowerUp(std::string _name)
{
    if (_name == "BombUp")
        max_bomb++;
    if (_name == "FireUp")
        _model.addRange();
    if (_name == "StrenghtUp")
        _model.addStrenght();
    if (_name == "SpeedUp")
        _model.addSpeed();
}

std::vector<float> Indie::Player::getStats()
{
    std::vector<float> all_stats;

    all_stats.push_back(static_cast<float>(max_bomb));
    all_stats.push_back(static_cast<float>(_model.getRange()));
    all_stats.push_back(static_cast<float>(_model.getStrenght()));
    all_stats.push_back((_model.getSpeed()));
    return all_stats;
}
std::vector<float> Indie::Player::getBigBrainStats()
{
    std::vector<float> all_stats;

    all_stats.push_back(static_cast<float>(max_bomb));
    all_stats.push_back(static_cast<float>(_model.getRange()));
    all_stats.push_back(static_cast<float>(_model.getStrenght()));
    all_stats.push_back(_model.getSpeed() * 10);
    return all_stats;
}

void Indie::Player::setStats(float _max_bomb, float range, float strength, float speed)
{
    max_bomb = _max_bomb;
    _model.setRange(range);
    _model.setStrenght(strength);
    _model.setSpeed(speed);
}

void Indie::Player::setActive()
{
    active = true;
}

void Indie::Player::update(double time)
{
    _model.update(time);
    if (!alive || !active)
        return;
    makeMovement(time);
    time_bomb += time;
    next_bomb += time;
    if (bomb_nbr < max_bomb && time_bomb > 8.0) {
        bomb_nbr++;
    }
    if (::IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && bomb_nbr > 0 && next_bomb > 1.0 && player_num != 1) {
        _model.CreateNewBomb();
        bomb_nbr--;
        next_bomb = 0.0;
    } if (::IsKeyDown(Indie::Event::Instance().getMapInputs()["Action"]) && bomb_nbr > 0 && next_bomb > 1.0 && player_num == 1) {
        _model.CreateNewBomb();
        bomb_nbr--;
        next_bomb = 0.0;
    }
}

void Indie::Player::draw()
{
    _model.draw();
}

std::vector<Vector3> Indie::Player::GetExploZone()
{
    return _model.GetExploZone(alive);
}

void Indie::Player::isDead()
{
    if (!alive)
        return;
    alive = false;
    time_bomb = 2.0f;
    Indie::Audio::Instance().startPlayingDeath();
    _model.PlayAnimation("Death");
}

bool Indie::Player::isAlive()
{
    if (alive)
        return true;
    else
        return false;
}

std::vector<Vector3> Indie::Player::getBombPosition()
{
    return _model.getBombPosition();
}

void Indie::Player::makeExplodeBomb(Vector3 _bomb)
{
    _model.makeExplodeBomb(_bomb);
}

bool Indie::Player::destroy_after_death()
{
    if (alive)
        return false;
    time_bomb -= 0.01667;
    if (time_bomb < 0 && !alive)
        return true;
    return false;
}

std::string Indie::Player::getName()
{
    return _champ;
}

void Indie::Player::setName(std::string Getname)
{
    _Currentname = Getname;
}

std::string Indie::Player::getPName()
{
    if (!alive)
        return "";
    return _Currentname;
}