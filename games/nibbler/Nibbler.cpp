/*
** EPITECH PROJECT, 2024
** Nibbler Game
** File description:
** Init and run for Nibbler in Arcade Proj
*/

#include "Nibbler.hpp"
#include <ctime>

JSON::JSON Arcade::Nibbler::refresh()
{
    return _data;
}

extern "C" Arcade::IGameLibrary *createLibrary()
{
    return new Arcade::Nibbler;
}

extern "C" bool isGame()
{
    return true;
}
