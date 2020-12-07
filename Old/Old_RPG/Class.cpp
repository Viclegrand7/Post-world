#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

class Spell {
	//Attributes
private : 
	string name;
	int cost;
	int damage;
	int dot; //Damage Over Time
};

class Spells {
	//Attributes
private:
	int number;
	Spell *Tab;
};

class Character {
	//Attributes
private : 
	string name;
	
	int max_HP;
	int cur_HP;
	int max_MP;
	int cur_MP;

	int physic;
	int magic;
	int social;
	
	Spells *spells;
	string attribute; 
	
	string weapon;
	int damage[2];

	int armor[3];

	//Methods
	
};

int main() {
	srand(time(0));
}