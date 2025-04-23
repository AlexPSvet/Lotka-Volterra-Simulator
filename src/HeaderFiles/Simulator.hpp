#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "Entity.hpp"
#include "Coord.hpp"
#include "Population.hpp"

class Game {
    public:
        Game();

        int ajouteAnimal(Type type, int age, Coord coord);
        void setEntityInit();

        bool verifieGrille();

        Ensemble emptyNeighbours(Coord cord);
        Ensemble typeNeighbours(Coord cord, Type type);
        void moveType(Type type);

        void moveEntity(int id);
        void eatPrey(int entityId, int preyId);
        void moveRandom(int id);
        void move(Entity* entity, int oldCoord, int newCoord);

        void next();
        void start();
        void stop();

    private:
        Population population;
        Grid grid;
};



#endif
