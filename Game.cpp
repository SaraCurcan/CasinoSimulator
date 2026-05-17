#include "Garage.h"
#include <iostream>
#include <string>
#include <stdexcept>

Game::Game():game("N/A"), minBet(0.0){}
Game::Game(std::string game, double minBet):game(game), minBet(minBet){}
Game::Game(const Game& obj) : game(obj.game), minBet(obj.minBet){}
Game& Game::operator=(const GAme& obj) {
    if (this!=&obj) {
        game=obj.game;
        minBet=obj.minBet;
    }
    return *this;
}
Game::~Game(){}
