/*
** EPITECH PROJECT, 2021
** BombComponent
** File description:
** The file to implement all the method for the bomb
*/

#include "BombComponent.hpp"

Indie::BombComponent::BombComponent()
{

}

void Indie::BombComponent::setBricks(std::vector<Vector3> _posWall)
{
    _walls = _posWall;
}

Vector3 Indie::BombComponent::getPosition()
{
    return _model.getPos();
}

void Indie::BombComponent::setStrenght(int _strenght)
{
    strenght = _strenght;
}

void Indie::BombComponent::setRange(int _range)
{
    range = _range;
}

void Indie::BombComponent::setPosition(Vector3 _pos)
{
    if (round(_pos.x) < _pos.x)
        _pos.x = round(_pos.x);
    else
        _pos.x = round(_pos.x);
    if (round(_pos.z) < _pos.z)
        _pos.z = round(_pos.z);
    else
        _pos.z = round(_pos.z);
    _model.SetPos(_pos);
}

void Indie::BombComponent::init()
{

}

Indie::BombComponent Indie::BombComponent::CreateNewBomb()
{
    Indie::BombComponent Bomb;

    Bomb._timeExploding = 1.0f;
    Bomb._model.setEverything("Assets/animations/bomb2/bomb.iqm", { 1.0f, 1.0f, 1.0f}, { 1.0f, 0.0f, 0.0f }, { 0.7f, 0.7f, 0.7f }, -90.0f);
    Bomb._model.AddAnimation("Idle", "Assets/animations/bomb2/bomb_animation.iqm");
    Bomb._model.setTexture("Assets/animations/bomb2/bomb_texture.png");
    Bomb._model.PlayAnimation("Idle");
    Bomb._explosion.setEverything("Assets/explosion/explosion/explosion.iqm", { 1.0f, 1.0f, 1.0f}, { 1.0f, 0.0f, 0.0f }, { 0.003f, 0.003f, 0.003f }, -90.0f);
    Bomb._explosion.setTexture("Assets/explosion/explosion/explosion_texture.png");
    Bomb._explosion.AddAnimation("Idle", "Assets/explosion/explosion/explosion_animation.iqm");
    Bomb._explosion.PlayAnimation("Idle");
    return Bomb;
}

void Indie::BombComponent::setIndestructibleWall(Texture2D cub, Color *map)
{
    width = cub.width;
    mapPixel = map;
}

bool Indie::BombComponent::checkExploded()
{
    return exploded;
}

bool Indie::BombComponent::ThereIsAWall(float x, float z)
{
    for (auto const &w : _walls)
        if (w.x == x && w.z == z)
            return true;
    return false;
}

void Indie::BombComponent::create_explosion()
{
    _explosion.SetPos({ x, 0.0f, z });
    _explo.push_back(_explosion);
    Rectangle tmp;
    remstrenght = strenght;

    for (int i = 0; i < range; i++) {
        x++;
        if (mapPixel[width * int(z) + int(x)].r == 255)
            break;
        if (ThereIsAWall(x, z) && strenght > 0) {
            _explosion.SetPos({ x, 0.0f, z });
            _explo.push_back(_explosion);
            strenght--;
        } else if (!ThereIsAWall(x, z)) {
            _explosion.SetPos({ x, 0.0f, z });
            _explo.push_back(_explosion);
        }
    }
    x = _model.getPos().x;
    strenght = remstrenght;
    for (int i = 0; i < range; i++) {
        x--;
        if (mapPixel[width * int(z) + int(x)].r == 255)
            break;
        if (ThereIsAWall(x, z) && strenght > 0) {
            _explosion.SetPos({ x, 0.0f, z });
            _explo.push_back(_explosion);
            strenght--;
        } else if (!ThereIsAWall(x, z)) {
            _explosion.SetPos({ x, 0.0f, z });
            _explo.push_back(_explosion);
        }
    }
    x = _model.getPos().x;
    strenght = remstrenght;
    for (int i = 0; i < range; i++) {
        z++;
        if (mapPixel[width * int(z) + int(x)].r == 255)
            break;
        if (ThereIsAWall(x, z) && strenght > 0) {
            _explosion.SetPos({ x, 0.0f, z });
            _explo.push_back(_explosion);
            strenght--;
        } else if (!ThereIsAWall(x, z)) {
            _explosion.SetPos({ x, 0.0f, z });
            _explo.push_back(_explosion);
        }
    }
    z = _model.getPos().z;
    strenght = remstrenght;
    for (int i = 0; i < range; i++) {
        z--;
        if (mapPixel[width * int(z) + int(x)].r == 255)
            break;
        if (ThereIsAWall(x, z) && strenght > 0) {
            _explosion.SetPos({ x, 0.0f, z });
            _explo.push_back(_explosion);
            strenght--;
        } else if (!ThereIsAWall(x, z)) {
            _explosion.SetPos({ x, 0.0f, z });
            _explo.push_back(_explosion);
        }
    }
    strenght = remstrenght;
}

void Indie::BombComponent::update(double time)
{
    _timeExploding -= time / 3;
    _model.update(time);
    if (_timeExploding <= 0) {
        if (anim == true) {
            exploded = true;
        }
        if (anim == false) {
            anim = true;
            x = _model.getPos().x;
            z = _model.getPos().z;
            Indie::Audio::Instance().startPlayingExplosion();
            create_explosion();
            _timeExploding = 0.18f;
        }
    }
    for (auto &y : _explo) {
        y.update(time);
    }
}

void Indie::BombComponent::draw()
{
    if (!anim) {
        _model.draw();
    } else {
        for (auto &y : _explo) {
            y.draw();
        }
    }
}

Indie::BombComponent::~BombComponent()
{
}

void Indie::BombComponent::setBombStrenght(int muscle)
{
    strenght = muscle;
}

void Indie::BombComponent::setBombRange(int str)
{
    range = str;
}

std::vector<Indie::ModelComponent> Indie::BombComponent::GetExplosionZone()
{
    return _explo;
}

void Indie::BombComponent::explodeBomb()
{
    if (anim == false)
        _timeExploding = 0.0f;
}