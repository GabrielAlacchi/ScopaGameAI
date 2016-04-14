
#include "Card.h"


#include <stdint.h>
#include <memory.h>

class Model {
//Model depends on a matrix of 3 rows with 5 parameters
//3 alpha values

	float alphas[3];
	float k0[5];
	float k1[5];
	float k2[5];

	float PickupRating(const float* K, const Pickup& P);
	const Pickup* Combinations(const Pickup& P, int* sz);
	static float SunRating(const Pickup& P);
	static float deltaPrimes(const Pickup& P);
	static int16_t prime_max(const Card* cards, int sz, Suit suit);
    static float Probability(const Pickup& P);

public:

	Model(float k0[5], float k1[5], float k2[5], float alphas[3]);

	float PickupScore(const Pickup& P);

};

