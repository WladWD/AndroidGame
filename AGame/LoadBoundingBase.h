#include "LoadStructure.h"
#include "CookieDestroyStruct.h"
#include "ResourceBase.h"

#pragma once
namespace Load
{
	class LoadBoundingBase
	{
	protected:
		Resource::ResourceBase * mResourceLoad;
		////////////////////////////////////////////////////////////////////////////////////////
		virtual void Load(std::string mName) = 0;
		////////////////////////////////////////////////////////////////////////////////////////
	public:
		LoadBoundingBase(std::string mFileName, Resource::ResourceBase * mResourceLoad);
		virtual ~LoadBoundingBase();
		////////////////////////////////////////////////////////////////////////////////////////
	};
}
