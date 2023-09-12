/*
** EPITECH PROJECT, 2021
** Components
** File description:
** File to handle differents type of components
*/

#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include "../ECS.hpp"
#include "raylib.h"

namespace Indie {
    class PositionComponent : public Component {
        private:
            Vector3 _pos;
        public:
            PositionComponent();
            ~PositionComponent();
            /*! Returns the current position of the component. */
            Vector3 getPos();
            /*! Initialize the position of the component at 0.0.0. */
            void init() override;
            /*! To modify the position of the component. */
            void setPos(float x, float y, float z);
    };
}

#endif /* !COMPONENTS_HPP */
