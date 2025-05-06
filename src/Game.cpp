#include "Game.hpp"

Game::Game(EntityParams params, int taille) : population(Population{params, taille}) {}

int Game::ajouteAnimal(Type type, int age, int coord) {
    int id = population.reserve(type, age);
    population.set(id, coord);
    return id;
}

void Game::setEntityInit() {
    EntityParams& params = population.getParams();
    Ensemble emptyCases = population.getGrid().getEmptyCases();
    for (Type type : params.getTypes()) {
        TypeParams typeParams = params.getTypeParams(type);
        int init = typeParams.entityInit;
        for (int i = 0; i < init; i++) {
            int cardinal = emptyCases.cardinal();
            if (cardinal == 0) {
                return;
            }
            int randomIndex = rand() % emptyCases.cardinal();
            int coord = emptyCases[randomIndex];
            // Il faut rajouter apres l'age pour les entites.
            int id = ajouteAnimal(type, 0, coord);
            emptyCases.erase(randomIndex);
        }
    }
}

bool Game::verifieGrille() {
    for (Entity* entity : population.getEntities()) {
        Coord coord = entity->getCoord();
        int id = entity->getId();
        if (population.getGrid()[coord.toInt()] != id) {
            return false;
        }
    }
    return true;
}

Ensemble Game::emptyNeighbours(Coord cord) {
    Ensemble neighbours = cord.neighbours();
    Ensemble neighboursVides;
    Grid& grid = population.getGrid();
    for (int i=0; i < neighbours.cardinal(); i++) {
        int indice = neighbours[i];
        if (grid[indice] == -1) {
            neighboursVides.ajoute(indice);
        }
    }
    return neighboursVides;
}

Ensemble Game::typeNeighbours(Coord cord, Type type) {
    Ensemble neighbours = cord.neighbours();
    Ensemble neighboursType;
    Grid& grid = population.getGrid();
    for (int i=0; i < neighbours.cardinal(); i++) {
        int indice = neighbours[i];
        int id = grid[indice];
        if (id != -1) {
            Entity* entity = population.get(id);
            if (entity->getType() == type) {
                neighboursType.ajoute(id);
            }
        }
    }
    return neighboursType;
}

void Game::move(Entity* entity, int oldCoord, int newCoord) {
    population.getGrid().voidCase(oldCoord);
    population.getGrid().setValue(newCoord, entity->getId());
    entity->setCoord(newCoord);
}

void Game::moveRandom(Entity* entity){
    Type type = entity->getType();
    TypeParams typeParams = population.getParams().getTypeParams(type);
    Coord currentCoord = entity->getCoord();
    Ensemble neighbours = emptyNeighbours(currentCoord);

    entity->addFood(typeParams.foodPerMove);

    // If no neighbours, can't move.
    if (neighbours.cardinal() == 0) {
        return;
    }

    // Move entity to random neighbour coordinate.
    int ind = rand() % neighbours.cardinal();
    move(entity, currentCoord.toInt(), neighbours[ind]);

    int minFreeBirth = typeParams.minFreeBirth;
    int foodToReproduce = typeParams.foodToReproduceLevel;
    if (neighbours.cardinal() >= minFreeBirth && entity->getFoodLevel() > foodToReproduce) {
        int probRepro = typeParams.probReproduce;
        int random = rand() % 100;
        if (random <= probRepro) {
            ajouteAnimal(type, 0, currentCoord.toInt());
            // entity->addFood(-foodToReproduce); Need to see...
        }
    }
}

void Game::eatPrey(Entity* entity, int preyId) {
    Entity* prey = population.get(preyId);
    Coord preyCoord = prey->getCoord();
    Type preyType = prey->getType();
    TypeParams params = population.getParams().getTypeParams(preyType);
    entity->addFood(params.foodValue);
    population.supprime(preyId);
    move(entity, entity->getCoord().toInt(), preyCoord.toInt());
}

void Game::moveEntity(Entity* entity) {
    Coord coord = entity->getCoord();
    Type type = entity->getType();
    TypeParams typeParams = population.getParams().getTypeParams(type);

    // If he hasn't enough food to reproduce, and there are preys, then eat one of them.
    if (entity->getFoodLevel() <= typeParams.foodMin) {
        for (Type& preyType : typeParams.preys) {
            Ensemble preys = typeNeighbours(coord, preyType);
            if (preys.cardinal() != 0) {
                int ind = rand() % preys.cardinal();
                int preyId = preys[ind];
                eatPrey(entity, preyId);
                return;
            }
        }
    }

    // If not, simply move.
    moveRandom(entity);

    // If entity has no food, it dies.
    if (entity->getFoodLevel() <= 0) {
        population.supprime(entity->getId());
        return;
    }
}

void Game::moveType(Type type) {
    Grid& grid = population.getGrid();
    for (int i = 0; i < grid.cardinal(); i++) {
        int id = grid[i];
        if (id == -1) {
            continue;
        }
        Entity* entity = population.get(id);
        if (entity->getType() == type) {
            moveEntity(entity);
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

void Game::stop() {
    population.clear();
}

Population& Game::getPopulation() {
    return population;
}