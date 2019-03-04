//#version 100
/////////////////////////////////////////////////////////
#define COOKIE_PICES_COUNT 64
/////////////////////////////////////////////////////////
//attribute
//attribute vec3 gWorldPos;
attribute vec2 gTexCoord;
/////////////////////////////////////////////////////////
//varying
varying vec2 gFragTexCoord;
/////////////////////////////////////////////////////////
//uniform
/////////////////////////////////////////////////////////
//vertex shader
void main()
{
	gFragTexCoord = gTexCoord;
	gl_Position = vec4(gTexCoord * vec2(2.0) + vec2(-1.0), 0.0, 1.0);
}
/////////////////////////////////////////////////////////

