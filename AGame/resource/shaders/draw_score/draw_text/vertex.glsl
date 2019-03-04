//#version 100
/////////////////////////////////////////////////////////
//attribute
attribute vec2 gWorldPos;
//attribute vec2 gTexCoord;
/////////////////////////////////////////////////////////
//varying
varying vec3 gFragWorldPos;
varying vec2 gFragTexCoord;
/////////////////////////////////////////////////////////
//uniform
uniform mat4 mWorld;
uniform vec4 mPackOffsetScaleTex;
/////////////////////////////////////////////////////////
//vertex shader
void main()
{
	vec4 gWorld = mWorld * vec4(gWorldPos, 0.0, 1.0);

	gFragWorldPos = gWorld.xyz;

	gFragTexCoord = gWorldPos;// *0.5 + 0.5;
	gFragTexCoord *= mPackOffsetScaleTex.zw;
	gFragTexCoord += mPackOffsetScaleTex.xy;
	gFragTexCoord = vec2(gFragTexCoord.x, 1.0 - gFragTexCoord.y);
	gl_Position = gWorld;
}
/////////////////////////////////////////////////////////

