#include "Population.hpp"

Population::Population() : params{{}} {}

Entity* Population::get(int id) const {
    for (Entity* entity : entities) {
        if (entity->getId() == id) {
            return entity;
        }
    }
    return NULL;
}

Ensemble Population::getIds() const {
    return ids;
}

int Population::reserve(Type type, int age) {
    int id = entities.size();
    Entity entity(id, type, age);
    entities.push_back(&entity);
    ids.ajoute(id);
    return id;
}

void Population::set(int id) {
    Entity* entity = get(id);
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