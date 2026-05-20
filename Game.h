#pragma once
#include<iostream>
#include<string>
#include "CasinoHistory.h"

class Player;
class Game {
protected:
    std::string game;
    double minBet;
    double validBet() const;
    double handleBetting(Player& player);
public:
    Game();
    Game(std::string game, double minBet);
    Game(const Game& obj);
    Game& operator=(const Game& obj);
    virtual ~Game();
    virtual void play(Player& player, CasinoHistory<Transaction>& log)=0;
    virtual void printRules() const=0;
    virtual double calculatePrize(double bet, double odds) const;
    void validate(double currentBet, double balance) const;
    std::string getName() const;
    double getMinBet() const;
};