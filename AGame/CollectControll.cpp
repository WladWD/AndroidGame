#include "CollectControll.h"


Draw::CollectControll::CollectControll(Resource::ResourceBase *resourceLoad, Camera::MCamera * cCamera, float mHeight, float mAngle, float fZOffset, float mStepH,
	int32_t mMinCount, int32_t mMaxCount,
	glm::vec2 fFog, const float * fFogColor, int32_t mSectorsCount, float mRotateVel, float mMaxDelta,
	Resource::MapResource * mMapResource, Resource::TextureLoad * textureLoad,
	float fCookieMinYOffset, float mCookieZOffset, Score::Score *mScore, 
	std::string mCollectName, std::string mCoffeeCollectName) : CollectControllBase(cCamera, mHeight, mAngle, fZOffset,
		fFog, fFogColor, mRotateVel, mSectorsCount), mMaxDelta(mMaxDelta),
	mStepH(mStepH)

{
	mMinCountSugar = mMinCount;
	mMaxCountSugar = mMaxCount;

	mCollect = new Draw::Collect(resourceLoad, mCollectName);
	mCoffee = new Draw::Collect(resourceLoad, mCoffeeCollectName);
	Init(resourceLoad, mMapResource, textureLoad, fCookieMinYOffset, mCookieZOffset, mScore);
}

Draw::CollectControll::~CollectControll()
{
	delete mSugarCollect;
	delete mCoffeeCollect;

	delete mCollect;
	delete mCoffee;

	delete mShader;
}

void Draw::CollectControll::Init(Resource::ResourceBase *resourceLoad, Resource::MapResource * mMapResource, Resource::TextureLoad * textureLoad, 
	float fCookieMinYOffset, float mCookieZOffset, Score::Score *mScore)
{
	mShader = new Shader::ShaderCollectDefault(resourceLoad);
	
	mCoffeeCollect = new CoffeeControll(mCoffee, cCamera, mHeight, mAngleBase, fZOffset, mStepH, fFog, fFogColor, mRotateVel,
		mShader, 1.0, 2.0f, mSectorsCount, mMaxDelta, resourceLoad, mMapResource, textureLoad, fCookieMinYOffset, mCookieZOffset, mScore);
	mSugarCollect = new SugarControll(mCollect, cCamera, mHeight, mAngleBase, fZOffset, mStepH, fFog, fFogColor,
		mRotateVel, mShader, mMinCountSugar, mMaxCountSugar, mSectorsCount, mMaxDelta, resourceLoad, mMapResource, textureLoad, fCookieMinYOffset, mCookieZOffset, mScore);
}

void Draw::CollectControll::Intersect(const Draw::CookieCollisionStruct & mCookieCollision)
{
	//mNearesSuggarIndex, mNearesCoffeeIndex
	mSugarCollect->Intersect(mCookieCollision);
	mCoffeeCollect->Intersect(mCookieCollision);
}

void Draw::CollectControll::Update(float fDeltaTime, float fGlobalTime, float fDeltaHeight)
{
	//mNearesSuggarIndex.clear();
	//mNearesCoffeeIndex.clear();

	mSugarCollect->Update(fDeltaTime, fGlobalTime, fDeltaHeight);
	mCoffeeCollect->Update(fDeltaTime, fGlobalTime, fDeltaHeight);
}

void Draw::CollectControll::Draw(void)
{
	mSugarCollect->Draw();
	mCoffeeCollect->Draw();

	mSugarCollect->DrawFlash();
	mCoffeeCollect->DrawFlash();
}

void Draw::CollectControll::Present(void)
{
	mSugarCollect->Present();
	mCoffeeCollect->Present();
}
