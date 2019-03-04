#include "StoreModel.h"
#include "CookieDestroyStructWrite.h"
#include "LowPolyModelStore.h"

#pragma once
namespace Resource
{
	class BarrierStore : public StoreModel
	{
		////////////////////////////////////////////////////////////////////////////
		void WriteParameter(std::string mFileName, const MEngine::MObjects *mObjects, const MeshLoad::StandartMesh *mBuffers);
	public:
		BarrierStore(void);
		~BarrierStore();
		////////////////////////////////////////////////////////////////////////////
		void Write(std::string mFileDirectory);
	};
}

