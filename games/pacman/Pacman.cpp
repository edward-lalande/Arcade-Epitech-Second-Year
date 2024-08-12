/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Pacman
*/

#include <memory>
#include <iterator>
#include "Pacman.hpp"

JSON::JSON Arcade::Pacman::refresh()
{
    return _data;
}

extern "C" bool isGame()
{
    return true;
}

extern "C" Arcade::IGameLibrary *createLibrary()
{
    return new Arcade::Pacman;
}

JSON::JSON Arcade::Pacman::getElementById(double id)
{
    JSON::JSONArray element = _data.get<JSON::JSONArray>("elements");
    JSON::JSON temp;

    for (std::size_t i = 0; element._values.size(); ++i) {
        temp = element.get<JSON::JSON>(i);

        if (temp.get<double>("id") == id) {
            return temp;
        }
    }

    return temp;
}

JSON::JSONArray Arcade::Pacman::getWallPosition()
{
    JSON::JSONArray copy = _data.get<JSON::JSONArray>("elements");
    JSON::JSONArray wallPos;

    for (std::size_t i = 0; i < copy._values.size(); ++i) {
        JSON::JSON temp = copy.get<JSON::JSON>(i);

        if (temp.get<double>("id") == WALL_ID) {
            wallPos = temp.get<JSON::JSONArray>("position");
            break;
        }
    }

    return wallPos;
}

JSON::JSONArray Arcade::Pacman::changeRectangle()
{
    JSON::JSONArray rect;

    if (_seconds != 0 && (int)_seconds % 3 == 0) {
        rect._values.push_back(90.0);
        rect._values.push_back(0.0);
        rect._values.push_back(30.0);
        rect._values.push_back(30.0);

        return rect;
    } else if (_seconds != 0 && (int)_seconds % 2 == 0) {
        rect._values.push_back(30.0);
        rect._values.push_back(0.0);
        rect._values.push_back(30.0);
        rect._values.push_back(30.0);

        return rect;
    }

    rect._values.push_back(0.0);
    rect._values.push_back(0.0);
    rect._values.push_back(30.0);
    rect._values.push_back(30.0);

    return rect;
}

JSON::JSON Arcade::Pacman::updateTime()
{
    JSON::JSON info;

    info = initTime();
    info._values["value"] = (double)(_seconds);

    return info;
}

void Arcade::Pacman::updateScore(JSON::JSONArray &copy)
{
    JSON::JSON score = initScore();
    double actualScore;

    for (std::size_t i = 0; i < copy._values.size(); ++i) {
        JSON::JSON index = copy.get<JSON::JSON>(i);

        if (index.get<double>("id") == SCORE_ID) {
            actualScore = index.get<double>("value");
            copy._values.erase(copy._values.begin() + i);
            break;
        }
    }

    score._values["value"] = actualScore + DOTS_SCORE_POINT;
    copy._values.push_back(score);
}

JSON::JSON Arcade::Pacman::updateDot(JSON::JSON newPlayerPos)
{
    JSON::JSON temp;
    JSON::JSONArray positions;
    JSON::JSON index;
    JSON::JSON indexTemp;
    bool isEating = false;
    JSON::JSONArray copy = _data.get<JSON::JSONArray>("elements");

    for (std::size_t i = 0; i < copy._values.size(); ++i) {
        index = copy.get<JSON::JSON>(i);

        if (index.get<double>("id") == DOTS_ID) {
            double x = newPlayerPos.get<double>("x");
            double y = newPlayerPos.get<double>("y");
            positions = index.get<JSON::JSONArray>("position");

            for (std::size_t j = 0; j < positions._values.size(); ++j) {
                indexTemp = positions.get<JSON::JSON>(j);

                if (indexTemp.get<double>("x") == x && indexTemp.get<double>("y") == y) {
                    isEating = true;
                    positions._values.erase(positions._values.begin() + j);
                    copy._values.erase(copy._values.begin() + i);
                    updateScore(copy);
                    break;
                }
            }
        }
    }

    temp = initPoint();
    temp._values["position"] = positions;
    if (isEating) {
        copy._values.push_back(temp);
    }
    _data._values["elements"] = copy;
    return temp;
}

bool Arcade::Pacman::isFinished()
{
    JSON::JSON dot = getElementById(DOTS_ID);
    JSON::JSON gum = getElementById(POWER_ID);

    if (dot.get<JSON::JSONArray>("position")._values.empty()
    && gum.get<JSON::JSONArray>("position")._values.empty()) {
        return true;
    }

    return false;
}

JSON::JSON Arcade::Pacman::getNewLevel(int actualLevel)
{
    JSON::JSONArray copy = _data.get<JSON::JSONArray>("elements");
    JSON::JSON tmp;

    for (std::size_t i = 0; i < copy._values.size(); ++i) {
        tmp = copy.get<JSON::JSON>(i);

        if (tmp.get<double>("id") == LEVEL_ID) {
            tmp._values["value"] = actualLevel + 1.0;
            break;
        }
    }
    return tmp;
}

