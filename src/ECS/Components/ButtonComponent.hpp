/*
** EPITECH PROJECT, 2021
** ButtonComponent
** File description:
** The file to implement a button component
*/

#ifndef BUTTONCOMPONENT_HPP
#define BUTTONCOMPONENT_HPP

#include "../ECS.hpp"
#include "../Components.hpp"
#include "raylib.h"
#include <functional>

namespace Indie {
    class ButtonComponent : public Component {
        public:
            /*! The constructor for the button component which take as parameters:
                -x : The size of the button, and the hitbox on x axis.
                -y : The size of the button, and the hitbox on the y axis.
                -pos : The position of the button on the window.
                -drawable : If you want to draw the button. Set it to false if you just want his hitbox.
                -function: The pointer to the function called when the button is pressed.
                -border: Activate of deactivate the border of the button. */
            ButtonComponent(float x, float y, Vector2 pos, bool drawable, std::function<void()> function, bool border);
            /*! The function to update the button. */
            void update(double time) override;
            /*! The function to draw the button. */
            void draw() override;
            /*! This function set the current button to the selected state. */
            void setSelected(bool selected);
            /*! Return the selected state of the button. */
            bool isSelected();
            /*! Function to see if the button is overed by the mouse. */
            void checkOvered();
            /*! Return the overed state of the button. */
            bool isOvered();
            /*! Set a new size for the button. */
            void resizeButton(float x, float y, Vector2 pos);
            ~ButtonComponent();

        protected:
        private:
            /*! The rectangle to create the hitbox of the button. */
            Rectangle _buttonBound;
            /*! The vector who store the position of the button. */
            Vector2 _posButton;
            /*! The boolean to know if the button will draw himself. */
            bool _drawable;
            /*! The boolean to check if the button as been pressed. */
            bool _doAction;
            /*! The boolean to see if the button is selected. */
            bool _isSelected;
            /*! The boolean to see if the button as been overed. */
            bool _isOvered;
            /*! The color of the button. */
            Color _color;
            /*! The function called when the button as been pressed. */
            std::function<void()> _action;
            /*! The rect to create the border of the button. */
            Rectangle _Rec;
            /*! The boolean to know if we are drawing the border */
            bool _Border;
    };
}

#endif /* !BUTTONCOMPONENT_HPP */
