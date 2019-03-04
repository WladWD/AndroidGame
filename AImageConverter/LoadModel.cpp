#include "LoadModel.h"

MEngine::LoadModel::LoadModel(std::string mRelativePath, std::string mFileName, std::string mImageFileName, bool needWrite) : needWrite(needWrite)
{
	Assimp::Importer Importer;

	VNT_object = new MObjects();
	
	if(needWrite)
		mStoreTextureFormat = new Resource::StoreTextureStream(mImageFileName + mFileName.substr(0, mFileName.find_last_of('.')) + ".tifm");
	
	//aiProcess_FixInfacingNormals | aiProcess_GenSmoothNormals
	const aiScene* pScene = Importer.ReadFile(mRelativePath + "\\" + mFileName, aiProcess_Triangulate );//aiProcess_FlipUVs | aiProcess_GenSmoothNormals);// | aiProcess_OptimizeMeshes);

	if (pScene) InitScene(pScene, mRelativePath);
	else 
		MessageBox(NULL, L"File Not Load", L"", MB_OK);

	Importer.FreeScene();
}

MEngine::LoadModel::~LoadModel() 
{
	delete VNT_object;
	
	if (needWrite)
		delete mStoreTextureFormat;

	mesh_VNT.m_index.clear();
	mesh_VNT.m_vertex.clear();
}

const Resource::StoreTextureStream * MEngine::LoadModel::GetResource(void)
{
	return mStoreTextureFormat;
}

const MEngine::MObjects * MEngine::LoadModel::GetObjects(void)
{
	return VNT_object;
}

const MeshLoad::StandartMesh * MEngine::LoadModel::GetMesh(void)
{
	return &mesh_VNT;
}

