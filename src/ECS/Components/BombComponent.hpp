/*
** EPITECH PROJECT, 2021
** BombComponent
** File description:
** The file to implement bomb method
*/

#ifndef BOMBCOMPONENT_HPP
#define BOMBCOMPONENT_HPP

#include "../ECS.hpp"
#include "ModelComponent.hpp"
#include "Audio.hpp"

namespace Indie {
    class BombComponent : public Component {
        public:
            BombComponent();
            ~BombComponent();

            void init() override;
            void update(double time) override;
            void draw() override;

            /*! Set the position of the bomb, automatically place it in the middle */
            void setPosition(Vector3 _pos);

            /*! Check if the bomb as exploded or not */
            bool checkExploded();

            /*! Set the range which is used for the range of the explosion*/
            void setRange(int);

            /*! Set the strenght which is used to destroy a certain number of wall a the same time */
            void setStrenght(int);

            /*! Create a new Bomb */
            BombComponent CreateNewBomb();

            /*! Get vector full of the placement of the explosion */
            std::vector<ModelComponent> GetExplosionZone();

            /*! Set the indestructible wall that cannot be destroyed */
            void setIndestructibleWall(Texture2D cub, Color *map);
            ModelComponent _model;

            /*! Set the breakable wall */
            void setBricks(std::vector<Vector3>);

            /*! Get the position of the bomb */
            Vector3 getPosition();

            /*! If there is a explosion on the bomb position it explode */
            void explodeBomb();

            /*! Set the strenght of the bomb the strenght reprensent the
            number of wall an explosion can destroy */
            void setBombStrenght(int);

            /*! The range of the bomb is the maximum number of explosion
            the bomb can do */
            void setBombRange(int);
        protected:
        private:
            int width;
            Color *mapPixel;
            /*! Create the explosion of the bomb. */
            void create_explosion();
            /*! Is the bomb exploded. */
            bool exploded = false;
            /*! The model of the explosion. */
            ModelComponent _explosion;
            /*! The vector of all the model for the explosion of the bomb. */
            std::vector<ModelComponent> _explo;
            /*! The vector of the position of all the walls of the map. */
            std::vector<Vector3> _walls;
            /*! The range of the bomb. */
            int range = 1;
            /*! The strenght of the bomb. */
            int strenght = 1;

            int remstrenght;
            /*! The position of the bomb. */
            float x, z;
            /*! The time before the bomb explode. */
            float _timeExploding;
            /*! Boolean to start the animation. */
            bool anim = false;
            /*! The function to check if there is a wall. */
            bool ThereIsAWall(float , float);
    };
}

#endif /* !BOMBCOMPONENT_HPP */
