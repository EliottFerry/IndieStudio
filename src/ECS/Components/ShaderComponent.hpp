/*
** EPITECH PROJECT, 2021
** B-YEP-400-NCY-4-1-indiestudio-jean.gauthier-damioli
** File description:
** ShaderComponent
*/

#ifndef SHADERCOMPONENT_HPP_
#define SHADERCOMPONENT_HPP_

#include "raylib.h"
#include "raymath.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB -> Not supported at this moment
    #define GLSL_VERSION            100
#endif

#include "../ECS.hpp"

namespace Indie {
    class ShaderComponent : public Component {
        public:
            ShaderComponent();
            ~ShaderComponent();

            /*! Load the shader using the given path */
            void SetShader(std::string _path);

            /*! Return the shader */
            Shader GetShader();

            /*! Draw the light */
            void draw();

            /*! Set Shader to the camera */
            void SetCameraShader(Vector3 cameraPosition, Vector3 cameraTarget);
        protected:
        private:
            Shader shader;
            int viewEyeLoc;
            int viewCenterLoc;
            int runTimeLoc;
            int resolutionLoc;
        };
}

#endif /* !SHADERCOMPONENT_HPP_ */
