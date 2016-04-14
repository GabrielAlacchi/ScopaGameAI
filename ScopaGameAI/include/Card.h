
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
	const int16_t getVal() const;
	const Suit getSuit() const;
	const int16_t getPrimesValue() const;
	static void getShuffledDeck(Card input[40]);
};

struct Pickup {
	Card* collected;
	int16_t collected_size;
	Card* hand;
	int16_t hand_size;
	Card* table;
	int16_t table_size;
	Card* Deck;
	int16_t deck_size;
	Card* pile;
	int16_t pile_size;
};

