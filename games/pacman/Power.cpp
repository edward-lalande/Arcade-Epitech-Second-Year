/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Power
*/

#include "Pacman.hpp"
#include "JSON.hpp"

void Arcade::Pacman::updateEatingScore(JSON::JSONArray &arrayTemp)
{
    JSON::JSONArray copy = _data.get<JSON::JSONArray>("elements");
    JSON::JSON index = getScore();

    for (std::size_t i = 0; i < copy._values.size(); ++i) {
        JSON::JSON indexDataTemp = copy.get<JSON::JSON>(i);

        if (indexDataTemp.get<double>("id") == SCORE_ID) {
            copy._values.erase(copy._values.begin() + i);
            break;
        }

    }

    for (std::size_t i = 0; i < arrayTemp._values.size(); ++i) {
        JSON::JSON indexTemp = arrayTemp.get<JSON::JSON>(i);

        if (indexTemp.get<double>("id") == SCORE_ID) {
            index = indexTemp;
            arrayTemp._values.erase(arrayTemp._values.begin() + i);
            break;
        }
    }

    index._values["value"] = index.get<double>("value") + EATING_GHOST_POINT;
    copy._values.push_back(index);
    _data._values["elements"] = copy;
    arrayTemp._values.push_back(index);
}

void Arcade::Pacman::canEatGhost(JSON::JSONArray &arrayTemp, JSON::JSON newPlayerPos)
{
    double x = newPlayerPos.get<double>("x");
    double y = newPlayerPos.get<double>("y");

    for (std::size_t i = 0; i < arrayTemp._values.size(); ++i) {
        JSON::JSON index = arrayTemp.get<JSON::JSON>(i);

        if (index.get<double>("id") == ORANGE_GHOST_ID) {
            JSON::JSONArray posArr = index.get<JSON::JSONArray>("position");
            JSON::JSON pos = posArr.get<JSON::JSON>(0);

            if (x == pos.get<double>("x") && y == pos.get<double>("y")) {
                arrayTemp._values.erase(arrayTemp._values.begin() + i);
                updateEatingScore(arrayTemp);
            }

        }

        if (index.get<double>("id") == RED_GHOST_ID) {
            JSON::JSONArray posArr = index.get<JSON::JSONArray>("position");
            JSON::JSON pos = posArr.get<JSON::JSON>(0);

            if (x == pos.get<double>("x") && y == pos.get<double>("y")) {
                arrayTemp._values.erase(arrayTemp._values.begin() + i);
                updateEatingScore(arrayTemp);
            }

        }

        if (index.get<double>("id") == BLUE_GHOST_ID) {
            JSON::JSONArray posArr = index.get<JSON::JSONArray>("position");
            JSON::JSON pos = posArr.get<JSON::JSON>(0);


            if (x == pos.get<double>("x") && y == pos.get<double>("y")) {
                arrayTemp._values.erase(arrayTemp._values.begin() + i);
                updateEatingScore(arrayTemp);
            }

        }

        if (index.get<double>("id") == PINK_GHOST_ID) {
            JSON::JSONArray posArr = index.get<JSON::JSONArray>("position");
            JSON::JSON pos = posArr.get<JSON::JSON>(0);

            if (x == pos.get<double>("x") && y == pos.get<double>("y")) {
                arrayTemp._values.erase(arrayTemp._values.begin() + i);
                updateEatingScore(arrayTemp);
            }

        }

    }
}

