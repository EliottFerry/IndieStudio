/*
** EPITECH PROJECT, 2021
** ExplosionComponent
** File description:
** The file to handle the explosion animation
*/

#include "ExplosionComponent.hpp"

Indie::ExplosionComponent::ExplosionComponent(std::string path)
{
    explosion = LoadTexture(path.c_str());
}

void Indie::ExplosionComponent::init()
{
    frameHeight = explosion.height / NUM_LINES;
    frameWidth = explosion.width / NUM_FRAMES_PER_LINE;
    frameRect = { 0, 0, frameWidth, frameHeight };
    position = { 0.0f, 0.0f };
    frameCounter = 0;
    currentFrame = 0;
    currentLine = 0;
    active = false;
}

void Indie::ExplosionComponent::update(double time)
{
    if (!active) {
        active = true;
    }
    if (active) {
        frameCounter++;
        if (frameCounter > 2) {
            currentFrame++;
            if (currentFrame >= NUM_FRAMES_PER_LINE) {
                currentFrame = 0;
                currentLine++;
                if (currentLine >= NUM_LINES) {
                    currentLine = 0;
                    active = false;
                    UnloadTexture(explosion);
                    entity->destroy();
                }
            }
            frameCounter = 0;
        }
    }
    frameRect.x = frameWidth * currentFrame;
    frameRect.y = frameHeight * currentLine;
}

bool Indie::ExplosionComponent::Usable()
{
    return active;
}

void Indie::ExplosionComponent::draw()
{
    if (active)
        DrawTextureRec(explosion, frameRect, position, WHITE);
}

Indie::ExplosionComponent::~ExplosionComponent()
{
}
