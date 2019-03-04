#include "OneDataTransformBase.h"


Random::OneDataTransformBase::OneDataTransformBase(float xOrigin, float xDelta, float xMinTime, float xMaxtime,
	float mRandomValue0, float mRandomValue1, float mRandomValue2) : xOrigin(xOrigin), xDelta(xDelta), xMinTime(xMinTime),
	xMaxtime(xMaxtime), xTimeLocal(0.0f), xStart(0.0f), xEnd(0.0f)
{
	Randomize(mRandomValue0, mRandomValue1, mRandomValue2);
}

Random::OneDataTransformBase::~OneDataTransformBase()
{
}

void Random::OneDataTransformBase::Randomize(float mRandomValue0, float mRandomValue1, float mRandomValue2)
{
	xTimeTransform = xMinTime + (xMaxtime - xMinTime) * mRandomValue0;

	float xMin = xOrigin - xDelta;
	float xMax = xOrigin + xDelta;

	xStart = xEnd;
	xEnd = xMin + (xMax - xMin) * mRandomValue2;

	xCur = xStart;
	xTimeLocal = 0.0f;
}

float Random::OneDataTransformBase::GetCurrentStatus(void)
{
	return xCur;
}
