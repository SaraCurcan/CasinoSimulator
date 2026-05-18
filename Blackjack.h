#pragma once
#include "Game.h"
#include "Player.h"
#include <vector>
#include<string>
class Blackjack : public Game {
private:
    std::vector<std::string> deck;
    void initializeDeck();
    void shuffleDeck();
    int handValue(const std::vector<std::string>& hand) const;
    int cardValue(const std::string& card) const;
    void showHand(const std::string& owner, const std::vector<std::string>& hand, bool hideCard=false) const;
    void winner(Player& player, double bet,int playertotal,int dealerTotal);
    void playerRound(std::vector<std::string>& playerHand, int& deckIndex,const std::string& playerName);
public:
    Blackjack();
    Blackjack(std::string game, double bet);
    Blackjack(const Blackjack& obj);
    Blackjack& operator=(const Blackjack& obj);
    ~Blackjack() override;

    void play(Player& player) override;
    void printRules() const override;
};