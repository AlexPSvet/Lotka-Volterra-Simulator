#include "Population.hpp"

Population::Population() : params{{}} {}

Entity Population::get(int id) const {
    int iPosition = ids.getPosition(id);
    if (iPosition == -1) {
        throw invalid_argument("Entity doesn't exist.");
    }
    return entities[iPosition];
}

Ensemble Population::getIds() const {
    return ids;
}

int Population::reserve(Type type, int age) {
    int id = ids.cardinal();
    Ensemble ens = getIds();

    if (ens.getPosition(id) != -1) {
        throw invalid_argument("Entity already exists");
    }

    entities = (Entity*) realloc(entities, (ids.cardinal() + 1) * sizeof(Entity));
    ens.ajoute(id);
    Entity entity = entities[ids.cardinal()];
    entity.setType(type);
    return id;
}

// Tenemos que ver de qué manera hay que utilizar ensemble, y si tenemos que
// usar un vector para guardar las entidades (o con pointeurs?)

void Population::set() {
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