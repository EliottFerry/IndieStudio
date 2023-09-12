/*
** EPITECH PROJECT, 2021
** TwoDComponent.hpp
** File description:
** TwoDComponent.hpp
*/

#ifndef TWODCOMPONENT_HPP
#define TWODCOMPONENT_HPP

#include "../ECS.hpp"
#include "raylib.h"
#include "../../encapsulation/Window.hpp"
#include "ChangePath.hpp"
extern std::string exec_path;

namespace Indie {

    class TwoDComponent : public Component {
        public:
            TwoDComponent(std::string PathImage, float sizeX, float sizeY, Vector2 pos);
            ~TwoDComponent();

            /*! Draw 2D picture */
            void draw() override;
            void setDrawable(bool drawable);

            /*! Set a new size. */
            void setSize(float x, float y);

            /*! Set a new position. */
            void setPos(Vector2 pos);

            /*! Update the component. */
            void update(double time) override;

            /*! Set the alpha for the image. */
            void setAlpha(int alpha);
            /*! Set the component to inactive state. */
            void setInactive();
            /*! Get the image created for the 2D Component. */
            Image getImage();
        protected:
        private:
            /*! The texture of the image. */
            Texture2D _Texture;
            /*! The position of the image. */
            Vector2 _Pos;
            /*! The image to be drawn. */
            Image _Background;
            /*! The state to draw the image. He won't be drawed if it's set to false. */
            bool _drawable;
            /*! The color to fade the image. */
            Color _color;
            /*! The state of the image. If it's set to false, the image will begin to fase out. */
            bool _active;
    };

};
#endif /* !TWODCOMPONENT_HPP */
