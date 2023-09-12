/*
** EPITECH PROJECT, 2021
** ModelComponent
** File description:
** The file to implement the function of the hpp file
*/

#include "ModelComponent.hpp"

Indie::ModelComponent::ModelComponent(std::string name) : _drawable(true)
{
    _name = name;
}

Indie::ModelComponent::ModelComponent() : _drawable(true)
{
}

void Indie::ModelComponent::setModel(std::string PathToModel)
{
    PathToModel = exec_path + (PathToModel);
    model = LoadModel(PathToModel.c_str());     // Load the model
}

Model Indie::ModelComponent::getModel()
{
    return model;
}

Indie::ModelComponent::~ModelComponent()
{

}

std::string Indie::ModelComponent::GetName()
{
    return _name;
}

Vector3 Indie::ModelComponent::getScale()
{
    return Scale;
}

bool Indie::ModelComponent::getDrawable()
{
    return _drawable;
}

void Indie::ModelComponent::update(double time)
{
    _totalTime += time;
    if (_totalTime > 0.03f) {
        Animated();
        _totalTime = 0.0f;
    }
}

void Indie::ModelComponent::clearRam()
{
    for (auto &c : _Animation) {
        UnloadModelAnimation(*c.second);
    }
    UnloadTexture(texture);
    UnloadModel(model);
}

void Indie::ModelComponent::Animated()
{
    if (CurrentAnimation == "NONE")
        return;
    if (CurrentAnimation == "Death" && animFrameCounter >= _Animation.at(CurrentAnimation)->frameCount - 1)
        return;
    animFrameCounter++;
    UpdateModelAnimation(model, _Animation.at(CurrentAnimation)[0], animFrameCounter);
    if (animFrameCounter >= _Animation.at(CurrentAnimation)->frameCount)
        animFrameCounter = 0;
}

void Indie::ModelComponent::setTexture(std::string _path, size_t i)
{
    _path = exec_path + (_path);
    texture = LoadTexture(_path.c_str());
    SetMaterialTexture(&model.materials[i], MAP_DIFFUSE, texture); // Put the texture on the model
}

void Indie::ModelComponent::setTexture(Texture text, size_t i)
{
    texture = text;
    SetMaterialTexture(&model.materials[i], MAP_DIFFUSE, texture);
}

void Indie::ModelComponent::AddAnimation(std::string AnimationName, std::string Path)
{
    Path = exec_path + (Path);
    ModelAnimation *anims = LoadModelAnimations(Path.c_str(), &animsCount);

    _Animation.insert(std::pair<std::string, ModelAnimation *>(AnimationName, anims));
}

void Indie::ModelComponent::setAnimation(std::map<std::string, ModelAnimation *> anim)
{
    _Animation = anim;
}

std::map<std::string, ModelAnimation *> Indie::ModelComponent::getAnimation()
{
    return _Animation;
}

void Indie::ModelComponent::setModel(Model mod)
{
    model = mod;
}

void Indie::ModelComponent::PlayAnimation(std::string AnimationName)
{
    if (CurrentAnimation == AnimationName)
        return;
    CurrentAnimation = AnimationName;
    animFrameCounter = 0;
}

void Indie::ModelComponent::SetPos(Vector3 Pos)
{
    _position = Pos;
}

Vector3 Indie::ModelComponent::getPos()
{
    return _position;
}

void Indie::ModelComponent::SetRotationAxis(Vector3 rot)
{
    _RotAxis = rot;
}

Vector3 Indie::ModelComponent::GetRotationAxis()
{
    return _RotAxis;
}

void Indie::ModelComponent::SetRotationAngle(float _rotAngle)
{
    _RotAng = _rotAngle;
}

float Indie::ModelComponent::GetRotationAngle()
{
    return _RotAng;
}

void Indie::ModelComponent::draw()
{
    if (_drawable)
        DrawModelEx(model, _position, _RotAxis, _RotAng, Scale, WHITE);
}

void Indie::ModelComponent::SetScale(Vector3 _Scale)
{
    Scale = _Scale;
}

Texture Indie::ModelComponent::getTexture()
{
    return texture;
}


void Indie::ModelComponent::setEverything(std::string PathModel, Vector3 PositionModel, Vector3 RotationAxis, Vector3 WantedScale,float RotationAngle)
{
    PathModel = exec_path + (PathModel);
    model = LoadModel(PathModel.c_str());

    _position = PositionModel;
    _RotAxis = RotationAxis;
    Scale = WantedScale;
    _RotAng = RotationAngle;
}

void Indie::ModelComponent::setShaderToModel(Shader _shader)
{
    model.materials[0].shader = _shader;
}

void Indie::ModelComponent::transformModel(Vector3 rotation)
{
    model.transform = MatrixRotateXYZ(rotation);
}

