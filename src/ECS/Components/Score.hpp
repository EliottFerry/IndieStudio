/*
** EPITECH PROJECT, 2021
** B-YEP-400-NCY-4-1-indiestudio-jean.gauthier-damioli
** File description:
** Score
*/

#ifndef SCORE_HPP_
#define SCORE_HPP_

#include <string>
#include "raylib.h"
#include "../Components.hpp"

namespace Indie {
    class Score : public Component {
        public:
            Score(std::string _name);
            ~Score();
            std::string getName();
        protected:
        private:
            std::string _name;
    };
}

#endif /* !SCORE_HPP_ */