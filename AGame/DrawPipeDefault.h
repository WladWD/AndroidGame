#include "DrawPipeBase.h"
#include "ShaderPipeDefault.h"

#pragma once
namespace GameEngine
{
	class DrawPipeDefault : public DrawPipeBase
	{
		const char *mPipeTextureName;
		////////////////////////////////////////////////////////////////////////////////
		void InitAttrib(void);
		////////////////////////////////////////////////////////////////////////////////
	public:
		DrawPipeDefault(Resource::ResourceBase *resourceLoad, Resource::TextureLoad *textureLoad, Resource::MapResource *mMapResource, Camera::MCamera *cCamera,
			float fOffset, float fRadius, uint32_t V_Count, uint32_t U_Count,
			float fFogStart, float fFogRadius, const float *fFogColor);
		~DrawPipeDefault();
		////////////////////////////////////////////////////////////////////////////////
		void ReleaseResource(void);
		void ReCreateResource(Resource::ResourceBase *resourceLoad, Resource::TextureLoad *textureLoad, Resource::MapResource *mMapResource);
		////////////////////////////////////////////////////////////////////////////////
		void Draw(const glm::mat4 *mWorld);
		////////////////////////////////////////////////////////////////////////////////
	};
}

