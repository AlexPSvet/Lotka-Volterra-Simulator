#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/HeaderFiles/Entity.hpp"

TEST_CASE("Entity constructor and getters") {
    Entity rabbit(1, Type::rabbit, 2);
    CHECK(rabbit.getId() == 1);
    CHECK(rabbit.getType() == Type::rabbit);
    CHECK(rabbit.getAge() == 2);
    CHECK(rabbit.getFoodLevel() == 0);
    CHECK(rabbit.isActive() == false); // Assuming default inactive
}

TEST_CASE("Entity constructor with foodLevel") {
    Entity fox(2, Type::fox, 3, 5);
    CHECK(fox.getId() == 2);
    CHECK(fox.getType() == Type::fox);
    CHECK(fox.getAge() == 3);
    CHECK(fox.getFoodLevel() == 5);
}

TEST_CASE("Entity can eat") {
    Entity e(3, Type::rabbit, 1, 2);
    e.eat(3);
    CHECK(e.getFoodLevel() == 5);
}

TEST_CASE("Entity can reproduce") {
    Entity rabbit(4, Type::rabbit, 3);
    CHECK(rabbit.canReproduce(Type::rabbit));

    Entity fox(5, Type::fox, 2);
    CHECK_FALSE(fox.canReproduce(Type::rabbit));
}

TEST_CASE("Entity setters and coord") {
    Entity e(6, Type::fox, 1);
    Coord c = {2, 3};
    e.setCoord(c);
    e.setAge(5);
    e.setFoodLevel(8);
    e.setActive(true);
    CHECK(e.getCoord() == c);
    CHECK(e.getAge() == 5);
    CHECK(e.getFoodLevel() == 8);
    CHECK(e.isActive());
}