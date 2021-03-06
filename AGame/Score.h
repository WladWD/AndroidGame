#include "DrawScore.h"

#pragma once
namespace Score
{
	class Score
	{
		//////////////////////////////////////////////////////////////////////////////////////////
		const float mScoreCoeff;
		const float mCoffeeScoreCoeff;
		const float mSugarScoreCoeff;
		//////////////////////////////////////////////////////////////////////////////////////////
		DrawScore::DrawScore *mDrawCoffeeScore;
		DrawScore::DrawScore *mDrawSugarScore;
		DrawScore::DrawScore *mDrawScore;
		//////////////////////////////////////////////////////////////////////////////////////////
		uint64_t mScore, mCoffeeScore, mSugarScore;
		float mScoreFloat;
		//////////////////////////////////////////////////////////////////////////////////////////
	public:
		Score(Resource::MapResource *mMapResource, Resource::TextureLoad *textureLoad, Resource::ResourceBase *resourceLoad,
			std::string mDigetTextureName, string mSugarTextureName, string mCoffeeTextureName, string mScoreTextureName,
			glm::vec4 mSugarDigetsRect, glm::vec4 mSugarBitmapRect, 
			glm::vec4 mCoffeeDigetsRect, glm::vec4 mCoffeeBitmapRect,
			glm::vec4 mScoreDigetsRect, glm::vec4 mScoreBitmapRect,
			uint32_t mDigetCount);
		~Score();
		//////////////////////////////////////////////////////////////////////////////////////////
		void IncSugar(void);
		void IncCoffee(void);
		//////////////////////////////////////////////////////////////////////////////////////////
		void UpdateScore(float mDeltaDistance);
		//////////////////////////////////////////////////////////////////////////////////////////
		void DrawScore(void);
		//////////////////////////////////////////////////////////////////////////////////////////
	};
}

