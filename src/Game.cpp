#include "HeaderFiles/Game.hpp"
#include "HeaderFiles/Coord.hpp"

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
        int init = typeParams.getEntityInit();
        for (int i = 0; i < init; i++) {
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
    TypeParams typeParams = population.getParams().getTypeParams(entity->getType());
    population.getGrid().voidCase(oldCoord);
    population.getGrid().setValue(newCoord, entity->getId());
    entity->setCoord(newCoord);
    entity->addFood(typeParams.getFoodPerMove());
}

void Game::moveRandom(Entity* entity){
    Coord currentCoord = entity->getCoord();
    Ensemble neighbours = emptyNeighbours(currentCoord);
    // If no neighbours, can't move.
    if (neighbours.cardinal() == 0) {
        return;
    }

    // Move entity to random neighbour coordinate.
    int ind = rand() % neighbours.cardinal();
    move(entity, currentCoord.toInt(), neighbours[ind]);

    Type type = entity->getType();
    TypeParams typeParams = population.getParams().getTypeParams(type);
    int minFreeBirth = typeParams.getMinFreeBirth();
    int foodToReproduce = typeParams.getFoodToReproduce();
    if (neighbours.cardinal() >= minFreeBirth && entity->getFoodLevel() >= foodToReproduce) {
        int probRepro = typeParams.getProbToReproduce();
        int random = rand() % 100;
        if (random <= probRepro) {
            ajouteAnimal(type, 0, currentCoord.toInt());
            entity->addFood(-foodToReproduce);
        }
    }
}

void Game::eatPrey(Entity* entity, int preyId) {
    Entity* prey = population.get(preyId);
    Coord preyCoord = prey->getCoord();
    Type preyType = prey->getType();
    TypeParams params = population.getParams().getTypeParams(preyType);
    entity->addFood(params.getFoodValue());
    population.supprime(preyId);
    move(entity, entity->getCoord().toInt(), preyCoord.toInt());
}

void Game::moveEntity(Entity* entity) {
    Coord coord = entity->getCoord();
    Type type = entity->getType();
    TypeParams typeParams = population.getParams().getTypeParams(type);
    Ensemble neighbours = emptyNeighbours(coord);

    // If no neighbours, can't move.
    if (neighbours.cardinal() == 0) {
        return;
    }

    // If entity has no food, it dies.
    if (entity->getFoodLevel() <= 0) {
        population.supprime(entity->getId());
        return;
    }

    // If preys, then eat one of them.
    for (Type preyType : typeParams.getPreys()) {
        Ensemble preys = typeNeighbours(coord, preyType);
        if (preys.cardinal() != 0) {
            int ind = rand() % preys.cardinal();
            int preyId = preys[ind];
            eatPrey(entity, preyId);
            return;
        }
    }

    // If not, move and reproduce if possible.
    moveRandom(entity);
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