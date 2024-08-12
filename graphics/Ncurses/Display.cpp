/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Display
*/

#include "Ncurses.hpp"

void Arcade::Ncurses::displaySprite(JSON::JSON sprite)
{
    double position[2] = {0, 0};

    JSON::JSONArray pos = sprite.getPOSITION;

    for (std::size_t i = 0; i < pos._values.size(); i++) {
        JSON::JSON onePos = pos.get<JSON::JSON>(i);
        position[0] = onePos.get<double>("x") + 2;
        position[1] = onePos.get<double>("y") + 3;
        mvwprintw(_games, position[1], position[0], sprite.getSTRING);
    }
}

void Arcade::Ncurses::displayText(JSON::JSON text)
{
    double position[2] = {0, 0};

    for (std::size_t i = 0; i < text.getPOSITION._values.size(); i++) {
        position[0] = text.getX(i) / 720 * 58 + 2;
        position[1] = text.getY(i) + 41;
        if (text.getVALUE == -1) {
            mvwprintw(_games, position[1], position[0], text.getCONTENT.c_str());
        } else {
            mvwprintw(_games, position[1], position[0], (text.getCONTENT + " " + std::to_string(text.getVALUE)).c_str());
        }
    }
}

void Arcade::Ncurses::displayLibs(JSON::JSON libs)
{
    JSON::JSONArray paths = libs.get<JSON::JSONArray>("libs");

    //_cacheLibs.clear();

    WINDOW *window = newwin(24, 34, 4, 4);

    werase(window);
    box(window, 0, 0);
    mvwprintw(window, 1, 12, "Libraries:");
    wrefresh(window);

    for (size_t i = 0; i < 7 && i < paths._values.size(); i++) {

        //_cacheLibs.push_back(paths.get<std::string>(i));

        WINDOW *lib = newwin(3, 30, 6 + i * 3, 6);
        WINDOW *square = newwin(3, 5, 6 + i * 3, 6);

        werase(lib);
        box(lib, 0, 0);
        mvwprintw(lib, 1, 7, paths.get<std::string>(i).substr(0, 20).c_str());
        wrefresh(lib);
        werase(square);
        box(square, 0, 0);
        mvwprintw(square, 1, 2, std::string(1, 'A' + i).c_str());
        wrefresh(square);

    }

}

void Arcade::Ncurses::displayGames(JSON::JSON games)
{
    JSON::JSONArray paths = games.get<JSON::JSONArray>("libs");
    double index = 0;

    //_cacheGames.clear();

    WINDOW *window = newwin(24, 76, 4, 40);

    werase(window);
    if (paths._values.size() != 0) {
        box(window, 0, 0);
        mvwprintw(window, 1, 2, "Games:");
        mvwprintw(window, 1, 54, "Enter Q to logout...");
    }
    wrefresh(window);

    for (size_t i = 0; i < 6 && i < paths._values.size(); i++) {

        //_cacheGames.push_back(paths.get<std::string>(i));

        index = (i == 3) ? 0 : index;

        WINDOW *lib = newwin(7, 35, 6 + index * 7, 42 + 37 * (i >= 3));
        WINDOW *square = newwin(3, 5, 8 + index * 7, 45 + 37 * (i >= 3));

        werase(lib);
        box(lib, 0, 0);
        mvwprintw(lib, 3, 10, paths.get<std::string>(i).substr(0, 22).c_str());
        wrefresh(lib);
        werase(square);
        box(square, 0, 0);
        mvwprintw(square, 1, 2, std::string(1, 'H' + i).c_str());
        wrefresh(square);

        index += 1;

    }

}

void Arcade::Ncurses::displayElement(JSON::JSON element)
{
    if (element.getTYPE == -1) {
        return;
    }
    if (element.getTYPE == SPRITE) {
        displaySprite(element);
    } else if (element.getTYPE == TEXT) {
        displayText(element);
    } else if (element.getTYPE == LIBS) {
        displayLibs(element);
    } else if (element.getTYPE == GAMES) {
        displayGames(element);
    }
}

void Arcade::Ncurses::display(JSON::JSON data)
{
    if (data._values.size() == 0) {
        _json._values.clear();
        return;
    }

    if (!_json._values.size()) {
        _json = data;
    } else {
        updateJSON(data);
    }

    werase(stdscr);

    werase(_window);
    box(_window, 0, 0);

    wrefresh(_window);

    WINDOW *window = newwin(3, 112, 1, 4);

    werase(window);
    box(window, 0, 0);
    mvwprintw(window, 1, 50, "4RCAD3 P3T");
    wrefresh(window);

    displayElement(_json.getELEMENTS.getINDEX(0));
    displayElement(_json.getELEMENTS.getINDEX(1));

    if (_json.getELEMENTS._values.size() > 8) {

        werase(_games);
        box(_games, 0, 0);
        for (std::size_t i = 8; i < _json.getELEMENTS._values.size(); i++) {
            displayElement(_json.getELEMENTS.getINDEX(i));
        }
        wrefresh(_games);
    }

    napms(60);
}
