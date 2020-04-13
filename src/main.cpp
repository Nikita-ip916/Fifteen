#include "gen.h"
#include "out.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
const int n = 5;
using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(200, 200), "SFML works!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);
    srand(time(0));

    int** arr = new int*[n];
    for (int i = 0; i < n; i++)
        arr[i] = new int[n];
    generateArray(arr, n);
    outArray(arr, n);
    cout << endl;
    while (window.isOpen()) {
        Event event;
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
