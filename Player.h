#pragma once
#include <string>
#include<iostream>
#include<stdexcept>
class Player {
private:
    std::string name;
    double balance;
    int age;
public:
    Player();
    Player(std::string name, double initialBalance, int age=0);
    Player(const Player& obj);
    Player& operator=(const Player& obj);
    ~Player();
    std::string getName() const;
    void setName(const std::string& name);
    double getBalance() const;
    void setBalance(double balance);
    int getAge() const;
    void setAge(int age);
    template <typename T>
    void placeBet(T amount, double bet) {
        if (amount<=0) {
            throw std::runtime_error("Bet amount must be positive\n");
        }
        if (static_cast<double>(amount)<bet) {
            throw std::runtime_error("This game requires a higher bet!\n");
        }
        if (static_cast<double>(amount)>balance) {
            throw std::runtime_error("Insufficient money!\n");
        }
        balance-=static_cast<double>(amount);
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};