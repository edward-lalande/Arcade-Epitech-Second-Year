/*
** EPITECH PROJECT, 2024
** Nibbler Game Class
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
    #define NIBBLER_HPP_
    #define WALL_ID 1.0
    #define HEAD_ID 2.0
    #define BODY_ID 3.0
    #define FRUITS_ID 4.0
    #define SCORE_ID 5.0
    #define TIME_ID 6.0
    #define LEVEL_ID 7.0

    #define UP 73
    #define DOWN 74
    #define LEFT 71
    #define RIGHT 72

    #define NIB_FONT "Assets/Fonts/ARCADE_I.ttf"
    #define WALL_C '#'

    #include "IGameLibrary.hpp"
    #include <string>
    #include <ctime>

namespace Arcade {

    class Nibbler : public IGameLibrary {

        public:
            enum Direction { up,
                            down,
                            left,
                            right,
                            null
                        };

            JSON::JSON init();
            JSON::JSON refresh();
            JSON::JSON run(JSON::JSON events);

        private:

//          ----   init du jeu   ----

            JSON::JSON _data;
            JSON::JSON initWall();
            JSON::JSON initHead();
            JSON::JSON initBody();
            JSON::JSON initFruits();
            JSON::JSON initScore();
            JSON::JSON initTime() const;
            JSON::JSON initLevel() const;

//          ---- gameManagement du jeu ----

            bool isOpenW(double X, double Y);
            JSON::JSONArray GameManagement();
            double checkKey(JSON::JSON &events);
            bool movingManagement(double intput);
            Direction NibDir(double key);
            void loadWallPos();
            void loadFruitPos();
            bool canPass(double X, double Y);
            bool isTcorner();
            bool nibAutoTurn();
            bool isReturn();
            bool checkEnd();

//          ---- update in game ----

            JSON::JSON refreshHead();
            JSON::JSON refreshBody();
            JSON::JSON refreshScore();
            JSON::JSON refreshLevel();
            JSON::JSON refreshTime();
            JSON::JSON refreshFruits();

            std::string changeHead(Direction _dir);
            bool isEating();
            bool canTurn(double key);
            std::pair<double, double> addBody();

//          ---- var ----

            Direction _dir = right;

            bool _freeze;
            bool _wavesEnd;

            std::clock_t _clock;
            std::clock_t _gameTime;

            JSON::JSONArray _cpyWall;
            JSON::JSONArray _cpyFruit;

//          ---- value in game ----

            double _key;
            double _score;
            double _lastKey;
            double _waves;
            std::size_t _speed;
            std::size_t _fruitsCount;

            std::vector<std::pair<double, double>> _nibPos;
            std::vector<std::pair<double, double>> _fruitsPos;
            std::vector<std::pair<double, double>> _WallPos;

    };
}

#endif /* !NIBBLER_HPP_ */
