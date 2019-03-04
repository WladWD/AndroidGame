//#version 100
/////////////////////////////////////////////////////////
//attribute
attribute vec3 gWorldPos;
attribute vec4 gOffset_Tex;
/////////////////////////////////////////////////////////
//varying
varying vec3 gFragWorldPos;
varying vec2 gFragTexCoord;
/////////////////////////////////////////////////////////
//uniform
uniform mat4 mProjView;
uniform mat4 mWorld;
uniform vec4 mCamPosition;
uniform vec4 mUpVec;
uniform vec2 mScaleAlpha;
/////////////////////////////////////////////////////////
//vertex shader
void main()
{
	vec4 gWorld = mWorld * vec4(gWorldPos * mScaleAlpha.x, 1.0);
	vec3 mDir = normalize(mCamPosition.xyz - gWorld.xyz);
	vec3 gRight = normalize(cross(mUpVec.xyz, mDir));
	vec3 gUp = normalize(cross(mDir, gRight));

	gFragWorldPos = gWorld.xyz;////gWorld + (gRight * gOffset_Tex.x + gUp * gOffset_Tex.y) * mScaleAlpha.x;//gWorld.xyz;//
	gFragTexCoord = gOffset_Tex.zw;

	gl_Position = mProjView * vec4(gFragWorldPos, 1.0);
}
/////////////////////////////////////////////////////////

