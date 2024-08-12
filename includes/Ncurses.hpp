/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
    #define NCURSES_HPP_

    #include <ncurses.h>

    #include <memory>

    #include "IGraphicLibrary.hpp"

    #define getOUTLINECOLOR(i) get<JSON::JSONArray>("outlineColor").get<double>(i)
    #define getFILLCOLOR(i) get<JSON::JSONArray>("fillColor").get<double>(i)
    #define getRECTANGLE(i) get<JSON::JSONArray>("rectangle").get<double>(i)
    #define getFONTCOLOR(i) get<JSON::JSONArray>("fontColor").get<double>(i)
    #define getSIZE(i) get<JSON::JSONArray>("size").get<double>(i)
    #define getX(i) getPOSITION.get<JSON::JSON>(i).get<double>("x")
    #define getY(i) getPOSITION.get<JSON::JSON>(i).get<double>("y")
    #define getPOSITION get<JSON::JSONArray>("position")
    #define getELEMENTS get<JSON::JSONArray>(ELEMENTS)
    #define getCONTENT get<std::string>("content")
    #define getSTRING get<std::string>("string").c_str()
    #define getFONTSIZE get<double>("fontSize")
    #define getINDEX(i) get<JSON::JSON>(i)
    #define getVALUE get<double>("value")
    #define getTYPE get<double>("type")
    #define getID get<double>("id")

    #define MARGINX 0
    #define MARGINY 0

    #define SPACEX 30
    #define SPACEY 30

    #define ELEMENTS "elements"
    #define SPRITE 0
    #define TEXT 1
    #define SHAPE 2
    #define LIBS 3
    #define GAMES 4
    #define SCORE 5

namespace Arcade {

    class Ncurses : public IGraphicLibrary {

        public:

            Ncurses();
            ~Ncurses();

            JSON::JSON getEvents();
            void display(JSON::JSON data);

        private:

            void updateJSON(JSON::JSON data);

            void displayElement(JSON::JSON element);
            void displaySprite(JSON::JSON sprite);
            void displayText(JSON::JSON text);
            void displayLibs(JSON::JSON libs);
            void displayGames(JSON::JSON games);

            std::map<double, std::string> _cacheText;
            //std::vector<std::string> _cacheLibs;
            //std::vector<std::string> _cacheGames;

            WINDOW *_window;
            WINDOW *_libs;
            WINDOW *_games;
            WINDOW *_header;

            JSON::JSON _json;

    };

};

#endif /* !NCURSES_HPP_ */
