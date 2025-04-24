#include "Simulator.hpp"

Game::Game() {
    setEntityInit();
}

Population Game::getPopulation() {
    return population;
}

int Game::ajouteAnimal(Type type, int age, Coord coord) {
    int id = population.reserve(type, age);
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
    int cardRabbit = params->init_entities[0];
    int cardFox = params->init_entities[1];
    int cardNull = 1 - (cardFox + cardRabbit);
    for (int i = 0; i < TAILLE_GRID; i++) {
        int random = rand() % 3;
        if (random == 2) {
            continue;
        }
        Coord coord(i);
        Type type = params->types[random];
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
    Entity* entity = population.get(id);
    Coord coord = entity->getCoord();
    Ensemble neighbours = emptyNeighbours(coord);
    if (neighbours.cardinal() == 0) {
        return;
    }
    int ind = rand() % neighbours.cardinal();
    grid.voidCase(coord.toInt());
    int i = neighbours[ind];
    grid.setCase(i, id);
    Coord newCoord(i);
    entity->setCoord(newCoord);

    //Reproduction
    Type type = entity->getType();
    TypeParams& typeParams = *params->typeParams[int(type)];
    int minFreeBirth = typeParams.MIN_FREE_BIRTH;
    if (neighbours.cardinal() >= minFreeBirth) {
        int probRepro = typeParams.PROB_REPRODUCE;
        int random = rand() % 100;
        if (random <= probRepro) { //Añadir la comida
            ajouteAnimal(type, 0, coord);
        }
    }
}

void Game::moveType(Type type) {
    for (Entity *entity : population.getEntities()) {
        if (entity->getType() == type) {
            moveEntity(entity->getId());
        }
    }
}

void Game::start() {
    setEntityInit();
}


void Game::next() {
    moveType(Type::rabbit);
    moveType(Type::fox);
}

