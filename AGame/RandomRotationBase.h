#include "RandomTransform.h"
#include "OneDataRotationAttenuation.h"

#pragma once
namespace Random
{
	class RandomRotationBase : public RandomTransform
	{
		///////////////////////////////////////////////////////////////
	public:
		RandomRotationBase(void);
		virtual ~RandomRotationBase();
		///////////////////////////////////////////////////////////////
		virtual void Update(float mDtMs, float mGtMs) = 0;
		///////////////////////////////////////////////////////////////
		virtual glm::mat4 GetTransormMatrix(void) = 0;
	};
}
