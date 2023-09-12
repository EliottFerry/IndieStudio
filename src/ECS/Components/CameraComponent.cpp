/*
** EPITECH PROJECT, 2021
** CameraComponent
** File description:
** The file to implement the function of the hpp
*/

#include "CameraComponent.hpp"

void Indie::CameraComponent::init()
{
    cam = { 0 };
    Vector3 tmp = { 0.0f, 0.0f, 0.0f };
    cam.position = tmp;
    tmp = { 0.0f, 0.0f, 0.0f };
    cam.target = tmp;
    tmp = { -120.0f, 2.0f, 255.0f };
    cam.up = tmp;
    cam.fovy = 55.0f;
    cam.projection = CAMERA_PERSPECTIVE;
}

void Indie::CameraComponent::update(double time)
{
    UpdateCamera(&cam);
}

void Indie::CameraComponent::Begin3DCameraMod()
{
    BeginMode3D(cam);
}

bool Indie::CameraComponent::AdvanceInPath()
{
    if (PathToFollow.empty())
        return false;
    Vector3 _movStr = Strenght.back();
    Vector3 _nextMov = cam.position;
    Vector3 tmp = PathToFollow.back();

    if (tmp.x < _nextMov.x) {
        _nextMov.x -= _movStr.z;
        if (tmp.x > _nextMov.x)
            _nextMov.x = tmp.x;
    } else if (tmp.x > _nextMov.x) {
        _nextMov.x += _movStr.z;
        if (tmp.x < _nextMov.x)
            _nextMov.x = tmp.x;
    } if (tmp.y < _nextMov.y) {
        _nextMov.y -= _movStr.z;
        if (tmp.y > _nextMov.y)
            _nextMov.y = tmp.y;
    } else if (tmp.y > _nextMov.y) {
        _nextMov.y += _movStr.z;
        if (tmp.y < _nextMov.y)
            _nextMov.y = tmp.y;
    } if (tmp.z < _nextMov.z) {
        _nextMov.z -= _movStr.z;
        if (tmp.z > _nextMov.z)
            _nextMov.z = tmp.z;
    } else if (tmp.z > _nextMov.z) {
        _nextMov.z += _movStr.z;
        if (tmp.z < _nextMov.z)
            _nextMov.z = tmp.z;
    }

    cam.position = _nextMov;
    _nextMov = cam.target;
    Vector3 tmp2 = PathTarget.back();

    if (tmp2.x < _nextMov.x) {
        _nextMov.x -= _movStr.x;
        if (tmp2.x > _nextMov.x)
            _nextMov.x = tmp2.x;
    } else if (tmp2.x > _nextMov.x) {
        _nextMov.x += _movStr.x;
        if (tmp2.x < _nextMov.x)
            _nextMov.x = tmp2.x;
    }  if (tmp2.y < _nextMov.y) {
        _nextMov.y -= _movStr.x;
        if (tmp2.y > _nextMov.y)
            _nextMov.y = tmp2.y;
    } else if (tmp2.y > _nextMov.y) {
        _nextMov.y += _movStr.x;
        if (tmp2.y < _nextMov.y)
            _nextMov.y = tmp2.y;
    } if (tmp2.z < _nextMov.z) {
        _nextMov.z -= _movStr.x;
        if (tmp2.z > _nextMov.z)
            _nextMov.z = tmp2.z;
    } else if (tmp2.z > _nextMov.z) {
        _nextMov.z += _movStr.x;
        if (tmp2.z < _nextMov.z)
            _nextMov.z = tmp2.z;
    }

    cam.target = _nextMov;
    _nextMov = cam.up;
    Vector3 tmp3 = PathUp.back();

    if (tmp3.x < _nextMov.x) {
        _nextMov.x -= _movStr.y;
        if (tmp3.x > _nextMov.x)
            _nextMov.x = tmp3.x;
    } else if (tmp3.x > _nextMov.x) {
        _nextMov.x += _movStr.y;
        if (tmp3.x < _nextMov.x)
            _nextMov.x = tmp3.x;
    } if (tmp3.y < _nextMov.y) {
        _nextMov.y -= _movStr.y;
        if (tmp3.y > _nextMov.y)
            _nextMov.y = tmp3.y;
    } else if (tmp3.y > _nextMov.y) {
        _nextMov.y += _movStr.y;
        if (tmp3.y < _nextMov.y)
            _nextMov.y = tmp3.y;
    } if (tmp3.z < _nextMov.z) {
        _nextMov.z -= _movStr.y;
        if (tmp3.z > _nextMov.z)
            _nextMov.z = tmp3.z;
    } else if (tmp3.z > _nextMov.z) {
        _nextMov.z += _movStr.y;
        if (tmp3.z < _nextMov.z)
            _nextMov.z = tmp3.z;
    }

    cam.up = _nextMov;
   if (cam.position.x == tmp.x && cam.position.y == tmp.y && cam.position.z == tmp.z &&
        cam.target.x == tmp2.x && cam.target.y == tmp2.y && cam.target.z == tmp2.z &&
        cam.up.x == tmp3.x && cam.up.y == tmp3.y && cam.up.z == tmp3.z) {
        PathToFollow.pop_back();
        PathUp.pop_back();
        PathTarget.pop_back();
        Strenght.pop_back();
    }
    return true;
}

void Indie::CameraComponent::SetFovy(float fov)
{
    cam.fovy = fov;
}

void Indie::CameraComponent::SetUpVector(Vector3 up)
{
    cam.up = up;
}

void Indie::CameraComponent::SetTarget(Vector3 target)
{
    cam.target = target;
}

void Indie::CameraComponent::SetPathCamera(std::vector<Vector3> _Path)
{
    PathToFollow = _Path;
}

void Indie::CameraComponent::AddPathPoint(Vector3 PointTarget, Vector3 PointUp, Vector3 PointPos, Vector3 SetStrenght)
{
    PathToFollow.push_back(PointPos);
    PathUp.push_back(PointUp);
    PathTarget.push_back(PointTarget);
    Strenght.push_back(SetStrenght);
}

Camera3D Indie::CameraComponent::getCurrentCam()
{
    return cam;
}

void Indie::CameraComponent::SetEverythingCamera(Vector3 WTarget, Vector3 Wup, Vector3 Wpos)
{
    cam.target = WTarget;
    cam.position = Wpos;
    cam.up = Wup;
}

Indie::CameraComponent::~CameraComponent()
{
}
