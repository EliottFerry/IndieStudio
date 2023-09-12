/*
** EPITECH PROJECT, 2021
** initscene
** File description:
** The file to handle the init scene
*/

#ifndef INITSCENE_HPP
#define INITSCENE_HPP

#include <iostream>
#include "raylib.h"
#include "../AScene.hpp"
#include "../../ECS/Components.hpp"
#include "../../ECS/ECS.hpp"
#include "../SceneManager.hpp"
#include "ChangePath.hpp"
extern std::string exec_path;

namespace Indie {
    class initScene : public AScene
    {
        private:
            /*! The manager of all the entity in the scene. */
            EntityManager entities;
            /*! The list who store all the logos in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _logos;
            /*! The list who store all the texts in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _texts;
            /*! Are we switching scene. */
            bool _switched;
            /*! Current text. */
            int _currentText;
        public:
            initScene(Indie::SceneManager& manager);
            ~initScene();

            bool update(double time) override;
            void draw() override;
    };
    
}

#endif /* !INITSCENE_HPP */
