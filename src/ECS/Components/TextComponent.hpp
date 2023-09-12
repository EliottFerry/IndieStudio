/*
** EPITECH PROJECT, 2021
** TextComponent
** File description:
** File to handle the function for the textComponent
*/

#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP

#include <string>
#include "raylib.h"
#include "../Components.hpp"

#define LETTER_BOUNDRY_SIZE     0.25f
#define TEXT_MAX_LAYERS         32
#define LETTER_BOUNDRY_COLOR    VIOLET

namespace Indie {

    class TextComponent : public Component {
        public:
            /*! Constructor for a 2Dtext component which take as parameters, the path to the font, the text you want to draw, the size of the font, and the color of the text.*/
            TextComponent(std::string font, std::string text, Vector2 pos, float size, Color color);
            /*! Constructor for a 3Dtext component which take as parameters, the path to the font, the text you want to draw, The position in the 3D world, the rotate of the text, the size of the font, and the color of the text.*/
            TextComponent(std::string font, std::string text, Vector3 pos, Vector3 rotateText, float size, Color color);
            ~TextComponent();
            /*! Set the color of the text to be draw. */
            void mustDraw();
            /*! Update the text if he is inactive. */
            void update(double time) override;
            /*! Draw the text at the postition asked. */
            void draw() override;
            /*! Set the text to inactive state, which make him to fade out, then he get destroyed. */
            void setInactive();
            /*! Set the color of the text to be draw. */
            void setColor(Color color);
            /*! Change the text */
            void setText(std::string newText);
            /*! Change position of the text */
            void setPosition(Vector2 newPos);
            /*! Change size of the text */
            void setSize(float newSize);
            /*! Change position of the text in 3D */
            void setPosition3D(Vector3 newPos);
            /*! Set the alpha of the text. */
            void setAlpha(float alpha);
            /*! Return the width of the text.*/
            Vector2 mesureText();

            Font getFont();
            void setFont(Font _toSet);
            /*! Set the drawable state of the text. */
            void setDrawable(bool drawable);
            /*! Return the size of the 3D text.*/
            Vector3 MeasureText3D(Font font, const char* text, float fontSize, float fontSpacing, float lineSpacing);
            /*! Return the alpha of the text. */
            float getAlpha();
        protected:
        private:
            /*! Used function to draw text in 3D.*/
            void DrawTextCodepoint3D(Font font, int codepoint, Vector3 position, float fontSize, bool backface, Color tint);
            /*! Used function to draw text in 3D.*/
            void DrawText3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, Color tint);
            /*! Store the font of the text. */
            Font _font;
            /*! Store the text to print. */
            std::string _text;
            /*! Store the position to draw the text. */
            Vector2 _position;
            /*! Store the position to draw the text 3D. */
            Vector3 _position3D;
            /*! Set a size for the font. */
            float _fontSize;
            /*! Store the color to draw the text. */
            Color _color;
            /*! Current state of the text. */
            bool _active;
            /*! Current fading of the text. */
            float _alpha;
            /*! Draw letters boundry in 3D */
            bool _showLettersBoundry;
            /*! Is the text 3D */
            bool _is3D;
            /*! Rotate the text 3D */
            Vector3 _rotateText;
            /*! The path of the font. */
            std::string _path;
            /*! The state to draw the text. He won't be drawed if it's set to false. */
            bool _drawable;
    };
}

#endif /* !TEXTCOMPONENT_HPP */