void Arcade::Pacman::changeGhostAssets(JSON::JSONArray &arrayTemp)
{
    if (_lastTimeEatingGum == _seconds - ELAPSED_TIME_FOR_DANGEROUS_GHOST) {
        _isGhostInDanger = false;
    }

    for (std::size_t i = 0; i < arrayTemp._values.size(); ++i) {
        JSON::JSON index = arrayTemp.get<JSON::JSON>(i);

        if (index.get<double>("id") == ORANGE_GHOST_ID) {
            index._values["assets"] = _isGhostInDanger ? DANEGROUS_GHOST_ASSETS : ORANGE_GHOST_PATH;
        }

        if (index.get<double>("id") == RED_GHOST_ID) {
            index._values["assets"] = _isGhostInDanger ? DANEGROUS_GHOST_ASSETS : RED_GHOST_PATH;
        }

        if (index.get<double>("id") == BLUE_GHOST_ID) {
            index._values["assets"] = _isGhostInDanger ? DANEGROUS_GHOST_ASSETS : BLUE_GHOST_PATH;
        }

        if (index.get<double>("id") == PINK_GHOST_ID) {
            index._values["assets"] = _isGhostInDanger ? DANEGROUS_GHOST_ASSETS : PINK_GHOST_PATH;
        }

        arrayTemp._values[i] = index;
    }
}

bool Arcade::Pacman::isEating(JSON::JSON newPlayerPos)
{
    JSON::JSONArray copy = _data.get<JSON::JSONArray>("elements");

    for (std::size_t i = 0; i < copy._values.size(); ++i) {
        JSON::JSON index = copy.get<JSON::JSON>(i);

        if (index.get<double>("id") == POWER_ID) {
            JSON::JSONArray gumPos = index.get<JSON::JSONArray>("position");

            for (std::size_t j = 0; j < gumPos._values.size(); ++j) {
                JSON::JSON pos = gumPos.get<JSON::JSON>(j);

                if (pos.get<double>("x") == newPlayerPos.get<double>("x")
                 && pos.get<double>("y") == newPlayerPos.get<double>("y")) {
                    return true;
                }
            }
        }

    }

    return false;
}

void Arcade::Pacman::deletePacGum(JSON::JSONArray &arrayTemp, JSON::JSON newPlayerPos)
{
    JSON::JSONArray copy = _data.get<JSON::JSONArray>("elements");
    JSON::JSON gum = initPower();

    for (std::size_t i = 0; i < copy._values.size(); ++i) {
        JSON::JSON index = copy.get<JSON::JSON>(i);

        if (index.get<double>("id") == POWER_ID) {
            JSON::JSONArray gumPos = index.get<JSON::JSONArray>("position");

            for (std::size_t j = 0; j < gumPos._values.size(); ++j) {
                JSON::JSON pos = gumPos.get<JSON::JSON>(j);

                if (pos.get<double>("x") == newPlayerPos.get<double>("x")
                 && pos.get<double>("y") == newPlayerPos.get<double>("y")) {

                    gumPos._values.erase(gumPos._values.begin() + j);

                }

            }

            copy._values.erase(copy._values.begin() + i);

            gum._values["position"] = gumPos;

            break;
        }
    }
    copy._values.push_back(gum);
    _data._values["elements"] = copy;
    arrayTemp._values.push_back(gum);
}

void Arcade::Pacman::eatingPacGum(JSON::JSONArray &arrayTemp)
{
    JSON::JSON index;
    _isGhostInDanger = true;

    _lastTimeEatingGum = _seconds;
    for (std::size_t i = 0; i < arrayTemp._values.size(); ++i) {
        index = arrayTemp.get<JSON::JSON>(i);

        if (index.get<double>("id") == ORANGE_GHOST_ID) {
            index._values["assets"] = DANEGROUS_GHOST_ASSETS;
        }

        if (index.get<double>("id") == RED_GHOST_ID) {
            index._values["assets"] = DANEGROUS_GHOST_ASSETS;            
        }

        if (index.get<double>("id") == BLUE_GHOST_ID) {
            index._values["assets"] = DANEGROUS_GHOST_ASSETS;
        }

        if (index.get<double>("id") == PINK_GHOST_ID) {
            index._values["assets"] = DANEGROUS_GHOST_ASSETS;
        }

        arrayTemp._values[i] = index;
    }

}
