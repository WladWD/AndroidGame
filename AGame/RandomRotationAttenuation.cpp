#include "RandomRotationAttenuation.h"

Random::RandomRotationAttenuation::RandomRotationAttenuation(float xOrigin, float xDeltaMax, float xDeltaMin, float xMinTime, float xMaxtime, float xAttentionTime,
	float yOrigin, float yDeltaMax, float yDeltaMin, float yMinTime, float yMaxtime, float yAttentionTime,
	float zOrigin, float zDeltaMax, float zDeltaMin, float zMinTime, float zMaxtime, float zAttentionTime)
{
	mAxis[0] = new OneDataRotationAttenuation(xOrigin, xDeltaMax, xDeltaMin, xMinTime * 1000.0f, xMaxtime * 1000.0f, GetRandom_0_1(), GetRandom_0_1(), GetRandom_0_1(), xAttentionTime * 1000.0f);
	mAxis[1] = new OneDataRotationAttenuation(yOrigin, yDeltaMax, yDeltaMin, yMinTime * 1000.0f, yMaxtime * 1000.0f, GetRandom_0_1(), GetRandom_0_1(), GetRandom_0_1(), yAttentionTime * 1000.0f);
	mAxis[2] = new OneDataRotationAttenuation(zOrigin, zDeltaMax, zDeltaMin, zMinTime * 1000.0f, zMaxtime * 1000.0f, GetRandom_0_1(), GetRandom_0_1(), GetRandom_0_1(), zAttentionTime * 1000.0f);
}

Random::RandomRotationAttenuation::~RandomRotationAttenuation()
{
	delete mAxis[0];
	delete mAxis[1];
	delete mAxis[2];
}

void Random::RandomRotationAttenuation::Update(float mDtMs, float mGtMs)
{
	mResultTransform = glm::mat4(1.0f);
	glm::vec3 mVector[] = 
	{
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	};

	for (register int32_t i = 0; i < 3; i++) 
	{
		if (mAxis[i]->Update(mDtMs, mGtMs))
				mAxis[i]->Randomize(GetRandom_0_1(), GetRandom_0_1(), GetRandom_0_1());

		mResultTransform *= glm::rotate(glm::mat4(1.0f), mAxis[i]->GetCurrentStatus(), mVector[i]);
	}
}

glm::mat4 Random::RandomRotationAttenuation::GetTransormMatrix(void)
{
	return mResultTransform;
}
