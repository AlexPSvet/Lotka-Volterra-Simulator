#include "Population.hpp"

Population::Population() : params{{}} {}

Entity Population::get(int id) const {
    for (Entity* entity : entities) {
        if (entity->getId() == id) {
            return *entity;
        }
    }
}

Ensemble Population::getIds() const {
    // lol
}

int Population::reserve(Type type, int age) {
    int id = entities.size();
    
    return id;
}

// Tenemos que ver de qué manera hay que utilizar ensemble, y si tenemos que
// usar un vector para guardar las entidades (o con pointeurs?)

void Population::set(int id) {
    //lol
}

void Population::supprime(int id) {
    /*
    for (int i=0; i<entities.size(); i++) {
        if (id == entities[i].getId()) {
            entities.erase(entities.begin() + i);
            params.erase(params.begin() + i);
        }
    }
    */
}