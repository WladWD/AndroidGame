#include "MeshObject.h"


MEngine::MeshObject::MeshObject(void) 
{
	index_buffer_offset = 0;
	index_count = 0;

}

MEngine::MeshObject::~MeshObject() 
{
	mDiffuse_id.clear();
	mDiffuse_id.shrink_to_fit();

	use_alpha.clear();
	use_alpha.shrink_to_fit();
}

void MEngine::MeshObject::SetTextureID(uint32_t id, bool UseAlpha)
{
	mDiffuse_id.push_back(id);
	use_alpha.push_back(UseAlpha);
}

bool MEngine::MeshObject::IsUseAlpha(uint32_t id) const
{
	if (id < use_alpha.size())return use_alpha[id];
	else
		throw "out of range error";
}

void MEngine::MeshObject::GetMaterialID( std::vector<GLuint> ** Diffuse,  std::vector<bool> ** Aplha) 
{
	*Diffuse = &mDiffuse_id;
	*Aplha = &use_alpha;
}

void MEngine::MeshObject::SetIndexCount(uint32_t value) 
{
	index_count = value;
}

void MEngine::MeshObject::SetStartIndex(uint32_t value)
{
	index_buffer_offset = value;
}

uint32_t MEngine::MeshObject::GetIndexCount(void) const
{
	return index_count;
}

uint32_t MEngine::MeshObject::GetStartIndex(void) const
{
	return index_buffer_offset;
}
