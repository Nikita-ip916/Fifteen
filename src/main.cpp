#include "SFML/Graphics.hpp"
#include "check.hpp"
#include "gen.hpp"
#include "leaderboard.hpp"
#include "move.hpp"
#include "out.hpp"
#include "resoursecheck.hpp"
#include "stopwatch.hpp"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;
using namespace sf;
struct Result {
    string name;
    int hours;
    int minutes;
    int seconds;
};
int main()
{
    const int defaultTextSize = 20;
    const int leaderboardTextSize = 16;
    const int width = 192;
    const int height = 224;
    const int textureMinSize = 32;
    const int boardSize = 5;
    const int moveDelay = 250; // milliSeconds
    vector<Result> vectorResult;
    Result result;
    RenderWindow window(
            VideoMode(width, height), "Fifteen 2020   ", Style::Close);
    Event event;
    Font font;
    Image numbersimage, othersimage;

    if (resourseCheck()) {
        numbersimage.loadFromFile("Numbers.jpg");
        othersimage.loadFromFile("Others.jpg");
        font.loadFromFile("TimesNewRoman.ttf");
    } else {
        return 1;
    }

    Texture numberstexture, otherstexture;
    numberstexture.loadFromImage(numbersimage);
    otherstexture.loadFromImage(othersimage);

    Sprite number, highScore, restart;
    number.setTexture(numberstexture);
    highScore.setTexture(otherstexture);
    restart.setTexture(otherstexture);
    highScore.setTextureRect(
            IntRect(textureMinSize, 0, textureMinSize * 4, textureMinSize));
    restart.setTextureRect(IntRect(0, 0, textureMinSize, textureMinSize));

    Text textStopWatch("", font, defaultTextSize);
    Text textLeaderboard("", font, leaderboardTextSize);
    textStopWatch.setStyle(Text::Bold);

    Clock clock, moveTimer;

    srand(time(0));

    int** gameBoard = new int*[boardSize];
    for (int i = 0; i < boardSize; i++) {
        gameBoard[i] = new int[boardSize];
    }
    generateArray(gameBoard, boardSize);
    int time[3], timeLock = 0;
    for (int i = 0; i < 3; i++) {
        time[i] = 0;
    }
    bool stopWatchStart, isSolved, showLeaderboard, nameInput;
    stopWatchStart = isSolved = showLeaderboard = nameInput = false;
    while (window.isOpen()) {
        ostringstream out;
        Vector2i pos = Mouse::getPosition(window);
        int dir = 0;
        int xMouse = pos.x / textureMinSize;
        int yMouse = pos.y / textureMinSize;
        int currentMoveDelay;
        int emptyElem[2];
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed && !nameInput
                && !isSolved) {
                if (xMouse == 5 && yMouse == 4 && !showLeaderboard) {
                    generateArray(gameBoard, boardSize);
                    timeLock = 0;
                    clock.restart();
                    stopWatchStart = false;
                    for (int i = 0; i < 3; i++) {
                        time[i] = 0;
                    }
                } else if (xMouse >= 1 && xMouse <= 4 && yMouse == 5) {
                    showLeaderboard = !showLeaderboard;
                }
            }
        }
        window.clear(Color::Black);
        if (isSolved) {
            cout << "Push the button (y/n) anywhere except console if you want "
                    "to enter name for leaderboard"
                 << endl;
            nameInput = true;
            isSolved = false;
        }
        if (nameInput) {
            if (Keyboard::isKeyPressed(Keyboard::Y)) {
                getResult(time, result, vectorResult);
                writeResult(result, vectorResult);
                readResult(result, vectorResult);
                generateArray(gameBoard, boardSize);
                timeLock = 0;
                clock.restart();
                stopWatchStart = false;
                for (int i = 0; i < 3; i++) {
                    time[i] = 0;
                }
                nameInput = false;
            } else if (Keyboard::isKeyPressed(Keyboard::N)) {
                generateArray(gameBoard, boardSize);
                timeLock = 0;
                clock.restart();
                stopWatchStart = false;
                for (int i = 0; i < 3; i++) {
                    time[i] = 0;
                }
                nameInput = false;
            }
        } else {
            if (showLeaderboard) {
                fixFile(result, vectorResult);
                readResult(result, vectorResult);
                if (vectorResult.size() <= 5) {
                    for (int i = 0; i < int(vectorResult.size()); i++) {
                        out << i + 1 << ". " << vectorResult[i].name << " - "
                            << setfill('0') << setw(2) << vectorResult[i].hours
                            << ":" << setfill('0') << setw(2)
                            << vectorResult[i].minutes << ":" << setfill('0')
                            << setw(2) << vectorResult[i].seconds << '\n';
                    }
                } else if (vector_result.size() == 0) {
                    out << "Leaderboard is empty!\n";
                }
                textLeaderboard.setString(out.str());
                out.str("");
                textLeaderboard.setPosition(20, 24);
                window.draw(textLeaderboard);
                vectorResult.clear();
                timeLock = time[0];
                clock.restart();
            } else {
                currentMoveDelay = moveTimer.getElapsedTime().asMilliseconds();
                if (stopWatchStart) {
                    time[0] = clock.getElapsedTime().asSeconds() + timeLock;
                } else {
                    clock.restart();
                }
                if (time[0] > 59) {
                    timeLock = 0;
                    clock.restart();
                }
                stopWatch(time);
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    window.close();
                }
                for (int i = 1; i < boardSize; i++) {
                    for (int j = 1; j < boardSize; j++) {
                        if (gameBoard[j][i] == 0) {
                            emptyElem[0] = j;
                            emptyElem[1] = i;
                        }
                    }
                }
                if ((Keyboard::isKeyPressed(Keyboard::A)
                     || Keyboard::isKeyPressed(Keyboard::Left))
                    && currentMoveDelay > moveDelay) {
                    dir = 1;
                    moveF(dir, gameBoard, boardSize, emptyElem);
                } else if (
                        (Keyboard::isKeyPressed(Keyboard::D)
                         || Keyboard::isKeyPressed(Keyboard::Right))
                        && currentMoveDelay > moveDelay) {
                    dir = 2;
                    moveF(dir, gameBoard, boardSize, emptyElem);
                } else if (
                        (Keyboard::isKeyPressed(Keyboard::W)
                         || Keyboard::isKeyPressed(Keyboard::Up))
                        && currentMoveDelay > moveDelay) {
                    dir = 3;
                    moveF(dir, gameBoard, boardSize, emptyElem);
                } else if (
                        (Keyboard::isKeyPressed(Keyboard::S)
                         || Keyboard::isKeyPressed(Keyboard::Down))
                        && currentMoveDelay > moveDelay) {
                    dir = 4;
                    moveF(dir, gameBoard, boardSize, emptyElem);
                }
                if (gameBoard[emptyElem[0]][emptyElem[1]] != 0) {
                    moveTimer.restart();
                    stopWatchStart = true;
                }
                for (int i = 1; i < boardSize; i++) {
                    for (int j = 1; j < boardSize; j++) {
                        number.setTextureRect(
                                IntRect(textureMinSize * gameBoard[j][i],
                                        0,
                                        textureMinSize,
                                        textureMinSize));
                        number.setPosition(
                                textureMinSize * i, textureMinSize * j);
                        window.draw(number);
                    }
                }
                restart.setPosition(textureMinSize * 5, textureMinSize * 4);
                window.draw(restart);
            }
            isSolved = checkToWin(gameBoard, boardSize);
            out << setfill('0') << setw(2) << time[2] << ":" << setfill('0')
                << setw(2) << time[1] << ":" << setfill('0') << setw(2)
                << time[0];
            textStopWatch.setString(out.str());
            out.str("");
            textStopWatch.setPosition(textureMinSize, 0);
            window.draw(textStopWatch);
            highScore.setPosition(textureMinSize, textureMinSize * 5);
            window.draw(highScore);
            window.display();
        }
    }
}
