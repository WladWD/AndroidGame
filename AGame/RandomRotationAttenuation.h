#include "RandomTransform.h"
#include "RandomRotationBase.h"

#pragma once
namespace Random
{
	class RandomRotationAttenuation : public RandomRotationBase
	{
		///////////////////////////////////////////////////////////////
		OneDataRotationAttenuation *mAxis[3];
		///////////////////////////////////////////////////////////////
	public:
		RandomRotationAttenuation(float xOrigin, float xDeltaMax, float xDeltaMin, float xMinTime, float xMaxtime, float xAttentionTime,
			float yOrigin, float yDeltaMax, float yDeltaMin, float yMinTime, float yMaxtime, float yAttentionTime,
			float zOrigin, float zDeltaMax, float zDeltaMin, float zMinTime, float zMaxtime, float zAttentionTime);
		~RandomRotationAttenuation();
		///////////////////////////////////////////////////////////////
		void Update(float mDtMs, float mGtMs);
		///////////////////////////////////////////////////////////////
		glm::mat4 GetTransormMatrix(void);
	};
}
