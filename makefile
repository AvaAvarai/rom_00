OBJ_NAME = rom_00
CC = gcc

OBJS = src/main.c src/common.h

C_FLAGS = `sdl2-config --cflags` -std=c99 -pedantic -Wall -Wextra -Wmissing-declarations
LINKER_FLAGS = `sdl2-config --libs` -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm

.PHONY: all build clean

all: build

build: $(OBJS)
	$(CC) $(OBJS) $(C_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
