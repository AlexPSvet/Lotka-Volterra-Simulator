#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>
#include <cstdlib>
#include "Ensemble.hpp"
#include "Coord.hpp"
#include "Entity.hpp"

class TypeParams {
    public:
        TypeParams(
            int entityInit,
            int foodInit,
            int foodToReproduceLevel,
            int foodPerMove,
            int foodValue,
            int probReproduce,
            int minFreeBirth,
            vector<Type> types
        );

        int getEntityInit();
        int getFoodInit();
        int getFoodToReproduce();
        int getFoodPerMove();
        int getFoodValue();
        int getProbToReproduce();
        int getMinFreeBirth();
        vector<Type>& getPreys();

        bool isPrey(Type type);
    private:
        const int entityInit;
        const int foodInit;
        const int foodToReproduceLevel;
        const int foodPerMove;
        const int foodValue;
        const int probReproduce;
        const int minFreeBirth;

        vector<Type> preys;
};

class EntityParams {
    public:
        vector<Type>& getTypes();
        TypeParams& getTypeParams(Type type);

        void addType(Type type, TypeParams params);
    private:
        vector<Type> types;
        vector<TypeParams> typeParams;
};

class Population {
    public:
        Population(int taille);

        Entity* get(int id);

        int reserve(Type type, int age);
        
        void set(int id, int coord);
        void supprime(int id);

        void setEntityParams(EntityParams* entityParams);

        void clear();

        vector<Entity*>& getEntities();
        EntityParams* getParams();
        Grid& getGrid();
    private:
        Grid grid;
        int countId = 0;
        vector<Entity*> entities;

        EntityParams* params;
};

#endif