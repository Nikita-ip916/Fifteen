#include "gen.h"
#include "out.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
const int n = 5;
#define m 192
using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(m, m), "test. kursach-TRPO");
    Event event;
    Image numbersimage, othersimage;
    numbersimage.loadFromFile("src/Numbers.jpg");
    othersimage.loadFromFile("src/Others.jpg");

    Texture numberstexture, otherstexture;
    numberstexture.loadFromImage(numbersimage);
    otherstexture.loadFromImage(othersimage);

    Sprite nmbr, scr, rstrt;
    nmbr.setTexture(numberstexture);
    scr.setTexture(otherstexture);
    rstrt.setTexture(otherstexture);
    scr.setTextureRect(IntRect(32, 0, 128, 32));
    rstrt.setTextureRect(IntRect(0, 0, 32, 32));

    srand(time(0));

    int** arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
    }
    generateArray(arr, n);
    outArray(arr, n);
    cout << endl;
    while (window.isOpen()) {
        nmbr.setPosition(32, 32);
        scr.setPosition(32, 160);
        rstrt.setPosition(160, 128);
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1; j++) {
                nmbr.setTextureRect(IntRect(32 * j + 128 * i, 0, 32, 32));
                window.draw(nmbr);
                nmbr.move(32, 0);
            }
            nmbr.move(-128, 32);
        }
        window.draw(scr);
        window.draw(rstrt);
        window.display();
        window.clear();
    }
}
