#include "Ennemy.hh"

Ennemy::Ennemy() : Character(){}

int Ennemy::getDamage(){
    return damage;
}

bool Ennemy::isDead(){
    return isDead;
}

Item Ennemy::randomDrop(){
    int ind = rand() % 3;   //Should return an unsigned int between 0 and Board.att_itemsList.size() or something
    Item& I();              //Why?
    switch (ind)
    {
    case 0:
        Melee M();          //Creates the default melee, may not be what we want
        I = M;
        break;
    case 1:
        Gun G();
        break;
    case 2:
        PowerUp P();
        break;
    
    default:
        break;
    }
}

void Ennemy::attack(){                              //Check if you can atatck first
    timeBeforeAttack += attackDownTime;
    for (std::size_t i=0; i<attackDownTime; i++){ //Do not do that. You just paused the game for several seconds. An 'update' function should deal with lowering it one by one
        sleep(1000);
        timeBeforeAttack--;
    }
}