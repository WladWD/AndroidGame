#include "Object.h"


Bounding::Object::Object(Resource::ResourceBase * mResourceLoad, std::string mResourceName) : ObjectBase(), mResourceName(mResourceName)
{
	Init(mResourceName, mResourceLoad);
	//PackToOOBB();
}

Bounding::Object::~Object()
{
	/*delete[] vertexBuffer;
	delete[] indexBuffer;*/
	ReleaseResource();
}

void Bounding::Object::ReleaseResource(void)
{
	delete mImagesResource;
	delete[] mObjects;

	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);

	delete[] vertexBuffer;
	delete[] indexBuffer;
}

void Bounding::Object::ReCreateResource(Resource::ResourceBase * resourceLoad)
{
	Init(mResourceName, resourceLoad);
}

void Bounding::Object::Init(std::string mResourceName, Resource::ResourceBase * mResourceLoad)
{
	Resource::ResourceLoad *mModel = new Resource::ResourceLoad(mResourceName, mResourceLoad);

	mImagesResource = mModel->GetImagesResource();
	mIndexBuffer = mModel->GetIndexBuffer(mIndexFormat);
	mVertexBuffer = mModel->GetVertexBuffer();
	mObjects = mModel->GetModelObjects(mDrawObjectCount);

	indexBuffer = reinterpret_cast<GLushort *>(mModel->GetIndexBufferData(mIndexCount));
	mIndexCount /= sizeof(GLushort);

	vertexBuffer = reinterpret_cast<Mesh::VTMesh *>(mModel->GetVertexBufferData(mVertexCount));
	mVertexCount /= sizeof(Mesh::VTMesh);

	delete mModel;
}

Mesh::VTMesh *Bounding::Object::GetVertexBuffer()
{
	return vertexBuffer;
}

