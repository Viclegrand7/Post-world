#include "Ennemy.hh"

Ennemy::Ennemy() : Character(){}

int Ennemy::getDamage(){
    return damage;
}

bool Ennemy::isDead(){
    return isDead;
}

Item Ennemy::randomDrop(){
    int ind = rand() % 3;
    Item& I();
    switch (ind)
    {
    case 0:
        Melee M();
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

void Ennemy::attack(){
    timeBeforeAttack += attackDownTime;
    for (std::size_t i=0; i<attackDownTime; i++){
        sleep(1000);
        timeBeforeAttack--;
    }
}