/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Main
*/

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include "Arcade.hpp"
#include "LinuxLoader.hpp"
#include "IGameLibrary.hpp"
#include <fstream>

static bool isEnvProblem(char **env)
{
    for (std::size_t i = 0; env[i] != NULL; ++i) {
        std::string index(env[i]);
        if (index.substr(0, index.find('=')) == "DISPLAY") {
            return false;
        }
    }
    return true;
}

int main(int ac, char **av, char **env)
{
    std::ifstream ifs;
    if (ac != NB_ARGS_REQUIRED) {
        std::cerr << "USAGE : ./arcade [path/to/shared_librairies.so]" << std::endl;
        return EXIT_WITH_ERROR;
    }

    ifs.open(av[PATH_TO_LIB]);
    if (!ifs.is_open()) {
        std::cerr << "Unable to open the file" << std::endl;
        return EXIT_WITH_ERROR;
    }

    if (isEnvProblem(env)) {
        std::cerr << "Reboot your PC please..." << std::endl;
        return EXIT_WITH_ERROR;
    }

    Arcade::Arcade arcade(av[PATH_TO_LIB]);

    return arcade.run();
}
