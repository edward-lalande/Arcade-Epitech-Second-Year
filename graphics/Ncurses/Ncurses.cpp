/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

extern "C" Arcade::Ncurses *createLibrary()
{
    std::cout << "Ncurses Loaded..." << std::endl;

    return new Arcade::Ncurses;
}

extern "C" bool isGame()
{
    return false;
}

Arcade::Ncurses::Ncurses()
{
    initscr();
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);

    curs_set(false);
    timeout(false);

    _window = newwin(30, 120, 0, 0);
    _games = newwin(24, 76, 4, 40);
}

Arcade::Ncurses::~Ncurses()
{
    endwin();
}
