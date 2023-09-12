/*
** EPITECH PROJECT, 2021
** B-YEP-400-NCY-4-1-indiestudio-jean.gauthier-damioli
** File description:
** AI
*/

#include "BombermanAI.hpp"

Indie::BombermanAI::BombermanAI()
{
    std::srand(std::time(nullptr));
}

Indie::BombermanAI::~BombermanAI()
{
}

void Indie::BombermanAI::init()
{
    
}

std::pair <int, int> Indie::BombermanAI::getCapacity()
{
    std::pair<int, int> cap;

    cap.first = _body.getStrenght();
    cap.second = _body.getRange();
    return cap;
}

void Indie::BombermanAI::AddEspectedExlosion(std::vector<std::vector<Vector3>> _bomb, std::vector<std::pair<int, int>> _stat)
{
    float rem;

    for (auto &Explo : _bomb) {
        for (auto &Expected : Explo) {
            float range = _stat.begin()->second;
            rem = Expected.x;
            _dangerousTile.push_back({Expected.x, Expected.y, Expected.z });
            for (int i = 0; i < range; i++) {
                rem += 1.0f;
                _dangerousTile.push_back({rem, Expected.y, Expected.z });
            } rem = Expected.x;
            for (int i = 0; i < range; i++) {
                rem -= 1.0f;
                _dangerousTile.push_back({rem, Expected.y, Expected.z });
            } rem = Expected.z;
            for (int i = 0; i < range; i++) {
                rem += 1.0f;
                _dangerousTile.push_back({Expected.x, Expected.y, rem });
            } rem = Expected.z;
            for (int i = 0; i < range; i++) {
                rem -= 1.0f;
                _dangerousTile.push_back({Expected.x, Expected.y, rem });
            }
            if (!_stat.empty())
                _stat.erase(_stat.begin());
        }
    }
}

void Indie::BombermanAI::AddCurrentExplosion(std::vector<std::vector<Vector3>> _explo)
{
    for (auto &Explo : _explo) {
        for (auto &Expected : Explo) {
            _dangerousTile.push_back(Expected);
        }
    }
}

void Indie::BombermanAI::update(double time)
{
    Vector3 tmp = _body.getPos();
    _body.update(time);
    _champPos = _body.getPos();
    _time = time;

    if (!alive || !active)
        return ;
    Algorithm();
    time_bomb += time;
    next_bomb += time;
    if (bomb_nbr < max_bomb && time_bomb > 8.0) {
        bomb_nbr++;
    }
    if (currentMovement == NO_STATE)
        Algorithm();
    if (tmp.x == _body.getPos().x && tmp.z == _body.getPos().z)
        _body.PlayAnimation("Idle");
}

void Indie::BombermanAI::clearAI()
{
    _dangerousTile.clear();
}

void Indie::BombermanAI::draw()
{
    _body.draw();
}

Vector3 Indie::BombermanAI::getPosition()
{
    return _body.getPos();
}

void Indie::BombermanAI::isDead()
{
    if (!alive)
        return ;
    alive = false;
    time_bomb = 2.0f;
    _body.PlayAnimation("Death");
}

bool Indie::BombermanAI::isAlive()
{
    if (alive)
        return true;
    else
        return false;
}

void Indie::BombermanAI::setActive()
{
    active = true;
}

