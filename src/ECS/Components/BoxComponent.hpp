/*
** EPITECH PROJECT, 2021
** BoxComponent
** File description:
** The file to implement a box component
*/

#ifndef BOXCOMPONENT_HPP
#define BOXCOMPONENT_HPP

#include "../ECS.hpp"
#include "../Components.hpp"
#include "raylib.h"
#include <functional>
namespace Indie {
    class BoxComponent : public Component {
    public:
        /*! The constructor for the box component which take as parameters:
            -x : The size of the box, and the hitbox on x axis.
            -y : The size of the box, and the hitbox on the y axis.
            -pos : The position of the box on the window.
            -drawable : If you want to draw the box. Set it to false if you just want his hitbox.
            -function: The pointer to the function called when the box is pressed.
            -border: Activate of deactivate the border of the box. */
        BoxComponent(float a, float b, float c, float d);
        /*! The function to update the box. */
        void update(double time) override;
        /*! The function to draw the box. */
        void draw() override;
        void mustDraw();
        Vector2 getPosition();
        bool isDrawn();
        /*! This function set the current box to the selected state. */
        void setSelected(bool selected);
        /*! Return the selected state of the box. */
        bool isSelected();
        /*! Function to see if the box is overed by the mouse. */
        void checkOvered();
        /*! Return the overed state of the box. */
        bool isOvered();
        /*! Set a new size for the box. */
        void resizeBox(float x, float y, Vector2 pos);
        ~BoxComponent();
        char getChar(void);
    protected:
    private:
        /*! The rectangle to create the hitbox of the box. */
        Rectangle _BoxBound;

        /*! The rectangle to create the hitbox of the box. */
        Rectangle textbox;
        /*! The vector who store the position of the box. */
        Vector2 _posBox;
        /*! The boolean to know if the box will draw himself. */
        bool _drawable;
        /*! The boolean to check if the box as been pressed. */
        bool _doAction;
        /*! The boolean to see if the box is selected. */
        bool _isSelected;
        /*! The boolean to see if the box as been overed. */
        bool _isOvered;
        /*! The color of the box. */
        Color _color;
        /*! The function called when the box as been pressed. */
        std::function<void()> _action;
        /*! The rect to create the border of the box. */
        Rectangle _Rec;
        /*! The boolean to know if we are drawing the border */
        bool _Border;
    };
}

#endif /* !boxCOMPONENT_HPP */
