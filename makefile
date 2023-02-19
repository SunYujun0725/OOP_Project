all: main.cpp blackjack.cpp
	g++ -g main.cpp blackjack.cpp -o oop_hw6.out
	
clean: oop_hw6.out
	rm -rf oop_hw6.out
