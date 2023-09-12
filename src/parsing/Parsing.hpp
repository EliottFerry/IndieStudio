/*
** EPITECH PROJECT, 2021
** Parsing
** File description:
** File to parse everything
*/

#ifndef PARSING_HPP
#define PARSING_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <filesystem>
#include "ChangePath.hpp"
extern std::string exec_path;

namespace Indie {
    class Parsing {
        public:
            // Parsing();
            Parsing(int test = 0);
            Parsing(Parsing &);
            ~Parsing();
            Parsing& operator=(Parsing &&) = delete;
            Parsing& operator=(const Parsing &) = delete;

            std::map<int, std::string> keyMap;
            static Indie::Parsing &Instance()
            {
                static Indie::Parsing parsing;

                return parsing;
            }
        protected:
        private:
            /*! Function do parse the key, and store them to the std::map called "keyMap"*/
            int ParseAllInputs();

            /*!  Function to split a string at a character, and store it in a std::vector*/
            std::vector<std::string> splitStr(std::string str, char separate);
    };
}

#endif /* !PARSING_HPP */
