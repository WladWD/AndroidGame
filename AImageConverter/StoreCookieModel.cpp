#include "StoreCookieModel.h"


Resource::StoreCookieModel::StoreCookieModel(void) : StoreModel()
{
}

Resource::StoreCookieModel::~StoreCookieModel()
{
}

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

		for (register uint32_t j = mOffset; j < (mDrawParam.mIndexCount + mOffset); j++)//mDrawParam.mIndexCount
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

void Resource::StoreCookieModel::Write(std::string mFileDirectory)
{
	SetOutputDirectory(mFileDirectory);

	WIN32_FIND_DATAA wfd;
	HANDLE const firstFile = FindFirstFileA(mFileDirectory.c_str(), &wfd);

	LowPolyModelStore *mLPModel = new LowPolyModelStore();
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
				WriteCookiePicesParameter("out\\" + mLocalPath + mName.substr(0, mName.find_last_of('.')) + ".tdofsp", mLoadModel->GetObjects(), mLoadModel->GetMesh());
				
				delete mLoadModel;
			}
		} while (FindNextFileA(firstFile, &wfd) != NULL);

		FindClose(firstFile);
	}

	mLPModel->Write(mFileDirectory);
	delete mLPModel;
}
