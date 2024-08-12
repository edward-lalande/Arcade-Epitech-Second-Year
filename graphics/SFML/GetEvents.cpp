/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** GetEvents
*/

#include "SFML.hpp"

std::string Arcade::SFML::getLib()
{
    sf::Vector2f mouse = {0, 0};

    mouse.x = sf::Mouse::getPosition().x;
    mouse.y = sf::Mouse::getPosition().y - 50.0;

    for (std::map<std::string, Arcade::Lib>::iterator it = _cacheLib.begin(); it != _cacheLib.end(); it++) {

        if (it->second._rectangle.getGlobalBounds().contains(mouse)) {
            return it->first;
        }

    }

    return "";
}

std::string Arcade::SFML::getGame()
{
    sf::Vector2f mouse = {0, 0};
    
    mouse.x = sf::Mouse::getPosition().x;
    mouse.y = sf::Mouse::getPosition().y - 50.0;

    for (std::map<std::string, Arcade::Lib>::iterator it = _cacheGame.begin(); it != _cacheGame.end(); it++) {

        if (it->second._rectangle.getGlobalBounds().contains(mouse)) {
            return it->first;
        }

    }

    return "";
}

std::string Arcade::SFML::getLogin()
{
    sf::Vector2f mouse = {0, 0};

    mouse.x = sf::Mouse::getPosition().x;
    mouse.y = sf::Mouse::getPosition().y - 50.0;

    if (_login._rectangle.getGlobalBounds().contains(mouse)) {
        _login._rectangle.setOutlineThickness(5);
        _loginSelected = true;
    } else {
        _login._rectangle.setOutlineThickness(0);
        _loginSelected = false;
    }

    return "";
}

JSON::JSON Arcade::SFML::getEvents()
{
    JSON::JSON json;
    JSON::JSONArray keys;

    json._values["close"] = false;
    json._values["logout"] = false;
    json._values["graphic"] = "";
    json._values["game"] = "";

    while (_window.pollEvent(_event)) {

        if (_event.type == sf::Event::Closed) {
            json._values["close"] = true;
            _window.close();
        }

        if (_event.type == sf::Event::KeyPressed) {
            if (!_loginSelected && _event.key.code == 11) {
                launcher();
            }
            keys._values.push_back((double)_event.key.code);
            if (_loginSelected && _currentName.length() && _event.key.code == ERASE) {
                _currentName.pop_back();
            }
            if (_loginSelected && _currentName.length() < 20 && 0 <= _event.key.code && _event.key.code < 26) {
                _currentName.append(std::string(1, 'a' + _event.key.code));
            }
            if (_loginSelected && _currentName.length() && _event.key.code == ENTER) {
                json._values["name"] = _currentName;
                _currentName.clear();
            }
            if (_event.key.code == 16) {
                json._values["logout"] = true;
            }
        }

        if (_event.type == sf::Event::MouseButtonPressed) {
            json._values["graphic"] = getLib();
            json._values["game"] = getGame();
            getLogin();
        }

    }

    json._values["keys"] = keys;
    return json;
}
