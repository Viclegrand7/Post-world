#include "Spells.h"

std :: string Spells :: giveName() const {
	return att_name;
}
int Spells :: giveDamage() const {
	return att_damage;
}
int Spells :: giveCost() const {
	return att_cost;
}
int Spells :: giveNumber() const {
	return att_dot + 1;
}
bool Spells :: doesStun() const {
	return att_does_stun;
}


Spells :: Spells() : att_name("Generic spell"), att_damage(3), att_cost(2), att_dot(0), att_does_stun(0) {}
Spells :: Spells(std::string name) : att_name(name), att_damage(3), att_cost(2), att_dot(0), att_does_stun(0) {}
Spells :: Spells(std::string name, int cost) : att_name(name), att_damage(3*cost/2), att_cost(cost), att_dot(0), att_does_stun(0) {}
Spells :: Spells(std::string name, int cost, int dot) : att_name(name), att_cost(cost), att_dot(dot), att_does_stun(0) {
	switch(dot) {
		case 0 : att_damage = 3*cost/2; break;
		case 1 : att_damage = cost; break;
		case 2 : att_damage = cost; break;
		default : att_damage = cost/2; break;
	}
}
Spells :: Spells(int cost) : att_name("Generic spell"), att_damage(3*cost/2), att_cost(cost), att_dot(0), att_does_stun(0) {}
Spells :: Spells(int cost, int dot) : att_name("Generic spell"), att_cost(cost), att_dot(dot), att_does_stun(0) {
	switch(dot) {
		case 0 : att_damage = 3*cost/2; break;
		case 1 : att_damage = cost; break;
		case 2 : att_damage = cost; break;
		default : att_damage = cost/2; break;
	}
}
Spells :: Spells(std::string name,int cost, int dot, bool stuns) : att_name(name), att_cost(cost), att_dot(dot), att_does_stun(stuns) {
	switch(dot) {
		case 0 : att_damage = 3*cost/2; break;
		case 1 : att_damage = cost; break;
		case 2 : att_damage = cost; break;
		default : att_damage = cost/2; break;
	}
}
Spells :: Spells(int cost, int dot, bool stuns) : att_name("Generic spell"), att_cost(cost), att_dot(dot), att_does_stun(stuns) {
	switch(dot) {
		case 0 : att_damage = 3*cost/2; break;
		case 1 : att_damage = cost; break;
		case 2 : att_damage = cost; break;
		default : att_damage = cost/2; break;
	}
}

Spells :: ~Spells() {
	
}