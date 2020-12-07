#include "Character.h"

int Character :: getHit(int damage, int type) {//returns 1 if target dies/get unconscious, 0 otherwhise
	int armor = 0;
	if (type)
		armor = att_armor[type - 1];
	if (damage - armor <= 0)
		return 0;
	att_cur_HP -= damage + armor;
	if (att_cur_HP < -5) {
		att_cur_HP = -5;
		att_isAlive = 0;
		return 1;
	}
	else if (att_cur_HP <= 0) {
		if (att_isConscious)
			att_damage_per_turn/=2;
		att_isConscious = 0;
		return 1;
	}
	return 0;
} 

void Character :: dodge()  const{
	std :: cout << att_name << " just dodged brilliantly!" << std :: endl;
}

void Character :: missTarget(Character &target) const {
	std :: cout << att_name << " just missed his hit on " << target.giveName() << std :: endl;
}

int Character :: attack(Character &target) { //returns 1 if target died/got unconscious, -1 if the attacker did
	int value = 0;
	int tenta = rand() % 100;
	if (tenta < 5 && rand() % 100 > 4) {
		value = target.getHit(att_weapon.giveDamage() + att_weapon.giveSecondary(),att_weapon.giveDamageType());
		std :: cout << "That's a critical strike!" << std :: endl;
	}
	else if (tenta > 94) {
		if (getHit(att_weapon.giveDamage() + att_weapon.giveSecondary(), 0))
			value = -1;
		std :: cout << att_name << " failed miserably and hit himself" << std :: endl;
	}
	else if (att_physic - tenta > 0) {
		if (!target.tryDodge(att_physic - tenta)) // tenta = Die roll - 1. If att_physic - tenta == 1, no malus on dodge 
		value = target.getHit(rand() % att_weapon.giveDamage() + att_weapon.giveSecondary() + 1, att_weapon.giveDamageType());
	}
	else 
		missTarget(target);
	return value;
}

std :: string Character :: giveName() const {
	return att_name;
}

void Character :: getHealed(int value) {
	att_cur_HP += value;
	if (att_cur_HP > att_max_HP)
		att_cur_HP = att_max_HP;
}

void Character :: getMana(int value) {
	att_cur_MP += value;
	if (att_cur_MP > att_max_MP)
		att_cur_MP = att_max_MP;
}

void Character :: displayStatus() const {
	if (!att_isAlive) {
		std :: cout << "I, " << att_name << ", have been killed" << std :: endl;
	}
	else if (!att_isConscious) {
		std :: cout << "The mighty " << att_name << "will be back after a short break" << std :: endl;
	}
	else {	
		std :: cout << "I, " << att_name << ", still have " << att_cur_HP << "HP left out of " << att_max_HP << " and " << att_cur_MP << "MP left out of " << att_max_MP << std :: endl;
		if (att_weapon.giveSecondary()) {
			std :: cout << "I hit for d" << att_weapon.giveDamage() << "+" << att_weapon.giveSecondary() << " with my " << att_weapon.giveName() << std :: endl ;
		}
		else std :: cout << "I hit for d" << att_weapon.giveDamage() << " with my " << att_weapon.giveName() << std :: endl;
	}
}

void Character :: addSpell() {
	Spells new_spell;
	att_spells.push_back(new_spell);
}

void Character :: addSpell(std::string name) {
	Spells new_spell(name);
	att_spells.push_back(new_spell);
}

void Character :: addSpell(std::string name, int cost) {
	Spells new_spell(name, cost);
	att_spells.push_back(new_spell);
}

void Character :: addSpell(std::string name,int cost, int dot) {
	Spells new_spell(name, cost, dot);
	att_spells.push_back(new_spell);
}

void Character :: addSpell(int cost) {
	Spells new_spell(cost);
	att_spells.push_back(new_spell);
}

void Character :: addSpell(int cost, int dot) {
	Spells new_spell(cost, dot);
	att_spells.push_back(new_spell);
}

void Character :: addSpell(std::string name,int cost, int dot, bool stuns) {
	Spells new_spell(name, cost, dot, stuns);
	att_spells.push_back(new_spell);
}

void Character :: addSpell(int cost, int dot, bool stuns) {
	Spells new_spell(cost, dot, stuns);
	att_spells.push_back(new_spell);
}


void Character :: getStunned() {
	att_isStunned = 1;
}

