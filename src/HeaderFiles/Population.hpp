#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "Grid.hpp"

class Population {
    public:
        void move();
        bool checkPreys();
    private:
        Grid grid;
        vector<Entity> entities;
};

#endif