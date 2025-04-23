#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "Entity.hpp"
#include "Coord.hpp"
#include "Population.hpp"

// Répartition des animaux au début de la simulation dans la grille.
static const int INIT_ENTITIES[] = {20, 7};

class Simulator {
    public:
        void next();
        void start();
        void stop();
    private:
};

struct EntityParams {
    const int FOOD_INIT_RABBIT;
    const int FOOD_TO_REPRODUCE_LEVE_RABBIT;
    const int PROB_REPRODUCE_RABBIT;

    const int FOOD_INIT_FOX;
    const int FOOD_TO_REPRODUCE_LEVEL_FOX;
    const int PROB_REPRODUCE_FOX;
};

class Game {
    public:
        Game();

        int ajouteAnimal(Type type, int age, Coord coord);
        void setEntityInit();

        bool verifieGrille();

        Ensemble emptyNeighbours(Coord cord);
        Ensemble typeNeighbours(Coord cord, Type type);
        void moveEntity(int id);
    private:
        Population population;
        Grid grid;

        EntityParams* params;
};

#endif