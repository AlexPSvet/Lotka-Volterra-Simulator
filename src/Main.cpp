#include <iostream>
#include <cmath>
#include "Console.hpp"
using namespace std;

int main() {
    // Set random seed for random.
    srand(time(0));
    // Start a console game.
    Console console;
    console.start();
    return 0;
}