int Character :: useSpell(int number, Character &target) { //Returns 1 if target dies/gets unconscious, -1 if attacker does, 2 if both do
	int value = 0;
	int tenta = rand() % 100;
	int damage = att_spells[number].giveDamage();
	if (tenta < 5) {
		if (!target.tryDodge(100)) {
			value = target.getHit(damage, 0);
			std :: cout << "That's a critical strike!" << std :: endl;
			if (att_spells[number].doesStun())
				target.getStunned();
			if (att_spells[number].giveNumber()) {
				takeStatus(att_spells[number].giveDamage(),att_spells[number].giveNumber());
			}
		}
		else {
			std :: cout << "That critical strike was dodged!" << std :: endl;
			return 0;
		}
	}
	else if (tenta > 94) {
		if (getHit(damage, 0))
			value = -1;
		std :: cout << att_name << " failed miserably and hit himself" << std :: endl;
		if (att_spells[number].giveNumber()) {
			takeStatus(att_spells[number].giveDamage(),att_spells[number].giveNumber());
		}
		if (att_spells[number].doesStun())
			target.getStunned();
	}
	else if (att_magic - tenta > 0) {
		if (!target.tryDodge(att_magic - tenta)) {
			value = target.getHit(rand() % damage + 1, 0);
			if (att_spells[number].giveNumber()) {
				takeStatus(att_spells[number].giveDamage(),att_spells[number].giveNumber());
			}
			if (att_spells[number].doesStun())
				target.getStunned();
		}
	}
	else 
		missTarget(target);
	int cost = att_spells[number].giveCost();
	if (att_cur_MP - cost > 0) {
		att_cur_MP -= cost;
	}
	else {
		if (getHit(cost - att_cur_MP, 0)) {
			if (value) {
				value = 2;
			}
			else 
				value = -1;
		}
		att_cur_MP = 0;
		std :: cout << "Using spells without mana seems very dangerous..." << std :: endl;
	}
	return value;
}

void Character :: takeStatus(int damage, int number) {
	if (!att_number_of_turn) 
		att_damage_per_turn = damage;
	else 
		att_damage_per_turn += damage;
	att_number_of_turn += number;
}

int Character :: tryDodge(int success) const{
		int tenta = rand() % 100;
		if (success == 100) {
			if (tenta > 5) 
				return 0; // Did not dodge
			else dodge();
		}
		return (rand() % 100 <= att_physic - success); // if my rand is lower or equel to goal, I dodge (rand has a -1, and success has a +1 in it)
}

int Character :: giveHP() const {
	return att_cur_HP;
}

int Character :: giveMaxHP() const {
	return att_max_HP;
}

int Character :: giveMP() const {
	return att_cur_MP;
}

int Character :: giveMaxMP() const {
	return att_max_MP;
}

std :: vector<Spells> Character :: giveSpells() const {
	return att_spells;
}

std :: string Character :: giveAttribute() const {
	return att_attribute;
}

bool Character :: giveConsciousness() const {
	return att_isConscious;
}

bool Character :: giveStunned() const {
	return att_isStunned;
}

bool Character :: giveLiving() const {
	return att_isAlive;
}

int * Character :: giveArmor() {
	return att_armor;
}

std :: string Character :: giveWeaponName() const {
	return att_weapon.giveName();
}

int Character :: giveNumber() const {
	return att_spells.size();
}

void Character :: displayInventoryWithNumber() const {
	att_inventory.displayInventory();
}

unsigned int Character :: giveInventorySize() const {
	return att_inventory.giveSize();
}

unsigned int Character :: giveItemNumber() const {
	return att_inventory.giveItemNumber();
}

unsigned int Character :: giveWeaponNumber() const {
	return att_inventory.giveWeaponNumber();
}

std::string Character :: giveItemName(int number) const {
	return att_inventory.giveItemName(number);
}

std::string Character :: giveWeaponName(int number) const {
	return att_inventory.giveWeaponName(number);
}

Item Character :: giveItemFromInventory(int number) const {
	return att_inventory.giveItemFromInventory(number);
}

Weapon Character :: giveWeaponFromInventory(int number) const {
	return att_inventory.giveWeaponFromInventory(number);
}

