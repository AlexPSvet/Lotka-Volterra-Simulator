#ifndef GAME_HPP
#define GAME_HPP

#include "Entity.hpp"
#include "Coord.hpp"
#include "Population.hpp"

/**
 * @brief Orchestrates the simulation logic, including entity behaviors and evolution.
 */
class Game {
public:
    /**
     * @brief Initializes the simulation with entity parameters and grid size.
     * @param params Configuration for all entity types.
     * @param taille Side length of the grid.
     */
    Game(EntityParams params, int taille);

    /**
     * @brief Adds a new animal to the simulation.
     * @param type The type of the animal.
     * @param age Initial age of the animal.
     * @param coord Position where the animal will be placed.
     * @return ID of the created entity.
     */
    int ajouteAnimal(Type type, int age, int coord);

    /// Initializes the population based on initial parameters.
    void setEntityInit();

    /// Checks consistency of the grid (e.g., positions of entities).
    bool verifieGrille();

    /// Returns a set of empty neighboring cells around the given coordinate.
    Ensemble emptyNeighbours(Coord cord);

    /// Returns a set of neighboring cells occupied by entities of the given type.
    Ensemble typeNeighbours(Coord cord, Type type);

    /// Moves all entities of a given type according to their rules.
    void moveType(Type type);

    /// Handles the movement logic for a single entity.
    void moveEntity(Entity* entity);

    /// Processes predation: entity eats prey at given ID.
    void eatPrey(Entity* entity, int preyId);

    /// Moves the entity to a random neighboring position.
    void moveRandom(Entity* entity);

    /// Moves entity from `oldCoord` to `newCoord`.
    void move(Entity* entity, int oldCoord, int newCoord);

    /// Proceeds to the next simulation step (e.g., time tick).
    void next();

    /// Starts the simulation (initial setup).
    void start();

    /// Stops the simulation (can be used to pause or end).
    void stop();

    /// Provides access to the underlying population object.
    Population& getPopulation();

private:
    Population population; ///< Manages all entities and grid.
};

#endif
