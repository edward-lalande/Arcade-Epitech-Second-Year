/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Ghost
*/

#include "Pacman.hpp"

bool Arcade::Pacman::isGhostAt(JSON::JSON pos, double yourId)
{
    JSON::JSONArray elements = _data.get<JSON::JSONArray>("elements");

    for (std::size_t i = 0; i < elements._values.size(); ++i) {
        JSON::JSON temp = elements.get<JSON::JSON>(i);

        if (temp.get<double>("id") == RED_GHOST_ID && RED_GHOST_ID != yourId) {
            JSON::JSONArray redGhost = temp.get<JSON::JSONArray>("position");
            JSON::JSON redPos = redGhost.get<JSON::JSON>(0);

            if (redPos.get<double>("x") == pos.get<double>("x")
            && redPos.get<double>("y") == pos.get<double>("y")) {
                return true;
            }
        }

        if (temp.get<double>("id") == PINK_GHOST_ID && PINK_GHOST_ID != yourId) {
            JSON::JSONArray pinkGhost = temp.get<JSON::JSONArray>("position");
            JSON::JSON pinkPos = pinkGhost.get<JSON::JSON>(0);

            if (pinkPos.get<double>("x") == pos.get<double>("x")
            && pinkPos.get<double>("y") == pos.get<double>("y")) {
                return true;
            }
        }

        if (temp.get<double>("id") == BLUE_GHOST_ID  && BLUE_GHOST_ID != yourId) {
            JSON::JSONArray blueGhost = temp.get<JSON::JSONArray>("position");
            JSON::JSON bluePos = blueGhost.get<JSON::JSON>(0);

            if (bluePos.get<double>("x") == pos.get<double>("x")
            && bluePos.get<double>("y") == pos.get<double>("y")) {
                return true;
            }
        }

        if (temp.get<double>("id") == ORANGE_GHOST_ID  && ORANGE_GHOST_ID != yourId) {
            JSON::JSONArray orangeGhost = temp.get<JSON::JSONArray>("position");
            JSON::JSON orangePos = orangeGhost.get<JSON::JSON>(0);

            if (orangePos.get<double>("x") == pos.get<double>("x")
            && orangePos.get<double>("y") == pos.get<double>("y")) {
                return true;
            }
        }

    }

    return false;
}

JSON::JSON Arcade::Pacman::getGhostPosition(double id)
{
    JSON::JSONArray tmp = _data.get<JSON::JSONArray>("elements");
    JSON::JSON ghostPos;

    for (std::size_t i = 0; i < tmp._values.size(); ++i) {
        JSON::JSON element = tmp.get<JSON::JSON>(i);

        if (element.get<double>("id") == id) {
            ghostPos = element.get<JSON::JSONArray>("position").get<JSON::JSON>(0);
            break;
        }
    }

    return ghostPos;
}

bool Arcade::Pacman::isWall(double x, double y)
{
    JSON::JSONArray wall = getWallPosition();

    for (std::size_t i = 0; i < wall._values.size(); ++i) {
        JSON::JSON temp = wall.get<JSON::JSON>(i);

        if (temp.get<double>("x") == x && temp.get<double>("y") == y) {
            return true;
        }
    }

    return false;
}

bool Arcade::Pacman::isPlayerDead(JSON::JSON newPlayerPos)
{
    JSON::JSONArray copy = _data.get<JSON::JSONArray>("elements");

    for (std::size_t i = 0; i < copy._values.size(); ++i) {
        JSON::JSON index = copy.get<JSON::JSON>(i);

        if (index.get<double>("id") == ORANGE_GHOST_ID
         || index.get<double>("id") == PINK_GHOST_ID
         || index.get<double>("id") == RED_GHOST_ID
         || index.get<double>("id") == BLUE_GHOST_ID) {

            JSON::JSONArray ghostPosition = index.get<JSON::JSONArray>("position");
            JSON::JSON ghostPos = ghostPosition.get<JSON::JSON>(0);

            if (ghostPos.get<double>("x") == newPlayerPos.get<double>("x")
             && ghostPos.get<double>("y") == newPlayerPos.get<double>("y")) {

                return true;

            }
        }
    }

    return false;
}

