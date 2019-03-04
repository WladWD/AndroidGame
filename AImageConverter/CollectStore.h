#include "StoreModel.h"
#include "CookieDestroyStructWrite.h"
#include "LowPolyModelStore.h"

#pragma once
namespace Resource
{
	class CollectStore : public StoreModel
	{
		////////////////////////////////////////////////////////////////////////////
		void WriteCollectParameter(std::string mFileName, const MEngine::MObjects *mObjects, const MeshLoad::StandartMesh *mBuffers);
	public:
		CollectStore(void);
		~CollectStore();
		////////////////////////////////////////////////////////////////////////////
		void Write(std::string mFileDirectory);
	};
}

