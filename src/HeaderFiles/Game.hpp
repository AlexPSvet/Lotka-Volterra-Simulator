#ifndef GAME_HPP
#define GAME_HPP

#include "Entity.hpp"
#include "Coord.hpp"
#include "Population.hpp"

class Game {
    public:
        Game(EntityParams params, int taille);

        int ajouteAnimal(Type type, int age, int coord);
        void setEntityInit();

        bool verifieGrille();

        Ensemble emptyNeighbours(Coord cord);
        Ensemble typeNeighbours(Coord cord, Type type);
        void moveType(Type type);

        void moveEntity(Entity* entity);
        void eatPrey(Entity* entity, int preyId);
        void moveRandom(Entity* entity);
        void move(Entity* entity, int oldCoord, int newCoord);

        void next();
        void start();
        void stop();

        Population& getPopulation();
    private:
        Population population;
};



#endif
