#include "DigetTextureResource.h"


DrawScore::DigetTextureResource::DigetTextureResource(Resource::MapResource *mMapResource, Resource::TextureLoad * textureLoad, std::string mDigetTextureName) :
	TextureResource::ResourceTextureBase(mMapResource, textureLoad, mDigetTextureName)
{
	//mDigetTexture = mMapResource->GetResourceByID(textureLoad->LoadFromResource(mFlashTextureName.c_str()));

	float mMainScale = 62.0f / 593.0f;
	mOffsets[0] = 0.0; mScals[0] = mMainScale;
	mOffsets[1] = mMainScale * 8.6f; mScals[1] = mMainScale;
	mOffsets[2] = mMainScale * 4.78; mScals[2] = mMainScale * 0.98;
	
	mOffsets[3] = mMainScale * 1.9; mScals[3] = mMainScale;
	mOffsets[4] = mMainScale * 6.6f; mScals[4] = mMainScale;
	mOffsets[5] = mMainScale * 5.7f; mScals[5] = mMainScale * 0.9f;

	mOffsets[6] = mMainScale * 2.8f; mScals[6] = mMainScale;
	mOffsets[7] = mMainScale * 7.6; mScals[7] = mMainScale;
	mOffsets[8] = mMainScale * 1; mScals[8] = mMainScale;
	mOffsets[9] = mMainScale * 3.8; mScals[9] = mMainScale;
}

DrawScore::DigetTextureResource::~DigetTextureResource()
{
}

//62/593
//0 8 3 6 9 2 5 4 7 1
//

glm::vec4 DrawScore::DigetTextureResource::GetTexParamByDiget(uint32_t mDig)
{
	return glm::vec4(mOffsets[mDig], 0.0f, mScals[mDig], 1.0f);
}

//const Resource::GLTextureResource & DrawScore::DigetTextureResource::GetFlashTexture(void)
//{
//	return mDigetTexture;
//}
