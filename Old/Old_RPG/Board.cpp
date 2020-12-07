#include "Board.h"

int Board :: userTurn() { // Returns -1 in case of loss, 1 in case of victory, 2 if fleet, 0 otherwhise
	if (!att_player.giveConsciousness() || !att_player.giveLiving())
		return -1;
	if (att_player.giveDoTNumber()) {
		att_player.getHit(att_player.giveDoTNumber(), 0);
		att_player.reduceDoT();
	}
	if (att_player.giveStunned() || !(att_player.giveConsciousness()) || !(att_player.giveLiving()))
		return 0;
	displayPlayer();
	displayAllies();
	std :: cout << std :: endl;
	displayEnnemies();
	do {
		std :: cout << std :: endl << std :: endl <<  "Now's my turn! Should I attack (1), use a spell (2), an item (3) or flee (4)?" << std :: endl;
		unsigned int choice;
		std :: cin >> choice;
		while (choice < 1 || choice > 4) {
			std :: cout << "Not sure what that means. I need to chose whether to attack (1), throw a spell (2), use an item (3) or to run away (4)" << std :: endl;
			std :: cin.clear(); std :: cin.ignore();  
			std :: cin >> choice;
		}
		switch (choice) {
		case 1 : if (att_ennemies_alive.size() > 1) {
				std :: cout << "I'm going to use my " << att_player.giveWeaponName() << ". But on who?" << std :: endl;
				displayEnnemiesStatusWithNumber();
				std :: cin >> choice;
				while (choice < 0 || choice > att_ennemies_alive.size())  {
					std :: cout << "I need to chose between those targets" << std :: endl;
					std :: cin.clear(); std :: cin.ignore();  
					std :: cin >> choice;
				}
				if (choice) {
					int deads = att_player.attack(*att_ennemies_alive[choice - 1]);
					if (deads == -1) {
						std :: cout << "Unfortunately, you were not strong enough." << std :: endl;
						return -1;
					}
					if (deads == 1)
						att_ennemies_alive.erase(att_ennemies_alive.begin() + choice - 1);
					return 0;
				}
			}
			else  {
				int deads = att_player.attack(*att_ennemies_alive[0]);
				if (deads == -1) {
					std :: cout << "Unfortunately, you were not strong enough." << std :: endl;
					return -1;
				}
				if (deads == 1) {
					att_ennemies_alive.clear();
					return 1;
				}
				return 0;
			}
			break;
		case 2 : if (!(att_player.giveNumber())) {
				std :: cout << "I really should have learnt some spells. That won't do" << std :: endl;
			}
			else {
				unsigned int number = att_player.giveNumber();
				att_player.displaySpellsWithNumber();
				std :: cout << std :: endl << "Which spell to use?" << std :: endl;
				do {
					std :: cin >> choice;
					std :: cin.clear(); std :: cin.ignore();  
				} while (choice < 0 || choice > number);
				if (choice) {
					if (att_ennemies_alive.size() > 1) {
						std :: cout <<  "I'm going to use " << att_player.giveSpells()[choice - 1].giveName() << ". But on who?" << std :: endl;
						displayEnnemiesStatusWithNumber();
						unsigned int ennemy_choice = -1;
						std :: cin >> ennemy_choice;
						while (ennemy_choice < 0 || ennemy_choice > att_ennemies_alive.size()) {
							std :: cout << "I need to chose between those targets" << std :: endl;
							std :: cin.clear(); std :: cin.ignore();  
							std :: cin >> ennemy_choice;
						}
						if (ennemy_choice) {
							int deads = att_player.useSpell(choice, *att_ennemies_alive[ennemy_choice - 1]);
							if (deads == -1 || deads == 2) {
								std :: cout << "Unfortunately, you were not strong enough." << std :: endl;
								return -1;
							}
							else if (deads == 1) 
								att_ennemies_alive.erase(att_ennemies_alive.begin() + ennemy_choice - 1);
							return 0;
						}
					}
					else {  
						int deads = att_player.useSpell(choice, *att_ennemies_alive[0]);
						if (deads == -1 || deads == 2) {
							std :: cout << "Unfortunately, you were not strong enough." << std :: endl;
							return -1;
						}
						if (deads == 1) {
							att_ennemies_alive.clear();
							return 1;
						}
					}
				}
			}
			break;
		case 3:  // USE AN INVENTORY, DISPLAY IT,... 
			att_player.displayInventoryWithNumber();
			std :: cout << std :: endl << "What item to use?" << std :: endl;
			do {
				std :: cin.clear(); std :: cin.ignore();  
				std :: cin >> choice;
			} while(choice > att_player.giveInventorySize());
			if (choice) {
				if (choice  <= att_player.giveWeaponNumber()) {
					att_player.exchangeWeapon(choice - 1);
					return 0;
				}
				else  {
					choice -= att_player.giveWeaponNumber() + 1;
					if (att_player.giveIsHealing(choice)) { // MAYBE AUTHORIZE USE ON ALLIES
						att_player.useItem(choice, att_player);
						return 0;
					}
					if (att_ennemies_alive.size() > 1) {
						std :: cout << "I'm going to use " << att_player.giveItemName(choice) << ". But on who?" << std :: endl;
						displayEnnemiesStatusWithNumber();
						unsigned int ennemy_choice = -1;
						std :: cin >> ennemy_choice;
						while (ennemy_choice < 0 || ennemy_choice > att_ennemies_alive.size()) {
							std :: cout << "I need to chose between those targets" << std :: endl;
							std :: cin.clear(); std :: cin.ignore(); 
							std :: cin >> ennemy_choice;
						}
						if (ennemy_choice) {
							if (att_player.useItem(choice, *att_ennemies_alive[ennemy_choice - 1])) {
								att_ennemies_alive.erase(att_ennemies_alive.begin() + ennemy_choice - 1);
								return 0;
							}
						}
					}
					else {
						if (att_player.useItem(choice, *att_ennemies_alive[0])) {
							return 1;
						}
					}
				}
			}
			break;
		case 4: std :: cout << "I only have 20\% chance to make it alive if I flee. Should I do it? Yes (1) or no (0)?" << std::endl;
			std :: cin >> choice;
			while (choice < 0 || choice > 1) {
				std :: cout << "I don't have much time to decide. Should I flee (1) or fight (0)?" << std :: endl;
				std :: cin.clear(); std :: cin.ignore();  
				std :: cin >> choice;
			}
			if (choice) {
				if (rand()%100 < 20)
					return 2;
				else {
					std :: cout << "Damn, it did not work" << std :: endl;
					return 0;
				}
			}
		}
	} while(1);
}

	Board :: Board() : att_player(), att_ennemies(), att_ennemies_alive(), att_allies() {}
	Board :: Board(std::string name) : att_player(name), att_ennemies(), att_ennemies_alive(), att_allies() {}
	Board :: Board(std::string name, int max_HP, int max_MP) : att_player(name, max_HP, max_MP), att_ennemies(), att_ennemies_alive(), att_allies() {}
	Board :: Board(std::string name, int phys, int mag, int soc) : att_player(name, phys, mag, soc), att_ennemies(), att_ennemies_alive(), att_allies() {}
	Board :: Board(std::string name, int max_HP, int max_MP, int phys, int mag, int soc) : att_player(name, max_HP, max_MP, phys, mag, soc), att_ennemies(), att_ennemies_alive(), att_allies() {}
	Board :: Board(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d) : att_player(name, max_HP, max_MP, phys, mag, soc, damage_d), att_ennemies(), att_ennemies_alive(), att_allies() {}
	Board :: Board(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus) : att_player(name, max_HP, max_MP, phys, mag, soc, damage_d, damage_plus), att_ennemies(), att_ennemies_alive(), att_allies() {}
	Board :: Board(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int armor_pierc, int armor_tranc, int armor_cont) : att_player(name, max_HP, max_MP, phys, mag, soc, damage_d, armor_pierc, armor_tranc, armor_cont), att_ennemies(), att_ennemies_alive(), att_allies() {}
	Board :: Board(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, int armor_cont) : att_player(name, max_HP, max_MP, phys,  mag, soc, damage_d, damage_plus, armor_pierc, armor_tranc, armor_cont), att_ennemies(), att_ennemies_alive(), att_allies() {}
	Board :: Board(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, int armor_cont, int damage_type) : att_player(name, max_HP, max_MP, phys,  mag, soc, damage_d, damage_plus, armor_pierc, armor_tranc, armor_cont, damage_type), att_ennemies(), att_ennemies_alive(), att_allies() {}
	Board :: ~Board() {
		for (unsigned int i = 0 ; i < att_ennemies.size() ; i++)
			delete att_ennemies[i];
		att_ennemies.clear();
		att_ennemies_alive.clear();
		att_allies.clear();
	}

