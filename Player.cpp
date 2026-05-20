#include "Player.h"
Player::Player():name("N/A"), balance(0.0),age(0){}
Player::Player(std::string name, double balance,int age): name(name) {
    if (balance>0.0)
        this->balance=balance;
    else {
        this->balance=0.0;
    }
    if (age>0)
        this->age=age;
    else {
        this->age=0;
    }
}
Player::Player(const Player& obj) : name(obj.name), balance(obj.balance),age(obj.age) {}
Player& Player::operator=(const Player& obj) {
    if (this!=&obj) {
        name=obj.name;
        balance=obj.balance;
        age=obj.age;
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
std::ostream& operator<<(std::ostream& out, const Player& player) {
    out<<"Player: "<<player.name<<" | "<<player.age<<" | Balance: $"<<player.balance<<"\n";
    return out;
}
int Player::getAge() const {
    return age;
}
void Player::setAge(int age) {
    if (age>0)
        this->age=age;
    else
        this->age=0;
}