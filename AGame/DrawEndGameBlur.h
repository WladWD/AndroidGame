#include "FramebufferResource.h"
#include "DrawFullScreenQuad.h"
#include "DrawBlur.h"
#include "MCamera.h"

#pragma once
namespace DrawFullScreen
{
	class DrawEndGameBlur
	{
		uint32_t mRealDimX, mRealDimY;
		//////////////////////////////////////////////////////////////////////////////////
		uint32_t mDimX, mDimY;
		//////////////////////////////////////////////////////////////////////////////////
		float mMipLevel;
		//////////////////////////////////////////////////////////////////////////////////
		glm::vec2 mOffset;
		//////////////////////////////////////////////////////////////////////////////////
		float mValue;
		//////////////////////////////////////////////////////////////////////////////////
		float mLocalTime;
		//////////////////////////////////////////////////////////////////////////////////
		float mDelayTime;
		float mDuriationTime;
		//////////////////////////////////////////////////////////////////////////////////
		FullScreenBuffer::FullScreenQuadBuffer *mFullScreenBuffer;
		//////////////////////////////////////////////////////////////////////////////////
		DrawBlur *mDrawBlur;
		//DrawFullScreenQuad *mDrawFullScreenQuad;
		//////////////////////////////////////////////////////////////////////////////////
		Framebuffer::FramebufferResource *mFramebufferResource;
		//////////////////////////////////////////////////////////////////////////////////
		uint32_t ToPow2(uint32_t mVal);
		void Init(Resource::ResourceBase *resourceLoad, uint32_t mDimX, uint32_t mDimY);
	public:
		DrawEndGameBlur(Resource::ResourceBase *resourceLoad, uint32_t mDimX, uint32_t mDimY, float mDelayTime, float mDuriationTime);
		~DrawEndGameBlur();
		//////////////////////////////////////////////////////////////////////////////////
		void Resize(uint32_t mDimX, uint32_t mDimY);
		//////////////////////////////////////////////////////////////////////////////////
		void ResetCameraFov(Camera::MCamera *mCamera);
		//////////////////////////////////////////////////////////////////////////////////
		bool IsEndBlur(void);
		//////////////////////////////////////////////////////////////////////////////////
		void BeginDrawBlurredObject(void);
		void EndDrawBlurredObject(void);
		//////////////////////////////////////////////////////////////////////////////////
		void Update(float fDeltaTime, float fGlobalTime);
		//////////////////////////////////////////////////////////////////////////////////
		void ShowBlur(void);
		//////////////////////////////////////////////////////////////////////////////////
	};
}

