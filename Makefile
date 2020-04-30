CC = g++
CFLAGS = -Wall -Werror -c
SFML = -lsfml-graphics -lsfml-window -lsfml-system
OUT = out
DIR = build
DIR2 = bin
DIR3 = src
SFML2 = -I SFML-2.5.1/include -L SFML-2.5.1/lib
.PHONY: all prog clean
all: prog
prog:
		$(CC) -o $(DIR)/main.o $(SFML2) $(CFLAGS) $(DIR3)/main.cpp
		$(CC) -o $(DIR)/gen.o $(CFLAGS) $(DIR3)/gen.cpp
		$(CC) -o $(DIR)/out.o $(CFLAGS) $(DIR3)/out.cpp
		$(CC) -o $(DIR)/stopwatch.o $(CFLAGS) $(DIR3)/stopwatch.cpp
		$(CC) -o $(DIR)/move.o $(CFLAGS) $(DIR3)/move.cpp
		$(CC) $(DIR)/*.o -o $(DIR2)/$(OUT) $(SFML2) $(SFML)
clean:
		rm -rf $(DIR2)/$(OUT)
		rm -rf $(DIR)/*.o
