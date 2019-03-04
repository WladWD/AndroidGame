#include "DrawFlash.h"

DrawFlash::DrawFlash::DrawFlash(Shader::ShaderDrawFlash * mShader, FlashResourceBuffer * mResourceBuffer, FlashResourceTexture * mFlashTexture, 
	Interpolate::InterpolateData mScale, Interpolate::InterpolateData mAlpha, float fYOffset, float fZOffset, Camera::MCamera * mCamera) :
	DrawFlashBase(mShader,  mResourceBuffer,  mFlashTexture,
		mScale, mAlpha, fYOffset, fZOffset, mCamera)
{
}

DrawFlash::DrawFlash::~DrawFlash()
{
}
