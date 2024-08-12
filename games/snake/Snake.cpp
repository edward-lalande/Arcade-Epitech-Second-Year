/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Snake
*/

#include "Snake.hpp"

extern "C" Arcade::IGameLibrary *createLibrary()
{
    std::cout << "Snake Loaded\n";
    return new Arcade::Snake;
}

extern "C" bool isGame()
{
    return true;
}

JSON::JSON Arcade::Snake::refresh()
{
    return _data;
}
