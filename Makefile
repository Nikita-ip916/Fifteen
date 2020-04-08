CC = g++
CFLAGS = -Wall -Werror -c
OUT = out
DIR = build
DIR2 = bin
DIR3 = src
all:
		$(CC) -o $(DIR)/main.o $(CFLAGS) $(DIR3)/main.cpp
		$(CC) -o $(DIR)/gen.o $(CFLAGS) $(DIR3)/gen.cpp
		$(CC) -o $(DIR)/out.o $(CFLAGS) $(DIR3)/out.cpp
		$(CC) $(DIR)/out.o $(DIR)/gen.o $(DIR)/main.o -o $(DIR2)/$(OUT)

clean:
		rm -rf $(DIR2)/$(OUT)
		rm -rf $(DIR)/*.o
