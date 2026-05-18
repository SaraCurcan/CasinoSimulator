#pragma once
#include <string>
class Player {
private:
    std::string name;
    double balance;
public:
    Player();
    Player(std::string name, double initialBalance);
    Player(const Player& obj);
    Player& operator=(const Player& obj);
    ~Player();
    std::string getName() const;
    void setName(const std::string& name);
    double getBalance() const;
    void setBalance(double balance);
};