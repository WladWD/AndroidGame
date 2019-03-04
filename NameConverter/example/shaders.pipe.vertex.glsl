//#version 100
/////////////////////////////////////////////////////////
//attribute
attribute vec3 gWorldPos;
attribute vec3 gWorldNorm;
attribute vec2 gTexCoord;
/////////////////////////////////////////////////////////
//varying
varying vec3 gFragWorldPos;
varying vec3 gFragWorldNorm;
varying vec2 gFragTexCoord;
/////////////////////////////////////////////////////////
//uniform
uniform mat4 mProjView;
uniform mat4 mWorld;
uniform mat4 mWorldInvTrans;
/////////////////////////////////////////////////////////
//vertex shader
void main()
{
	vec4 gWorld = mWorld * vec4(gWorldPos, 1.0);

	gFragWorldPos.xyz = gWorld.xyz;
	gFragWorldNorm = (mWorldInvTrans * vec4(gWorldNorm, 0.0)).xyz;
	gFragTexCoord = gTexCoord;

	gl_Position = mProjView * gWorld;
}
/////////////////////////////////////////////////////////

