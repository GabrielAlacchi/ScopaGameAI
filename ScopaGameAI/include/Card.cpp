
#include "Card.h"

Card::Card(int16_t val, Suit suit) 
	: val(val), suit(suit)
{ 
	if (val < 1 || val > 10)
		throw std::exception("Invalid card value, pick a value between 1 and 10");
}

const int16_t Card::getVal() const
{
	return this->val;
}

const Suit Card::getSuit() const
{
	return this->suit;
}

const int16_t Card::getPrimesValue() const
{
	// 8, 9, 10 ==> 10
	// 7 ==> 21
	// 6 ==> 18
	// 1 ==> 16
	// 5,4,3,2 ==> 15,14,13,12

	if (val == 1) return 16;
	if (val > 5) return 3 * val;
	
	return val + 10;

}

void Card::getShuffledDeck(Card input[40])
{
	for (size_t t = 0; t < 40; ++t) {
		Suit st = Suit::Clubs;
		switch (t % 4) {
		case 0:
			st = Suit::Clubs;
			break;
		case 1:
			st = Suit::Cups;
			break;
		case 2:
			st = Suit::Suns;
			break;
		case 3:
			st = Suit::Swords;
			break;
		}
		input[t] = Card(t % 10 + 1, st);
	}

	time_t t;
	time(&t);
	srand(static_cast<unsigned int>(t));

	size_t i1, i2;
	for (size_t t = 0; t < 5000; ++t) {
		int i1 = abs(rand() % 40);
		int i2 = abs(rand() % 40);

		if (i1 != i2) {
			std::swap(input[i1], input[i2]);
		}

	}

}
