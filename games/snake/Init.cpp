/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Init
*/

#include "Snake.hpp"

JSON::JSON Arcade::Snake::initWall() const
{
    JSON::JSON wall;
    JSON::JSONArray pos;
    JSON::JSONArray rectangle;

    pos.parseMap(SNAKE_PATH, '#');

    rectangle._values = {0.0, 0.0, 30.0, 30.0};

    wall._values["id"] = 1.0;
    wall._values["type"] = 0.0;
    wall._values["string"] = "#";
    wall._values["position"] = pos;
    wall._values["rectangle"] = rectangle;
    wall._values["assets"] = "Assets/Snake/wall.png";

    return wall;
}

JSON::JSON Arcade::Snake::initHead() const
{
    JSON::JSON head;
    JSON::JSONArray pos;
    JSON::JSONArray rectangle;

    pos.parseMap(SNAKE_PATH, '8');

    rectangle._values = {0.0, 0.0, 30.0, 30.0};

    head._values["id"] = 2.0;
    head._values["type"] = 0.0;
    head._values["string"] = "8";
    head._values["position"] = pos;
    head._values["rectangle"] = rectangle;
    head._values["assets"] = DIRECTION_RIGHT;

    return head;
}

JSON::JSON Arcade::Snake::initBody() const
{
    JSON::JSON body;
    JSON::JSONArray pos;
    JSON::JSONArray rectangle;

    pos.parseMap(SNAKE_PATH, '=');

    rectangle._values = {0.0, 0.0, 30.0, 30.0};

    body._values["id"] = 3.0;
    body._values["type"] = 0.0;
    body._values["string"] = "=";
    body._values["position"] = pos;
    body._values["rectangle"] = rectangle;
    body._values["assets"] = "Assets/Snake/body.png";

    return body;
}

JSON::JSON Arcade::Snake::initApple() const
{
    JSON::JSON apple;
    JSON::JSONArray pos;
    JSON::JSONArray rectangle;

    pos.parseMap(SNAKE_PATH, '.');

    rectangle._values = {0.0, 0.0, 30.0, 30.0};

    apple._values["id"] = 4.0;
    apple._values["type"] = 0.0;
    apple._values["string"] = "=";
    apple._values["position"] = pos;
    apple._values["rectangle"] = rectangle;
    apple._values["assets"] = "Assets/Snake/apple.png";

    return apple;
}

JSON::JSON Arcade::Snake::initScore() const
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
    score._values["value"] = 0.0;
    score._values["fontSize"] = 20.0;
    score._values["fontFamily"] = "Assets/Fonts/ARCADE_I.ttf";
    score._values["fontColor"] = color;
    score._values["position"] = positions;

    return score;
}

JSON::JSON Arcade::Snake::initTime() const
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
    time._values["value"] = 0.0;
    time._values["fontSize"] = 20.0;
    time._values["fontFamily"] = "Assets/Fonts/ARCADE_I.ttf";
    time._values["fontColor"] = color;
    time._values["position"] = positions;

    return time;
}

JSON::JSON Arcade::Snake::initBackground() const
{
    JSON::JSON background;
    JSON::JSONArray positions;
    JSON::JSONArray rectangle;
    JSON::JSON pos;

    pos._values["x"] = 0.0;
    pos._values["y"] = 0.0;

    positions._values.push_back(pos);

    rectangle._values = {0.0, 0.0, 1320.0, 600.0};

    background._values["id"] = 7.0;
    background._values["type"] = 0.0;
    background._values["string"] = "";
    background._values["position"] = positions;
    background._values["rectangle"] = rectangle;
    background._values["assets"] = "Assets/Snake/background.jpg";

    return background;
}

JSON::JSON Arcade::Snake::init()
{
    JSON::JSONArray array;

    array._values.push_back(initBackground());
    array._values.push_back(initWall());
    array._values.push_back(initHead());
    array._values.push_back(initBody());
    array._values.push_back(initApple());
    array._values.push_back(initScore());
    array._values.push_back(initTime());

    _data._values["elements"] = array;

    _positions.push_back({5.0, 2.0});
    _positions.push_back({4.0, 2.0});
    _positions.push_back({3.0, 2.0});

    _apple = {11.0, 5.0};

    _score = 0.0;

    _key = 0.0;
    _lastKey = 0.0;

    _clock = std::clock();
    _globalClock = std::clock();
    _direction = DIRECTION_RIGHT;

    return _data;
}

