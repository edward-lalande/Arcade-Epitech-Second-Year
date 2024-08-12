/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** getEvents
*/

#include "Ncurses.hpp"

JSON::JSON Arcade::Ncurses::getEvents()
{
    JSON::JSON json;
    JSON::JSONArray keys;

    json._values["close"] = false;
    json._values["logout"] = false;
    json._values["graphic"] = "";
    json._values["game"] = "";

    int c = getch();

    if (_json._values.size() != 0 && _json.getELEMENTS._values.size() != 0) {
        JSON::JSONArray libs = _json.getELEMENTS.get<JSON::JSON>(0).get<JSON::JSONArray>("libs");

        for (std::size_t i = 0; libs._values.size() != 0 && i < 7 && i < libs._values.size(); i++) {
            if (c == 'a' + (int)i) {
                json._values["graphic"] = libs.get<std::string>(i);
            }
        }

    }

    if (_json._values.size() != 0 && _json.getELEMENTS._values.size() != 0) {
        JSON::JSONArray libs = _json.getELEMENTS.get<JSON::JSON>(1).get<JSON::JSONArray>("libs");

        for (std::size_t i = 0; libs._values.size() != 0 && i < 6 && i < libs._values.size(); i++) {
            if (c == 'h' + (int)i) {
                json._values["game"] = libs.get<std::string>(i);
            }
        }

    }

    if (c != ERR) {

        if (c == 65) {
            c = 73;
        }
        if (c == 66) {
            c = 74;
        }
        if (c == 67) {
            c = 72;
        }
        if (c == 68) {
            c = 71;
        }
        keys._values.push_back((double)c);

    }

    if (c == 'z') {
        json._values["close"] = true;
    }

    json._values["keys"] = keys;
    return json;
}
