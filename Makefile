CC = g++
CFLAGS = -Wall -Werror -c
SFML = -lsfml-graphics -lsfml-window -lsfml-system
SFML2 = -I SFML-2.5.1/include -L SFML-2.5.1/lib
OUT = out
DIR = build
DIR2 = bin
DIR3 = src
DIR4 = test
PRE = cxxtestgen --error-printer
RUN = runner
.PHONY: all prog test clean
all: prog test
prog:
		$(CC) -o $(DIR)/$(DIR3)/main.o $(SFML2) $(CFLAGS) $(DIR3)/main.cpp
		$(CC) -o $(DIR)/$(DIR3)/gen.o $(CFLAGS) $(DIR3)/gen.cpp
		$(CC) -o $(DIR)/$(DIR3)/out.o $(CFLAGS) $(DIR3)/out.cpp
		$(CC) -o $(DIR)/$(DIR3)/tstopwatch.o $(CFLAGS) $(DIR3)/stopwatch.cpp
		$(CC) -o $(DIR)/$(DIR3)/tmove.o $(CFLAGS) $(DIR3)/move.cpp
		$(CC) $(DIR)/$(DIR3)/*.o -o $(DIR2)/$(OUT) $(SFML2) $(SFML)
		$(PRE) -o $(DIR)/$(DIR4)/$(RUN).cpp $(DIR4)/*.h
		$(CC) -I $(DIR4) -I $(DIR3) $(DIR)/$(DIR4)/$(RUN).cpp $(DIR)/$(DIR3)/t*.o -o $(DIR2)/$(RUN)
test:
		./$(DIR2)/$(RUN) --help-tests
		./$(DIR2)/$(RUN)
clean:
		rm -rf $(DIR2)/$(OUT) $(DIR2)/$(RUN)
		rm -rf $(DIR)/$(DIR3)/*.o $(DIR)/$(DIR4)/*.cpp
