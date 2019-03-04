#include "ReadCollisionObjectDataBase.h"
#include "CookieDestroyStruct.h"

#pragma once
namespace Bounding
{
	class ReadCoockieCollisionData : public ReadCollisionObjectDataBase
	{
		DrawCookie::CookieDestroy *mCookieDestroy;
		////////////////////////////////////////////////////////////////////
		void ReadCollisionData(std::string mFileName, Resource::ResourceBase * mResourceLoad);
	public:
		ReadCoockieCollisionData(std::string mFileName, Resource::ResourceBase * mResourceLoad,  DrawCookie::CookieDestroy *mCookieDestroy);
		~ReadCoockieCollisionData();
		////////////////////////////////////////////////////////////////////
	};
}

