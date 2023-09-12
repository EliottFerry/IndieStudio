/*
** EPITECH PROJECT, 2021
** Indie
** File description:
** Indie
*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <iostream>
#include <vector>
#include "raylib.h"
#include "Event.hpp"
#include "../ECS/Components/Audio.hpp"

namespace Indie
{
    /*! Class for window management */ 
    class Window {
        public:
            /*! Creating an instance, in order to prevent a multiple creation of the window */
            static Indie::Window& Instance()
            {
                static Indie::Window mainWindow;

                return mainWindow;
            }

            /*! Get the event of the runing window */
            Indie::Event getEvent(); 

            /*! Get the time difference */ 
            double getElapsedTime();

            /*! Returning the window size x and y in a 2 dimension vector */
            Vector2 getWindowSize();

            /*! Returning the current volume of the window. */
            int getWindowVolume();

            /*! Returning the current framerate limit of the window. */
            int getWindowFramerate();

            /*! Setting the window to fullscreen mode. */
            void setWindowFullScreen();

            /*! Modifying the window FPS + the modif variable.*/
            void setWindowFramerate(int modif);

            /*! Modifying the window volume + the modif variable. */
            void setWindowVolume(int modif);

            /*! Set the window resolution WIDTHxHEIGHT*/
            void setWindowResolution(int width, int height);

            /*! Check if the window is open */ 
            bool isOpen();
        protected:
        private:
            /*! The window creator, with basic parameters. If you don't put any parameters, the basics one will be used.
            If you want to change the basics values, you can call the constructor like this : Indie::Window window(1400, 1000, "Test 1.2.1.2")*/
            Window(int width = 1200, int height = 800, const std::string&& title = "Indie Studio 2021"); 
            Window(Window &);
            ~Window();
            Window& operator=(Window&&) = delete;
            Window& operator=(const Window&) = delete;
            
            /*! Event mangement of the window */
            Indie::Event eventHandler;
            
            /*! Variable to store main volume. */
            int _volume;

            /*! Variable to store current framerate limit. */
            int _framerateLimit;

            /*! Timer for the game */
            double _gameClock; 
    };
}

#endif /* !WINDOW */
