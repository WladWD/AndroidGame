#include "RandomTransform.h"
#include "RandomRotationBase.h"
#include "OneDataRotation.h"

#pragma once
namespace Random
{
	class RandomRotation : public RandomRotationBase
	{
		///////////////////////////////////////////////////////////////
		OneDataRotation *mAxis[3];
		///////////////////////////////////////////////////////////////
	public:
		RandomRotation(float xOrigin, float xDelta, float xMinTime, float xMaxtime,
			float yOrigin, float yDelta, float yMinTime, float yMaxtime,
			float zOrigin, float zDelta, float zMinTime, float zMaxtime);
		~RandomRotation();
		///////////////////////////////////////////////////////////////
		void Update(float mDtMs, float mGtMs);
		///////////////////////////////////////////////////////////////
		glm::mat4 GetTransormMatrix(void);
	};
}
