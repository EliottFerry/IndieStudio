/*
** EPITECH PROJECT, 2021
** Player
** File description:
** File to handle the player component
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "../ECS.hpp"
#include "BombComponent.hpp"
#include "ModelComponent.hpp"
#include "Champion.hpp"

namespace Indie {
    class Player : public Component {
        private:
            Indie::Champion _model;
            std::vector<Vector3> _ExploPlace;
            int bomb_nbr = 1;
            int max_bomb = 1;
            int player_num = 0;
            int gamepad = 0;
            float time_bomb = 0.0f;
            float next_bomb = 0.0f;
            bool alive = true;
            bool active = false;
            std::string _champ;
            std::string _Currentname;
            std::list<std::reference_wrapper<Indie::Entity>> ComponentIndie;
        public:
            Player() = default;
            ~Player();
            /*! Initialize the value for the player */
            void init() override;
            /*! Update the player based on the inputs */
            void update(double time) override;
            /*! Draw the player. */
            void draw() override;
            /*! Give you access to the ModelComponent of the player. */
            void createNewPlayer(std::string _ChampName);
            /*! Call the addAnimation of the model */
            void AddAnimation(std::string _AnimationName, std::string _path);
            /*! Check all the colision based on the given movement */
            void setPlayerColision(std::string _PathToMap);
            /*! Use to move the player in the wanted direction */
            void makeMovement(double time);
            Vector3 getPosition();
            /*! Set all the bricks position, aka the breakable wall */
            void setBricksPosition(std::vector<Vector3> _posWall);
            /*! return all the explosion that touch something */
            std::vector<Vector3> GetExploZone();
            /*! Set all the brickwall to manage hitbox for the movement */
            void setBrickWall(std::vector<Vector3> _posWall);
            /*! Set the position of the player */
            void SetPosition(Vector3 _position);
            /*! Get all the position of all planted bomb */
            std::vector<Vector3> getBombPosition();
            /*! If a bomb is touch by another explosion make it explode */
            void makeExplodeBomb(Vector3 _bomb);
            /*! check if the player is dead */
            void isDead();
            /*! get the champ */
            std::string getChamp();
            /*! check if the player is dead and return  */
            bool isAlive();
            /*! set the gamepad to the player */
            void SetGamepad(int control, int player);
            /*! after a few time after death destroy the player */
            bool destroy_after_death();
            /*! Add the power up stat to your character. */
            void addPowerUp(std::string _name);
            /*! Set the player stats. */
            void setStats(float, float, float, float);
            /*! Return a vector of all the stat of the player. */
            std::vector<float> getStats();

            std::vector<float> getBigBrainStats();

            /*! Get the strenght and the lenght of the explosition of the player. */
            std::pair<int, int> getCapacity();
            /*! Get the name of the player. */
            std::string getName();
            /*! Set if the player is active. */
            void setActive();

            void setName(std::string name);

            std::string getPName();
        protected:
    };
}

#endif /* !PLAYER_HPP_ */



