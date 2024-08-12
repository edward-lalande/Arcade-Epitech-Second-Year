/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** arcade
*/

#ifndef ARCADE_HPP_
    #define ARCADE_HPP_

    #define NB_ARGS_REQUIRED 2
    #define EXIT_WITH_SUCCESS 0
    #define EXIT_WITH_ERROR 84
    #define PATH_TO_LIB 1

    #define ENTER 58

    #define FUNCTION reinterpret_cast<IGraphicLibrary *(*)()>

    #define getELEMENTS get<JSON::JSONArray>("elements")
    #define getKEYS get<JSON::JSONArray>("keys")
    #define getKEY(i) getKEYS.get<double>(i)

    #define isOpen get<bool>("close") == false
    #define getLOGOUT get<bool>("logout")
    #define getGraphic get<std::string>("graphic")
    #define getGame get<std::string>("game")
    #define getNAME get<std::string>("name")

    #include "IGameLibrary.hpp"
    #include "IGraphicLibrary.hpp"
    #include "LinuxLoader.hpp"
    #include <string>
    #include <memory>

namespace Arcade {

    class Arcade {

        public:

            typedef enum mode_e {

                LOGGING,
                MENU,
                GAME,
                SCORE

            } mode_t;

            Arcade(const std::string &lib);
            ~Arcade() = default;

            int run();
            void setGraphicLib(const std::string &lib);
            void setGame(const std::string &game);

            void createMenu();

            void getGraphicLibs();
            void getGames();
            void getLeaderBoard(const std::string &game);

            void setScore(const std::string &game, const std::string &name, const double score);

            mode_t _mode;

            JSON::JSON _data;
            JSON::JSON _gameData;

            std::string _name;
            std::string _leaderBoard;

            LinuxLoader _dlLoader;
            IGameLibrary *_gameLibrary;
            IGraphicLibrary *_graphicLibrary;

    };

};

#endif /* !ARCADE_HPP_ */