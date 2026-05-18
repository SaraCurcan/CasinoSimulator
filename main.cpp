#include <iostream>
#include "Blackjack.h"
#include "Player.h"
int main() {
    Game* joc=new Blackjack();
    Player jucator("SAra",100.0);
    joc->printRules();
    joc->play(jucator);
    delete joc;
}
