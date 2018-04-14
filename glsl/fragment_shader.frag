precision mediump float;

/* AlphaFunction */
#define HGL_NEVER                          0x0200
#define HGL_LESS                           0x0201
#define HGL_EQUAL                          0x0202
#define HGL_LEQUAL                         0x0203
#define HGL_GREATER                        0x0204
#define HGL_NOTEQUAL                       0x0205
#define HGL_GEQUAL                         0x0206
#define HGL_ALWAYS                         0x0207

#define HGL_LINEAR				0x2601
#define HGL_EXP					0x0800
#define HGL_EXP2					0x0801

struct AlphaTest{
	bool enabled; // 启用Alpha测试
	int func; // 测试函数
	float ref; // 参考值
}; // Alpha测试

varying vec2 fTexcoord; // 纹理坐标0
varying float fFogFactory; // 雾因子
varying vec4 fFogColor; // 雾颜色

uniform sampler2D fTexture; // 纹理0采样器
uniform vec4 fColor; // 颜色
uniform AlphaTest fAlphaTest; // Alpha测试
uniform bool fBindTexture; // 是否绑定纹理

// Alpha测试
bool glAlphaTest(in float a)
{
	bool ava = false;
	if(fAlphaTest.func == HGL_ALWAYS)
		ava = true;
	else if(fAlphaTest.func == HGL_NEVER)
		ava = false;
	else if(fAlphaTest.func == HGL_LESS)
		ava = (a < fAlphaTest.ref);
	else if(fAlphaTest.func == HGL_EQUAL)
		ava = (a == fAlphaTest.ref);
	else if(fAlphaTest.func == HGL_LEQUAL)
		ava = (a <= fAlphaTest.ref);
	else if(fAlphaTest.func == HGL_GREATER)
		ava = (a > fAlphaTest.ref);
	else if(fAlphaTest.func == HGL_NOTEQUAL)
		ava = (a != fAlphaTest.ref);
	else if(fAlphaTest.func == HGL_GEQUAL)
		ava = (a >= fAlphaTest.ref);
	else
		ava = false;
	return ava;
}

void main()
{
	// gl_FragCoord
	// gl_FragFacing
	
	/*
	if(fAlphaTest.enabled)
	{
		if(fAlphaTest.func == 0x0200)
		{
			discard;
			return;
		}
	}
	*/

	/*
	if(fBindTexture)
		gl_FragColor = texture2D(fTexture, fTexcoord) * fColor;
	else
		gl_FragColor = fColor;
		*/
	vec4 color = texture2D(fTexture, fTexcoord) * fColor;
	gl_FragColor = mix(fFogColor, color, fFogFactory);
	/*
	if(gl_FragColor.a < 0.1)
		discard;
		*/

	/*
	if(fAlphaTest.enabled)
	{
		//gl_FragColor = vec4(0.0, 1 ,0, 1);
		if(!glAlphaTest(gl_FragColor.a))
		{
			discard;
			return;
		}
	}
	*/
}

