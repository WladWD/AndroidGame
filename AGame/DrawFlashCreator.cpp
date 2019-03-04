#include "DrawFlashCreator.h"


DrawFlash::DrawFlashCreator::DrawFlashCreator(Resource::ResourceBase * resourceLoad, Resource::MapResource * mMapResource, Resource::TextureLoad * textureLoad,
	std::string mFlashTextureName, Camera::MCamera * mCamera, float fCookieMinYOffset, float mCookieZOffset) : mCamera(mCamera),
	fCookieMinYOffset(fCookieMinYOffset), mCookieZOffset(mCookieZOffset)
{
	mShader = new Shader::ShaderDrawFlash(resourceLoad);
	mResourceBuffer = new FlashResourceBuffer();
	mFlashTexture = new FlashResourceTexture(mMapResource, textureLoad, mFlashTextureName);
}

DrawFlash::DrawFlashCreator::~DrawFlashCreator()
{
	delete mFlashTexture;
	delete mShader;
	delete mResourceBuffer;
}

DrawFlash::DrawFlash * DrawFlash::DrawFlashCreator::CreateDrawFlash(Interpolate::InterpolateData mScale, Interpolate::InterpolateData mAlpha)
{
	return new DrawFlash(mShader, mResourceBuffer, mFlashTexture, mScale, mAlpha, fCookieMinYOffset, mCookieZOffset, mCamera);
}
