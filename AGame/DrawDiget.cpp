#include "DrawDiget.h"


DrawScore::DrawDiget::DrawDiget(Shader::ShaderDrawText *mShader, DigetTextureResource *mTextureResource, QuadBuffer *mBuffer) : ScoreDrawerBase(mBuffer),
mShader(mShader), mTextureResource(mTextureResource)
{
}

DrawScore::DrawDiget::~DrawDiget()
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

void DrawScore::DrawDiget::Draw(glm::vec4 mOffsetScaleDiget, uint32_t mDiget)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	glUseProgram(mShader->GetProgram());
	InitAttrib(mShader->GetPositionAttrib());
	mShader->BindTextureToSlot();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	mShader->SetTexture();
	auto mTex = mTextureResource->GetTexture();
	glBindTexture(mTex.texture_target, mTex.texture);

	mShader->SetWorldMatrix(ConvertOffetScaleToWorld(mOffsetScaleDiget));
	mShader->SetPackOffsetScale(mTextureResource->GetTexParamByDiget(mDiget));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	mBuffer->Draw();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	mBuffer->UnbindBuffer();
	mShader->ResetProgram();
	glUseProgram(0);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
}
