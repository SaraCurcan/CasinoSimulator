#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "CasinoHistory.h"
#include "Blackjack.h"
#include "Roulette.h"
#include "Slots.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    Player jucator("emima", 500.0);
    CasinoHistory<Transaction> istoric;
    istoric.LoadProgress("casino_history.txt");
    Blackjack blackjack;
    Roulette roulette;
    Slots slots;
    blackjack.play(jucator, istoric);
    roulette.play(jucator, istoric);
    slots.play(jucator, istoric);
    istoric.SaveProgress("casino_history.txt");
}