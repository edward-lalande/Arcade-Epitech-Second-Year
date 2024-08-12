/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** SDL
*/

#ifndef SDL_HPP_
    #define SDL_HPP_

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
    #include <vector>
    #include "IGraphicLibrary.hpp"

    #define UP 74.0
    #define DOWN 73.0
    #define LEFT 71.0
    #define RIGHT 72.0

    #define getELEMENTS get<JSON::JSONArray>("elements")
    #define getINDEX(i) get<JSON::JSON>(i)
    #define getTYPE get<double>("type")
    #define getID get<double>("id")
    #define getRECTANGLE(i) get<JSON::JSONArray>("rectangle").get<double>(i)
    #define getONEX(i) get<JSON::JSON>(i).get<double>("x")
    #define getONEY(i) get<JSON::JSON>(i).get<double>("y")
    #define getPOSITION get<JSON::JSONArray>("position")
    #define getFONT get<std::string>("fontFamily")
    #define getFONT_SIZE get<double>("fontSize")
    #define getCONTENT get<std::string>("content")
    #define getVALUE get<double>("value")
    #define getCOLOR(i) get<JSON::JSONArray>("fontColor").get<double>(i)

    #define SPACEX 30
    #define SPACEY 30
    #define MARGINX 520
    #define MARGINY 340


namespace Arcade
{
    class SDL : public IGraphicLibrary {

    public:
            SDL();
            ~SDL();

            JSON::JSON getEvents();
            void display(JSON::JSON data);

    private:
        void updateJSON(JSON::JSON data);
        void displaySprite(JSON::JSON sprite);

        SDL_Texture *createTexture(JSON::JSON element);
        SDL_Texture *createText(JSON::JSON element);

        void filledGraphicLibrairies(JSON::JSON libs);
        void filledGamesLibrairies(JSON::JSON games);
        SDL_Window *_window;
        SDL_Renderer* _renderer;

        std::map<double, SDL_Texture *> _cacheTexture;
        std::vector<std::string> _gameAvailable;
        std::vector<std::string> _graphicLibAvailable;
        JSON::JSON _json;
    };

}

#endif /* !SDL_HPP_ */
