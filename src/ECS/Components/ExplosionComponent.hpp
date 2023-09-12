/*
** EPITECH PROJECT, 2021
** ExplosionComponent
** File description:
** The file to handle the explosion, and destroy them when the animation end
*/

#ifndef EXPLOSIONCOMPONENT_HPP
#define EXPLOSIONCOMPONENT_HPP

#include "../Components.hpp"
#define NUM_FRAMES_PER_LINE 5
#define NUM_LINES 4

namespace Indie
{
    class ExplosionComponent : public Component{
        public:
            /*! The constructor of the explosion component. Take a string to the asset in parameters. */
            ExplosionComponent(std::string path);
            ~ExplosionComponent();
            /*! Init the component. */
            void init() override;
            /*! Update the component. */
            void update(double time) override;
            /*! Draw the component. */
            void draw() override;
            bool Usable();
        protected:
        private:
            /*! The texture of the component. */
            Texture2D explosion;
            /*! The width of the frame. */
            float frameWidth;
            /*! The height of the frame. */
            float frameHeight;
            /*! The number of the current frame in the image. */
            int currentFrame;
            /*! The number of the current line in the image. */
            int currentLine;
            /*! The rect to set the right texture of the image. */
            Rectangle frameRect;
            /*! The position of the explosion. */
            Vector2 position;
            /*! The current frame your at. */
            int frameCounter;
            /*! Set if the explosion is active or not. Destroy the entity when active = false. */
            bool active;
    };
}


#endif /* !EXPLOSIONCOMPONENT_HPP */
