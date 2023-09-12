/*
** EPITECH PROJECT, 2021
** PowerUpComponent
** File description:
** The file to implement powerups
*/

#ifndef POWERUPCOMPONENT_HPP
#define POWERUPCOMPONENT_HPP

#include "ModelComponent.hpp"
#include "PositionComponent.hpp"
#include "../ECS.hpp"

namespace Indie {
    class PowerUpComponent : public ModelComponent {
        public:
            PowerUpComponent(std::string name);
            ~PowerUpComponent();
            void update(double time) override;
            void draw() override;

            /*! Set the model to our power up. */
            void setModelComponent(ModelComponent modelToSet);
        protected:
        private:
    };
}

#endif /* !POWERUPCOMPONENT_HPP */
