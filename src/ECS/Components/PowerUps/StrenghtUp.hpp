/*
** EPITECH PROJECT, 2021
** StrenghtUp
** File description:
** The file to implement wallpass powerup
*/

#ifndef WALLPASS_HPP
#define WALLPASS_HPP

#include "../PowerUpComponent.hpp"

namespace Indie {
    class StrenghtUp : public PowerUpComponent{
        public:
            StrenghtUp();
            StrenghtUp(Indie::ModelComponent);
            bool getStatUp();
            ~StrenghtUp();

        protected:
        private:
            /*!  */
            bool isPickedUp;
            bool _isStrenghtUping;
    };
}

#endif /* !WALLPASS_HPP */
