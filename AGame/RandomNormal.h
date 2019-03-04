#include "MHeder.h"
#include <random>
#include <time.h>

#pragma once
namespace Engine
{
	class RandomNormal
	{
		std::default_random_engine *mre;
		std::uniform_real_distribution<double> *mRD;
		std::uniform_int_distribution<int> *mRDInt;
		////////////////////////////////////////////////////////////////
	public:
		RandomNormal(void);
		~RandomNormal();
		////////////////////////////////////////////////////////////////
		double GetNextDouble(void);
		int32_t GetNextInteger(void);
		int GetNextDoubleIntGen(double mVer);
		////////////////////////////////////////////////////////////////
	};
}

