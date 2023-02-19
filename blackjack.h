#ifndef BLACKJACK_H
#define BLACKJACK_H
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
class Card
{
    friend ostream &operator<<(ostream &os, const Card &c);

public:
    Card(int rank, int suit) : rank(rank), suit(suit) {}
    int rank;
    int suit; //花色
    // makeCard n: 幾副牌
    static vector<Card> makeCard(const int n)
    {
        vector<Card> v;
        for (int k = 0; k < n; k++)
        {
            for (int i = 1; i < 14; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    v.__emplace_back(Card(i, j)); //系上工作站是emplace_back 繳交之前要改
                }
            }
        }
        // 洗牌
        for (int i = 0; i < 52 * n / 2; i++)
        {
            int a = rand() % v.size(), b = rand() % v.size();
            std::swap(v[a], v[b]);
        }
        return v;
    }
};

class Player
{
public:
    virtual ~Player() {}
    string name;
    int bankroll;
    int bet;
    int seven_club; //是0的話代表沒有梅花七
    int win_count;  //紀錄連續贏了幾次
    vector<Card> cards;
    // strategy return true if player wanna draw a card
    virtual void win() {
        bankroll += bet;
        win_count++;
    };
    virtual void lose() { bankroll -= bet; };
    virtual void bust() { cout << name << " busted at " << evaluatePoint() << "!\n"; }
    virtual void askBet() {}
    virtual bool strategy() const = 0;
    void draw(const Card c) { cards.__emplace_back(c); } //系上工作站emplace_back 繳交之前要改
    int evaluatePoint() const;
};

class Human : public Player
{
public:
    Human(){};
    bool strategy() const;
    void askBet();
};

class Meek : public Player
{
public:
    Meek() { seven_club = 0; }
    bool strategy() const;
    void askBet();
};

class Random : public Player
{
public:
    Random() {}
    bool strategy() const;
    void askBet();
};

class Dealer : public Player
{
public:
    Dealer() { name = "Dealer"; }
    bool strategy() const;
};


class Game
{
    vector<Player *> players;
    Dealer dealer;
    int make_card; //製作牌
    
public:
    vector<Card> cards;
    Game()
    {
        dealer.bankroll = 10000;
        make_card = 0;
        for (auto &player : players) {
            player->win_count = 0;
            player->seven_club = 0;
        }
    }
    void joinPlayer(Player *p) { players.__emplace_back(p); } //系上工作站emplace_back 繳交之前要改

    void run();
};

#endif
