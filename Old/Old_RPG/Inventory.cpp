#include "Inventory.h"

Inventory :: Inventory() : att_exchange_weapon(), att_items() {}
Inventory :: Inventory(int index) {
	if (index == 1) {
		Weapon new_weapon;
		att_exchange_weapon.push_back(new_weapon);
	}
	else {
		Item new_item(index);
		att_items.push_back(new_item);
	}
}
Inventory :: Inventory(std::string name, int index) {
	if (index == 1) {
		Weapon new_weapon(name);
		att_exchange_weapon.push_back(new_weapon);
	}
	else {
		Item new_item(name, index);
		att_items.push_back(new_item);
	}
}
Inventory :: Inventory(int index, int damage) {
	if (index == 1) {
		Weapon new_weapon(2, damage);
		att_exchange_weapon.push_back(new_weapon);
	}
	else {
		Item new_item(index, damage);
		att_items.push_back(new_item);
	}
}
Inventory :: Inventory(std::string name, int index, int damage) {
	if (index == 1) {
		Weapon new_weapon(name, 2, damage);
		att_exchange_weapon.push_back(new_weapon);
	}
	else {
		Item new_item(name, index, damage);
		att_items.push_back(new_item);
	}
}
Inventory :: Inventory(int index, int damage, int second) {
	if (index == 1) {
		Weapon new_weapon(2, damage, second);
		att_exchange_weapon.push_back(new_weapon);
	}
	else {
		Item new_item(index, damage, second);
		att_items.push_back(new_item);
	}
}
Inventory :: Inventory(std::string name, int index, int damage, int second) {
	if (index == 1) {
		Weapon new_weapon(name, 2, damage, second);
		att_exchange_weapon.push_back(new_weapon);
	}
	else {
		Item new_item(name, index, damage, second);
		att_items.push_back(new_item);
	}
}
Inventory :: ~Inventory() {
	att_exchange_weapon.clear();
	att_items.clear();
}

unsigned int Inventory :: giveItemNumber() const {
	return att_items.size();
}

unsigned int Inventory :: giveWeaponNumber() const {
	return att_exchange_weapon.size();
}

std::string Inventory :: giveItemName(int number) const {
	return att_items[number].giveName();
}

std::string Inventory :: giveWeaponName(int number) const {
	return att_exchange_weapon[number].giveName();
}

Item Inventory :: giveItemFromInventory(int number) const {
	return att_items[number];
}

Weapon Inventory :: giveWeaponFromInventory(int number) const {
	return att_exchange_weapon[number];
}

void Inventory :: deleteWeapon(int number) {
	att_exchange_weapon.erase(att_exchange_weapon.begin() + number);
}

bool Inventory :: giveIsHealing(int number) const  {
	return att_items[number].giveIsHealing();
}

void Inventory :: useItem(int number) {
	if (att_items[number].useItem())
		att_items.erase(att_items.begin() + number);
}

unsigned int Inventory :: giveSize() const {
	return att_exchange_weapon.size() + att_items.size();
}

void Inventory :: displayInventory() const {
	std :: cout << "Back(0)" << std :: endl;
	unsigned int i = 0;
	while (i < att_exchange_weapon.size()) {
		std :: cout << "(" << i + 1 << ") " << att_exchange_weapon[i].giveName() << " : d" << att_exchange_weapon[i].giveDamage(); 
		if (att_exchange_weapon[i].giveSecondary())
			std :: cout << "+" << att_exchange_weapon[i].giveSecondary();
		if (att_exchange_weapon[i].giveDamageType() == 1)
			std :: cout << ". Type : piercing" << std :: endl;
		if (att_exchange_weapon[i].giveDamageType() == 2)
			std :: cout << ". Type : slicing" << std :: endl;
		if (att_exchange_weapon[i].giveDamageType() == 3)
			std :: cout << ". Type : contondant" << std :: endl;
		i++;
	}
	std :: cout << std :: endl;
	unsigned int temp = att_exchange_weapon.size();
	unsigned int size = att_items.size() + temp;
	while (i < size) {
		std :: cout << "(" << i + 1 << ") " << att_items[i - temp].giveName() << ". Value : " << att_items[i - temp].giveDamage() << ". Quantity : " << att_items[i - temp].giveSecondary() << std :: endl;
		i++;
	}
}
void Inventory :: displayWeapons() const {
	std :: cout << "Back(0)" << std :: endl;
	for (unsigned int i = 0; i < att_exchange_weapon.size() ; i++) {
		std :: cout << att_exchange_weapon[i].giveName() << " : d" << att_exchange_weapon[i].giveDamage(); 
		if (att_exchange_weapon[i].giveSecondary())
			std :: cout << "+" << att_exchange_weapon[i].giveSecondary();
		if (att_exchange_weapon[i].giveDamageType() == 1)
			std :: cout << ". Type : piercing" << std :: endl;
		if (att_exchange_weapon[i].giveDamageType() == 2)
			std :: cout << ". Type : slicing" << std :: endl;
		if (att_exchange_weapon[i].giveDamageType() == 3)
			std :: cout << ". Type : contondant" << std :: endl;
	}
}

