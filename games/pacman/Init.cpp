/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Init
*/

#include "unistd.h"
#include "Pacman.hpp"

JSON::JSONArray Arcade::Pacman::initBaseRectangle() const
{
    JSON::JSONArray rectangle;

    rectangle._values.push_back(0.0);
    rectangle._values.push_back(0.0);
    rectangle._values.push_back(30.0);
    rectangle._values.push_back(30.0);

    return rectangle;
}

JSON::JSON Arcade::Pacman::initScore() const
{
    JSON::JSON info;
    JSON::JSON position;
    JSON::JSONArray pos;

    position._values["x"] = 1000.0;
    position._values["y"] = -1.0;
    pos._values.push_back(1.0);
    pos._values.push_back(255.0);
    pos._values.push_back(255.0);
    info._values["type"] = 1.0;
    info._values["id"] = SCORE_ID;
    info._values["content"] = "score";
    info._values["value"] = 0.0;
    info._values["fontSize"] = 22.0;
    info._values["fontFamily"] = "Assets/Fonts/ARCADE_I.ttf";
    info._values["fontColor"] = pos;
    pos._values.clear();
    pos._values.push_back(position);
    info._values["position"] = pos;

    return info;
}

JSON::JSON Arcade::Pacman::initLevel() const
{
    JSON::JSON info;
    JSON::JSON position;
    JSON::JSONArray pos;

    position._values["x"] = 0.0;
    position._values["y"] = -1.0;

    pos._values.push_back(1.0);
    pos._values.push_back(255.0);
    pos._values.push_back(255.0);
    info._values["type"] = 1.0;
    info._values["id"] = LEVEL_ID;
    info._values["content"] = "level";
    info._values["value"] = 1.0;
    info._values["fontSize"] = 22.0;
    info._values["fontFamily"] = "Assets/Fonts/ARCADE_I.ttf";
    info._values["fontColor"] = pos;
    pos._values.clear();
    pos._values.push_back(position);
    info._values["position"] = pos;

    return info;
}

JSON::JSON Arcade::Pacman::initTime() const
{
    JSON::JSON info;
    JSON::JSON position;
    JSON::JSONArray pos;

    position._values["x"] = 1000.0;
    position._values["y"] = 350.0;

    pos._values.push_back(1.0);
    pos._values.push_back(255.0);
    pos._values.push_back(255.0);
    info._values["type"] = 1.0;
    info._values["id"] = TIME_ID;
    info._values["content"] = "time";
    info._values["value"] = 0.0;
    info._values["fontSize"] = 30.0;
    info._values["fontFamily"] = "Assets/Fonts/ARCADE_I.ttf";
    info._values["fontColor"] = pos;
    pos._values.clear();
    pos._values.push_back(position);
    info._values["position"] = pos;

    return info;
}

JSON::JSON Arcade::Pacman::initWall() const
{
    JSON::JSON info;
    JSON::JSONArray pos;

    pos.parseMap(PACMAN_PATH, WALL_CHAR);

    info._values["type"] = 0.0;
    info._values["assets"] = std::string("Assets/Pacman/wall.png");
    info._values["id"] = WALL_ID;
    info._values["rectangle"] = initBaseRectangle();
    info._values["string"] = std::string("#");
    info._values["position"] = pos;

    return info;
}

JSON::JSON Arcade::Pacman::initPlayer() const
{
    JSON::JSON info;
    JSON::JSONArray pos;

    pos.parseMap(PACMAN_PATH, PACMAN_CHAR);

    info._values["type"] = 0.0;
    info._values["assets"] = std::string("Assets/Pacman/pacman.png");
    info._values["id"] = PLAYER_ID;
    info._values["rectangle"] = initBaseRectangle();
    info._values["string"] = std::string("G");
    info._values["position"] = pos;

    return info;
}

JSON::JSON Arcade::Pacman::initOrangeGhost() const
{
    JSON::JSON info;
    JSON::JSONArray pos;
    JSON::JSONArray destArray;

    pos.parseMap(PACMAN_PATH, ORANGE_GHOST_CHAR);

    info._values["type"] = 0.0;
    info._values["assets"] = std::string(ORANGE_GHOST_PATH);
    info._values["id"] = ORANGE_GHOST_ID;
    info._values["rectangle"] = initBaseRectangle();
    info._values["string"] = std::string("O");
    info._values["position"] = pos;

    return info;
}

