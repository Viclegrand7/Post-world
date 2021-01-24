#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Character.hh"
#include "Player.hh"
#include "Ennemy.hh"
#include "Gun.hh"
#include "Melee.hh"
#include "PowerUp.hh"

TEST_CASE("1: Gun"){
  Gun g(5, true, 3);
  REQUIRE(g.use() == -1);
  REQUIRE(g.getCurMag() == 20);
  REQUIRE(g.getCurBull() == 20);
  REQUIRE(g.attack() == true);
  REQUIRE(g.getCurBull() == 19);
  g.countDown();
  REQUIRE(g.attack() == false);
  g.countDown();
  g.countDown();
  REQUIRE(g.attack() == true);
  g.addBullet(3);
  REQUIRE(g.getCurBull() == 20);
  REQUIRE(g.secondary() == true);
}

TEST_CASE("2: Melee"){
  Melee M(1, 2, 0, 1);
  REQUIRE(M.use() == -2);
  REQUIRE(M.getRange() == 0);
  REQUIRE(M.getDamage() == 1);
  REQUIRE(M.attack() == true);
  REQUIRE(M.isAuto() == false);
  M.countDown();
  REQUIRE(M.attack() == false);
  M.countDown();
  REQUIRE(M.secondary() == true);
  M.countDown();
  REQUIRE(M.attack() == true);
}

TEST_CASE("3: PowerUp"){
  PowerUp P(1);
  REQUIRE(P.use() == 1);
}

TEST_CASE("4: Ennemy"){
  Ennemy E;
  Ennemy E2(2, 5);
  REQUIRE(E.getDamage() == 0);
  REQUIRE(E2.getDamage() == 2);
  REQUIRE(E.getHealth() == 20);
  E.getHit(E2.getDamage());
  REQUIRE(E.getHealth() == 18);
  REQUIRE(E.isDead() == false);
  E2.getHit(20);
  REQUIRE(E2.isDead() == true);
}

TEST_CASE("5: Player : weapons"){
  Player P1;
  REQUIRE(P1.getMaxHealth() == 20);
  Gun g1, g2;
  Melee k, k2;
  PowerUp up1(1), up0(0);
  REQUIRE(P1.getMaxStamina() == 5);
  P1.use(up0);
  REQUIRE(P1.getMaxStamina() == 15);
  P1.use(k);
  REQUIRE(P1.getCurrentWeapon() == 0);
  P1.use(g1);
  REQUIRE(P1.getCurrentWeapon() == 1);
  P1.use(g2);
  REQUIRE(P1.getCurrentWeapon() == 2);
  P1.use(k2);
  REQUIRE(P1.getCurrentWeapon() == 2);
  P1.changeWeapon(0);
  REQUIRE(P1.getCurrentWeapon() == 0);
  P1.prevWeapon();
  REQUIRE(P1.getCurrentWeapon() == 2);
  P1.use(up1);
  REQUIRE(P1.getWeaponDamage() == 6);
  P1.nextWeapon();
  REQUIRE(P1.getCurrentWeapon() == 0);
  REQUIRE(P1.getWeaponDamage() == 1);
  P1.nextWeapon();
  P1.dropWeapon();
  REQUIRE(P1.getCurrentWeapon() == 0);
  P1.nextWeapon();
  P1.nextWeapon();
  REQUIRE(P1.getCurrentWeapon() == 0);
}