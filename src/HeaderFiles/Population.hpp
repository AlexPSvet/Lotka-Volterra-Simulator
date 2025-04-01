#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "Grid.hpp"

const struct EntityParams {
    int FOOD_INIT;
    int FOOD_TO_REPRODUCE_LEVEL;
    int PROB_REPRODUCE;
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