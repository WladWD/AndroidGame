#include "LowPolyModelStore.h"


Resource::LowPolyModelStore::LowPolyModelStore(void) : StoreModel()
{
}

Resource::LowPolyModelStore::~LowPolyModelStore()
{
}
/*
void Resource::StoreCookieModel::WriteCookiePicesParameter(std::string mFileName, const MEngine::MObjects *mObjects, const MeshLoad::StandartMesh *mBuffers)
{
	std::ofstream mof(mFileName, std::ios::binary | std::ios::out);

	CookieDestroy mCookieDestroy;

	GLuint mVertSize = mBuffers->m_vertex.size() * sizeof(MeshLoad::MVertexTex);
	GLuint mIndexSize = mBuffers->m_index.size() * sizeof(GLushort);
	GLuint mDrawObjectCount = mObjects->mEntries.size();
	GLenum mIndexFormat = GL_UNSIGNED_SHORT;

	glm::vec3 gMinVec, gMaxVec;
	gMinVec = gMaxVec = mBuffers->m_vertex[0].l_pos;

	for (register uint32_t i = 0; i < mDrawObjectCount; i++)
	{
		DrawParam mDrawParam;
		mDrawParam.mIndexCount = mObjects->mEntries[i].GetIndexCount();
		mDrawParam.mIndexOffset = mObjects->mEntries[i].GetStartIndex();

		uint32_t mOffset = mDrawParam.mIndexOffset / sizeof(GLushort);

		glm::vec3 minVec, maxVec;
		minVec = maxVec = mBuffers->m_vertex[mOffset].l_pos;

		for (register uint32_t j = mOffset; j < mDrawParam.mIndexCount; j++)
		{
			glm::vec3 mPos = mBuffers->m_vertex[j].l_pos;
			minVec = glm::min(minVec, mPos);
			maxVec = glm::max(maxVec, mPos);

			gMinVec = glm::min(gMinVec, mPos);
			gMaxVec = glm::max(gMaxVec, mPos);
		}

		mCookieDestroy.mPicesCenter[i % COOKIE_PICES_COUNT] = glm::vec4((maxVec + minVec) * 0.5f, 0.0f);
	}

	glm::vec3 mSphereCenter = (gMaxVec + gMinVec) * 0.5f;
	float Radius = 0.0f;
	for (register uint32_t i = 0; i < mBuffers->m_vertex.size(); i++)
		Radius = glm::max(glm::length(mSphereCenter - mBuffers->m_vertex[i].l_pos), Radius);

	mCookieDestroy.mCenter = glm::vec4(mSphereCenter, Radius);

	mof.write(reinterpret_cast<const char *>(&mCookieDestroy), sizeof(mCookieDestroy));

	mof.close();
}
*/

void Resource::LowPolyModelStore::WriteToFile(std::string mFileName, const MEngine::MObjects *mObjects, const MeshLoad::StandartMesh *mBuffers)
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
		DrawParamLowPoly mDrawParam;
		mDrawParam.mIndexCount = mObjects->mEntries[i].GetIndexCount();
		mDrawParam.mIndexOffset = mObjects->mEntries[i].GetStartIndex();

		mof.write(reinterpret_cast<const char *>(&mDrawParam), sizeof(DrawParamLowPoly));
	}

	mof.write(reinterpret_cast<const char *>(mBuffers->m_vertex.data()), mVertSize);
	mof.write(reinterpret_cast<const char *>(mBuffers->m_index.data()), mIndexSize);

	mof.close();
}

bool Resource::LowPolyModelStore::CheckFile(std::string mName)
{
	size_t pos = mName.find('.');
	if (pos != (-1))
	{
		std::string ps = mName.substr(0, pos);
		std::string as = mName.substr(pos + 1, mName.length() - pos);
		if (ps != "" && (as == "objlp"))return true;
	}

	return false;
}

void Resource::LowPolyModelStore::Write(std::string mFileDirectory)
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
			//std::string mCName = mName.substr(0, mName.find_last_of('.')) + "lp.obj";
			if (CheckFile(mName))// && mName.substr(0, mName.find_last_of('.')) == ".")
			{
				//string mNewName = FileDirectory.substr(0, FileDirectory.length() - 2) + "\\" + mName;
				//storeTexture->LoadResource(mNewName, "out\\" + mNewName);
				mLoadModel = new MEngine::LoadModel(mLocalPath, mName, "out\\" + mLocalPath, false);

				//mLoadModel->GetMesh();
				//mLoadModel->GetObjects();
				//mLoadModel->GetResource();

				WriteToFile("out\\" + mLocalPath + mName.substr(0, mName.find_last_of('.')) + ".tdoflp", mLoadModel->GetObjects(), mLoadModel->GetMesh());
				//WriteCookiePicesParameter("out\\" + mLocalPath + mName.substr(0, mName.find_last_of('.')) + ".tdofp", mLoadModel->GetObjects(), mLoadModel->GetMesh());
				delete mLoadModel;
			}
		} while (FindNextFileA(firstFile, &wfd) != NULL);

		FindClose(firstFile);
	}
}
