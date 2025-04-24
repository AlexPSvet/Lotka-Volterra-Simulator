#include <iostream>
#include <cmath>
#include "Game.hpp"
using namespace std;

void print(Game& game) {
    Ensemble& grid = game.getPopulation().getGrid().getEnsemble();
    int lenght = sqrt(grid.cardinal());
    for (int y = 0; y < lenght; y++) {
        for (int x = 0; x < lenght; x++) {
            int entityId = grid[y * lenght + x];
            if (entityId == -1) {
                cout << "-";
            } else {
                Entity* entity = game.getPopulation().get(entityId);
                entity->operator<<(cout);
            }
            cout << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < 2*lenght; i++) {
        cout << ".";
    }
    cout << endl;
}

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

    cout << game.getPopulation().getEntities().size() << " ENTITIES." << endl;

    cout << "GAME START :" << endl;
    print(game);
    cout << "NEXT STEPS :" << endl;

    for (int i = 0; i < 20; i++) {
        game.moveType(Type::rabbit);
        game.moveType(Type::fox);
        print(game);
        cout << game.getPopulation().getEntities().size() << " ENTITIES." << endl;
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