#include <iostream>
#include <cmath>
#include "Console.hpp"
#include "Graphics.hpp"
using namespace std;

int main() {
    // Set random seed for random.
    srand(time(0));
    // Start a console game.
    // Console console;
    // console.start();

    // Start a Graphics game>
    Graphics graphics;
    graphics.start();
    return 0;
}