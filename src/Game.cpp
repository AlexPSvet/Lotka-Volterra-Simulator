#include "Game.hpp"

Game::Game(EntityParams& params, int taille) : population(Population{taille}) {
    population.setEntityParams(&params);
    setEntityInit();
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
    EntityParams* params = population.getParams();
    for (Type type : params->getTypes()) {
        TypeParams typeParams = params->getTypeParams(type);
        int init = typeParams.getEntityInit();
        Ensemble emptyCases = population.getGrid().getEmptyCases();
        for (int i = 0; i < init; i++) {
            int randomIndex = rand() % emptyCases.cardinal();
            int caseId = emptyCases[randomIndex];
            // Il faut rajouter apres l'age pour les entites.
            ajouteAnimal(type, 0, Coord(caseId));
        }
    }
}

bool Game::verifieGrille() {
    for (Entity* entity : population.getEntities()) {
        Coord coord = entity->getCoord();
        int id = entity->getId();
        if (population.getGrid().getValue(coord.toInt()) != id) {
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
        if (grid.getValue(i) == -1) {
            neighboursVides.ajoute(i);
        }
    }
    return neighboursVides;
}

Ensemble Game::typeNeighbours(Coord cord, Type type) {
    Ensemble neighbours = cord.neighbours();
    Ensemble neighboursType;
    Grid& grid = population.getGrid();
    for (int i=0; i < neighbours.cardinal(); i++) {
        int value = grid.getValue(i);
        if (value != -1){
            Entity* entity = population.get(value);
            if (entity->getType() == type) {
                neighboursType.ajoute(i);
            }
        }
    }
    return neighboursType;
}

void Game::move(Entity* entity, int oldCoord, int newCoord) {
    population.getGrid().voidCase(oldCoord);
    population.getGrid().setCase(newCoord, entity->getId());
    entity->setCoord(newCoord);
}

void Game::moveRandom(int id){
    Entity* entity = population.get(id);
    Coord currentCoord = entity->getCoord();
    Ensemble neighbours = emptyNeighbours(currentCoord);
    // If no neighbours, can't move.
    if (neighbours.cardinal() == 0) {
        return;
    }

    // Move entity to random neighbour coordinate.
    int ind = rand() % neighbours.cardinal();
    move(entity, currentCoord.toInt(), neighbours[ind]);
}

void Game::eatPrey(int entityId, int preyId) {
    Entity* entity = population.get(entityId);
    Entity* prey = population.get(preyId);
    Coord preyCoord = prey->getCoord();

    population.supprime(preyId);

    Type preyType = prey->getType();
    TypeParams params = population.getParams()->getTypeParams(preyType);
    entity->setFoodLevel(entity->getFoodLevel() + params.getFoodValue());
}

void Game::moveEntity(int id) {
    Entity* entity = population.get(id);
    Coord coord = entity->getCoord();
    Type type = entity->getType();
    TypeParams typeParams = population.getParams()->getTypeParams(type);
    Ensemble neighbours = emptyNeighbours(coord);

    // If no neighbours, can't move.
    if (neighbours.cardinal() == 0) {
        return;
    }

    // If preys, then eat one of them.
    for (Type preyType : typeParams.getPreys()) {
        Ensemble preys = typeNeighbours(coord, preyType);
        if (preys.cardinal() != 0) {
            int ind = rand() % preys.cardinal();
            int preyId = preys[ind];
            eatPrey(entity->getId(), preyId);
            return;
        }
    }

    // If not, move and reproduce if possible.
    moveRandom(entity->getId());
    int minFreeBirth = typeParams.getMinFreeBirth();
    int foodToReproduce = typeParams.getFoodToReproduce();
    if (neighbours.cardinal() >= minFreeBirth && entity->getFoodLevel() >= foodToReproduce) {
        int probReproLapin = typeParams.getProbToReproduce();
        int random = rand() % 100;
        if (random <= probReproLapin) {
            ajouteAnimal(type, 0, coord);
        }
        entity->setFoodLevel(entity->getFoodLevel() - foodToReproduce);
    }
}

void Game::moveType(Type type) {
    for (Entity* entity : population.getEntities()) {
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

void Game::stop() {
    population.getEntities().clear();

}

Population& Game::getPopulation() {
    return population;
}