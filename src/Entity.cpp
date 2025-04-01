#include "Entity.hpp"

Entity::Entity(int id, Type type, int age) : id{id}, type{type}, age{age} {}

Entity::Entity(int id, Type type, int age, int foodLevel) : id{id}, type{type}, age{age}, foodLevel{foodLevel} {}

bool Entity::isPrey(Type type) {
    for (Type preyType : preys) {
        if (preyType == type) {
            return true;
        }
    }
    return false;
}

bool Entity::canReproduce(Type type) {
    return this->type == type;
}

int Entity::getId() {
    return id;
}

Type Entity::getType() {
    return type;
}

int Entity::getAge() {
    return age;
}

int Entity::getFoodLevel() {
    return foodLevel;
}

void Entity::setAge(int age) {
    this->age = age;
}

void Entity::setFoodLevel(int foodLevel) {
    this->foodLevel = foodLevel;
}