void Board :: displayPlayer() const {
	std :: cout << att_player << std :: endl;
}

void Board :: displayAllies() const {
	if (att_allies.size())
		std :: cout << "Your allies" << std :: endl;
	for (unsigned int i = 0; i < att_allies.size(); i++) {
		std :: cout << att_allies[i];
	}
	std :: cout << std :: endl;
}

void Board :: displayEnnemies() const {
	if (att_ennemies.size())
		std :: cout << "Your ennemies" << std :: endl;
	for (unsigned int i = 0 ; i < att_ennemies.size() ; i++) {
		std :: cout << *att_ennemies[i];
	}
}

void Board :: displayEnnemiesStatusWithNumber() const {
	if (att_ennemies_alive.size()) 
		std :: cout << "Get back (0)" << std :: endl;
	for (unsigned int i = 0; i < att_ennemies_alive.size() ; i++) 
		std :: cout << "(" << i + 1 << ") " << (*att_ennemies_alive[i]);
}

void Board ::displayAlliesStatusWithNumber() const {
	std :: cout << "Get back (0)" << std :: endl;
	for (unsigned int i = 0; i < att_allies.size() ; i++) 
		std :: cout << "(" << i + 1 << ") " << att_allies[i];
}

void Board :: createEnnemy() {
	Character* new_guy = new Character();
	att_ennemies.push_back(new_guy);
	att_ennemies_alive.push_back(new_guy);
}

