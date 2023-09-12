/*
** EPITECH PROJECT, 2021
** Indie
** File description:
** Indie
*/

#include "Window.hpp"

Indie::Window::Window(int width, int height, const std::string&& title) : _volume(50)
{
    if (::IsWindowReady()) {
        throw std::runtime_error("The window has already been created.");
        return;
    }
    ::InitWindow(GetScreenWidth(), GetScreenHeight(), title.c_str());
    if (!::IsWindowReady())
        throw std::runtime_error("The window has not been created.");
    _framerateLimit = 60;
    ::ToggleFullscreen();
    ::SetTargetFPS(_framerateLimit);
    ::SetExitKey(Indie::Event::F10);
    _gameClock = ::GetTime();
    InitAudioDevice();
}

double Indie::Window::getElapsedTime()
{
    double oldGameClock = _gameClock;

    _gameClock = ::GetTime();
    return _gameClock - oldGameClock;
}

bool Indie::Window::isOpen()
{
    return !::WindowShouldClose();
}

Indie::Event Indie::Window::getEvent()
{
    std::vector<int> allInputsOnFrame;
    static int frame = 0;
    double passedTime = 0;
    int test = 0;
    allInputsOnFrame.clear();
    return (eventHandler);
}

Vector2 Indie::Window::getWindowSize()
{
    Vector2 size = { (float)GetScreenWidth(), (float)GetScreenHeight() };
    return size;
}

int Indie::Window::getWindowFramerate()
{
    return _framerateLimit;
}

int Indie::Window::getWindowVolume()
{
    return _volume;
}

void Indie::Window::setWindowFramerate(int modif)
{
    _framerateLimit = modif;
    ::SetTargetFPS(_framerateLimit);
}

void Indie::Window::setWindowVolume(int modif)
{
    _volume += modif;
    if (_volume > 100)
        _volume = 100;
    if (_volume < 0)
        _volume = 0;
    Indie::Audio::Instance().setVolume(((float)Indie::Window::Instance().getWindowVolume() / 1000));
}

void Indie::Window::setWindowFullScreen()
{
    ::ToggleFullscreen();
}

void Indie::Window::setWindowResolution(int width, int height)
{
    ::SetWindowSize(width, height);
}

Indie::Window::~Window()
{
    CloseAudioDevice();
}
