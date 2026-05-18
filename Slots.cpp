#include"Slots.h"
#include<iostream>
#include<random>
#include<ctime>
#include<string>
#include<fstream>
#include<limits>
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

std::vector<std::vector<std::string>> Slots::screen() const {
    std::vector<std::vector<std::string>> screen(rows,std::vector<std::string>(columns));
    for (int i=0;i<rows;++i) {
        for (int j=0;j<columns;++j) {
            int random=rand()%symbols.size();
            screen[i][j]=symbols[random];
        }
    }
    return screen;
}

void Slots::printScreen(const std::vector<std::vector<std::string>> &screen) const{
    for (int i=0;i<rows;i++) {
        std::cout<<"| ";
        for (int j=0;j<columns;++j) {
            std::cout<<screen[i][j]<<" | \n";
        }
        std::cout<<std::endl;
    }
}

bool Slots::checkLine(const std::vector<std::vector<std::string> > &screen, std::string &winningSymbols) const {
    int middle=rows/2;
    winningSymbols=screen[middle][0];
    for (int j=1;j<columns;++j) {
        if (screen[middle][j]!=winningSymbols) {
            return false;
        }
    }
    return true;
}

double Slots::multiply(const std::string& symbol) const {
    if (symbol=="777") return 20.0;
    if (symbol=="BAR") return 10.0;
    if (symbol=="PLUM" || symbol=="ORANGE") return 5.0;
    if (symbol=="CHERRY" || symbol=="LEMON") return 3.0;
    return 0.0;
}
void Slots::play(Player& player) {
    std::cout<<"===== SPINNING THE REELS IN "<<getName()<<" =====\n";
    std::cout<<"Enter your bet (Min: "<<getMinBet()<<" )\n";
    double bet=validBet();
    player.placeBet(bet,getMinBet());
    std::vector<std::vector<std::string>> actualScreen=screen();
    std::cout<<"-----SCREEN-----\n";
    printScreen(actualScreen);
    std::cout<<"-------------------\n";

    std::string winningSymbols;
    if (checkLine(actualScreen,winningSymbols)) {
        double odds=multiply(winningSymbols);
        double prize=calculatePrize(bet,odds);
        player.setBalance(player.getBalance()+prize);
        std::cout << "🎉 WINNER! Matching line of [" << winningSymbols << "]!\n";
        std::cout << "💰 You won: $" << prize << "\n";
    }
    else {
        std::cout<<"❌. No match. Better luck next time!\n";
    }
}

void Slots::printRules() const {
    std::ifstream file("SlotsRules.txt");
    if (!file.is_open()) {
        std::cout << "Welcome to " << getName() << "! Bet above $" << getMinBet() << " and match 3 symbols on the middle row to win!\n";
        return;
    }
    std::string line;
    std::cout<<std::endl;
    while (std::getline(file,line)) {
        std::cout<<line<<"\n";
    }
    std::cout<<"\n";
    file.close();
}