bool Arcade::Pacman::isInArray(JSON::JSONArray arr, double x, double y)
{
    for (std::size_t i = 0; i < arr._values.size(); ++i) {
        JSON::JSON tmp = arr.get<JSON::JSON>(i);

        if (tmp.get<double>("x") == x
         && tmp.get<double>("y") == y) {
            return true;
        }
    }

    return false;
}

bool Arcade::Pacman::isInMap(double x, double y)
{
    if ((x > 0 && x < 32) && (y > 0 && y < 14)) {
        return true;
    }

    return false;
}

JSON::JSONArray Arcade::Pacman::goToPosRed(JSON::JSON pos, JSON::JSONArray newPosArray)
{
    JSON::JSON ghost = newPosArray.get<JSON::JSON>(newPosArray._values.size() - 1);
    JSON::JSON newPos;

    double xPlayer = pos.get<double>("x");
    double yPlayer = pos.get<double>("y");
    double xGhost = ghost.get<double>("x");
    double yGhost = ghost.get<double>("y");

    if (_newRedPos._values.size() != 0) {
        return _newRedPos;
    }

    if ((xGhost == xPlayer && yGhost == yPlayer) || newPosArray._values.size() > 10) {
        newPosArray._values.erase(newPosArray._values.begin());
        _newRedPos = newPosArray;
        return newPosArray;
    }

    if (xPlayer > xGhost) {

        if ((!isWall(xGhost + 1, yGhost) && !isInArray(newPosArray, xGhost + 1, yGhost))
        && isInMap(xGhost + 1, yGhost) && !isGhostAt(ghost, RED_GHOST_ID)) {
            newPos._values["x"] = xGhost + 1;
            newPos._values["y"] = yGhost;
            newPosArray._values.push_back(newPos);
            goToPosRed(pos, newPosArray);
            newPosArray._values.pop_back();
        }

        if ((!isWall(xGhost - 1, yGhost) && !isInArray(newPosArray, xGhost - 1, yGhost))
        && isInMap(xGhost - 1, yGhost) && !isGhostAt(ghost, RED_GHOST_ID)) {
            newPos._values["x"] = xGhost - 1;
            newPos._values["y"] = yGhost;
            newPosArray._values.push_back(newPos);
            goToPosRed(pos, newPosArray);
            newPosArray._values.pop_back();
        }

    } else {

        if ((!isWall(xGhost - 1, yGhost) && !isInArray(newPosArray, xGhost - 1, yGhost))
        && isInMap(xGhost - 1, yGhost) && !isGhostAt(ghost, RED_GHOST_ID)) {
            newPos._values["x"] = xGhost - 1;
            newPos._values["y"] = yGhost;
            newPosArray._values.push_back(newPos);
            goToPosRed(pos, newPosArray);
            newPosArray._values.pop_back();
        }

        if ((!isWall(xGhost + 1, yGhost) && !isInArray(newPosArray, xGhost + 1, yGhost))
        && isInMap(xGhost + 1, yGhost) && !isGhostAt(ghost, RED_GHOST_ID)) {
            newPos._values["x"] = xGhost + 1;
            newPos._values["y"] = yGhost;
            newPosArray._values.push_back(newPos);
            goToPosRed(pos, newPosArray);
            newPosArray._values.pop_back();
        }

    }

    if (yPlayer > yGhost) {

        if ((!isWall(xGhost, yGhost + 1) && !isInArray(newPosArray, xGhost, yGhost + 1))
        && isInMap(xGhost, yGhost + 1) && !isGhostAt(ghost, RED_GHOST_ID)) {
            newPos._values["x"] = xGhost;
            newPos._values["y"] = yGhost + 1;
            newPosArray._values.push_back(newPos);
            goToPosRed(pos, newPosArray);
            newPosArray._values.pop_back();
        }

        if ((!isWall(xGhost, yGhost - 1) && !isInArray(newPosArray, xGhost, yGhost - 1))
        && isInMap(xGhost, yGhost - 1) && !isGhostAt(ghost, RED_GHOST_ID)) {
            newPos._values["x"] = xGhost;
            newPos._values["y"] = yGhost - 1;
            newPosArray._values.push_back(newPos);
            goToPosRed(pos, newPosArray);
            newPosArray._values.pop_back();
        }

    } else {

        if ((!isWall(xGhost, yGhost - 1) && !isInArray(newPosArray, xGhost, yGhost - 1))
        && isInMap(xGhost, yGhost - 1) && !isGhostAt(ghost, RED_GHOST_ID)) {
            newPos._values["x"] = xGhost;
            newPos._values["y"] = yGhost - 1;
            newPosArray._values.push_back(newPos);
            goToPosRed(pos, newPosArray);
            newPosArray._values.pop_back();
        }

        if ((!isWall(xGhost, yGhost + 1) && !isInArray(newPosArray, xGhost, yGhost + 1))
        && isInMap(xGhost, yGhost + 1) && !isGhostAt(ghost, RED_GHOST_ID)) {
            newPos._values["x"] = xGhost;
            newPos._values["y"] = yGhost + 1;
            newPosArray._values.push_back(newPos);
            goToPosRed(pos, newPosArray);
            newPosArray._values.pop_back();
        }

    }

    return newPosArray;
}

