#include "blackjack.h"

ostream &operator<<(ostream &os, const Card &c) {
        os << "[" << c.rank << "SDHC"[c.suit] << "]";
        return os;
}

int Player::evaluatePoint() const {
        int aceCnt = 0;
        int point = 0;
        for (const Card &card : cards) {
            point += min(card.rank, 10);
            if (card.rank == 1) aceCnt++;
        }
        while (aceCnt > 0 && point < 11) {
            aceCnt--;
            point += 10;
        }
        return point;
}

bool Human:: strategy() const {
    char ans;
    cout << "draw another card? [y/n] " << flush;
    cin >> ans;
    return ans == 'y';
}

void Human:: askBet() {
    cout << name << ", how much would you like to bet? ";
    cin >> bet;
    if(bet > bankroll) {  //代表要跟借錢了
        cout << name <<" Notice! You need to borrow money from the casino if you lose" << endl;
    }
}

bool Meek:: strategy() const { 

    if(evaluatePoint()%2!=0){
        if(seven_club==1){   //如果有梅花7就要抽
        
            return 1;
        }
        return 0;
    }

    else {  //總和是偶數也要抽
        return 1;
    }
}

void Meek:: askBet() {
    bet = pow(2,win_count / 3 + 1);

    if(bet > bankroll) {  //代表要跟借錢了
        cout << name <<" Notice! You need to borrow money from the casino if you lose" << endl;
    }
}


bool Random:: strategy() const {   //<=9:100%
    if(evaluatePoint() <= 9) {
        return 1;
    }
    else if(10 <= evaluatePoint() && evaluatePoint() <= 12) {   //10~12:80%
        //"1110111011"
        int x = rand() % (9 - 0 + 1) + 0;  //0到9隨機選
        if(x == 3 || x == 7){
            return 0;
        }
        return 1;
    }
    else if(13 <= evaluatePoint() && evaluatePoint() <= 15) {   //13~15:70%
        //"1110101011"
        int x = rand() % (9 - 0 + 1) + 0;  //0到9隨機選
        if(x == 3 || x == 5 || x == 7){
            return 0;
        }
        return 1;
    }
    else if(16 <= evaluatePoint() && evaluatePoint() <= 18) {   //16~18:50%
        //"1010101010"
        int x = rand() % (9 - 0 + 1) + 0;  //0到9隨機選
        if(x % 2 != 0){
            return 0;
        }
        return 1;
    }
    else{   //>=19:0%
        return 0;
    }
}
void Random:: askBet(){  //隨機取1到一半的資金
    bet = rand() % ((bankroll/2) - 1 + 1) + 1;

    if(bet > bankroll) {  //代表要跟借錢了
        cout << name <<" Notice! You need to borrow money from the casino if you lose" << endl;
    }
}

 
bool Dealer::strategy() const { return evaluatePoint() < 17; }

 

