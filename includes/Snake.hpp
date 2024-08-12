/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
    #define SNAKE_HPP_

    #include <ctime>

    #include "IGameLibrary.hpp"

    #define getKEYS get<JSON::JSONArray>("keys")
    #define getKEY(i) get<JSON::JSONArray>("keys").get<double>(i)

    #define DIRECTION_LEFT "Assets/Snake/head_left.png"
    #define DIRECTION_RIGHT "Assets/Snake/head_right.png"
    #define DIRECTION_UP "Assets/Snake/head_up.png"
    #define DIRECTION_DOWN "Assets/Snake/head_down.png"

    #define SNAKE_PATH "map/Snake.map"

    #define LEFT 71
    #define RIGHT 72
    #define UP 73
    #define DOWN 74


    #define XMIN 0
    #define XMAX 44

    #define YMIN 0
    #define YMAX 20

namespace Arcade
{

    class Snake : public IGameLibrary{

        public:

            JSON::JSON init();
            JSON::JSON refresh();
            JSON::JSON run(JSON::JSON events);

        private:

            JSON::JSON initWall() const;
            JSON::JSON initHead() const;
            JSON::JSON initBody() const;
            JSON::JSON initApple() const;
            JSON::JSON initScore() const;
            JSON::JSON initTime() const;
            JSON::JSON initBackground() const;

            JSON::JSON getHead();
            JSON::JSON getBody();
            JSON::JSON getApple();
            JSON::JSON getScore();
            JSON::JSON getTime();

            std::pair<double, double> getTailPosition();
            bool isOccuped(std::pair<double, double> position);

            bool move();
            bool checkApple();
            bool checkEnd();

            double _score;

            double _key;
            double _lastKey;

            JSON::JSON _data;

            std::clock_t _clock;
            std::clock_t _globalClock;
            std::string _direction;

            std::pair<double, double> _apple;
            std::vector<std::pair<double, double>> _positions;

    };

}

#endif /* !SNAKE_HPP_ */
