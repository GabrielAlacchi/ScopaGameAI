
#include "Model.h"

Model::Model(float k0[5], float k1[5], float k2[5], float alphas[3])
{
	memcpy_s(this->k0, sizeof(this->k0), k0, sizeof(k0));
	memcpy_s(this->k1, sizeof(this->k1), k1, sizeof(k1));
	memcpy_s(this->k2, sizeof(this->k2), k2, sizeof(k2));
	memcpy_s(this->alphas, sizeof(this->alphas), alphas, sizeof(alphas));
}
