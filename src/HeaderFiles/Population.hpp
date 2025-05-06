#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>
#include <cstdlib>
#include "Ensemble.hpp"
#include "Coord.hpp"
#include "Entity.hpp"

/**
 * @brief Configuration parameters for a given entity type.
 */
struct TypeParams {
    /**
     * @brief Construct TypeParams with all configuration values.
     */
    TypeParams(
        int entityInit,
        int foodMin,
        int foodMax,
        int foodToReproduceLevel,
        int foodPerMove,
        int foodValue,
        int probReproduce,
        int minFreeBirth,
        std::vector<Type> types
    );

    /// Check if a given type is considered prey.
    bool isPrey(Type type);

    int entityInit;
    int foodMin;
    int foodMax;
    int foodToReproduceLevel;
    int foodPerMove;
    int foodValue;
    int probReproduce;
    int minFreeBirth;

    std::vector<Type> preys;
};

/**
 * @brief Holds configuration for all entity types in the simulation.
 */
class EntityParams {
public:
    /// Returns all types added.
    std::vector<Type>& getTypes();
    /// Returns parameters for a given type.
    TypeParams& getTypeParams(Type type);
    /// Add a new type with its associated parameters.
    void addType(Type type, TypeParams params);

private:
    std::vector<Type> types;
    std::vector<TypeParams> typeParams;
};

/**
 * @brief Manages all entities in the simulation.
 */
class Population {
public:
    /**
     * @brief Constructs a population with parameters and grid size.
     */
    Population(EntityParams params, int taille);

    /// Get pointer to entity by ID.
    Entity* get(int id);

    /// Reserve and create a new entity (returns its ID).
    int reserve(Type type, int age);

    /// Place entity on the grid and activate it.
    void set(int id, int coord);

    /// Delete entity from memory and remove it from grid.
    void supprime(int id);

    /// Clear all entities and reset the grid.
    void clear();

    /// Access all active entities.
    std::vector<Entity*>& getEntities();
    /// Access the parameters used for the population.
    EntityParams& getParams();
    /// Access the simulation grid.
    Grid& getGrid();

private:
    Grid grid;
    int countId = 0;
    std::vector<Entity*> entities;
    EntityParams params;
};

#endif
