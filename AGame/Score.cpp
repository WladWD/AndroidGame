#include "Score.h"


Score::Score::Score(Resource::MapResource * mMapResource, Resource::TextureLoad * textureLoad, Resource::ResourceBase * resourceLoad,
	std::string mDigetTextureName, string mSugarTextureName, string mCoffeeTextureName,
	string mScoreTextureName, glm::vec4 mSugarDigetsRect, glm::vec4 mSugarBitmapRect, 
	glm::vec4 mCoffeeDigetsRect, glm::vec4 mCoffeeBitmapRect, glm::vec4 mScoreDigetsRect, 
	glm::vec4 mScoreBitmapRect, uint32_t mDigetCount) : mScoreCoeff(0.5f), mCoffeeScoreCoeff(4.0f), mSugarScoreCoeff(2.0f), mScoreFloat(0.0f),
	mScore(0), mCoffeeScore(0), mSugarScore(0)
{
	mDrawCoffeeScore = new DrawScore::DrawScore(mMapResource, textureLoad, resourceLoad,
		mDigetTextureName, mCoffeeTextureName,
		mCoffeeDigetsRect, mDigetCount, mCoffeeBitmapRect);
	mDrawSugarScore = new DrawScore::DrawScore(mMapResource, textureLoad, resourceLoad,
		mDigetTextureName, mSugarTextureName,
		mSugarDigetsRect, mDigetCount, mSugarBitmapRect);
	mDrawScore = new DrawScore::DrawScore(mMapResource, textureLoad, resourceLoad,
		mDigetTextureName, mScoreTextureName,
		mScoreDigetsRect, mDigetCount, mScoreBitmapRect);
}

Score::Score::~Score()
{
	delete mDrawCoffeeScore;
	delete mDrawSugarScore;
	delete mDrawScore;
}

void Score::Score::IncSugar(void)
{
	++mSugarScore;
	mScore += mSugarScoreCoeff;
}

void Score::Score::IncCoffee(void)
{
	++mCoffeeScore;
	mScore += mCoffeeScoreCoeff;
}

void Score::Score::UpdateScore(float mDeltaDistance)
{
	mScoreFloat += mDeltaDistance * mScoreCoeff;
	//mScore += mDeltaDistance * mScoreCoeff;
}

void Score::Score::DrawScore(void)
{
	//////////////////////////////////////////////////////////////////////////////////////
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//////////////////////////////////////////////////////////////////////////////////////
	mDrawCoffeeScore->Draw(mCoffeeScore, false);
	mDrawSugarScore->Draw(mSugarScore, false);
	mDrawScore->Draw(mScore + mScoreFloat, false);
	//////////////////////////////////////////////////////////////////////////////////////
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	//////////////////////////////////////////////////////////////////////////////////////
}
