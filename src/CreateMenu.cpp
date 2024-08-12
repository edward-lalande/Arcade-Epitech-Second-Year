/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** CreateMenu
*/

#include "Arcade.hpp"
#include "CreateMenu.hpp"
#include "JSON.hpp"

void Arcade::Arcade::createMenu()
{
    JSON::JSONArray array;

    for (std::size_t i = 0; i < 3; i++) {
        array._values.push_back({});
    }

    for (std::size_t i = 0; i < menuElements.size(); i++) {
        array._values.push_back(menuElements[i]._json);
    }

    _data._values["elements"] = array;

    getGraphicLibs();
    getGames();
}
