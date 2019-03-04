//#version 100
/////////////////////////////////////////////////////////
#define ALPHA_THRESHOLD 0.1
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
varying vec3 gFragWorldPos;
varying vec2 gFragTexCoord;
/////////////////////////////////////////////////////////
//uniform 
/////////////////////////////////////////////////////////
//uniform sampler
uniform sampler2D mDiffuse;
uniform vec2 mScaleAlpha;
/////////////////////////////////////////////////////////
//fragment shader
void main()
{
	vec4 mColor = texture2D(mDiffuse, gFragTexCoord);
	gl_FragColor = pow(mColor, vec4(1.0));//vec4(mColor.r, mColor.r, mColor.r, mColor.r);// vec4(mColor.a, mColor.a, mColor.a, mColor.a);
	gl_FragColor.a *= mScaleAlpha.g;// *(1.0 - mColor.r * mColor.g * mColor.g);
	if (gl_FragColor.a < ALPHA_THRESHOLD)
		discard;

	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
/////////////////////////////////////////////////////////
