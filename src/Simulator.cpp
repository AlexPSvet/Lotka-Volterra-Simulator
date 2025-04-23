#include "Simulator.hpp"

Game::Game() {
    setEntityInit();
}

int Game::ajouteAnimal(Type type, int age, Coord coord) {
    int id = population.reserve(type, age);
    Entity* entity = population.get(id);
    population.set(id, coord);
    return id;
}

void modifie(int& card, int& i, Grid& grid, int id) {
    if (card > 0){
        grid.setCase(id, i);
        card--;
    } else {
        i--;
    }
}

void Game::setEntityInit() {
    int cardRabbit = INIT_ENTITIES[0];
    int cardFox = INIT_ENTITIES[1];
    int cardNull = 1 - (cardFox + cardRabbit);
    for (int i = 0; i < TAILLE_GRID; i++) {
        int random = rand() % 3;
        if (random == 2) {
            continue;
        }
        Coord coord(i);
        Type type = types[random];
        int id = ajouteAnimal(type, 0, coord);
        switch (random) {
            case 0:
                modifie(cardRabbit, i, grid, id);
                break;
            case 1:
                modifie(cardFox, i, grid, id);
                break;
        }
    }
}

bool Game::verifieGrille() {
    for (Entity* entity : population.getEntities()) {
        Coord coord = entity->getCoord();
        int id = entity->getId();
        if (grid.getCase(coord.toInt()) != id) {
            return false;
        }
    }
    return true;
}

Ensemble Game::emptyNeighbours(Coord cord) {
    Ensemble neighbours = cord.neighbours();
    Ensemble neighboursVides;
    for (int i=0; i<neighbours.cardinal(); i++) {
        if (neighbours[i] == -1) {
            neighboursVides.ajoute(i);
        }
    }
    return neighboursVides;
}

Ensemble Game::typeNeighbours(Coord cord, Type type) {
    Ensemble neighbours = cord.neighbours();
    Ensemble neighboursType;
    for (int i=0; i < neighbours.cardinal(); i++) {
        int value = neighbours[i]; 
        if (value != -1){
            Entity* entity = population.get(value);
            if (entity->getType() == type) {
                neighboursType.ajoute(i);
            }
        }
    }
    return neighboursType;
}

void Game::moveEntity(int id){
    Coord coord = population.get(id)->getCoord();
    Ensemble neighbours = emptyNeighbours(coord);
    if (neighbours.cardinal() == 0) {
        return;
    }
    int ind = rand() % neighbours.cardinal();
    grid.voidCase(coord.toInt());
    grid.setCase(neighbours[ind], id);
}