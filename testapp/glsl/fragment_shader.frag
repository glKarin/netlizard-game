precision mediump float;

struct AlphaTest{
	bool enabled;
	int func;
	float ref;
};

varying vec2 fTexcoord;

uniform sampler2D fTexture;
uniform vec4 fColor; // color
uniform AlphaTest fAlphaTest;

bool glAlphaTest(in int func, in float ref, in float a)
{
	bool ava = false;
	if(func == 0x0207) // always
		ava = true;
	else if(func == 0x0200) // never
		ava = false;
	else if(func == 0x0201) // less 
		ava = (a < ref);
	else if(func == 0x0202) // equal
		ava = (a == ref);
	else if(func == 0x0203) // lequal
		ava = (a <= ref);
	else if(func == 0x0204) // greater
		ava = (a > ref);
	else if(func == 0x0205) // notequal
		ava = (a != ref);
	else if(func == 0x0206) // gequal
		ava = (a >= ref);
	else
		ava = false;
	return ava;
}

void main()
{
	// gl_FragCoord
	// gl_FragFacing
	
	if(fAlphaTest.enabled)
	{
		if(fAlphaTest.func == 0x0200)
		{
			discard;
			return;
		}
	}

	//gl_FragColor = texture2D(fTexture, fTexcoord) * fColor;
	gl_FragColor = fColor;
	return;

	if(!glAlphaTest(fAlphaTest.func, fAlphaTest.ref, gl_FragColor.a))
	{
		discard;
		return;
	}
}

