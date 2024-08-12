/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** SFML
*/

#include "SFML.hpp"

extern "C" Arcade::IGraphicLibrary *createLibrary()
{
    return new Arcade::SFML;
}

extern "C" bool isGame()
{
    return false;
}

Arcade::SFML::SFML()
{
    _window.create(sf::VideoMode(1920, 1080), "Arcade SFML");
    _login = createScore("");
}

Arcade::SFML::~SFML()
{
    _window.close();
}