JSON::JSONArray Arcade::Pacman::goToPosBlue(JSON::JSON pos, JSON::JSONArray newPosArray)
{
    JSON::JSON ghost = newPosArray.get<JSON::JSON>(newPosArray._values.size() - 1);
    JSON::JSON newPos;

    double xPlayer = pos.get<double>("x");
    double yPlayer = pos.get<double>("y");
    double xGhost = ghost.get<double>("x");
    double yGhost = ghost.get<double>("y");

    if (_newBluePos._values.size() != 0) {
        return _newBluePos;
    }

    if ((xGhost == xPlayer && yGhost == yPlayer) || newPosArray._values.size() > 10) {
        newPosArray._values.erase(newPosArray._values.begin());
        _newBluePos = newPosArray;
        return newPosArray;
    }

    if (xPlayer < xGhost) {

        if ((!isWall(xGhost - 1, yGhost) && !isInArray(newPosArray, xGhost - 1, yGhost))
        && isInMap(xGhost - 1, yGhost) && !isGhostAt(ghost, BLUE_GHOST_ID)) {
            newPos._values["x"] = xGhost - 1;
            newPos._values["y"] = yGhost;
            newPosArray._values.push_back(newPos);
            goToPosBlue(pos, newPosArray);
            newPosArray._values.pop_back();
        }

        if ((!isWall(xGhost + 1, yGhost) && !isInArray(newPosArray, xGhost + 1, yGhost))
        && isInMap(xGhost + 1, yGhost) && !isGhostAt(ghost, BLUE_GHOST_ID)) {
            newPos._values["x"] = xGhost + 1;
            newPos._values["y"] = yGhost;
            newPosArray._values.push_back(newPos);
            goToPosBlue(pos, newPosArray);
            newPosArray._values.pop_back();
        }

    } else {

        if ((!isWall(xGhost + 1, yGhost) && !isInArray(newPosArray, xGhost + 1, yGhost))
        && isInMap(xGhost + 1, yGhost) && !isGhostAt(ghost, BLUE_GHOST_ID)) {
            newPos._values["x"] = xGhost + 1;
            newPos._values["y"] = yGhost;
            newPosArray._values.push_back(newPos);
            goToPosBlue(pos, newPosArray);
            newPosArray._values.pop_back();
        }

        if ((!isWall(xGhost - 1, yGhost) && !isInArray(newPosArray, xGhost - 1, yGhost))
        && isInMap(xGhost - 1, yGhost) && !isGhostAt(ghost, BLUE_GHOST_ID)) {
            newPos._values["x"] = xGhost - 1;
            newPos._values["y"] = yGhost;
            newPosArray._values.push_back(newPos);
            goToPosBlue(pos, newPosArray);
            newPosArray._values.pop_back();
        }

    }

    if (yPlayer > yGhost) {

        if ((!isWall(xGhost, yGhost + 1) && !isInArray(newPosArray, xGhost, yGhost + 1))
        && isInMap(xGhost, yGhost + 1) && !isGhostAt(ghost, BLUE_GHOST_ID)) {
            newPos._values["x"] = xGhost;
            newPos._values["y"] = yGhost + 1;
            newPosArray._values.push_back(newPos);
            goToPosBlue(pos, newPosArray);
            newPosArray._values.pop_back();
        }

        if ((!isWall(xGhost, yGhost - 1) && !isInArray(newPosArray, xGhost, yGhost - 1))
        && isInMap(xGhost, yGhost - 1) && !isGhostAt(ghost, BLUE_GHOST_ID)) {
            newPos._values["x"] = xGhost;
            newPos._values["y"] = yGhost - 1;
            newPosArray._values.push_back(newPos);
            goToPosBlue(pos, newPosArray);
            newPosArray._values.pop_back();
        }

    } else {

        if ((!isWall(xGhost, yGhost - 1) && !isInArray(newPosArray, xGhost, yGhost - 1))
        && isInMap(xGhost, yGhost - 1) && !isGhostAt(ghost, BLUE_GHOST_ID)) {
            newPos._values["x"] = xGhost;
            newPos._values["y"] = yGhost - 1;
            newPosArray._values.push_back(newPos);
            goToPosBlue(pos, newPosArray);
            newPosArray._values.pop_back();
        }

        if ((!isWall(xGhost, yGhost + 1) && !isInArray(newPosArray, xGhost, yGhost + 1))
        && isInMap(xGhost, yGhost + 1) && !isGhostAt(ghost, BLUE_GHOST_ID)) {
            newPos._values["x"] = xGhost;
            newPos._values["y"] = yGhost + 1;
            newPosArray._values.push_back(newPos);
            goToPosBlue(pos, newPosArray);
            newPosArray._values.pop_back();
        }

    }

    return newPosArray;
}

