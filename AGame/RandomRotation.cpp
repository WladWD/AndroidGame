#include "RandomRotation.h"


Random::RandomRotation::RandomRotation(float xOrigin, float xDelta, float xMinTime, float xMaxtime,
	float yOrigin, float yDelta, float yMinTime, float yMaxtime,
	float zOrigin, float zDelta, float zMinTime, float zMaxtime)
{
	mAxis[0] = new OneDataRotation(xOrigin, xDelta, xMinTime * 1000.0f, xMaxtime * 1000.0f, GetRandom_0_1(), GetRandom_0_1(), GetRandom_0_1());
	mAxis[1] = new OneDataRotation(yOrigin, yDelta, yMinTime * 1000.0f, yMaxtime * 1000.0f, GetRandom_0_1(), GetRandom_0_1(), GetRandom_0_1());
	mAxis[2] = new OneDataRotation(zOrigin, zDelta, zMinTime * 1000.0f, zMaxtime * 1000.0f, GetRandom_0_1(), GetRandom_0_1(), GetRandom_0_1());
}

Random::RandomRotation::~RandomRotation()
{
	delete mAxis[0];
	delete mAxis[1];
	delete mAxis[2];
}

void Random::RandomRotation::Update(float mDtMs, float mGtMs)
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

glm::mat4 Random::RandomRotation::GetTransormMatrix(void)
{
	return mResultTransform;
}
