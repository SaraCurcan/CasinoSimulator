#pragma once
#include "Game.h"
#include "Player.h"
#include<iostream>
#include<vector>
#include<string>

class Slots : public Game {
private:
    std::vector<std::string> symbols;
    int rows;
    int columns;
    std::vector<std::vector<std::string>> screen() const;
    void printScreen(const std::vector<std::vector<std::string>> &screen) const;
    bool checkLine(const std::vector<std::vector<std::string>> &screen, std::string& winningSymbols) const;
    double multiply(const std::string& symbol) const;
public:
    Slots();
    Slots(std::string game, double minBet,int rows,int columns);
    Slots(const Slots& obj);
    Slots& operator=(const Slots& obj);
   ~Slots() override;
    void play(Player& player) override;
    void printRules() const override;
};