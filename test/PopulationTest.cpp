#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/HeaderFiles/Population.hpp"

TEST_CASE("TypeParams getters and isPrey") {
    vector<Type> preys = {Type::rabbit};
    TypeParams tp(10, 2, 8, 6, 1, 5, 30, 2, preys);

    CHECK(tp.getEntityInit() == 10);
    CHECK(tp.getFoodMin() == 2);
    CHECK(tp.getFoodMax() == 8);
    CHECK(tp.getFoodToReproduce() == 6);
    CHECK(tp.getFoodPerMove() == 1);
    CHECK(tp.getFoodValue() == 5);
    CHECK(tp.getProbToReproduce() == 30);
    CHECK(tp.getMinFreeBirth() == 2);
    CHECK(tp.isPrey(Type::rabbit) == true);
    CHECK(tp.isPrey(Type::fox) == false);
}

TEST_CASE("EntityParams: addType and get") {
    EntityParams ep;
    TypeParams tp1(5, 1, 3, 2, 1, 2, 50, 1, {Type::rabbit});
    ep.addType(Type::rabbit, tp1);

    CHECK(ep.getTypes().size() == 1);
    CHECK(ep.getTypes()[0] == Type::rabbit);

    TypeParams& fetched = ep.getTypeParams(Type::rabbit);
    CHECK(fetched.getFoodMin() == 1);
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
}

TEST_CASE("Population set and foodLevel range") {
    EntityParams ep;
    TypeParams rabbitParams(2, 2, 6, 3, 1, 4, 70, 1, {});
    ep.addType(Type::rabbit, rabbitParams);
    Population pop(ep, 10);

    int id = pop.reserve(Type::rabbit, 1);
    pop.set(id, 0);

    Entity* e = pop.get(id);
    CHECK(e->isActive());
    CHECK(e->getCoord().toInt() == 0);
    CHECK(e->getFoodLevel() >= 2);
    CHECK(e->getFoodLevel() < 6);
}

TEST_CASE("Population supprime and clear") {
    EntityParams ep;
    TypeParams foxParams(2, 1, 4, 3, 1, 4, 70, 1, {});
    ep.addType(Type::fox, foxParams);
    Population pop(ep, 10);

    int id1 = pop.reserve(Type::fox, 2);
    pop.set(id1, 1);
    CHECK(pop.getEntities().size() == 1);

    pop.supprime(id1);
    CHECK(pop.getEntities().empty());

    int id2 = pop.reserve(Type::fox, 5);
    pop.set(id2, 2);
    CHECK(pop.getEntities().size() == 1);
    pop.clear();
    CHECK(pop.getEntities().empty());
}
