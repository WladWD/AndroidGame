#include "PipeDrawControl.h"



DrawPipe::PipeDrawControl::PipeDrawControl(Resource::ResourceBase *resourceLoad, Resource::TextureLoad *textureLoad, Resource::MapResource *mMapResource, Camera::MCamera *cCamera,
	float fOffset, float fRadius, uint32_t V_Count, uint32_t U_Count,
	float fFogStart, float fFogRadius, const float *fFogColor, float fCylinderHeight, float fMoveSpeed, float fCookieMinYOffset,
	float mAngle, float fZOffset, float mStepH, int32_t mMinCount, int32_t mMaxCount, int32_t mSectorsCount, float mRotateVelCollect, float mCookieZOffset, Score::Score *mScore) : cCamera(cCamera),
	mDrawPipe(0), mIntersect(false)
{
	mGlobalMove = new GameEngine::GlobalMove(fCylinderHeight, fMoveSpeed);
	//mDrawPipe = new GameEngine::DrawPipeDefault(resourceLoad, textureLoad, mMapResource, cCamera, fOffset, fRadius, V_Count, U_Count, fFogStart, fFogRadius, fFogColor, fCookieMinYOffset);

	SetCookieIndexDraw(0, resourceLoad, textureLoad, mMapResource, fOffset, fRadius, V_Count, U_Count, fFogStart, fFogRadius, fFogColor);

	mBarrierManager = new Barrier::BarrierManager(resourceLoad, cCamera, mGlobalMove, -fCylinderHeight, glm::vec2(fFogStart, fFogRadius), fFogColor, fCookieMinYOffset,
		mAngle, fZOffset, mStepH, mMinCount, mMaxCount, mSectorsCount, mRotateVelCollect, mMapResource, textureLoad, mCookieZOffset, mScore);
}

DrawPipe::PipeDrawControl::~PipeDrawControl()
{
	delete mGlobalMove;
	delete mDrawPipe;

	mDrawPipe = 0;
	mGlobalMove = 0;
}

void DrawPipe::PipeDrawControl::SetCookieIndexDraw(uint32_t mIndex, Resource::ResourceBase *resourceLoad, Resource::TextureLoad *textureLoad, Resource::MapResource *mMapResource,
	float fOffset, float fRadius, uint32_t V_Count, uint32_t U_Count,
	float fFogStart, float fFogRadius, const float *fFogColor)
{
	if (mDrawPipe) delete mDrawPipe;

	switch (mIndex)
	{
	case 0:
	{
		mDrawPipe = new GameEngine::DrawPipeDefault(resourceLoad, textureLoad, mMapResource, cCamera, fOffset, fRadius, V_Count, U_Count, fFogStart, fFogRadius, fFogColor);
	}break;

	}
}

void DrawPipe::PipeDrawControl::SetBarriers(uint32_t mIndex, Resource::ResourceBase *resourceLoad, Resource::TextureLoad *textureLoad, Resource::MapResource *mMapResource)
{
	mBarrierManager->LoadSet(mIndex, resourceLoad, mMapResource, textureLoad);
}

void DrawPipe::PipeDrawControl::Update(float fDeltaTime, float fGlobalTime)
{
	mGlobalMove->Move(fDeltaTime, fGlobalTime);
	mBarrierManager->Upade(fDeltaTime, fGlobalTime);
}

float DrawPipe::PipeDrawControl::GetDeltaDistance(void)
{
	return mGlobalMove->GetMove();
}

bool DrawPipe::PipeDrawControl::Intersect(const Draw::CookieCollisionStruct &mCookieCollision)
{
	return mBarrierManager->Intersect(mCookieCollision);
}

/*void DrawPipe::PipeDrawControl::ReleaseResource(void)
{
	mDrawPipe->ReleaseResource();
	mBarrierManager->ReleaseResource();
}

void DrawPipe::PipeDrawControl::ReCreateResource(Resource::ResourceBase *resourceLoad, Resource::TextureLoad *textureLoad, Resource::MapResource *mMapResource)
{
	mDrawPipe->ReCreateResource(resourceLoad, textureLoad, mMapResource);
	mBarrierManager->ReCreateResource(resourceLoad);
}
*/
void DrawPipe::PipeDrawControl::Draw(void) 
{
	////////////////////////////////////////////////////////////////////////////////
	//Update
	//mGlobalMove->Move(fDeltaTime, fGlobalTime);
	//mBarrierManager->Upade(fDeltaTime, fGlobalTime);
	////////////////////////////////////////////////////////////////////////////////
	//Draw
	mDrawPipe->Draw(mGlobalMove->GetMoveMatrix());
	mBarrierManager->DrawBarriers();
	////////////////////////////////////////////////////////////////////////////////
}