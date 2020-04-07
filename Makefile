CC = g++
CFLAGS = -Wall -Werror
OUT = out
DIR = build
DIR2 = bin
all:
		$(CC) $(CFLAGS) src/main.cpp -o $(DIR2)/$(OUT)
clean:
		rm -rf $(DIR2)/$(OUT)
