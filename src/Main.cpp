#include <iostream>
#include "Game.hpp"
using namespace std;

void normalGame() {
    EntityParams params;

    // (ENTITY NUMBER START, FOOD TO REPRODUCE, FOOD VALUE FOR PREYS, PROBABILITY TO REPRODUCE,
    // MIN FREE CASES TO REPRODUCE, PREY TYPES)
    TypeParams foxParams(7, 20, 15, 5, 20, 7, {Type::rabbit});
    params.addType(Type::fox, foxParams);

    TypeParams rabbitParams(20, 50, 5, 10, 30, 1, {});
    params.addType(Type::rabbit, rabbitParams);

    Game game(params, TAILLE_GRID * TAILLE_GRID);

    Ensemble& ids = game.getPopulation().getGrid().getEnsemble();

    game.start();

    cout << game.getPopulation().getEntities().size() << endl;

    for (int i = 0; i < 3; i++) {
        game.next();
        ids.operator<<(cout) << endl;
    }
    
    game.stop();
}

int main() {
    // Set random seed for random.
    srand(time(0));
    // Start a normal game.
    normalGame();
    return 0;
}