/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Run
*/

#include "Snake.hpp"

bool Arcade::Snake::move()
{
    if (_key != 0 && ((std::clock() - _clock) * 1000.0 / CLOCKS_PER_SEC) > 80) {

        if (_key == LEFT && _positions[0].first - 1.0 == _positions[1].first) {
            _key = _lastKey;
            return true;
        }

        if (_key == RIGHT && _positions[0].first + 1.0 == _positions[1].first) {
            _key = _lastKey;
            return true;
        }

        if (_key == UP && _positions[0].second - 1.0 == _positions[1].second) {
            _key = _lastKey;
            return true;
        }

        if (_key == DOWN && _positions[0].second + 1.0 == _positions[1].second) {
            _key = _lastKey;
            return true;
        }

        for (std::size_t i = _positions.size() - 1; i > 0; i--) {
            _positions[i].first = _positions[i - 1].first;
            _positions[i].second = _positions[i - 1].second;
        }

        if (_key == LEFT) {
            _positions[0].first -= 1.0;
            _direction = DIRECTION_LEFT;
        }

        if (_key == RIGHT) {
            _positions[0].first += 1.0;
            _direction = DIRECTION_RIGHT;
        }

        if (_key == UP) {
            _positions[0].second -= 1.0;
            _direction = DIRECTION_UP;
        }

        if (_key == DOWN) {
            _positions[0].second += 1.0;
            _direction = DIRECTION_DOWN;
        }

        _clock = std::clock();

        return true;
    }

    return false;
}

std::pair<double, double> Arcade::Snake::getTailPosition()
{
    std::pair<double, double> beforeLast = _positions[_positions.size() - 2];
    std::pair<double, double> last = _positions[_positions.size() - 1];

    if (beforeLast.second == last.second) {
        if (beforeLast.first < last.first) {
            return std::make_pair(last.first + 1, last.second);
        }
        return std::make_pair(last.first - 1, last.second);
    }

    if (beforeLast.first < last.first) {
        return std::make_pair(last.first, last.second + 1);
    }
    return std::make_pair(last.first, last.second - 1);
}

bool Arcade::Snake::checkApple()
{
    if (_positions[0].first == _apple.first && _positions[0].second == _apple.second) {
        _positions.push_back(getTailPosition());
        _apple.first = 1 + (rand() % (XMAX - 2));
        _apple.second = 1 + (rand() % (YMAX - 2));
        while (isOccuped(_apple)) {
            _apple.first = 1 + (rand() % (XMAX - 2));
            _apple.second = 1 + (rand() % (YMAX - 2));
        }
        _score += 1;
        return true;
    }

    return false;
}

bool Arcade::Snake::isOccuped(std::pair<double, double> position)
{
    for (std::size_t i = 1; i < _positions.size(); i++) {
        if (position.first == _positions[i].first && position.second == _positions[i].second) {
            return true;
        }
    }
    return false;
}

bool Arcade::Snake::checkEnd()
{
    if (_positions[0].first == XMIN || _positions[0].first == XMAX - 1) {
        return true;
    }

    if (_positions[0].second == YMIN || _positions[0].second == YMAX - 1) {
        return true;
    }

    for (std::size_t i = 1; i < _positions.size(); i++) {
        if (_positions[0] == _positions[i]) {
            return true;
        }
    }

    return false;
}

JSON::JSON Arcade::Snake::run(JSON::JSON events)
{
    JSON::JSON json;
    JSON::JSONArray array;

    json._values["isFinished"] = false;

    if (events.getKEYS._values.size() == 1 && (events.getKEY(0) == UP || events.getKEY(0) == DOWN || events.getKEY(0) == RIGHT || events.getKEY(0) == LEFT)) {
        _lastKey = _key;
        _key = events.getKEY(0);
    }

    if (move()) {
        if (checkApple()) {
            array._values.push_back(getScore());
        }
        array._values.push_back(getApple());
        array._values.push_back(getBody());
        array._values.push_back(getHead());
        array._values.push_back(getTime());
    }

    if (checkEnd()) {
        json._values["isFinished"] = true;
        array._values.clear();
        array._values.push_back(getScore());
    }

    json._values["elements"] = array;

    return json;
}
