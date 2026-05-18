#include "Player.h"
Player::Player():name("N/A"), balance(0.0){}
Player::Player(std::string name, double balance): name(name) {
    if (balance>0.0)
        this->balance=balance;
    else {
        this->balance=0.0;
    }
}
Player::Player(const Player& obj) : name(obj.name), balance(obj.balance) {}
Player& Player::operator=(const Player& obj) {
    if (this!=&obj) {
        name=obj.name;
        balance=obj.balance;
    }
    return *this;
}
Player::~Player(){}

std::string Player::getName() const {
    return name;
}
void Player::setName(const std::string& name) {
    if (!name.empty())
        this->name=name;
}
double Player::getBalance() const {
    return balance;
}
void Player::setBalance(double balance){
    if (balance>0.0) {
        this->balance=balance;
    }
    else {
        this->balance=0.0;
    }
}
