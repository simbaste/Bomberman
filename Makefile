COMP		= g++

EDITOR		= emacs -nw

CFLAGS		= -std=c++11 ##-W -Wall -Wextra -std=c++11 -Wfatal-errors -g3

##CXXFLAGS	= -O3 -ffast-math
CXXFLAGS	= -L./usr/lib ./lib/libIrrKlang.so
INCLUDES	= -I./includes

CPPFLAGS	= -I./includes/irrklang -I./include -I./include/irr/ -I/usr/X11R6/include
LDFLAGS		= -L/usr/X11R6/lib$(LIBSELECT) -L./lib/ -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lXcursor -lpthread

RM		= rm -f

NAME		= indie
NAME_DEBUG	= debug

SRC		= src/Map.cpp		\
		  src/main.cpp		\
		  src/Ia.cpp		\
		  src/Ias.cpp		\
		  src/Iap.cpp		\
		  src/Character.cpp	\
		  src/Game.cpp		\
		  src/Bomb.cpp		\
		  src/Event.cpp		\
		  src/Player.cpp	\
		  src/ThreadPool.cpp	\
		  src/Sound.cpp		\
		  src/Menu.cpp		\
		  src/Excep.cpp		\

DEBUG_SRC	=

OBJ		= $(SRC:.cpp=.o)
DEBUG_OBJ	= $(DEBUG_SRC:.cpp=.o)

ECHO		= echo -e

DEFAULT		= "\033[00m"
GREEN		= "\033[0;32m"
BLUE		= "\033[1;36m"
RED		= "\033[0;31m"

IRRLICHT	= lib/libIrrlicht.a

all: $(NAME)

ifeq ($(HOSTTYPE), x86_64)
LIBSELECT=64
endif

$(IRRLICHT): 
	make -C irrlicht-1.8.3/source/Irrlicht/
	cp irrlicht-1.8.3/lib/Linux/libIrrlicht.a $(IRRLICHT)

install: $(IRRLICHT)

clean_install:
		rm -f $(IRRLICHT)
		make -C irrlicht-1.8.3/source/Irrlicht/ clean

%.o: %.cpp
	@$(COMP) -o $@ -c $< $(CFLAGS) $(LDFLAGS)  $(CPPFLAGS) $(INCLUDES) && \
	 ($(ECHO) $(GREEN) "[OK]" $(BLUE) $@ $(DEFAULT)) || \
	 ($(ECHO) $(RED) "[XX]" $(BLUE) $@ $(DEFAULT))

$(NAME): $(OBJ) $(IRRLICHT)
	@$(COMP) $(OBJ) -o $@ $(CFLAGS) $(LDFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(INCLUDES) && \
	 ($(ECHO) $(GREEN) "[OK]" $(BLUE) $@ $(DEFAULT)) || \
	 ($(ECHO) $(RED) "[XX]" $(BLUE) $@ $(DEFAULT))

clean:
	@$(RM) $(OBJ)
	@$(RM) $(DEBUG_OBJ)
	@$(ECHO) $(BLUE) "Cleaning object files" $(DEFAULT)


fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_DEBUG)
	@$(ECHO) $(BLUE) "Cleaning binary" $(DEFAULT)

re: fclean all

rec: all clean

edit:
	$(EDITOR) $(SRC)


$(NAME_DEBUG): $(DEBUG_OBJ)
		@$(COMP) $(DEBUG_OBJ) -o $@ $(CFLAGS) $(LDFLAGS) $(INCLUDES) && \
		($(ECHO) $(GREEN) "[OK]" $(BLUE) $@ $(DEFAULT)) || \
		($(ECHO) $(RED) "[XX]" $(BLUE) $@ $(DEFAULT))
debugre: fclean $(NAME_DEBUG)

.PHONY: all clean fclean lib re rec edit debugre
