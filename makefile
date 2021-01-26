OBJ_NAME = rom_00
CC = gcc

OBJS = src/*

C_FLAGS = `sdl2-config --cflags` -std=c99 -pedantic -Wall -Wextra -Wmissing-declarations
LINKER_FLAGS = `sdl2-config --libs` -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm

DEBUG_OBJ_NAME = debug_$(OBJ_NAME)
DEBUG_FLAGS = -mconsole

.PHONY: all build clean debug

all: build

build: $(OBJS)
	$(CC) $(OBJS) $(C_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

debug: $(OBJS)
	$(CC) $(OBJS) $(C_FLAGS) $(DEBUG_FLAGS) $(LINKER_FLAGS) -o $(DEBUG_OBJ_NAME)

clean:
	rm $(OBJ_NAME) $(DEBUG_OBJ_NAME)
