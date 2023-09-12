/*
** EPITECH PROJECT, 2021
** B-YEP-400-NCY-4-1-indiestudio-jean.gauthier-damioli
** File description:
** Audio
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include "../ECS.hpp"
#include "ModelComponent.hpp"

namespace Indie {
    class Audio : public Component {
        public:
            Audio();
            ~Audio();

            static Indie::Audio& Instance()
            {
                static Indie::Audio currentAudio;

                return currentAudio;
            }

            void init() override;
            void update(double time) override;
            void draw() override;

            /*! Set the volume of a music or a sound. */
            void setVolume(float vol);

            /*! The function to launch the menu music. */
            void startPlayingMenuMusic();

            /*! The function to launch the game music. */
            void startPlayingGameMusic();

            /*! The function to launch the explosion sound. */
            void startPlayingExplosion();

            /*! The function to launch the death sound. */
            void startPlayingDeath();

            /*! The function to launch the powerup sound. */
            void startPlayingPowerUp();

            /*! The function to stop the menu music. */
            void stopPlayingMenuMusic();

            /*! The function to stop the game music. */
            void stopPlayingGameMusic();

            /*! Set the playing music. */
            void setState(int _state);

            /*! Get the current music playing. */
            int getState();
        protected:
        private:
            /*! Music are used to played music they are harder to 
            manipulate but have better quality and only used to be set looping
            at true for never stoping */
            Music _musicMenu;
            Music _musicGame;

            /*! Sound don't have to be updated they only need to be played
            which make them easier to use for multiple same sound at the same time */
            Sound _bomb;
            Sound _death;
            Sound _PowerUp;
            float _volume;
            int state = 0;
    };
}

#endif /* !AUDIO_HPP_ */
