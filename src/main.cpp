#include "gen.hpp"
#include "out.hpp"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
const int width = 192;
const int height = 224;
const int n = 5;
using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(width, height), "TagGame");
    Event event;
    Image numbersimage, othersimage;
    numbersimage.loadFromFile("Numbers.jpg");
    othersimage.loadFromFile("Others.jpg");

    Texture numberstexture, otherstexture;
    numberstexture.loadFromImage(numbersimage);
    otherstexture.loadFromImage(othersimage);

    Sprite nmbr, scr, rstrt;
    nmbr.setTexture(numberstexture);
    scr.setTexture(otherstexture);
    rstrt.setTexture(otherstexture);
    scr.setTextureRect(IntRect(32, 0, 128, 32));
    rstrt.setTextureRect(IntRect(0, 0, 32, 32));
    Font font;
    font.loadFromFile("TimesNewRoman.ttf");
    Text text("", font, 20);
    text.setStyle(Text::Bold);
    Clock clock, moveTimer;

    srand(time(0));

    int** arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
    }
    generateArray(arr, n);
    cout << endl;
    int t[3];
    for (int i = 0; i < 3; i++) {
        t[i] = 0;
    }
    bool flag = false;
    while (window.isOpen()) {
        Vector2i pos = Mouse::getPosition(window);
        int x = pos.x / 32;
        int y = pos.y / 32;
        int mas[2]; // Gets coordinates of empty sprite
        int time = moveTimer.getElapsedTime().asMilliseconds();
        if (flag) {
            t[0] = clock.getElapsedTime().asSeconds();
        } else {
            clock.restart();
        }
        if (t[0] > 59) {
            clock.restart();
            t[1]++;
        }
        if (t[1] > 59) {
            t[1] = 0;
            t[2]++;
        }
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed)
                if (x == 5 && y == 4) {
                    generateArray(arr, n);
                    clock.restart();
                    flag = false;
                    for (int i = 0; i < 3; i++) {
                        t[i] = 0;
                    }
                }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        window.clear(Color::Black);
        for (int i = 1; i < 5; i++) {
            for (int j = 1; j < 5; j++) {
                nmbr.setTextureRect(IntRect(32 * arr[j][i], 0, 32, 32));
                nmbr.setPosition(32 * i, 32 * j);
                window.draw(nmbr);
                if (arr[j][i] == 0) {
                    mas[0] = j;
                    mas[1] = i;
                }
            }
        }
        if ((Keyboard::isKeyPressed(Keyboard::A)
             || Keyboard::isKeyPressed(Keyboard::Left))
            && mas[1] < 4 && time > 250) {
            arr[mas[0]][mas[1]] = arr[mas[0]][mas[1] + 1];
            arr[mas[0]][mas[1] + 1] = 0;
            moveTimer.restart();
            flag = true;
        } else if (
                (Keyboard::isKeyPressed(Keyboard::D)
                 || Keyboard::isKeyPressed(Keyboard::Right))
                && mas[1] > 1 && time > 250) {
            arr[mas[0]][mas[1]] = arr[mas[0]][mas[1] - 1];
            arr[mas[0]][mas[1] - 1] = 0;
            moveTimer.restart();
            flag = true;
        } else if (
                (Keyboard::isKeyPressed(Keyboard::W)
                 || Keyboard::isKeyPressed(Keyboard::Up))
                && mas[0] < 4 && time > 250) {
            arr[mas[0]][mas[1]] = arr[mas[0] + 1][mas[1]];
            arr[mas[0] + 1][mas[1]] = 0;
            moveTimer.restart();
            flag = true;
        } else if (
                (Keyboard::isKeyPressed(Keyboard::S)
                 || Keyboard::isKeyPressed(Keyboard::Down))
                && mas[0] > 1 && time > 250) {
            arr[mas[0]][mas[1]] = arr[mas[0] - 1][mas[1]];
            arr[mas[0] - 1][mas[1]] = 0;
            moveTimer.restart();
            flag = true;
        }
        ostringstream Out;
        Out << setfill('0') << setw(2) << t[2] << ":" << setfill('0') << setw(2)
            << t[1] << ":" << setfill('0') << setw(2) << t[0];
        text.setString(Out.str());
        text.setPosition(32, 0);
        scr.setPosition(32, 160);
        rstrt.setPosition(160, 128);
        window.draw(text);
        window.draw(scr);
        window.draw(rstrt);
        window.display();
    }
}
