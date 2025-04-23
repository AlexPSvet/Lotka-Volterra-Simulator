#include "Population.hpp"

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
    int id = entities.size();
    Entity entity(id, type, age);
    entities.push_back(&entity);
    return id;
}

void Population::set(int id, Coord coord) {
    Entity* entity = get(id);
    entity->setCoord(coord);
    entity->setActive(true);
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

vector<Entity*> Population::getEntities() {
    return entities;
}