JSON::JSONArray Arcade::Pacman::goToPosOrange(JSON::JSON pos, JSON::JSONArray newPosArray)
{
    JSON::JSON ghost = newPosArray.get<JSON::JSON>(newPosArray._values.size() - 1);
    JSON::JSON newPos;

    double xPlayer = pos.get<double>("x");
    double yPlayer = pos.get<double>("y");
    double xGhost = ghost.get<double>("x");
    double yGhost = ghost.get<double>("y");

    if (_newOrangePos._values.size() != 0) {
        return _newOrangePos;
    }

    if ((xGhost == xPlayer && yGhost == yPlayer) || newPosArray._values.size() > 10) {
        newPosArray._values.erase(newPosArray._values.begin());
        _newOrangePos = newPosArray;
        return newPosArray;
    }

    if (yPlayer > yGhost) {

        if ((!isWall(xGhost, yGhost + 1) && !isInArray(newPosArray, xGhost, yGhost + 1))
        && isInMap(xGhost, yGhost + 1) && !isGhostAt(ghost, ORANGE_GHOST_ID)) {
            newPos._values["x"] = xGhost;
            newPos._values["y"] = yGhost + 1;
            newPosArray._values.push_back(newPos);
            goToPosOrange(pos, newPosArray);
            newPosArray._values.pop_back();
        }

        if ((!isWall(xGhost, yGhost - 1) && !isInArray(newPosArray, xGhost, yGhost - 1))
        && isInMap(xGhost, yGhost - 1) && !isGhostAt(ghost, ORANGE_GHOST_ID)) {
            newPos._values["x"] = xGhost;
            newPos._values["y"] = yGhost - 1;
            newPosArray._values.push_back(newPos);
            goToPosOrange(pos, newPosArray);
            newPosArray._values.pop_back();
        }

    } else {

        if ((!isWall(xGhost, yGhost - 1) && !isInArray(newPosArray, xGhost, yGhost - 1))
        && isInMap(xGhost, yGhost - 1) && !isGhostAt(ghost, ORANGE_GHOST_ID)) {
            newPos._values["x"] = xGhost;
            newPos._values["y"] = yGhost - 1;
            newPosArray._values.push_back(newPos);
            goToPosOrange(pos, newPosArray);
            newPosArray._values.pop_back();
        }

        if ((!isWall(xGhost, yGhost + 1) && !isInArray(newPosArray, xGhost, yGhost + 1))
        && isInMap(xGhost, yGhost + 1) && !isGhostAt(ghost, ORANGE_GHOST_ID)) {
            newPos._values["x"] = xGhost;
            newPos._values["y"] = yGhost + 1;
            newPosArray._values.push_back(newPos);
            goToPosOrange(pos, newPosArray);
            newPosArray._values.pop_back();
        }

    }

    if (xPlayer < xGhost) {

        if ((!isWall(xGhost - 1, yGhost) && !isInArray(newPosArray, xGhost - 1, yGhost))
        && isInMap(xGhost - 1, yGhost) && !isGhostAt(ghost, ORANGE_GHOST_ID)) {
            newPos._values["x"] = xGhost - 1;
            newPos._values["y"] = yGhost;
            newPosArray._values.push_back(newPos);
            goToPosOrange(pos, newPosArray);
            newPosArray._values.pop_back();
        }

        if ((!isWall(xGhost + 1, yGhost) && !isInArray(newPosArray, xGhost + 1, yGhost))
        && isInMap(xGhost + 1, yGhost) && !isGhostAt(ghost, ORANGE_GHOST_ID)) {
            newPos._values["x"] = xGhost + 1;
            newPos._values["y"] = yGhost;
            newPosArray._values.push_back(newPos);
            goToPosOrange(pos, newPosArray);
            newPosArray._values.pop_back();
        }

    } else {

        if ((!isWall(xGhost + 1, yGhost) && !isInArray(newPosArray, xGhost + 1, yGhost))
        && isInMap(xGhost + 1, yGhost) && !isGhostAt(ghost, ORANGE_GHOST_ID)) {
            newPos._values["x"] = xGhost + 1;
            newPos._values["y"] = yGhost;
            newPosArray._values.push_back(newPos);
            goToPosOrange(pos, newPosArray);
            newPosArray._values.pop_back();
        }

        if ((!isWall(xGhost - 1, yGhost) && !isInArray(newPosArray, xGhost - 1, yGhost))
        && isInMap(xGhost - 1, yGhost) && !isGhostAt(ghost, ORANGE_GHOST_ID)) {
            newPos._values["x"] = xGhost - 1;
            newPos._values["y"] = yGhost;
            newPosArray._values.push_back(newPos);
            goToPosOrange(pos, newPosArray);
            newPosArray._values.pop_back();
        }

    }

    return newPosArray;
}

