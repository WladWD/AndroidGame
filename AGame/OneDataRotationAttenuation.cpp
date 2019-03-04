#include "OneDataRotationAttenuation.h"


Random::OneDataRotationAttenuation::OneDataRotationAttenuation(float xOrigin, float xDeltaMax, float xDeltaMin, float xMinTime, float xMaxtime,
	float mRandomValue0, float mRandomValue1, float mRandomValue2, 
	float mAttantionTime) : OneDataTransformBase(xOrigin, xDeltaMax, xMinTime, xMaxtime,
		mRandomValue0, mRandomValue1, mRandomValue2), xDeltaMax(xDeltaMax), xDeltaMin(xDeltaMin), mAttantionTime(mAttantionTime),
	mDeltaAttentionTime(0.0f)
	
	/*xOrigin(xOrigin), xDelta(xDeltaMax), xMinTime(xMinTime),
	xMaxtime(xMaxtime), xTimeLocal(0.0f), xStart(0.0f), xEnd(0.0f), xDeltaMax(xDeltaMax), xDeltaMin(xDeltaMin), mAttantionTime(mAttantionTime),
	mDeltaAttentionTime(0.0f)*/
{
	//Randomize(mRandomValue0, mRandomValue1, mRandomValue2);
}

Random::OneDataRotationAttenuation::~OneDataRotationAttenuation()
{
}

bool Random::OneDataRotationAttenuation::Update(float mDtMs, float mGtMs)
{
	static const float mDiv = 1.0f / 16.0f;

	xTimeLocal += mDtMs;
	mDeltaAttentionTime += mDtMs;

	xDelta = xDelta * glm::pow(0.9f, (mDtMs * mDiv));//xDeltaMax + (xDeltaMin - xDeltaMax) * glm::sin(glm::pow(mDeltaAttentionTime / mAttantionTime, 0.2f) * 1.5707963267948966192313216916398f);

		
		/////glm::pow(glm::sin(glm::pow(mDeltaAttentionTime / mAttantionTime, 0.0001f) * 1.5707963267948966192313216916398f), 0.348f);

	if (xTimeLocal >= xTimeTransform)
	{
		xCur = xEnd;
		return true;
	}

	xCur = xStart + (xEnd - xStart) * (xTimeLocal / xTimeTransform);
	//if (xTimeLocal >= xTimeTransform)
	//	return true;

	return false;
}

/*void Random::OneDataRotationAttenuation::Randomize(float mRandomValue0, float mRandomValue1, float mRandomValue2)
{
	xTimeTransform = xMinTime + (xMaxtime - xMinTime) * mRandomValue0;
	
	float xMin = xOrigin - xDelta;
	float xMax = xOrigin + xDelta;

	//xStart = xMin + (xMax - xMin) * mRandomValue1;
	//xEnd = xStart;//xMin + (xMax - xMin) * mRandomValue2;
	//xStart = xMin + (xMax - xMin) * mRandomValue1;

	xStart = xEnd;
	xEnd = xMin + (xMax - xMin) * mRandomValue2;

	//if (xStart > xEnd)
	//	std::swap(xStart, xEnd);

	xCur = xStart;
	xTimeLocal = 0.0f;
}

float Random::OneDataRotationAttenuation::GetCurrentStatus(void)
{
	return xCur;
}*/
