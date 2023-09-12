/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** File to create function of the ECS hpp file
*/

#include "ECS.hpp"
#include "Components.hpp"

Indie::Entity::Entity()
{
}

bool Indie::Entity::isActive() const
{
    return active;
}

void Indie::Entity::destroy()
{
    active = false;
}

void Indie::Entity::update(double time)
{
    for (auto &c : components)
        c->update(time);
}

void Indie::Entity::draw()
{
    for (auto &c : components)
        c->draw();
}

Indie::Entity::~Entity()
{
}

Indie::EntityManager::EntityManager()
{
}

void Indie::EntityManager::draw()
{
    for (auto &entity : entities) {
        entity->draw();
    }
}

void Indie::EntityManager::update(double time)
{
    for (auto &entity : entities) {
        entity->update(time);
    }    
}

void Indie::EntityManager::clear()
{
    for (auto &entity : entities) {
        entity.get()->destroy();
    }
    refresh();
}

Indie::Entity &Indie::EntityManager::getCamera()
{
    for (auto &entity : entities) {
        if (entity->hasComponent<Indie::CameraComponent>()) {
            return *entity.get();
        }
    }
    throw std::runtime_error("No camera component is contained in the entity.");
}

std::list<std::reference_wrapper<Indie::Entity>> Indie::EntityManager::getBomb()
{
    std::list<std::reference_wrapper<Indie::Entity>> list;
    for (auto &entity : entities) {
        if (entity->hasComponent<Indie::BombComponent>()) {
            list.push_back(*entity);
        }
    }
    if (list.empty())
        throw std::runtime_error("No bomb component is contained in the entity.");
    return list;
}

std::list<std::reference_wrapper<Indie::Entity>> Indie::EntityManager::getBreakWalls()
{
    std::list<std::reference_wrapper<Indie::Entity>> list;
    for (auto &entity : entities) {
        if (entity->hasComponent<Indie::BreakableWall>()) {
            list.push_back(*entity);
        }
    }
    if (list.empty())
        throw std::runtime_error("No breakable wall component is contained in the entity.");
    return list;
}

std::list<std::reference_wrapper<Indie::Entity>> Indie::EntityManager::getAudioDevice()
{
    std::list<std::reference_wrapper<Indie::Entity>> list;
    for (auto &entity : entities) {
        if (entity->hasComponent<Indie::Audio>()) {
            list.push_back(*entity);
        }
    }
    if (list.empty())
        throw std::runtime_error("No auudiodevice component is contained in the entity.");
    return list;
}

std::list<std::reference_wrapper<Indie::Entity>> Indie::EntityManager::getBombermanAI()
{
    std::list<std::reference_wrapper<Indie::Entity>> list;
    for (auto &entity : entities) {
        if (entity->hasComponent<Indie::BombermanAI>()) {
            list.push_back(*entity);
        }
    }
    return list;
}

std::list<std::reference_wrapper<Indie::Entity>> Indie::EntityManager::getModel()
{
    std::list<std::reference_wrapper<Indie::Entity>> list;
    for (auto &entity : entities) {
        if (entity->hasComponent<Indie::ModelComponent>()) {
            list.push_back(*entity);
        }
    }
    if (list.empty())
        throw std::runtime_error("No model component is contained in the entity.");
    return list;
}

std::list<std::reference_wrapper<Indie::Entity>> Indie::EntityManager::get2DModel()
{
    std::list<std::reference_wrapper<Indie::Entity>> list;
    for (auto& entity : entities) {
        if (entity->hasComponent<Indie::Model2DComponent>()) {
            list.push_back(*entity);
        }
    }
    if (list.empty())
        throw std::runtime_error("No 2D model component is contained in the entity.");
    return list;
}

std::list<std::reference_wrapper<Indie::Entity>> Indie::EntityManager::getPlayer()
{
    std::list<std::reference_wrapper<Indie::Entity>> list;
    for (auto& entity : entities) {
        if (entity->hasComponent<Indie::Player>()) {
            list.push_back(*entity);
        }
    }
    if (list.empty())
        throw std::runtime_error("No Player component is contained in the entity.");
    return list;
}

std::list<std::reference_wrapper<Indie::Entity>> Indie::EntityManager::getScore()
{
    std::list<std::reference_wrapper<Indie::Entity>> list;
    for (auto& entity : entities) {
        if (entity->hasComponent<Indie::Score>()) {
            list.push_back(*entity);
        }
    }
    if (list.empty())
        throw std::runtime_error("No Score component is contained in the entity.");
    return list;
}

std::list<std::reference_wrapper<Indie::Entity>> Indie::EntityManager::getText()
{
    std::list<std::reference_wrapper<Indie::Entity>> list;
    for (auto &entity : entities) {
        if (entity->hasComponent<Indie::TextComponent>()) {
            list.push_back(*entity);
        }
    }
    return list;
}

std::list<std::reference_wrapper<Indie::Entity>> Indie::EntityManager::getBox()
{
    std::list<std::reference_wrapper<Indie::Entity>> list;
    for (auto& entity : entities) {
        if (entity->hasComponent<Indie::BoxComponent>()) {
            list.push_back(*entity);
        }
    }
    if (list.empty())
        throw std::runtime_error("No box component is contained in the entity.");
    return list;
}

std::list<std::reference_wrapper<Indie::Entity>> Indie::EntityManager::getButton()
{
    std::list<std::reference_wrapper<Indie::Entity>> list;
    for (auto &entity : entities) {
        if (entity->hasComponent<Indie::ButtonComponent>()) {
            list.push_back(*entity);
        }
    }
    if (list.empty())
        throw std::runtime_error("No button component is contained in the entity.");
    return list;
}

std::list<std::reference_wrapper<Indie::Entity>> Indie::EntityManager::getShader()
{
    std::list<std::reference_wrapper<Indie::Entity>> list;
    for (auto &entity : entities) {
        if (entity->hasComponent<Indie::ShaderComponent>()) {
            list.push_back(*entity);
        }
    }
    if (list.empty())
        throw std::runtime_error("No shader component is contained in the entity.");
    return list;
}

std::list<std::reference_wrapper<Indie::Entity>> Indie::EntityManager::getTwoDComponent()
{
    std::list<std::reference_wrapper<Indie::Entity>> list;
    for (auto &entity : entities) {
        if (entity->hasComponent<Indie::TwoDComponent>()) {
            list.push_back(*entity);
        }
    }
    return list;
}

std::list<std::reference_wrapper<Indie::Entity>> Indie::EntityManager::getPowerUps()
{
    std::list<std::reference_wrapper<Indie::Entity>> list;
    for (auto &entity : entities) {
        if (entity->hasComponent<Indie::BombUp>() || entity->hasComponent<Indie::SpeedUp>() || entity->hasComponent<Indie::StrenghtUp>() || entity->hasComponent<Indie::ExploUp>()) {
            list.push_back(*entity);
        }
    }
    return list;
}

void Indie::EntityManager::refresh()
{
    entities.erase(std::remove_if(std::begin(entities), std::end(entities),
        [](const std::unique_ptr<Entity> &mEntity)
            {
                return !mEntity->isActive();
            }),
        std::end(entities));
}


Indie::Entity &Indie::EntityManager::addEntity()
{
    Entity *entity = new Entity();
    std::unique_ptr<Entity> uPtr{ entity };
    entities.emplace_back(std::move(uPtr));
    return *entity;
}

Indie::EntityManager::~EntityManager()
{
}