bool Character :: useItem(int choice, Character &target) {
	int type = att_inventory.giveType(choice);
	int damage = att_inventory.giveDamage(choice);
	att_inventory.useItem(choice);

	if (type == 2) {
		target.getHealed(damage);
		return 0;
	}
	else if (type == 3) {
		target.getMana(damage);
		return 0;
	}
	else if (type == 4) {
		return target.getHit(damage, 1);
	}
	else {
		target.getStunned();
		return target.getHit(damage, 3);
	}
}


bool Character :: giveIsHealing(int number) const {
	return att_inventory.giveIsHealing(number);
}

void Character :: exchangeWeapon(int number) {
	att_inventory.addWeapon(att_weapon);
	att_weapon = att_inventory.giveWeaponFromInventory(number);
	att_inventory.deleteWeapon(number);
}

void Character :: displaySpellsWithNumber() const {
	std :: cout << "Back (0)" << std :: endl;
	for (unsigned int i = 0; i < att_spells.size(); i++) {
		std :: cout << att_spells[i].giveName() << ": " << att_spells[i].giveCost() << "MP (" << i << ")" << std :: endl;
	}
}

int Character :: giveDoTNumber() const {
	return att_number_of_turn;
}

int Character :: giveDoTDamage() const {
	return att_damage_per_turn;
}

void Character :: reduceDoT() {
	att_number_of_turn --;
}


void Character :: addWeapon() {
	att_inventory.addWeapon();
}
void Character :: addWeapon(std::string name) {
	att_inventory.addWeapon(name);
}
void Character :: addWeapon(int type) {
	att_inventory.addWeapon(type);
}
void Character :: addWeapon(std::string name, int type) {
	att_inventory.addWeapon(name, type);
}
void Character :: addWeapon(int type, int damage) {
	att_inventory.addWeapon(type, damage);
}
void Character :: addWeapon(int type, int damage, int second) {
	att_inventory.addWeapon(type, damage, second);
}
void Character :: addWeapon(std::string name, int type, int damage) {
	att_inventory.addWeapon(name, type, damage);
}
void Character :: addWeapon(std::string name, int type, int damage, int second) {
	att_inventory.addWeapon(name, type, damage, second);
}

void Character :: addItem(int index) {
	att_inventory.addItem(index);
}
void Character :: addItem(std::string name, int index) {
	att_inventory.addItem(name, index);
}
void Character :: addItem(int index, int damage) {
	att_inventory.addItem(index, damage);
}
void Character :: addItem(std::string name, int index, int damage) {
	att_inventory.addItem(name, index, damage);
}
void Character :: addItem(int index, int damage, int second) {
	att_inventory.addItem(index, damage, second);
}
void Character :: addItem(std::string name, int index, int damage, int second) {
	att_inventory.addItem(name, index, damage, second);
}


