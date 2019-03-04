#include "OneDataRotation.h"


Random::OneDataRotation::OneDataRotation(float xOrigin, float xDelta, float xMinTime, float xMaxtime,
	float mRandomValue0, float mRandomValue1, float mRandomValue2) : OneDataTransformBase(xOrigin, xDelta, xMinTime, xMaxtime,
		mRandomValue0, mRandomValue1, mRandomValue2)
{
}

Random::OneDataRotation::~OneDataRotation()
{
}

bool Random::OneDataRotation::Update(float mDtMs, float mGtMs)
{
	xTimeLocal += mDtMs;

	if (xTimeLocal >= xTimeTransform) 
	{
		xCur = xEnd;
		return true;
	}

	xCur = xStart + (xEnd - xStart) * glm::sin( glm::pow((xTimeLocal / xTimeTransform), 1.6f) * 1.5707963267948966192313216916398f);
	//if (xTimeLocal >= xTimeTransform)
	//	return true;

	return false;
}
/*
void Random::OneDataRotation::Randomize(float mRandomValue0, float mRandomValue1, float mRandomValue2)
{
	xTimeTransform = xMinTime + (xMaxtime - xMinTime) * mRandomValue0;

	float xMin = xOrigin - xDelta;
	float xMax = xOrigin + xDelta;

	xStart = xEnd;
	xEnd = xMin + (xMax - xMin) * mRandomValue2;

	xCur = xStart;
	xTimeLocal = 0.0f;
}

float Random::OneDataRotation::GetCurrentStatus(void)
{
	return xCur;
}
*/