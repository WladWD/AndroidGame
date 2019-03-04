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
varying vec2 gFragTexCoord;
/////////////////////////////////////////////////////////
//uniform 
uniform vec4 mStep;// 1.0f / DimX; 1.0f / DimY; mLerp
/////////////////////////////////////////////////////////
//uniform sampler
uniform sampler2D gRenderTexture;
/////////////////////////////////////////////////////////
//fragment shader
void main()
{
	vec4 sample0 = texture2D(gRenderTexture, gFragTexCoord + vec2(  mStep.x,  mStep.y), mStep.w);
	vec4 sample1 = texture2D(gRenderTexture, gFragTexCoord + vec2(  mStep.x, -mStep.y), mStep.w);
	vec4 sample2 = texture2D(gRenderTexture, gFragTexCoord + vec2( -mStep.x,  mStep.y), mStep.w);
	vec4 sample3 = texture2D(gRenderTexture, gFragTexCoord + vec2( -mStep.x, -mStep.y), mStep.w);

	gl_FragColor = mix(texture2D(gRenderTexture, gFragTexCoord, 0.2 * mStep.w), (sample0 + sample1 +
															sample2 + sample3) * 0.25, mStep.z);

	//gl_FragColor = texture2D(gRenderTexture, gFragTexCoord, 1.90);
	//	vec4(0.4, 0.5, 0.8, 1.0);
}
/////////////////////////////////////////////////////////
