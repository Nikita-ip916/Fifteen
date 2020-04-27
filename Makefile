CC = g++
CFLAGS = -Wall -Werror -c
SFML = -lsfml-graphics -lsfml-window -lsfml-system
OUT = out
DIR = build
DIR2 = bin
DIR3 = src
all:
		$(CC) -o $(DIR)/main.o $(CFLAGS) $(DIR3)/main.cpp
		$(CC) -o $(DIR)/gen.o $(CFLAGS) $(DIR3)/gen.cpp
		$(CC) -o $(DIR)/out.o $(CFLAGS) $(DIR3)/out.cpp
		$(CC) -o $(DIR)/stopwatch.o $(CFLAGS) $(DIR3)/stopwatch.cpp
		$(CC) $(DIR)/*.o -o $(DIR2)/$(OUT) $(SFML)

clean:
		rm -rf $(DIR2)/$(OUT)
		rm -rf $(DIR)/*.o
