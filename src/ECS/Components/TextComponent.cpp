/*
** EPITECH PROJECT, 2021
** Text Component
** File description:
** FIle to implement all function of testComponent
*/

#include "TextComponent.hpp"
#include "rlgl.h"
#define RAYLIB_NEW_RLGL

Indie::TextComponent::TextComponent(std::string font, std::string text, Vector2 pos, float size, Color color) : _showLettersBoundry(false), _is3D(false), _drawable(true), _path(font)
{
    _font = ::LoadFontEx((exec_path + font).c_str(), size, 0, 250);
    _color = color;
    _fontSize = size;
    _position = pos;
    _text = text;
    _active = true;
    _alpha = 1;
}

Indie::TextComponent::TextComponent(std::string font, std::string text, Vector3 pos, Vector3 rotateText, float size, Color color) : _showLettersBoundry(false), _is3D(true), _drawable(true), _path(font)
{
    _font = ::LoadFontEx((exec_path + font).c_str(), size, 0, 250);
    _color = color;
    _fontSize = size;
    _position3D = pos;
    _text = text;
    _active = true;
    _alpha = 1;
    _rotateText = rotateText;
}

Vector2 Indie::TextComponent::mesureText()
{
    UnloadFont(_font);
    _font = ::LoadFontEx((exec_path + _path).c_str(), _fontSize, 0, 250);
    Image tmp = ::ImageTextEx(_font, _text.c_str(), _fontSize, 0, _color);
    Vector2 sizeText = { (float)tmp.width, (float)tmp.height };
    return sizeText;
}

void Indie::TextComponent::DrawTextCodepoint3D(Font font, int codepoint, Vector3 position, float fontSize, bool backface, Color tint)
{
    int index = ::GetGlyphIndex(font, codepoint);
    float scale = fontSize/(float)font.baseSize;

    position.x += (float)(font.chars[index].offsetX - font.charsPadding)/(float)font.baseSize*scale;
    position.z += (float)(font.chars[index].offsetY - font.charsPadding)/(float)font.baseSize*scale;

    Rectangle srcRec = { font.recs[index].x - (float)font.charsPadding, font.recs[index].y - (float)font.charsPadding,
                         font.recs[index].width + 2.0f*font.charsPadding, font.recs[index].height + 2.0f*font.charsPadding };

    float width = (float)(font.recs[index].width + 2.0f*font.charsPadding)/(float)font.baseSize*scale;
    float height = (float)(font.recs[index].height + 2.0f*font.charsPadding)/(float)font.baseSize*scale;
    Vector3 tmp;
    Vector3 tmp2;

    if(font.texture.id > 0)
    {
        const float x = 0.0f;
        const float y = 0.0f;
        const float z = 0.0f;

        const float tx = srcRec.x/font.texture.width;
        const float ty = srcRec.y/font.texture.height;
        const float tw = (srcRec.x+srcRec.width)/font.texture.width;
        const float th = (srcRec.y+srcRec.height)/font.texture.height;

        if (_showLettersBoundry) {
            tmp = { position.x + width / 2, position.y, position.z + height / 2 };
            tmp2 = { width, LETTER_BOUNDRY_SIZE, height };
            ::DrawCubeWiresV(tmp, tmp2, LETTER_BOUNDRY_COLOR);
        }

        #if defined(RAYLIB_NEW_RLGL)
            rlCheckRenderBatchLimit(4 + 4*backface);
            rlSetTexture(font.texture.id);
        #else
            if (rlCheckBufferLimit(4 + 4*backface)) rlglDraw();
            rlEnableTexture(font.texture.id);
        #endif
            rlPushMatrix();
                rlTranslatef(position.x, position.y, position.z);

                rlBegin(RL_QUADS);
                    rlColor4ub(tint.r, tint.g, tint.b, tint.a);

                    rlNormal3f(0.0f, 1.0f, 0.0f);
                    rlTexCoord2f(tx, ty); rlVertex3f(x, y, z);
                    rlTexCoord2f(tx, th); rlVertex3f(x, y, z + height);
                    rlTexCoord2f(tw, th); rlVertex3f(x + width, y, z + height);
                    rlTexCoord2f(tw, ty); rlVertex3f(x + width, y, z);

                    if (backface)
                    {
                        rlNormal3f(0.0f, -1.0f, 0.0f);
                        rlTexCoord2f(tx, ty); rlVertex3f(x, y, z);
                        rlTexCoord2f(tw, ty); rlVertex3f(x + width, y, z);
                        rlTexCoord2f(tw, th); rlVertex3f(x + width, y, z + height);
                        rlTexCoord2f(tx, th); rlVertex3f(x, y, z + height);
                    }
                rlEnd();
            rlPopMatrix();

        #if defined(RAYLIB_NEW_RLGL)
                rlSetTexture(0);
        #else
                rlDisableTexture();
        #endif
    }
}

