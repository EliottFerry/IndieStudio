/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** main.cpp
*/

#include "Core.hpp"
#include <filesystem>
#include "ChangePath.hpp"

std::string exec_path;

int main()
{
    try {
        changePath();
        auto _Core = std::make_unique<Indie::Core>();
        return _Core->start();
    } catch (const std::exception &e) {
        std::cerr << "Error : " << e.what() << std::endl;
        return 84;
    }
    return 0;
}