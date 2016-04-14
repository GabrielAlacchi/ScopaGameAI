
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
	
	int sz1;
	const Pickup* C_of_P = Combinations(P, &sz1);
	for (int i = 0; i < sz1; ++i) {
		const Pickup& P_pr = C_of_P[i];
	    
        float sub_result = PickupRating(k1, P_pr) * Probability(P_pr);        

        float loop_result = alphas[1];
        int sz2;
        const Pickup* C_of_P_pr = Combinations(P_pr, &sz2);
        for (int j = 0; j < sz2; ++j) {
            const Pickup& P_pr2 = C_of_P_pr[j];
            loop_result -= alphas[2] * PickupRating(k2, P_pr2) * Probability(P_pr2);
        }
        
        sub_result *= loop_result;

        result -= sub_result;

	}
    
    return result;
    
}

float Model::Probability(const Pickup& P) {
    int16_t card_val = P.leadingCard->getVal();
    int16_t m = P.counts[card_val];
    int16_t n = P.deck_size;
    int16_t k = P.hand_size;

    //Pr(P) = (n-k)(n-k-1)...(n-m-k+1) / (n(n-1)...(n-m+1)
 
    int16_t numerator;
    int16_t denominator;

    for (int16_t i = 0; i < m; ++i) {
        numerator += n - k - i;
        denominator += n - i;
    }

    return static_cast<float>(numerator) / static_cast<float>(denominator);

}
    
