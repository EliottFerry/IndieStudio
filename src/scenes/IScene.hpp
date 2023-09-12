/*
** EPITECH PROJECT, 2021
** IScene.hpp
** File description:
** IScene.hpp
*/

#ifndef IScene_HPP
#define IScene_HPP

#include <string>

namespace Indie {

    class IScene {
        public:
            virtual ~IScene() = default;
            virtual bool update(double _Time) = 0;
            virtual void draw() = 0;
        protected:
        private:

    };

};

#endif /* !IScene_HPP */
