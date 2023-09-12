/*
** EPITECH PROJECT, 2021
** B-YEP-400-NCY-4-1-indiestudio-jean.gauthier-damioli
** File description:
** ShaderComponent
*/

#include "ShaderComponent.hpp"

Indie::ShaderComponent::ShaderComponent()
{
}

Indie::ShaderComponent::~ShaderComponent()
{
}

void Indie::ShaderComponent::SetShader(std::string _path)
{
    shader = LoadShader(0, TextFormat("Assets/Shaders/raymarching.fs", GLSL_VERSION));

    viewEyeLoc = GetShaderLocation(shader, "viewEye");
    viewCenterLoc = GetShaderLocation(shader, "viewCenter");
    runTimeLoc = GetShaderLocation(shader, "runTime");
    resolutionLoc = GetShaderLocation(shader, "resolution");

    float resolution[2] = { (float)GetScreenWidth(), (float)GetScreenHeight() };
    SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
}

Shader Indie::ShaderComponent::GetShader()
{
    return shader;
}

void Indie::ShaderComponent::draw()
{
    BeginShaderMode(shader);
    DrawRectangle(0, 0, 1, 1, WHITE);
    EndShaderMode();
}

void Indie::ShaderComponent::SetCameraShader(Vector3 cameraPosition, Vector3 cameraTarget)
{
    float cameraPos[3] = { cameraPosition.x, cameraPosition.y, cameraPosition.z };
    float cameraTar[3] = { cameraTarget.x, cameraTarget.y, cameraTarget.z };

    SetShaderValue(shader, viewEyeLoc, cameraPos, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, viewCenterLoc, cameraTar, SHADER_UNIFORM_VEC3);
}