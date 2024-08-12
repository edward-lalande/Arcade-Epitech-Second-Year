/*
** EPITECH PROJECT, 2024
** Nibbler Games management
** File description:
** GameManagement
*/

#include "Nibbler.hpp"

bool Arcade::Nibbler::isEating()
{
    for (auto it = _fruitsPos.begin(); it < _fruitsPos.end(); ++it) {
        if (_nibPos[0].first == it->first && _nibPos[0].second == it->second) {
            _nibPos.push_back(addBody());
            _fruitsCount += 1;
            _fruitsPos.erase(it);
            return true;
        }
    }
    return false;
}

double Arcade::Nibbler::checkKey(JSON::JSON &events)
{
    if (events.get<JSON::JSONArray>("keys")._values.size() == 1
    && (events.get<JSON::JSONArray>("keys").get<double>(0) == UP
    || events.get<JSON::JSONArray>("keys").get<double>(0) == DOWN
    || events.get<JSON::JSONArray>("keys").get<double>(0) == RIGHT
    || events.get<JSON::JSONArray>("keys").get<double>(0) == LEFT)) {
        _key = events.get<JSON::JSONArray>("keys").get<double>(0);
        _freeze = false;
    }
    return _key;
}

bool Arcade::Nibbler::checkEnd()
{
    for (std::size_t i = 1; i < _nibPos.size(); i++) {
        if (_nibPos[0] == _nibPos[i]) {
            return true;
        }
    }
    return false;
}

JSON::JSON Arcade::Nibbler::run(JSON::JSON events)
{
    JSON::JSON result;
    JSON::JSONArray positionsArray;

    result._values["isFinished"] = false;
    _key = checkKey(events);

    if (((std::clock() - _clock) * 1000.0 / CLOCKS_PER_SEC) > _speed) {

        if (_freeze == false) {

            if (movingManagement(_key) == true) {
                if (isEating() == true) {
                    if (_fruitsCount == 26.0) {
                        positionsArray._values.push_back(refreshLevel());
                        _wavesEnd = true;
                    }
                    _score += 6.5;
                    positionsArray._values.push_back(refreshFruits());
                    positionsArray._values.push_back(refreshHead());
                    positionsArray._values.push_back(refreshBody());
                    positionsArray._values.push_back(refreshScore());
                }
            }

            else if (movingManagement(_lastKey) == true) {
                if (isEating() == true) {
                    if (_fruitsCount == 26.0) {
                        positionsArray._values.push_back(refreshLevel());
                        _wavesEnd = true;
                    }
                    _score += 6.5;
                    positionsArray._values.push_back(refreshFruits());
                    positionsArray._values.push_back(refreshHead());
                    positionsArray._values.push_back(refreshBody());
                    positionsArray._values.push_back(refreshScore());
                }
            }

            if (isTcorner() == true) {
                _freeze = true;
            }

            if (nibAutoTurn()) {};

        }

       	positionsArray._values.push_back(refreshTime());
       	positionsArray._values.push_back(refreshHead());
       	positionsArray._values.push_back(refreshBody());

        if (checkEnd()) {
            result._values["isFinished"] = true;
            positionsArray._values.clear();
            positionsArray._values.push_back(refreshLevel());

        }

        if (_wavesEnd == true) {
            _fruitsCount = 0.0;
            loadFruitPos();
            positionsArray._values.push_back(refreshFruits());
            _wavesEnd = false;
            _speed -= 10;

        }
        _clock = std::clock();
    }
    result._values["elements"] = positionsArray;
    return result;
}
