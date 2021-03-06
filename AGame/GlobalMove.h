#include "MCamera.h"

#pragma once
namespace GameEngine
{
	class GlobalMove
	{
		///////////////////////////////////////////////////////////////////
		const float fMoveStep, fMoveSpeed;
		const float fDiv;
		///////////////////////////////////////////////////////////////////
		float fDMove;
		///////////////////////////////////////////////////////////////////
		glm::mat4 mMoveMatrix[2];
		float fMoveValue, fH[2];
		uint8_t flag;
		///////////////////////////////////////////////////////////////////
	public:
		GlobalMove(float fMoveStep, float fMoveSpeed);
		~GlobalMove();
		///////////////////////////////////////////////////////////////////
		void Move(float fDeltaTimeMs, float fGlobalTimeMs);
		///////////////////////////////////////////////////////////////////
		float GetMove(void);
		///////////////////////////////////////////////////////////////////
		const glm::mat4 *GetMoveMatrix();
	};
}
