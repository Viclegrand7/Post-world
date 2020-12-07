#ifndef Vic_STRING
#define Vic_STRING
#include <string>
#endif

#ifndef Vic_STDLIB
#define Vic_STDLIB
#include <stdlib.h>
#endif

#ifndef Vic_IOSTREAM
#define Vic_IOSTREAM
#include <iostream>
#endif

#ifndef Vic_VECTOR
#define Vic_VECTOR
#include <vector>
#endif

#ifndef Vic_CHARACTER
#define Vic_CHARACTER
#include"Character.h"
#endif

class Board {
	//Attributes
private : 
	Character att_player;
	
	std :: vector <Character*> att_ennemies;	
	std :: vector <Character*> att_ennemies_alive;
	std :: vector <Character> att_allies;

	//Methods
public :
	Board();
	Board(std::string name);
	Board(std::string name, int max_HP, int max_MP);
	Board(std::string name, int phys, int mag, int soc);
	Board(std::string name, int max_HP, int max_MP, int phys, int mag, int soc);
	Board(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d);
	Board(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus);
	Board(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int armor_pierc, int armor_tranc, int armor_cont);
	Board(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, int armor_cont);
	Board(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, int armor_cont, int damage_type);
	~Board();


	int userTurn();
	void displayPlayer() const;
	void displayAllies() const;
	void displayEnnemies() const;
	void displayEnnemiesStatusWithNumber() const;
	void displayAlliesStatusWithNumber() const;
	int ennemyTurn(int number);
	int allyTurn(int number);
	void playGame();
	void showLoss() const;
	void showWin() const;
	void showFleet() const;
	void displayStatusPlayer() const;

	void createEnnemy();
	void createEnnemy(std::string name);
	void createEnnemy(std::string name, int max_HP, int max_MP);
	void createEnnemy(std::string name, int phys, int mag, int soc);
	void createEnnemy(std::string name, int max_HP, int max_MP, int phys, int mag, int soc);
	void createEnnemy(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d);
	void createEnnemy(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus);
	void createEnnemy(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int armor_pierc, int armor_tranc, int armor_cont);
	void createEnnemy(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, int armor_cont);
	void createEnnemy(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, int armor_cont, int damage_type);

	void createAlly();
	void createAlly(std::string name);
	void createAlly(std::string name, int max_HP, int max_MP);
	void createAlly(std::string name, int phys, int mag, int soc);
	void createAlly(std::string name, int max_HP, int max_MP, int phys, int mag, int soc);
	void createAlly(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d);
	void createAlly(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus);
	void createAlly(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int armor_pierc, int armor_tranc, int armor_cont);
	void createAlly(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, int armor_cont);
	void createAlly(std::string name, int max_HP, int max_MP, int phys, int mag, int soc, int damage_d, int damage_plus, int armor_pierc, int armor_tranc, int armor_cont, int damage_type);

	void addWeapon(Character &target);
	void addWeapon(Character &target, std::string name);
	void addWeapon(Character &target, int type);
	void addWeapon(Character &target, std::string name, int type);
	void addWeapon(Character &target, int type, int damage);
	void addWeapon(Character &target, int type, int damage, int second);
	void addWeapon(Character &target, std::string name, int type, int damage);
	void addWeapon(Character &target, std::string name, int type, int damage, int second);

	void addItem(Character &target, int index);
	void addItem(Character &target, std::string name, int index);
	void addItem(Character &target, int index, int damage);
	void addItem(Character &target, std::string name, int index, int damage);
	void addItem(Character &target, int index, int damage, int second);
	void addItem(Character &target, std::string name, int index, int damage, int second);

	void addItemToPlayer(int index);
	void addItemToPlayer(std::string name, int index);
	void addItemToPlayer(int index, int damage);
	void addItemToPlayer(std::string name, int index, int damage);
	void addItemToPlayer(int index, int damage, int second);
	void addItemToPlayer(std::string name, int index, int damage, int second);

	void upgradePlayerItem(int number);
	void upgradePlayerWeapon(int number);
};