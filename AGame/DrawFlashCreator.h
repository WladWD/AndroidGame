#include "DrawFlash.h"

#pragma once
namespace DrawFlash
{
	class DrawFlashCreator
	{
		float fCookieMinYOffset, mCookieZOffset;
		///////////////////////////////////////////////////////////////////////////////
		Camera::MCamera *mCamera;
		///////////////////////////////////////////////////////////////////////////////
		Shader::ShaderDrawFlash *mShader;
		FlashResourceBuffer *mResourceBuffer;
		FlashResourceTexture *mFlashTexture;
		///////////////////////////////////////////////////////////////////////////////
	public:
		DrawFlashCreator(Resource::ResourceBase *resourceLoad, Resource::MapResource *mMapResource, Resource::TextureLoad *textureLoad,
			std::string mFlashTextureName, Camera::MCamera *mCamera, float fCookieMinYOffset, float mCookieZOffset);
		~DrawFlashCreator();
		///////////////////////////////////////////////////////////////////////////////
		DrawFlash *CreateDrawFlash(Interpolate::InterpolateData mScale, Interpolate::InterpolateData mAlpha);
		///////////////////////////////////////////////////////////////////////////////
	};
}