bool Indie::BombermanAI::offensiveState()
{
    size_t move = 0;
    _champPos = _body.getPos();
    Vector3 _step = _champPos;

    if (!CheckTileDanger({_champPos.x, _champPos.z}))
        return false;
    if (directionBot == LEFT_STATE || directionBot == NO_DIRECTION) {
        if (_champPos.x > _playerPos.x && CheckTileDanger({ _champPos.x - 1.0f, _champPos.z }) && _body.check_hard_collision({_champPos.x - 1.0f, _champPos.z})) {
            _step.x = round(_champPos.x) - 1.0f;
            _point.push_back(_step);
            move++;
        }
        else if (_champPos.z > _playerPos.z && CheckTileDanger({ _champPos.x, _champPos.z - 1.0f }) && _body.check_hard_collision({_champPos.x, _champPos.z - 1.0f})) {
            _step.z = round(_champPos.z) - 1.0f;
            _point.push_back(_step);
            move++;
        }
        else if (_champPos.x < _playerPos.x && CheckTileDanger({ _champPos.x + 1.0f, _champPos.z }) && _body.check_hard_collision({_champPos.x + 1.0f, _champPos.z})) {
            _step.x = round(_champPos.x) + 1.0f;
            _point.push_back(_step);
            move++;
        }
        else if (_champPos.z < _playerPos.z && CheckTileDanger({ _champPos.x, _champPos.z + 1.0f }) && _body.check_hard_collision({_champPos.x, _champPos.z + 1.0f})) {
            _step.z = round(_champPos.z) + 1.0f;
            _point.push_back(_step);
            move++;
        }
    }
    else if (directionBot == RIGHT_STATE) {
        if (_champPos.x < _playerPos.x && CheckTileDanger({ _champPos.x + 1.0f, _champPos.z }) && _body.check_hard_collision({_champPos.x + 1.0f, _champPos.z})) {
            _step.x = round(_champPos.x) + 1.0f;
            _point.push_back(_step);
            move++;
        }
        else if (_champPos.z > _playerPos.z && CheckTileDanger({ _champPos.x, _champPos.z - 1.0f }) && _body.check_hard_collision({_champPos.x, _champPos.z - 1.0f})) {
            _step.z = round(_champPos.z) - 1.0f;
            _point.push_back(_step);
            move++;
        }
        else if (_champPos.z < _playerPos.z && CheckTileDanger({ _champPos.x, _champPos.z + 1.0f }) && _body.check_hard_collision({_champPos.x, _champPos.z + 1.0f})) {
            _step.z = round(_champPos.z) + 1.0f;
            _point.push_back(_step);
            move++;
        }
        else if (_champPos.x > _playerPos.x && CheckTileDanger({ round(_champPos.x) - 1.0f, _champPos.z }) && _body.check_hard_collision({_champPos.x - 1.0f, _champPos.z})) {
            _step.x = round(_champPos.x) - 1.0f;
            _point.push_back(_step);
            move++;
        }
    }
    else if (directionBot == UP_STATE) {
        if (_champPos.z > _playerPos.z && CheckTileDanger({ _champPos.x, _champPos.z - 1.0f }) && _body.check_hard_collision({_champPos.x, _champPos.z - 1.0f})) {
            _step.z = round(_champPos.z) - 1.0f;
            _point.push_back(_step);
            move++;
        }
        else if (_champPos.x > _playerPos.x && CheckTileDanger({ _champPos.x - 1.0f, _champPos.z }) && _body.check_hard_collision({_champPos.x - 1.0f, _champPos.z})) {
            _step.x = round(_champPos.x) - 1.0f;
            _point.push_back(_step);
            move++;
        }
        else if (_champPos.x < _playerPos.x && CheckTileDanger({ _champPos.x + 1.0f, _champPos.z }) && _body.check_hard_collision({_champPos.x + 1.0f, _champPos.z})) {
            _step.x = round(_champPos.x) + 1.0f;
            _point.push_back(_step);
            move++;
        }
        else if (_champPos.z < _playerPos.z && CheckTileDanger({ _champPos.x, _champPos.z + 1.0f }) && _body.check_hard_collision({_champPos.x, _champPos.z + 1.0f})) {
            _step.z = round(_champPos.z) + 1.0f;
            _point.push_back(_step);
            move++;
        }
    }
    else if (directionBot == DOWN_STATE) {
        if (_champPos.z < _playerPos.z && CheckTileDanger({ _champPos.x, _champPos.z + 1.0f }) && _body.check_hard_collision({_champPos.x, _champPos.z + 1.0f})) {
            _step.z = round(_champPos.z) + 1.0f;
            _point.push_back(_step);
            move++;
        }
        else if (_champPos.x > _playerPos.x && CheckTileDanger({ _champPos.x - 1.0f, _champPos.z }) && _body.check_hard_collision({_champPos.x - 1.0f, _champPos.z})) {
            _step.x = round(_champPos.x) - 1.0f;
            _point.push_back(_step);
            move++;
        }
        else if (_champPos.z > _playerPos.z && CheckTileDanger({ _champPos.x, _champPos.z - 1.0f }) && _body.check_hard_collision({_champPos.x, _champPos.z - 1.0f})) {
            _step.z = round(_champPos.z) - 1.0f;
            _point.push_back(_step);
            move++;
        }
        else if (_champPos.x < _playerPos.x && CheckTileDanger({ _champPos.x + 1.0f, _champPos.z }) && _body.check_hard_collision({_champPos.x + 1.0f, _champPos.z})) {
            _step.x = round(_champPos.x) + 1.0f;
            _point.push_back(_step);
            move++;
        }
    }
    if (move == 0) {
        currentMovement = NO_STATE;
        plantBomb();
        return false;
    }
    currentMovement = OFFENSIVE_STATE;
    return true;
}

