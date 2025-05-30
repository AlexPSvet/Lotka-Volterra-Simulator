#include <iostream>
#include <cmath>
#include "Console.hpp"
#include "Graphics.hpp"
using namespace std;

int main() {
    // Set random seed for random.
    srand(time(0));

    string answer;
    cout << "Do you wanna make the simulation on SFML (s) or on the console (c) ? (s/c)" << endl;
    cin >> answer;

    if (answer == "s") {
        Graphics* graphics = new Graphics();
        graphics->start();
        delete graphics;
    } else if (answer == "c") {
        Console console;
        console.start();
    } else {
        cout << "Invalid answer" << endl;
        return -1;
    }

    return 0;
}