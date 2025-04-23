#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>
#include <cstdlib>
#include "Ensemble.hpp"
#include "Coord.hpp"
#include "Entity.hpp"

struct EntityParams {
    const int FOOD_INIT;
    const int FOOD_TO_REPRODUCE_LEVEL;
    const int PROB_REPRODUCE;
};

class Population {
    public:
        Population();

        Entity* get(int id) const;

        int reserve(Type type, int age);
        
        void set(int id, Coord coord);
        void supprime(int id);

        vector<Entity*> getEntities();
    private:
        Ensemble ids;
        vector<Entity*> entities;
};

#endif