bool Indie::BombermanAI::CheckAllAngle(Vector2 _pos)
{
    if (CheckTileDanger({_pos.x - 1.0f, _pos.y}) && _body.check_collision({_pos.x - 1.0f, _pos.y})) {
        _point.push_back({_pos.x, 0.1f, _pos.y});
        _point.push_back({_pos.x - 1.0f, 0.1f, _pos.y});
        directionBot = LEFT_STATE;
        currentMovement = DEFENSIVE_STATE;
        return true;
    }
    else if (CheckTileDanger({_pos.x + 1.0f, _pos.y}) && _body.check_collision({_pos.x + 1.0f, _pos.y})) {
        _point.push_back({_pos.x, 0.1f, _pos.y});
        _point.push_back({_pos.x + 1.0f, 0.1f, _pos.y});
        directionBot = RIGHT_STATE;
        currentMovement = DEFENSIVE_STATE;
        return true;
    }
    else if (CheckTileDanger({_pos.x, _pos.y - 1.0f}) && _body.check_collision({_pos.x, _pos.y - 1.0f})) {
        _point.push_back({_pos.x, 0.1f, _pos.y});
        _point.push_back({_pos.x, 0.1f, _pos.y - 1.0f});
        directionBot = UP_STATE;
        currentMovement = DEFENSIVE_STATE;
        return true;
    }
    else if (CheckTileDanger({_pos.x, _pos.y + 1.0f}) && _body.check_collision({_pos.x, _pos.y + 1.0f})) {
        _point.push_back({_pos.x, 0.1f, _pos.y});
        _point.push_back({_pos.x, 0.1f, _pos.y + 1.0f});
        directionBot = DOWN_STATE;
        currentMovement = DEFENSIVE_STATE;

        return true;
    } return false;
}

void Indie::BombermanAI::defensiveState()
{
    _champPos = _body.getPos();
    float x = ceil(_champPos.x);
    float x2 = ceil(_champPos.x);
    float z = ceil(_champPos.z);
    float z2 = ceil(_champPos.z);
    float diff = 0.0f;
    float diff2 = 0.0f;
    float diff3 = 0.0f;
    float diff4 = 0.0f;

    while (!CheckTileDanger({x, _champPos.z}) && x <= _body.getMapWidth()) {
        if (!_body.check_collision({x, _champPos.z})) {
            x = _body.getMapWidth();
            break;
        }
        if (CheckAllAngle({x, _champPos.z}))
            return;
        x += 1.0f;
        diff += 1.0f;
    }

    while (!CheckTileDanger({x2, _champPos.z}) && x2 > 0) {
        if (!_body.check_collision({x2, _champPos.z})) {
            x2 = 0;
            break;
        }
        if (CheckAllAngle({x2, _champPos.z}))
            return;
        x2 -= 1.0f;
        diff2 += 1.0f;
    }

    while (!CheckTileDanger({_champPos.x, z}) && z <= _body.getMapHeight()) {
        if (!_body.check_collision({_champPos.x, z})) {
            z = _body.getMapHeight();
            break;
        }
        if (CheckAllAngle({_champPos.x, z}))
            return;
        z += 1.0f;
        diff3 += 1.0f;
    }

    while (!CheckTileDanger({_champPos.x, z2}) && z2 > 0) {
        if (!_body.check_collision({_champPos.x, z2})) {
            z2 = 0;
            break;
        }
        if (CheckAllAngle({_champPos.x, z2}))
            return;
        z2 -= 1.0f;
        diff4 += 1.0f;
    }
    currentMovement = DEFENSIVE_STATE;
}

