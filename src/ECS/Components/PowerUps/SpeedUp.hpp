/*
** EPITECH PROJECT, 2021
** SpeedUp
** File description:
** THe file to implement speed up powerup
*/

#ifndef SPEEDUP_HPP
#define SPEEDUP_HPP

#include "../PowerUpComponent.hpp"

namespace Indie {
    class SpeedUp : public PowerUpComponent{
        public:
            SpeedUp();
            SpeedUp(Indie::ModelComponent);
            float getStatUp();
            ~SpeedUp();

        protected:
        private:
            bool isPickedUp;
            float _addedSpeed;
    };
}

#endif /* !SPEEDUP_HPP */
