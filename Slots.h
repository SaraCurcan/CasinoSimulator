#pragma once
#include "Game.h"
#include<iostream>
#include<vector>
#include<string>

class Slots : public Game {
private:
    std::vector<std::string> symbols;
    int rows;
    int columns;
    std::vector<std::vector<std::string>> screen() const;
public:
    Slots();
    Slots(std::string game, double minBet,int rows,int columns);
    Slots(const Slots& obj);
    Slots& operator=(const Slots& obj);
    virtual ~Slots();
    void play(double& price) override;
    void printRules() const override;
};