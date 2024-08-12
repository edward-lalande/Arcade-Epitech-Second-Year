/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Display
*/

#include "SFML.hpp"

void Arcade::SFML::displaySprite(JSON::JSON sprite)
{
    sf::Vector2f position = {0, 0};

    if (_cacheSprite.find(sprite.getID) != _cacheSprite.end()) {

        JSON::JSONArray allPositions = sprite.getPOSITION;

        for (std::size_t i = 0; i < allPositions._values.size(); i++) {
            position.x = allPositions.getONEX(i) * SPACEX + MARGINX * (sprite.getID != 100.0);
            position.y = allPositions.getONEY(i) * SPACEY + MARGINY * (sprite.getID != 100.0);
            _cacheSprite[sprite.getID].setPosition(position);
            _window.draw(_cacheSprite[sprite.getID]);
        }
    } else {    
        _cacheSprite[sprite.getID] = createSprite(sprite);
        displaySprite(sprite);        
    }

}

void Arcade::SFML::displayText(JSON::JSON text)
{
    sf::Vector2f position = {0, 0};

    if (_cacheText.find(text.getID) != _cacheText.end()) {

        for (std::size_t i = 0; i < text.getPOSITION._values.size(); i++) {
            position.x = text.getX(i) + MARGINX * (text.getID != 104.0);
            position.y = text.getY(i) + MARGINY * (text.getID != 104.0);
            _cacheText[text.getID].setPosition(position);
            _window.draw(_cacheText[text.getID]);
        }

    } else {
        _cacheText[text.getID] = createText(text);
        displayText(text);
    }
}

void Arcade::SFML::displayShape(JSON::JSON shape)
{
    if (_cacheShape.find(shape.getID) != _cacheShape.end()) {

        _window.draw(_cacheShape[shape.getID]);

    } else {

        _cacheShape[shape.getID] = createShape(shape);
        displayShape(shape);

    }
}

void Arcade::SFML::displayGames(JSON::JSON games)
{
    JSON::JSONArray paths = games.get<JSON::JSONArray>("libs");
    sf::Vector2f mouse = {0, 0};
    double index = 0;

    for (size_t i = 0; i < paths._values.size(); i++) {

        Lib libraries = createLib("Games :");

        libraries._text.setFillColor(sf::Color::White);
        libraries._text.setPosition({580.0, 315.0});
        libraries._text.setCharacterSize(20);

        _window.draw(libraries._text);

        Lib logoutText = createLib("Enter Q to logout...");

        logoutText._text.setFillColor(sf::Color::White);
        logoutText._text.setPosition({1380.0, 315.0});
        logoutText._text.setCharacterSize(20);

        _window.draw(logoutText._text);

        if (_cacheGame.find(paths.get<std::string>(i)) != _cacheGame.end()) {

            index = (i == 4) ? 0 : index; 

            _cacheGame[paths.get<std::string>(i)]._rectangle.setPosition({(float)(580.0 + index * 320.0), (float)(370.0 + 320 * (i > 3))});
            mouse = {(float)sf::Mouse::getPosition().x, (float)(sf::Mouse::getPosition().y - 50.0)};
            if (_cacheGame[paths.get<std::string>(i)]._rectangle.getGlobalBounds().contains(mouse)) {
                _cacheGame[paths.get<std::string>(i)]._rectangle.setFillColor(sf::Color::Green);
            } else {
                _cacheGame[paths.get<std::string>(i)]._rectangle.setFillColor(sf::Color::White);
            }
            _window.draw(_cacheGame[paths.get<std::string>(i)]._rectangle);

            _cacheGame[paths.get<std::string>(i)]._sprite.setPosition({(float)(635.0 + index * 320.0), (float)(410.0 + 320 * (i > 3))});
            _window.draw(_cacheGame[paths.get<std::string>(i)]._sprite);

            _cacheGame[paths.get<std::string>(i)]._text.setPosition({(float)(610.0 + index * 320.0), (float)(590.0 + 320 * (i > 3))});
            _window.draw(_cacheGame[paths.get<std::string>(i)]._text);

            index += 1;

        } else {

            _cacheGame[paths.get<std::string>(i)] = createGame(paths.get<std::string>(i).erase(0, 4).substr(0, 13));

        }

    }
}

