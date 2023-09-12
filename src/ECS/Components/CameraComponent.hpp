/*
** EPITECH PROJECT, 2021
** CameraComponent
** File description:
** The file to create the component Camera
*/

#ifndef CAMERACOMPONENT_HPP
#define CAMERACOMPONENT_HPP

#include "../ECS.hpp"
#include "raylib.h"
#include "../Components.hpp"

namespace Indie {
    class CameraComponent : public Component {
        public:
            CameraComponent() = default;
            ~CameraComponent();

            /*! Initialization of the value of the camera */
            void init() override;

            /*! Set the field of view */
            void SetFovy(float fov);

            /*! Set the up axis of the camera */
            void SetUpVector(Vector3 up);

            /*! Were the camera will look */
            void SetTarget(Vector3 target);

            /*! Set a path to the camera */
            void SetPathCamera(std::vector<Vector3> Path);

            /*! Add new point to the path */
            void AddPathPoint(Vector3 PointTarget, Vector3 PointUp, Vector3 PointPos, Vector3 SetStrenght);

            /*! Advance in the set path if it is not empty */
            bool AdvanceInPath();

            /*! Get the current camera */
            Camera3D getCurrentCam();

            /*! Update the camera to the new position */
            void update(double time) override;

            /*! Start the 3D with the camera */
            void Begin3DCameraMod();

            /*! Set the position of the camera */
            void SetCameraPosition(Vector3 _pos);

            /*! Init everything for the camera */
            void SetEverythingCamera(Vector3 WTarget, Vector3 Wup, Vector3 Wpos);
        protected:
        private:
            /*! Current cam var */
            Camera3D cam = { 0 };
            /*! The differents points the camera will follow by calling AdvanceInPath, 
                The camera will use PathToFollow PathUp PathTarget to know the exact direction
                you want it to take, also the vector Strenght is use to advance at different
                speed */
            std::vector<Vector3> PathToFollow;
            std::vector<Vector3> PathUp;
            std::vector<Vector3> PathTarget;
            std::vector<Vector3> Strenght;
    };
}

#endif /* !CAMERACOMPONENT_HPP */
