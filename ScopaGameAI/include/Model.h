
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

public:

	Model(float k0[5], float k1[5], float k2[5], float alphas[3]);

	float Score(const Pickup P);

};

