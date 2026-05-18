#include "Blackjack.h"
#include <iostream>
#include<random>
#include<algorithm>
#include<string>
#include<limits>
#include<fstream>
Blackjack::Blackjack() : Game("Blackjack", 5.0) {
    initializeDeck();
}
Blackjack::Blackjack(std::string game, double bet) : Game(game, bet) {
    initializeDeck();
}
Blackjack::Blackjack(const Blackjack& obj) : Game(obj), deck(obj.deck) {}
Blackjack& Blackjack::operator=(const Blackjack& obj) {
    if (this!=&obj) {
        Game::operator=(obj);
        deck=obj.deck;
    }
    return *this;
}
Blackjack::~Blackjack() {}

void Blackjack::initializeDeck() {
    deck.clear();
    std::vector<std::string> types={"Hearts", "Diamonds","Clubs", "Spades"};
    std::vector<std::string> values={"2","3","4","5","6","7","8","9","10","A","J","Q","K"};
    for (const auto& type: types) {
        for (const auto& value:values ) {
            deck.push_back(type+"_"+value);
        }
    }
}

void Blackjack::shuffleDeck() {
    std::random_device randDeck;
    std::mt19937 g(randDeck());
    std::shuffle(deck.begin(),deck.end(),g);
}

int Blackjack::cardValue(const std::string &card) const {
    std::string value=card.substr(card.find('_')+1);
    if (value=="J" || value=="Q" || value=="K") return 10;
    if (value=="A") return 11;
    return std::stoi(value);
}
int Blackjack::handValue(const std::vector<std::string>& hand) const {
    int value=0;
    int acesCount=0;

    for (const auto& card: hand) {
        int val=cardValue(card);
        value+=val;
        if (val==11) acesCount++;
    }
    while (value>21 && acesCount>0) {
        value-=10;
        acesCount--;
    }
    return value;
}

void Blackjack::showHand(const std::string &owner, const std::vector<std::string> &hand, bool hideCard) const {
    std::cout<<owner<<"'s hand: ";
    if (hideCard && !hand.empty()) {
        std::cout<<"[HIDDEN_CARD] ";
        for (int i=1;i<hand.size();++i) {
            std::cout<<"[ "<<hand[i]<<"] ";
        }
        std::cout<<"\n";
    }
    else {
        for (const auto& card: hand) {
            std::cout<<"[ "<<card<<"] ";
        }
        std::cout<<"(Total: "<<handValue(hand)<<")\n";
    }
}

void Blackjack::playerRound(std::vector<std::string> &playerHand, int &deckIndex,const std::string& playerName) {
    char choice=' ';
    while (handValue(playerHand)<21) {
        std::cout<<"Do you want to Hit (H) or Stand (S)?\n";
        std::cin>>choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (choice=='h'||choice=='H') {
            playerHand.push_back(deck[deckIndex++]);
            showHand(playerName,playerHand,false);
        }
        else if (choice=='S'||choice=='s') break;
        else {
            std::cout<<"Invalid choice! Please enter 'H' or 'S'\n";
        }
    }

}

void Blackjack::winner(Player &player, double bet, int playerTotal, int dealerTotal) {
    if (dealerTotal>21 || playerTotal>dealerTotal) {
        double prize=calculatePrize(bet,2.0);
        player.setBalance(player.getBalance() + prize);
        std::cout<<"You won $"<<prize<<"\n";
    }
    else if (playerTotal<dealerTotal) {
        std::cout<<"You lost! Better luck next time!\n";
    }
    else {
        player.setBalance(player.getBalance() + bet);
        std::cout << "It's a Push! Your bet of $" << bet << " was returned.\n";
    }
}

void Blackjack::play(Player &player) {
    std::cout << "\n=========================================\n";
    std::cout << "          WELCOME TO BLACKJACK           \n";
    std::cout << "=========================================\n";
    std::cout << "Enter your bet (Min: " << getMinBet() << "$):\n";
    double bet = validBet();
    player.placeBet(bet, getMinBet());
    shuffleDeck();
    std::vector<std::string> playerHand={deck[0],deck[1]};
    std::vector<std::string> dealerHand={deck[2],deck[3]};
    int deckIndex=4;
    showHand("Dealer",dealerHand,true);
    showHand(player.getName(),playerHand,false);
    playerRound(playerHand,deckIndex,player.getName());
    int playerTotal=handValue(playerHand);
    if (playerTotal>21) {
        std::cout << "\n❌ Bust! You went over 21. Dealer wins!\n";
        return;
    }
    std::cout<<"Dealer's turn\n";
    showHand("Dealer", dealerHand,false);
    while (handValue(dealerHand)<17) {
        std::cout << "Dealer draws a card...\n";
        dealerHand.push_back(deck[deckIndex++]);
        showHand("Dealer", dealerHand,false);
    }
    winner(player,bet,playerTotal,handValue(dealerHand));
}

void Blackjack::printRules() const {
    std::ifstream file("BlackjackRules.txt");
    if (!file.is_open()) {
        std::cout<<"Welcome to BLackjack! Try your bedt to win\n";
        return;
    }
    std::string line;
    while (std::getline(file,line)) {
        std::cout<<line<<"\n";
    }
    file.close();
}
