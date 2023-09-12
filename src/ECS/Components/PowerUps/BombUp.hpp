/*
** EPITECH PROJECT, 2021
** BombUp
** File description:
** The file to implement bomb up power up
*/

#ifndef BOMBUP_HPP
#define BOMBUP_HPP

#include "../PowerUpComponent.hpp"
#include "../../ECS.hpp"

namespace Indie {
    class BombUp : public PowerUpComponent {
        public:
            BombUp();
            BombUp(Indie::ModelComponent);
            ~BombUp();
            int getStatUp();
        protected:
        private:
            bool isPickedUp;
            int _addedBomb;
    };
}

#endif /* !BOMBUP_HPP */
