#pragma once
#include<iostream>
#include<string>
class Game {
protected:
    std::string game;
    double minBet;
public:
    Game();
    Game(std::string game, double minBet);
    Game(const Game& obj);
    Game& operator=(const Game& obj);
    virtual ~Game();
    virtual void play(double& price)=0;
    virtual void printRules() const=0;
    virtual double calculatePrize(double bet, double odds) const;
    void validate(double currentBet, double balance) const;
    std::string getName() const;
    double getMinBet() const;
};