void Indie::BombermanAI::move_next_point()
{
    if (_champPos.x > _point.begin()->x) {
        if (!_body.LeftMove(_body.getPos(), _time)) {
            plantBomb();
        }
        if (_body.getPos().x < _point.begin()->x) {
            _body.SetPosition({_point.begin()->x, _point.begin()->y, _point.begin()->z});
            _point.erase(_point.begin());
        }
    }
    else if (_champPos.x < _point.begin()->x) {
        if (!_body.RightMove(_body.getPos(), _time)) {
            plantBomb();
        }
        if (_body.getPos().x > _point.begin()->x) {
            _body.SetPosition({_point.begin()->x, _point.begin()->y, _point.begin()->z});
            _point.erase(_point.begin());
        }
    }
    else if (_champPos.z > _point.begin()->z) {
        if (!_body.UpMove(_body.getPos(), _time))  {
            plantBomb();  
        }
        if (_body.getPos().z < _point.begin()->z) {
            _body.SetPosition({_point.begin()->x, _point.begin()->y, _point.begin()->z});
            _point.erase(_point.begin());
        }
    }
    else if (_champPos.z < _point.begin()->z) {
        if (!_body.DownMove(_body.getPos(), _time))  {
            plantBomb();
        }
        if (_body.getPos().z > _point.begin()->z) {
            _body.SetPosition({_point.begin()->x, _point.begin()->y, _point.begin()->z});
            _point.erase(_point.begin());
        }
    }
    if (!_point.empty() && _point.begin()->x == _champPos.x && _point.begin()->z == _champPos.z) {
        _point.erase(_point.begin());
    }
    if (_point.empty()) {
        currentMovement = NO_STATE;
    }
}

void Indie::BombermanAI::Algorithm()
{
    if (currentMovement != NO_STATE)
        move_next_point();
    else if (!offensiveState())
        defensiveState();
    attackPlayer();
}

void Indie::BombermanAI::attackPlayer()
{
    for (auto const &c : _OtherPlayerPosition) {
        if (_champPos.x != c.x && _champPos.z != c.z) {
            if (_champPos.x > c.x)
                if (_champPos.x - range < c.x)
                    plantBomb();
            if (_champPos.x < c.x)
                if (_champPos.x + range > c.x)
                    plantBomb();
            if (_champPos.z > c.z)
                if (_champPos.z - range < c.z)
                    plantBomb();
            if (_champPos.z > c.z)
                if (_champPos.z + range < c.z)
                    plantBomb();
        }
    }
}

void Indie::BombermanAI::getPositionOfOtherPlayer(std::vector<Vector3> positionPlayer)
{
    _OtherPlayerPosition = positionPlayer;
    float x = 0.0f;
    float z = 0.0f;
    float glob = 0.0f, glob2 = 100.0f;

    for (auto const &playerPos : positionPlayer) {
        x = playerPos.x - _champPos.x;
        if (x < 0)
            x *= -1;
        z = playerPos.z - _champPos.z;
        if (z < 0)
            z *= -1;
        glob = x + z;
        if (glob2 > glob) {
            if (glob > 1) {
                _playerPos.x = playerPos.x;
                _playerPos.z = playerPos.z;
                glob2 = glob;
            }
        } glob = 0.0f;
    }
}


