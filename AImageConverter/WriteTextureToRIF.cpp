#include "WriteTextureToRIF.h"



RIF::WriteTextureToRIF::WriteTextureToRIF(void)
{
	storeTexture = new StoreTexture();

}

RIF::WriteTextureToRIF::~WriteTextureToRIF()
{
	delete storeTexture;
}

void RIF::WriteTextureToRIF::RIFFileDirectory(string FileDirectory)
{
	//string mNewDir = ("out\\" + FileDirectory.substr(0, FileDirectory.length() - 2));
	CreateDirectoryA("out", NULL);
	if (GetLastError() == ERROR_PATH_NOT_FOUND)
	{
		MessageBox(NULL, L"Error Create New Directory", L"Error", MB_OK);
		return;
	}

	size_t i = FileDirectory.find('\\');
	string lDir = "out\\";
	while (i != (-1))
	{
		string nDir = lDir + FileDirectory.substr(0, i);

		CreateDirectoryA(nDir.c_str(), NULL);
		if (GetLastError() == ERROR_PATH_NOT_FOUND)
		{
			MessageBox(NULL, L"Error Create New Directory", L"Error", MB_OK);
			return;
		}

		i = FileDirectory.find('\\', i+1);
	}
}

void RIF::WriteTextureToRIF::WriteToRIF(string FileDirectory) 
{	
	RIFFileDirectory(FileDirectory);

	WIN32_FIND_DATAA wfd;
	HANDLE const firstFile = FindFirstFileA(FileDirectory.c_str(), &wfd);

	if (firstFile != INVALID_HANDLE_VALUE) 
	{
		do 
		{
			string mName = wfd.cFileName;
			
			if (mName.find('.') != (-1) && isdigit(mName[0])) 
			{
				string mNewName = FileDirectory.substr(0, FileDirectory.length() - 2) + "\\" + mName;
				storeTexture->LoadResource(mNewName, "out\\" + mNewName);
			}
		} while (FindNextFileA(firstFile, &wfd) != NULL);

		FindClose(firstFile);
	}
}