int Arcade::Pacman::getActualLevel()
{
    JSON::JSONArray copy = _data.get<JSON::JSONArray>("elements");

    for (std::size_t i = 0; i < copy._values.size(); ++i) {
        JSON::JSON temp = copy.get<JSON::JSON>(i);

        if (temp.get<double>("id") == LEVEL_ID) {
            return (int)temp.get<double>("value");
        }
    }

    return 1;
}

JSON::JSON Arcade::Pacman::getScore()
{
    JSON::JSONArray cpy = _data.get<JSON::JSONArray>("elements");
    JSON::JSON score;

    for (std::size_t i = 0; i < cpy._values.size(); ++i) {
        score = cpy.get<JSON::JSON>(i);

        if (score.get<double>("id") == SCORE_ID) {
            return score;
        }
    
    }

    return score;
}

JSON::JSON Arcade::Pacman::run(JSON::JSON events)
{
    JSON::JSON temp;
    JSON::JSONArray arrayTemp;
    JSON::JSON newPlayerPos;
    int key = 0;
    int actualLevel = getActualLevel();

    temp._values["isFinished"] = false;

    if (events.get<JSON::JSONArray>("keys")._values.size() == 1) {
        key = events.get<JSON::JSONArray>("keys").get<double>(0);
    }
    if (key == 0) {
        key = _lastKey;
    }
    if (((std::clock() - _clock) * 1000.0 / CLOCKS_PER_SEC) > 80) {
        newPlayerPos = handleMovement(key);
        arrayTemp._values.push_back(newPlayerPos);
        _clock = std::clock();
    } else {
        newPlayerPos = getElementById(PLAYER_ID);
    }
    _lastKey = key;

    if (_seconds > ELAPSED_TIME_FOR_RED_DEPARTURE) {
        if (((std::clock() - _redGhostClock) * 1000.0 / CLOCKS_PER_SEC) > 140 - (actualLevel * 10)) {
            arrayTemp._values.push_back(getNewRedGhostPos(newPlayerPos.getPLAYER_POS));
            _redGhostClock = std::clock();
        }
    }

    if (_seconds > ELAPSED_TIME_FOR_PINK_DEPARTURE) {
        if (((std::clock() - _pinkGhostClock) * 1000.0 / CLOCKS_PER_SEC) > 140 - (actualLevel * 10)) {
            arrayTemp._values.push_back(getNewPinkGhostPos(newPlayerPos.getPLAYER_POS));
            _pinkGhostClock = std::clock();
        }
    }

    if (_seconds > ELAPSED_TIME_FOR_ORANGE_DEPARTURE) {
        if (((std::clock() - _orangeGhostClock) * 1000.0 / CLOCKS_PER_SEC) > 140 - (actualLevel * 10)) {
            _orangeGhostClock = std::clock();
            arrayTemp._values.push_back(getNewOrangeGhostPos(newPlayerPos.getPLAYER_POS));
        }
    }   

    if (_seconds > ELAPSED_TIME_FOR_BLUE_DEPARTURE) {
        if (((std::clock() - _blueGhostClock) * 1000.0 / CLOCKS_PER_SEC) > 140 - (actualLevel * 10)) {
            arrayTemp._values.push_back(getNewBlueGhostPos(newPlayerPos.getPLAYER_POS));
            _blueGhostClock = std::clock();
        }
    }

    arrayTemp._values.push_back(updateTime());
    arrayTemp._values.push_back(updateDot(newPlayerPos.getPLAYER_POS));
    arrayTemp._values.push_back(getScore());


    if (_isGhostInDanger) {
        changeGhostAssets(arrayTemp);
        canEatGhost(arrayTemp, newPlayerPos.getPLAYER_POS);
    } else if (_isGhostInDanger && _lastTimeEatingGum + 10 > _seconds) {
        _isGhostInDanger = false;
    }

    if (isEating(newPlayerPos.getPLAYER_POS)) {
        _lastTimeEatingGum = _seconds;
        eatingPacGum(arrayTemp);
        deletePacGum(arrayTemp, newPlayerPos.getPLAYER_POS);
    }

    if (isFinished() || (isPlayerDead(newPlayerPos.getPLAYER_POS) && !_isGhostInDanger)) {
        _data = init();
        temp._values.clear();
        temp._values["isFinished"] = true;
        arrayTemp._values.clear();
        arrayTemp._values.push_back(getScore());
    }

    temp._values["elements"] = arrayTemp;
    _currentTime = std::chrono::steady_clock::now();
    _elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(_currentTime - _chrono).count();
    _refreshTime = _seconds - 1;
    return temp;
}
