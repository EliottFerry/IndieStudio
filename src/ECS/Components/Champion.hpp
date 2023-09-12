/*
** EPITECH PROJECT, 2021
** B-YEP-400-NCY-4-1-indiestudio-jean.gauthier-damioli
** File description:
** Champion
*/

#ifndef CHAMPION_HPP_
#define CHAMPION_HPP_

#include "../ECS.hpp"
#include "BombComponent.hpp"
#include "ModelComponent.hpp"

namespace Indie {
    class Champion : public Component {
        public:
            Champion();
            ~Champion();
            void init() override;
            /*! Update the player based on the inputs */
            void update(double time) override;
            /*! Draw the player. */
            void draw() override;
            /*! The function to move the champion to the left */
            bool LeftMove(Vector3 oldPos, double time);

            /*! The function to move the champion to the right */
            bool RightMove(Vector3 oldPos, double time);

            /*! The function to move the champion up */
            bool UpMove(Vector3 oldPos, double time);

            /*! The function to move the champion down */
            bool DownMove(Vector3 oldPos, double time);

            /*! The function to move the champion to the left */
            Vector3 getPos();

            /*! Check the collision between the terrain and the player. */
            bool check_collision(Vector2 _pos);

            /*! Play the animation of the Champion. */
            void PlayAnimation(std::string _anim);

            /*! Create a new champion and set a name to it. */
            void CreateNewChamp(std::string _ChampName);

            /*! SEt the position of the Champion by using a Vector3. */
            void SetPosition(Vector3 _position);

            /*! Set the position of all the bricks. */
            void setBricksPosition(std::vector<Vector3> _posWall);

            /*! Set the collision of the player with the map. */
            void setPlayerColision(std::string _PathToMap);

            /*! Set all the bricks. */
            void setBrickWall(std::vector<Vector3> _posWall);

            /*! Create a placed bomb. */
            void CreateNewBomb();

            /*! Get the zone of an explosion. */
            std::vector<Vector3> GetExploZone(bool alive);

            /*! Geet the position of the placed bomb. */
            std::vector<Vector3> getBombPosition();

            /*! Explode the placed bomb. */
            void makeExplodeBomb(Vector3 _bomb);

            /*! Return the height of the map. */
            int getMapHeight();
            
            /*! Return the Width of the map */
            int getMapWidth();

            /*!  */
            bool check_hard_collision(Vector2 _pos);

            /*! Add range to the bomb. */
            void addRange();

            /*! Add strenght to the bomb. */
            void addStrenght();

            /*! Get the range of the bomb. */
            int getRange();

            /*! Get the strenght of the bomb. */
            int getStrenght();

            /*! Get the speed of the champion. */
            float getSpeed();

            /*! Add the speed to the player. */
            void addSpeed();
       
            /*! Set the speed of the champion. */
            void setSpeed(float);
            /*! Set the range of the champion's bomb. */
            void setRange(float);
            /*! Set the strenght of the champion's bomb. */
            void setStrenght(float);
        protected:
        private:
            /*! The enum of all the direction of the champion. */
            enum direction {
                RIGHT_ANIM,
                LEFT_ANIM,
                UP_ANIM,
                DOWN_ANIM,
                NO_ANIM
            };
            /*! The name of the champion. */
            std::string _name;
            /*! The strenght of the champion's bomb. */
            int strenght = 1;
            /*! The range of the champion's bomb. */
            int range = 1;
            /*! The champion's speed. */
            float speed = 2.0f;
            /*! THe current direction of the player. */
            direction currentDirection = NO_ANIM;
            /*! The model of the champion. */
            ModelComponent _model;
            /*! The vector of all the bricks. */
            std::vector<Vector3> _Bricks;
            /*! The vector of all the placed bomb. */
            std::vector<Indie::BombComponent> _PlacableBomb;
            /*! The bomb of the champion. */
            Indie::BombComponent _bomb;
            /*! The procedural texture of the map. */
            Texture2D cubicmap;
            /*! The procedural color of the map. */
            Color *mapPixel;

    };
}

#endif /* !CHAMPION_HPP_ */