void MEngine::LoadModel::InitScene(const aiScene* pScene, std::string mRelativePath)
{
	uint32_t mesh_count_VNT = 0;
	uint32_t index_count_VNT = 0;
	uint32_t vertex_count_VNT = 0;

	uint32_t base_vertex_VNT = 0;
	uint32_t base_index_VNT = 0;


	for (int i = 0; i < pScene->mNumMaterials; i++)
	{
		aiMaterial *pMaterial = pScene->mMaterials[i];
		//MeshLoad::ObjectMaterial mCurentMaterial;

		//aiColor4D mcol;
		//aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_SPECULAR, &mcol);//specular
		//mCurentMaterial.material.specular_color = vec4(mcol.r, mcol.g, mcol.b, 1.0f);

		//aiGetMaterialColor(pMaterial, AI_MATKEY_SHININESS, &mcol);//Ns - по неизввесным причинам Assimp загружает значение Ns * 4, поэтому считанное значение необходимо делить на 4
		//mCurentMaterial.material.specular_color.a = mcol.r * 0.25f;

		/*
		aiGetMaterialColor(pMaterial, AI_MATKEY_REFLECTIVITY, &mcol);//величина отражения света

		aiGetMaterialColor(pMaterial, AI_MATKEY_REFRACTI, &mcol);//величина преломления света

		aiGetMaterialColor(pMaterial, AI_MATKEY_OPACITY, &mcol);//величина прозрачности материала
		*/

		//aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_DIFFUSE, &mcol);//diffuse
		//mCurentMaterial.material.diffuse_color = vec4(mcol.r, mcol.g, mcol.b, 1.0f);

		//aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_AMBIENT, &mcol);//ambient
		//mCurentMaterial.material.diffuse_color.a = pow((mcol.r / mCurentMaterial.material.diffuse_color.r)*0.8f, 2.5f);

		//aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_EMISSIVE, &mcol);//Ke - emissive-материал способлый к свечению(для реализации использовать рассчет освещени на шейдерах, а затем размытие)
		//mCurentMaterial.material.emissive_color = vec4(mcol.r, mcol.g, mcol.b, 1.0f);

		//mCurentMaterial.diffuse_map_id = 0;
		//mCurentMaterial.bump_map_id = 0;
		//mCurentMaterial.reflaction_map_id = 0;
		//mCurentMaterial.specular_map_id = 0;

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			uint32_t mCountTex = pMaterial->GetTextureCount(aiTextureType_DIFFUSE);
			for (register uint32_t i = 0; i < mCountTex; i++) 
			{
				aiString Path;

				if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path,
					NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
				{
					std::string FullPath = mRelativePath + Path.data;

					if (needWrite)
						mStoreTextureFormat->LoadResource(FullPath);
						//mCurentMaterial.diffuse_map_id = load_texture->LoadResource(FullPath);
				}
			}
		}

		

		//mresource->mMaterial.push_back(mCurentMaterial);
		//mresource->mMaterial[i] = mCurentMaterial;
	}

	for (register uint32_t i = 0; i < pScene->mNumMeshes; i++) 
	{
		if (pScene->mMeshes[i]->HasTextureCoords(0))
		{
			mesh_count_VNT++;
			index_count_VNT += pScene->mMeshes[i]->mNumFaces;
			vertex_count_VNT += pScene->mMeshes[i]->mNumVertices;
		}
	}

	index_count_VNT *= 3;

	VNT_object->mEntries.resize(mesh_count_VNT);
	mesh_VNT.m_vertex.resize(vertex_count_VNT);
	mesh_VNT.m_index.resize(index_count_VNT);


	register uint32_t i = 0, j = 0, k = 0;
	for (; i < pScene->mNumMeshes; i++) 
	{
		if (pScene->mMeshes[i]->HasTextureCoords(0))
		{
				const aiMesh *paiMesh = pScene->mMeshes[i];

				aiMaterial *pMaterial = pScene->mMaterials[paiMesh->mMaterialIndex];
				if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
				{
					uint32_t mCountTex = pMaterial->GetTextureCount(aiTextureType_DIFFUSE);
					for (register uint32_t i = 0; i < mCountTex; i++)
					{
						aiString Path;

						if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path,
							NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
						{
							std::string FullPath = mRelativePath + Path.data;

							if (needWrite)
								VNT_object->mEntries[j].SetTextureID(mStoreTextureFormat->LoadResource(FullPath), false);
						}
					}
				}

				//VNT_object->mEntries[j].SetObjectName(paiMesh->mName.C_Str(), paiMesh->mName.length);
				//VNT_object->mEntries[j].SetVertexCount(paiMesh->mNumVertices);
				//VNT_object->mEntries[j].SetVertexStart(base_vertex_VNT);
				
				VNT_object->mEntries[j].SetStartIndex(base_index_VNT * sizeof(GLushort));
				VNT_object->mEntries[j].SetIndexCount(paiMesh->mNumFaces * 3);

				//VNT_object->mEntries[j].SetFaceCount(paiMesh->mNumFaces);
				//VNT_object->mEntries[j].SetType(MeshLoad::ID_Face::TRIANGLE_NTEX);
				//VNT_object->mEntries[j].SetMaterialID(paiMesh->mMaterialIndex);

				//pScene->mMaterials[paiMesh->mMaterialIndex].

				InitMeshVNT(base_vertex_VNT, base_index_VNT, paiMesh);

				base_vertex_VNT += paiMesh->mNumVertices;
				base_index_VNT += paiMesh->mNumFaces * 3;

				//MeshLoad::ObjectMaterial material = mresource->mMaterial[paiMesh->mMaterialIndex];

				//bool use_clip_alpha = (mresource->texture_map->GetAlphaMap(material.diffuse_map_id)) && material.diffuse_map_id ? true : false;
				//bool use_alpha = (mresource->texture_map->GetAlphaMap(material.diffuse_map_id)) && material.diffuse_map_id ? true : false;

				/*VNT_object->mEntries[j].SetUseReflaction(use_reflect);
				VNT_object->mEntries[j].SetUseDiffuse(use_diffuse);
				VNT_object->mEntries[j].SetUseSpecular(use_specular);
				VNT_object->mEntries[j].SetClipOpacity(use_clip_alpha);
				VNT_object->mEntries[j].SetUseAlpha(false);
				VNT_object->mEntries[j].SetUseBump(false);
				VNT_object->mEntries[j].SetUseHeightAlpha(false);*/

				j++;
		}
	}


	if (needWrite)
		mStoreTextureFormat->SetEnd();
	//MCreateBufferVNT();
}

void MEngine::LoadModel::InitMeshVNT(uint32_t base_vertex, uint32_t base_index, const aiMesh *paiMesh)
{
	//здесь собираеться 1 обьект, так что при необходимости можно его выделить отсюда в отдельный буффер(например если обьект динамичен), (для скелетной анимации)

	for (register uint32_t i = 0; i < paiMesh->mNumVertices; i++) 
	{
		aiVector3D vert_pos = paiMesh->mVertices[i];
		//aiVector3D vert_norm = paiMesh->mNormals[i];
		aiVector3D vert_tex = paiMesh->mTextureCoords[0][i];

		mesh_VNT.m_vertex[base_vertex + i].l_pos = glm::vec3(vert_pos.x, vert_pos.y, vert_pos.z);
		//mesh_VNT.m_vertex[base_vertex + i].l_norm = normalize(glm::vec3(vert_norm.x, vert_norm.y, vert_norm.z));
		mesh_VNT.m_vertex[base_vertex + i].l_tex = glm::vec2(vert_tex.x, vert_tex.y);//1.0f - vert_tex.y);
	}

	for (register uint32_t i = 0; i < paiMesh->mNumFaces; i++)
	{
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);

		mesh_VNT.m_index[base_index + i * 3 + 0] = Face.mIndices[0] + base_vertex;// - base_vertex
		mesh_VNT.m_index[base_index + i * 3 + 1] = Face.mIndices[1] + base_vertex;// - base_vertex
		mesh_VNT.m_index[base_index + i * 3 + 2] = Face.mIndices[2] + base_vertex;// - base_vertex
	}
}

