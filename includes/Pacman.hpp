/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
    #define PACMAN_HPP_

    #define WALL_ID 1.0
    #define DOTS_ID 2.0
    #define POWER_ID 3.0
    #define SCORE_ID 4.0
    #define LEVEL_ID 5.0
    #define TIME_ID 6.0

    #define ORANGE_GHOST_ID 8.0
    #define RED_GHOST_ID 9.0
    #define BLUE_GHOST_ID 10.0
    #define PINK_GHOST_ID 11.0

    #define ORANGE_GHOST_PATH "Assets/Pacman/orange_enemy.png"
    #define PINK_GHOST_PATH "Assets/Pacman/pink_enemy.png"
    #define RED_GHOST_PATH "Assets/Pacman/red_enemy.png"
    #define BLUE_GHOST_PATH "Assets/Pacman/blue_enemy.png"

    #define DANEGROUS_GHOST_ASSETS "Assets/Pacman/kill_enemy.png"

    #define PLAYER_ID 7.0

    #define EATING_GHOST_POINT 20.0

    #define NB_GHOST_MIN 8.0
    #define NB_GHOST_MAX 12.0

    #define DEFAULT_ORANGE_POSX 15.0
    #define DEFAULT_ORANGE_POSY 8.0

    #define DEFAULT_BLUE_POSX 14.0
    #define DEFAULT_BLUE_POSY 8.0

    #define DEFAULT_RED_POSX 16.0
    #define DEFAULT_RED_POSY 8.0

    #define DEFAULT_PINK_POSX 17.0
    #define DEFAULT_PINK_POSY 8.0

    #define ELAPSED_TIME_FOR_RED_DEPARTURE 10.0
    #define ELAPSED_TIME_FOR_PINK_DEPARTURE 12.0
    #define ELAPSED_TIME_FOR_ORANGE_DEPARTURE 14.0
    #define ELAPSED_TIME_FOR_BLUE_DEPARTURE 16.0

    #define BEGIN_OF_RED 12
    #define BEGIN_OF_BLUE 13
    #define BEGIN_OF_PINK 14
    #define BEGIN_OF_ORANGE 14

    #define DOTS_SCORE_POINT 10.0

    #define ELAPSED_TIME_FOR_DANGEROUS_GHOST 10

    #define UP 74
    #define DOWN 73
    #define LEFT 71
    #define RIGHT 72

    #define SPAWN_X 17.0
    #define SPAWN_Y 6.0

    #define TP_LEFT_X 0.0
    #define TP_LEFT_Y 7.0
    #define TP_RIGHT_X 31.0
    #define TP_RIGHT_Y 7.0

    #define WALL_CHAR '#'
    #define PACMAN_CHAR 'G'
    #define ORANGE_GHOST_CHAR 'O'
    #define PINK_GHOST_CHAR 'P'
    #define RED_GHOST_CHAR 'R'
    #define BLUE_GHOST_CHAR 'B'
    #define DOTS_CHAR '.'
    #define POWER_CHAR 'o'

    #include <chrono>
    #include <ctime>
    #include "IGameLibrary.hpp"

namespace Arcade
{

    using Starter = std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration>;
    using Counter = std::chrono::_V2::steady_clock::time_point;

    class Pacman : public IGameLibrary {

        public:

            JSON::JSON init();
            JSON::JSON refresh();
            JSON::JSON run(JSON::JSON events);

        private:
            // !--- INIT ---! //
            JSON::JSON initWall() const;
            JSON::JSON initPlayer() const;
            JSON::JSON initOrangeGhost() const;
            JSON::JSON initPinkGhost() const;
            JSON::JSON initRedGhost() const;
            JSON::JSON initBlueGhost() const;
            JSON::JSON initPoint() const;
            JSON::JSON initPower() const;
            JSON::JSON initScore() const;
            JSON::JSON initLevel() const;
            JSON::JSON initTime() const;
            JSON::JSONArray initBaseRectangle() const;

