/*
** EPITECH PROJECT, 2024
** LibLoader for Arcade
** File description:
** Arcade Proj
*/

#ifndef LIBLOADER_HPP_
    #define LIBLOADER_HPP_

    #include "IDLLoader.hpp"
    #include <dlfcn.h>
    #include <fcntl.h>

extern "C" void *dlsym_C(void *handle, const char *symbol);
extern "C" void *dlopen_C(const char *filename, const int flags);
extern "C" int dlclose_C(void *handle);
extern "C" char *dlerror_C(void);

namespace Arcade {

    class LinuxLoader : public IDLLoader {

        public:

            void setGameLibrary(const std::string &path);
            void setGraphicLibrary(const std::string &path);
    
            template <typename T>
            T *getInstance(void *handler, const std::string &name) {
                auto function = dlsym(handler, name.c_str());
                return reinterpret_cast<T *(*)()>(function);
            }

            void *_gameHandler;
            void *_graphicHandler;

    };
}

#endif /* !LIBLOADER_HPP_ */