bool Indie::BombermanAI::CheckTileDanger(Vector3 _pos)
{
    _pos.x = floor(_pos.x);
    _pos.y = floor(_pos.y);

    if (_pos.x < 1 || _pos.y < 1 || _pos.x > _body.getMapWidth() || _pos.y > _body.getMapHeight()) {
        return false;
    }
    for (auto const &w : _dangerousTile) {
        if (w.x == _pos.x && w.z == _pos.y) {
            return false;
        }
    }
    if (_pos.x < 0 || _pos.y < 0)
        return false;
    return true;
}

void Indie::BombermanAI::plantBomb()
{
    if (bomb_nbr > 0)
        if (next_bomb > 5.0) {
            bomb_nbr--;
            next_bomb = 0.0;
            _body.CreateNewBomb();
        }
}

void Indie::BombermanAI::setPlayerToFocus(Vector3 _pos)
{
    _playerPos = _pos;
}

void Indie::BombermanAI::setMap(std::string mapPath)
{
    _body.setPlayerColision(mapPath);
}

void Indie::BombermanAI::setPosition(Vector3 Position)
{
    _body.SetPosition(Position);
    _champPos = _body.getPos();
    _point.push_back({_champPos.x, _champPos.y, _champPos.z});
}

std::vector<Vector3> Indie::BombermanAI::getBombPosition()
{
    return _body.getBombPosition();
}

void Indie::BombermanAI::makeExplodeBomb(Vector3 _bomb)
{
    _body.makeExplodeBomb(_bomb);
}

std::vector<Vector3> Indie::BombermanAI::GetExploZone()
{
    return _body.GetExploZone(alive);
}

void Indie::BombermanAI::setPlayerColision(std::string _PathToMap)
{
    _body.setPlayerColision(_PathToMap);
}

void Indie::BombermanAI::setBrickWall(std::vector<Vector3> _posWall)
{
    if (!alive)
        return ;
    _body.setBrickWall(_posWall);
}

void Indie::BombermanAI::setBricksPosition(std::vector<Vector3> _posWall)
{
    if (!alive)
        return ;
    _body.setBricksPosition(_posWall);
}

bool Indie::BombermanAI::destroy_after_death()
{
    if (alive)
        return false;
    time_bomb -= 0.01667;
    if (time_bomb < 0 && !alive)
        return true;
    return false;
}

void Indie::BombermanAI::CreateChamp(std::string champ)
{
    _champ = champ;
    _body.CreateNewChamp(champ);
}

std::string Indie::BombermanAI::getChamp()
{
    return (_champ);
}

void Indie::BombermanAI::addPowerUp(std::string _name)
{
    if (_name == "BombUp")
        max_bomb++;
    if (_name == "FireUp")
        _body.addRange();
    if (_name == "StrenghtUp")
        _body.addStrenght();
    if (_name == "SpeedUp")
        _body.addSpeed();
}

std::vector<float> Indie::BombermanAI::getStats()
{
    std::vector<float> all_stats;

    all_stats.push_back(static_cast<float>(max_bomb));
    all_stats.push_back(static_cast<float>(_body.getRange()));
    all_stats.push_back(static_cast<float>(_body.getStrenght()));
    all_stats.push_back((_body.getSpeed()));
    return all_stats;
}

void Indie::BombermanAI::setStats(float _max_bomb, float range, float strength, float speed)
{
    max_bomb = _max_bomb;
    _body.setRange(range);
    _body.setStrenght(strength);
    _body.setSpeed(speed);
}

void Indie::BombermanAI::setName(std::string name)
{
    _Currentname = name;
}

std::string Indie::BombermanAI::getPName()
{
    if (!alive)
        return "";
    return _Currentname;
}

std::vector<float> Indie::BombermanAI::getBigBrainStats()
{
    std::vector<float> all_stats;

    all_stats.push_back(static_cast<float>(max_bomb));
    all_stats.push_back(static_cast<float>(_body.getRange()));
    all_stats.push_back(static_cast<float>(_body.getStrenght()));
    all_stats.push_back(_body.getSpeed() * 10);
    return all_stats;
}