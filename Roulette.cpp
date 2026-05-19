#include "Roulette.h"
#include <iostream>
#include <random>
#include<string>
#include <limits>
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