#include "RandomNormal.h"


Engine::RandomNormal::RandomNormal()
{
	mre = new std::default_random_engine(time(0));
	mRD = new std::uniform_real_distribution<double>();
	mRDInt = new std::uniform_int_distribution<int>();
}

Engine::RandomNormal::~RandomNormal()
{
	delete mre;
	delete mRD;
	delete mRDInt;
}

double Engine::RandomNormal::GetNextDouble(void)
{
	double rn = glm::clamp((*mRD)(*mre), 0.0, 1.0);
	return rn;
}

int32_t Engine::RandomNormal::GetNextInteger(void)
{
	int32_t rn = (*mRDInt)(*mre);
	return rn;
}

int Engine::RandomNormal::GetNextDoubleIntGen(double mVer)
{
	int dgt = (*mRDInt)(*mre);
	int mv = ceil(1.0 / mVer); //* mRDInt->max();
	int val = (1 + abs((*mRDInt)(*mre) ^ dgt));
	if (!(dgt % mv))
		return val > 1234567 ? 127 : val;// dgt * ((*mRDInt)(*mre) & 1 ? -1 : 1);
	else
		return 0;
}
