/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** JSON
*/

#include <fstream>
#include "JSON.hpp"

void JSON::JSONArray::parseMap(const std::string &filepath, char c)
{
    JSON pos;
    std::fstream ifs;
    std::string line;
    double y = 0;

    ifs.open(filepath, std::fstream::in);

    while (!ifs.eof() && std::getline(ifs, line)) {
        for (std::size_t i = 0; i < line.size(); ++i) {

            if (line[i] == c) {
                pos._values["x"] = (double)(i);
                pos._values["y"] = y;
                _values.push_back(pos);
            }

        }

        y++;
    }

}

void JSON::JSON::dump_image(JSON element) const
{
    JSONArray rectangle = element.get<JSONArray>("rectangle");

    std::cout << "  {" << std::endl;
    std::cout << "    \"id\": " << element.get<double>("id") << "," << std::endl;
    std::cout << "    \"type\": " << element.get<double>("type") << "," << std::endl;
    std::cout << "    \"assets\": \"" << element.get<std::string>("assets") << "\" ," << std::endl;
    std::cout << "    \"string\": \"" << element.get<std::string>("string") << "\" ," << std::endl;

    std::cout << "    \"rectangle\": [ ";
    for (std::size_t j = 0; j != 4; j++) {
        std::cout << rectangle.get<double>(j) << (j != 3 ? ", " : "");
    }
    std::cout << " ]," << std::endl;
}

void JSON::JSON::dump_text(JSON element) const
{
    JSONArray fontColor = element.get<JSONArray>("fontColor");
    std::cout << "  {" << std::endl;
    std::cout << "    \"id\": " << element.get<double>("id") << "," << std::endl;
    std::cout << "    \"type\": " << element.get<double>("type") << "," << std::endl;

    std::cout << "    \"content\": \"" << element.get<std::string>("content") << "\" ," << std::endl;
    std::cout << "    \"value\": " << element.get<double>("value") << "," << std::endl;
    std::cout << "    \"fontSize\": " << element.get<double>("fontSize") << "," << std::endl;
    std::cout << "    \"fontFamily\": \"" << element.get<std::string>("fontFamily") << "\" ," << std::endl;

    std::cout << "    \"fontColor\": [ ";
    for (std::size_t j = 0; j != 3; j++) {
        std::cout << fontColor.get<double>(j) << (j != 2 ? ", " : "");
    }
    std::cout << " ]," << std::endl;
}

void JSON::JSON::dump_positions(JSON element) const
{
    JSONArray position = element.get<JSONArray>("position");

    std::cout << "    \"position\": {[" << std::endl;

    for (std::size_t j = 0; j < position._values.size(); j++) {
        JSON pos = position.get<JSON>(j);
        std::cout << "      {" << std::endl;
        std::cout << "          \"x\": " << pos.get<double>("x") << "," <<std::endl;
        std::cout << "          \"y\": " << pos.get<double>("y") << std::endl;
        std::cout << "      }" << (j != position._values.size() - 1 ? "," : "") << std::endl;
    }

    std::cout << "    ]}" << std::endl;
}

void JSON::JSON::dump()
{

    JSONArray array = get<JSONArray>("elements");

    std::cout << "\"elements\": {[" << std::endl;

    for (std::size_t i = 0; i < array._values.size(); i++) {

        JSON element = array.get<JSON>(i);

        if (element.get<double>("type") == 0) {
            dump_image(element);
        } else {
            dump_text(element);
        }
        dump_positions(element);

        std::cout << "  }" << (i != array._values.size() - 1 ? "," : "") << std::endl;
    }

    std::cout << "]}" << std::endl;
}
