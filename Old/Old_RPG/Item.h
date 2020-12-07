#ifndef Vic_STRING
#define Vic_STRING
#include <string>
#endif

class Item {
	//Attributes
protected : 
	int att_index;
	std :: string att_name;
	
	int att_damage_value; //Number it heals/damages
	int att_secondary_value; //Weapon : d+y ; Else : Quantity left

	bool equals(Item const& other) const;
	//Methods
public :
	Item();
	Item(int index);
	Item(std::string name, int index);
	Item(int index, int damage);
	Item(std::string name, int index, int damage);
	Item(int index, int damage, int second);
	Item(std::string name, int index, int damage, int second);
	~Item();

	std :: string giveName() const;
	int giveType() const; // 1 : Weapon. 2 : Heal. 3 : Mana. 4 : Projectile. 5 : Stun
	int giveDamage() const;
	int giveSecondary() const;

	void setName(std :: string name);
	void setValue(int value);
	void setSecondary(int value);
	bool giveIsHealing() const;
	int useItem();
	void addTo(Item const& other);
	Item &operator+=(Item const& second);
	Item &operator++();
	Item &operator++(int);
	void increment();
	friend bool operator==(Item const& first, Item const& second);
};


class Weapon : public Item {
private : 
	int att_damage_type; // 1 = Piercing; 2 = Slicing; 3 = Contondant;
	void increment();
public :
	Weapon();
	Weapon(std::string name);
	Weapon(int type);
	Weapon(std::string name, int type);
	Weapon(int type, int damage);
	Weapon(int type, int damage, int second);
	Weapon(std::string name, int type, int damage);
	Weapon(std::string name, int type, int damage, int second);
	Weapon(Weapon const &copy);
	~Weapon();
	Weapon &operator++();
	Weapon &operator++(int);
	
	int giveDamageType() const;
};