void Board :: createEnnemy(std::string name) {
	Character* new_guy = new Character(name);
	att_ennemies.push_back(new_guy);
	att_ennemies_alive.push_back(new_guy);
}

void Board :: createEnnemy(std::string name, int max_HP, int max_MP) {
	Character* new_guy = new Character(name, max_HP, max_MP);
	att_ennemies.push_back(new_guy);
	att_ennemies_alive.push_back(new_guy);
}

void Board :: createEnnemy(std::string name, int phys, int mag, int soc) {
	Character* new_guy = new Character(name, phys, mag, soc);
	att_ennemies.push_back(new_guy);
	att_ennemies_alive.push_back(new_guy);
}

void Board :: createEnnemy(std::string name, int max_HP, int max_MP, int phys, int mag, int soc) {
	Character* new_guy = new Character(name, max_HP, max_MP, phys, mag, soc);
	att_ennemies.push_back(new_guy);
	att_ennemies_alive.push_back(new_guy);
}

void Board :: createEnnemy(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d) {
	Character* new_guy = new Character(name, max_HP, max_MP, phys, mag, soc, damage_d);
	att_ennemies.push_back(new_guy);
	att_ennemies_alive.push_back(new_guy);
}

void Board :: createEnnemy(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus) {
	Character* new_guy = new Character(name, max_HP, max_MP, phys, mag, soc, damage_d, damage_plus);
	att_ennemies.push_back(new_guy);
	att_ennemies_alive.push_back(new_guy);
}

void Board :: createEnnemy(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int armor_pierc, int armor_tranc, int armor_cont) {
	Character* new_guy = new Character(name, max_HP, max_MP, phys, mag, soc, damage_d, armor_pierc, armor_tranc, armor_cont);
	att_ennemies.push_back(new_guy);
	att_ennemies_alive.push_back(new_guy);
}

void Board :: createEnnemy(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, int armor_cont) {
	Character* new_guy = new Character(name, max_HP, max_MP, phys, mag, soc, damage_d, damage_plus, armor_pierc, armor_tranc, armor_cont);
	att_ennemies.push_back(new_guy);
	att_ennemies_alive.push_back(new_guy);
}

void Board :: createEnnemy(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, int armor_cont, int damage_type) {
	Character* new_guy = new Character(name, max_HP, max_MP, phys, mag, soc, damage_d, damage_plus, armor_pierc, armor_tranc, armor_cont, damage_type);
	att_ennemies.push_back(new_guy);
	att_ennemies_alive.push_back(new_guy);
}

void Board :: createAlly() {
	Character new_guy;
	att_allies.push_back(new_guy);
}

void Board :: createAlly(std::string name) {
	Character new_guy(name);
	att_allies.push_back(new_guy);
}

void Board :: createAlly(std::string name, int max_HP, int max_MP) {
	Character new_guy(name, max_HP, max_MP);
	att_allies.push_back(new_guy);
}

void Board :: createAlly(std::string name, int phys, int mag, int soc) {
	Character new_guy(name, phys, mag, soc);
	att_allies.push_back(new_guy);
}

