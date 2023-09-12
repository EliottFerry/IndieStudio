/*
** EPITECH PROJECT, 2021
** SceneManager.hpp
** File description:
** SceneManager.hpp
*/

#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <iostream>
#include <stack>
#include <memory>
#include <stdexcept>
#include "AScene.hpp"

namespace Indie {

    class SceneManager : public Indie::AScene {
        public:
            SceneManager();
            ~SceneManager() = default;

            template <typename Scene, typename ...Arg>
            void ScenePush(Arg&& ...values)
            {
                /*! Build a new scene */
                auto NewScene = std::make_unique<Scene>(*this, std::forward<Arg>(values)...);

                /*! Push the new scene in the stack */
                Scenes.push(std::move(NewScene));
            }
            void removeScene()
            {
                /*! check before remove if there is scene in the stack */
                if (Scenes.empty())
                    throw std::runtime_error("Deletion not possible");
                /*! Remove actual scene */
                Scenes.pop();
            }

            void removeNbScene(int nbLoop)
            {
                int i = 0;

                while (i < nbLoop) {
                    /*! check before remove if there is scene in the stack */
                    if (Scenes.empty())
                        throw std::runtime_error("Deletion not possible");
                    /*! Remove actual scene */
                    Scenes.pop();
                    i++;
                }
            }

            void clear()
            {
                while (!Scenes.empty())
                    Scenes.pop();
            }
            virtual bool update(double time) override;
            virtual void draw() override;

        protected:
        private:
            std::stack<std::unique_ptr<Indie::AScene>> Scenes; /*! Stock all scene */
    };

};

#endif /* !SceneManager_HPP */