JSON::JSON Arcade::Pacman::initPinkGhost() const
{
    JSON::JSON info;
    JSON::JSONArray pos;

    pos.parseMap(PACMAN_PATH, PINK_GHOST_CHAR);

    info._values["type"] = 0.0;
    info._values["assets"] = std::string(PINK_GHOST_PATH);
    info._values["id"] = PINK_GHOST_ID;
    info._values["rectangle"] = initBaseRectangle();
    info._values["string"] = std::string("P");
    info._values["position"] = pos;

    return info;
}

JSON::JSON Arcade::Pacman::initRedGhost() const
{
    JSON::JSON info;
    JSON::JSONArray pos;

    pos.parseMap(PACMAN_PATH, RED_GHOST_CHAR);

    info._values["type"] = 0.0;
    info._values["assets"] = std::string(RED_GHOST_PATH);
    info._values["id"] = RED_GHOST_ID;
    info._values["rectangle"] = initBaseRectangle();
    info._values["string"] = std::string("R");
    info._values["position"] = pos;

    return info;
}

JSON::JSON Arcade::Pacman::initBlueGhost() const
{
    JSON::JSON info;
    JSON::JSONArray pos;

    pos.parseMap(PACMAN_PATH, BLUE_GHOST_CHAR);

    info._values["type"] = 0.0;
    info._values["assets"] = std::string(BLUE_GHOST_PATH);
    info._values["id"] = BLUE_GHOST_ID;
    info._values["rectangle"] = initBaseRectangle();
    info._values["string"] = std::string("B");
    info._values["position"] = pos;

    return info;
}

JSON::JSON Arcade::Pacman::initPoint() const
{
    JSON::JSON info;
    JSON::JSONArray pos;

    pos.parseMap(PACMAN_PATH, DOTS_CHAR);

    info._values["type"] = 0.0;
    info._values["assets"] = std::string("Assets/Pacman/dot.png");
    info._values["id"] = DOTS_ID;
    info._values["rectangle"] = initBaseRectangle();
    info._values["string"] = std::string(".");
    info._values["position"] = pos;

    return info;
}

JSON::JSON Arcade::Pacman::initPower() const
{
    JSON::JSON info;
    JSON::JSONArray pos;

    pos.parseMap(PACMAN_PATH, POWER_CHAR);

    info._values["type"] = 0.0;
    info._values["assets"] = std::string("Assets/Pacman/pac_gum.png");
    info._values["id"] = POWER_ID;
    info._values["rectangle"] = initBaseRectangle();
    info._values["string"] = std::string("o");
    info._values["position"] = pos;

    return info;
}

JSON::JSON Arcade::Pacman::init()
{
    JSON::JSON info;
    JSON::JSONArray arr;

    info._values["isFinished"] = false;

    arr._values.push_back(initWall());
    arr._values.push_back(initPoint());
    arr._values.push_back(initPower());
    arr._values.push_back(initScore());
    arr._values.push_back(initLevel());
    arr._values.push_back(initTime());
    arr._values.push_back(initPlayer());
    arr._values.push_back(initOrangeGhost());
    arr._values.push_back(initRedGhost());
    arr._values.push_back(initBlueGhost());
    arr._values.push_back(initPinkGhost());
    info._values["elements"] = arr;

    _seconds = 0;
    _refreshTime = 0;
    _isGhostInDanger = false;
    _lastTimeEatingGum = 0;
    _lastBlueGet = 0;
    _lastOrangeGet = 0;
    _lastPinkGet = 0;
    _newBluePos._values.clear();
    _newOrangePos._values.clear();
    _newRedPos._values.clear();
    _newPinkPos._values.clear();

    _chrono = std::chrono::steady_clock::now();
    _clock = std::clock();
    _redGhostClock = std::clock();
    _blueGhostClock = std::clock();
    _orangeGhostClock = std::clock();
    _pinkGhostClock = std::clock();
    _data = info;

    return info;
}
