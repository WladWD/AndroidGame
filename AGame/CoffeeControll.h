#include "CollectDrawControllBase.h"

#pragma once
namespace Draw
{
	class CoffeeControll : public CollectDrawControllBase
	{
		///////////////////////////////////////////////////////////////////////
		float mMinTime, mMaxTime;
		///////////////////////////////////////////////////////////////////////
		float mCurrentCount, mCurrentTarget;
		///////////////////////////////////////////////////////////////////////
	protected:
		Score::Score *mScore;
		DrawFlash::DrawFlashCreator *mDrawFlash;
		///////////////////////////////////////////////////////////////////////
		uint32_t mCountCoffee;
		///////////////////////////////////////////////////////////////////////
		void ResizeLine(void);
		void Init(Draw::Collect *mCollect, Shader::ShaderCollectBase *mShader);
	public:
		CoffeeControll(Draw::Collect *mCollect, Camera::MCamera *cCamera, float mHeight, float mAngleBase, float fZOffset, float mStepH,
			glm::vec2 fFog, const float *fFogColor, float mRotateVel, Shader::ShaderCollectBase *mShaderCollect,
			float mMinTime, float mMaxTime, int32_t mSectorsCount, float mMaxDelta,
			Resource::ResourceBase *resourceLoad, Resource::MapResource * mMapResource, Resource::TextureLoad * textureLoad,
			float fCookieMinYOffset, float mCookieZOffset, Score::Score *mScore);
		~CoffeeControll();
		///////////////////////////////////////////////////////////////////////
		void Intersect(const Draw::CookieCollisionStruct &mCookieCollision);
		void Update(float fDeltaTime, float fGlobalTime, float fDeltaHeight);
		void Draw(void);
		void Present(void);
		///////////////////////////////////////////////////////////////////////
	};
}

