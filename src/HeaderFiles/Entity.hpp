#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Coord.hpp"
#include <iostream>
using namespace std;

enum class Type { rabbit, fox };
Type types[2] = { Type::rabbit, Type::fox };

class Entity {
    public:
        Entity(int id, Type type, int age);
        Entity(int id, Type type, int age, int foodLevel);

        void eat(int amount);

        bool canReproduce(Type type) const;

        int getId() const;
        Type getType() const;
        int getAge() const;
        int getFoodLevel() const;
        Coord getCoord() const;
        bool isActive() const;

        void setType(Type type);
        void setAge(int age);
        void setFoodLevel(int foodLevel);
        void setCoord(Coord coord);
        void setActive(bool value);

        ostream& operator<<(ostream& o) const;
    private:
        Type type;

        const int id;
        int age;
        int foodLevel;
        bool active;
        Coord coord;
};

#endif