JSON::JSONArray Arcade::Pacman::goToPosPink(JSON::JSON pos, JSON::JSONArray newPosArray)
{
    JSON::JSON ghost = newPosArray.get<JSON::JSON>(newPosArray._values.size() - 1);
    JSON::JSON newPos;

    double xPlayer = pos.get<double>("x");
    double yPlayer = pos.get<double>("y");
    double xGhost = ghost.get<double>("x");
    double yGhost = ghost.get<double>("y");

    if (_newPinkPos._values.size() != 0) {
        return _newPinkPos;
    }

    if ((xGhost == xPlayer && yGhost == yPlayer) || newPosArray._values.size() > 10) {
        newPosArray._values.erase(newPosArray._values.begin());
        _newPinkPos = newPosArray;
        return newPosArray;
    }

    if (xPlayer < xGhost) {

        if ((!isWall(xGhost - 1, yGhost) && !isInArray(newPosArray, xGhost - 1, yGhost))
        && isInMap(xGhost - 1, yGhost) && !isGhostAt(ghost, PINK_GHOST_ID)) {
            newPos._values["x"] = xGhost - 1;
            newPos._values["y"] = yGhost;
            newPosArray._values.push_back(newPos);
            goToPosPink(pos, newPosArray);
            newPosArray._values.pop_back();
        }

        if ((!isWall(xGhost + 1, yGhost) && !isInArray(newPosArray, xGhost + 1, yGhost))
        && isInMap(xGhost + 1, yGhost) && !isGhostAt(ghost, PINK_GHOST_ID)) {
            newPos._values["x"] = xGhost + 1;
            newPos._values["y"] = yGhost;
            newPosArray._values.push_back(newPos);
            goToPosPink(pos, newPosArray);
            newPosArray._values.pop_back();
        }

    } else {

        if ((!isWall(xGhost + 1, yGhost) && !isInArray(newPosArray, xGhost + 1, yGhost))
        && isInMap(xGhost + 1, yGhost) && !isGhostAt(ghost, PINK_GHOST_ID)) {
            newPos._values["x"] = xGhost + 1;
            newPos._values["y"] = yGhost;
            newPosArray._values.push_back(newPos);
            goToPosPink(pos, newPosArray);
            newPosArray._values.pop_back();
        }

        if ((!isWall(xGhost - 1, yGhost) && !isInArray(newPosArray, xGhost - 1, yGhost))
        && isInMap(xGhost - 1, yGhost) && !isGhostAt(ghost, PINK_GHOST_ID)) {
            newPos._values["x"] = xGhost - 1;
            newPos._values["y"] = yGhost;
            newPosArray._values.push_back(newPos);
            goToPosPink(pos, newPosArray);
            newPosArray._values.pop_back();
        }

    }

    if (yPlayer > yGhost) {

        if ((!isWall(xGhost, yGhost + 1) && !isInArray(newPosArray, xGhost, yGhost + 1))
        && isInMap(xGhost, yGhost + 1) && !isGhostAt(ghost, PINK_GHOST_ID)) {
            newPos._values["x"] = xGhost;
            newPos._values["y"] = yGhost + 1;
            newPosArray._values.push_back(newPos);
            goToPosPink(pos, newPosArray);
            newPosArray._values.pop_back();
        }

        if ((!isWall(xGhost, yGhost - 1) && !isInArray(newPosArray, xGhost, yGhost - 1))
        && isInMap(xGhost, yGhost - 1) && !isGhostAt(ghost, PINK_GHOST_ID)) {
            newPos._values["x"] = xGhost;
            newPos._values["y"] = yGhost - 1;
            newPosArray._values.push_back(newPos);
            goToPosPink(pos, newPosArray);
            newPosArray._values.pop_back();
        }

    } else {

        if ((!isWall(xGhost, yGhost - 1) && !isInArray(newPosArray, xGhost, yGhost - 1))
        && isInMap(xGhost, yGhost - 1) && !isGhostAt(ghost, PINK_GHOST_ID)) {
            newPos._values["x"] = xGhost;
            newPos._values["y"] = yGhost - 1;
            newPosArray._values.push_back(newPos);
            goToPosPink(pos, newPosArray);
            newPosArray._values.pop_back();
        }

        if ((!isWall(xGhost, yGhost + 1) && !isInArray(newPosArray, xGhost, yGhost + 1))
        && isInMap(xGhost, yGhost + 1) && !isGhostAt(ghost, PINK_GHOST_ID)) {
            newPos._values["x"] = xGhost;
            newPos._values["y"] = yGhost + 1;
            newPosArray._values.push_back(newPos);
            goToPosPink(pos, newPosArray);
            newPosArray._values.pop_back();
        }

    }

    return newPosArray;
}

