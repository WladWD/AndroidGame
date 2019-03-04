#include "BarrierSetBase.h"


Barrier::BarrierSetBase::BarrierSetBase(float fStep, float fHeight, Camera::MCamera *cCamera, GameEngine::GlobalMove *mGloablMove) : fStep(fStep), fHeight(fHeight), cCamera(cCamera),
	mGloablMove(mGloablMove)
{
}

Barrier::BarrierSetBase::~BarrierSetBase()
{
}
