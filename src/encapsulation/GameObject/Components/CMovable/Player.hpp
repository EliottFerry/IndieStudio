/*
** EPITECH PROJECT, 2021
** Player
** File description:
** Player game object, to handle every player actions
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../../IComponent.hpp"
#include "raylib.h"
#include "../../../Models.hpp"
#include <map>
#include <string>

namespace Indie {
    class Player : public IComponent{
        public:
            Player();
            ~Player();

            /*! Function that returns the position of the player Object. */
            Vector3 getPlayerPos();

            /*! Function used to move the player Object depending on his speed stat. */
            void movePlayer();

            /*! Get the skin of the player to make change */
            Indie::Models GetSkin();

            /*! Set an already created model */
            void SetModel(Indie::Models);

            /*! Set the position of the player */
            void SetPosition(Vector3 _position);
        protected:
            /*! The vector where we store the player position. */
            Vector3 _posPlayer;

            /*! The variable where we store the HP of the player. */
            int _hp;

            /*! A map, where we store the differents stats of the player, such as his speed, his bomb power... */
            std::map<std::string, float> _stats;

            /*! This is the skin of the player */
            Indie::Models _skin;
        private:
    };
}

#endif /* !PLAYER_HPP */