void Board :: createAlly(std::string name, int max_HP, int max_MP, int phys, int mag, int soc) {
	Character new_guy(name, max_HP, max_MP, phys, mag, soc);
	att_allies.push_back(new_guy);
}

void Board :: createAlly(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d) {
	Character new_guy(name, max_HP, max_MP, phys, mag, soc, damage_d);
	att_allies.push_back(new_guy);
}

void Board :: createAlly(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus) {
	Character new_guy(name, max_HP, max_MP, phys, mag, soc, damage_d, damage_plus);
	att_allies.push_back(new_guy);
}

void Board :: createAlly(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int armor_pierc, int armor_tranc, int armor_cont) {
	Character new_guy(name, max_HP, max_MP, phys, mag, soc, damage_d, armor_pierc, armor_tranc, armor_cont);
	att_allies.push_back(new_guy);
}

void Board :: createAlly(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, int armor_cont) {
	Character new_guy(name, max_HP, max_MP, phys, mag, soc, damage_d, damage_plus, armor_pierc, armor_tranc, armor_cont);
	att_allies.push_back(new_guy);
}

void Board :: createAlly(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, int armor_cont, int damage_type) {
	Character new_guy(name, max_HP, max_MP, phys, mag, soc, damage_d, damage_plus, armor_pierc, armor_tranc, armor_cont, damage_type);
	att_allies.push_back(new_guy);
}

int Board :: ennemyTurn(int number) { // Returns -1 in case of loss, 1 if victory, 0 otherwhise
	if (att_ennemies_alive[number]->giveDoTNumber()) {
		int deads = att_ennemies_alive[number]->getHit(att_ennemies_alive[number]->giveDoTNumber(), 0);
		att_ennemies_alive[number]->reduceDoT();
		if (deads) {
			if (att_ennemies_alive.size() == 1)
				return 1;
			att_ennemies_alive.erase(att_ennemies_alive.begin() + number);
			return 0;
		}
	}
	if (att_ennemies_alive[number]->giveStunned() || !(att_ennemies_alive[number]->giveConsciousness()) || !(att_ennemies_alive[number]->giveLiving()))
		return 0;
	int choice = rand() % att_allies.size();
	if (choice) {
		int deads;
		if (att_ennemies_alive[number]->giveNumber() && att_ennemies_alive[number]->giveMP() && rand() % 2)
			deads = att_ennemies_alive[number]->useSpell(rand() % att_ennemies_alive[number]->giveNumber(), att_allies[choice]);
		else 
			deads = att_ennemies_alive[number]->attack(att_allies[choice]);
		if (deads == -1) {
			if (att_ennemies_alive.size() == 1)
				return 1;
			att_ennemies_alive.erase(att_ennemies_alive.begin() + number);
		}
		else if (deads == 1) {
			att_allies.erase(att_allies.begin() + choice - 1);
		}
		else if (deads == 2) {
			if (att_ennemies.size() == 1)
				return 1;
			att_ennemies_alive.erase(att_ennemies_alive.begin() + number);
			att_allies.erase(att_allies.begin() + choice - 1);
		}
		return 0;
	}
	else {
		int deads;
		if (att_ennemies_alive[number]->giveNumber() && att_ennemies_alive[number]->giveMP() && rand() % 2)
			deads = att_ennemies_alive[number]->useSpell(rand() % att_ennemies_alive[number]->giveNumber(), att_player);
		else 
			deads = att_ennemies_alive[number]->attack(att_player);
		if (deads == -1) {
			if (att_ennemies_alive.size() == 1)
				return 1;
			att_ennemies_alive.erase(att_ennemies_alive.begin() + number);
			return 0;
		}
		if (deads)
			return -1;
		return 0;
	}
}

