#include "MHeder.h"

#pragma once
namespace Interpolate
{
	struct InterpolateData
	{
		float a, b, time;
	};

	class LinearInterpolateData
	{
		//////////////////////////////////////////////////////////////////////////
		float a, b, time;
		float mCurrentVal, mCurrentTime;
		//////////////////////////////////////////////////////////////////////////
		float Interpolate(float x, float y, float a);
	public:
		LinearInterpolateData(InterpolateData mData);
		~LinearInterpolateData();
		//////////////////////////////////////////////////////////////////////////
		void Present(void);
		void Update(float mDtMs);
		float GetValue(void);
		bool EndLerp(void);
		//////////////////////////////////////////////////////////////////////////
	};
}

