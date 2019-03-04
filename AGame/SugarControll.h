#include "CollectDrawControllBase.h"

#pragma once
namespace Draw
{
	class SugarControll : public CollectDrawControllBase
	{
	protected:
		Score::Score *mScore;
		DrawFlash::DrawFlashCreator *mDrawFlash;
		///////////////////////////////////////////////////////////////////////
		int32_t mMinCount, mMaxCount;
		///////////////////////////////////////////////////////////////////////
		int32_t mCurrentCount, mCurrentTarget;
		///////////////////////////////////////////////////////////////////////
		uint32_t mCountSugar;
		///////////////////////////////////////////////////////////////////////
		void ResizeLine(void);
		void Init(Draw::Collect *mCollect, Shader::ShaderCollectBase *mShader);
	public:
		SugarControll(Draw::Collect *mCollect, Camera::MCamera *cCamera, float mHeight, float mAngleBase, float fZOffset, float mStepH,
			glm::vec2 fFog, const float *fFogColor, float mRotateVel, Shader::ShaderCollectBase *mShaderCollect,
			int32_t mMinCount, int32_t mMaxCount, int32_t mSectorsCount, float mMaxDelta,
			Resource::ResourceBase *resourceLoad, Resource::MapResource * mMapResource, Resource::TextureLoad * textureLoad,
			float fCookieMinYOffset, float mCookieZOffset, Score::Score *mScore);
		~SugarControll();
		///////////////////////////////////////////////////////////////////////
		void Intersect(const Draw::CookieCollisionStruct &mCookieCollision);
		void Present(void);
		///////////////////////////////////////////////////////////////////////
	};
}

