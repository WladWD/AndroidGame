#include "TimerHighResolution.h"


Timer::TimerHighResolution::TimerHighResolution() : mGlobalTime(0.0f), mDelataTime(0.0f), mSleep(false)
{
	mLast = mCurrent = std::chrono::high_resolution_clock::now();
}

Timer::TimerHighResolution::~TimerHighResolution()
{
}

float Timer::TimerHighResolution::GetGlobalTime(void)
{
	return mGlobalTime;
}

float Timer::TimerHighResolution::GetDelataTime(void)
{
	return mDelataTime;
}

void Timer::TimerHighResolution::Tick(void)
{
	static const float mDiv = 1.0f / 1000.0f;
	if (!mSleep)
	{
		mLast = mCurrent;
		mCurrent = std::chrono::high_resolution_clock::now();


		mDelataTime =
			static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(mCurrent - mLast).count()) * mDiv;

		mDelataTime = mDelataTime > 0.0f ? mDelataTime : 0.0f;

		mGlobalTime += mDelataTime;
	}
	else mDelataTime = 0.0f;
}

void Timer::TimerHighResolution::Resume(void)
{
	if (mSleep)
	{
		mSleep = false;
		mLast = mCurrent = std::chrono::high_resolution_clock::now();
	}
}

void Timer::TimerHighResolution::Pause(void)
{
	if (!mSleep)
		mSleep = true;
}
