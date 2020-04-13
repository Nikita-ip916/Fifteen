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
    numbersimage.loadFromFile("Numbers.jpg");
    othersimage.loadFromFile("Others.jpg");

    Texture numberstexture, otherstexture;
    numberstexture.loadFromImage(numbersimage);
    otherstexture.loadFromImage(othersimage);

    Sprite nmbr, scr, rsrt;
    nmbr.setTexture(numberstexture);
    scr.setTexture(otherstexture);
    rsrt.setTexture(otherstexture);

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

        window.clear();
        window.draw(shape);
        window.display();
    }
}
