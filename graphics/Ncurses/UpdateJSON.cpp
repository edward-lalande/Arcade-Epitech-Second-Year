/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** UpdateJSON
*/

#include "Ncurses.hpp"

void Arcade::Ncurses::updateJSON(JSON::JSON data)
{
    JSON::JSONArray copy = _json.getELEMENTS;
    JSON::JSONArray elements = data.getELEMENTS;
    bool isPassed = false;

    for (std::size_t i = 0; i < 8; i++) {
        copy._values[i] = elements._values[i];
    }

    for (std::size_t i = 8; i < elements._values.size(); i++) {
        isPassed = false;
        for (std::size_t j = 8; j < copy._values.size(); j++) {
            if (elements.getINDEX(i).getID == copy.getINDEX(j).getID) {
                isPassed = true;
                copy._values[j] = elements.getINDEX(i);
                _cacheText.erase(elements.getINDEX(i).getID);
                break;
            }
        }
        if (!isPassed) {
            copy._values.push_back(elements.getINDEX(i));
        }
    }
    _json._values[ELEMENTS] = copy;
}
