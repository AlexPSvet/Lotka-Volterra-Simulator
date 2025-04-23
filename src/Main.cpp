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
    game.start();
    Ensemble ids = game.getPopulation().getGrid().getEnsemble();
    ids.operator<<(cout);
    
    game.getPopulation().clear();
}

int main() {
    normalGame();
    return 0;
}