JSON::JSONArray Arcade::Pacman::goToNextOrangePos()
{
    JSON::JSONArray newPosArray;
    JSON::JSON newPos = _newOrangePos.get<JSON::JSON>(0);

    newPosArray._values.push_back(newPos);
    _newOrangePos._values.erase(_newOrangePos._values.begin());

    return newPosArray;
}

JSON::JSONArray Arcade::Pacman::goToNextBluePos()
{
    JSON::JSONArray newPosArray;
    JSON::JSON newPos = _newBluePos.get<JSON::JSON>(0);

    newPosArray._values.push_back(newPos);
    _newBluePos._values.erase(_newBluePos._values.begin());

    return newPosArray;
}

JSON::JSONArray Arcade::Pacman::goToNextPinkPos()
{
    JSON::JSONArray newPosArray;
    JSON::JSON newPos = _newPinkPos.get<JSON::JSON>(0);

    newPosArray._values.push_back(newPos);
    _newPinkPos._values.erase(_newPinkPos._values.begin());

    return newPosArray;
}

JSON::JSONArray Arcade::Pacman::goToNextRedPos()
{
    JSON::JSONArray newPosArray;
    JSON::JSON newPos = _newRedPos.get<JSON::JSON>(0);

    newPosArray._values.push_back(newPos);
    _newRedPos._values.erase(_newRedPos._values.begin());

    return newPosArray;
}

