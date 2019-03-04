#include "ScoreDrawerBase.h"


DrawScore::ScoreDrawerBase::ScoreDrawerBase(QuadBuffer *mBuffer) : mBuffer(mBuffer)
{
}

DrawScore::ScoreDrawerBase::~ScoreDrawerBase()
{
}

void DrawScore::ScoreDrawerBase::InitAttrib(GLint gWorldPos)
{
	//programm mast binding!!!

	/*attribute vec2 gWorldPos;*/

	mBuffer->BindBuffer();

	//GLint gWorldPos = mShader->GetPositionAttrib();

	uint32_t mStride = sizeof(glm::vec2);
	uint32_t offset = 0;
	if (gWorldPos != (-1))
	{
		glVertexAttribPointer(gWorldPos, 2, GL_FLOAT, GL_FALSE, mStride, (const void *)offset);
		glEnableVertexAttribArray(gWorldPos);
	}

	//mShader->BindTextureToSlot();
}

glm::mat4 DrawScore::ScoreDrawerBase::ConvertRectToWorld(glm::vec4 mRect)
{
	glm::vec2 mScale = glm::vec2(mRect.z, mRect.w) - glm::vec2(mRect.x, mRect.y);
	glm::vec2 mOffset = glm::vec2(mRect.x, mRect.y);
	
	glm::mat4 mWorld = glm::translate(glm::mat4(1.0f), glm::vec3(mOffset, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(mScale, 1.0f));

	return mWorld;
}

glm::mat4 DrawScore::ScoreDrawerBase::ConvertOffetScaleToWorld(glm::vec4 mOffetScale)
{
	glm::vec2 mScale = glm::vec2(mOffetScale.z, mOffetScale.w);
	glm::vec2 mOffset = glm::vec2(mOffetScale.x, mOffetScale.y);

	glm::mat4 mWorld = glm::translate(glm::mat4(1.0f), glm::vec3(mOffset, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(mScale, 1.0f));

	return mWorld;
}