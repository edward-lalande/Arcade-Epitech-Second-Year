/*
** EPITECH PROJECT, 2024
** Movement for Nibbler game
** File description:
** Arcade Proj
*/

#include "Nibbler.hpp"

bool Arcade::Nibbler::canPass(double X, double Y)
{
	for (std::size_t t = 0; t < _WallPos.size(); t++) {
		if (_WallPos.at(t).first == X && _WallPos.at(t).second == Y) {
			return false;
		}
	}
	return true;
}

Arcade::Nibbler::Direction Arcade::Nibbler::NibDir(double key)
{
    if (key == 73) {
        return up;
    }
    if (key == 74) {
        return down;
    }
    if (key == 71) {
        return  left;
    }
    if (key == 72) {
        return right;
    }
    return _dir;
}

bool Arcade::Nibbler::isReturn()
{
    if (_key == LEFT && _nibPos[0].first - 1.0 == _nibPos[1].first) {
        _key = _lastKey;
        return true;
    }
    if (_key == RIGHT && _nibPos[0].first + 1.0 == _nibPos[1].first) {
        _key = _lastKey;
        return true;
    }
    if (_key == UP && _nibPos[0].second - 1.0 == _nibPos[1].second) {
        _key = _lastKey;
        return true;
    }
    if (_key == DOWN && _nibPos[0].second + 1.0 == _nibPos[1].second) {
        _key = _lastKey;
        return true;
    }
    return false;
}

bool Arcade::Nibbler::movingManagement(double key)
{
    _dir = NibDir(key);

    if (isReturn() == true) {
        return false;
    }

    for (std::size_t t = _nibPos.size() - 1; t > 0; t--) {
        _nibPos[t].first = _nibPos[t - 1].first;
        _nibPos[t].second = _nibPos[t - 1].second;

    }
    if (_dir == up && canTurn(key) == true) {
        _nibPos[0].second -= 1.0;
        _lastKey = key;
        return true;
    }
    if (_dir == down && canTurn(key) == true) {
        _nibPos[0].second += 1.0;
        _lastKey = key;
        return true;
    }
    if (_dir == left && canTurn(key) == true) {
        _nibPos[0].first -= 1.0;
        _lastKey = key;
        return true;
    }
    if (_dir == right && canTurn(key) == true) {
        _nibPos[0].first += 1.0;
        _lastKey = key;
        return true;
    }
    _key = _lastKey;
    return false;
}

bool Arcade::Nibbler::canTurn(double key)
{
    for (std::size_t t = 0; t < _WallPos.size(); t++) {

        if (key == UP && _nibPos[0].first == _WallPos[t].first
        && _nibPos[0].second == _WallPos[t].second + 1) {
            return false;
        }
        if (key == DOWN && _nibPos[0].first == _WallPos[t].first
        && _nibPos[0].second == _WallPos[t].second - 1) {
            return false;
        }
        if (key == LEFT && _nibPos[0].first == _WallPos[t].first + 1
        && _nibPos[0].second == _WallPos[t].second) {
            return false;
        }
        if (key == RIGHT && _nibPos[0].first == _WallPos[t].first - 1
        && _nibPos[0].second == _WallPos[t].second) {
            return false;
        }
    }
    _lastKey = _key;
    return true;
}

bool Arcade::Nibbler::isTcorner(void)
{
    if (_lastKey == RIGHT) {
        if (canTurn(UP) == true && canTurn(DOWN) == true
        && canPass(_nibPos[0].first + 1, _nibPos[0].second) == false) {
                return true;
        }
    }
    if (_lastKey == LEFT) {
        if (canTurn(UP) == true && canTurn(DOWN) == true
        && canPass(_nibPos[0].first - 1, _nibPos[0].second) == false) {
                return true;
        }
    }
    if (_lastKey == UP || _lastKey == DOWN) {
        if (canTurn(RIGHT) == true && canTurn(LEFT) == true
        && canPass(_nibPos[0].first, _nibPos[0].second + 1) == false) {
            return true;
        }
    }
    if (_lastKey == UP) {
        if (canTurn(RIGHT) == true && canTurn(LEFT) == true
        && canPass(_nibPos[0].first, _nibPos[0].second - 1) == false) {
            return true;
        }
    }
    return false;
}

bool Arcade::Nibbler::nibAutoTurn(void)
{
    if (_lastKey == RIGHT) {
        if (canTurn(UP) == true && canTurn(DOWN) == false
        && canPass(_nibPos[0].first + 1, _nibPos[0].second) == false) {
            _lastKey = UP;
            return true;
        }
    }
    if (_lastKey == RIGHT) {
        if (canTurn(UP) == false && canTurn(DOWN) == true
        && canPass(_nibPos[0].first + 1, _nibPos[0].second) == false) {
            _lastKey = DOWN;
            return true;
        }
    }

    if (_lastKey == LEFT) {
        if (canTurn(UP) == true && canTurn(DOWN) == false
        && canPass(_nibPos[0].first - 1, _nibPos[0].second) == false) {
            _lastKey = UP;
            return true;
        }
    }
    if (_lastKey == LEFT) {
        if (canTurn(UP) == false && canTurn(DOWN) == true
        && canPass(_nibPos[0].first - 1, _nibPos[0].second) == false) {
            _lastKey = DOWN;
            return true;
        }
    }

    if (_lastKey == UP) {
        if (canTurn(RIGHT) == true && canTurn(LEFT) == false
        && canPass(_nibPos[0].first, _nibPos[0].second - 1) == false) {
            _lastKey = RIGHT;
            return true;
        }
    }

    if (_lastKey == UP) {
        if (canTurn(RIGHT) == false && canTurn(LEFT) == true
        && canPass(_nibPos[0].first, _nibPos[0].second - 1) == false) {
            _lastKey = LEFT;
            return true;
        }
    }

    if (_lastKey == DOWN) {
        if (canTurn(RIGHT) == true && canTurn(LEFT) == false
        && canPass(_nibPos[0].first, _nibPos[0].second + 1) == false) {
            _lastKey = RIGHT;
            return true;
        }
    }

    if (_lastKey == DOWN) {
        if (canTurn(RIGHT) == false && canTurn(LEFT) == true
        && canPass(_nibPos[0].first, _nibPos[0].second + 1) == false) {
            _lastKey = LEFT;
            return true;
        }
    }
    return false;
}
