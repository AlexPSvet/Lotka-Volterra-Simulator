#include "Population.hpp"

TypeParams::TypeParams(
    int entityInit,
    int foodInit,
    int foodToReproduceLevel,
    int foodValue,
    int probReproduce,
    int minFreeBirth,
    vector<Type> p) : 
    entityInit(entityInit), 
    foodInit(foodInit),
    foodToReproduceLevel(foodToReproduceLevel),
    foodValue(foodValue),
    probReproduce(probReproduce),
    minFreeBirth(minFreeBirth) 
{
    preys.insert(preys.end(), p.begin(), p.end());
}

int TypeParams::getEntityInit() {
    return entityInit;
}

int TypeParams::getFoodInit() {
    return foodInit;
}

int TypeParams::getFoodToReproduce() {
    return foodToReproduceLevel;
}

int TypeParams::getFoodValue() {
    return foodValue;
}

int TypeParams::getProbToReproduce() {
    return probReproduce;
}

int TypeParams::getMinFreeBirth() {
    return minFreeBirth;
}

vector<Type>& TypeParams::getPreys() {
    return preys;
}

bool TypeParams::isPrey(Type type) {
    for (Type t : preys) {
        if (t == type) {
            return true;
        }
    }
    return false;
}

vector<Type>& EntityParams::getTypes() {
    return types;
}

TypeParams& EntityParams::getTypeParams(Type type) {
    return typeParams[int(type)];
}

void EntityParams::addType(Type type, TypeParams params) {
    types.push_back(type);
    typeParams.push_back(params);
}

Population::Population() {}

Entity* Population::get(int id) const {
    for (Entity* entity : entities) {
        if (entity->getId() == id) {
            return entity;
        }
    }
    return NULL;
}

int Population::reserve(Type type, int age) {
    int id = ++countId;
    Entity entity(id, type, age);
    entities.push_back(&entity);
    return id;
}

void Population::set(int id, Coord coord) {
    Entity* entity = get(id);
    entity->setCoord(coord);
    entity->setActive(true);
    int foodLevel = params->getTypeParams(entity->getType()).getFoodInit();
    entity->setFoodLevel(foodLevel);
}

void Population::supprime(int id) {
    for (int i = 0; i < entities.size(); i++) {
        Entity* entity = entities[i];
        if (entity->getId() == id) {
            entities.erase(entities.begin() + i);
            break;
        }
    }
}

vector<Entity*>& Population::getEntities() {
    return entities;
}

EntityParams* Population::getParams() {
    return params;
}

Ensemble& Population::getIds() {
    return ids;
}