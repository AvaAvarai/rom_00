OBJ_NAME = rom_00
DEBUG_OBJ_NAME = debug_$(OBJ_NAME)

CC = gcc

OBJS = src/main.c

C_FLAGS = `sdl2-config --cflags` -std=c99 -pedantic
LINKER_FLAGS = `sdl2-config --libs` -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm
BUILD_FLAGS = -O2
DEBUG_FLAGS = -Wall -Wextra -Wmissing-declarations -g -mconsole

.PHONY: all build clean debug

all: build

build: $(OBJS)
	@echo Compiling $@ target
	$(CC) $(OBJS) $(C_FLAGS) $(BUILD_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

debug: $(OBJS)
	@echo Compiling $@ target
	$(CC) $(OBJS) $(C_FLAGS) $(DEBUG_FLAGS) $(LINKER_FLAGS) -o $(DEBUG_OBJ_NAME)

clean:
	@echo Running $@ on targets
	rm -f $(OBJ_NAME) $(DEBUG_OBJ_NAME)
