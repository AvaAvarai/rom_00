OBJ_NAME = rom_00
CC = gcc

OBJS = main.c

C_FLAGS = -std=c99 -Wall -pedantic -Wl,-subsystem,windows
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

.PHONY: all build clean

all: build

build: $(OBJS)
	$(CC) $(OBJS) $(C_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
