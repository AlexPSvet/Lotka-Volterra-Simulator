#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Coord.hpp"

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

TEST_CASE("Coord constructors and behavior") {
    // Default constructor
    Coord c0;
    CHECK(c0.getX() == -1);  // 1
    CHECK(c0.getY() == -1);  // 2

    // 1D index constructor
    Coord c1(0);
    CHECK(c1.getX() == 0);   // 3
    CHECK(c1.getY() == 0);   // 4
    CHECK(c1.toInt() == 0);  // 5

    Coord c2(TAILLE_GRID - 1);
    CHECK(c2.getX() == TAILLE_GRID - 1);  // 6
    CHECK(c2.getY() == 0);                // 7

    Coord c3(TAILLE_GRID); // should be (0,1)
    CHECK(c3.getX() == 0);  // 8
    CHECK(c3.getY() == 1);  // 9
    CHECK(c3.toInt() == TAILLE_GRID);  // 10

    Coord c4(99);
    CHECK(c4.getX() == 9);  // 11
    CHECK(c4.getY() == 9);  // 12
    CHECK(c4.toInt() == 99);  // 13

    // (x, y) constructor
    Coord c5(3, 4);
    CHECK(c5.getX() == 3);  // 14
    CHECK(c5.getY() == 4);  // 15
    CHECK(c5.toInt() == 43); // 16

    Coord c6(0, 0);
    CHECK(c6.getX() == 0);  // 17
    CHECK(c6.getY() == 0);  // 18
    CHECK(c6.toInt() == 0); // 19

    Coord c7(9, 9);
    CHECK(c7.getX() == 9);  // 20
    CHECK(c7.getY() == 9);  // 21
    CHECK(c7.toInt() == 99); // 22

    // Equality / Inequality
    Coord a(2, 3);
    Coord b(2, 3);
    Coord d(3, 2);
    CHECK(a == b); // 23
    CHECK_FALSE(a != b); // 24
    CHECK(a != d); // 25

    // (x, y) constructor bounds checking (try-catch)
    try {
        Coord(-1, 0);
        CHECK(false); // Should not reach here 26
    } catch (const std::runtime_error&) {
        CHECK(true);  // 27
    }

    try {
        Coord(10, 10);
        CHECK(false); // 28
    } catch (const std::runtime_error&) {
        CHECK(true);  // 29
    }

    // Check round-trip (Coord → int → Coord)
    Coord c8(7, 5);
    Coord c9(c8.toInt());
    CHECK(c8 == c9); // 30
}