#include <Windows.h>
#include "StoreTexture.h"

#pragma once
namespace RIF
{
	class WriteTextureToRIF
	{
		StoreTexture *storeTexture;
		void RIFFileDirectory(string FileDirectory);
	public:
		WriteTextureToRIF(void);
		~WriteTextureToRIF();
		/////////////////////////////////////////////////////////////////////////////////////
		void WriteToRIF(string FileDirectory);
	};
}

