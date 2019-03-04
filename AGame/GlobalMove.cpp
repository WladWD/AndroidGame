#include "GlobalMove.h"


GameEngine::GlobalMove::GlobalMove(float fMoveStep, float fMoveSpeed) : fMoveStep(fMoveStep), fMoveSpeed(fMoveSpeed), fDiv(1.0f / 1000.0f)
{
	fMoveValue = 0.0f;
	flag = 0;
	fDMove = 0.0f;
}

GameEngine::GlobalMove::~GlobalMove()
{
}

void GameEngine::GlobalMove::Move(float fDeltaTimeMs, float fGlobalTimeMs)
{
	fDMove = fMoveSpeed * fDeltaTimeMs * fDiv;
	fMoveValue += fDMove;

	if (fMoveValue >= fMoveStep) 
	{
		fMoveValue -= fMoveStep;
		flag ^= 1;
	}

	fH[flag] = fMoveValue;
	fH[flag ^ 1] = fMoveValue - fMoveStep;

	mMoveMatrix[0] = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, fH[0], 0.0f));
	mMoveMatrix[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, fH[1], 0.0f));
}

float GameEngine::GlobalMove::GetMove(void)
{
	return fDMove;
}

const glm::mat4 *GameEngine::GlobalMove::GetMoveMatrix() 
{
	return mMoveMatrix;
}