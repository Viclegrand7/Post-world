#include "Character.h"

void Character :: getHit(int damage, int success) {
	if (success == 200) {
		att_cur_HP -= damage;
		if (att_cur_HP < -5) {
			att_cur_HP = -5;
			att_isAlive = 0;
		}
		else if (att_cur_HP < 0) {
			att_isConscious = 0;
		}
	}
	else {
		tenta = rand() % 100;
		if (success == 100) {
			if (tenta > 5) {
				att_cur_HP -= damage;
				if (att_cur_HP < -5) {
					att_cur_HP = -5;
					att_isAlive = 0;
				}
				else if (att_cur_HP < 0) {
					att_isConscious = 0;
				}
			}
			else dodge();
		}
		if (rand() % 100 > att_physic - success) {
			att_cur_HP -= damage;
			if (att_cur_HP < -5) {
				att_cur_HP = -5;
				att_isAlive = 0;
			}
			else if (att_cur_HP < 0) {
				att_isConscious = 0;
			}
		}
		else dodge();
	}
} 

void Character :: dodge()  const{
	std :: cout << att_name << " just dodged brilliantly!" << endl;
}

void Character :: attack(Character &target) {
	int tenta = rand() % 100;
	if (tenta < 5) {
		target.getHit(att_damage[0] + att_damage[1], 100);
		std :: cout << "That's a critical strike!" << endl;
	}
	else if (tenta > 94) {
		getHit(att_damage[0] + att_damage[1], 100)
		std :: cout << att_name << " failed miserably and hit himself for " << att_damage[0]+att_damage[1] << "HP" << endl;
	}
	else if (att_physic - tenta >= 0) {
		target.getHit(rand() % att_damage[0] + att_damage[1] + 1, att_physic - tenta);
	}
	else 
		missTarget(&target);
}

void Character :: missTarget(Character &target) const {
	std :: cout << att_name << " just missed his hit on " << target.giveName() << endl;
}

std :: string Character :: giveName() const {
	return att_name;
}

void Character :: getHealed(int value) {
	att_cur_HP += value;
	if (att_cur_HP > att_max_HP)
		att_cur_HP = att_max_HP;
}

void Character :: displayStatus() const {
	if (!att_isAlive) {
		std :: cout << "I, " << att_name << ", have been killed" << endl;
	}
	else if (!att_isConscious) {
		std :: cout << "The mighty " << att_name << "will be back after a short break" << endl;
	}
	else {	
		std :: cout << "I, " << att_name << ", still have " << att_cur_HP << "HP left out of " << att_max_HP << " and " << att_cur_MP << "MP left out of " << att_max_MP << endl;
		if (att_damage[1]) {
			std :: cout << "I hit for d" << att_damage[0] << "+" << att_damage[1] << "with my " << att_weapon << endl ;
		}
		else std :: cout << "I hit for d" << att_damage[0] << endl;
	}
}

void addSpell() {
	if (att_spells) {
		att_spells[att_number] = &Spells();
		att_number ++;
	}
	else {
		Spells * att_spells = new(Spells);
		att_spells = &Spells();
		att_number ++;
	}
}

void addSpell(std::string name) {
	if (att_spells) {
		att_spells[att_number] = &Spells(name);
		att_number ++;
	}
	else {
		Spells * att_spells = new(Spells);
		att_spells = &Spells(name);
		att_number ++;
	}
}

void addSpell(std::string name, int cost) {
	if (att_spells) {
		att_spells[att_number] = &Spells(name, cost);
		att_number ++;
	}
	else {
		Spells * att_spells = new(Spells);
		att_spells = &Spells(name, cost);
		att_number ++;
	}
}

void addSpell(std::string name,int cost, int dot) {
	if (att_spells) {
		att_spells[att_number] = &Spells(name, cost, dot);
		att_number ++;
	}
	else {
		Spells * att_spells = new(Spells);
		att_spells = &Spells(name, cost, dot);
		att_number ++;
	}
}

void addSpell(int cost) {
	if (att_spells) {
		att_spells[att_number] = &Spells(cost);
		att_number ++;
	}
	else {
		Spells * att_spells = new(Spells);
		att_spells = &Spells(cost);
		att_number ++;
	}
}

void addSpell(int cost, int dot) {
	if (att_spells) {
		att_spells[att_number] = &Spells(cost, dot);
		att_number ++;
	}
	else {
		Spells * att_spells = new(Spells);
		att_spells = &Spells(cost, dot);
		att_number ++;
	}
}

