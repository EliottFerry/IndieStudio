/*
** EPITECH PROJECT, 2021
** Event
** File description:
** The .hpp file to handle the event class
*/

#ifndef EVENT_HPP
#define EVENT_HPP

#include "raylib.h"
#include <string>
#include <map>

namespace Indie
{
    /*! Class for event management */ 
    class Event {
        private:
            std::map<std::string, int> mapInputs {
                 { "Up", Indie::Event::Inputs::UP_ARROW },
                 { "Down", Indie::Event::Inputs::DOWN_ARROW },
                 { "Left", Indie::Event::Inputs::LEFT_ARROW },
                 { "Right", Indie::Event::Inputs::RIGHT_ARROW },
                 { "Action", Indie::Event::Inputs::SPACEBAR }
            };
        public:
            Event();
            ~Event();

            /*! Create a instance of the event. */
            static Indie::Event &Instance()
            {
                static Indie::Event event;

                return event;
            }
            /*! Close the running window */ 
            void closeMainWindow();

            /*! Get the mapping of the inputs. */
            std::map<std::string, int> getMapInputs();

            /*! Set an input in the map. */
            void setInputs(std::string pos, int input);

            /*! The enumeration to store all events */
            enum Inputs {
                NO_INPUTS,
                SPACEBAR = 32,
                ACCENT_U = 39,
                SEMI_COLUMN = 44,
                CLOSE_PARENTHESES,
                COLUMN,
                EXCLAMATION,
                A_ACCENT,
                AND,
                E_AIGU,
                DOUBLE_QUOTE,
                QUOTE,
                OPEN_PARENTHESES,
                MINUS,
                E_GRAVE,
                UNDERSCORE,
                C_CEDILLE,
                M = 59,
                EQUAL = 61,
                Q = 65,
                B,
                C,
                D,
                E,
                F,
                G,
                H,
                I,
                J,
                K,
                L,
                COMMA,
                N,
                O,
                P,
                A,
                R,
                S,
                T,
                U,
                V,
                Z,
                X,
                Y,
                W,
                STAR = 92,
                DOLLAR,
                SQUARE = 96,
                RETURN = 257,
                TAB,
                RIGHT_ARROW = 262,
                LEFT_ARROW,
                DOWN_ARROW,
                UP_ARROW,
                VERR_MAJ = 280,
                F1 = 290,
                F2,
                F3,
                F4,
                F5,
                F6,
                F7,
                F8,
                F9,
                F10,
                F11,
                SHIFT = 340,
                CONTROL,
                ALT,
                CIRCUMFLEX = 346
            };
    };
}

#endif /* !EVENT_HPP */
