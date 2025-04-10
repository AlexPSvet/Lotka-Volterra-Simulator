#include "Population.hpp"

Population::Population() : entities{{}}, params{{}} {}

Entity Population::get(int id) const {
    for (Entity entity : entities) {
        if (id == entity.getId()) {
            return entity;
        }
    }
}

Ensemble Population::getIds() const {
    
}

int Population::reserve(Type type, int age) {
    int id = rand() % 1000;
    Ensemble ens = getIds();
    if (id in ens) {
        throw invalid_argument("Entity already exists");
    }
    Entity(id, type, age); //meterle un Malloc
    return id;
}

void Population::set() {
    //lol
}

void Population::supprime(int id) {
    for (int i=0; i<entities.size(); i++) {
        if (id == entities[i].getId()) {
            entities.erase(entities.begin() + i);
            params.erase(params.begin() + i);
        }
    }
}
