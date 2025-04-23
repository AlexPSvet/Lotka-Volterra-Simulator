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
            int foodValue,
            int probReproduce,
            int minFreeBirth,
            vector<Type> types
        );

        int getEntityInit();
        int getFoodInit();
        int getFoodToReproduce();
        int getFoodValue();
        int getProbToReproduce();
        int getMinFreeBirth();
        vector<Type>& getPreys();

        bool isPrey(Type type);
    private:
        const int entityInit;
        const int foodInit;
        const int foodToReproduceLevel;
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
        Population();

        Entity* get(int id) const;

        int reserve(Type type, int age);
        
        void set(int id, Coord coord);
        void supprime(int id);

        vector<Entity*>& getEntities();
        EntityParams* getParams();
        Ensemble& getIds();
    private:
        Ensemble ids;
        int countId = 0;
        vector<Entity*> entities;

        EntityParams* params;
};

#endif