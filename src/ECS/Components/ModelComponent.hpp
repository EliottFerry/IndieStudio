/*
** EPITECH PROJECT, 2021
** ModelComponent
** File description:
** The hpp file which contain the class ModelComponent
*/

#ifndef MODELCOMPONENT_HPP
#define MODELCOMPONENT_HPP

#include "../ECS.hpp"
#include "raylib.h"
#include "raymath.h"
#include <map>
#include "ChangePath.hpp"
extern std::string exec_path;
namespace Indie {
    class ModelComponent : public Component {
        public:
            ModelComponent();
            ModelComponent(std::string _name);
            ~ModelComponent();

            void update(double time) override;

            /*! To set the 3D model to the model variable. */
            void setModel(std::string);

            /*! To set the 3D model to the model variable. */
            void setModel(Model mod);

            /*! Go to the next frame of the animation */
            void Animated();

            void clearRam();
    
            /*! Set Position of the model */
            void SetPos(Vector3 Pos);

            /*! Set the texture to the model by using the path*/
            void setTexture(std::string, size_t = 0);

            /*! Set the texture to the model with already loaded texture. */
            void setTexture(Texture texture, size_t = 0);

            /*! Set animation using the given name */
            void AddAnimation(std::string _AnimationName, std::string _path);

            /*! Play the animation you give as an argument */
            void PlayAnimation(std::string);

            /*! Get the position of the model */
            Vector3 getPos();

            /*! set the rotation axis of the model */
            void SetRotationAxis(Vector3);

            /*! Set the animation by passing a loaded animation as parameter. */
            void setAnimation(std::map<std::string, ModelAnimation *>);

            /*! get The loaded animation in the model. */
            std::map<std::string, ModelAnimation *> getAnimation();

            /*! Get the rptation axis of the model */
            Vector3 GetRotationAxis();

            /*! Get the rotation angle of the model */
            void SetRotationAngle(float);

            /*! Get the rotation angle of the model */
            float GetRotationAngle();

            /*! Draw the model */
            void draw();

            /*! Set the scale of the model */
            void SetScale(Vector3);

            /*! Return the model stored in the component. */
            Model getModel();

            /*! Return the texture stored in the component. */
            Texture getTexture();

            /*! Set the shader to the model */
            void setShaderToModel(Shader _shader);

            /*! Get name of the model */
            std::string GetName();

            /*! Get the drawable state of the model. */
            bool getDrawable();

            /*! Get the scale of the model. */
            Vector3 getScale();

            /*! Init everything for a perfect model */
            void setEverything(std::string PathModel, Vector3 PositionModel, Vector3 RotationAxis, Vector3 WantedScale, float RotationAngle);

            /*! Do the transform to make the rotation of the model */
            void transformModel(Vector3 rotation);
            /*! Create new champ using the given string */
            ModelComponent CreateNewChamp(std::string WantedChamp);

            ModelComponent createNewPlayer(std::string iqm_base, std::string texture, std::string idle, std::string run, std::string death, Vector3 scale);

            void setDrawable(bool drawable);
        protected:
        private:
            /*! The texture of the model. */
            Texture2D texture;
            /*! The model */
            Model model;
            /*! All animation are stored in a map, you can use PlayAnimation
                and the string you put inside the map to use the animation you want */
            std::map<std::string, ModelAnimation *> _Animation;
            /*! The name of the current animation loaded */
            std::string CurrentAnimation = "NONE";
            /*! The counter to loop in the animation. */
            int animsCount = 0;
            /*! The counter of the frame of the animation. */
            int animFrameCounter = 0;
            /*! The position of the model. */
            Vector3 _position;
            /*! The rotation axis of the model. */
            Vector3 _RotAxis = { 0 };
            /*! The rotation angle of the model. */
            float _RotAng = 0.0f;
            size_t i = 0;
            /*! The scaling of the model. */
            Vector3 Scale = { 1.0f, 1.0f, 1.0f };
            /*! The name of the model. */
            std::string _name = "NONE";
            /*! The state of the model. If it's set to false, the model won't draw anymore. */
            bool _drawable;
            /*! Total time passed. */
            float _totalTime = 0.0f;
    };
}

#endif /* !MODELCOMPONENT_HPP */
