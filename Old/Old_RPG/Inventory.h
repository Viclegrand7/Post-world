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

#ifndef Vic_ITEM
#define Vic_ITEM
#include "Item.h"
#endif


class Inventory {
	//Attributes
private : 
	std :: vector<Weapon> att_exchange_weapon; //Maybe redo this to get pointers of weapons. Idem in character. Weapon drop made easier. Gotta free the weapons in destructor
	std :: vector<Item> att_items; // Make a single item pointer list. Every function should be virtual or something :)
	//No need for inventory then :))))))
	//Gotta find how to decide to use Item (If Weapon, change weapon. Else, use item on someone. How?)

	//Methods
public :
	Inventory();
	Inventory(int index);
	Inventory(std::string name, int index);
	Inventory(int index, int damage);
	Inventory(std::string name, int index, int damage);
	Inventory(int index, int damage, int second);
	Inventory(std::string name, int index, int damage, int second);
	~Inventory();

	unsigned int giveItemNumber() const;
	unsigned int giveWeaponNumber() const;

	std::string giveItemName(int number) const;
	std::string giveWeaponName(int number) const;

	Item giveItemFromInventory(int number) const;
	Weapon giveWeaponFromInventory(int number) const;
	void deleteWeapon(int number);
	void useItem(int number);
	bool giveIsHealing(int number) const;

	int giveType(int number) const;
	int giveDamage(int number) const;
	int giveSecondary(int number) const;

	unsigned int giveSize() const;
	void displayInventory() const;
	void displayWeapons() const;

	void addWeapon();
	void addWeapon(const Weapon &Copy);
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
};