#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Character.hh"
#include "Player.hh"
#include "Ennemy.hh"
#include "Gun.hh"
#include "Melee.hh"
#include "PowerUp.hh"

TEST_CASE("1: Gun"){
  Gun g;
  REQUIRE(g.use() == 1);
  REQUIRE(g.getCurMag() == 20);
  REQUIRE(g.getCurBull() == 20);
  REQUIRE(g.attack() == true);
  REQUIRE(g.getCurBull() == 19);
  g.addBullet(3);
  REQUIRE(g.getCurBull() == 20);
  REQUIRE(g.secondary() == true);
}

TEST_CASE("2: Melee"){
  Melee M;
  REQUIRE(M.use() == 0);
  REQUIRE(M.getRange() == 0);
  REQUIRE(M.getDamage() == 1);
  REQUIRE(M.attack() == true);
  REQUIRE(M.isAuto() == false);
}

TEST_CASE("3: PowerUp"){
  PowerUp P;
  REQUIRE(P.use() == 2);
}
/*
TEST_CASE("4: Ennemy"){
  Ennemy E;
  //Ennemy E2(2, 5);
  //REQUIRE(E.getDamage() == 0);
  //REQUIRE(E2.getDamage() == 2);
  //REQUIRE(E.getHealth() == 100);
  //E.getHit(E2.getDamage());
  //REQUIRE(E.getHealth() == 98);
  //REQUIRE(E.isDead() == false);
  //E2.getHit(100);
  //REQUIRE(E2.isDead() == true);
}*/