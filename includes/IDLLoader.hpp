/*
** EPITECH PROJECT, 2024
** Interface DLLoader
** File description:
** Arcade proj
*/

#ifndef IDLLOADER_HPP_
    #define IDLLOADER_HPP_
    #include "IGameLibrary.hpp"
    #include "IGraphicLibrary.hpp"
    #include <memory>

namespace Arcade {

    class IDLLoader {

        public:

            virtual ~IDLLoader() = default;

            virtual void setGameLibrary(const std::string &path) = 0;
            virtual void setGraphicLibrary(const std::string &path) = 0;

            void *_gameHandler;
            void *_graphicHandler;

    };
}

#endif /* !IDLLOADER_HPP_ */
