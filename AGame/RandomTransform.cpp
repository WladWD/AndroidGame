#include "RandomTransform.h"


Random::RandomTransform::RandomTransform()
{
	mre = new std::default_random_engine(time(0));
	mRD = new std::uniform_real_distribution<double>();

	mResultTransform = glm::mat4(1.0f);
}

Random::RandomTransform::~RandomTransform()
{
	delete mre;
	delete mRD;
}

double Random::RandomTransform::GetRandom_0_1(void)
{
	double rn = glm::clamp((*mRD)(*mre), 0.0, 1.0);
	return rn;
}