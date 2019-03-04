#include "FlashResourceBuffer.h"
#include "ShaderDrawFlash.h"
#include "FlashResourceTexture.h"
#include "LinearInterpolateData.h"
#include "MCamera.h"

#pragma once
namespace DrawFlash
{
	class DrawFlashBase
	{
		bool once;
		const float mDelta, mZDelta;
	protected:
		Interpolate::LinearInterpolateData *mScale;
		Interpolate::LinearInterpolateData *mAlpha;
		////////////////////////////////////////////////////////////////////
		Camera::MCamera *mCamera;
		Shader::ShaderDrawFlash *mShader;
		FlashResourceBuffer *mResourceBuffer;
		FlashResourceTexture *mFlashTexture;
		////////////////////////////////////////////////////////////////////
		glm::mat4 mTranslate, mWorld;
		////////////////////////////////////////////////////////////////////
		virtual void InitAttrib(void);
	public:
		DrawFlashBase(Shader::ShaderDrawFlash *mShader, FlashResourceBuffer *mResourceBuffer, FlashResourceTexture *mFlashTexture,
			Interpolate::InterpolateData mScale, Interpolate::InterpolateData mAlpha, float fYOffset, float fZOffset, Camera::MCamera *mCamera);
		virtual ~DrawFlashBase();
		////////////////////////////////////////////////////////////////////
		virtual void Present(void);
		virtual void Update(float mDtMs);
		virtual void Draw(void);
		bool EndFlash(void);
		////////////////////////////////////////////////////////////////////
	};
}

