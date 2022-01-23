#define CATCH_CONFIG_MAIN

#include <iostream>
#include <fstream>
#include <list>
#include "catch.hpp"
#include "Entity.hpp"


using namespace std;


TEST_CASE("1 : Entity placement and movement", "{Entity}")
{
    Entity e(150, 0);

    REQUIRE(e.x() == 150);
    REQUIRE(e.efficientX() == 150);
    REQUIRE(e.y() == 0);
    REQUIRE(e.efficientY() == 0);

    e.move(50, 25);
    REQUIRE(e.x() == 200);
    REQUIRE(e.efficientX() == 200);
    REQUIRE(e.y() == 25);
    REQUIRE(e.efficientY() == 25);

     e += (-50.25);
    REQUIRE(e.x() == 150);
    REQUIRE(e.efficientX() == 150);
    REQUIRE(e.y() == 0);
    REQUIRE(e.efficientY() == 0);

    e.setPosition(25, 200, 0);
    REQUIRE(e.x() == 25);
    REQUIRE(e.efficientX() == 25);
    REQUIRE(e.y() == 0);
    REQUIRE(e.efficientY() == 200);
}

TEST_CASE("2 : Entities collision", "{Entities}")
{
    Entity e1(0, -100), e2(200, -300);

    /*
-300|                     e2-----------------*
    |                     |                  |
    |                     |                  |
    |                     |                  |
    |                     |                  |
-200|                     *------------------*
    |
    |
    |
    |
-100|e1------------------*
    ||                   |
    ||                   |
    ||                   |
    |*-------------------*
   0 ----------------------------------------
    0          100       200       300       400
    */

    REQUIRE(!e1.collideWith(&e2));
    e2.setPosition(200, -100, -100);


    /*
-300|
    |
    |
    |
    |
-200|                    e2-----------------*
    |                    |                  |
    |                    |                  |
    |                    |                  |
    |                    |                  |
-100|e1------------------*------------------*
    ||                   |
    ||                   |
    ||                   |
    |*-------------------*
   0 ----------------------------------------
    0          100       200       300       400
    */

    REQUIRE(e1.collideWith(&e2));
    e2.setPosition(100, -50, -50);

    /*
-300|
    |
    |
    |
    |
-200|
    |
    |          e2------------------*
    |          |                   |
    |          |                   |
-100|e1------------------*         |
    ||         |         |         |
    ||         *---------|---------*
    ||                   |
    |*-------------------*
   0 ----------------------------------------
    0          100       200       300       400
    */

    REQUIRE(e1.collideWith(&e2));
    e2.setPosition(0, -100, -100);

    /*
-300|
    |
    |
    |
    |
-200|
    |
    |
    |
    |
-100|e1+e2---------------*
    ||                   |
    ||                   |
    ||                   |
    |*-------------------*
   0 ----------------------------------------
    0          100       200       300       400
    */

    REQUIRE(e1.collideWith(&e2));
}

TEST_CASE("3 : Entities distance", "{Entities}")
{
    Entity e1(0, 0), e2(5, 0);

    REQUIRE(e1.distance(&e2) == 5);

    e2.setPosition(0, 5, 5);
    REQUIRE(e1.distance(&e2) == 5);

    e2.setPosition(3, 4, 4);
    REQUIRE(e1.distance(&e2) == 5);

    e2.setPosition(0, 0, 0);
    REQUIRE(!e1.distance(&e2));
}

TEST_CASE("4 : Entity sprite counting", "{Entity}")
{
    Entity e(0, 0);

    REQUIRE(!e.spriteCounter());

    e.nextFrame();
    REQUIRE(e.spriteCounter() == 1);

    e.nextFrame();
    REQUIRE(e.spriteCounter() == 2);

    e.nextFrame();
    REQUIRE(!e.spriteCounter());

    e.spriteCounter(2);
    REQUIRE(e.spriteCounter() == 2);

    e.nextFrame();
    REQUIRE(!e.spriteCounter());
}

TEST_CASE("5 : Adding Entities to scene", "{Entities}")
{
    list<Entity*> entitiesList;
    Entity e1(0, 0), e2(0, 0);

    e1.addItemToScene(&e1, &entitiesList);
    REQUIRE(entitiesList.front() == &e1);

    e1.addItemToScene(&e2, &entitiesList);
    REQUIRE(entitiesList.front() == &e1);
    REQUIRE(entitiesList.back()  == &e2);
    REQUIRE(entitiesList.size()  == 2  );
}

TEST_CASE("6 : Entity's invincibility", "{Entity}")
{
    Entity e(0, 0);
    REQUIRE(!e.invincible());

    e.invincible(true);
    REQUIRE(e.invincible());
}
