/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** SDL
*/

#include <array>
#include <sstream>
#include <SDL2/SDL_image.h>
#include "ArcadeSDL.hpp"

extern "C" Arcade::IGraphicLibrary *createLibrary()
{
    return new Arcade::SDL;
}

extern "C" bool isGame()
{
    return false;
}

void Arcade::SDL::updateJSON(JSON::JSON data)
{
    JSON::JSONArray copy = _json.getELEMENTS;
    JSON::JSONArray elements = data.getELEMENTS;
    bool isPassed = false;

    for (std::size_t i = 0; i < 8; i++) {
        copy._values[i] = elements._values[i];
    }

    for (std::size_t i = 8; i < elements._values.size(); i++) {
        isPassed = false;
        for (std::size_t j = 8; j < copy._values.size(); j++) {
            if (elements.getINDEX(i).getID == copy.getINDEX(j).getID) {
                isPassed = true;
                copy._values[j] = elements.getINDEX(i);
                _cacheTexture.erase(elements.getINDEX(i).getID);
                break;
            }
        }
        if (!isPassed) {
            copy._values.push_back(elements.getINDEX(i));
        }
    }
    _json._values["elements"] = copy;
}

Arcade::SDL::SDL()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    _window = SDL_CreateWindow("SDL2",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    1920, 1080,
                                    0);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}

Arcade::SDL::~SDL()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

JSON::JSON Arcade::SDL::getEvents()
{
    JSON::JSON event;
    JSON::JSONArray keys;

    SDL_Event e;
    SDL_PollEvent(&e);
    if (e.type == SDL_QUIT) {
        event._values["close"] = true;
        SDL_Quit();
        return event;
    }

    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_DOWN) {
            keys._values.push_back(UP);
        }
        if (e.key.keysym.sym == SDLK_UP) {
            keys._values.push_back(DOWN);
        }
        if (e.key.keysym.sym == SDLK_LEFT) {
            keys._values.push_back(LEFT);
        }
        if (e.key.keysym.sym == SDLK_RIGHT) {
            keys._values.push_back(RIGHT);
        }
        if (e.key.keysym.scancode == SDL_SCANCODE_P && !_graphicLibAvailable.empty()) {
            event._values["graphic"] = _graphicLibAvailable.front();
        }
        if (e.key.keysym.scancode == SDL_SCANCODE_G && !_gameAvailable.empty()) {
            event._values["game"] = _gameAvailable.front();
        }

    }

    event._values["close"] = false;
    event._values["keys"] = keys;
    SDL_UpdateWindowSurface(_window);
    return event;
}

SDL_Texture *Arcade::SDL::createText(JSON::JSON element)
{
    std::string content (element.getCONTENT);
    std::stringstream stream;
    int r = (int)element.get<JSON::JSONArray>("fontColor").get<double>(0);
    int g = (int)element.get<JSON::JSONArray>("fontColor").get<double>(1);
    int b = (int)element.get<JSON::JSONArray>("fontColor").get<double>(2);

    stream << element.getVALUE;
    content = content + " ";
    content.append(stream.str());
    TTF_Font *font = TTF_OpenFont(element.getFONT.c_str(), 10);
    SDL_Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    SDL_Surface *sprite = TTF_RenderText_Solid(font, content.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, sprite);

    SDL_FreeSurface(sprite);

    return texture;
}

SDL_Texture *Arcade::SDL::createTexture(JSON::JSON element)
{
    SDL_Surface *sprite = IMG_Load(element.get<std::string>("assets").c_str());
    if (!sprite) {
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, sprite);
    SDL_FreeSurface(sprite);

    return texture;
}

void Arcade::SDL::filledGraphicLibrairies(JSON::JSON libs)
{
    JSON::JSONArray paths = libs.get<JSON::JSONArray>("libs");

    if (!_graphicLibAvailable.empty()) {
        _graphicLibAvailable.clear();
    }
    for (std::size_t i = 0; i < paths._values.size(); ++i) {
        _graphicLibAvailable.push_back(paths.get<std::string>(i));
    }
}

void Arcade::SDL::filledGamesLibrairies(JSON::JSON games)
{
    JSON::JSONArray paths = games.get<JSON::JSONArray>("games");

    if (!_graphicLibAvailable.empty()) {
        _graphicLibAvailable.clear();
    }
    for (std::size_t i = 0; i < paths._values.size(); ++i) {
        _graphicLibAvailable.push_back(paths.get<std::string>(i));
    }
}

void Arcade::SDL::displaySprite(JSON::JSON sprite)
{
    if (_cacheTexture.find(sprite.getID) == _cacheTexture.end()) {
        if (sprite.get<double>("type") == 0.0) {
            _cacheTexture[sprite.getID] = createTexture(sprite);
        } else if (sprite.get<double>("type") == 1.0) {
            _cacheTexture[sprite.getID] = createText(sprite);
        }
    }
    double x = 0;
    double y = 0;

    for (std::size_t i = 0; i < sprite.getPOSITION._values.size(); ++i) {
        x = sprite.getPOSITION.get<JSON::JSON>(i).get<double>("x") * SPACEX + MARGINX ;
        y = sprite.getPOSITION.get<JSON::JSON>(i).get<double>("y") * SPACEY + MARGINY;
        if (sprite.get<double>("type") == 0.0) {
            SDL_Rect destinationRect = { static_cast<int>(x), static_cast<int>(y), 30, 30 };
            SDL_Rect srcRect = {0, 0, 30, 30};
            SDL_RenderCopy(_renderer, _cacheTexture[sprite.getID], &srcRect, &destinationRect);
        } else if (sprite.get<double>("type") == 1.0) {
            SDL_Rect destinationRect = { static_cast<int>(x), static_cast<int>(y), 70, 20 };
            SDL_RenderCopy(_renderer, _cacheTexture[sprite.getID], nullptr, &destinationRect);
        }
    }
}

void Arcade::SDL::display(JSON::JSON data)
{
    try {
        if (data._values.size() == 0) {
            _json._values.clear();
            _cacheTexture.clear();
            return;
        }

        if (_json._values.empty()) {
            _json = data;
        } else {
            updateJSON(data);
        }

        SDL_RenderClear(_renderer);
        for (std::size_t i = 0; i < _json.getELEMENTS._values.size(); ++i) {
            if (_json.getELEMENTS.getINDEX(i).getTYPE == 3.0) {
                filledGraphicLibrairies(_json.getELEMENTS.getINDEX(i));
            }
            if (_json.getELEMENTS.getINDEX(i).getTYPE == 4.0) {
                filledGamesLibrairies(_json.getELEMENTS.getINDEX(i));
            }
            if (_json.getELEMENTS.getINDEX(i).getTYPE == 0.0 || _json.getELEMENTS.getINDEX(i).getTYPE == 1.0) {        
                displaySprite(_json.getELEMENTS.getINDEX(i));
            }
        }

        SDL_RenderPresent(_renderer);
        SDL_Delay(1);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
