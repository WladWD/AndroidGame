#include "MShapeGenerator.h"


ShapeGenerator::MShapeGenerator::MShapeGenerator()
{
}

ShapeGenerator::MShapeGenerator::~MShapeGenerator()
{
}

void ShapeGenerator::MShapeGenerator::GenCylinder(int32_t uVSliceCount, int32_t uHSliceCount/*= 2*/, float fYOffset, float fRadius, float fHeight, GLuint &vbBuffer, GLuint &ibBuffer, uint32_t &uCount)
{
	int32_t uVertCount = uVSliceCount + 1;
	Mesh::VTMesh *cylinder = new Mesh::VTMesh[uHSliceCount * uVertCount];//VNTMesh
	uint16_t *index = new uint16_t[(uHSliceCount - 1) * uVSliceCount * 6];

	float fStepAngle = glm::pi<float>() * 2.0f / float(uVSliceCount);
	float fHeightStep = fHeight / float(uHSliceCount - 1);
	float fUTexStep = 1.0f / float(uVSliceCount);
	float fVTexStep = 1.0f / float(uHSliceCount - 1);
	float fCurrentHeight = 0.0f;
	float fVCurrentTex = 0.0f;
	for (register int32_t i = 0; i < uHSliceCount; i++)
	{
		float fCurrentAngle = 0.0f;
		float fUCurrentTex = 0.0f;
		for (register int32_t j = 0; j < uVertCount; j++)
		{
			cylinder[i * uVertCount + j].gWorldPos = glm::vec3(fRadius * glm::cos(fCurrentAngle), fCurrentHeight + fYOffset, fRadius * glm::sin(fCurrentAngle));
			//cylinder[i * uVertCount + j].gWorldNorm = glm::normalize( glm::vec3(-cylinder[i * uVertCount + j].gWorldPos.x, 0.0f, -cylinder[i * uVertCount + j].gWorldPos.z));
			cylinder[i * uVertCount + j].gTexCoord = glm::vec2(fUCurrentTex, fVCurrentTex)*4.0f;//glm::vec2(fUCurrentTex* 2.0f, fVCurrentTex*1.0f) * 4.0f;


			fCurrentAngle += fStepAngle;
			fUCurrentTex += fUTexStep;
		}
		fVCurrentTex += fVTexStep;
		fCurrentHeight += fHeightStep;
	}

	uint32_t index_counter = 0;
	for (register int32_t i = 0; i < (uHSliceCount-1); i++) 
	{
		for (register int32_t j = 0; j < uVSliceCount; j++)
		{
			index[index_counter++] = (i + 0) * uVertCount + (j + 0);
			index[index_counter++] = (i + 0) * uVertCount + (j + 1);
			index[index_counter++] = (i + 1) * uVertCount + (j + 0);
			
			index[index_counter++] = (i + 1) * uVertCount + (j + 0);
			index[index_counter++] = (i + 0) * uVertCount + (j + 1);
			index[index_counter++] = (i + 1) * uVertCount + (j + 1);
		}
	}

	/*float vert[] = {0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f};*/
	const float g = 0.2f;
	const float gz = 1.0f;
	float vert[] = { 0.0f, -gz, g,
					-g, -gz, -g,
					 g, -gz, -g };

	uint16_t ind[] = {0, 1, 2};


	glGenBuffers(1, &vbBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, vert, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Mesh::VTMesh) * uHSliceCount * uVertCount, cylinder, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glGenBuffers(1, &ibBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibBuffer);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 3, ind, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * index_counter, index, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	uCount = index_counter;

	delete[] index;
	delete[] cylinder;
}