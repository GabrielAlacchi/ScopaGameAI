
#include <stdint.h>
#include <exception>
#include <random>
#include <ctime>

enum Suit {
	Clubs,
	Swords,
	Suns,
	Cups
};

class Card {
private:
	int16_t val;
	Suit suit;
public:
	Card(int16_t val, Suit suit);
	const int16_t getVal();
	const Suit getSuit();
	static void getShuffledDeck(Card input[40]);
};

struct Pickup {
	Card* hand;
	int16_t hand_size;
	Card* table;
	int16_t table_size;
	Pickup(Card* hand, int16_t hand_size, Card* table, int16_t table_size) 
		: hand(hand), hand_size(hand_size), table(table), table_size(table_size)
	{}
};