void Arcade::SFML::displayLibs(JSON::JSON libs)
{
    JSON::JSONArray paths = libs.get<JSON::JSONArray>("libs");
    sf::Vector2f mouse = {0, 0};

    for (size_t i = 0; i < paths._values.size(); i++) {

        Lib libraries = createLib("Libraries :");

        libraries._text.setFillColor(sf::Color::White);
        libraries._text.setPosition({130.0, 315.0});
        libraries._text.setCharacterSize(20);

        _window.draw(libraries._text);

        if (_cacheLib.find(paths.get<std::string>(i)) != _cacheLib.end()) {

            _cacheLib[paths.get<std::string>(i)]._rectangle.setPosition({70.0, (float)(370.0 + i * 60)});
            mouse = {(float)sf::Mouse::getPosition().x, (float)(sf::Mouse::getPosition().y - 50.0)};
            if (_cacheLib[paths.get<std::string>(i)]._rectangle.getGlobalBounds().contains(mouse)) {
                _cacheLib[paths.get<std::string>(i)]._rectangle.setFillColor(sf::Color::Green);
            } else {
                _cacheLib[paths.get<std::string>(i)]._rectangle.setFillColor(sf::Color::White);
            }
            _window.draw(_cacheLib[paths.get<std::string>(i)]._rectangle);

            _cacheLib[paths.get<std::string>(i)]._sprite.setPosition({90.0, (float)(370.0 + i * 60)});
            _window.draw(_cacheLib[paths.get<std::string>(i)]._sprite);

            _cacheLib[paths.get<std::string>(i)]._text.setPosition({160.0, (float)(390.0 + i * 60)});
            _window.draw(_cacheLib[paths.get<std::string>(i)]._text);
        
        } else {

            _cacheLib[paths.get<std::string>(i)] = createLib(paths.get<std::string>(i).erase(0, 4).substr(0, 20));

        }

    }
}

void Arcade::SFML::displayLeaderBoard(JSON::JSON leaderBoard)
{
    JSON::JSONArray scores = leaderBoard.get<JSON::JSONArray>("scores");

    for (size_t i = 0; i < 9 && i < scores._values.size(); i++) {

        Lib libraries = createLib("LeaderBoard :");

        libraries._text.setFillColor(sf::Color::White);
        libraries._text.setPosition({1080.0, 315.0});
        libraries._text.setCharacterSize(20);

        _window.draw(libraries._text);

        Lib enterPressed = createLib("Press ENTER to continue...");

        enterPressed._text.setFillColor(sf::Color::White);
        enterPressed._text.setPosition({925.0, 920.0});
        enterPressed._text.setCharacterSize(20);

        _window.draw(enterPressed._text);

        if (_cacheScore.find(scores.get<std::string>(i)) != _cacheScore.end()) {

            _cacheScore[scores.get<std::string>(i)]._rectangle.setPosition({900.0, (float)(360.0 + i * 60)});

            _window.draw(_cacheScore[scores.get<std::string>(i)]._rectangle);

            _cacheScore[scores.get<std::string>(i)]._text.setPosition({940.0, (float)(380.0 + i * 60)});
            _window.draw(_cacheScore[scores.get<std::string>(i)]._text);
        
        } else {

            _cacheScore[scores.get<std::string>(i)] = createScore(scores.get<std::string>(i));

        }

    }
}

void Arcade::SFML::displayLogin()
{
    _login._text.setFillColor(sf::Color::Green);
    _login._text.setPosition({885.0, 585.0});
    _login._text.setCharacterSize(20);
    _login._text.setString(_currentName);

    _login._rectangle.setPosition({865.0, 570.0});
    _login._rectangle.setOutlineColor(sf::Color::Green);

    _window.draw(_login._rectangle);
    _window.draw(_login._text);

    Lib enterName = createLib("Enter a name to login...");

    enterName._text.setFillColor(sf::Color::White);
    enterName._text.setPosition({925.0, 520.0});
    enterName._text.setCharacterSize(20);

    _window.draw(enterName._text);

    Lib enterPressed = createLib("Press ENTER to valide...");

    enterPressed._text.setFillColor(sf::Color::White);
    enterPressed._text.setPosition({925.0, 800.0});
    enterPressed._text.setCharacterSize(20);

    _window.draw(enterPressed._text);
}

void Arcade::SFML::displayElement(JSON::JSON element)
{
    if (element.getTYPE == -1) {
        return;
    }

    if (element.getTYPE == SPRITE) {
        displaySprite(element);
    } else if (element.getTYPE == TEXT) {
        displayText(element);
    } else if (element.getTYPE == SHAPE) {
        displayShape(element);
    } else if (element.getTYPE == LIBS) {
        displayLibs(element);
    } else if (element.getTYPE == GAMES) {
        displayGames(element);
    } else {
        displayLeaderBoard(element);
    }
}

void Arcade::SFML::display(JSON::JSON data)
{
    if (data._values.size() == 0) {
        _json._values.clear();
        _cacheSprite.clear();
        _cacheText.clear();
        return;
    }

    if (!_json._values.size()) {
        _json = data;
    } else {
        updateJSON(data);
    }

    _window.clear();

    for (std::size_t i = 3; i < 8; i++) {
        displayElement(_json.getELEMENTS.getINDEX(i));
    }

    if (_json.getELEMENTS.getINDEX(1).getTYPE == -1.0) {
        displayLogin();
    }
    
    displayElement(_json.getELEMENTS.getINDEX(0));
    displayElement(_json.getELEMENTS.getINDEX(1));
    displayElement(_json.getELEMENTS.getINDEX(2));

    for (std::size_t i = 8; i < _json.getELEMENTS._values.size(); i++) {
        displayElement(_json.getELEMENTS.getINDEX(i));
    }


    _window.display();
}
