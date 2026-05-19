#include <iostream>
#include "Blackjack.h"
#include "Game.h"
#include "Roulette.h"
#include "Player.h"
#include "Slots.h"
#include<ctime>
#include<cstdlib>
int main() {
    std::srand(std::time(0));
    Player player("sara", 500.0);
    Roulette roulette;
    roulette.printRules();
    roulette.play(player);
    std::cout << player.getBalance();
    Blackjack blk;
    Slots slots;
    blk.play(player);
    slots.play(player);
}