            void setNewPlayerPos(JSON::JSON newPOs);
            JSON::JSON getPlayerPos();

            // !--- MOUVMENT OF THE PLAYER ---! //
            JSON::JSON handleMovement(int key);
            JSON::JSON moveUp(JSON::JSON index);
            JSON::JSON moveDown(JSON::JSON index);
            JSON::JSON moveLeft(JSON::JSON index);
            JSON::JSON moveRight(JSON::JSON index);
            void checkMovementOnMap(JSON::JSON &pos);

            JSON::JSONArray getWallPosition();

            JSON::JSON getElementById(double id);

            JSON::JSONArray changeRectangle();

            void teleportation(JSON::JSON &player);

            // !--- SCORE HANDLING ---! //
            JSON::JSON updateTime();
            JSON::JSON updateDot(JSON::JSON newPlayerPos);
            void updateScore(JSON::JSONArray &copy);
            void eatingPacGum(JSON::JSONArray &arrayTemp);
            JSON::JSON getScore();
            JSON::JSON getNewLevel(int actualLevel);
            int getActualLevel();

            // !--- GHOST INTERACTION HANDLING ---! //
            bool isEating(JSON::JSON newPlayerPos);
            void changeGhostAssets(JSON::JSONArray &arrayTemp);
            void canEatGhost(JSON::JSONArray &arrayTemp, JSON::JSON newPlayerPos);
            void updateEatingScore(JSON::JSONArray &arrayTemp);
            void deletePacGum(JSON::JSONArray &arrayTemp, JSON::JSON newPlayerPos);

            // !--- END FUNCTION ---! //
            bool isPlayerDead(JSON::JSON newPlayerPos);
            bool isFinished();

            // !--- GHOST MOUVEMENT HANDLING ---! //
            JSON::JSON getNewPinkGhostPos(JSON::JSON pos);
            JSON::JSON getNewRedGhostPos(JSON::JSON pos);
            JSON::JSON getNewBlueGhostPos(JSON::JSON pos);
            JSON::JSON getNewOrangeGhostPos(JSON::JSON pos);
            JSON::JSON getGhostPosition(double id);
            bool isGhostAt(JSON::JSON pos, double yourId);
            bool isWall(double x, double y);

            // !--- SET / GET GHOST DESTINATION ---! //
            JSON::JSONArray goToPosRed(JSON::JSON pos, JSON::JSONArray newPosArray);
            JSON::JSONArray goToPosBlue(JSON::JSON pos, JSON::JSONArray newPosArray);
            JSON::JSONArray goToPosOrange(JSON::JSON pos, JSON::JSONArray newPosArray);
            JSON::JSONArray goToPosPink(JSON::JSON pos, JSON::JSONArray newPosArray);

            JSON::JSONArray goToNextRedPos();
            JSON::JSONArray goToNextOrangePos();
            JSON::JSONArray goToNextBluePos();
            JSON::JSONArray goToNextPinkPos();

            bool isInArray(JSON::JSONArray arr, double x, double y);
            bool isInMap(double x, double y);

            JSON::JSONArray _newRedPos;
            JSON::JSONArray _newBluePos;
            JSON::JSONArray _newOrangePos;
            JSON::JSONArray _newPinkPos;

            JSON::JSON _data;
            Starter _chrono;
            Counter _currentTime;
        
            // !--- CLOCK ---! //
            std::clock_t _clock;
            std::clock_t _redGhostClock;
            std::clock_t _blueGhostClock;
            std::clock_t _orangeGhostClock;
            std::clock_t _pinkGhostClock;

            int _lastBlueGet;
            int _lastOrangeGet;
            int _lastPinkGet;

            int _refreshTime;
            int _seconds;
            int _lastKey;
            int _lastTimeEatingGum;
            bool _isGhostInDanger;
            int64_t _elapsedTime;
    };

}

#endif /* !PACMAN_HPP_ */
