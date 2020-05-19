#include "SFML/Graphics.hpp"
#include "gen.hpp"
#include "leaderboard.hpp"
#include "move.hpp"
#include "out.hpp"
#include "stopwatch.hpp"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
const int width = 192;
const int height = 224;
const int n = 5;
using namespace std;
using namespace sf;
struct result {
    string name;
    int h;
    int m;
    int s;
};

int main()
{
    vector<result> vr;
    result r;
    RenderWindow window(VideoMode(width, height), "Fifteen 2020   ");
    Event event;
    Image numbersimage, othersimage;
    numbersimage.loadFromFile("Numbers.jpg");
    othersimage.loadFromFile("Others.jpg");

    Texture numberstexture, otherstexture;
    numberstexture.loadFromImage(numbersimage);
    otherstexture.loadFromImage(othersimage);

    Sprite number, highScore, restart;
    number.setTexture(numberstexture);
    highScore.setTexture(otherstexture);
    restart.setTexture(otherstexture);
    highScore.setTextureRect(IntRect(32, 0, 128, 32));
    restart.setTextureRect(IntRect(0, 0, 32, 32));
    Font font;
    font.loadFromFile("TimesNewRoman.ttf");
    Text text("", font, 20);
    text.setStyle(Text::Bold);
    Clock clock, moveTimer;

    srand(time(0));

    int** gameBoard = new int*[n];
    for (int i = 0; i < n; i++) {
        gameBoard[i] = new int[n];
    }
    generateArray(gameBoard, n);
    cout << endl;
    int time[3];
    for (int i = 0; i < 3; i++) {
        time[i] = 0;
    }
    bool timerStart = false;
    while (window.isOpen()) {
        Vector2i pos = Mouse::getPosition(window);
        int dir = 0;
        int x = pos.x / 32;
        int y = pos.y / 32;
        int emptyElem[2]; // Gets coordinates of empty sprite
        int milliSecond = moveTimer.getElapsedTime().asMilliseconds();
        if (timerStart) {
            time[0] = clock.getElapsedTime().asSeconds();
        } else {
            clock.restart();
        }
        if (time[0] > 59) {
            clock.restart();
        }
        stopWatch(time);
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed)
                if (x == 5 && y == 4) {
                    generateArray(gameBoard, n);
                    clock.restart();
                    timerStart = false;
                    for (int i = 0; i < 3; i++) {
                        time[i] = 0;
                    }
                }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        window.clear(Color::Black);
        for (int i = 1; i < 5; i++) {
            for (int j = 1; j < 5; j++) {
                number.setTextureRect(IntRect(32 * gameBoard[j][i], 0, 32, 32));
                number.setPosition(32 * i, 32 * j);
                window.draw(number);
                if (gameBoard[j][i] == 0) {
                    emptyElem[0] = j;
                    emptyElem[1] = i;
                }
            }
        }
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
        ostringstream Out;
        Out << setfill('0') << setw(2) << time[2] << ":" << setfill('0')
            << setw(2) << time[1] << ":" << setfill('0') << setw(2) << time[0];
        text.setString(Out.str());
        text.setPosition(32, 0);
        highScore.setPosition(32, 160);
        restart.setPosition(160, 128);
        window.draw(text);
        window.draw(highScore);
        window.draw(restart);
        window.display();
    }
}
