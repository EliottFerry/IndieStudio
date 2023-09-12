/*
** EPITECH PROJECT, 2021
** Model2DComponent
** File description:
** The cpp file which contain the functions Model2DComponent
*/

#include "Model2DComponent.hpp"

Indie::Model2DComponent::Model2DComponent(std::string PathMap, std::string PathTexture)
{
    PathMap = exec_path + (PathMap);
    PathTexture = exec_path + (PathTexture);
    Image image = LoadImage(PathMap.c_str());      // Load cubicmap image (RAM)
    Texture2D cubicmap = LoadTextureFromImage(image);       // Convert image to texture to display (VRAM)
    Vector3 tmp = { 1.0f, 1.0f, 1.0f };
    Mesh mesh = GenMeshCubicmap(image, tmp);
    model = LoadModelFromMesh(mesh);
    Color *mapPixels = LoadImageColors(image);

    // NOTE: By default each cube is mapped to one part of texture atlas
    Texture2D texture = LoadTexture(PathTexture.c_str());    // Load map texture
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;             // Set map diffuse texture pas touche

    mapPosition = { 0.0f, 0.0f, 0.0f };          // Set model position

    UnloadImage(image);     // Unload cubesmap image from RAM, already uploaded to VRAM
}

Indie::Model2DComponent::~Model2DComponent()
{
}

void Indie::Model2DComponent::draw()
{
    DrawModel(model, mapPosition, 1.0f, WHITE);
}