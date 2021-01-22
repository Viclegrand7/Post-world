#include "Character.hh"

int main(){
    Character c;
    int i = c.getHealth();
    std::cout << i << std::endl;
    c.getHit(3);
    std::cout << c.getHealth() << std::endl;
    return 1;
}