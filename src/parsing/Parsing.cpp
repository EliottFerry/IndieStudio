/*
** EPITECH PROJECT, 2021
** Parsing
** File description:
** File to parse everything
*/

#include "Parsing.hpp"



std::vector<std::string> Indie::Parsing::splitStr(std::string str, char separate)
{
    size_t position = str.find(separate);
    size_t init = 0;
    std::vector<std::string> splitS;

    splitS.push_back(str.substr(init, position - init));
    init = position + 1;
    splitS.push_back(str.substr(init, position - init));
    return (splitS);
}

int Indie::Parsing::ParseAllInputs()
{
    std::ifstream keyFile;
    std::string line;
    std::vector<std::string> splitedString;
    int posMap = 0;

    keyFile.open(exec_path + ("config_files/key_config.txt"));
    if (keyFile.is_open()) {
        while (std::getline(keyFile, line)) {
            if (line.c_str()) {
                if (line.find('/') != 0) {
                    splitedString = splitStr(line, '/');
                    keyMap.insert(std::pair<int, std::string>(std::stoi(splitedString[0]), splitedString[1]));
                }
            }
            posMap++;
        }
        keyFile.close();
    }
    else
        throw std::runtime_error ("Could not open the configuration file.\n");
    return (0);
}

Indie::Parsing::Parsing(int test)
{
    ParseAllInputs();
}

Indie::Parsing::~Parsing()
{
}