void Indie::TextComponent::DrawText3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, Color tint)
{
    int length = ::TextLength(text);

    float textOffsetY = 0.0f;
    float textOffsetX = 0.0f;

    float scale = fontSize/(float)font.baseSize;
    Vector3 tmp;

    for (int i = 0; i < length;)
    {
        int codepointByteCount = 0;
        int codepoint = ::GetCodepoint(&text[i], &codepointByteCount);
        int index = ::GetGlyphIndex(font, codepoint);

        if (codepoint == 0x3f)
            codepointByteCount = 1;

        if (codepoint == '\n')
        {
            textOffsetY += scale + lineSpacing/(float)font.baseSize*scale;
            textOffsetX = 0.0f;
        }
        else
        {
            if ((codepoint != ' ') && (codepoint != '\t'))
            {
                tmp = { position.x + textOffsetX, position.y, position.z + textOffsetY };
                DrawTextCodepoint3D(font, codepoint, tmp, fontSize, backface, tint);
            }
            if (font.chars[index].advanceX == 0) textOffsetX += (float)(font.recs[index].width + fontSpacing)/(float)font.baseSize*scale;
            else textOffsetX += (float)(font.chars[index].advanceX + fontSpacing)/(float)font.baseSize*scale;
        }

        i += codepointByteCount;
    }
}

float Indie::TextComponent::getAlpha()
{
    return _alpha;
}

Vector3 Indie::TextComponent::MeasureText3D(Font font, const char* text, float fontSize, float fontSpacing, float lineSpacing)
{
    int len = ::TextLength(text);
    int tempLen = 0;
    int lenCounter = 0;

    float tempTextWidth = 0.0f;

    float scale = fontSize/(float)font.baseSize;
    float textHeight = scale;
    float textWidth = 0.0f;

    int letter = 0;
    int index = 0;

    for (int i = 0; i < len; i++)
    {
        lenCounter++;

        int next = 0;
        letter = ::GetCodepoint(&text[i], &next);
        index = ::GetGlyphIndex(font, letter);

        if (letter == 0x3f)
            next = 1;
        i += next - 1;

        if (letter != '\n')
        {
            if (font.chars[index].advanceX != 0)
                textWidth += (font.chars[index].advanceX+fontSpacing)/(float)font.baseSize*scale;
            else
                textWidth += (font.recs[index].width + font.chars[index].offsetX)/(float)font.baseSize*scale;
        }
        else
        {
            if (tempTextWidth < textWidth) tempTextWidth = textWidth;
            lenCounter = 0;
            textWidth = 0.0f;
            textHeight += scale + lineSpacing/(float)font.baseSize*scale;
        }

        if (tempLen < lenCounter)
            tempLen = lenCounter;
    }

    if (tempTextWidth < textWidth)
        tempTextWidth = textWidth;

    Vector3 vec = { 0 };
    vec.x = tempTextWidth + (float)((tempLen - 1)*fontSpacing/(float)font.baseSize*scale);
    vec.y = 0.25f;
    vec.z = textHeight;

    return vec;
}

void Indie::TextComponent::setInactive()
{
    _active = false;
}

void Indie::TextComponent::update(double time)
{
    if (!_active) {
        _alpha -= 0.01;
        _color = ::Fade(_color, _alpha);
        if (_alpha <= 0.0f) {
            this->entity->destroy();
        }
    }
    else
        if (_alpha < 1) {
            _alpha += 0.01;
            _color = ::Fade(_color, _alpha);
        }
}

void Indie::TextComponent::setAlpha(float alpha)
{
    _alpha = alpha;
}

void Indie::TextComponent::setColor(Color color)
{
    _color = color;
}

void Indie::TextComponent::draw()
{
    if (_is3D && _drawable) {
        ::rlPushMatrix();
        if (_text != "Start the game" && _text != "No player has won, time is up" && (_text.find(" !") == 0 || _text.find(" !") > _text.size()) && (_text.find(" : ") < 0 || _text.find(" : ") > _text.size()))
            rlRotatef(90.0, 1.0f, 0.0f, 0.0f);
        if (_text == "Settings" || _text == "Exit")
            rlRotatef(50, 0.0f, 0.0f, 1.0f);
        if (_text == "Play" || _text == "New game" || _text == "Load game")
            rlRotatef(145, 0.0f, 0.0f, 1.0f);
        Vector3 m = MeasureText3D(_font, _text.c_str(), _fontSize, 1.0f, -1.0f);
        Vector3 pos = { -m.x/1.5f, 0.0f, -2.0f};
        DrawText3D(_font, _text.c_str(), _position3D, _fontSize, 1.0f, 0.0f, false, _color);
        ::rlPopMatrix();
    }
    else if (_drawable)
        DrawTextEx(_font, _text.c_str(), _position, _fontSize, 0, _color);
}

void Indie::TextComponent::setText(std::string newText)
{
    _text = newText;
}

void Indie::TextComponent::setPosition(Vector2 newPos)
{
    _position = newPos;
}

void Indie::TextComponent::setPosition3D(Vector3 newPos)
{
    _position3D = newPos;
}

void Indie::TextComponent::setSize(float newSize)
{
    _fontSize = newSize;
}

void Indie::TextComponent::setDrawable(bool drawable)
{
    _drawable = drawable;
}

void Indie::TextComponent::mustDraw()
{
    if (_drawable == false)
        _drawable = true;
    else
        _drawable = false;
}

Indie::TextComponent::~TextComponent()
{
    ::UnloadFont(_font);
}

Font Indie::TextComponent::getFont()
{
    return _font;
}