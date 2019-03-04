#include "LowPolyModelBase.h"
#include <vector>

#pragma once
namespace Collision
{
	class LowPolyModel : public LowPolyModelBase
	{
		uint32_t mCurrent;
		/////////////////////////////////////////////////////
		std::vector<glm::vec3> mVertex;
		std::vector<uint16_t> mIndex;
		/////////////////////////////////////////////////////
	public:
		LowPolyModel(std::vector<glm::vec3>& mVertex, std::vector<uint16_t>& mIndex);
		~LowPolyModel();
		/////////////////////////////////////////////////////
		bool GetNextTriangle(glm::vec3 &mV0, glm::vec3 &mV1, glm::vec3 &mV2);
		/////////////////////////////////////////////////////
	};
}