void Game:: run() {
    int n_card;
    if((players.size()+1)%4==0){
        n_card = (players.size()+1) / 4;
    }
    else{
        n_card = (players.size()+1) / 4 + 1;
    }
    if(make_card == 0){  //第一局進來run要做牌
        cards = Card::makeCard(n_card);
        make_card++;
    }
    if(cards.size()<=(players.size()+1)*5){  //如果已經進行多局了，要判斷剩下的牌是否太少

        cards = Card::makeCard(n_card);  //如果太少要重新製作
    }

    // 要先清空手上的牌
    for (auto &player : players) {
        player->cards.clear();
    }
    dealer.cards.clear();
    // 賭錢
    for (auto &player : players) {
        player->askBet();
    }
    //印出大家各自分別賭多少錢
    cout << "Okay, time for betting!" << endl;
    cout << "-----------------------" << endl;
    for (auto &player : players) {

        cout << player->name << " bet $" << player->bet << endl;
    }
    // 給大家發兩張排
    auto c = cards[cards.size() - 1];   //c
    cards.pop_back();
    dealer.draw(c);
    c = cards[cards.size() - 1];
    cards.pop_back();
    dealer.draw(c);
    //dealer.bankroll = 10000;  //
    cout << "The initial starting cards are:" <<endl;
    cout << "-------------------------------" << endl;
    for (auto &player : players) {
        auto c = cards[cards.size() - 1];
        cards.pop_back();
        player->draw(c);
        c = cards[cards.size() - 1];
        cards.pop_back();
        player->draw(c);
        cout << player->name << "'s cur hand: ";
        int hide = 0;   //是否要隱藏牌 0:隱藏
        player->seven_club = 0;  //初始化沒有梅花7
        for (const Card &card : player->cards) {
            if(hide == 0) {   //要隱藏看不到牌
                cout << "[??]"; 
                hide = 1;
            }
            else {
                cout << card;
                hide = 0;
            }
            //如果有梅花7
            if(card.rank == 7 && card.suit == 3) {
                player->seven_club = 1;
            }
        }
        cout << endl;
    }
    //印出Dealer的牌
    cout << "Dealer's cur hand: ";
    int hide = 0;   //是否要隱藏牌 0:隱藏
    for (const Card &card : dealer.cards) {
        if(hide == 0){
            cout << "[??]";
            hide = 1;
        }
        else {
            cout << card << endl;
            hide = 0;
        }
    }

    for (Player *player : players) {
        cout << player->name << "'s turn:"<< endl;
        cout << "-----------" << endl;
        cout << player->name << "'s cur hand: ";
        for (const Card &card : player->cards) {
            cout << card << " ";
        }
        cout << "(" << player->evaluatePoint() << " points)" << endl;

        int bust = 0;   //是否有爆掉 0:沒有爆掉
        while (player->strategy()) {
            bust = 0;
            auto c = cards[cards.size() - 1];
            cards.pop_back();
            player->draw(c);
            cout << player->name << "'s cur hand: ";
            for (const Card &card : player->cards) {
                cout << card << " ";
            }
            cout << "(" << player->evaluatePoint() << " points)"<< endl;
            if (player->evaluatePoint() > 21) {
                player->bust();
                player->bankroll -= player->bet; //初始資金要扣掉(lose)
                dealer.bankroll += player->bet;  //莊家的資金增加
                bust = 1;
                break;
            }
        }
        if(!bust){
            cout << player->name << " chooses to stay." << endl;
        }

    }
    //莊家部分
    cout << "Dealer's turn:"<< endl;
    cout << "-----------" << endl;
    cout << "Dealer's cur hand: ";
    for (const Card &card : dealer.cards) {
        cout << card << " ";
    }
    cout << "(" << dealer.evaluatePoint() << " points)" << endl;
    int bust = 0;   //是否有爆掉 0:沒有爆掉
    while (dealer.strategy()) {
            auto c = cards[cards.size() - 1];
            cards.pop_back();
            dealer.draw(c);
            cout << "Dealer's cur hand: ";
            for (const Card &card : dealer.cards) {
                cout << card << " ";
            }
            cout << "(" << dealer.evaluatePoint() << " points)"<< endl;
            if (dealer.evaluatePoint() > 21) {  //莊家爆掉
                bust = 1;
                dealer.bust();
                break;
            }
    }
    if(bust == 0){
        cout << "Dealer chooses to stay." << endl;
    }

    //開始紀錄誰輸誰贏
    cout << "Let't see how it turned out:" << endl;
    cout << "----------------------------" << endl;
    for (Player *player : players) {
        //如果dealer爆掉
        if(dealer.evaluatePoint()>21){
            player->win();  //給每個人都賠錢
            if(player->evaluatePoint()<=21) {
                cout << "Yowzah! " << player->name << " wins $" << player->bet << endl;
            }
            else {
                cout << player->name << " and Dealer are both busted!" << endl;
                player->win_count = 0;
            }
            dealer.bankroll-=player->bet;
        }
        else if(player->evaluatePoint() > 21){  //玩家爆掉
            cout << "Ouch! " << player->name << " loses $" << player->bet << endl;
            player->win_count = 0;
        }
        else if(player->evaluatePoint()>dealer.evaluatePoint()) {
            player->win();
            cout << "Yowzah! " << player->name << " wins $" << player->bet << endl;
            dealer.bankroll-=player->bet;
        }
        else if(player->evaluatePoint()<=dealer.evaluatePoint()) {
            player->lose();
            cout << "Ouch! " << player->name << " loses $" << player->bet << endl;
            dealer.bankroll+=player->bet;
        }
    }

    //開始總結結果
    cout << "The standings so far:" << endl;
    cout << "---------------------" << endl;
    for (Player *player : players) {
        cout << player->name << " $ " << player->bankroll << endl;
    }
    cout << "Dealer $ " << dealer.bankroll << endl;

    //印出賭場目前借貸狀況，及資本額剩餘多少
    cout << "******************************" << endl;
    cout << "Casino's current leding status" << endl;
    cout << "------------------------------" << endl;
    int casino_bankroll = 100000000;  //賭場資金
    for (Player *player : players) {
        if(player->bankroll < 0){
            cout << player->name << " currently borrowed $ " << 0 - player->bankroll << endl;
            casino_bankroll -= (0 - player->bankroll);
        }
        else{
            cout << player->name << " currently not borrowing" << endl;
        }
    }
    cout << "Casino's current capital $ " << casino_bankroll << endl;

}