Indie::ModelComponent Indie::ModelComponent::CreateNewChamp(std::string WantedChamp)
{
    ModelComponent _Model;
    Vector3 scale;

    if (WantedChamp == "Knight") {
        scale = { 0.01f, 0.01f, 0.01f };
        _Model = createNewPlayer("Assets/Champion/Knight/Knight.iqm", "Assets/Champion/Knight/KnightTexture.png", "Assets/Champion/Knight/Idle.iqm", "Assets/Champion/Knight/Run.iqm", "Assets/Champion/Knight/Death.iqm", scale);
        return _Model;
    }  else if (WantedChamp == "Blitz") {
        scale = {  0.36f, 0.36f, 0.36f };
        _Model = createNewPlayer("Assets/Champion/Blitzcrank/blitz_mesh.iqm", "Assets/Champion/Blitzcrank/Blitztank_Texture_edit3.png", "Assets/Champion/Blitzcrank/blitz_idle_animation.iqm", "Assets/Champion/Blitzcrank/blitz_running_animation.iqm", "Assets/Champion/Blitzcrank/blitz_death_animation.iqm", scale);
        return _Model;
    } else if (WantedChamp == "Plant") {
        scale = { 0.2f, 0.2f, 0.2f };
        _Model = createNewPlayer("Assets/Champion/Plant/plant.iqm", "Assets/Champion/Plant/textures/plant_texture.png", "Assets/Champion/Plant/idle.iqm", "Assets/Champion/Plant/run.iqm", "Assets/Champion/Plant/death.iqm", scale);
        return _Model;
    } else if (WantedChamp == "Carlo") {
        scale = { 0.13f, 0.13f, 0.13f };
        _Model = createNewPlayer("Assets/Champion/Carlo/Carlo.iqm", "Assets/Champion/Carlo/squidward.png", "Assets/Champion/Carlo/Carlo_idle.iqm", "Assets/Champion/Carlo/Carlo_fast_run.iqm", "Assets/Champion/Carlo/Carlo_death.iqm", scale);
        return _Model;
    } else if (WantedChamp == "Crash") {
        scale = { 0.01f, 0.01f, 0.01f };
        _Model = createNewPlayer("Assets/Champion/Crash/Crash.iqm", "Assets/Champion/Crash/color_pallete_baseColor.png", "Assets/Champion/Crash/Crash_idle.iqm", "Assets/Champion/Crash/Crash_fast_run.iqm", "Assets/Champion/Crash/Crash_death.iqm", scale);
        return _Model;
    } else if (WantedChamp == "Krusty") {
        scale = { 1.0f, 1.0f, 1.0f };
        _Model = createNewPlayer("Assets/Champion/Krusty/Krusty.iqm", "Assets/Champion/Krusty/char_swatches_lit_bmp.png", "Assets/Champion/Krusty/Krusty_idle.iqm", "Assets/Champion/Krusty/Krusty_fast_run.iqm", "Assets/Champion/Krusty/Krusty_death.iqm", scale);
        return _Model;
    } else if (WantedChamp == "Ralph") {
        scale = { 1.3f, 1.3f, 1.3f };
        _Model = createNewPlayer("Assets/Champion/Ralph/Ralph.iqm", "Assets/Champion/Ralph/char_swatches_lit_bmp.png", "Assets/Champion/Ralph/Ralph_idle.iqm", "Assets/Champion/Ralph/Ralph_fast_run.iqm", "Assets/Champion/Ralph/Ralph_death.iqm", scale);
        return _Model;
    } else if (WantedChamp == "Spongebob") {
        scale = { 0.17f, 0.17f, 0.17f };
        _Model = createNewPlayer("Assets/Champion/Spongebob/Spongebob.iqm", "Assets/Champion/Spongebob/chr_sb05.png", "Assets/Champion/Spongebob/Spongebob_idle.iqm", "Assets/Champion/Spongebob/Spongebob_fast_run.iqm", "Assets/Champion/Spongebob/Spongebob_death.iqm", scale);
        return _Model;
    } 
    throw std::runtime_error ("Error cannot load: " + WantedChamp);
    return _Model;
}

Indie::ModelComponent Indie::ModelComponent::createNewPlayer(std::string iqm_base, std::string texture, std::string idle, std::string run, std::string death, Vector3 scale)
{
    ModelComponent _Model;
    Vector3 pos = { 1.0f, 0.1f, 1.0f};
    float RotAng = -90.0f;
    Vector3 RotAx = { 1.0f, 0.0f, 0.0f };

    _Model.setEverything(iqm_base, pos, RotAx, scale, RotAng);
    _Model.setTexture(texture);
    _Model.AddAnimation("Idle", idle);
    _Model.AddAnimation("Run", run);
    _Model.AddAnimation("Death", death);
    _Model.PlayAnimation("Idle");
    return _Model;
}

void Indie::ModelComponent::setDrawable(bool drawable)
{
    _drawable = drawable;
}