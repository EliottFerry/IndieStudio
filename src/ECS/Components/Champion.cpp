/*
** EPITECH PROJECT, 2021
** B-YEP-400-NCY-4-1-indiestudio-jean.gauthier-damioli
** File description:
** Champion
*/

#include "Champion.hpp"

Indie::Champion::Champion()
{
}

Indie::Champion::~Champion()
{
}

void Indie::Champion::init()
{

}

void Indie::Champion::update(double time)
{
    _model.update(time);
    if (!_PlacableBomb.empty()) {
        for (auto& y : _PlacableBomb) {
            y.update(time);
        }
    }
}

void Indie::Champion::draw()
{
    size_t i = 0;
    
    _model.draw();
    if (!_PlacableBomb.empty()) {
        for (auto &y : _PlacableBomb) {
            y.draw();
            if (y.checkExploded()) {
                _PlacableBomb.erase(_PlacableBomb.begin());
            }
            i++;
        }
    }
}

int Indie::Champion::getMapHeight()
{
    return cubicmap.height;
}

int Indie::Champion::getMapWidth()
{
    return cubicmap.width;
}

bool Indie::Champion::check_hard_collision(Vector2 _pos)
{
    Rectangle tmp;
    _pos.x = ceil(_pos.x);
    _pos.y = ceil(_pos.y);

    tmp = { _pos.x, _pos.y, 1.0f, 1.0f };
    if ((mapPixel[(int)_pos.y * cubicmap.width + (int)_pos.x].r == 255) &&       // Collision: white pixel, only check R channel
        (CheckCollisionCircleRec({ _pos.x, _pos.y } , 1.2f, tmp)))
        return false;
    for (auto &x : _Bricks) {
        tmp = { x.x, x.z };
        if (CheckCollisionCircleRec({ _pos.x, _pos.y }, 0.84f, tmp))
            return false;
    } return true;
}

bool Indie::Champion::check_collision(Vector2 _pos)
{
    Rectangle tmp;
    _pos.x = round(_pos.x);
    _pos.y = round(_pos.y);

    tmp = { _pos.x, _pos.y, 1.2f, 1.2f };
    if ((mapPixel[(int)_pos.y * cubicmap.width + (int)_pos.x].r == 255) &&       // Collision: white pixel, only check R channel
        (CheckCollisionCircleRec({ _pos.x, _pos.y } , 1.2f, tmp)))
        return false;
    for (auto &x : _Bricks) {
        tmp = { x.x, x.z };
        if (CheckCollisionCircleRec({ _pos.x, _pos.y }, 0.9f, tmp))
            return false;
    }
    return true;
}

bool Indie::Champion::LeftMove(Vector3 oldPos, double time)
{
    if (check_collision({ oldPos.x - (speed * (float)time), oldPos.z })) {
        _model.SetPos({oldPos.x - (speed * (float)time), oldPos.y, oldPos.z});
        if (currentDirection != LEFT_ANIM) {
            currentDirection = LEFT_ANIM;
            _model.SetRotationAxis({ 15.0f, 13.0f, 12.0f });
            _model.SetRotationAngle(-113);
            _model.PlayAnimation("Run");
        }
        return true;
    } return false;
}

bool Indie::Champion::RightMove(Vector3 oldPos, double time)
{
    if (check_collision({ oldPos.x + (speed * (float)time), oldPos.z })) {
        _model.SetPos({ oldPos.x + (speed * (float)time), oldPos.y, oldPos.z });
        if (currentDirection != RIGHT_ANIM) {
            currentDirection = RIGHT_ANIM;
            _model.SetRotationAxis({ 110.0f, -91.0f, -84.0f });
            _model.SetRotationAngle(-130);
            _model.PlayAnimation("Run");
        }
        return true;
    } return false;
}