int Board :: allyTurn(int number) { // Returns 1 if victory, 0 otherwhise
	if (att_allies[number].giveDoTNumber()) {
		int deads = att_allies[number].getHit(att_allies[number].giveDoTNumber(), 0);
		att_ennemies_alive[number]->reduceDoT();
		if (deads) {
			att_allies.erase(att_allies.begin() + number - 1);
			return 0;
		}
	}
	if (att_allies[number].giveStunned() || !(att_allies[number].giveConsciousness()) || !(att_allies[number].giveLiving()))
		return 0;
	int choice = rand() % att_ennemies_alive.size();
	int deads;
	if (att_allies[number].giveNumber() && att_allies[number].giveMP() && rand() % 2)
		deads = att_allies[number].useSpell(rand() % att_allies[number].giveNumber(), *att_ennemies_alive[choice]);
	else 
		deads = att_allies[number].attack(*att_ennemies_alive[choice]);
	if (deads == -1) {
		att_allies.erase(att_allies.begin() + number);
	}
	else if (deads == 1) {
		if (att_ennemies_alive.size() == 1)
			return 1;
		att_ennemies_alive.erase(att_ennemies_alive.begin() + choice);
	}
	else if (deads == 2) {
		if (att_ennemies_alive.size() == 1)
			return 1;
		att_ennemies_alive.erase(att_ennemies_alive.begin() + choice);
		att_allies.erase(att_allies.begin() + number);
	}
	return 0;
}

void Board :: showFleet() const {
	std :: cout << "Great! I made it out alive!" << std :: endl;
}

void Board :: playGame() {
	int turn = 1;
	int does_win;
	do {
		std :: cout << std :: endl << std :: endl << std :: endl << std :: endl << std :: endl << std :: endl << std :: endl << std :: endl << std :: endl << std :: endl << std :: endl << std :: endl << std :: endl << "Turn number " << turn << std :: endl;
		does_win = userTurn();
		if (does_win == -1) {
			showLoss();
			return;
		}
		if (does_win == 1) {
			showWin();
			return;
		}
		if (does_win == 2) {
			showFleet();
			return;
		}
		for (unsigned int i = 0; i < att_allies.size() ; i++) {
			does_win = allyTurn(i);
			if (does_win) {
				showWin();
				return;
			}
		}
		for (unsigned int i = 0; i < att_ennemies_alive.size() ; i++) {
			does_win = ennemyTurn(i);
			if (does_win == -1) {
				showLoss();
				return;
			}
			if (does_win == 1) {
				showWin();
				return;
			}
		}
		turn++;
	} while (1);
}

void Board :: showWin() const {
	std :: cout << "Congratulations, you won" << std :: endl;
}

void Board :: showLoss() const {
	std :: cout << "GAME OVER" << std :: endl;
}


void Board :: addWeapon(Character &target) {
	target.addWeapon();
}
void Board :: addWeapon(Character &target, std::string name) {
	target.addWeapon(name);
}
void Board :: addWeapon(Character &target, int type) {
	target.addWeapon(type);
}
void Board :: addWeapon(Character &target, std::string name, int type) {
	target.addWeapon(name, type);
}
void Board :: addWeapon(Character &target, int type, int damage) {
	target.addWeapon(type, damage);
}
void Board :: addWeapon(Character &target, int type, int damage, int second) {
	target.addWeapon(type, damage, second);
}
void Board :: addWeapon(Character &target, std::string name, int type, int damage) {
	target.addWeapon(name, type, damage);
}
void Board :: addWeapon(Character &target, std::string name, int type, int damage, int second) {
	target.addWeapon(name, type, damage, second);
}

void Board :: addItem(Character &target, int index) {
	target.addItem(index);
}
void Board :: addItem(Character &target, std::string name, int index) {
	target.addItem(name, index);
}
void Board :: addItem(Character &target, int index, int damage) {
	target.addItem(index, damage);
}
void Board :: addItem(Character &target, std::string name, int index, int damage) {
	target.addItem(name, index, damage);
}
void Board :: addItem(Character &target, int index, int damage, int second) {
	target.addItem(index, damage, second);
}
void Board :: addItem(Character &target, std::string name, int index, int damage, int second) {
	target.addItem(name, index, damage, second);
}

void Board :: addItemToPlayer(int index) {
	att_player.addItem(index);
}
void Board :: addItemToPlayer(std::string name, int index) {
	att_player.addItem(name, index);
}
void Board :: addItemToPlayer(int index, int damage) {
	att_player.addItem(index, damage);
}
void Board :: addItemToPlayer(std::string name, int index, int damage) {
	att_player.addItem(name, index, damage);
}
void Board :: addItemToPlayer(int index, int damage, int second) {
	att_player.addItem(index, damage, second);
}
void Board :: addItemToPlayer(std::string name, int index, int damage, int second) {
	att_player.addItem(name, index, damage, second);
}

void Board :: upgradePlayerItem(int number) {
	att_player.upgradeItem(number);
}

void Board :: upgradePlayerWeapon(int number) {
	att_player.upgradeWeapon(number);
}


void Board :: displayStatusPlayer() const {
	att_player.displayStatus();
}