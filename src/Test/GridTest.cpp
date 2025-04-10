#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "Grid.hpp"

TEST_CASE("Test des constructeurs de Coord") {
    Coord c1(3, 7);
    CHECK(c1.getX() == 3);
    CHECK(c1.getY() == 7);
    CHECK(c1.toInt() == 73);

    Coord c2(42);  // 42 % 10 = 2, 42 / 10 = 4
    CHECK(c2.getX() == 2);
    CHECK(c2.getY() == 4);
    CHECK(c2.toInt() == 42);
}

TEST_CASE("Test des valeurs limites") {
    Coord c1(0, 0);
    CHECK(c1.toInt() == 0);

    Coord c2(9, 9);
    CHECK(c2.toInt() == 99);

    Coord c3(99);
    CHECK(c3.getX() == 9);
    CHECK(c3.getY() == 9);
}