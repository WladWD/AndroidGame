#include "CollectBase.h"
#include "Cookie.h"
#include "ShaderCollectBase.h"
#include "RandomNormal.h"

#pragma once
namespace Draw
{
	class CollectControllBase
	{
	protected:
		///////////////////////////////////////////////////////////////////////
		Engine::RandomNormal *mRandom;
		///////////////////////////////////////////////////////////////////////
		int32_t mIntAngle;
		float mHeight, mAngleBase, fZOffset, mRotateVel;
		int32_t mSectorsCount;
		///////////////////////////////////////////////////////////////////////
		int32_t mMinCountSugar, mMaxCountSugar;
		///////////////////////////////////////////////////////////////////////
		glm::vec2 fFog;
		const float *fFogColor;
		///////////////////////////////////////////////////////////////////////
		Camera::MCamera *cCamera;
		//uint32_t mNearestIndex;
		///////////////////////////////////////////////////////////////////////
		Shader::ShaderCollectBase *mShader;
		//std::vector<CollectBase *> mCollects;
		///////////////////////////////////////////////////////////////////////
	public:
		CollectControllBase(Camera::MCamera *cCamera, float mHeight, float mAngleBase, float fZOffset, //fZOffset = Cookie fZOffset
			glm::vec2 fFog, const float *fFogColor, float mRotateVel, int32_t mSectorsCount);
		~CollectControllBase();
		///////////////////////////////////////////////////////////////////////
		//CollectBase *GetNearestObject(void);
		///////////////////////////////////////////////////////////////////////
		virtual void Intersect(const Draw::CookieCollisionStruct &mCookieCollision) = 0;
		virtual void Update(float fDeltaTime, float fGlobalTime, float fDeltaHeight) = 0;
		virtual void Draw(void) = 0;
		virtual void Present(void) = 0;
		///////////////////////////////////////////////////////////////////////
	};
}
