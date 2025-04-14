#ifndef POPULATION_HPP
#define POPULATION_HPP

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

        Entity get(int id) const;
        Ensemble getIds() const;

        int reserve(Type type, int age);
        void set();
        void supprime(int id);
    private:
        Entity* entities;
        int amount;
        Ensemble ids;
        EntityParams params;
};

#endif