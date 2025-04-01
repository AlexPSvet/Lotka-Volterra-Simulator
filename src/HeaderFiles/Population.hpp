#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "Grid.hpp"

struct EntityParams {
    const int FOOD_INIT;
    const int FOOD_TO_REPRODUCE_LEVEL;
    const int PROB_REPRODUCE;
};

class Population {
    public:
        Population();

        void move();
        bool checkPreys();

        Entity get(int id) const;
        Ensemble getIds() const;

        int reserve(Type type, int age);
        void set();
        void supprime(int id);

    private:
        Grid grid;
        vector<Entity> entities;
        vector<EntityParams> params;
};

#endif