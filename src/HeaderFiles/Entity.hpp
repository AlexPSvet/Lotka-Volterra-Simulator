#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
using namespace std;

enum class Type { rabbit, fox };

const struct EntityType {
    Type type;
    int FOOD_INIT; 
};

class Entity {
    public:
    private:
        EntityType type;
        vector<EntityType> preys;

        int food;
};

#endif