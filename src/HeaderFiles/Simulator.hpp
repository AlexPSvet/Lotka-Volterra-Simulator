#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "Entity.hpp"
#include "Coord.hpp"
#include "Population.hpp"

class Simulator {
    public:
        void next();
        void start();
        void stop();
    private:
};

struct TypeParams {
    int FOOD_INIT;
    int FOOD_TO_REPRODUCE_LEVEL;
    int PROB_REPRODUCE;
};

struct EntityParams {
    Type types[2] = { Type::rabbit, Type::fox };
    int init_entities[2] = {20, 7};
    TypeParams* typeParams[2];
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