/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** SFML
*/

#ifndef SFML_HPP_
    #define SFML_HPP_

    #include <SFML/Graphics.hpp>

    #include <memory>

    #include "IGraphicLibrary.hpp"

    #define getOUTLINECOLOR(i) get<JSON::JSONArray>("outlineColor").get<double>(i)
    #define getFILLCOLOR(i) get<JSON::JSONArray>("fillColor").get<double>(i)
    #define getRECTANGLE(i) get<JSON::JSONArray>("rectangle").get<double>(i)
    #define getFONTCOLOR(i) get<JSON::JSONArray>("fontColor").get<double>(i)
    #define getSIZE(i) get<JSON::JSONArray>("size").get<double>(i)
    #define getX(i) getPOSITION.get<JSON::JSON>(i).get<double>("x")
    #define getY(i) getPOSITION.get<JSON::JSON>(i).get<double>("y")
    #define getONEX(i) get<JSON::JSON>(i).get<double>("x")
    #define getONEY(i) get<JSON::JSON>(i).get<double>("y")
    #define getFONTFAMILY get<std::string>("fontFamily")
    #define getPOSITION get<JSON::JSONArray>("position")
    #define getELEMENTS get<JSON::JSONArray>(ELEMENTS)
    #define getCONTENT get<std::string>("content")
    #define getTEXTURE get<std::string>("assets")
    #define getFONTSIZE get<double>("fontSize")
    #define getINDEX(i) get<JSON::JSON>(i)
    #define getVALUE get<double>("value")
    #define getTYPE get<double>("type")
    #define getID get<double>("id")

    #define ERASE 59
    #define ENTER 58

    #define MARGINX 520
    #define MARGINY 340

    #define SPACEX 30
    #define SPACEY 30

    #define ELEMENTS "elements"
    #define SPRITE 0
    #define TEXT 1
    #define SHAPE 2
    #define LIBS 3
    #define GAMES 4
    #define SCORE 5

    #define getONEX(i) get<JSON::JSON>(i).get<double>("x")
    #define getONEY(i) get<JSON::JSON>(i).get<double>("y")


namespace Arcade {

    class Lib {

        public:

            sf::RectangleShape _rectangle;
            sf::Text _text;
            sf::Font _font;
            sf::Sprite _sprite;
            sf::Texture _texture;

    };

    class SFML : public IGraphicLibrary {

        public:

            SFML();
            ~SFML();

            JSON::JSON getEvents();
            void display(JSON::JSON data);

        private:

            void updateJSON(JSON::JSON data);

            void displayElement(JSON::JSON element);
            void displaySprite(JSON::JSON sprite);
            void displayText(JSON::JSON text);
            void displayShape(JSON::JSON shape);
            void displayLibs(JSON::JSON libs);
            void displayGames(JSON::JSON games);
            void displayLeaderBoard(JSON::JSON games);
            void displayLogin();

            void launcher();
            sf::RectangleShape create(double width, double height, double x, double y);

            sf::Sprite createSprite(JSON::JSON element);
            sf::Text createText(JSON::JSON element);
            sf::RectangleShape createShape(JSON::JSON element);
            Lib createLib(std::string name);
            Lib createGame(std::string name);
            Lib createScore(std::string name);

            std::string getLib();
            std::string getGame();
            std::string getLogin();

            Lib _login;
            bool _loginSelected;

            sf::RenderWindow _window;
            sf::Event _event;

            JSON::JSON _json;

            std::string _currentName;

            std::map<double, sf::RectangleShape> _cacheShape;
            std::map<double, sf::Sprite> _cacheSprite;
            std::map<double, sf::Text> _cacheText;

            std::map<double, sf::Texture> _cacheTexture;
            std::map<double, sf::Font> _cacheFont;

            std::map<std::string, Lib> _cacheLib;
            std::map<std::string, Lib> _cacheGame;
            std::map<std::string, Lib> _cacheScore;

            const std::vector<sf::RectangleShape> _launcher = {

                create(150, 20, 790, 250),
                create(50, 20, 840, 272),
                create(50, 20, 480, 72),
                create(50, 20, 690, 360),
                create(50, 20, 840, 338),
                create(50, 20, 580, 72),
                create(50, 20, 700, 72),
                create(200, 20, 20, 138),
                create(50, 20, 840, 316),
                create(100, 20, 610, 316),
                create(150, 20, 1100, 50),
                create(50, 20, 840, 294),
                create(50, 20, 130, 116),
                create(50, 20, 900, 138),
                create(50, 20, 130, 160),
                create(50, 20, 460, 116),
                create(50, 20, 460, 138),
                create(50, 20, 480, 160),
                create(50, 20, 770, 72),
                create(50, 20, 680, 94),
                create(110, 20, 1120, 182),
                create(100, 20, 80, 50),
                create(120, 20, 60, 72),
                create(50, 20, 570, 360),
                create(110, 20, 500, 50),
                create(50, 20, 470, 294),
                create(50, 20, 40, 94),
                create(50, 20, 130, 94),
                create(60, 20, 340, 116),
                create(130, 20, 360, 338),
                create(50, 20, 20, 116),
                create(50, 20, 580, 160),
                create(50, 20, 690, 338),
                create(50, 20, 900, 72),
                create(50, 20, 130, 182),
                create(100, 20, 260, 138),
                create(110, 20, 900, 50),
                create(60, 20, 360, 182),
                create(50, 20, 1200, 160),
                create(50, 20, 360, 316),
                create(50, 20, 470, 316),
                create(50, 20, 900, 94),
                create(50, 20, 1000, 94),
                create(50, 20, 370, 72),
                create(110, 20, 500, 182),
                create(80, 20, 720, 50),
                create(50, 20, 900, 116),
                create(50, 20, 1020, 116),
                create(50, 20, 790, 160),
                create(50, 20, 680, 182),
                create(130, 20, 360, 250),
                create(50, 20, 790, 94),
                create(50, 20, 680, 116),
                create(50, 20, 1200, 138),
                create(50, 20, 470, 272),
                create(60, 20, 340, 160),
                create(110, 20, 900, 182),
                create(50, 20, 680, 160),
                create(50, 20, 370, 94),
                create(50, 20, 260, 116),
                create(50, 20, 360, 360),
                create(50, 20, 360, 382),
                create(50, 20, 790, 116),
                create(160, 20, 680, 138),
                create(50, 20, 460, 94),
                create(50, 20, 1180, 72),
                create(50, 20, 1000, 138),
                create(50, 20, 980, 160),
                create(50, 20, 900, 160),
                create(110, 20, 590, 382),
                create(50, 20, 840, 360),
                create(50, 20, 840, 382),
                create(130, 20, 260, 50),
                create(150, 20, 570, 250),
                create(50, 20, 650, 272),
                create(50, 20, 630, 294),
                create(100, 20, 260, 138),
                create(50, 20, 260, 160),
                create(50, 20, 360, 272),
                create(50, 20, 260, 182),
                create(50, 20, 1100, 160),
                create(50, 20, 260, 94),
                create(50, 20, 360, 294),
                create(50, 20, 1160, 94),
                create(100, 20, 1140, 116),
                create(50, 20, 980, 72),
                create(50, 20, 790, 182),
                create(50, 20, 260, 72),
                create(150, 20, 1100, 50)

            };

    };

};

#endif /* !SFML_HPP_ */
