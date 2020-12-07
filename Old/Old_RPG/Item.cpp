#include "Item.h"

#ifndef Vic_STRING
#define Vic_STRING
#include <string>
#endif

Item :: Item() : att_index(0), att_name("Generic item"), att_damage_value(0), att_secondary_value(0) {}

Item :: Item(int index) : att_index(index) { // Index has to not be 1
	if (index == 2) {
		att_damage_value = 8;
		att_name = "Life Potion";
		att_secondary_value = 1;
	}
	else if (index == 3) {
		att_damage_value = 6;
		att_name = "Mana Potion";
		att_secondary_value = 1;
	}
	else if (index == 4) {
		att_damage_value = 4;
		att_name = "Throwing knife";
		att_secondary_value = 5;
	}
	else if (index == 5) {
		att_damage_value = 0;
		att_name = "Debilitating ofuda";
		att_secondary_value = 1;
	}
	else  {
		att_damage_value = 4;
		att_name = "Generic item";
		att_secondary_value = 1;
	}
}

Item :: Item(std::string name, int index) : att_index(index), att_name(name) {
	if (index == 2) {
		att_damage_value = 8;
		att_secondary_value = 1;
	}
	else if (index == 3) {
		att_damage_value = 6;
		att_secondary_value = 1;
	}
	else if (index == 4) {
		att_damage_value = 4;
		att_secondary_value = 5;
	}
	else if (index == 5) {
		att_damage_value = 0;
		att_secondary_value = 1;
	}
	else  {
		att_damage_value = 4;
		att_secondary_value = 1;
	}

}

Item :: Item(int index, int damage) : att_index(index), att_damage_value(damage) {
	if (index == 2) {
		att_name = "Life Potion";
		att_secondary_value = 1;
	}
	else if (index == 3) {
		att_name = "Mana Potion";
		att_secondary_value = 1;
	}
	else if (index == 4) {
		att_name = "Throwing knife";
		att_secondary_value = 5;
	}
	else if (index == 5) {
		att_name = "Debilitating ofuda";
		att_secondary_value = 1;
	}
	else  {
		att_name = "Generic item";
		att_secondary_value = 1;
	}

}

Item :: Item(std::string name, int index, int damage) : att_index(index), att_name(name), att_damage_value(damage) {
	if (index == 2) {
		att_secondary_value = 1;
	}
	else if (index == 3) {
		att_secondary_value = 1;
	}
	else if (index == 4) {
		att_secondary_value = 5;
	}
	else if (index == 5) {
		att_secondary_value = 1;
	}
	else  {
		att_secondary_value = 1;
	}

}

Item :: Item(int index, int damage, int second) : att_index(index), att_damage_value(damage), att_secondary_value(second) {
	if (index == 2) {
		att_name = "Life Potion";
	}
	else if (index == 3) {
		att_name = "Mana Potion";
	}
	else if (index == 4) {
		att_name = "Throwing knife";
	}
	else if (index == 5) {
		att_name = "Debilitating ofuda";
	}
	else  {
		att_name = "Generic item";
	}

}

Item :: Item(std::string name, int index, int damage, int second) : att_index(index), att_name(name), att_damage_value(damage), att_secondary_value(second) {}
Item :: ~Item() {}

std :: string Item :: giveName() const {
	return att_name;
}

int Item :: giveType() const /* 1 : Weapon. 2 : Heal. 3 : Mana. 4 : Projectile. 5 : Stun*/ {
	return att_index;
}

int Item :: giveDamage() const {
	return att_damage_value;
}

int Item :: giveSecondary() const {
	return att_secondary_value;
}

void Item :: setName(std :: string name) {
	att_name = name;
}

void Item :: setValue(int value) {
	att_damage_value = value;
}

void Item :: setSecondary(int value) {
	att_secondary_value = value;
}


Weapon :: Weapon() : Item("Short sword", 1, 4, 0), att_damage_type(2) {}

Weapon :: Weapon(std :: string name) : Item(name, 1, 4, 0), att_damage_type(2) {}

Weapon :: Weapon(int type) : Item("No name", 1, 4, 0), att_damage_type(type) {
	if (type == 1) 
		setName("Pointy knife");
	else if (type == 2)
		setName("Short sword");
	else if (type == 3)
		setName("Mace");
}

Weapon :: Weapon(std::string name, int type) : Item(name, 1, 4, 0), att_damage_type(type) {}

Weapon :: Weapon(int type, int damage) : Item("No_name", 1, damage, 0), att_damage_type(type) {
	if (type == 1) {
		if (damage >= 6)
			setName("Spear");
		else setName("Pointy knife");
	}
	else if (type == 2) {
		if (damage >= 6)
			setName("Long sword");
		else setName("Short sword");
	}
	else if (type == 3) {
		if (damage >= 6)
			setName("War hammer");
		else setName("Mace");
	}
}

Weapon :: Weapon(std::string name, int type, int damage) : Item(name, 1, damage, 0), att_damage_type(type) {}

Weapon :: Weapon(int type, int damage, int second) : Item("No_name", 1, damage, second), att_damage_type(type) {
	if (type == 1) {
		if (damage >= 6)
			setName("Spear");
		else setName("Pointy knife");
	}
	else if (type == 2) {
		if (damage >= 6)
			setName("Long sword");
		else setName("Short sword");
	}
	else if (type == 3) {
		if (damage >= 6)
			setName("War hammer");
		else setName("Mace");
	}
}

Weapon :: Weapon(std::string name, int type, int damage, int second) : Item(name, 1, damage, second), att_damage_type(type) {}

Weapon :: Weapon(const Weapon &Copy) : Item(Copy.att_name, 1, Copy.att_damage_value, Copy.att_secondary_value), att_damage_type(Copy.att_damage_type) {}

Weapon :: ~Weapon() {}


int Weapon :: giveDamageType() const {
	return att_damage_type;
}

int Item :: useItem() {
	if (--att_secondary_value <= 0)
		return 1;
	return 0;
}

bool Item :: giveIsHealing() const {
	return (att_index == 2);
}

bool Item :: equals(Item const& other) const {
	return (att_index == other.att_index && att_damage_value == other.att_damage_value);
}

bool operator==(Item const& first, Item const& second) {
	return first.equals(second);
}

void Item :: addTo(Item const& other) {
	att_secondary_value += other.att_secondary_value;
}

Item &Item :: operator+=(Item const& second) {
	addTo(second);
	return *this;
}

void Item :: increment() {
	att_damage_value ++;
}

Item &Item :: operator++() {
	increment();
	return *this;
}

Item &Item :: operator++(int) {
	increment();
	return *this;
}

void Weapon :: increment() {
	att_damage_value ++;
}

Weapon &Weapon :: operator++() {
	increment();
	return *this;
}

Weapon &Weapon :: operator++(int) {
	increment();
	return *this;
}