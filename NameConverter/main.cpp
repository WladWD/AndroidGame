#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

const int lexem = 8;
string mReserverFileR[lexem] =
{
	"tifm",
	"tdof",
	"tdofsp",
	"tdofspc",
	"tdoflp",
	"tdofaabb",
	"rif",
	"glsl"
};

string mOutFileDir;

bool CheckDir(std::string mName) 
{
	size_t pos = mName.find('.');
	if (pos != (-1))
		return false;

	return true;
}

bool CheckFile(std::string mName)
{
	size_t pos = mName.find_last_of('.');
	if (pos != (-1))
	{
		std::string ps = mName.substr(0, pos);
		std::string as = mName.substr(pos + 1, mName.length() - pos);

		for(int k = 0; k < lexem; k++)
			if(ps != "" && (as == mReserverFileR[k]))
				return true;
	}

	return false;
}

void ConvertFile(string mCurrentDir, string mFileConvertName, string mFileName)
{
	string mNewFileConvertName;
	for (register uint32_t i = 0; i < mFileConvertName.length(); i++)
		mNewFileConvertName += mFileConvertName[i] == '\\' ? '.': mFileConvertName[i];
	CopyFileA((mCurrentDir + mFileName).c_str(), (mOutFileDir + mNewFileConvertName).c_str(), FALSE);
}

void Convert(string mFileDir, string mFileDirName, string mBaseDir)
{
	WIN32_FIND_DATAA wfd;
	HANDLE const firstFile = FindFirstFileA(mFileDir.c_str(), &wfd);
	if (firstFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			std::string mName = wfd.cFileName;

			if (CheckFile(mName))
				ConvertFile(mFileDirName, mBaseDir + mName, mName);
			else if (CheckDir(mName))
				Convert(mFileDirName + mName + "\\*", mFileDirName + mName + "\\", mBaseDir + mName + "\\");


		} while (FindNextFileA(firstFile, &wfd) != NULL);

		FindClose(firstFile);
	}
}

int main() 
{
	ifstream mfs("directory_name.txt");
	string dir;

	getline(mfs, mOutFileDir);

	while (!mfs.eof())
	{
		getline(mfs, dir);
		
		Convert(dir + "*", dir, "");
	}

	mfs.close();

	return 0;
}