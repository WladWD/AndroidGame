#include "CollectBase.h"
#include "ShaderCollectDefault.h"
#include "RandomNormal.h"
#include "Collision.h"
#include "DrawFlashCreator.h"
#include "Score.h"

#pragma once
namespace Draw
{
	class CollectStandart : public CollectBase
	{
		float HeightShowConst;
		Engine::RandomNormal *mRandom;
	protected:
		DrawFlash::DrawFlash *mDrawFlash;
		/////////////////////////////////////////////////////////////////////////////////////
		float fZOffset;
		/////////////////////////////////////////////////////////////////////////////////////
		glm::mat4 mRotateLocal;
		glm::mat4 mRotateGlobal, mTranslateGlobal;
		/////////////////////////////////////////////////////////////////////////////////////
		float mRotateVel, mRotateVal;
		/////////////////////////////////////////////////////////////////////////////////////
		glm::vec2 fFog;
		const float * fFogColor;
		/////////////////////////////////////////////////////////////////////////////////////
		Shader::ShaderCollectBase *mShader;
		/////////////////////////////////////////////////////////////////////////////////////
		void InitAttrib(void);
		void RandomizeAngle(void);
		void UpdateRotate(float fDeltaTime, float fGlobalTime);
		/////////////////////////////////////////////////////////////////////////////////////
		void DrawEvent(void);
	public:
		CollectStandart(Draw::Collect *mCollect, Camera::MCamera *cCamera, float mHeight, float mAngle, float fZOffset,
			glm::vec2 fFog, const float *fFogColor, float mRotateVel, Shader::ShaderCollectBase *mShaderCollect, float mRotateVal, float HeightShowConst, DrawFlash::DrawFlashCreator *mDrawFlash);
		~CollectStandart();
		/////////////////////////////////////////////////////////////////////////////////////
		bool Intersect(const Draw::CookieCollisionStruct &mCookieCollision);
		void Update(float fDeltaTime, float fGlobalTime, float fDeltaHeight);
		void Draw(void);
		void DrawFlash(void);
		bool IsCollected(void);
		/////////////////////////////////////////////////////////////////////////////////////
		bool Present(float mHeight, float mAngle, float mRotateVel);
		/////////////////////////////////////////////////////////////////////////////////////
	};
	//TODO:
	//добавить отрисовку сбора (не рисовать объект и нарисовать раст€гивающуюс€ текстуру вспышки)
}

