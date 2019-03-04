#include "MCamera.h"


Camera::MCamera::MCamera(float fov, float fnear, float ffar, uint32_t width, uint32_t height, float offset, float fRotateAngle, float fTimeToRotate) : fFov(fov), 
fNear(fnear), fFar(ffar), width(width), height(height), fOffset(offset), fRotateAngle(fRotateAngle), fTimeToRotate(fTimeToRotate), fAspectRatio(float(width) / float(height)),
fTargetAngle(0.0f), fCurrentAngle(0.0f)
{
	mProj = glm::perspectiveFov(fov, float(width), float(height), fNear, fFar);
	InitViewMatrix();
	mProjView = mProj * mView;
}

Camera::MCamera::~MCamera()
{
}

void Camera::MCamera::ReCreateProjMatrix(float fov, float fnear, float ffar, uint32_t width, uint32_t height)
{
	fNear = fnear;
	fFar = ffar;
	fFov = fov;
	this->width = width; 
	this->height = height;
	fAspectRatio = float(width) / float(height);

	mProj = glm::perspectiveFov(fov, float(width), float(height), fNear, fFar);
}

void Camera::MCamera::Resize(uint32_t width, uint32_t height)
{
	this->width = width;
	this->height = height;

	mProj = glm::perspectiveFov(fFov, float(width), float(height), fNear, fFar);
	BuildViewMatrix();
}

void Camera::MCamera::InitViewMatrix()
{
	glm::mat4 mRotateMatrix(-1.0f, 0.0f, 0.0f, 0.0f, 
							0.0f, 0.0f, 1.0f, 0.0f,
							0.0f, 1.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 mTranslateMatrix( 1.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 1.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 1.0f, 0.0f,
								0.0f, 0.0f, fOffset, 1.0f);

	mView = glm::transpose(mRotateMatrix) * glm::inverse(mTranslateMatrix);

	/*glm::mat4 cCeck = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));*/
}

void Camera::MCamera::BuildViewMatrix(void)
{
	glm::mat4 mRot = glm::rotate(glm::mat4(1.0f), fCurrentAngle, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 mRotateMatrix(-1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);//mRot[0], mRot[2], mRot[1], glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	glm::mat4 mTranslateMatrix(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, fOffset, 1.0f);

	mView = glm::transpose(mRotateMatrix) * glm::inverse(mTranslateMatrix) * glm::inverse(mRot);

	mProjView = mProj * mView;
}

void Camera::MCamera::Update(float fDeltaTime_ms, float fGlobalTime_ms)
{
	if (fTargetAngle != fCurrentAngle) 
	{
		float fRotate = fDeltaTime_ms * fTimeToRotate;

		if (fCurrentAngle < fTargetAngle) 
		{
			fCurrentAngle += fRotate;

			if (fCurrentAngle > fTargetAngle)fCurrentAngle = fTargetAngle;
		}
		else if (fCurrentAngle > fTargetAngle)
		{
			fCurrentAngle -= fRotate;

			if (fCurrentAngle < fTargetAngle)fCurrentAngle = fTargetAngle;
		}
	}

	BuildViewMatrix();
}

void Camera::MCamera::UpdateOnly(float fDeltaTime_ms, float fGlobalTime_ms)
{
	BuildViewMatrix();
}

void Camera::MCamera::RotateRight(void)
{
	fTargetAngle += fRotateAngle;

	if (fTargetAngle >= pi2) 
	{
		fTargetAngle -= pi2;
		fCurrentAngle -= pi2;
	}
}

void Camera::MCamera::RotateLeft(void)
{
	fTargetAngle -= fRotateAngle;

	if (fTargetAngle <= -pi2)
	{
		fTargetAngle += pi2;
		fCurrentAngle += pi2;
	}
}

glm::vec3 Camera::MCamera::GetCameraPosition(void)
{
	return glm::vec3(glm::inverse(mView)[3]);
}

glm::mat4 Camera::MCamera::GetViewMatrix(void)
{
	return mView;
}

glm::mat4 Camera::MCamera::GetProjMatrix(void)
{
	return mProj;
}

glm::mat4 Camera::MCamera::GetProjViewMatrix(void) 
{
	return mProjView;
}

glm::mat4 Camera::MCamera::GetRotateMatrix(void)
{
	glm::mat4 mRot = glm::rotate(glm::mat4(1.0f), fCurrentAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	return mRot;
}

void Camera::MCamera::SetRandomNoise(glm::mat4 mTransform)
{
	mView *= glm::inverse(mTransform);
	mProjView = mProj * mView;
}