/*uint32_t index_count = mesh_VNT.m_index.size();
	uint32_t vertex_count = mesh_VNT.m_vertex.size();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_VNT.m_index.size() * sizeof(uint32_t), &mesh_VNT.m_index[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, mesh_VNT.m_vertex.size() * sizeof(MeshLoad::VERTEX), &mesh_VNT.m_vertex[0], GL_STATIC_DRAW);
	*/
/*
void MEngine::LoadModel::MCreateBufferVNT(void) 
{
	VNT_object->IB = 0;
	VNT_object->VB = 0;
	VNT_object->VAO = 0;

	uint32_t index_count = mesh_VNT.m_index.size();
	uint32_t vertex_count = mesh_VNT.m_vertex.size();

	if (!index_count || !vertex_count)return;

	glCreateBuffers(1, &VNT_object->IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VNT_object->IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_VNT.m_index.size() * sizeof(uint32_t), &mesh_VNT.m_index[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &VNT_object->VAO);
	glBindVertexArray(VNT_object->VAO);

	glCreateBuffers(1, &VNT_object->VB);
	glBindBuffer(GL_ARRAY_BUFFER, VNT_object->VB);
	glBufferData(GL_ARRAY_BUFFER, mesh_VNT.m_vertex.size() * sizeof(MeshLoad::VERTEX), &mesh_VNT.m_vertex[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
*/
/*
void MEngine::LoadModel::SortVNTObject(void)
{

	uint32_t clip_offset = (-1);
	for (register uint32_t i = 0; i < VNT_object->mEntries.size(); i++)
	{
		if (!VNT_object->mEntries[i].IsClipOpacity())
		{
			clip_offset++;
			swap(VNT_object->mEntries[clip_offset], VNT_object->mEntries[i]);
		}
	}
	clip_offset++;
	
	uint32_t c1, c2, c3, c4, c5, c0, c6, c7;
	SortVNTObject(0, clip_offset, c0, c1, c2, c3);
	SortVNTObject(clip_offset, VNT_object->mEntries.size(), c4, c5, c6, c7);

	//[0;c0)
	//[c0;c1)
	//[c1;c2)
	//[c2;c3)

	//[c3;c4)
	//[c4;c5)
	//[c5;c6)
	//[c6;c7)
	VNT_object_list.c0 = c0;
	VNT_object_list.c1 = c1;
	VNT_object_list.c2 = c2;
	VNT_object_list.c3 = c3;
	VNT_object_list.c4 = c4;
	VNT_object_list.c5 = c5;
	VNT_object_list.c6 = c6;
	VNT_object_list.c7 = c7;
	VNT_object_list.clip_offset = clip_offset;
}

void MEngine::LoadModel::SortVNTObject(uint32_t start, uint32_t end, uint32_t &c1, uint32_t &c2, uint32_t &c3, uint32_t &c4)
{
	
	int32_t ai = (-1) + start;//categori 1)
	int32_t bi = (-1) + start;//categori 2)
	int32_t ci = (-1) + start;//categori 3)
	int32_t di = (-1) + start;//categori 4)
	for (register int32_t i = start; i < end; i++)
	{
		if (!VNT_object->mEntries[i].IsUseDiffuse())
		{
			ai++;
			bi++;
			ci++;
			di++;
			swap(VNT_object->mEntries[bi], VNT_object->mEntries[ai]);
			swap(VNT_object->mEntries[ci], VNT_object->mEntries[ai]);
			swap(VNT_object->mEntries[i], VNT_object->mEntries[ai]);
		}
		else if (VNT_object->mEntries[i].IsUseDiffuse() && !VNT_object->mEntries[i].IsUseReflaction() && !VNT_object->mEntries[i].IsUseSpecular())
		{
			bi++;
			ci++;
			di++;
			swap(VNT_object->mEntries[ci], VNT_object->mEntries[bi]);
			swap(VNT_object->mEntries[i], VNT_object->mEntries[bi]);
		}
		else if (VNT_object->mEntries[i].IsUseDiffuse() && !VNT_object->mEntries[i].IsUseReflaction() && VNT_object->mEntries[i].IsUseSpecular())
		{
			ci++;
			di++;
			swap(VNT_object->mEntries[i], VNT_object->mEntries[ci]);
		}
		else if(VNT_object->mEntries[i].IsUseDiffuse() && VNT_object->mEntries[i].IsUseReflaction() && !VNT_object->mEntries[i].IsUseSpecular()) di++;
		else MessageBox(NULL, L"Error", L"Errors in sorting meshs", MB_ICONERROR | MB_OK);
	}

	c1 = ai + 1;
	c2 = bi + 1;
	c3 = ci + 1;
	c4 = di + 1;
}
*/