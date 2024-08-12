/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** JSON
*/

#ifndef JSON_HPP_
    #define JSON_HPP_

    #define PACMAN_PATH "map/Pacman.map"
    #define NIBBLER_PATH "map/Nibbler.map"

    #define getPLAYER_POS get<JSON::JSONArray>("position").get<JSON::JSON>(0)

    #include <map>
    #include <string>
    #include <vector>
    #include <variant>

    #include <iostream>

namespace JSON {

    class JSON;
    class JSONArray;

    typedef std::variant<std::string, double, bool, JSON, JSONArray> JSONValue;

    class JSON {

        public:

            JSON() = default;
            ~JSON() = default;

            template <typename T>
            T get(const std::string &key) {
                return std::get<T>(_values[key]);
            };

            void dump();

            std::map<std::string, JSONValue> _values;

        private:

            void dump_image(JSON element) const;
            void dump_text(JSON element) const;
            void dump_positions(JSON element) const;

    };

    class JSONArray {

        public:

            JSONArray() = default;
            ~JSONArray() = default;

            void parseMap(const std::string &filepath, char c);

            template <typename T>
            T get(const std::size_t index) {
                return std::get<T>(_values[index]);
            }

            std::vector<JSONValue> _values;

    };

};

#endif /* !JSON_HPP_ */
