#include "Entity.hpp"

Entity::Entity(int id, Type type, int age) : id{id}, type{type}, age{age} {}

Entity::Entity(int id, Type type, int age, int foodLevel) : id{id}, type{type}, age{age}, foodLevel{foodLevel} {}

void Entity::eat(int amount) {
    foodLevel += amount;
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

Coord Entity::getCoord() {
    return coord;
}

void Entity::setType(Type type) {
    this->type = type;
}

void Entity::setAge(int age) {
    this->age = age;
}

void Entity::setFoodLevel(int foodLevel) {
    this->foodLevel = foodLevel;
}

void Entity::setCoord(Coord coord) {
    this->coord = coord;
}

ostream& Entity::operator<<(ostream& o) {
    switch (type) {
        case Type::rabbit:
            o << "R";
            break;
        case Type::fox:
            o << "F";
    }
    return o;
}