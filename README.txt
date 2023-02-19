README

姓名: 孫渝鈞
學號: 409510049
e-mail: yujun91725@gmail.com

完成項目:
Blackjack:
1.blackjack.cpp: C++寫一個21點的遊戲，該遊戲就是每個玩家都先詢問要賭多少錢（莊家不用賭錢），然後給每個人發兩張牌（莊家也要），接著從第一位開始詢問是否要再加牌，如果加牌後超過21點就爆掉，但越接近21點越好，接下來再跟莊家比看誰的點數比較接近21點，若莊家比較接近那玩家就要把賭金給莊家，反之就要把賭金給玩家，且若莊家超過21點的話就要給所有人陪賭金。
2.blackjack.h: blackjack.cpp的標頭檔，用來連接main.cpp及blackjack.cpp檔，裡面還包含所有class的參數及函式宣告。
3.makefile: 將main.cpp及blackjack.cpp編譯成oop_hw6.out檔的指令。
4.main.cpp: 21點遊戲的主函式，詢問有多少玩家參與，各個玩家的名字及初始資金是多少，並將各個玩家加入遊戲內。
5.範例程式執行結果圖: 用來提示如何輸入玩家資料及輸出應該為何的範例圖。


遊戲進行方式：
首先先詢問玩家人數有多少人（不包含莊家），皆著輸入玩家的屬性(Human\Meek\Random)、玩家名字、玩家的初始資金。接著開始將每位玩家加入遊戲中，首先我第一局開始前都會製作幾副牌，幾副牌的數量取決於參加遊戲的玩家加莊家的人數，若超過4人則就要在多加一副牌，8人則需要兩副牌，以此類推。之後就判斷上一局結束後剩下的牌是否有大於玩家人數*5張牌，沒有的話就shuffle牌再重新做一次牌，注意每局開始前都要清空上一局所有人手上的牌。接著開始詢問要賭多少錢，所以這邊我在Player的class寫了一個virtual的askbet函式，因為每種屬性的玩家賭金決定都不一樣，所以就可以照不同屬性的玩家去決定賭金是多少，Human的賭金是直接由玩家輸入式多少，而Meek則是一開始為$2如果贏3場則翻倍（ex:贏3場後每場都是$4，贏6場後沒場都是$8，以此類推），如果爆掉就歸0，所以這邊我直接在player的class寫一個win_count變數來紀錄目前連贏幾場了，random是直接random 1~總資金的一半的錢。接下來給大家發兩張牌，這裡要注意每發一次都要注意牌數量要減掉。接下來用迴圈開始決定要不要加牌，這裡我在Player的class寫了一個virtual的strategy函式，因為每種屬性的玩家決定要不要抽的策略是不一樣的，像是Human就是直接由玩家那方輸入(y/n)來決定要不要繼續抽，而Meek則是如果總點數是偶數就抽，奇數就不抽，但如果有梅花7的牌也抽，這裡我直接在player的class寫的一個seven_club的變數紀錄有沒有梅花7(有的話seven_club=1)，而random是由點數大小去做有機率的random，points<=9的時候100%抽、10<=point<=12時80%抽、13<=point<=15時70%抽、16<=point<=18時50%抽，19<=point時0%抽，而機率的調整方法如下：假設要80%的機率抽，那我就自己設一串數字“110111011“然後random 0~9的數字，如果random出來是3那就代表是數字中第4個數字(從0開始算)的值(1->要抽)，以此類推，而莊家的策略是點數小於17就抽。如果加牌後爆掉那麼該玩家的賭金就要給莊家，自己的初始資金當然也會減少，並離開迴圈。接下來在開始將每一位玩家與莊家比點數大小，如果比莊家大那麼就可以拿到與賭金相同的金額，如果沒有那麼就要將賭金給莊家，但如果莊家超過21點的話要賠每個人賭金，但如果莊家與玩家都超過21點的話，那麼雙方都不會賠到賭金，因為一開始玩家爆掉的時候會將賭金給莊家，但最後莊家也爆掉的話他也會賠賭金給每一個人，所以正負扣加錢後，雙方都不會賠到錢。
P.s計算點數方式：因為Ａ可以當作1點或11點，所以如果我當前point小於10那麼A就當做1點如果當前point大於10那麼A就當作1點。
P.s最後印出玩家輸贏的部分，如果莊家爆掉，玩家也爆掉的話不會有任何一方贏，會印出“玩家名字 and Dealer are both busted!”

各個class及main功能：
Card:存每張牌的rank、suit，及製作牌、洗牌的功能，另外還有operator overloading "<<"用來印出牌的樣子(ex:[1H])
Player:存每個玩家的名字、賭金、資金、有沒有梅花7、贏了幾次、virtual win(贏的人資金可以加上賭金、win_count++)、virtual lose(輸的人資金要扣掉賭金)、virtual bust(印出該玩家已經爆)、virtual askBet(詢問賭金)、virtual strategy(策略)、draw(抽牌)、evaluatePoint(計算點數)
Human繼承Player，並有自己的askBet(詢問賭金)、virtual strategy(策略)
Meek繼承Player，並有自己的askBet(詢問賭金)、virtual strategy(策略)
Random繼承Player，並有自己的askBet(詢問賭金)、virtual strategy(策略)
Dealer繼承Player，並有virtual strategy(策略)
Game: joinplayer(加入玩家)、run(整個遊戲的過程都在這邊)
Main:詢問有多少玩家參與，各個玩家的名字及初始資金是多少，並將各個玩家加入遊戲內，每一局結束後還要詢問是不是還要再一局。

Bonus:
1.如果玩家的賭金大於資本金的話會體醒玩家，如果這局輸的話就要跟賭場借錢。
2.多了一個賭場，賭場有一個原先資金預設為一億，是用來借玩家錢的，因爲每位玩家可以賭比本身資金還大的賭金，所以如果玩家或莊家玩到資金是負的代表要跟賭場借錢了，最後每局結束會印出所有玩家包含莊家與賭場的借貸關係（如果沒有借錢會印出玩家目前沒有借錢），而且玩家每贏一次都要還賭場最大可以還的金額，也就是說有多少還多少。除此之外還會印出，賭場目前還有多少資金可以借。



Reference:
1.c++(operator overloading):http://wccclab.cs.nchu.edu.tw/www/images/VCplusplus/ch6.pdf
			    https://www.csie.ntu.edu.tw/~r95116/CA200/slide/C3_Overloading.pdf
			    https://openhome.cc/Gossip/CppGossip/OverloadOperator.html
2.c++(有機率random):https://www.geeksforgeeks.org/generate-0-1-25-75-probability/
3.c++(virtual function):https://shengyu7697.github.io/cpp-virtual/
			https://vimsky.com/zh-tw/examples/usage/virtual-function-cpp.html



