//#version 100
/////////////////////////////////////////////////////////
//define 
#ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
#else
precision mediump float;
#endif
/////////////////////////////////////////////////////////
#define MPIDIV2  1.57079632679
/////////////////////////////////////////////////////////
//varying
//varying vec3 gFragWorldPos;
varying vec2 gFragTexCoord;
/////////////////////////////////////////////////////////
//uniform 
/////////////////////////////////////////////////////////
//uniform sampler
uniform sampler2D mDiffuse;
/////////////////////////////////////////////////////////
//fragment shader
void main()
{
	gl_FragColor = texture2D(mDiffuse, gFragTexCoord);
}
/////////////////////////////////////////////////////////
