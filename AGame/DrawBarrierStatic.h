#include "BarrierBase.h"
#include "ShaderBarrierStatic.h"
#include "RandomNormal.h"

#pragma once
namespace Barrier
{
	class DrawBarrierStatic : public BarrierBase
	{
		int32_t mRandomCounter;
		int32_t mMod;
		//////////////////////////////////////////////////////////////////////////////////
		glm::vec2 fFog;
		const float *fFogColor;
		//////////////////////////////////////////////////////////////////////////////////
		int32_t mSectorCount;
		//////////////////////////////////////////////////////////////////////////////////
		int32_t mCurSector;
		float mBaseAngle;
		float mZoffset;
		//float fVelMin, fVelMax, fVel;//2*pi/ms
		//////////////////////////////////////////////////////////////////////////////////
		glm::mat4 mRotateMatrix, mTranslateMatrix;
		//////////////////////////////////////////////////////////////////////////////////
		//glm::mat4 mWorldTransform;
		//////////////////////////////////////////////////////////////////////////////////
		Shader::ShaderBarrierStatic *mShader;
		//////////////////////////////////////////////////////////////////////////////////
		void InitAttrib(void);
		void PresentSector(void);
		//////////////////////////////////////////////////////////////////////////////////
	public:
		DrawBarrierStatic(Draw::Barrier *mBarrier, Shader::ShaderBarrierBase *mShader, Camera::MCamera *cCamera,
			float fHeight, int32_t mSectorCount, float mBaseAngle, float mZoffset, glm::vec2 fFog, const float *fFogColor, 
			int32_t mRandomCounter = 0, int32_t mMod = 1e5);//rotate per second
		~DrawBarrierStatic();
		//////////////////////////////////////////////////////////////////////////////////
		void Update(float fDeltaTime, float fGlobalTime, float fDeltaHeight);
		//////////////////////////////////////////////////////////////////////////////////
		void Draw(void);
		//////////////////////////////////////////////////////////////////////////////////
		void Present(float fHeight);
		//////////////////////////////////////////////////////////////////////////////////
	};
}

