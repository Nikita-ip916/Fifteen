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
const int defaultTextSize = 20;
const int leaderboardTextSize = 16;
const int width = 192;
const int height = 224;
const int n = 5;
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
    vector<Result> vector_result;
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
    highScore.setTextureRect(IntRect(32, 0, 128, 32));
    restart.setTextureRect(IntRect(0, 0, 32, 32));

    Text textTimer("", font, defaultTextSize);
    Text textLeaderboard("", font, leaderboardTextSize);
    textTimer.setStyle(Text::Bold);

    Clock clock, moveTimer;

    srand(time(0));

    int** gameBoard = new int*[n];
    for (int i = 0; i < n; i++) {
        gameBoard[i] = new int[n];
    }
    generateArray(gameBoard, n);
    int time[3], timeLock = 0;
    for (int i = 0; i < 3; i++) {
        time[i] = 0;
    }
    bool timerStart, isSolved, showLeaderboard, nameInput;
    timerStart = isSolved = showLeaderboard = nameInput = false;
    while (window.isOpen()) {
        ostringstream out;
        Vector2i pos = Mouse::getPosition(window);
        int dir = 0;
        int x = pos.x / 32;
        int y = pos.y / 32;
        int milliSecond;
        int emptyElem[2]; // Gets coordinates of empty sprite
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed && !nameInput
                && !isSolved) {
                if (x == 5 && y == 4 && !showLeaderboard) {
                    generateArray(gameBoard, n);
                    clock.restart();
                    timerStart = false;
                    for (int i = 0; i < 3; i++) {
                        time[i] = 0;
                    }
                } else if (x >= 1 && x <= 4 && y == 5) {
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
                getResult(time, result, vector_result);
                writeResult(result, vector_result);
                readResult(result, vector_result);
                generateArray(gameBoard, n);
                clock.restart();
                timerStart = false;
                for (int i = 0; i < 3; i++) {
                    time[i] = 0;
                }
                nameInput = false;
            } else if (Keyboard::isKeyPressed(Keyboard::N)) {
                generateArray(gameBoard, n);
                clock.restart();
                timerStart = false;
                for (int i = 0; i < 3; i++) {
                    time[i] = 0;
                }
                nameInput = false;
            }
        } else {
            if (showLeaderboard) {
                readResult(result, vector_result);
                if (vector_result.size() != 0) {
                    for (int i = 0; i < int(vector_result.size()); i++) {
                        out << i + 1 << ". " << vector_result[i].name << " - "
                            << setfill('0') << setw(2) << vector_result[i].hours
                            << ":" << setfill('0') << setw(2)
                            << vector_result[i].minutes << ":" << setfill('0')
                            << setw(2) << vector_result[i].seconds << '\n';
                    }
                } else {
                    out << "Leaderboard is empty!\n";
                }
                textLeaderboard.setString(out.str());
                out.str("");
                textLeaderboard.setPosition(20, 24);
                window.draw(textLeaderboard);
                vector_result.clear();
                timeLock = time[0];
                clock.restart();
            } else {
                milliSecond = moveTimer.getElapsedTime().asMilliseconds();
                if (timerStart) {
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
                if (!showLeaderboard) {
                    if ((Keyboard::isKeyPressed(Keyboard::A)
                         || Keyboard::isKeyPressed(Keyboard::Left))
                        && milliSecond > 250) {
                        dir = 1;
                        moveF(dir, gameBoard, n, emptyElem);
                        moveTimer.restart();
                        timerStart = true;
                    } else if (
                            (Keyboard::isKeyPressed(Keyboard::D)
                             || Keyboard::isKeyPressed(Keyboard::Right))
                            && milliSecond > 250) {
                        dir = 2;
                        moveF(dir, gameBoard, n, emptyElem);
                        moveTimer.restart();
                        timerStart = true;
                    } else if (
                            (Keyboard::isKeyPressed(Keyboard::W)
                             || Keyboard::isKeyPressed(Keyboard::Up))
                            && emptyElem[0] < 4 && milliSecond > 250) {
                        dir = 3;
                        moveF(dir, gameBoard, n, emptyElem);
                        moveTimer.restart();
                        timerStart = true;
                    } else if (
                            (Keyboard::isKeyPressed(Keyboard::S)
                             || Keyboard::isKeyPressed(Keyboard::Down))
                            && emptyElem[0] > 1 && milliSecond > 250) {
                        dir = 4;
                        moveF(dir, gameBoard, n, emptyElem);
                        moveTimer.restart();
                        timerStart = true;
                    }
                    for (int i = 1; i < 5; i++) {
                        for (int j = 1; j < 5; j++) {
                            number.setTextureRect(
                                    IntRect(32 * gameBoard[j][i], 0, 32, 32));
                            number.setPosition(32 * i, 32 * j);
                            window.draw(number);
                            if (gameBoard[j][i] == 0) {
                                emptyElem[0] = j;
                                emptyElem[1] = i;
                            }
                        }
                    }
                    restart.setPosition(160, 128);
                    window.draw(restart);
                }
            }
            isSolved = checkToWin(gameBoard, n);
            out << setfill('0') << setw(2) << time[2] << ":" << setfill('0')
                << setw(2) << time[1] << ":" << setfill('0') << setw(2)
                << time[0];
            textTimer.setString(out.str());
            out.str("");
            textTimer.setPosition(32, 0);
            window.draw(textTimer);
            highScore.setPosition(32, 160);
            window.draw(highScore);
            window.display();
        }
    }
}
