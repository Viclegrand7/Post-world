#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Character.hh"
#include "Player.hh"
#include "Ennemy.hh"
#include "Gun.hh"
#include "Melee.hh"
#include "PowerUp.hh"


TEST_CASE("1: PowerUp"){
  PowerUp P(1);
  REQUIRE(P.use() == 1);
}

TEST_CASE("2: Ennemy"){
  Ennemy E;
  Ennemy E2(2, 5);
  REQUIRE(E.getDamage() == 1);
  REQUIRE(E2.getDamage() == 2);
  REQUIRE(E.getHealth() == 20);
  E.getHit(E2.getDamage());
  REQUIRE(E.getHealth() == 18);
  REQUIRE(E.isDead() == false);
  E2.getHit(20);
  REQUIRE(E2.isDead() == true);
}

TEST_CASE("3: Player : weapons"){
  Player P1;
  REQUIRE(P1.getMaxHealth() == 20);
  Gun g1, g2;
  Melee k, k2;
  PowerUp up1(1), up0(0);
  REQUIRE(P1.getMaxStamina() == 5);
  P1.use(up0);
  REQUIRE(P1.getMaxStamina() == 15);
  P1.use(k);
  REQUIRE(P1.getCurrentWeapon() == 1);
  P1.use(g1);
  REQUIRE(P1.getCurrentWeapon() == 2);
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
  P1.nextWeapon();
  P1.dropWeapon();
  REQUIRE(P1.getCurrentWeapon() == 0);
  P1.nextWeapon();
  P1.nextWeapon();
  REQUIRE(P1.getCurrentWeapon() == 0);
}

TEST_CASE("4: Player : Gun"){
  Player P1;
  Gun g(5, true, 3);
  Melee M(1, 2, 0, 1);
  REQUIRE(g.use() == -1);
  REQUIRE(g.getCurMag() == 20);
  REQUIRE(g.getCurBull() == 20);
  REQUIRE(g.isShooting() == false);
  REQUIRE(g.attack() == false);  //isShooting = false
  P1.use(g);
  REQUIRE(P1.getCurrentWeapon() == 1);
  REQUIRE(P1.attack() == false);
  P1.toAttack();
  REQUIRE(g.isShooting() == true);
  REQUIRE(P1.attack() == true);
  REQUIRE(g.getCurMag() == 19);
  g.countDown();
  REQUIRE(P1.attack() == false);
  g.countDown();
  g.countDown();
  REQUIRE(P1.attack() == true);
  g.addBullet(3);
  REQUIRE(g.getCurBull() == 20);
  REQUIRE(g.secondary() == true);
}


TEST_CASE("5: Player : Melee"){
  Player P1;
  Melee M(1, 2, 0, 1);
  REQUIRE(M.use() == -2);
  REQUIRE(M.getRange() == 0);
  REQUIRE(M.getDamage() == 1);
  REQUIRE(M.isAuto() == false);
  P1.use(M);
  REQUIRE(P1.getCurrentWeapon() == 1);
  P1.toAttack();
  REQUIRE(P1.attack() == true);
  M.countDown();
  REQUIRE(P1.attack() == false);
  M.countDown();
  REQUIRE(P1.attack() == true);
}
