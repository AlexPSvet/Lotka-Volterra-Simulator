#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Coord.hpp"
#include <iostream>
using namespace std;

enum class Type { rabbit, fox };

class Entity {
    public:
        Entity(int id, Type type, int age);
        Entity(int id, Type type, int age, int foodLevel);

        void eat(int amount);

        bool canReproduce(Type type);

        int getId();
        Type getType();
        int getAge();
        int getFoodLevel();
        Coord getCoord();

        void setType(Type type);
        void setAge(int age);
        void setFoodLevel(int foodLevel);
        void setCoord(Coord coord);

        ostream& operator<<(ostream& o);
    private:
        Type type;

        const int id;
        int age;
        int foodLevel;
        Coord coord;
};

#endif