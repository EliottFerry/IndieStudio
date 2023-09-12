/*
** EPITECH PROJECT, 2021
** B-YEP-400-NCY-4-1-indiestudio-jean.gauthier-damioli
** File description:
** AI
*/

#ifndef AI_HPP_
#define AI_HPP_

#include "../ECS.hpp"
#include "ModelComponent.hpp"
#include "Player.hpp"
#include "Champion.hpp"
#include <cstdlib>
#include <ctime>

namespace Indie {
    class BombermanAI : public Component {
        public:
            BombermanAI();
            ~BombermanAI();
            /*! Initialize the value for the bot */
            void init() override;
            /*! Update the bot and start its creation */
            void update(double time) override;
            /*! Draw the bot */
            void draw() override;
            /*! Set the difficulty of the bot */
            void setDifficulty(int difficulty);
            /*! Bot register the map for colision */
            void setMap(std::string mapPath);
            /*! Parameter to set the position */
            void setPosition(Vector3 Position);
            /*! get the position of all the bomb planted by the IA */
            std::vector<Vector3> getBombPosition();
            /*! check bomb colision with explosion */
            void makeExplodeBomb(Vector3 _bomb);
            /*! Get all the explosion my by the bomb planted by the bot */
            std::vector<Vector3> GetExploZone();
            /*! Set player colision with the breakable wall */
            void setPlayerColision(std::string _PathToMap);
            void setBrickWall(std::vector<Vector3> _posWall);
            void setBricksPosition(std::vector<Vector3> _posWall);
            /*! after a certain time destroy the model */
            bool destroy_after_death();
            void CreateChamp(std::string champ);
            /*! calculate the expected explosion of all the bomb */
            void AddEspectedExlosion(std::vector<std::vector<Vector3>> _bomb, std::vector<std::pair<int, int>> _stat);
            /*! add the current explosion */
            void AddCurrentExplosion(std::vector<std::vector<Vector3>> explo);
            void setPlayerToFocus(Vector3 _pos);
            /*! get the position of all the player and decide wich one to focus */
            void getPositionOfOtherPlayer(std::vector<Vector3> positionPlayer);
            Vector3 getPosition();
            /*! kill the AI */
            void isDead();
            /*! check if the ai is alive */
            bool isAlive();
            std::string getChamp();
            /*! cleanup everything */
            void clearAI();
            /*! recolt a power up and add it to the stat */
            void addPowerUp(std::string _name);
            /*! get the strenght and the range */
            std::pair<int, int> getCapacity();
            
            /*! Set if the AI is alive. */
            void setActive();
            /*! Set the stats of the AI. */
            void setStats(float, float, float, float);

            /*! Get the stat of the AI. */
            std::vector<float> getStats();

            /*! Set the name of the AI. */
            void setName(std::string name);

            /*! Get the name of the AI. */
            std::string getPName();

            /*! Get some more stats. */
            std::vector<float> getBigBrainStats();
        protected:
        private:
            /*! Check if a tile is in danger stats. return true if she is. */
            bool CheckTileDanger(Vector3 _pos);

            /*! The algortithme for the AI. */
            void Algorithm();

            /*! The function for the AI to plant a bomb. */
            void plantBomb();

            /*! Set the state to offensiv for the AI. */
            bool offensiveState();

            /*! Set the state to defensive for the AI. */
            void defensiveState();

            /*! Move the AI to the next tile. */
            void move_next_point();

            /*! Change path if the AI is stuck. */
            void Unstuck();

            /*! Move trought angle. */
            bool CheckAllAngle(Vector2);

            /*! The function to attack the player. */
            void attackPlayer();
            /*! The different state of the AI. */
            enum StateAI {
                DEFENSIVE_STATE,
                OFFENSIVE_STATE,
                UNBLOCK_STATE,
                NO_STATE
            };
            /*! All the direction of the AI. */
            enum CurrentDirection {
                RIGHT_STATE,
                LEFT_STATE,
                UP_STATE,
                DOWN_STATE,
                NO_DIRECTION
            };
            /*! The current direction of the AI. */
            CurrentDirection directionBot = NO_DIRECTION;
            /*! The current state of the AI. */
            StateAI currentMovement = NO_STATE;
            /*! The difficulty of the AI. */
            int difficulty = 1;
            /*! The pos of the player. */
            Vector3 _playerPos;
            /*! The pos of the champion. */
            Vector3 _champPos;
            /*! The name of the AI*/
            std::string _Currentname;
            /*! The time passed. */
            double _time;
            /*!  */
            bool focusAxis = true;
            /*! Is the AI active. */
            bool active = false;
            /*! A vector of the position of all the other players. */
            std::vector<Vector3> _OtherPlayerPosition;
            /*! A vector of the position of the dangerous tiles. */
            std::vector<Vector3> _dangerousTile;
            /*! A vector of the expected position of the explosion. */
            std::vector<Vector3> _posExpectedExplosion;
            /*! A vector of the position of the active explosion. */
            std::vector<Vector3> _currentExplosion;
            /*!  */
            std::vector<Vector3> _point;
            /*! The body of the AI. */
            Indie::Champion _body;
            /*! The time to put the next bomb. */
            float time_bomb = 0.0f;
            /*! The time between all bomb. */
            float next_bomb = 6.0f;
            /*! Is the AI alive. */
            bool alive = true;
            /*! Number of bomb the AI can throw. */
            int bomb_nbr = 1;
            /*! Number of the maximum bomb that can be putted down. */
            int max_bomb = 1;
            /*! The strenght of the bomb. */
            int strenght = 1;
            /*! The range of the bomb. */
            int range = 1;
            /*! The name of the AI. */
            std::string _champ;
    };
}

#endif /* !AI_HPP_ */