void Inventory :: addWeapon() {
	Weapon new_weapon;
	att_exchange_weapon.push_back(new_weapon);
}

void Inventory :: addWeapon(const Weapon &Copy) {
	Weapon new_weapon(Copy);
	att_exchange_weapon.push_back(new_weapon);
}


void Inventory :: addWeapon(std::string name) {
	Weapon new_weapon(name);
	att_exchange_weapon.push_back(new_weapon);
}

void Inventory :: addWeapon(int type) {
	Weapon new_weapon(type);
	att_exchange_weapon.push_back(new_weapon);
}

void Inventory :: addWeapon(std::string name, int type) {
	Weapon new_weapon(name, type);
	att_exchange_weapon.push_back(new_weapon);
}

void Inventory :: addWeapon(int type, int damage) {
	Weapon new_weapon(type, damage);
	att_exchange_weapon.push_back(new_weapon);
}

void Inventory :: addWeapon(int type, int damage, int second) {
	Weapon new_weapon(type, damage, second);
	att_exchange_weapon.push_back(new_weapon);
}

void Inventory :: addWeapon(std::string name, int type, int damage) {
	Weapon new_weapon(name);
	att_exchange_weapon.push_back(new_weapon);
}

void Inventory :: addWeapon(std::string name, int type, int damage, int second) {
	Weapon new_weapon(name, type, damage, second);
	att_exchange_weapon.push_back(new_weapon);
}


void Inventory :: addItem(int index) {
	if (index == 1) 
		return addWeapon();
	Item new_item(index);
	for (unsigned int i = 0; i < att_items.size() ; i++) {
		if (new_item == att_items[i]) {
			att_items[i] += new_item;
			return;
		}
	}
	att_items.push_back(new_item);
}

void Inventory :: addItem(std::string name, int index) {
	if (index == 1) 
		return addWeapon(name);
	Item new_item(name, index);
	for (unsigned int i = 0; i < att_items.size() ; i++) {
		if (new_item == att_items[i]) {
			att_items[i] += new_item;
			return;
		}
	}
	att_items.push_back(new_item);
}

void Inventory :: addItem(int index, int damage) {
	if (index == 1) 
		return addWeapon(damage);
	Item new_item(index, damage);
	for (unsigned int i = 0; i < att_items.size() ; i++) {
		if (new_item == att_items[i]) {
			att_items[i] += new_item;
			return;
		}
	}
	att_items.push_back(new_item);
}

void Inventory :: addItem(std::string name, int index, int damage) {
	if (index == 1) 
		return addWeapon(name, damage);
	Item new_item(name, index, damage);
	for (unsigned int i = 0; i < att_items.size() ; i++) {
		if (new_item == att_items[i]) {
			att_items[i] += new_item;
			return;
		}
	}
	att_items.push_back(new_item);
}

void Inventory :: addItem(int index, int damage, int second) {
	if (index == 1) 
		return addWeapon(damage, second);
	Item new_item(index, damage, second);
	for (unsigned int i = 0; i < att_items.size() ; i++) {
		if (new_item == att_items[i]) {
			att_items[i] += new_item;
			return;
		}
	}
	att_items.push_back(new_item);
}

void Inventory :: addItem(std::string name, int index, int damage, int second) {
	if (index == 1) 
		return addWeapon(name, damage, second);
	Item new_item(name, index, damage, second);
	for (unsigned int i = 0; i < att_items.size() ; i++) {
		if (new_item == att_items[i]) {
			att_items[i] += new_item;
			return;
		}
	}
	att_items.push_back(new_item);
}

int Inventory :: giveType(int number) const {
	return att_items[number].giveType();
}

int Inventory :: giveDamage(int number) const {
	return att_items[number].giveDamage();
}

int Inventory :: giveSecondary(int number) const {
	return att_items[number].giveSecondary();
}

void Inventory :: upgradeItem(int number) {
	++att_items[number];
}

void Inventory :: upgradeWeapon(int number) {
	++att_exchange_weapon[number];
}