/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** GetElements
*/

#include "Snake.hpp"

JSON::JSON Arcade::Snake::getHead()
{
    JSON::JSON head;
    JSON::JSONArray positions;
    JSON::JSONArray rectangle;

    JSON::JSON pos;

    pos._values["x"] = _positions[0].first;
    pos._values["y"] = _positions[0].second;
    positions._values.push_back(pos);

    rectangle._values = {0.0, 0.0, 30.0, 30.0};

    head._values["id"] = 2.0;
    head._values["type"] = 0.0;
    head._values["string"] = "8";
    head._values["rectangle"] = rectangle;
    head._values["position"] = positions;

    head._values["assets"] = _direction;

    return head;
}

JSON::JSON Arcade::Snake::getBody()
{
    JSON::JSON body;
    JSON::JSONArray positions;
    JSON::JSONArray rectangle;

    for (std::size_t i = 1; i < _positions.size(); i++) {
        JSON::JSON pos;

        pos._values["x"] = _positions[i].first;
        pos._values["y"] = _positions[i].second;
        positions._values.push_back(pos);
    }

    rectangle._values = {0.0, 0.0, 30.0, 30.0};

    body._values["id"] = 3.0;
    body._values["type"] = 0.0;
    body._values["string"] = "=";
    body._values["rectangle"] = rectangle;
    body._values["position"] = positions;
    body._values["assets"] = "Assets/Snake/body.png";

    return body;
}

JSON::JSON Arcade::Snake::getApple()
{
    JSON::JSON apple;
    JSON::JSONArray positions;
    JSON::JSONArray rectangle;

    JSON::JSON pos;

    pos._values["x"] = _apple.first;
    pos._values["y"] = _apple.second;
    positions._values.push_back(pos);

    rectangle._values = {0.0, 0.0, 30.0, 30.0};

    apple._values["id"] = 4.0;
    apple._values["type"] = 0.0;
    apple._values["string"] = ".";
    apple._values["rectangle"] = rectangle;
    apple._values["position"] = positions;

    apple._values["assets"] = "Assets/Snake/apple.png";

    return apple;
}

JSON::JSON Arcade::Snake::getScore()
{
    JSON::JSON score;
    JSON::JSONArray positions;
    JSON::JSONArray color;
    JSON::JSON pos;

    pos._values["x"] = 0.0;
    pos._values["y"] = -40.0;

    positions._values.push_back(pos);

    color._values = {1.0, 255.0, 255.0};

    score._values["type"] = 1.0;
    score._values["id"] = 5.0;
    score._values["content"] = "SCORE";
    score._values["value"] = _score;
    score._values["fontSize"] = 20.0;
    score._values["fontFamily"] = "Assets/Fonts/ARCADE_I.ttf";
    score._values["fontColor"] = color;
    score._values["position"] = positions;

    return score;
}

JSON::JSON Arcade::Snake::getTime()
{
    JSON::JSON time;
    JSON::JSONArray positions;
    JSON::JSONArray color;
    JSON::JSON pos;

    pos._values["x"] = 720.0;
    pos._values["y"] = -40.0;

    positions._values.push_back(pos);

    color._values = {1.0, 255.0, 255.0};

    time._values["type"] = 1.0;
    time._values["id"] = 6.0;
    time._values["content"] = "TIME";
    time._values["value"] = (double)((std::clock() - _globalClock) / CLOCKS_PER_SEC);
    time._values["fontSize"] = 20.0;
    time._values["fontFamily"] = "Assets/Fonts/ARCADE_I.ttf";
    time._values["fontColor"] = color;
    time._values["position"] = positions;

    return time;
}
