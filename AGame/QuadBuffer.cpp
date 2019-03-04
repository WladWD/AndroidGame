#include "QuadBuffer.h"


DrawScore::QuadBuffer::QuadBuffer()
{
	Init();
}

DrawScore::QuadBuffer::~QuadBuffer()
{
	UnbindBuffer();

	glDeleteBuffers(1, &mVertexArray);
	glDeleteBuffers(1, &mElementArray);
}

void DrawScore::QuadBuffer::Init(void)
{
	/*glm::vec3 gWorldPos;
	glm::vec4 gOffset_Tex;*/
	glm::vec2 mVert[4] =
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f)
	};
	/*glm::vec2(-1.0f, -1.0f),
		glm::vec2(-1.0f, 1.0f),
		glm::vec2(1.0f, -1.0f),
		glm::vec2(1.0f, 1.0f)*/
	uint16_t mIndex[6] =
	{
		0, 1, 2, 2, 1, 3
	};
	///////////////////////////////////////////////////////////////////////////
	glGenBuffers(1, &mElementArray);
	glGenBuffers(1, &mVertexArray);
	///////////////////////////////////////////////////////////////////////////
	glBindBuffer(GL_ARRAY_BUFFER, mVertexArray);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVert), mVert, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementArray);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndex), mIndex, GL_STATIC_DRAW);
	mElementArrayFormat = GL_UNSIGNED_SHORT;
	///////////////////////////////////////////////////////////////////////////
	UnbindBuffer();
}

void DrawScore::QuadBuffer::BindBuffer(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, mVertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementArray);
}

void DrawScore::QuadBuffer::UnbindBuffer(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void DrawScore::QuadBuffer::Draw(void)
{
	glDrawElements(GL_TRIANGLES, 6, mElementArrayFormat, 0);
	//	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}
