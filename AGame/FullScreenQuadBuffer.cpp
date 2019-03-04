#include "FullScreenQuadBuffer.h"


FullScreenBuffer::FullScreenQuadBuffer::FullScreenQuadBuffer(void)
{
	InitBuffer();
}

FullScreenBuffer::FullScreenQuadBuffer::~FullScreenQuadBuffer()
{
	glDeleteBuffers(1, &vbBuffer);
	glDeleteBuffers(1, &ibBuffer);
}

void FullScreenBuffer::FullScreenQuadBuffer::InitBuffer(void)
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/*Mesh::VTMesh mTex[] = { {{ -1.0f, -1.0f, 0.0f}, { 0.0f, 0.0f }},
	{ { -1.0f, 1.0f, 0.0f },{ 0.0f, 1.0f }},
	{ { 1.0f, -1.0f, 0.0f },{ 1.0f, 0.0f }},
	{ { 1.0f, 1.0f, 0.0f },{ 1.0f, 1.0f }} };*/
	glm::vec2 mTex[] = { { 0.0f, 0.0f } ,
	{ 0.0f, 1.0f } ,
	{ 1.0f, 0.0f } ,
	{ 1.0f, 1.0f } };
	uint16_t mIdx[] = { 0, 1, 2, 2, 1, 3 };
	/////////////////////////////////////////////////////////////////////////////////////////
	glGenBuffers(1, &vbBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vbBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mTex), mTex, GL_STATIC_DRAW);
	/////////////////////////////////////////////////////////////////////////////////////////
	glGenBuffers(1, &ibBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIdx), mIdx, GL_STATIC_DRAW);
	/////////////////////////////////////////////////////////////////////////////////////////
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	/////////////////////////////////////////////////////////////////////////////////////////
}

GLuint FullScreenBuffer::FullScreenQuadBuffer::GetArrayBuffer(void)
{
	return vbBuffer;
}

GLuint FullScreenBuffer::FullScreenQuadBuffer::GetElementArrayBuffer(void)
{
	return ibBuffer;
}
