#include "DrawScore.h"


DrawScore::DrawScore::DrawScore(Resource::MapResource * mMapResource, Resource::TextureLoad * textureLoad, Resource::ResourceBase *resourceLoad,
	std::string mDigetTextureName, string mBitmapTextureName, 
	glm::vec4 mDigetsRect, uint32_t mDigetCount, glm::vec4 mBitmapRect) : mDigetsRect(mDigetsRect), mDigetCount(mDigetCount), mBitmapRect(mBitmapRect)
{
	mTextureResourceText = new DigetTextureResource(mMapResource, textureLoad, mDigetTextureName);
	mTextureResourceBitmap = new TextureResource::ResourceTextureBase(mMapResource, textureLoad, mBitmapTextureName);

	Init(mMapResource, textureLoad, resourceLoad);
}

DrawScore::DrawScore::~DrawScore()
{
	delete mDrawBitmapShader;
	delete mDrawTextShader;
	delete mQuadBuffer;

	delete mTextureResourceText;
	delete mTextureResourceBitmap;

	delete mDrawBitmap;
	delete mDrawDiget;
}

void DrawScore::DrawScore::Init(Resource::MapResource *mMapResource, Resource::TextureLoad *textureLoad, Resource::ResourceBase *resourceLoad)
{
	mDrawBitmapShader = new Shader::ShaderDrawBitmap(resourceLoad);
	mDrawTextShader = new Shader::ShaderDrawText(resourceLoad);

	mQuadBuffer = new QuadBuffer();

	mDrawBitmap = new DrawBitmap(mDrawBitmapShader, mTextureResourceBitmap, mQuadBuffer);
	mDrawDiget = new DrawDiget(mDrawTextShader, mTextureResourceText, mQuadBuffer);
}

void DrawScore::DrawScore::InitDigets(uint32_t mDiget)
{
	mDigets.clear();

	if (!mDiget)
		mDigets.push_back(0);

	while (mDiget) 
	{
		mDigets.push_back(mDiget % 10);
		mDiget /= 10;
	}
	reverse(mDigets.begin(), mDigets.end());

	mWightDiget = (mDigetsRect.z - mDigetsRect.x) / (static_cast<float>( glm::max(mDigetCount, (uint32_t)mDigets.size())));
	mOffsetScaleDiget = glm::vec4(mDigetsRect.x, mDigetsRect.y, mWightDiget, mDigetsRect.w - mDigetsRect.y);
}

void DrawScore::DrawScore::DrawLeft(void)
{
	for (register uint32_t i = 0; i < mDigets.size(); ++i)
	{
		glm::vec4 mLocalOffsetScale = glm::vec4(mOffsetScaleDiget.x + i * mWightDiget, mOffsetScaleDiget.y,
			mOffsetScaleDiget.z, mOffsetScaleDiget.w);

		mDrawDiget->Draw(mLocalOffsetScale, mDigets[i]);
	}
}

void DrawScore::DrawScore::DrawRight(void)
{
	uint32_t mRealCount = glm::max(mDigetCount, (uint32_t)mDigets.size()) - 1;
	for (register int32_t i = mDigets.size() - 1, j = 0; i >= 0; --i, ++j)
	{
		glm::vec4 mLocalOffsetScale = glm::vec4(mOffsetScaleDiget.x + (mRealCount  - j) * mWightDiget, mOffsetScaleDiget.y,
			mOffsetScaleDiget.z, mOffsetScaleDiget.w);

		mDrawDiget->Draw(mLocalOffsetScale, mDigets[i]);
	}
}

void DrawScore::DrawScore::Draw(uint32_t mDiget, bool ToLeftAlign)
{
	////////////////////////////////////////////////////////////////////////////////////////////
	mDrawBitmap->Draw(mBitmapRect);
	////////////////////////////////////////////////////////////////////////////////////////////
	InitDigets(mDiget);//1234567890
	////////////////////////////////////////////////////////////////////////////////////////////
	if (ToLeftAlign)
		DrawLeft();
	else
		DrawRight();
}