JSON::JSON Arcade::Pacman::getNewRedGhostPos(JSON::JSON pos)
{
    JSON::JSONArray copy = _data.get<JSON::JSONArray>("elements");
    JSON::JSON newGhost = initRedGhost();
    JSON::JSON temp = getElementById(RED_GHOST_ID);
    JSON::JSONArray newPos = temp.get<JSON::JSONArray>("position");

    for (std::size_t i = 0; i < copy._values.size(); ++i) {
        JSON::JSON tmp = copy.get<JSON::JSON>(i);

        if (tmp.get<double>("id") == RED_GHOST_ID) {
            copy._values.erase(copy._values.begin() + i);
            break;
        }

    }

    if (_isGhostInDanger
        && (newPos.get<JSON::JSON>(0).get<double>("x") != SPAWN_X
        && newPos.get<JSON::JSON>(0).get<double>("y") != SPAWN_Y)
        && isPlayerDead(pos)) {
        pos._values["x"] = newGhost.get<JSON::JSONArray>("position").get<JSON::JSON>(0).get<double>("x");
        pos._values["y"] = newGhost.get<JSON::JSONArray>("position").get<JSON::JSON>(0).get<double>("y");
        _newRedPos._values.clear();
    }

    if (_newRedPos._values.empty()) {
        goToPosRed(pos, temp.get<JSON::JSONArray>("position"));
    }
    newPos = goToNextRedPos();
    newGhost._values["position"] = newPos;
    copy._values.push_back(newGhost);
    _data._values["elements"] = copy;

    return newGhost;
}

