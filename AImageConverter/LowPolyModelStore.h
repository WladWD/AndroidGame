#include "StoreModel.h"

#pragma once
namespace Resource
{
	class LowPolyModelStore : public StoreModel
	{
		////////////////////////////////////////////////////////////////////////////
		bool CheckFile(std::string mName);
		void WriteToFile(std::string mFileName, const MEngine::MObjects *mObjects, const MeshLoad::StandartMesh *mBuffers);
		//void WriteCookiePicesParameter(std::string mFileName, const MEngine::MObjects *mObjects, const MeshLoad::StandartMesh *mBuffers);
	public:
		LowPolyModelStore(void);
		~LowPolyModelStore();
		////////////////////////////////////////////////////////////////////////////
		void Write(std::string mFileDirectory);
	};
}

