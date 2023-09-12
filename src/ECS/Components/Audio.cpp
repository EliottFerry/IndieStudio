/*
** EPITECH PROJECT, 2021
** B-YEP-400-NCY-4-1-indiestudio-jean.gauthier-damioli
** File description:
** Audio
*/

#include "Audio.hpp"

Indie::Audio::Audio()
{
    _musicMenu = LoadMusicStream((exec_path + "Assets/Audio/TavernMusic.mp3").c_str());
    _musicMenu.looping = true;
    _musicGame = LoadMusicStream((exec_path + "Assets/Audio/GameMusic.mp3").c_str());
    _musicGame.looping = true;
    _bomb = LoadSound((exec_path + "Assets/Audio/BombExplosion.wav").c_str());
    _death = LoadSound((exec_path + "Assets/Audio/DeathSound.wav").c_str());
    _PowerUp = LoadSound((exec_path + "Assets/Audio/PowerUp.wav").c_str());
}

Indie::Audio::~Audio()
{
    UnloadMusicStream(_musicMenu);
    UnloadMusicStream(_musicGame);
}

void Indie::Audio::init()
{

}

void Indie::Audio::update(double time)
{
}

void Indie::Audio::draw()
{
    if (state == 0)
        UpdateMusicStream(_musicMenu);
    if (state == 1)
        UpdateMusicStream(_musicGame);
}

void Indie::Audio::setVolume(float vol)
{
    SetMusicVolume(_musicMenu, vol);
    SetMusicVolume(_musicGame, vol);
    SetSoundVolume(_bomb, vol);
    SetSoundVolume(_death, vol);
    SetSoundVolume(_PowerUp, vol);
}

void Indie::Audio::startPlayingMenuMusic()
{
    PlayMusicStream(_musicMenu);
}

void Indie::Audio::startPlayingGameMusic()
{
    PlayMusicStream(_musicGame);
}

void Indie::Audio::stopPlayingMenuMusic()
{
    StopMusicStream(_musicMenu);
}

void Indie::Audio::stopPlayingGameMusic()
{
    StopMusicStream(_musicGame);
}

void Indie::Audio::startPlayingExplosion()
{
    PlaySoundMulti(_bomb);
}

void Indie::Audio::startPlayingDeath()
{
    PlaySoundMulti(_death);
}

void Indie::Audio::startPlayingPowerUp()
{
    PlaySoundMulti(_PowerUp);
}

void Indie::Audio::setState(int _state)
{
    state = _state;
}

int Indie::Audio::getState()
{
    return state;
}
