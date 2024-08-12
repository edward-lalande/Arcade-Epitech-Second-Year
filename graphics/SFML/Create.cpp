/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Create
*/

#include "SFML.hpp"

sf::Sprite Arcade::SFML::createSprite(JSON::JSON element)
{
    sf::IntRect rectangle;
    sf::Sprite sprite;

    _cacheTexture[element.getID].loadFromFile(element.getTEXTURE);

    rectangle.left = element.getRECTANGLE(0);
    rectangle.top = element.getRECTANGLE(1);
    rectangle.width = element.getRECTANGLE(2);
    rectangle.height = element.getRECTANGLE(3);

    sprite.setTexture(_cacheTexture[element.getID]);
    sprite.setTextureRect(rectangle);

    return sprite;
}

sf::Text Arcade::SFML::createText(JSON::JSON element)
{
    sf::Text text;
    sf::Font font;
    sf::Color color;

    color.r = element.getFONTCOLOR(0);
    color.g = element.getFONTCOLOR(1);
    color.b = element.getFONTCOLOR(2);

    _cacheFont[element.getID].loadFromFile(element.getFONTFAMILY);

    if (element.getVALUE == -1) {
        text.setString(element.getCONTENT);
    } else {
        text.setString(element.getCONTENT + " " + std::to_string((int)element.getVALUE));
    }

    text.setFont(_cacheFont[element.getID]);
    text.setFillColor(color);
    text.setStyle(sf::Text::Bold);
    text.setCharacterSize(element.getFONTSIZE);

    return text;
}

sf::RectangleShape Arcade::SFML::createShape(JSON::JSON element)
{
    sf::Vector2f size;
    sf::Color fillColor;
    sf::Vector2f position;
    sf::Color outlineColor;
    sf::RectangleShape shape;

    size.x = element.getSIZE(0);
    size.y = element.getSIZE(1);

    position.x = element.getX(0);
    position.y = element.getY(0);

    fillColor.r = element.getFILLCOLOR(0);
    fillColor.g = element.getFILLCOLOR(1);
    fillColor.b = element.getFILLCOLOR(2);
    fillColor.a = element.getFILLCOLOR(3);

    outlineColor.r = element.getOUTLINECOLOR(0);
    outlineColor.g = element.getOUTLINECOLOR(1);
    outlineColor.b = element.getOUTLINECOLOR(2);
    outlineColor.a = element.getOUTLINECOLOR(3);

    shape.setSize(size);
    shape.setPosition(position);
    shape.setOutlineThickness(4);
    shape.setFillColor(fillColor);
    shape.setOutlineColor(outlineColor);

    return shape;
}

Arcade::Lib Arcade::SFML::createLib(std::string name)
{
    Lib lib;

    lib._rectangle.setSize((sf::Vector2f){330, 50});
    lib._rectangle.setFillColor(sf::Color::White);

    _cacheTexture[444].loadFromFile("Assets/folder.png");

    lib._sprite.setTexture(_cacheTexture[444]);

    _cacheFont[444].loadFromFile("Assets/Fonts/ARCADE_I.ttf");

    lib._text.setString(name);
    lib._text.setFont(_cacheFont[444]);
    lib._text.setFillColor(sf::Color::Black);
    lib._text.setStyle(sf::Text::Bold);
    lib._text.setCharacterSize(10);

    return lib;
}

Arcade::Lib Arcade::SFML::createGame(std::string name)
{
    Lib lib;

    lib._rectangle.setSize((sf::Vector2f){260, 260});
    lib._rectangle.setFillColor(sf::Color::White);

    _cacheTexture[445].loadFromFile("Assets/game.png");

    lib._sprite.setTexture(_cacheTexture[445]);

    _cacheFont[445].loadFromFile("Assets/Fonts/ARCADE_I.ttf");

    lib._text.setString(name);
    lib._text.setFont(_cacheFont[445]);
    lib._text.setFillColor(sf::Color::Black);
    lib._text.setStyle(sf::Text::Bold);
    lib._text.setCharacterSize(15);

    return lib;
}

Arcade::Lib Arcade::SFML::createScore(std::string name)
{
    Lib score;

    score._rectangle.setSize((sf::Vector2f){600.0, 50.0});
    score._rectangle.setFillColor(sf::Color::White);

    _cacheFont[445].loadFromFile("Assets/Fonts/ARCADE_I.ttf");

    score._text.setString(name);
    score._text.setFont(_cacheFont[445]);
    score._text.setFillColor(sf::Color::Black);
    score._text.setStyle(sf::Text::Bold);
    score._text.setCharacterSize(15);

    return score;
}