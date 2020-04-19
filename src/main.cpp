#include "gen.hpp"
#include "out.hpp"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
const int n = 5;
#define m 224
using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(m, m), "test. kursach-TRPO");
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

    srand(time(0));

    int** arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
    }
    generateArray(arr, n);
    outArray(arr, n);
    cout << endl;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
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
            }
        }
        scr.setPosition(32, 160);
        rstrt.setPosition(160, 128);
        window.draw(scr);
        window.draw(rstrt);
        window.display();
    }
}
