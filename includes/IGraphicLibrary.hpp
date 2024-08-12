/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-edward.lalande
** File description:
** IGraphicLibrary
*/

#ifndef IGRAPHICLIBRARY_HPP_
    #define IGRAPHICLIBRARY_HPP_

    #include "JSON.hpp"

namespace Arcade {

    class IGraphicLibrary {

        public:

            virtual ~IGraphicLibrary() = default;

            virtual JSON::JSON getEvents() = 0;
            virtual void display(JSON::JSON data) = 0;

    };

}

#endif /* !IGRAPHICLIBRARY_HPP_ */
