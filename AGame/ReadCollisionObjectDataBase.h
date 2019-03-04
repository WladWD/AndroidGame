#include "ResourceLoad.h"
#include "Mesh.h"
#include "LoadStructure.h"
#include "MCamera.h"

#pragma once
namespace Bounding
{
	class ReadCollisionObjectDataBase
	{
	protected:
		////////////////////////////////////////////////////////////////////
		virtual void ReadCollisionData(std::string mFileName, Resource::ResourceBase * mResourceLoad) = 0;
	public:
		ReadCollisionObjectDataBase();
		virtual ~ReadCollisionObjectDataBase();
		////////////////////////////////////////////////////////////////////
	};
}

