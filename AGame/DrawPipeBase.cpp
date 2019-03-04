#include "DrawPipeBase.h"


GameEngine::DrawPipeBase::DrawPipeBase(Camera::MCamera *cCamera, 
	float fOffset, float fRadius, uint32_t V_Count, uint32_t U_Count,
	float fFogStart, float fFogRadius, const float *fFogColor) :
	cCamera(cCamera), fFogStart(fFogStart), fFogRadius(fFogRadius), fFogColor(fFogColor),
	fOffset(fOffset), fRadius(fRadius), V_Count(V_Count), U_Count(U_Count)
{
	CreateResources();
	//ShapeGenerator::MShapeGenerator::GenCylinder(V_Count, U_Count, -fOffset, fRadius, fOffset, vbBuffer, ibBuffer, uCountCylinder);
	//InitAttrib();
}

GameEngine::DrawPipeBase::~DrawPipeBase()
{
	DeleteResources();
}

void GameEngine::DrawPipeBase::DeleteResources(void)
{
	glDeleteBuffers(1, &vbBuffer);
	glDeleteBuffers(1, &ibBuffer);
}

void GameEngine::DrawPipeBase::CreateResources(void) 
{
	ShapeGenerator::MShapeGenerator::GenCylinder(V_Count, U_Count, -fOffset, fRadius, fOffset, vbBuffer, ibBuffer, uCountCylinder);
}