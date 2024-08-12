/*
** EPITECH PROJECT, 2024
** Arcade core class
** File description:
** Arcade Proj
*/

#include <filesystem>
#include <fstream>

#include "Arcade.hpp"

#define getELEMENTS get<JSON::JSONArray>("elements")

Arcade::Arcade::Arcade(const std::string &lib): _mode(LOGGING)
{
    createMenu();

    _gameLibrary = nullptr;
    _graphicLibrary = nullptr;

    setGraphicLib(lib);

    _name = "MR LALANDE";
}

void Arcade::Arcade::getGraphicLibs()
{
    JSON::JSONArray copy = _data.getELEMENTS;
    JSON::JSONArray array;
    JSON::JSON libs;

    for (const auto &entry : std::filesystem::directory_iterator("lib/")) {

        void *handle = dlopen_C(entry.path().c_str(), RTLD_LAZY);

        bool (*isGame)() = reinterpret_cast<bool (*)()>(dlsym_C(handle, "isGame"));

        if (!isGame()) {
            array._values.push_back(entry.path().c_str());
        }

    }

    libs._values["type"] = 3.0;
    libs._values["libs"] = array;

    copy._values[0] = libs;
    _data._values["elements"] = copy;
}

void Arcade::Arcade::getGames()
{
    JSON::JSONArray copy = _data.getELEMENTS;
    JSON::JSONArray array;
    JSON::JSON libs;

    for (const auto &entry : std::filesystem::directory_iterator("lib/")) {

        void *handle = dlopen_C(entry.path().c_str(), RTLD_LAZY);

        bool (*isGame)() = reinterpret_cast<bool (*)()>(dlsym_C(handle, "isGame"));

        if (isGame()) {
            array._values.push_back(entry.path().c_str());
        }

    }

    libs._values["type"] = 4.0;
    libs._values["libs"] = array;

    copy._values[1] = libs;
    _data._values["elements"] = copy;
}

void Arcade::Arcade::getLeaderBoard(const std::string &game)
{
    JSON::JSONArray copy = _data.getELEMENTS;
    JSON::JSONArray array;
    JSON::JSON leaderBoard;

    std::fstream file(game);
    std::string line;

    for (std::size_t i = 0; i < 10 && !file.eof() && std::getline(file, line); i++) {
        array._values.push_back(line);
    }
    file.close();

    leaderBoard._values["type"] = 5.0;
    leaderBoard._values["scores"] = array;

    copy._values[2] = leaderBoard;
    _data._values["elements"] = copy;
}

void Arcade::Arcade::setScore(const std::string &game, const std::string &name, const double score)
{
    std::fstream file(game, std::ios::in | std::ios::out);
    std::string line;
    std::stringstream temp;
    bool inserted = false;

    while (file.is_open() && std::getline(file, line)) {
        double lineScore = std::atof(line.substr(line.find_last_of(' ') + 1).c_str());
        if (score > lineScore && !inserted) {
            temp << name << " " << score << std::endl;
            inserted = true;
        }
        temp << line << std::endl;
    }

    if (!inserted) {
        temp << name << " " << score << std::endl;
    }

    file.close();
    file.open(game, std::ios::out | std::ios::trunc);
    file << temp.rdbuf();
    file.close();
}

void Arcade::Arcade::setGraphicLib(const std::string &lib)
{
    _dlLoader.setGraphicLibrary(lib);

    IGraphicLibrary *(*library)() = FUNCTION(dlsym_C(_dlLoader._graphicHandler, "createLibrary"));

    if (_graphicLibrary != nullptr) {
        delete _graphicLibrary;
    }

    _graphicLibrary = library();

    if (!_graphicLibrary) {
        std::cerr << dlerror_C() << std::endl;
    }
}

void Arcade::Arcade::setGame(const std::string &game)
{
    _dlLoader.setGameLibrary(game);
    IGameLibrary *(*library)() =
        reinterpret_cast<IGameLibrary *(*)()>(dlsym_C(_dlLoader._gameHandler, "createLibrary"));

    _gameLibrary = library();
    if (!_gameLibrary) {
        std::cerr << dlerror_C() << std::endl;
    }
}
