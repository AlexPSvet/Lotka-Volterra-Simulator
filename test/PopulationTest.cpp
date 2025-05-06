#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Population.hpp"

TEST_CASE("TypeParams getters and isPrey") {
    vector<Type> preys = {Type::rabbit};
    TypeParams tp(10, 2, 8, 6, 1, 5, 30, 2, preys);

    CHECK(tp.entityInit == 10);
    CHECK(tp.foodMin == 2);
    CHECK(tp.foodMax == 8);
    CHECK(tp.foodToReproduceLevel == 6);
    CHECK(tp.foodPerMove == 1);
    CHECK(tp.foodValue == 5);
    CHECK(tp.probReproduce == 30);
    CHECK(tp.minFreeBirth == 2);
    CHECK(tp.isPrey(Type::rabbit));
    CHECK_FALSE(tp.isPrey(Type::fox));
}

TEST_CASE("EntityParams: addType and get") {
    EntityParams ep;
    TypeParams tp1(5, 1, 3, 2, 1, 2, 50, 1, {Type::rabbit});
    ep.addType(Type::rabbit, tp1);

    CHECK(ep.getTypes().size() == 1);
    CHECK(ep.getTypes()[0] == Type::rabbit);

    TypeParams& fetched = ep.getTypeParams(Type::rabbit);
    CHECK(fetched.foodMin == 1);
    CHECK(fetched.isPrey(Type::rabbit));
}

TEST_CASE("Population basic creation and reserve") {
    EntityParams ep;
    TypeParams rabbitParams(2, 1, 5, 3, 1, 4, 70, 1, {});
    ep.addType(Type::rabbit, rabbitParams);

    Population pop(ep, 10);
    CHECK(pop.getEntities().size() == 0);

    int id = pop.reserve(Type::rabbit, 3);
    CHECK(pop.getEntities().size() == 1);

    Entity* e = pop.get(id);
    CHECK(e != nullptr);
    CHECK(e->getAge() == 3);
    CHECK(e->getType() == Type::rabbit);

    pop.clear();
}
