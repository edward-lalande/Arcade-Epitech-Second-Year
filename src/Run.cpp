/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** Run
*/

#include "Arcade.hpp"

int Arcade::Arcade::run()
{
    JSON::JSON events = _graphicLibrary->getEvents();

    while (events.isOpen) {

        getGraphicLibs();

        if (_mode == LOGGING) {

            JSON::JSONArray array = _data.getELEMENTS;
            JSON::JSON score;
            JSON::JSON games;

            score._values["type"] = 5.0;
            score._values["scores"] = JSON::JSONArray();

            games._values["type"] = -1.0;
            games._values["libs"] = JSON::JSONArray();

            array._values[1] = games;
            array._values[2] = score;

            _data._values["elements"] = array;

            _graphicLibrary->display(_data);

            if (events.getNAME != "") {
                _mode = MENU;
                _name = events.getNAME;
                _graphicLibrary->display(JSON::JSON());
                return run();
            }

            if (events.getGraphic != "") {
                setGraphicLib(events.getGraphic);
                return run();
            }

        }

        if (_mode == MENU) {

            JSON::JSONArray array = _data.getELEMENTS;
            JSON::JSON score;

            score._values["type"] = 5.0;
            score._values["scores"] = JSON::JSONArray();

            array._values[2] = score;
            _data._values["elements"] = array;

            getGames();
            _graphicLibrary->display(_data);
            
            if (events.getGraphic != "") {
                setGraphicLib(events.getGraphic);
                return run();
            }

            if (events.getGame != "") {
                setGame(events.getGame);
                _leaderBoard = events.getGame.erase(0, 4);
                _leaderBoard.pop_back();
                _leaderBoard.pop_back();
                _leaderBoard.pop_back();
                _leaderBoard.append("_scores.txt");
                _gameData = _gameLibrary->init();
                _mode = GAME;
                return run();
            }

            if (events.getLOGOUT) {
                _mode = LOGGING;
                return run();
            }

        }

        if (_mode == GAME) {
            JSON::JSON json;
            JSON::JSONArray data = _data.getELEMENTS;
            JSON::JSONArray game = _gameData.getELEMENTS;
            JSON::JSON games;

            games._values["type"] = 4.0;
            games._values["libs"] = JSON::JSONArray();

            for (std::size_t i = 0; i < game._values.size(); i++) {
                data._values.push_back(game._values[i]);
            }

            data._values[1] = games;
            json._values["elements"] = data;

            _graphicLibrary->display(json);

            _gameData = _gameLibrary->run(events);
            if (_gameData.get<bool>("isFinished")) {
                _mode = SCORE;
                setScore("scores/" + _leaderBoard, _name, _gameData.getELEMENTS.get<JSON::JSON>(0).get<double>("value"));
                _gameData._values.clear();
                _graphicLibrary->display(JSON::JSON());
                return run();
            }

            if (events.getGraphic != "") {
                setGraphicLib(events.getGraphic);

                JSON::JSON json;
                JSON::JSONArray data = _data.getELEMENTS;
                JSON::JSONArray game = _gameLibrary->refresh().getELEMENTS;

                JSON::JSON games;

                games._values["type"] = 4.0;
                games._values["libs"] = JSON::JSONArray();

                for (std::size_t i = 0; i < game._values.size(); i++) {
                    data._values.push_back(game._values[i]);
                }

                data._values[1] = games;
                json._values["elements"] = data;
                _graphicLibrary->display(json);

                return run();
            }

        }

        if (_mode == SCORE) {

            JSON::JSONArray array = _data.getELEMENTS;
            JSON::JSON games;

            games._values["type"] = 4.0;
            games._values["libs"] = JSON::JSONArray();

            array._values[1] = games;
            _data._values["elements"] = array;

            getLeaderBoard("scores/" + _leaderBoard);
            _graphicLibrary->display(_data);

            if (events.getGraphic != "") {
                setGraphicLib(events.getGraphic);
                return run();
            }

            if (events.getKEYS._values.size() != 0 && events.getKEY(0) == ENTER) {
                _mode = MENU;
                _graphicLibrary->display(JSON::JSON());
                return run();
            }

        }

        events = _graphicLibrary->getEvents();

    }

    return EXIT_SUCCESS;
}
