
#include "Model.h"

Model::Model(float k0[5], float k1[5], float k2[5], float alphas[3])
{
	memcpy_s(this->k0, sizeof(this->k0), k0, sizeof(k0));
	memcpy_s(this->k1, sizeof(this->k1), k1, sizeof(k1));
	memcpy_s(this->k2, sizeof(this->k2), k2, sizeof(k2));
	memcpy_s(this->alphas, sizeof(this->alphas), alphas, sizeof(alphas));
}

float Model::PickupRating(const float* K, const Pickup& P)
{
	float result = 0;
	result += K[0] * P.collected_size;
	result += K[1] * SunRating(P);
	result += K[2] * deltaPrimes(P);
	
	bool setteBello = false;
	bool scopa = P.table_size == 0;
	for (int i = 0; !setteBello && i < P.collected_size; ++i)
		if (P.collected[i].getVal() == 7 && P.collected[i].getSuit() == Suit::Suns)
			setteBello = true;

	if (setteBello)
		result += K[3];

	if (scopa)
		result += K[4];

}

const Pickup* Model::Combinations(const Pickup& P, int* sz)
{
	
}

float Model::SunRating(const Pickup& P)
{
	int res = 0;

	for (size_t t = 0; t < P.collected_size; ++t) {
		if (P.collected[t].getSuit() == Suit::Suns)
			++res;
	}

	float result = (float)res;
	result = std::exp(result) + 1;

	return result;

}

float Model::deltaPrimes(const Pickup& P)
{
	int16_t result = 0;
	result += prime_max(P.collected, P.collected_size, Suit::Clubs) - prime_max(P.pile, P.pile_size, Suit::Clubs);
	result += prime_max(P.collected, P.collected_size, Suit::Suns) - prime_max(P.pile, P.pile_size, Suit::Suns);
	result += prime_max(P.collected, P.collected_size, Suit::Swords) - prime_max(P.pile, P.pile_size, Suit::Swords);
	result += prime_max(P.collected, P.collected_size, Suit::Cups) - prime_max(P.pile, P.pile_size, Suit::Cups);
	return static_cast<float>(result);
}

int16_t Model::prime_max(const Card* cards, int sz, Suit suit)
{
	int16_t res = 0;
	for (int i = 0; i < sz; ++i) {
		if (cards[i].getSuit() == suit) {
			int16_t prime_val = cards[i].getPrimesValue();
			if (prime_val > res) res = prime_val;
		}
	}
	return res;
}

float Model::PickupScore(const Pickup& P)
{
	float result = 0;
	result += alphas[0] * PickupRating(k0, P);
	
	int C_of_P_sz;
	const Pickup* C_of_P = Combinations(P, &C_of_P_sz);
	for (int i = 0; i < C_of_P_sz; ++i) {

	}

}
