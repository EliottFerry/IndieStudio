/*
** EPITECH PROJECT, 2021
** Credit.hpp
** File description:
** Credit.hpp
*/

#ifndef CREDIT_HPP
#define CREDIT_HPP

#include <iostream>
#include "raylib.h"
#include "../AScene.hpp"
#include "../SceneManager.hpp"
#include "../../ECS/Components.hpp"
#include "../../ECS/ECS.hpp"

namespace Indie {

    class Credit : public Indie::AScene {
        public:
            Credit(Indie::SceneManager& manager);
            ~Credit();
            bool update(double time) override;
            void draw() override;
            /*! Generic function to draw. */
            void putNameDev(std::string name, int nb);
        protected:
        private:
            EntityManager entity;
            /*! The list of all the text entity in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _Text;
            /*! The list of all the image entity in the scene. */
            std::list<std::reference_wrapper<Indie::Entity>> _Image;
            /*! Save the size of the window. */
            Vector2 _SizeWindow;
    };

};

#endif /* !CREDIT_HPP */
