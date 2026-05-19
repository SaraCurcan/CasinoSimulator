#pragma once

#include "Game.h"
#include "Player.h"
#include<iostream>
#include <vector>
#include<string>

struct number {
    int value;
    std::string color;
};
class Roulette :  public Game {
private:
    std::vector<number> wheel;
    number spinWheel() const;
    void betType(int choice,double bet, Player& player, const number winningSlot);
    void numberBet(double bet, Player& player, const number winningSlot);
    void color(double bet, Player& player, const number winningSlot);
    void evenOdd(double bet,Player& player, const number winningSlot);
public:
    Roulette();
    Roulette(std::string game, double bet);
    Roulette(const Roulette& obj);
    Roulette& operator=(const Roulette& obj);
    ~Roulette() override {};
    void play(Player& player) override;
    void printRules() const override;

};