Character :: Character() : att_name("Generic character"), att_max_HP(20), att_cur_HP(20), att_max_MP(10), att_cur_MP(10), att_physic(50), att_magic(50), att_social(50), att_spells({}), att_attribute("No attribute"), att_weapon(), att_armor{0,2,1}, att_isAlive(1), att_isConscious(1), att_isStunned(0), att_damage_per_turn(0), att_number_of_turn(0) {}
Character :: Character(std::string name) : att_name(name), att_max_HP(20), att_cur_HP(20), att_max_MP(10), att_cur_MP(10), att_physic(50), att_magic(50), att_social(50), att_spells({}), att_attribute("No attribute"), att_weapon(), att_armor{0,2,1}, att_isAlive(1), att_isConscious(1), att_isStunned(0), att_damage_per_turn(0), att_number_of_turn(0) {}
Character :: Character(std::string name, int max_HP, int max_MP) : att_name(name), att_max_HP(max_HP), att_cur_HP(max_HP), att_max_MP(max_MP), att_cur_MP(max_MP), att_physic(50), att_magic(50), att_social(50), att_spells({}), att_attribute("No attribute"), att_weapon(), att_armor{0,2,1}, att_isAlive(1), att_isConscious(1), att_isStunned(0), att_damage_per_turn(0), att_number_of_turn(0) {}
Character :: Character(std::string name, int phys, int mag, int soc) : att_name(name), att_max_HP(20), att_cur_HP(20), att_max_MP(10), att_cur_MP(10), att_physic(phys), att_magic(mag), att_social(soc), att_spells({}), att_attribute("No attribute"), att_weapon(), att_armor{0,2,1}, att_isAlive(1), att_isConscious(1), att_isStunned(0), att_damage_per_turn(0), att_number_of_turn(0) {}
Character :: Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc) : att_name(name), att_max_HP(max_HP), att_cur_HP(max_HP), att_max_MP(max_MP), att_cur_MP(max_MP), att_physic(phys), att_magic(mag), att_social(soc), att_spells({}), att_attribute("No attribute"), att_weapon(), att_armor{0,2,1},	att_isAlive(1), att_isConscious(1), att_isStunned(0), att_damage_per_turn(0), att_number_of_turn(0) {}
Character :: Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d) : att_name(name), att_max_HP(max_HP), att_cur_HP(max_HP), att_max_MP(max_MP), att_cur_MP(max_MP), att_physic(phys), att_magic(mag), att_social(soc), att_spells({}), att_attribute("No attribute"), att_weapon(2, damage_d), att_armor{0,2,1}, att_isAlive(1), att_isConscious(1), att_isStunned(0), att_damage_per_turn(0), att_number_of_turn(0) {}
Character :: Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus) : att_name(name), att_max_HP(max_HP), att_cur_HP(max_HP), att_max_MP(max_MP), att_cur_MP(max_MP), att_physic(phys), att_magic(mag), att_social(soc), att_spells({}), att_attribute("No attribute"), att_weapon(2, damage_d,damage_plus), att_armor{0,2,1}, att_isAlive(1), att_isConscious(1), att_isStunned(0), att_damage_per_turn(0), att_number_of_turn(0) {}
Character :: Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int damage_type) : att_name(name), att_max_HP(max_HP), att_cur_HP(max_HP), att_max_MP(max_MP), att_cur_MP(max_MP), att_physic(phys), att_magic(mag), att_social(soc), att_spells({}), att_attribute("No attribute"), att_weapon(damage_type, damage_d, damage_plus), att_armor{0,2,1}, att_isAlive(1), att_isConscious(1), att_isStunned(0), att_damage_per_turn(0), att_number_of_turn(0) {}
Character :: Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int armor_pierc, int armor_tranc, int armor_cont) : att_name(name), att_max_HP(max_HP), att_cur_HP(max_HP), att_max_MP(max_MP), att_cur_MP(max_MP), att_physic(phys), att_magic(mag), att_social(soc), att_spells({}), att_attribute("No attribute"), att_weapon(2, damage_d), att_armor{armor_pierc,armor_tranc,armor_cont},	att_isAlive(1), att_isConscious(1), att_isStunned(0), att_damage_per_turn(0), att_number_of_turn(0) {}
Character :: Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, int armor_cont) : att_name(name), att_max_HP(max_HP), att_cur_HP(max_HP), att_max_MP(max_MP), att_cur_MP(max_MP), att_physic(phys), att_magic(mag), att_social(soc), att_spells({}), att_attribute("No attribute"), att_weapon(2, damage_d, damage_plus), att_armor{armor_pierc,armor_tranc,armor_cont}, att_isAlive(1), att_isConscious(1), att_isStunned(0), att_damage_per_turn(0), att_number_of_turn(0) {}
Character :: Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, int armor_cont, int damage_type) : att_name(name), att_max_HP(max_HP), att_cur_HP(max_HP), att_max_MP(max_MP), att_cur_MP(max_MP), att_physic(phys), att_magic(mag), att_social(soc), att_spells({}), att_attribute("No attribute"), att_weapon(damage_type, damage_d, damage_plus), att_armor{armor_pierc, armor_tranc, armor_cont}, att_isAlive(1), att_isConscious(1), att_isStunned(0), att_damage_per_turn(0), att_number_of_turn(0) {}
Character :: ~Character() {
	att_spells.clear();
}

void Character :: upgradeItem(int number) {
	att_inventory.upgradeItem(number);
}

void Character :: upgradeWeapon(int number) {
	if (!number) {
		++att_weapon;
		return;
	}
	att_inventory.upgradeWeapon(number - 1);
}

void Character :: print(std :: ostream &flux) const {
	flux << att_name << ". HP : " << att_cur_HP << "/" << att_max_HP << ". MP : " << att_cur_MP << "/" << att_max_MP << std :: endl;
}

std :: ostream &operator<<(std :: ostream &flux, Character const &character) {
	character.print(flux);
	return flux;
}