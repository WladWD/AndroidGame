#include "StoreModel.h"
#include "CookieDestroyStructWrite.h"
#include "LowPolyModelStore.h"

#pragma once
namespace Resource
{
	class StoreCookieModel : public StoreModel
	{
		////////////////////////////////////////////////////////////////////////////
		void WriteCookiePicesParameter(std::string mFileName, const MEngine::MObjects *mObjects, const MeshLoad::StandartMesh *mBuffers);
	public:
		StoreCookieModel(void);
		~StoreCookieModel();
		////////////////////////////////////////////////////////////////////////////
		void Write(std::string mFileDirectory);
	};
}