bool Indie::Champion::UpMove(Vector3 oldPos, double time)
{
    if (check_collision({ oldPos.x, oldPos.z - (speed * (float)time) })) {
        _model.SetPos({oldPos.x, oldPos.y, oldPos.z - (speed * (float)time)});
        if (currentDirection != UP_ANIM) {
            currentDirection = UP_ANIM;
            _model.SetRotationAxis({ 1.0f, 16.0f, 22.0f });
            _model.SetRotationAngle(-177);
            _model.PlayAnimation("Run");
        }
        return true;
    } return false;
}

bool Indie::Champion::DownMove(Vector3 oldPos, double time)
{
    if (check_collision({ oldPos.x, oldPos.z + (speed * (float)time) })) {
        _model.SetPos({oldPos.x, oldPos.y, oldPos.z + (speed * (float)time)});
        if (currentDirection != DOWN_ANIM) {
            currentDirection = DOWN_ANIM;
            _model.SetRotationAxis({ 1.0f, 0.0f, 0.0f });
            _model.SetRotationAngle(-90);
            _model.PlayAnimation("Run");
        }
        return true;
    } return false;
}

Vector3 Indie::Champion::getPos()
{
    return _model.getPos();
}

void Indie::Champion::PlayAnimation(std::string _anim)
{
    currentDirection = NO_ANIM;
    _model.PlayAnimation(_anim);
}

void Indie::Champion::CreateNewChamp(std::string _ChampName)
{
    _model = _model.CreateNewChamp(_ChampName);
    _bomb = _bomb.CreateNewBomb();
}

void Indie::Champion::SetPosition(Vector3 _position)
{
    _model.SetPos(_position);
}

void Indie::Champion::setBricksPosition(std::vector<Vector3> _posWall)
{
    _Bricks = _posWall;
}

void Indie::Champion::setPlayerColision(std::string _PathToMap)
{
    _PathToMap = exec_path + (_PathToMap);
    Image image = LoadImage(_PathToMap.c_str());

    mapPixel = LoadImageColors(image);
    cubicmap = LoadTextureFromImage(image);

    UnloadImage(image);
}

void Indie::Champion::setBrickWall(std::vector<Vector3> _posWall)
{
    _Bricks = _posWall;
    for (auto &y : _PlacableBomb) {
        y.setBricks(_posWall);
    }
}

void Indie::Champion::CreateNewBomb()
{
    _bomb.setStrenght(strenght);
    _bomb.setRange(range);
    _bomb.setPosition(_model.getPos());
    _bomb.setIndestructibleWall(cubicmap, mapPixel);
    _PlacableBomb.push_back(_bomb);   
}

std::vector<Vector3> Indie::Champion::GetExploZone(bool alive)
{
    std::vector<Vector3> _kaboum;
    Rectangle tmp;

    for (auto &bomb : _PlacableBomb) {
        for (auto &explo : bomb.GetExplosionZone()) {
            _kaboum.push_back(explo.getPos());
        }
    } return _kaboum;
}

std::vector<Vector3> Indie::Champion::getBombPosition()
{
    std::vector<Vector3> _BombPos;

    for (auto &bomb : _PlacableBomb) {
        _BombPos.push_back(bomb.getPosition());
    } return _BombPos;
}

void Indie::Champion::makeExplodeBomb(Vector3 _bomb)
{
    for (auto &i : _PlacableBomb) {
        if (i.getPosition().x == _bomb.x && i.getPosition().z == _bomb.z)
            i.explodeBomb();
    }
}

void Indie::Champion::addRange()
{
    range++;
}

void Indie::Champion::addStrenght()
{
    strenght++;
}

int Indie::Champion::getStrenght()
{
    return strenght;
}

int Indie::Champion::getRange()
{
    return range;
}

void Indie::Champion::addSpeed()
{
    speed += 0.2f;
}

float Indie::Champion::getSpeed()
{
    return speed;
}

void Indie::Champion::setSpeed(float _speed)
{
    speed = _speed;
}

void Indie::Champion::setStrenght(float _strength)
{
    strenght = static_cast<int>(_strength);
}

void Indie::Champion::setRange(float _range)
{
    range = static_cast<int>(_range);
}