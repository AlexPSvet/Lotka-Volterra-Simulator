#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
using namespace std;

enum class Type { rabbit, fox };

const struct EntityParams {
    int FOOD_INIT;
    int FOOD_TO_REPRODUCE_LEVEL;
    int PROB_REPRODUCE;
};

class Entity {
    public:
        bool isPrey(Type type);
        bool canReproduce(Type type);

        Type getType();
        int getAge();
        int getFoodLevel();

        void setType(Type type);
        int setAge();
        int setFoodLevel();
    private:
        Type type;
        vector<Type> preys;
        EntityParams params;

        int age;
        int foodLevel;
};

#endif