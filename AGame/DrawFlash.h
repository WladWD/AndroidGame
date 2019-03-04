#include "DrawFlashBase.h"

#pragma once
namespace DrawFlash
{
	class DrawFlash : public DrawFlashBase
	{
	public:
		DrawFlash(Shader::ShaderDrawFlash *mShader, FlashResourceBuffer *mResourceBuffer, FlashResourceTexture *mFlashTexture,
			Interpolate::InterpolateData mScale, Interpolate::InterpolateData mAlpha, float fYOffset, float fZOffset, Camera::MCamera *mCamera);
		~DrawFlash();
	};

}

