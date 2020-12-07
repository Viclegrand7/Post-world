#ifndef Vic_STRING
#define Vic_STRING
#include <string>
#endif

class Spells {
	//Attributes
private : 
	std :: string att_name;
	
	int att_damage;
	int att_cost;
	int att_dot;

	bool att_does_stun;
	//Methods
public :
	Spells();
	Spells(std::string name);
	Spells(std::string name, int cost);
	Spells(std::string name,int cost, int dot);
	Spells(int cost);
	Spells(int cost, int dot);
	Spells(std::string name,int cost, int dot, bool stuns);
	Spells(int cost, int dot, bool stuns);
	~Spells();

	std :: string giveName() const;
	int giveDamage() const;
	int giveCost() const;
	int giveNumber() const;
	bool doesStun() const;
};