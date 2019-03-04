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
varying vec3 gFragWorldPos;
varying vec3 gFragWorldNorm;
varying vec2 gFragTexCoord;
/////////////////////////////////////////////////////////
//uniform 
uniform vec2 gFog;
uniform vec4 gFogColor;
/////////////////////////////////////////////////////////
//uniform sampler
uniform sampler2D mTexture;
/////////////////////////////////////////////////////////
//fragment shader
void main()
{
	float f = length(gFragWorldPos);
	f = sin(clamp((f - gFog.x) / gFog.y, 0.0, 1.0) * MPIDIV2);

	vec4 mColor = texture(mTexture, gFragTexCoord);

	//vec4 color = vec4(mod(gFragWorldPos.y, 1.0)) * vec4(mod(gFragWorldPos.x, 1.0)) * vec4(mod(gFragWorldPos.z, 1.0)) * vec4(gFragTexCoord, 1.0, 1.0);//vec4(gFragWorldNorm*vec3(0.5) + vec3(0.5), 1.0) *
	//color = mix(color, gFogColor, f);
	mColor = mix(mColor, gFogColor, f);

	gl_FragColor = mColor;
}
/////////////////////////////////////////////////////////
