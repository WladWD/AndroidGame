#include "LowPolyModel.h"


Collision::LowPolyModel::LowPolyModel(std::vector<glm::vec3>& mVertex, std::vector<uint16_t>& mIndex) : mCurrent(0), mVertex(mVertex), mIndex(mIndex)
{

}

Collision::LowPolyModel::~LowPolyModel()
{
	mVertex.clear();
	mIndex.clear();

	mVertex.shrink_to_fit();
	mIndex.shrink_to_fit();
}

bool Collision::LowPolyModel::GetNextTriangle(glm::vec3 & mV0, glm::vec3 & mV1, glm::vec3 & mV2)
{
	mV0 = mVertex[mCurrent++];
	mV1 = mVertex[mCurrent++];
	mV2 = mVertex[mCurrent++];

	if (mCurrent == mIndex.size())
		mCurrent = 0;

	return mCurrent;
}
