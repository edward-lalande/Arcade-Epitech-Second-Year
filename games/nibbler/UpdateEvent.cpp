/*
** EPITECH PROJECT, 2024
** updateGame in nibbler
** File description:
** Arcade Proj
*/

#include "Nibbler.hpp"

std::string Arcade::Nibbler::changeHead(Direction _dir)
{
    std::string ret;

    if (_dir == left) {
        ret = "Assets/Nibbler/NibblerHeadL.png";
    }
    if (_dir == up) {
        ret = "Assets/Nibbler/NibblerHeadU.png";
    }
    if (_dir == down) {
        ret = "Assets/Nibbler/NibblerHeadD.png";
    }
    if (_dir == right) {
        ret = "Assets/Nibbler/NibblerHeadR.png";
    }
    return ret;
}

std::pair<double, double> Arcade::Nibbler::addBody()
{
    std::pair<double, double> postQ = _nibPos[_nibPos.size() - 2];
    std::pair<double, double> Q = _nibPos[_nibPos.size() - 1];

    if (postQ.second == Q.second) {
        if (postQ.first < Q.first) {
            return std::make_pair(Q.first + 1, Q.second);
        }
    }
    std::make_pair(Q.first - 1, Q.second);

    if (postQ.first < Q.first)
        return std::make_pair(Q.first, Q.second + 1);
    return std::make_pair(Q.first, Q.second - 1);
}

JSON::JSON Arcade::Nibbler::refreshHead()
{
    JSON::JSON info;
    JSON::JSONArray pos;
    JSON::JSONArray rectangle;

    std::string head = changeHead(_dir);

    JSON::JSON position;
    position._values["x"] = _nibPos.at(0).first;
    position._values["y"] = _nibPos.at(0).second;
    pos._values.push_back(position);

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

JSON::JSON Arcade::Nibbler::refreshBody()
{
    JSON::JSON info;
    JSON::JSONArray pos;
    JSON::JSONArray rectangle;
    const std::string body = "Assets/Nibbler/NibblerBody.png";

    for (std::size_t i = 1; i < _nibPos.size(); ++i) {
        JSON::JSON position;
        position._values["x"] = _nibPos.at(i).first;
        position._values["y"] = _nibPos.at(i).second;
        pos._values.push_back(position);
    }

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

JSON::JSON Arcade::Nibbler::refreshFruits()
{
    JSON::JSON info;
    JSON::JSONArray pos;
    JSON::JSONArray rectangle;
    const std::string fruit = "Assets/Nibbler/NibblerFruit.png";

    for (std::size_t i = 1; i < _fruitsPos.size(); ++i) {
        JSON::JSON position;
        position._values["x"] = _fruitsPos.at(i).first;
        position._values["y"] = _fruitsPos.at(i).second;
        pos._values.push_back(position);
    }

    rectangle._values.push_back(0.0);
    rectangle._values.push_back(0.0);
    rectangle._values.push_back(30.0);
    rectangle._values.push_back(30.0);

    info._values["type"] = 0.0;
    info._values["assets"] = fruit;
    info._values["id"] = FRUITS_ID;
    info._values["rectangle"] = rectangle;
    info._values["string"] = std::string(".");
    info._values["position"] = pos;
    return info;
}

JSON::JSON Arcade::Nibbler::refreshScore()
{
    JSON::JSON info;
    JSON::JSON position;
    JSON::JSONArray pos;

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

JSON::JSON Arcade::Nibbler::refreshTime()
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
    info._values["value"] = (double)(std::clock() - _gameTime) / CLOCKS_PER_SEC;
    info._values["fontSize"] = 22.0;
    info._values["fontFamily"] = NIB_FONT;
    info._values["fontColor"] = pos;
    pos._values.clear();
    pos._values.push_back(position);
    info._values["position"] = pos;

    return info;
}

JSON::JSON Arcade::Nibbler::refreshLevel()
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
    info._values["value"] = _waves += 1;
    info._values["fontSize"] = 30.0;
    info._values["fontFamily"] = NIB_FONT;
    info._values["fontColor"] = pos;
    pos._values.clear();
    pos._values.push_back(position);
    info._values["position"] = pos;

    return info;
}
