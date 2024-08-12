##
## EPITECH PROJECT, 2024
## arcade
## File description:
## arcade
##

CXX              =       g++
CXXFLAGS        +=      -std=c++2a -Wall -Wextra -Werror
CPPFLAGS        +=      -iquote $(INC_DIR)
TTFLAGS         =       -lcriterion --coverage
SFMLFLAGS		=		-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SDLFLAGS		=		-Llib -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
NCURSESFLAGS	=		-lncurses

SRC_DIR         =       ./src
GAMES_DIR		=		./games
GRAPHICS_DIR	=		./graphics
INC_DIR         =       ./includes
TEST_DIR        =       ./tests

MAIN            =       $(SRC_DIR)/Main.cpp				\

SRC             =		$(SRC_DIR)/Arcade.cpp			\
						$(SRC_DIR)/CreateMenu.cpp		\
						$(SRC_DIR)/JSON.cpp				\
						$(SRC_DIR)/Run.cpp				\
						$(SRC_DIR)/LinuxLoader.cpp		\

SDL_SRC			=		$(GRAPHICS_DIR)/SDL/SDL.cpp		\
						$(SRC_DIR)/JSON.cpp				\

SDL_OBJ			=		$(SDL_SRC:.cpp=.o)

SFML_SRC		=		$(GRAPHICS_DIR)/SFML/Create.cpp			\
						$(GRAPHICS_DIR)/SFML/Display.cpp		\
						$(GRAPHICS_DIR)/SFML/GetEvents.cpp		\
						$(GRAPHICS_DIR)/SFML/SFML.cpp			\
						$(GRAPHICS_DIR)/SFML/UpdateJSON.cpp		\
						$(GRAPHICS_DIR)/SFML/Launcher.cpp		\
						$(SRC_DIR)/JSON.cpp						\

SFML_OBJ		=		$(SFML_SRC:.cpp=.o)

NCURSES_SRC		=		$(GRAPHICS_DIR)/Ncurses/Ncurses.cpp			\
						$(GRAPHICS_DIR)/Ncurses/UpdateJSON.cpp		\
						$(GRAPHICS_DIR)/Ncurses/Display.cpp			\
						$(GRAPHICS_DIR)/Ncurses/GetEvents.cpp		\
						$(SRC_DIR)/JSON.cpp							\

NCURSES_OBJ		=		$(NCURSES_SRC:.cpp=.o)

PACMAN_SRC		=		$(GAMES_DIR)/pacman/Movement.cpp\
						$(GAMES_DIR)/pacman/Pacman.cpp	\
						$(GAMES_DIR)/pacman/Power.cpp	\
						$(GAMES_DIR)/pacman/Init.cpp	\
						$(GAMES_DIR)/pacman/Ghost.cpp	\
						$(SRC_DIR)/JSON.cpp				\

PACMAN_OBJ		=		$(PACMAN_SRC:.cpp=.o)

NIBBLER_SRC		= 		$(GAMES_DIR)/nibbler/Init.cpp 	\
						$(GAMES_DIR)/nibbler/Nibbler.cpp	\
						$(GAMES_DIR)/nibbler/Movement.cpp	\
						$(GAMES_DIR)/nibbler/UpdateEvent.cpp 	\
						$(GAMES_DIR)/nibbler/GameManagement.cpp \
						$(SRC_DIR)/JSON.cpp						\

NIBBLER_OBJ		=		$(NIBBLER_SRC:.cpp=.o)

SNAKE_SRC		=		$(GAMES_DIR)/snake/Snake.cpp		\
						$(GAMES_DIR)/snake/Init.cpp			\
						$(GAMES_DIR)/snake/Run.cpp			\
						$(GAMES_DIR)/snake/GetElements.cpp	\
						$(SRC_DIR)/JSON.cpp					\

SNAKE_OBJ		=		$(SNAKE_SRC:.cpp=.o)

SRC_TEST        =		$(TEST_DIR)/TestsArcade.cpp		\

SRC_OBJ         =       $(SRC:.cpp=.o)					\
                        $(MAIN:.cpp=.o)

BIN_NAME        =       ./arcade
TEST_NAME       =       ./unit_tests
PACMAN_NAME		=		./lib/arcade_pacman.so
NIBBLER_NAME	=		./lib/arcade_nibbler.so
SNAKE_NAME		=		./lib/arcade_snake.so
SFML_NAME		=		./lib/arcade_sfml.so
SDL_NAME		=		./lib/arcade_sdl2.so
NCURSES_NAME	=		./lib/arcade_ncurses.so

all:  games graphicals core

core: $(SRC_OBJ)
			$(CXX) -o $(BIN_NAME) $(SRC_OBJ)

tests_run: $(SRC_TEST) $(SRC)
		$(CXX) -o $(TEST_NAME) $(SRC) $(SRC_TEST) $(CPPFLAGS) $(CXXFLAGS) $(TTFLAGS)
		./unit_tests

games:	snake pacman snake nibbler

pacman:	CXXFLAGS += -fPIC
pacman:	$(PACMAN_OBJ)
		$(CXX) -shared -o $(PACMAN_NAME) $(PACMAN_OBJ)

snake:	CXXFLAGS += -fPIC
snake:	$(SNAKE_OBJ)
		$(CXX) -shared -o $(SNAKE_NAME) $(SNAKE_OBJ)

nibbler: CXXFLAGS += -fPIC
nibbler: $(NIBBLER_OBJ)
		 $(CXX) -shared -o $(NIBBLER_NAME) $(NIBBLER_OBJ)

graphicals:	sfml ncurses

#sdl: CXXFLAGS += $(SDLFLAGS) -fPIC
#sdl:	$(SDL_OBJ)
#		$(CXX) -shared -o $(SDL_NAME) $(SDL_OBJ) $(SDLFLAGS)

sfml: CXXFLAGS += $(SFMLFLAGS) -fPIC
sfml:	$(SFML_OBJ)
		$(CXX) -shared -o  $(SFML_NAME) $(SFML_OBJ) $(SFMLFLAGS)

ncurses: CXXFLAGS += $(NCURSESFLAGS) -fPIC
ncurses:	$(NCURSES_OBJ)
		$(CXX) -shared -o  $(NCURSES_NAME) $(NCURSES_OBJ) $(NCURSESFLAGS)

coverage: tests_run
		clear
		@ gcovr --exclude "tests/*"

clean:
		@ $(RM) $(SRC_OBJ)
		@ $(RM) $(PACMAN_OBJ)
		@ $(RM) $(SNAKE_OBJ)
		@ $(RM) $(NIBBLER_OBJ)
		@ $(RM) $(SFML_OBJ)
		@ $(RM) $(SDL_OBJ)
		@ $(RM) *.gcda *.gcno
		@ $(RM) vgcore*

fclean: clean
		@ $(RM) $(BIN_NAME)
		@ $(RM) $(TEST_NAME)
		@ $(RM) $(PACMAN_NAME)
		@ $(RM) $(NIBBLER_NAME)
		@ $(RM) $(SNAKE_NAME)
		@ $(RM) $(SFML_NAME)
		@ $(RM) $(SDL_NAME)

re: fclean all

.PHONY: all tests_run coverage clean fclean re games core graphicals snake pacman