void useSpell(int number, Character &target) {
	int tenta = rand() % 100;
	damage = att_spells[number].giveDamage();
	if (tenta < 5) {
		target.getHit(damage, 100);
		std :: cout << "That's a critical strike!" << endl; // FINIR POUR LES STATUS
	}
	else if (tenta > 94) {
		getHit(damage, 100)
		std :: cout << att_name << " failed miserably and hit himself for " << damage << "HP" << endl;
	}
	else if (att_magic - tenta >= 0) {
		target.getHit(rand() % damage + 1, att_magic - tenta);
	}
	else 
		missTarget(&target);
}


Character :: Character() : att_name("Generic character"), att_max_HP(20), att_cur_HP(20), att_max_MP(10), att_cur_MP(10), att_physic(50), att_magic(50), att_social(50), att_spells(0), att_number(0), att_attribute("No attribute"), att_weapon("small sword"),att_damage(4,0), att_armor(0,2,1),	att_isAlive(1), att_isConscious(1) {}
Character :: Character(std::string name) : att_name(name), att_max_HP(20), att_cur_HP(20), att_max_MP(10), att_cur_MP(10), att_physic(50), att_magic(50), att_social(50), att_spells(0), att_number(0), att_attribute("No attribute"), att_weapon("small sword"),att_damage(4,0), att_armor(0,2,1),	att_isAlive(1), att_isConscious(1) {}
Character :: Character(std::string name, int max_HP, int max_MP) : att_name(name), att_max_HP(max_HP), att_cur_HP(max_HP), att_max_MP(max_MP), att_cur_MP(max_MP), att_physic(50), att_magic(50), att_social(50), att_spells(0), att_number(0), att_attribute("No attribute"), att_weapon("small sword"),att_damage(4,0), att_armor(0,2,1),	att_isAlive(1), att_isConscious(1) {}
Character :: Character(std::string name, int phys, int mag, int soc) : att_name(name), att_max_HP(20), att_cur_HP(20), att_max_MP(10), att_cur_MP(10), att_physic(phys), att_magic(mag), att_social(soc), att_spells(0), att_number(0), att_attribute("No attribute"), att_weapon("small sword"),att_damage(4,0), att_armor(0,2,1),	att_isAlive(1), att_isConscious(1) {}
Character :: Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc) : att_name(name), att_max_HP(max_HP), att_cur_HP(max_HP), att_max_MP(max_MP), att_cur_MP(max_MP), att_physic(phys), att_magic(mag), att_social(soc), att_spells(0), att_number(0), att_attribute("No attribute"), att_weapon("small sword"),att_damage(4,0), att_armor(0,2,1),	att_isAlive(1), att_isConscious(1) {}
Character :: Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d) : att_name(name), att_max_HP(max_HP), att_cur_HP(max_HP), att_max_MP(max_MP), att_cur_MP(max_MP), att_physic(phys), att_magic(mag), att_social(soc), att_spells(0), att_number(0), att_attribute("No attribute"), att_weapon("small sword"),att_damage(damage_d,0), att_armor(0,2,1),	att_isAlive(1), att_isConscious(1) {}
Character :: Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus) : att_name(name), att_max_HP(max_HP), att_cur_HP(max_HP), att_max_MP(max_MP), att_cur_MP(max_MP), att_physic(phys), att_magic(mag), att_social(soc), att_spells(0), att_number(0), att_attribute("No attribute"), att_weapon("small sword"),att_damage(damage_d,damage_plus), att_armor(0,2,1),	att_isAlive(1), att_isConscious(1) {}
Character :: Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int armor_pierc, int armor_tranc, int armor_cont) : att_name(name), att_max_HP(max_HP), att_cur_HP(max_HP), att_max_MP(max_MP), att_cur_MP(max_MP), att_physic(phys), att_magic(mag), att_social(soc), att_spells(0),, att_number(0) att_attribute("No attribute"), att_weapon("small sword"),att_damage(damage_d,0), att_armor(armor_pierc,armor_tranc,armor_cont),	att_isAlive(1), att_isConscious(1) {}
Character :: Character(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, armor_cont) : att_name(name), att_max_HP(max_HP), att_cur_HP(max_HP), att_max_MP(max_MP), att_cur_MP(max_MP), att_physic(phys), att_magic(mag), att_social(soc), att_spells(0), att_number(0), att_attribute("No attribute"), att_weapon("small sword"),att_damage(damage_d,damage_plus), att_armor(armor_pierc,armor_tranc,armor_cont),	att_isAlive(1), att_isConscious(1) {}
Character :: ~Character() {
	if (Spells)
		delete(Spells);
}