JSON::JSON Arcade::Pacman::getNewBlueGhostPos(JSON::JSON pos)
{
    JSON::JSONArray copy = _data.get<JSON::JSONArray>("elements");
    JSON::JSON newGhost = initBlueGhost();
    JSON::JSON temp = getElementById(BLUE_GHOST_ID);
    JSON::JSONArray newPos = temp.get<JSON::JSONArray>("position");;

    for (std::size_t i = 0; i < copy._values.size(); ++i) {
        JSON::JSON tmp = copy.get<JSON::JSON>(i);

        if (tmp.get<double>("id") == BLUE_GHOST_ID) {
            copy._values.erase(copy._values.begin() + i);
            break;
        }

    }

    if (_isGhostInDanger
        && (newPos.get<JSON::JSON>(0).get<double>("x") != SPAWN_X
        && newPos.get<JSON::JSON>(0).get<double>("y") != SPAWN_Y)
        && isPlayerDead(pos)) {
        pos._values["x"] = 29.0;
        pos._values["y"] = 2.0;
        _newBluePos._values.clear();
    }

    if (_lastBlueGet > _seconds || _newBluePos._values.empty()) {
        goToPosBlue(pos, temp.get<JSON::JSONArray>("position"));
        _lastBlueGet = _seconds + 10;
    }
    newPos = goToNextBluePos();
    newGhost._values["position"] = newPos;
    copy._values.push_back(newGhost);
    _data._values["elements"] = copy;

    return newGhost;
}

JSON::JSON Arcade::Pacman::getNewPinkGhostPos(JSON::JSON pos)
{
    JSON::JSONArray copy = _data.get<JSON::JSONArray>("elements");
    JSON::JSON newGhost = initPinkGhost();
    JSON::JSON temp = getElementById(PINK_GHOST_ID);
    JSON::JSONArray newPos = temp.get<JSON::JSONArray>("position");;

    for (std::size_t i = 0; i < copy._values.size(); ++i) {
        JSON::JSON tmp = copy.get<JSON::JSON>(i);

        if (tmp.get<double>("id") == PINK_GHOST_ID) {
            copy._values.erase(copy._values.begin() + i);
            break;
        }

    }

    if (_isGhostInDanger
        && (newPos.get<JSON::JSON>(0).get<double>("x") != SPAWN_X
        && newPos.get<JSON::JSON>(0).get<double>("y") != SPAWN_Y)
        && isPlayerDead(pos)) {
        pos._values["x"] = 1.0;
        pos._values["y"] = 12.0;
        _newPinkPos._values.clear();
    }

    if (_lastPinkGet > _seconds || _newPinkPos._values.empty()) {
        goToPosPink(pos, temp.get<JSON::JSONArray>("position"));
        _lastPinkGet = _seconds + 8;
    }
    newPos = goToNextPinkPos();
    newGhost._values["position"] = newPos;
    copy._values.push_back(newGhost);
    _data._values["elements"] = copy;

    return newGhost;
}

JSON::JSON Arcade::Pacman::getNewOrangeGhostPos(JSON::JSON pos)
{
    JSON::JSONArray copy = _data.get<JSON::JSONArray>("elements");
    JSON::JSON newGhost = initOrangeGhost();
    JSON::JSON temp = getElementById(ORANGE_GHOST_ID);
    JSON::JSONArray newPos = temp.get<JSON::JSONArray>("position");;

    for (std::size_t i = 0; i < copy._values.size(); ++i) {
        JSON::JSON tmp = copy.get<JSON::JSON>(i);

        if (tmp.get<double>("id") == ORANGE_GHOST_ID) {
            copy._values.erase(copy._values.begin() + i);
            break;
        }

    }

    if (_isGhostInDanger
        && (newPos.get<JSON::JSON>(0).get<double>("x") != SPAWN_X
        && newPos.get<JSON::JSON>(0).get<double>("y") != SPAWN_Y)
        && isPlayerDead(pos)) {
        pos._values["x"] = 3.0;
        pos._values["y"] = 2.0;
        _newOrangePos._values.clear();
    }

    if (_lastOrangeGet > _seconds || _newOrangePos._values.empty()) {
        goToPosOrange(pos, temp.get<JSON::JSONArray>("position"));
        _lastOrangeGet = _seconds +5; 
    }
    newPos = goToNextOrangePos();
    newGhost._values["position"] = newPos;
    copy._values.push_back(newGhost);
    _data._values["elements"] = copy;

    return newGhost;
}
