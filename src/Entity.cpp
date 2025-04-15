#include "Entity.hpp"

Entity::Entity(int id, Type type, int age) : id{id}, type{type}, age{age} {}

Entity::Entity(int id, Type type, int age, int foodLevel) : id{id}, type{type}, age{age}, foodLevel{foodLevel} {}

void Entity::eat(int amount) {
    foodLevel += amount;
}

bool Entity::canReproduce(Type type) const {
    return this->type == type;
}

int Entity::getId() const {
    return id;
}

Type Entity::getType() const {
    return type;
}

int Entity::getAge() const {
    return age;
}

int Entity::getFoodLevel() const {
    return foodLevel;
}

Coord Entity::getCoord() const {
    return coord;
}

bool Entity::isActive() const {
    return active;
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

void Entity::setActive(bool value) {
    active = value;
}

ostream& Entity::operator<<(ostream& o) const {
    switch (type) {
        case Type::rabbit:
            o << "R";
            break;
        case Type::fox:
            o << "F";
    }
    return o;
}