#include "DrawBitmap.h"


DrawScore::DrawBitmap::DrawBitmap(Shader::ShaderDrawBitmap * mShader, TextureResource::ResourceTextureBase * mTextureResource, QuadBuffer *mBuffer) : ScoreDrawerBase(mBuffer),
	mShader(mShader), mTextureResource(mTextureResource)
{
}

DrawScore::DrawBitmap::~DrawBitmap()
{
}

//void DrawScore::DrawBitmap::InitAttrib(void)
//{
//	//programm mast binding!!!
//
//	/*attribute vec2 gWorldPos;*/
//
//	mBuffer->BindBuffer();
//
//	GLint gWorldPos = mShader->GetPositionAttrib();
//
//	uint32_t mStride = sizeof(glm::vec2);
//	uint32_t offset = 0;
//	if (gWorldPos != (-1))
//	{
//		glVertexAttribPointer(gWorldPos, 2, GL_FLOAT, GL_FALSE, mStride, (const void *)offset);
//		glEnableVertexAttribArray(gWorldPos);
//	}
//
//	mShader->BindTextureToSlot();
//}

void DrawScore::DrawBitmap::Draw(glm::vec4 mRect)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	glUseProgram(mShader->GetProgram());
	InitAttrib(mShader->GetPositionAttrib());
	mShader->BindTextureToSlot();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	mShader->SetTexture();
	auto mTex = mTextureResource->GetTexture();
	glBindTexture(mTex.texture_target, mTex.texture);

	mShader->SetWorldMatrix(ConvertRectToWorld(mRect));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	mBuffer->Draw();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	mBuffer->UnbindBuffer();
	mShader->ResetProgram();
	glUseProgram(0);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
}
