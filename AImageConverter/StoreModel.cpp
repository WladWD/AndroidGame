#include "StoreModel.h"


Resource::StoreModel::StoreModel(void)
{
}

Resource::StoreModel::~StoreModel()
{
}

bool Resource::StoreModel::CheckFile(std::string mName)
{
	size_t pos = mName.find('.');
	if (pos != (-1)) 
	{
		std::string ps = mName.substr(0, pos);
		std::string as = mName.substr(pos+1, mName.length() - pos);
		if (ps != "" && (as == "obj"))return true;
	}

	return false;
}

void Resource::StoreModel::SetOutputDirectory(std::string mFileDirectory)
{
	CreateDirectoryA("out", NULL);
	if (GetLastError() == ERROR_PATH_NOT_FOUND)
	{
		MessageBox(NULL, L"Error Create New Directory", L"Error", MB_OK);
		return;
	}

	size_t i = mFileDirectory.find('\\');
	std::string lDir = "out\\";
	while (i != (-1))
	{
		std::string nDir = lDir + mFileDirectory.substr(0, i);

		CreateDirectoryA(nDir.c_str(), NULL);
		if (GetLastError() == ERROR_PATH_NOT_FOUND)
		{
			MessageBox(NULL, L"Error Create New Directory", L"Error", MB_OK);
			return;
		}

		i = mFileDirectory.find('\\', i + 1);
	}
}

void Resource::StoreModel::WriteToFile(std::string mFileName, const MEngine::MObjects *mObjects, const MeshLoad::StandartMesh *mBuffers)
{
	std::ofstream mof(mFileName, std::ios::binary | std::ios::out);

	GLuint mVertSize = mBuffers->m_vertex.size() * sizeof(MeshLoad::MVertexTex);
	GLuint mIndexSize = mBuffers->m_index.size() * sizeof(GLushort);
	GLuint mDrawObjectCount = mObjects->mEntries.size();
	GLenum mIndexFormat = GL_UNSIGNED_SHORT;

	mof.write(reinterpret_cast<const char *>(&mVertSize), sizeof(GLuint));
	mof.write(reinterpret_cast<const char *>(&mIndexSize), sizeof(GLuint));
	mof.write(reinterpret_cast<const char *>(&mDrawObjectCount), sizeof(GLuint));
	mof.write(reinterpret_cast<const char *>(&mIndexFormat), sizeof(GLenum));

	for (register uint32_t i = 0; i < mDrawObjectCount; i++) 
	{
		DrawParam mDrawParam;
		mDrawParam.mIndexCount = mObjects->mEntries[i].GetIndexCount();
		mDrawParam.mIndexOffset = mObjects->mEntries[i].GetStartIndex();

		std::vector<GLuint> *mDiffuse;
		std::vector<bool> *mAlpha;
		const_cast<MEngine::MObjects *>(mObjects)->mEntries[i].GetMaterialID(&mDiffuse, &mAlpha);

		mDrawParam.mImageCount = mDiffuse->size();

		mof.write(reinterpret_cast<const char *>(&mDrawParam), sizeof(DrawParam));

		for (register uint32_t j = 0; j < mDrawParam.mImageCount; j++)
		{
			GLuint mDiffuseID = (*mDiffuse)[j];
			mof.write(reinterpret_cast<const char *>(&mDiffuseID), sizeof(GLuint));
		}
	}

	mof.write(reinterpret_cast<const char *>(mBuffers->m_vertex.data()), mVertSize);
	mof.write(reinterpret_cast<const char *>(mBuffers->m_index.data()), mIndexSize);

	mof.close();
}

void Resource::StoreModel::Write(std::string mFileDirectory)
{
	SetOutputDirectory(mFileDirectory);

	WIN32_FIND_DATAA wfd;
	HANDLE const firstFile = FindFirstFileA(mFileDirectory.c_str(), &wfd);

	MEngine::LoadModel *mLoadModel;

	std::string mLocalPath = mFileDirectory.substr(0, mFileDirectory.find_last_of('\\') + 1);

	if (firstFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			std::string mName = wfd.cFileName;

			if (CheckFile(mName))
			{
				//string mNewName = FileDirectory.substr(0, FileDirectory.length() - 2) + "\\" + mName;
				//storeTexture->LoadResource(mNewName, "out\\" + mNewName);
				mLoadModel = new MEngine::LoadModel(mLocalPath, mName, "out\\" + mLocalPath);

				mLoadModel->GetMesh();
				mLoadModel->GetObjects();
				//mLoadModel->GetResource();

				WriteToFile("out\\" + mLocalPath + mName.substr(0, mName.find_last_of('.')) + ".tdof", mLoadModel->GetObjects(), mLoadModel->GetMesh());

				delete mLoadModel;
			}
		} while (FindNextFileA(firstFile, &wfd) != NULL);

		FindClose(firstFile);
	}
}
