#include "LinearInterpolateData.h"


Interpolate::LinearInterpolateData::LinearInterpolateData(InterpolateData mData) : a(mData.a), b(mData.b), time(mData.time), mCurrentVal(mData.a), mCurrentTime(0.0f)
{
}

Interpolate::LinearInterpolateData::~LinearInterpolateData()
{
}

float Interpolate::LinearInterpolateData::Interpolate(float x, float y, float a)
{
	return x + a * (y - x);
}

void Interpolate::LinearInterpolateData::Present(void)
{
	mCurrentTime = 0.0f;
	mCurrentVal = a;
}

void Interpolate::LinearInterpolateData::Update(float mDtMs)
{
	mCurrentTime += mDtMs;
	mCurrentTime = glm::min(mCurrentTime, time);
	mCurrentVal = Interpolate(a, b, mCurrentTime / time);
}

float Interpolate::LinearInterpolateData::GetValue(void)
{
	return mCurrentVal;
}

bool Interpolate::LinearInterpolateData::EndLerp(void)
{
	return mCurrentTime >= time;
}
