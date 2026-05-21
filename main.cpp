
#include <memory>
#include <iostream>
#include <limits>
#include "Game.h"
#include "Blackjack.h"
#include "Roulette.h"
#include "Slots.h"
#include "Player.h"
#include "CasinoHistory.h"
#include "ctime"
#include <cstdlib>
class GameFactory {
public:
    static std::unique_ptr<Game> createGame(int choice) {
        if (choice==1) return std::make_unique<Blackjack>();
        if (choice==2) return std::make_unique<Roulette>();
        if (choice==3) return std::make_unique<Slots>();
        return nullptr;
    }
};
void showHistory() {

    std::ifstream file("casino_history.txt");
    if (!file.is_open()) {
        std::cout<<"No history found yet\n";
        return;
    }
    std::string line;
    while (std::getline(file,line)) {
        std::cout<<line<<"\n";
    }
    file.close();
}
class Menu {
private:
    Player player;
    CasinoHistory<Transaction> log;
    std::weak_ptr<Game> last;
    Menu(): player("player",500.0,0) {
        log.LoadProgress("casino_history.txt");
    }
public:
    Menu(const Menu& obj)=delete;
    Menu& operator=(const Menu& obj)=delete;

    static Menu& getInstance() {
        static Menu instance;
        return instance;
    }

    void init() {
        std::string name;
        std::string tempAge;
        int age=0;
        std::cout<<"Name: ";
        std::getline(std::cin, name);
        std::cout<<"\n";
        while (true) {
            std::cout<<"Age: ";
            std::cin>>tempAge;
            std::cout<<"\n";
            bool valid=true;
            for (char c : tempAge) {
                if (!std::isdigit(c)) {
                    valid=false; break;
                }
            }
            if (valid && !tempAge.empty()) {
                age=std::stoi(tempAge);
                if (age>0)
                    break;
            }
            std::cout<<"Enter your age: \n";
        }
        if (age<18) {
            std::cout<<"Minimum age of 18 is required!\n App will close\n";
            std::exit(0);
        }
        player.setName(name);
        player.setAge(age);
        player.setBalance(500.0);
        std::cout<<"Account created! You recerived $500\n";
    }
   void menu() {
        std::string choice="";
        while (choice!="5") {
            std::cout<<"\n";
            std::cout << "(Player: " << player.getName() << " | Age: " << player.getAge() << " | Balance: $" << player.getBalance() << ")\n";
            std::cout << "1. Play Blackjack\n";
            std::cout << "2. Play Roulette\n";
            std::cout << "3. Play Slots\n";
            std::cout<<"4. View income history\n";
            std::cout << "5. Exit & Save\n";

            std::cin>>choice;
            if (choice=="1" || choice=="2" || choice=="3") {
                int choiceInt=std::stoi(choice);
                std::unique_ptr<Game> game=GameFactory::createGame(choiceInt);
                if (game) {
                    std::shared_ptr<Game> session=std::move(game);
                    last=session;

                    std::string secondChoice="";
                    while (secondChoice!="3") {
                        std::cout<<"\n";
                        std::cout << "(Player: " << player.getName() << " | Age: " << player.getAge() << " | Balance: $" << player.getBalance() << ")\n";
                        std::cout << "1. Print Rules\n";
                        std::cout << "2. Play\n";
                        std::cout << "3. back to Menu\n";
                        std::cin>>secondChoice;

                        if (secondChoice=="1") session->printRules();
                        else if (secondChoice=="2") session->play(player,log);
                        else if (secondChoice=="3") break;
                        else std::cout<<"Invalid choice!";
                    }
                    if (auto sharedGame=last.lock()) {
                        std::cout<<"Session over for "<<sharedGame->getName()<<"\n";
                    }
                }
            }
            else if (choice=="4") {
                showHistory();
            }
            else if (choice=="5") {
                std::cout<<"Bye\n";
                log.SaveProgress("casino_history.txt");
            }
            else std::cout <<"Invalid option\n";
        }
    }

};

int main() {
    std::srand(std::time(0));

    Menu::getInstance().init();
    Menu::getInstance().menu();
}

