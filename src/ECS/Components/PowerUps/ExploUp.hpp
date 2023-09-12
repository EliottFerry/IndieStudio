/*
** EPITECH PROJECT, 2021
** ExploUp
** File description:
** The file to implement the explo up component
*/

#ifndef EXPLOUP_HPP
#define EXPLOUP_HPP

#include "../PowerUpComponent.hpp"

namespace Indie {
    class ExploUp : public PowerUpComponent{
        public:
            ExploUp();
            ExploUp(Indie::ModelComponent);
            int getStatUp();
            ~ExploUp();

        protected:
        private:
            bool isPickedUp;
            int _addedStrenght;
    };
}

#endif /* !EXPLOUP_HPP */
