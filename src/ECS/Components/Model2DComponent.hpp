/*
** EPITECH PROJECT, 2021
** Model2DComponent
** File description:
** The hpp file which contain the class Model2DComponent
*/

#ifndef MODEL2DCOMPONENT_HPP
#define MODEL2DCOMPONENT_HPP

#include "../ECS.hpp"
#include "raylib.h"
#include <map>
#include "ChangePath.hpp"
extern std::string exec_path;
namespace Indie {
    class Model2DComponent : public Component {
    public:
        /*! Init everything for a perfect map model */
        Model2DComponent(std::string PathMap, std::string PathTexture);
        ~Model2DComponent();
        /*! Draw the model */
        void draw();
    protected:
    private:
        /*! The model. */
        Model model;
        /*! The position of the model. */
        Vector3 mapPosition;
    };
}

#endif /* !MODEL2DCOMPONENT_HPP */
