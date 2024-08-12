/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Movement
*/

#include "Pacman.hpp"

JSON::JSON Arcade::Pacman::getPlayerPos()
{
    JSON::JSONArray elem = _data.get<JSON::JSONArray>("elements");
    JSON::JSONArray elementPos;
    JSON::JSON nullElem;
    JSON::JSON pos;

    nullElem._values["elements"] = "null";
    for (std::size_t i = 0; i < elem._values.size(); ++i) {

        JSON::JSON obj = elem.get<JSON::JSON>(i);
        if (obj.get<double>("id") == PLAYER_ID) {
            elementPos = obj.get<JSON::JSONArray>("position");
            pos = elementPos.get<JSON::JSON>(0);
            return pos;
        }

    }

    return nullElem;
}

void Arcade::Pacman::setNewPlayerPos(JSON::JSON newPOs)
{
    JSON::JSONArray copy = _data.get<JSON::JSONArray>("elements");

    for (std::size_t i = 0; i < copy._values.size(); ++i) {

        JSON::JSON obj = copy.get<JSON::JSON>(i);
        if (obj.get<double>("id") == PLAYER_ID) {
            copy._values.at(i) = newPOs;
        }
    }
    _data._values["elements"] = copy;
}

void Arcade::Pacman::checkMovementOnMap(JSON::JSON &pos)
{
    double posX = pos.get<double>("x");
    double posY = pos.get<double>("y");

    JSON::JSONArray elem = _data.get<JSON::JSONArray>("elements");

    for (std::size_t i = 0; i < elem._values.size(); ++i) {
        JSON::JSON getPos = elem.get<JSON::JSON>(i);

        if (getPos.get<double>("id") == WALL_ID) {
            JSON::JSONArray position = getPos.get<JSON::JSONArray>("position");
            for (std::size_t j = 0; j < position._values.size(); ++j) {
                JSON::JSON tempPos = position.get<JSON::JSON>(j);
                if (tempPos.get<double>("x") == posX && tempPos.get<double>("y") == posY) {
                    pos = getPlayerPos();
                }

            }

        }

    }
}

JSON::JSON Arcade::Pacman::moveUp(JSON::JSON index)
{
    index._values["y"] = std::get<double>(index._values["y"]) + 1;
    return index;
}

JSON::JSON Arcade::Pacman::moveDown(JSON::JSON index)
{
    index._values["y"] = std::get<double>(index._values["y"]) - 1;
    return index;
}

JSON::JSON Arcade::Pacman::moveLeft(JSON::JSON index)
{
    index._values["x"] = std::get<double>(index._values["x"]) - 1;
    return index;
}

JSON::JSON Arcade::Pacman::moveRight(JSON::JSON index)
{
    index._values["x"] = std::get<double>(index._values["x"]) + 1;
    return index;
}

void Arcade::Pacman::teleportation(JSON::JSON &pos)
{
    double x = pos.get<double>("x");
    double y = pos.get<double>("y");

    if (x == TP_LEFT_X && y == TP_LEFT_Y) {
        pos._values["x"] = TP_RIGHT_X;
        pos._values["y"] = TP_RIGHT_Y;
    } else if (x == TP_RIGHT_X && y == TP_RIGHT_Y) {
        pos._values["x"] = TP_LEFT_X;
        pos._values["y"] = TP_LEFT_Y;
    }

}

JSON::JSON Arcade::Pacman::handleMovement(int key)
{
    JSON::JSONArray elem = _data.get<JSON::JSONArray>("elements");
    JSON::JSON index;
    JSON::JSON newPlayerInfo;
    JSON::JSON playerPos;
    JSON::JSONArray newPos;

    _currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(_currentTime - _chrono).count();

    for (std::size_t i = 0; i < elem._values.size() - 1; ++i) {

        JSON::JSON index = elem.get<JSON::JSON>(i);

        if (index.get<double>("id") == PLAYER_ID) {
            JSON::JSONArray getPos = index.get<JSON::JSONArray>("position");
            playerPos = getPos.get<JSON::JSON>(0);

            switch (key) {
                case DOWN:
                    playerPos = moveDown(playerPos);
                    checkMovementOnMap(playerPos);
                    break;

                case RIGHT:
                    playerPos = moveRight(playerPos);
                    checkMovementOnMap(playerPos);
                    break;

                case LEFT:
                    playerPos = moveLeft(playerPos);
                    checkMovementOnMap(playerPos);
                    break;

                case UP:
                    playerPos = moveUp(playerPos);
                    checkMovementOnMap(playerPos);
                    break;

                default:
                    break;

            }

            break;
        }

    }


    if (elapsedTime > _seconds) {
        newPlayerInfo._values["rectangle"] = changeRectangle();
        _seconds++;
    } else {
        newPlayerInfo._values["rectangle"] = initBaseRectangle();
    }
    teleportation(playerPos);
    newPlayerInfo = initPlayer();
    newPos._values.push_back(playerPos);
    newPlayerInfo._values["position"] = newPos;
    setNewPlayerPos(newPlayerInfo);

    return newPlayerInfo;
}
