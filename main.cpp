#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>
#include <cmath>
#include "blackjack.h"
using namespace std;

int main() {
    
    srand(time(NULL));
    Game game;
    int number,money;
    string player_name;
    cout << "請輸入有幾名玩家(不包含莊家):";
    cin >> number;
    string player_type;
    Human *h = new Human;
    Meek *m = new Meek;
    Random *r = new Random;
    Dealer *d = new Dealer;
    for(int i=0;i<number;i++){
        h = new Human;
        m = new Meek;
        r = new Random;
        cout << "請輸入第" << i+1 << "個玩家屬於哪一類:";
        cin >> player_type;
        if(player_type == "Human"){
            cout << "請輸入人類名字:";
            cin >> player_name;
            h->name = player_name;
            cout << "請輸入人類有多少初始資金:";
            cin >> money;
            h->bankroll = money;
            game.joinPlayer(h);
        }
        else if(player_type == "Meek"){
            cout << "請輸入computer Meek的名字:";
            cin >> player_name;
            m->name = player_name;
            cout << "請輸入Meek有多少初始資金:";
            cin >> money;
            m->bankroll=money;
            game.joinPlayer(m);
        }
        else if(player_type == "Random"){
            cout << "請輸入computer Random的名字:";
            cin >> player_name;
            r->name = player_name;
            cout << "請輸入Random有多少初始資金:";
            cin >> money;
            r->bankroll=money;
            game.joinPlayer(r);
        }
    }
    
    string nextGame;
    do {
        game.run();
        cout << "wanna player another game? [y/n]";
        cin >> nextGame;
    } while (nextGame == "y");
 
    delete h;
    delete m;
    delete r;
 
    return 0;
}
