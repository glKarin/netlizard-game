#define LOG2E 1.442695

struct Fog{
	bool enabled;
	int mode;
	float density;
	vec4 color;
	float start;
	float end;
};

// 输入
attribute vec3 vPosition; // 顶点坐标
attribute vec3 vNormal; // 法线
attribute vec2 vTexcoord; // 纹理坐标0
attribute vec4 vColor; // 颜色

uniform mat4 vModelviewMatrix; // 模型视图矩阵
uniform mat4 vProjectionMatrix; // 投影矩阵
uniform mat4 vModelviewProjectionMatrix; // MVP矩阵
uniform float vPointSize; // 点大小
uniform Fog fFog; // 雾

// 输出
varying vec2 fTexcoord; // 纹理坐标
varying float fFogFactory; // 雾因子
varying vec4 fFogColor; // 雾颜色
varying vec4 fPrimaryColor; // 雾颜色
//varing vec3 fNormal; // 法线

float glFog_Linear(in vec3 pos)
{
	float absz = abs(pos.z);
	float factory = (fFog.end - absz) / (fFog.end - fFog.start);
	return clamp(factory, 0.0, 1.0);
}

float glFog_Exp(in vec3 pos)
{
	float absz = abs(pos.z);
	float factory = exp(- fFog.density * absz);
	return clamp(factory, 0.0, 1.0);
}

float glFog_Exp2(in vec3 pos)
{
	float absz = abs(pos.z);
	float factory = exp2(-fFog.density * fFog.density * absz * absz * LOG2E);
	return clamp(factory, 0.0, 1.0);
}

void main()
{
	gl_PointSize = vPointSize;
	// p v m
	gl_Position = vModelviewProjectionMatrix * vec4(vPosition, 1);
	//gl_Position = vec4(vPosition, 1.0);

	fTexcoord = vTexcoord;
	vec3 pos = vec3(vModelviewMatrix * vec4(vPosition, 1.0));
	//vec3 pos = gl_Position.xyz;
	fFogFactory = fFog.enabled ? glFog_Linear(pos) : 1.0;
	fFogColor = fFog.color;
	fPrimaryColor = vColor;
	//fNormal = vNormal;
}
