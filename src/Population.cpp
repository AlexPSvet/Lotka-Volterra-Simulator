#include "Population.hpp"

TypeParams::TypeParams(
    int entityInit,
    int foodMin,
    int foodMax,
    int foodToReproduceLevel,
    int foodPerMove,
    int foodValue,
    int probReproduce,
    int minFreeBirth,
    vector<Type> p) : 
    entityInit(entityInit), 
    foodMin(foodMin),
    foodMax(foodMax),
    foodToReproduceLevel(foodToReproduceLevel),
    foodPerMove(foodPerMove),
    foodValue(foodValue),
    probReproduce(probReproduce),
    minFreeBirth(minFreeBirth) 
{
    preys.insert(preys.end(), p.begin(), p.end());
}

int TypeParams::getEntityInit() {
    return entityInit;
}

int TypeParams::getFoodMin() {
    return foodMin;
}

int TypeParams::getFoodMax() {
    return foodMax;
}

int TypeParams::getFoodToReproduce() {
    return foodToReproduceLevel;
}

int TypeParams::getFoodPerMove() {
    return foodPerMove;
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

Population::Population(EntityParams params, int taille) : grid(Grid{taille}), params(params) {}

Entity* Population::get(int id) {
    for (Entity* entity : entities) {
        if (entity->getId() == id) {
            return entity;
        }
    }
    return NULL;
}

int Population::reserve(Type type, int age) {
    int id = countId++;
    Entity* entity = new Entity(id, type, age);
    entities.push_back(entity);
    return id;
}

void Population::set(int id, int coord) {
    Entity* entity = get(id);
    entity->setCoord(coord);
    entity->setActive(true);


    TypeParams& typeParams = params.getTypeParams(entity->getType());
    int minFood = typeParams.getFoodMin();
    int maxFood = typeParams.getFoodMax();
    int foodLevel = minFood + rand() % (maxFood - minFood);
    
    entity->setFoodLevel(foodLevel);
    grid.setValue(coord, id);
}

void Population::supprime(int id) {
    for (int i = 0; i < entities.size(); i++) {
        Entity* entity = entities[i];
        Coord coord = entity->getCoord();
        if (entity->getId() == id) {
            delete entity;
            entities.erase(entities.begin() + i);
            grid.voidCase(coord.toInt());
            return;
        }
    }
    throw runtime_error("Failed to remove entity id.");
}

void Population::clear() {
    for (Entity* entity : entities) {
        delete entity;
    }
    entities.clear();
    grid.restartGrid();
}

vector<Entity*>& Population::getEntities() {
    return entities;
}

EntityParams& Population::getParams() {
    return params;
}

Grid& Population::getGrid() {
    return grid;
}