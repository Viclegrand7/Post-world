#ifndef Vic_STRING
#define Vic_STRING
#include <string>
#endif

#ifndef Vic_IOSTREAM
#define Vic_IOSTREAM
#include <iostream>
#endif

#ifndef Vic_VECTOR
#define Vic_VECTOR
#include <vector>
#endif

#ifndef Vic_SPELLS
#define Vic_SPELLS
#include "Spells.h"
#endif

#ifndef Vic_INVENTORY
#define Vic_INVENTORY
#include "Inventory.h"
#endif

#ifndef Vic_ITEM
#define Vic_ITEM
#include "Item.h"
#endif


class Character {
	//Attributes
private : 
	std :: string att_name;
	
	int att_max_HP;
	int att_cur_HP;
	int att_max_MP;
	int att_cur_MP;

	int att_physic;
	int att_magic;
	int att_social;
	
	std :: vector <Spells> att_spells;
	std :: string att_attribute; 
	
	Weapon att_weapon;

	Inventory att_inventory; 

	int att_armor[3]; //Piercing ; Slicing ; Contondant
	bool att_isAlive;
	bool att_isConscious;

	bool att_isStunned;
	int att_damage_per_turn;
	int att_number_of_turn;

	void print(std :: ostream &flux) const;
	//Methods
public :
	Character();
	Character(std::string name);
	Character(std::string name, int max_HP, int max_MP);
	Character(std::string name, int phys, int mag, int soc);
	Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc);
	Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d);
	Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus);
	Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int damage_type);
	Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int armor_pierc, int armor_tranc, int armor_cont);
	Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, int armor_cont);
	Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, int armor_cont, int damage_type);
	~Character();

	int getHit(int damage, int type);
	void dodge() const;
	int attack(Character &target);
	void missTarget(Character &target) const;
	void getHealed(int value);
	void getMana(int value);
	void displayStatus() const;

	std :: string giveName() const;
	int giveHP() const;
	int giveMaxHP() const;
	int giveMP() const;
	int giveMaxMP() const;
	std :: vector<Spells> giveSpells() const;
	int giveNumber() const;
	std :: string giveAttribute() const;
	std :: string giveWeaponName() const;
	bool giveConsciousness() const;
	bool giveStunned() const;
	bool giveLiving() const;
	int *giveArmor() ;
	unsigned int giveInventorySize() const;
	unsigned int giveItemNumber() const;
	unsigned int giveWeaponNumber() const;

	bool giveIsHealing(int number) const; 
	bool useItem(int choice, Character &target);

	Item giveItemFromInventory(int number) const;
	Weapon giveWeaponFromInventory(int number) const;

	std::string giveItemName(int number) const;
	std::string giveWeaponName(int number) const;

	void displaySpellsWithNumber() const;
	void displayInventoryWithNumber() const;
	int giveDoTNumber() const;
	int giveDoTDamage() const;
	void reduceDoT();

	void changeArmor();
	void changeWeapon();
	void exchangeWeapon(int number);

	void addSpell();
	void addSpell(std::string name);
	void addSpell(std::string name, int cost);
	void addSpell(std::string name,int cost, int dot) ;
	void addSpell(int cost);
	void addSpell(int cost, int dot); 
	void addSpell(std::string name,int cost, int dot, bool stuns);
	void addSpell(int cost, int dot, bool stuns);

	void getStunned();
	int useSpell(int number, Character &target);
	void takeStatus(int damage, int number);
	int tryDodge(int success)const;

	void addWeapon();
	void addWeapon(std::string name);
	void addWeapon(int type);
	void addWeapon(std::string name, int type);
	void addWeapon(int type, int damage);
	void addWeapon(int type, int damage, int second);
	void addWeapon(std::string name, int type, int damage);
	void addWeapon(std::string name, int type, int damage, int second);

	void addItem(int index);
	void addItem(std::string name, int index);
	void addItem(int index, int damage);
	void addItem(std::string name, int index, int damage);
	void addItem(int index, int damage, int second);
	void addItem(std::string name, int index, int damage, int second);

	void upgradeItem(int number);
	void upgradeWeapon(int number);

	friend std :: ostream &operator<<(std :: ostream &flux, Character const &character);
};
