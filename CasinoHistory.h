#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
struct Transaction {
    std::string gameName;
    double betAmount;
    double wonAmount;

    friend std::ostream& operator<<(std::ostream& out, const Transaction& t) {
        out<<t.gameName<<" "<<t.betAmount<<" "<<t.wonAmount;
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Transaction& t) {
        in >> t.gameName >> t.betAmount >> t.wonAmount;
        return in;
    }
};

template <typename T>
class CasinoHistory {
private:
    std::vector<T> data;
public:
    CasinoHistory()=default;
    CasinoHistory(const CasinoHistory& obj) : data(obj.data){}
    CasinoHistory& operator=(const CasinoHistory& obj) {
        if (this!=&obj) data=obj.data;
        return *this;
    }

    ~CasinoHistory()=default;
    void addEvvent(const T& evvent) {
        data.push_back(evvent);
    }
    void SaveProgress(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr<<"Error at file openning\n";
            return;
        }
        for (const auto& evvent:data) {
            file<<evvent<<"\n";
        }
        file.close();
    }

    void LoadProgress(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return;
        }
        data.clear();
        T tempData;
        while (file>>tempData){
            data.push_back(tempData);
        }
        file.close();
    }
    void printHistory() const {
        if (data.empty()) {
            return;
        }
        double bet=0;
        double won=0;
        for (int i=0;i<data.size();++i) {
            std::cout<<"Round "<<i+1<<" Game: "<<data[i].gameName;
            std::cout<<" | Bet: $"<<data[i].betAmount<<" | Won: $"<<data[i].wonAmount<<"\n";
            bet+=data[i].betAmount;
            won+=data[i].wonAmount;
        }
        std::cout<<"-------------------------------------------------------\n";
        std::cout<<"Total player bets: $"<<bet<<"\n";
        std::cout<<"Total player winnings: $"<<won<<"\n";
        std::cout<<"House profit: $ "<<(bet-won)<<"\n";
        std::cout<<"-------------------------------------------------------\n";
    }
};