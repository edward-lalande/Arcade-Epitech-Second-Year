/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** IGameLibrary
*/

#ifndef IGAMELIBRARY_HPP_
    #define IGAMELIBRARY_HPP_

    #include "JSON.hpp"

namespace Arcade {

    class IGameLibrary {

        public:

            virtual ~IGameLibrary() = default;

            virtual JSON::JSON init() = 0;
            virtual JSON::JSON refresh() = 0;
            virtual JSON::JSON run(JSON::JSON events) = 0;

    };

};

#endif /* !IGAMELIBRARY_HPP_ */
