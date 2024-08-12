/*
** EPITECH PROJECT, 2024
** Init Nibbler Game
** File description:
** Load JsonClass in Arcade Proj
*/

#include "Nibbler.hpp"
#include <fstream>
#include <ctime>

void Arcade::Nibbler::loadWallPos()
{
    for (std::size_t t = 0; t < _cpyWall._values.size(); t++) {
        JSON::JSON tmp = _cpyWall.get<JSON::JSON>(t);
        _WallPos.push_back(std::make_pair(tmp.get<double>("x"), tmp.get<double>("y")));
    }
}

void Arcade::Nibbler::loadFruitPos()
{
    for (std::size_t t = 0; t < _cpyFruit._values.size(); t++) {
        JSON::JSON tmp = _cpyFruit.get<JSON::JSON>(t);
        _fruitsPos.push_back(std::make_pair(tmp.get<double>("x"), tmp.get<double>("y")));
    }
}
JSON::JSON Arcade::Nibbler::initWall()
{
    JSON::JSON info;
    JSON::JSONArray pos;
    JSON::JSONArray rectangle;

    const std::string wall ("Assets/Nibbler/NibblerWall.png");

    pos.parseMap(NIBBLER_PATH, '#');
    _cpyWall.parseMap(NIBBLER_PATH, '#');
    loadWallPos();
    rectangle._values.push_back(0.0);
    rectangle._values.push_back(0.0);
    rectangle._values.push_back(30.0);
    rectangle._values.push_back(30.0);

    info._values["type"] = 0.0;
    info._values["assets"] = wall;
    info._values["id"] = WALL_ID;
    info._values["rectangle"] = rectangle;
    info._values["string"] = std::string("#");
    info._values["position"] = pos;
    return info;
}

JSON::JSON Arcade::Nibbler::initHead()
{
    JSON::JSON info;
    JSON::JSONArray pos;
    JSON::JSONArray rectangle;
    const std::string head = "Assets/Nibbler/NibblerHeadR.png";

    pos.parseMap(NIBBLER_PATH, '8');
    _nibPos.push_back(std::make_pair(6.0, 17.0));
    _nibPos.push_back(std::make_pair(5.0, 17.0));
    _nibPos.push_back(std::make_pair(4.0, 17.0));
    _nibPos.push_back(std::make_pair(3.0, 17.0));
    rectangle._values.push_back(0.0);
    rectangle._values.push_back(0.0);
    rectangle._values.push_back(30.0);
    rectangle._values.push_back(30.0);

    info._values["type"] = 0.0;
    info._values["assets"] = head;
    info._values["id"] = HEAD_ID;
    info._values["rectangle"] = rectangle;
    info._values["string"] = std::string("8");
    info._values["position"] = pos;

    return info;
}

JSON::JSON Arcade::Nibbler::initBody()
{
    JSON::JSON info;
    JSON::JSONArray pos;
    JSON::JSONArray rectangle;
    const std::string body = "Assets/Nibbler/NibblerBody.png";

    pos.parseMap(NIBBLER_PATH, '=');

    rectangle._values.push_back(0.0);
    rectangle._values.push_back(0.0);
    rectangle._values.push_back(30.0);
    rectangle._values.push_back(30.0);

    info._values["type"] = 0.0;
    info._values["assets"] = body;
    info._values["id"] = BODY_ID;
    info._values["rectangle"] = rectangle;
    info._values["string"] = std::string("=");
    info._values["position"] = pos;
    return info;
}

JSON::JSON Arcade::Nibbler::initFruits()
{
    JSON::JSON info;
    JSON::JSONArray pos;
    JSON::JSONArray rectangle;
    const std::string fruit = "Assets/Nibbler/NibblerFruit.png";

    pos.parseMap(NIBBLER_PATH, '.');
    _cpyFruit.parseMap(NIBBLER_PATH, '.');
    loadFruitPos();
    rectangle._values.push_back(0.0);
    rectangle._values.push_back(0.0);
    rectangle._values.push_back(29.0);
    rectangle._values.push_back(29.0);

    info._values["type"] = 0.0;
    info._values["assets"] = fruit;
    info._values["id"] = FRUITS_ID;
    info._values["rectangle"] = rectangle;
    info._values["string"] = std::string(".");
    info._values["position"] = pos;

    return info;
}

JSON::JSON Arcade::Nibbler::initScore()
{
    JSON::JSON info;
    JSON::JSON position;
    JSON::JSONArray pos;
    _score = 0.0;

    position._values["x"] = 0.0;
    position._values["y"] = -40.0;

    pos._values.push_back(1.0);
    pos._values.push_back(255.0);
    pos._values.push_back(255.0);
    info._values["type"] = 1.0;
    info._values["id"] = SCORE_ID;
    info._values["content"] = "Score";
    info._values["value"] = _score;
    info._values["fontSize"] = 22.0;
    info._values["fontFamily"] = NIB_FONT;
    info._values["fontColor"] = pos;
    pos._values.clear();
    pos._values.push_back(position);
    info._values["position"] = pos;

    return info;
}

JSON::JSON Arcade::Nibbler::initTime() const
{
    JSON::JSON info;
    JSON::JSON position;
    JSON::JSONArray pos;

    position._values["x"] = 920.0;
    position._values["y"] = -40.0;

    pos._values.push_back(1.0);
    pos._values.push_back(255.0);
    pos._values.push_back(255.0);
    info._values["type"] = 1.0;
    info._values["id"] = TIME_ID;
    info._values["content"] = "Time";
    info._values["value"] = 1.0;
    info._values["fontSize"] = 22.0;
    info._values["fontFamily"] = NIB_FONT;
    info._values["fontColor"] = pos;
    pos._values.clear();
    pos._values.push_back(position);
    info._values["position"] = pos;

    return info;
}

JSON::JSON Arcade::Nibbler::initLevel() const
{
    JSON::JSON info;
    JSON::JSON position;
    JSON::JSONArray pos;

    position._values["x"] = 420.0;
    position._values["y"] = -40.0;

    pos._values.push_back(1.0);
    pos._values.push_back(255.0);
    pos._values.push_back(255.0);
    info._values["type"] = 1.0;
    info._values["id"] = LEVEL_ID;
    info._values["content"] = "Waves";
    info._values["value"] = 1.0;
    info._values["fontSize"] = 30.0;
    info._values["fontFamily"] = NIB_FONT;
    info._values["fontColor"] = pos;
    pos._values.clear();
    pos._values.push_back(position);
    info._values["position"] = pos;

    return info;
}


JSON::JSON Arcade::Nibbler::init()
{
    JSON::JSON info;
    JSON::JSONArray arr;

    _wavesEnd = false;

    _fruitsCount = 0;
    _speed = 80;
    _lastKey = RIGHT;
    _key = RIGHT;
    _waves = 1;

    _gameTime = std::clock();

    _clock = std::clock();

    arr._values.push_back(initWall());
    arr._values.push_back(initFruits());
    arr._values.push_back(initHead());
    arr._values.push_back(initBody());
    arr._values.push_back(initScore());
    arr._values.push_back(initTime());
    arr._values.push_back(initLevel());
    info._values["elements"] = arr;
    _data = info;
    return info;
}
