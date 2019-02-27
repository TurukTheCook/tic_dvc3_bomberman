##
## ETNA PROJECT, 14/01/2019 (aslani_a, gros_m, ly_m, roule_y)
## Bomberman
## File description:
##      makefile for Bomberman
##

## Variables ##
CC		= gcc
CFLAGS	= -I ./headers -std=c11
RM		= rm -f
NAME	= bomberman
SRC		= $(wildcard ./sources/*.c)
OBJ		= $(SRC:.c=.o)
SDL2	= $(shell sdl2-config --cflags --libs)
#SDL2_CFLAGS := $(shell sdl2-config --cflags)
#SDL2_LDFLAGS := $(shell sdl2-config --libs)

## Rules ##

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L./ -o $(NAME) $(SDL2) -lSDL2_image -lSDL2_ttf

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) $(LIBNAME)

re: fclean all

coco: clean all clean

.PHONY: all clean fclean re coco