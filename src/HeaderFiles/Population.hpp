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
        void move();
        bool checkPreys();
    private:
        Grid grid;
        vector<Entity> entities;
        vector<EntityParams> params;
};

#endif