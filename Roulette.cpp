#include "Roulette.h"
#include <iostream>
#include <random>
#include<string>
#include <fstream>
#include <limits>

Roulette::Roulette():Game("Roulette", 10.0) {
    wheel.resize(37);
    wheel[0]={0,"Green"};
    for (int i=1;i<=36;++i) {
        if ((i>=1 && i<=10) || (i>=19 && i<=28)) {
            if (i%2==1) {
                wheel[i]={i,"Red"};
            }
            else {
                wheel[i]={i,"Black"};
            }
        }
        else {
            if (i%2==0) {
                wheel[i]={i,"Red"};
            }
            else {
                wheel[i]={i,"Black"};
            }
        }
    }
}
Roulette::Roulette(std::string game,double bet):Game(game,bet) {
    wheel.resize(37);
    wheel[0]={0,"Green"};
    for (int i=1;i<=36;++i) {
        if ((i>=1 && i<=10) || (i>=19 && i<=28)) {
            if (i%2==1) {
                wheel[i]={i,"Red"};
            }
            else {
                wheel[i]={i,"Black"};
            }
        }
        else {
            if (i%2==0) {
                wheel[i]={i,"Red"};
            }
            else {
                wheel[i]={i,"Black"};
            }
        }
    }
}
Roulette::Roulette(const Roulette& obj):Game(obj) {
    this->wheel=obj.wheel;
}
Roulette& Roulette::operator=(const Roulette& obj) {
    if (this!=&obj) {
        Game::operator=(obj);
        this->wheel=obj.wheel;
    }
    return *this;
}
Roulette::~Roulette() {};

number Roulette::spinWheel() const {
    int random=rand()%37;
    return wheel[random];
}

void Roulette::numberBet(double bet, Player &player, const number winningSlot,CasinoHistory<Transaction>& log) {
    int guessed=-1;
    std::string input;
    std::cout<<"Enter a number to bet on (0-36)\n";
    while (true) {
        std::getline(std::cin, input);
        try {
            guessed=std::stoi(input);
            if (guessed>=0 && guessed<37) break;
        } catch (...){}
        std::cout<<"Invalid input! Enter a number to bet on (0-36)\n";
    }
    std::cout<<"SPINNING THE WHEEL\n";
    std::cout<<"The ball landed on: "<<winningSlot.color<<" "<<winningSlot.value<<"\n";
    if (guessed==winningSlot.value) {
        double prize=calculatePrize(bet,35.0);
        player.setBalance(player.getBalance()+prize);
        std::cout<<"HIT ! YOU WON $"<<prize<<"\n";
        log.addEvvent({game, bet, prize});
    }else {
        std::cout<<"LOSER ! BETTER LUCK NEXT TIME\n";
        log.addEvvent({game, bet, 0.0});
    }
}

void Roulette::color(double bet, Player &player, const number winningSlot,CasinoHistory<Transaction>& log) {
    std::string input;
    int colorChoice=0;
    std::cout<<"Choose a color: 1.RED | 2.BLACK\n";
    while (true) {
        std::getline(std::cin, input);
        try {
            colorChoice=std::stoi(input);
            if (colorChoice==1 || colorChoice==2) break;
        }catch (...){}
        std::cout<<"Press 1 for RED or 2 for BLACK\n";
    }
    std::string chosenColor;
    if (colorChoice==1) {
        chosenColor="Red";
    }else { chosenColor="Black"; }
    std::cout<<"SPINNING THE WHEEL\n";
    std::cout<<"The ball landed on: "<<winningSlot.color<<" "<<winningSlot.value<<"\n";
    if (chosenColor==winningSlot.color) {
        double prize=calculatePrize(bet,2.0);
        player.setBalance(player.getBalance()+prize);
        std::cout<<"Correct ! YOU WON $"<<prize<<"\n";
        log.addEvvent({game, bet, prize});
    }else {
        std::cout<<"Wrong color!You lost!\n";
        log.addEvvent({game, bet, 0.0});
    }
}

void Roulette::evenOdd(double bet, Player &player, const number winningSlot,CasinoHistory<Transaction>& log) {
    std::string input;
    int choice=0;
    std::cout<<"Choose: 1.EVEN | 2.ODD\n";
    while(true) {
        std::getline(std::cin,input);
        try{
            choice=std::stoi(input);
            if (choice==1 || choice==2) break;
        }catch(...) {}
        std::cout<<"Choose: 1.EVEN | 2.ODD\n";
    }
    std::cout<<"SPINNING THE WHEEL\n";
    std::cout<<"The ball landed on: "<<winningSlot.color<<" "<<winningSlot.value<<"\n";
    if (winningSlot.value==0) {
        std::cout<<"0 !!!. Houes wins\n";
        log.addEvvent({game, bet, 0.0});
        return;
    }
    bool isEven=(winningSlot.value%2==0);
    if (choice==1) {
        if (isEven) {
            double prize=calculatePrize(bet,2.0);
            player.setBalance(player.getBalance()+prize);
            std::cout<<"Correct ! YOU WON $"<<prize<<"\n";
            log.addEvvent({game, bet, prize});
        } else {
            std::cout<<"Wrong parity !You lost! \n";
            log.addEvvent({game, bet, 0.0});
        }
    }
        else if (choice==  2) {
            if (!isEven) {
                double prize=calculatePrize(bet,2.0);
                player.setBalance(player.getBalance()+prize);
                std::cout<<"Correct ! YOU WON $"<<prize<<"\n";
                log.addEvvent({game, bet, prize});
            } else {
                std::cout<<"Wrong parity !You lost! \n";
                log.addEvvent({game, bet, 0.0});
            }
        }
}

void Roulette::betType(int choice, double bet, Player &player, const number winningSlot,CasinoHistory<Transaction>& log) {
    if (choice==1)
        numberBet(bet,player,winningSlot,log);
    else if (choice==2)
        color(bet,player,winningSlot,log);
    else if (choice==3)
        evenOdd(bet,player,winningSlot,log);
}

void Roulette::play(Player& player,CasinoHistory<Transaction>& log) {
    std::cout << "\n=========================================\n";
    std::cout << "          WELCOME TO ROULETTE          \n";
    std::cout << "=========================================\n";
    double bet=handleBetting(player);
    std::cout<<"Choose bet type: \n 1.EXACT NUMBER \n 2.CCOLOR (Red/Black) \n 3. EVEN/ODD\n";
    std::string input;
    int choice=0;
    while (true) {
        std::getline(std::cin,input);
        try {
            choice=std::stoi(input);
            if (choice==1 || choice==2 || choice==3) break;
        }catch (...){}
        std::cout<<"Enter 1,2 or 3\n";
    }
    number winningSlot=spinWheel();
    betType(choice,bet,player,winningSlot,log);
}

void Roulette::printRules() const {
    std::ifstream file("RouletteRules.txt");
    if (!file.is_open()) {
        std::cout<<"Place your bets on numbers, colors, or parity! Good luck!\n";
        return;
    }
    std::string line;
    while (std::getline(file,line)) {
        std::cout<<line<<"\n";
    }
    file.close();
}
