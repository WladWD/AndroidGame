#include "CollectControllBase.h"
#include "CollectStandart.h"
#include "ShaderCollectDefault.h"
#include "SugarControll.h"
#include "CoffeeControll.h"

#pragma once
namespace Draw
{
	class CollectControll : public CollectControllBase
	{
	protected:
		///////////////////////////////////////////////////////////////////////
		Draw::Collect *mCollect;
		SugarControll *mSugarCollect;
		///////////////////////////////////////////////////////////////////////
		Draw::Collect *mCoffee;
		CoffeeControll* mCoffeeCollect;
		///////////////////////////////////////////////////////////////////////
		float mStepH, mMaxDelta;
		///////////////////////////////////////////////////////////////////////
		//std::vector<uint32_t> mNearesSuggarIndex, mNearesCoffeeIndex;
		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////
		void Init(Resource::ResourceBase *resourceLoad, Resource::MapResource * mMapResource, Resource::TextureLoad * textureLoad, float fCookieMinYOffset, float mCookieZOffset, Score::Score *mScore);
	public:
		CollectControll(Resource::ResourceBase *resourceLoad, Camera::MCamera *cCamera, float mHeight, float mAngle, float fZOffset, float mStepH,
			int32_t mMinCount, int32_t mMaxCount, //fZOffset = Cookie fZOffset
			glm::vec2 fFog, const float *fFogColor, int32_t mSectorsCount, float mRotateVel, float mMaxDelta,
			Resource::MapResource * mMapResource, Resource::TextureLoad * textureLoad,
			float fCookieMinYOffset, float mCookieZOffset, Score::Score *mScore,
			std::string mCollectName,// = "resource\\models\\collect\\sugar\\sugar.tdof",
			std::string mCoffeeCollectName);// = "resource\\models\\collect\\coffee\\coffee.tdof");
		~CollectControll();
		///////////////////////////////////////////////////////////////////////
		void Intersect(const Draw::CookieCollisionStruct &mCookieCollision);
		void Update(float fDeltaTime, float fGlobalTime, float fDeltaHeight);
		void Draw(void);
		void Present(void);
		///////////////////////////////////////////////////////////////////////
	};
}

