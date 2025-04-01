#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
using namespace std;

enum class Type { rabbit, fox };

class Entity {
    public:
        Entity(int id, Type type, int age);
        Entity(int id, Type type, int age, int foodLevel);

        bool isPrey(Type type);
        bool canReproduce(Type type);

        int getId();
        Type getType();
        int getAge();
        int getFoodLevel();

        void setAge(int age);
        void setFoodLevel(int foodLevel);
    private:
        const Type type;
        vector<Type> preys;

        const int id;
        int age;
        int foodLevel;
};

#endif