GLushort *Bounding::Object::GetIndexBuffer()
{
	return indexBuffer;
}
///*
//void Bounding::BoundingObject::PackToOOBB(void)
//{
//	float min_x, min_y, min_z;
//	float s_x = 0.0f, s_y = 0.0f, s_z = 0.0f;
//	float max_x, max_y, max_z;
//
//	glm::vec3 mPos = vertexBuffer[0].gWorldPos;
//
//	min_x = max_x = mPos.x;
//	min_y = max_y = mPos.y;
//	min_z = max_z = mPos.z;
//
//
//	for (register uint32_t i = 1; i < mVertexCount; i++) 
//	{
//		mPos = vertexBuffer[i].gWorldPos;
//
//		s_x += mPos.x;
//		s_y += mPos.y;
//		s_z += mPos.z;
//
//		min_x = glm::min(min_x, mPos.x);
//		min_y = glm::min(min_y, mPos.y);
//		min_z = glm::min(min_z, mPos.z);
//
//		max_x = glm::max(max_x, mPos.x);
//		max_y = glm::max(max_y, mPos.y);
//		max_z = glm::max(max_z, mPos.z);
//	}
//
//	mOOBB.mCenter = glm::vec4(s_x / float(mVertexCount), s_y / float(mVertexCount), s_z / float(mVertexCount), 1.0f);
//	//mOOBB.mCenter = glm::vec4(min_x + max_x, min_y + max_y, min_z + max_z, 1.0f);
//	//mOOBB.mCenter *= glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
//	mOOBB.mDim = glm::vec4(max_x, max_y, max_z, 1.0f) - mOOBB.mCenter;
//	mOOBB.mDim.w = 0.0f;
//}*/
///*
//
//   //система координат B
//   for( k=0 ; k<3 ; k++ )
//   {
//      ra = a[0]*fabs(R[0][k]) + a[1]*fabs(R[1][k]) + a[2]*fabs(R[2][k]);
//      rb = b[k];
//      t = fabs( T[0]*R[0][k] + T[1]*R[1][k] + T[2]*R[2][k] );
//      if ( t > ra + rb )
//         return FALSE;
//   }
//
//   //9 векторных произведений
//   //L = A0 x B0
//   ra = a[1]*fabs(R[2][0]) + a[2]*fabs(R[1][0]);
//   rb = b[1]*fabs(R[0][2]) + b[2]*fabs(R[0][1]);
//   t = fabs( T[2]*R[1][0] - T[1]*R[2][0] );
//   if ( t > ra + rb )
//      return FALSE;
//   
//   //L = A0 x B1
//   ra = a[1]*fabs(R[2][1]) + a[2]*fabs(R[1][1]);
//   rb = b[0]*fabs(R[0][2]) + b[2]*fabs(R[0][0]);
//   t = fabs( T[2]*R[1][1] - T[1]*R[2][1] );
//   if ( t > ra + rb )
//      return FALSE;
//   
//   //L = A0 x B2
//   ra = a[1]*fabs(R[2][2]) + a[2]*fabs(R[1][2]);
//   rb = b[0]*fabs(R[0][1]) + b[1]*fabs(R[0][0]);
//   t = fabs( T[2]*R[1][2] - T[1]*R[2][2] );
//   if ( t > ra + rb )
//      return FALSE;
//
//   //L = A1 x B0
//   ra = a[0]*fabs(R[2][0]) + a[2]*fabs(R[0][0]);
//   rb = b[1]*fabs(R[1][2]) + b[2]*fabs(R[1][1]);
//   t = fabs( T[0]*R[2][0] - T[2]*R[0][0] );
//   if ( t > ra + rb )
//      return FALSE;
//
//   //L = A1 x B1
//   ra = a[0]*fabs(R[2][1]) + a[2]*fabs(R[0][1]);
//   rb = b[0]*fabs(R[1][2]) + b[2]*fabs(R[1][0]);
//   t = fabs( T[0]*R[2][1] - T[2]*R[0][1] );
//   if ( t > ra + rb )
//      return FALSE;
//
//   //L = A1 x B2
//   ra = a[0]*fabs(R[2][2]) + a[2]*fabs(R[0][2]);
//   rb = b[0]*fabs(R[1][1]) + b[1]*fabs(R[1][0]);
//   t = fabs( T[0]*R[2][2] - T[2]*R[0][2] );
//   if ( t > ra + rb )
//      return FALSE;
//
//   //L = A2 x B0
//   ra = a[0]*fabs(R[1][0]) + a[1]*fabs(R[0][0]);
//   rb = b[1]*fabs(R[2][2]) + b[2]*fabs(R[2][1]);
//   t = fabs( T[1]*R[0][0] - T[0]*R[1][0] );
//   if ( t > ra + rb )
//      return FALSE;
//
//   //L = A2 x B1
//   ra = a[0]*fabs(R[1][1]) + a[1]*fabs(R[0][1]);
//   rb = b[0] *fabs(R[2][2]) + b[2]*fabs(R[2][0]);
//   t = fabs( T[1]*R[0][1] - T[0]*R[1][1] );
//   if ( t > ra + rb )
//      return FALSE;
//
//   //L = A2 x B2
//   ra = a[0]*fabs(R[1][2]) + a[1]*fabs(R[0][2]);
//   rb = b[0]*fabs(R[2][1]) + b[1]*fabs(R[2][0]);
//   t = fabs( T[1]*R[0][2] - T[0]*R[1][2] );
//   if ( t > ra + rb )
//      return FALSE;
//
//   return TRUE;*/
////http://www.gamasutra.com/view/feature/131790/simple_intersection_tests_for_games.php?page=5
////http://www.randygaul.net/2014/05/22/deriving-obb-to-obb-intersection-sat/
////http://www.gamedev.ru/code/forum/?id=52254
////http://www.gamedev.ru/code/forum/?id=52254
////http://gdlinks.hut.ru/cdfaq/aabb.shtml
////http://steps3d.narod.ru/tutorials/tutorial-obb.html
////http://gdlinks.hut.ru/cdfaq/obb.shtml#obb
////https://xakep.ru/2002/02/13/14503/
//bool Bounding::BoundingObject::OOBBIntersect(const Mesh::OOBB *mObject1, const Mesh::OOBB *mObject2, const glm::mat4* mWorld1, const glm::mat4 *mWorld2)
//{
//	glm::vec3 a = glm::vec3((*mWorld1) * mObject1->mDim),//glm::transpose(glm::inverse
//		b = glm::vec3((*mWorld2) * mObject2->mDim),//glm::transpose(glm::inverse
//		Pa = glm::vec3((*mWorld1) * mObject1->mCenter),
//		Pb = glm::vec3((*mWorld2) * mObject2->mCenter);
//
//
//	glm::vec3 axis[3] = 
//	{	glm::vec3(1.0f, 0.0f, 0.0f),
//		glm::vec3(0.0f, 1.0f, 0.0f),
//		glm::vec3(0.0f, 0.0f, 1.0f) };
//
//	glm::vec3 A[3];
//	glm::vec3 B[3];
//	for (int i = 0; i < 3; i++)
//	{
//		A[i] = glm::normalize(glm::vec3((*mWorld1) * glm::vec4(axis[i], 0.0f)));
//		B[i] = glm::normalize(glm::vec3((*mWorld2) * glm::vec4(axis[i], 0.0f)));
//	}
//	/*glm::mat4 mA = (*mWorld1);//glm::transpose(glm::inverse(*mWorld1));//(*mWorld1);//
//	glm::mat4 mB = (*mWorld2);//glm::transpose(glm::inverse(*mWorld2));//(*mWorld2);//
//	for (int i = 0; i < 3; i++)
//	{
//		mA[i] = glm::vec4((glm::vec3(mA[i])), 0.0f);//glm::vec4(glm::normalize(glm::vec3(mA[i])), 0.0f);
//		mB[i] = glm::vec4((glm::vec3(mB[i])), 0.0f); //glm::vec4(glm::normalize(glm::vec3(mB[i])), 0.0f);
//	}
//
//	glm::mat3 A, B;
//
//
//	for (int i = 0; i < 3; i++) 
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			A[i][j] = (mA)[i][j];
//			B[i][j] = (mB)[i][j];
//		}
//	}
//	a = A * glm::vec3(mObject1->mDim);
//	b = B * glm::vec3(mObject2->mDim);
//
//	for (int j = 0; j < 3; j++)
//	{
//		a[j] = glm::abs(a[j]);
//		b[j] = glm::abs(b[j]);
//	}
//
//	//смещение в мировой системе координат
//	glm::vec3 v = Pb - Pa;
//	//смещение в системе координат А
//	glm::vec3 T = A * v;
//	//создаем матрицу поворота B относительно А
//	glm::mat3 R = (A * glm::transpose(B));// //glm::inverse(B));//glm::transpose(B));
//	*/
//					  //calculate rotation matrix
//	//for (int i = 0; i<3; i++)
//		//for (int k = 0; k<3; k++)
//			//R[i][k] = A[i].dot(B[k]);
//
//	//смещение в мировой системе координат
//	glm::vec3 v = Pb - Pa;
//	//смещение в системе координат А
//	glm::vec3 T(glm::dot(v, A[0]), glm::dot(v, A[1]), glm::dot(v, A[2]));//A * v;
//	long i, k;
//	float R[3][3];
//	for (i = 0; i<3; i++)
//		for (k = 0; k<3; k++)
//			R[i][k] = glm::dot(A[i], B[k]);
//
//
//	float ra, rb, t;
//	for (i = 0; i<3; i++)
//	{
//
//
//
//		ra = a[i];
//
//		rb =
//			b[0] * fabs(R[i][0]) + b[1] * fabs(R[i][1]) + b[2] * fabs(R[i][2]);
//
//		t = fabs(T[i]);
//
//		if (t > ra + rb)
//			return false;
//
//	}
//
//	//B's basis vectors
//	for (k = 0; k<3; k++)
//	{
//
//
//
//		ra =
//			a[0] * fabs(R[0][k]) + a[1] * fabs(R[1][k]) + a[2] * fabs(R[2][k]);
//
//		rb = b[k];
//
//		t =
//			fabs(T[0] * R[0][k] + T[1] * R[1][k] +
//				T[2] * R[2][k]);
//
//		if (t > ra + rb)
//			return false;
//
//	}
//
//	//9 cross products
//
//	//L = A0 x B0
//	ra =
//		a[1] * fabs(R[2][0]) + a[2] * fabs(R[1][0]);
//
//	rb =
//		b[1] * fabs(R[0][2]) + b[2] * fabs(R[0][1]);
//
//	t =
//		fabs(T[2] * R[1][0] -
//			T[1] * R[2][0]);
//
//	if (t > ra + rb)
//		return false;
//
//	//L = A0 x B1
//	ra =
//		a[1] * fabs(R[2][1]) + a[2] * fabs(R[1][1]);
//
//	rb =
//		b[0] * fabs(R[0][2]) + b[2] * fabs(R[0][0]);
//
//	t =
//		fabs(T[2] * R[1][1] -
//			T[1] * R[2][1]);
//
//	if (t > ra + rb)
//		return false;
//
//	//L = A0 x B2
//	ra =
//		a[1] * fabs(R[2][2]) + a[2] * fabs(R[1][2]);
//
//	rb =
//		b[0] * fabs(R[0][1]) + b[1] * fabs(R[0][0]);
//
//	t =
//		fabs(T[2] * R[1][2] -
//			T[1] * R[2][2]);
//
//	if (t > ra + rb)
//		return false;
//
//	//L = A1 x B0
//	ra =
//		a[0] * fabs(R[2][0]) + a[2] * fabs(R[0][0]);
//
//	rb =
//		b[1] * fabs(R[1][2]) + b[2] * fabs(R[1][1]);
//
//	t =
//		fabs(T[0] * R[2][0] -
//			T[2] * R[0][0]);
//
//	if (t > ra + rb)
//		return false;
//
//	//L = A1 x B1
//	ra =
//		a[0] * fabs(R[2][1]) + a[2] * fabs(R[0][1]);
//
//	rb =
//		b[0] * fabs(R[1][2]) + b[2] * fabs(R[1][0]);
//
//	t =
//		fabs(T[0] * R[2][1] -
//			T[2] * R[0][1]);
//
//	if (t > ra + rb)
//		return false;
//
//	//L = A1 x B2
//	ra =
//		a[0] * fabs(R[2][2]) + a[2] * fabs(R[0][2]);
//
//	rb =
//		b[0] * fabs(R[1][1]) + b[1] * fabs(R[1][0]);
//
//	t =
//		fabs(T[0] * R[2][2] -
//			T[2] * R[0][2]);
//
//	if (t > ra + rb)
//		return false;
//
//	//L = A2 x B0
//	ra =
//		a[0] * fabs(R[1][0]) + a[1] * fabs(R[0][0]);
//
//	rb =
//		b[1] * fabs(R[2][2]) + b[2] * fabs(R[2][1]);
//
//	t =
//		fabs(T[1] * R[0][0] -
//			T[0] * R[1][0]);
//
//	if (t > ra + rb)
//		return false;
//
//	//L = A2 x B1
//	ra =
//		a[0] * fabs(R[1][1]) + a[1] * fabs(R[0][1]);
//
//	rb =
//		b[0] * fabs(R[2][2]) + b[2] * fabs(R[2][0]);
//
//	t =
//		fabs(T[1] * R[0][1] -
//			T[0] * R[1][1]);
//
//	if (t > ra + rb)
//		return false;
//
//	//L = A2 x B2
//	ra =
//		a[0] * fabs(R[1][2]) + a[1] * fabs(R[0][2]);
//
//	rb =
//		b[0] * fabs(R[2][1]) + b[1] * fabs(R[2][0]);
//
//	t =
//		fabs(T[1] * R[0][2] -
//			T[0] * R[1][2]);
//
//	if (t > ra + rb)
//		return false;
//
//	/*no separating axis found,
//	the two boxes overlap */
//
//	return true;
//	/*
//	//система координат А
//	for (i = 0; i<3; i++)
//	{
//		ra = a[i];
//		rb = b[0] * fabs(R[i][0]) + b[1] * fabs(R[i][1]) + b[2] * fabs(R[i][2]);
//		t = fabs(T[i]);
//		if (t > ra + rb)
//			return FALSE;
//	}
//	//система координат B
//	for (k = 0; k<3; k++)
//	{
//		ra = a[0] * fabs(R[0][k]) + a[1] * fabs(R[1][k]) + a[2] * fabs(R[2][k]);
//		rb = b[k];
//		t = fabs(T[0] * R[0][k] + T[1] * R[1][k] + T[2] * R[2][k]);
//		if (t > ra + rb)
//			return FALSE;
//	}
//	//9 векторных произведений
//	//L = A0 x B0
//	ra = a[1] * fabs(R[2][0]) + a[2] * fabs(R[1][0]);
//	rb = b[1] * fabs(R[0][2]) + b[2] * fabs(R[0][1]);
//	t = fabs(T[2] * R[1][0] - T[1] * R[2][0]);
//	if (t > ra + rb)
//		return FALSE;
//	//L = A0 x B1
//	ra = a[1] * fabs(R[2][1]) + a[2] * fabs(R[1][1]);
//	rb = b[0] * fabs(R[0][2]) + b[2] * fabs(R[0][0]);
//	t = fabs(T[2] * R[1][1] - T[1] * R[2][1]);
//	if (t > ra + rb)
//		return FALSE;
//	//L = A0 x B2
//	ra = a[1] * fabs(R[2][2]) + a[2] * fabs(R[1][2]);
//	rb = b[0] * fabs(R[0][1]) + b[1] * fabs(R[0][0]);
//	t = fabs(T[2] * R[1][2] - T[1] * R[2][2]);
//	if (t > ra + rb)
//		return FALSE;
//	//L = A1 x B0
//	ra = a[0] * fabs(R[2][0]) + a[2] * fabs(R[0][0]);
//	rb = b[1] * fabs(R[1][2]) + b[2] * fabs(R[1][1]);
//	t = fabs(T[0] * R[2][0] - T[2] * R[0][0]);
//	if (t > ra + rb)
//		return FALSE;
//	//L = A1 x B1
//	ra = a[0] * fabs(R[2][1]) + a[2] * fabs(R[0][1]);
//	rb = b[0] * fabs(R[1][2]) + b[2] * fabs(R[1][0]);
//	t = fabs(T[0] * R[2][1] - T[2] * R[0][1]);
//	if (t > ra + rb)
//		return FALSE;
//	//L = A1 x B2
//	ra = a[0] * fabs(R[2][2]) + a[2] * fabs(R[0][2]);
//	rb = b[0] * fabs(R[1][1]) + b[1] * fabs(R[1][0]);
//	t = fabs(T[0] * R[2][2] - T[2] * R[0][2]);
//	if (t > ra + rb)
//		return FALSE;
//	//L = A2 x B0
//	ra = a[0] * fabs(R[1][0]) + a[1] * fabs(R[0][0]);
//	rb = b[1] * fabs(R[2][2]) + b[2] * fabs(R[2][1]);
//	t = fabs(T[1] * R[0][0] - T[0] * R[1][0]);
//	if (t > ra + rb)
//		return FALSE;
//	//L = A2 x B1
//	ra = a[0] * fabs(R[1][1]) + a[1] * fabs(R[0][1]);
//	rb = b[0] * fabs(R[2][2]) + b[2] * fabs(R[2][0]);
//	t = fabs(T[1] * R[0][1] - T[0] * R[1][1]);
//	if (t > ra + rb)
//		return FALSE;
//	//L = A2 x B2
//	ra = a[0] * fabs(R[1][2]) + a[1] * fabs(R[0][2]);
//	rb = b[0] * fabs(R[2][1]) + b[1] * fabs(R[2][0]);
//	t = fabs(T[1] * R[0][2] - T[0] * R[1][2]);
//	if (t > ra + rb)
//		return FALSE;
//	return TRUE;*/
//}
////http://www.randygaul.net/2014/05/22/deriving-obb-to-obb-intersection-sat/
//bool OOBBIntersectp(const Mesh::OOBB *mObject1, const Mesh::OOBB *mObject2 , const glm::mat4* mWorld1, const glm::mat4 *mWorld2)
//{
//	//TODO write THIS Method)!!!
//	glm::mat3 rmatrix;
//	glm::vec4 Pa = mObject1->mCenter, Pb = mObject2->mCenter;
//	glm::vec4 Da = mObject1->mDim, Db = mObject2->mDim;
//
//	glm::vec4 PaW = (*mWorld1) * Pa, PbW = (*mWorld2) * Pb;
//	glm::vec4 DaW = glm::transpose(glm::inverse(*mWorld1)) * mObject1->mDim, DbW = glm::transpose(glm::inverse(*mWorld1)) * mObject2->mDim;
//
//	glm::vec3 a, b;
//	a = glm::vec3(glm::abs(DaW[0]),
//		glm::abs(DaW[1]),
//		glm::abs(DaW[2]));
//	b = glm::vec3(glm::abs(DbW[0]),
//		glm::abs(DbW[1]),
//		glm::abs(DbW[2]));
//
//	glm::vec3 mDir[3] = { glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) };
//
//	for (int i = 0; i<3; i++)
//		for (int j = 0; j<3; j++) {
//			rmatrix[i][j] = glm::dot(glm::normalize(glm::vec3((*mWorld1) * glm::vec4(mDir[i], 0.0f))),
//				glm::normalize(glm::vec3((*mWorld2) * glm::vec4(mDir[j], 0.0f))));
//		}
//
//	glm::vec4 dP = Pb - Pa;
//	glm::vec3 T;
//	T[0] = (glm::dot(glm::normalize((*mWorld1) * glm::vec4(mDir[0], 0.0f)), dP));
//	T[1] = (glm::dot(glm::normalize((*mWorld1) * glm::vec4(mDir[1], 0.0f)), dP));
//	T[2] = (glm::dot(glm::normalize((*mWorld1) * glm::vec4(mDir[2], 0.0f)), dP));
//
//	for (register int i = 0; i < 3; i++) 
//	{
//		//glm::vec4 l = glm::normalize((*mWorld1) * glm::vec4(mDir[i], 0.0f));
//
//		float t = glm::abs(T[i]);//glm::dot(l, dP));
//		float ra = a[i];//((*mWorld1) * glm::vec4(mDir[i], 0.0f))[i]);
//		float rb = b[0] * fabs(rmatrix[i][0]) +
//			b[1] * fabs(rmatrix[i][1]) +
//			b[2] * fabs(rmatrix[i][2]);
//		//glm::abs(DbW[0])
//			/*glm::abs(glm::dot(l, (*mWorld2) * glm::vec4(mDir[0], 0.0f))) + 
//			glm::abs(glm::dot(l, (*mWorld2) * glm::vec4(mDir[1], 0.0f))) + 
//			glm::abs(glm::dot(l, (*mWorld2) * glm::vec4(mDir[2], 0.0f)));*/
//
//		if (ra + rb < t)
//			return false;
//	}
//
//	for (register int i = 0; i < 3; i++)
//	{
//		/*ra = a[0]*fabs(rmatrix[0][i]) + 
//a[1]*fabs(rmatrix[1][i]) + 
//a[2]*fabs(rmatrix[2][i]);
//
//rb = b.size [i];
//
//t = fabs( T[0]*rmatrix[0][i] + 
//T[1]*rmatrix[1][i] +
//T[2]*rmatrix[2][i] );
//
//if (t > ra + rb) return 0;*/
//		float ra = a[0] * fabs(rmatrix[0][i]) +
//			a[1] * fabs(rmatrix[1][i]) +
//			a[2] * fabs(rmatrix[2][i]);
//		float rb = b[i];
//
//		//glm::vec4 l = glm::normalize((*mWorld2) * glm::vec4(mDir[i], 1.0f));
//
//		float t = fabs(T[0] * rmatrix[0][i] +
//			T[1] * rmatrix[1][i] +
//			T[2] * rmatrix[2][i]);
//
//		/*float tl = glm::abs(glm::dot(l, dP));
//		float ra = glm::abs(((*mWorld2) * glm::vec4(mDir[i], 0.0f))[i]);
//		float rb = glm::abs(glm::dot(l, (*mWorld1) * glm::vec4(mDir[0], 0.0f))) +
//			glm::abs(glm::dot(l, (*mWorld1) * glm::vec4(mDir[1], 0.0f))) +
//			glm::abs(glm::dot(l, (*mWorld1) * glm::vec4(mDir[2], 0.0f)));
//		*/
//		if (ra + rb < t)
//			return false;
//	}
//
//	// 9 векторных произведений
//	float ra, rb, t;
//	//L = A0 x B0
//	ra = a[1] * fabs(rmatrix[2][0]) + a[2] * fabs(rmatrix[1][0]);
//	rb = b[1] * fabs(rmatrix[0][2]) + b[2] * fabs(rmatrix[0][1]);
//	t = fabs(T[2] * rmatrix[1][0] - T[1] * rmatrix[2][0]);
//	if (t > ra + rb) return 0;
//
//	//L = A0 x B1
//	ra = a[1] * fabs(rmatrix[2][1]) + a[2] * fabs(rmatrix[1][1]);
//	rb = b[0] * fabs(rmatrix[0][2]) + b[2] * fabs(rmatrix[0][0]);
//	t = fabs(T[2] * rmatrix[1][1] - T[1] * rmatrix[2][1]);
//	if (t > ra + rb) return 0;
//
//	//L = A0 x B2
//	ra = a[1] * fabs(rmatrix[2][2]) + a[2] * fabs(rmatrix[1][2]);
//	rb = b[0] * fabs(rmatrix[0][1]) + b[1] * fabs(rmatrix[0][0]);
//	t = fabs(T[2] * rmatrix[1][2] - T[1] * rmatrix[2][2]);
//	if (t > ra + rb) return 0;
//
//	//L = A1 x B0
//	ra = a[0] * fabs(rmatrix[2][0]) + a[2] * fabs(rmatrix[0][0]);
//	rb = b[1] * fabs(rmatrix[1][2]) + b[2] * fabs(rmatrix[1][1]);
//	t = fabs(T[0] * rmatrix[2][0] - T[2] * rmatrix[0][0]);
//	if (t > ra + rb) return 0;
//
//	//L = A1 x B1
//	ra = a[0] * fabs(rmatrix[2][1]) + a[2] * fabs(rmatrix[0][1]);
//	rb = b[0] * fabs(rmatrix[1][2]) + b[2] * fabs(rmatrix[1][0]);
//	t = fabs(T[0] * rmatrix[2][1] - T[2] * rmatrix[0][1]);
//	if (t > ra + rb) return 0;
//
//	//L = A1 x B2
//	ra = a[0] * fabs(rmatrix[2][2]) + a[2] * fabs(rmatrix[0][2]);
//	rb = b[0] * fabs(rmatrix[1][1]) + b[1] * fabs(rmatrix[1][0]);
//	t = fabs(T[0] * rmatrix[2][2] - T[2] * rmatrix[0][2]);
//	if (t > ra + rb) return 0;
//
//	//L = A2 x B0
//	ra = a[0] * fabs(rmatrix[1][0]) + a[1] * fabs(rmatrix[0][0]);
//	rb = b[1] * fabs(rmatrix[2][2]) + b[2] * fabs(rmatrix[2][1]);
//	t = fabs(T[1] * rmatrix[0][0] - T[0] * rmatrix[1][0]);
//	if (t > ra + rb) return 0;
//
//	//L = A2 x B1
//	ra = a[0] * fabs(rmatrix[1][1]) + a[1] * fabs(rmatrix[0][1]);
//	rb = b[0] * fabs(rmatrix[2][2]) + b[2] * fabs(rmatrix[2][0]);
//	t = fabs(T[1] * rmatrix[0][1] - T[0] * rmatrix[1][1]);
//	if (t > ra + rb) return 0;
//
//	//L = A2 x B2
//	ra = a[0] * fabs(rmatrix[1][2]) + a[1] * fabs(rmatrix[0][2]);
//	rb = b[0] * fabs(rmatrix[2][1]) + b[1] * fabs(rmatrix[2][0]);
//	t = fabs(T[1] * rmatrix[0][2] - T[0] * rmatrix[1][2]);
//	if (t > ra + rb) return 0;
//	//return 0;
//	// если до сих пор не вышли, то боксы пересекаются
//	return 1;
//
//	//if (glm::abs(mObject1->mCenter.y - mObject2->mCenter.y) <= 0.3f) return true;
//
//	//return true;//false;
//}
//
