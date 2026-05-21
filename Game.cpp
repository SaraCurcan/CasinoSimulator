#include "Game.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

#include "Player.h"
Game::Game():game("N/A"), minBet(0.0){}
Game::Game(std::string game, double minBet):game(game), minBet(minBet){}
Game::Game(const Game& obj) : game(obj.game), minBet(obj.minBet){}
Game& Game::operator=(const Game& obj) {
    if (this!=&obj) {
        game=obj.game;
        minBet=obj.minBet;
    }
    return *this;
}
Game::~Game(){}
double Game::calculatePrize(double bet,double odds) const {
    return bet*odds;
}
void Game::validate(double bet, double balance) const {
    if (bet<minBet)
        throw std::runtime_error("this game requires more money!\n");
    if (bet>balance)
        throw std::runtime_error("Insuficient funds for this bet!\n");
}
std::string Game::getName() const {
    return game;
}
double Game::getMinBet() const {
    return minBet;
}
double  Game::validBet() const {
    double bet;
    std::cin>>bet;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

        throw std::runtime_error("Invalid input! PLease enter a valid number\n");

    }
    return bet;
}

double Game::handleBetting(Player &player) {
    double bet=0;
    while (true) {
    try {
        std::cout << "Enter your bet (Min: " << minBet << "$):\n";
        bet = validBet();
        player.placeBet(bet,minBet);
        break;
    } catch (const std::runtime_error& e) {
        std::cout<<"WARNING "<<e.what()<<" You have $ "<<player.getBalance()<<" . Try again \n";
    }
    }
    return bet;
}
