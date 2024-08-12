/*
** EPITECH PROJECT, 2024
** LibLoader for Arcade
** File description:
** LibLoader
*/

#include <dlfcn.h>
#include <fcntl.h>
#include "IGameLibrary.hpp"
#include "LinuxLoader.hpp"

extern "C" void *dlopen_C(const char *filename, const int flags)
{
	return dlopen(filename, flags);
}

extern "C" void *dlsym_C(void *handle, const char *symbol)
{
	return dlsym(handle, symbol);
}

extern "C" int dlclose_C(void *handle)
{
	return dlclose(handle);
}

extern "C" char *dlerror_C(void)
{
	return dlerror();
}

void Arcade::LinuxLoader::setGameLibrary(const std::string &path)
{
	_gameHandler = dlopen_C(path.c_str(), RTLD_LAZY);

	if (_gameHandler == nullptr)	{
		std::cerr << dlerror_C() << std::endl;
	}
}

void Arcade::LinuxLoader::setGraphicLibrary(const std::string &path)
{
	_graphicHandler = dlopen_C(path.c_str(), RTLD_LAZY);

	if (_graphicHandler == nullptr)	{
		std::cerr << dlerror_C() << std::endl;
	}
}
