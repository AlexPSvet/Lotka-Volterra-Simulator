//
// Created by desarrollo on 3/4/25.
//
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "../HeaderFiles/Ensemble.hpp"

TEST_CASE("Test Ensemble::estVide") {
    Ensemble e;
    CHECK(e.estVide() == true);
    e.ajoute(1);
    CHECK(e.estVide() == false);
}

TEST_CASE("Test Ensemble::cardinal") {
    Ensemble e;
    CHECK(e.cardinal() == 0);
    e.ajoute(5);
    CHECK(e.cardinal() == 1);
    e.ajoute(10);
    CHECK(e.cardinal() == 2);
}

TEST_CASE("Test Ensemble::ajoute") {
    Ensemble e;
    e.ajoute(5);
    CHECK(e.cardinal() == 1);
    CHECK(e.estVide() == false);
    e.ajoute(3);
    e.ajoute(7);
    CHECK(e.cardinal() == 3);
}

TEST_CASE("Test Ensemble::ajoute exceeding MAXCARD") {
    Ensemble e;
    for (int i = 0; i < MAXCARD; ++i) {
        e.ajoute(i);
    }
    CHECK_THROWS_AS(e.ajoute(MAXCARD), std::invalid_argument);
}

TEST_CASE("Test Ensemble::tire") {
    Ensemble e;
    e.ajoute(3);
    e.ajoute(7);
    e.ajoute(10);
    int before = e.cardinal();
    e.tire();
    CHECK(e.cardinal() == before - 1);
}

TEST_CASE("Test Ensemble::tire when empty") {
    Ensemble e;
    CHECK_NOTHROW(e.tire());
}

TEST_CASE("Test Ensemble::ajoute and tire combined") {
    Ensemble e;
    e.ajoute(1);
    e.ajoute(2);
    e.ajoute(3);
    CHECK(e.cardinal() == 3);
    e.tire();
    CHECK(e.cardinal() == 2);
    e.tire();
    CHECK(e.cardinal() == 1);
    e.tire();
    CHECK(e.cardinal() == 0);
    CHECK(e.estVide() == true);
}
