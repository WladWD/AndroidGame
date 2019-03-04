#include "FlashResourceBuffer.h"


DrawFlash::FlashResourceBuffer::FlashResourceBuffer()
{
	Init();
}

DrawFlash::FlashResourceBuffer::~FlashResourceBuffer()
{
	UnbindBuffer();

	glDeleteBuffers(1, &mVertexArray);
	glDeleteBuffers(1, &mElementArray);
}

void DrawFlash::FlashResourceBuffer::Init(void)
{
	/*glm::vec3 gWorldPos;
		glm::vec4 gOffset_Tex;*/
	Mesh::VFlash mFlash[4] = 
	{
		{ glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec4(-1.0f, -1.0f, 0.0f, 0.0f) },
		{ glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec4(-1.0f,  1.0f, 0.0f, 1.0f) },
		{ glm::vec3(1.0f, 0.0f, -1.0f), glm::vec4( 1.0f, -1.0f, 1.0f, 0.0f) },
		{ glm::vec3(1.0f, 0.0f, 1.0f), glm::vec4( 1.0f,  1.0f, 1.0f, 1.0f) }
	};

	uint16_t mIndex[6] = 
	{
		0, 1, 2, 2, 1, 3
	};
	///////////////////////////////////////////////////////////////////////////
	glGenBuffers(1, &mElementArray);
	glGenBuffers(1, &mVertexArray);
	///////////////////////////////////////////////////////////////////////////
	glBindBuffer(GL_ARRAY_BUFFER, mVertexArray);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mFlash), mFlash, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementArray);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndex), mIndex, GL_STATIC_DRAW);
	mElementArrayFormat = GL_UNSIGNED_SHORT;
	///////////////////////////////////////////////////////////////////////////
	UnbindBuffer();
}

void DrawFlash::FlashResourceBuffer::BindBuffer(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, mVertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementArray);
}

void DrawFlash::FlashResourceBuffer::UnbindBuffer(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void DrawFlash::FlashResourceBuffer::Draw(void)
{
	glDrawElements(GL_TRIANGLES, 6, mElementArrayFormat, 0);
	//	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}
