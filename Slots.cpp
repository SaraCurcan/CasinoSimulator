#include"Slots.h"
#include<iostream>
#include<random>
#include<ctime>
#include<string>
Slots::Slots():Game("Slots",1.0), rows(3),columns(3) {
    symbols={"CHERRY","LEMON","ORANGE","PLUM","BAR","777"};
}
Slots::Slots(std::string game, double bet, int rows, int columns):
Game(game,bet), rows(rows), columns(columns) {
    symbols={"CHERRY","LEMON","ORANGE","PLUM","BAR","777"};
}
Slots::Slots(const Slots& obj):Game(obj),rows(obj.rows),columns(obj.columns),symbols(obj.symbols){}
Slots& Slots::operator=(const Slots& obj) {
    if (this!=&obj) {
        Game::operator=(obj);
        rows=obj.rows;
        columns=obj.columns;
        symbols=obj.symbols;
    }
    return *this;
}
Slots::~Slots(){}
