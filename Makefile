CXX = g++
CXXFLAGS = -Wall -Werror
LIB = -std=c++11
SFML = -lsfml-graphics -lsfml-window -lsfml-system
SFML2 = -I SFML-2.5.1/include -L SFML-2.5.1/lib
OUT = fifteen
PRE = cxxtestgen --error-printer
RUN = runner
.PHONY: all test runprog clean
all: bin/$(OUT)

bin/$(OUT): build/src/main.o build/src/gen.o build/src/stopwatch.o build/src/move.o build/src/leaderboard.o build/src/resoursecheck.o build/src/check.o
		$(CXX) build/src/main.o build/src/gen.o build/src/stopwatch.o build/src/move.o build/src/leaderboard.o build/src/resoursecheck.o build/src/check.o -o $@ $(SFML2) $(SFML) $(LIB)

build/src/main.o: src/main.cpp
		$(CXX) $(SFML2) $(CXXFLAGS) -I src -c $< -o $@ $(LIB)

build/src/gen.o: src/gen.cpp
		$(CXX) $(CXXFLAGS) -I src -c $< -o $@ $(LIB)

build/src/stopwatch.o: src/stopwatch.cpp
		$(CXX) $(CXXFLAGS) -I src -c $< -o $@ $(LIB)

build/src/move.o: src/move.cpp
		$(CXX) $(CXXFLAGS) -I src -c $< -o $@ $(LIB)

build/src/leaderboard.o: src/leaderboard.cpp
		$(CXX) $(CXXFLAGS) -I src -c $< -o $@ $(LIB)

build/src/resoursecheck.o: src/resoursecheck.cpp
		$(CXX) $(CXXFLAGS) -I src -c $< -o $@ $(LIB)

build/src/check.o: src/check.cpp
		$(CXX) $(CXXFLAGS) -I src -c $< -o $@ $(LIB)

bin/$(RUN): build/test/$(RUN).cpp build/src/gen.o build/src/stopwatch.o build/src/move.o build/src/leaderboard.o
		$(CXX) -I test -I src build/test/$(RUN).cpp build/src/gen.o build/src/stopwatch.o build/src/move.o build/src/leaderboard.o -o $@ $(LIB)

build/test/$(RUN).cpp:
		$(PRE) test/*.h -o $@

runprog:
		./bin/$(OUT)

test: bin/$(RUN)
		./$< --help-tests
		./$<

clean:
		rm -rf bin/$(OUT) bin/$(RUN)
		rm -rf build/src/*.o build/test/*.cpp
