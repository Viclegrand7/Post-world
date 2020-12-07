#ifndef Vic_STRING
#define Vic_STRING
#include <string>
#endif

#ifndef Vic_STATUS
#define Vic_STATUS

class Character {
	//Attributes
private : 
	int att_damage_per_turn;
	int att_turn;

	//Methods
public :
	Character();
	Character(std::string name);
	Character(std::string name, int max_HP, int max_MP);
	Character(std::string name, int phys, int mag, int soc);
	Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc);
	Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d);
	Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus);
	Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int armor_pierc, int armor_tranc, int armor_cont);
	Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus);
	Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, int armor_cont);
	~Character();

	Character :: getHit(int damage, int success);
	Character :: dodge() const;
	Character :: attack(Character &target);
	Character :: missTarget(Character &target) const;
	std :: string Character :: giveName() const;
	Character :: getHealed(int value);
	Character :: displayStatus() const;

	Character :: useSpell(int number, Character &target);

	Character :: addSpell();
	Character :: addSpell(std::string name);
	Character :: addSpell(std::string name, int cost);
	Character :: addSpell(std::string name,int cost, int dot) ;
	Character :: addSpell(int cost);
	Character :: addSpell(int cost, int dot);
};
#endif