float v_lambert1 = 1.4953241322;
float dMul = 1.0 / v_lambert1;
float dAdd = (v_lambert1 - 1) * dMul;
		
attribute vec4 vaPosition;
attribute vec3 vaNormal;
attribute vec2 vaTexCoord;


uniform vec4 texOffset;
uniform vec4 colorMix;
uniform vec4 lightInfo;
uniform vec4 dLightDir;
uniform vec4 eLightPos;
uniform vec4 eLightColor;
uniform vec4 worldEye;
uniform mat4 muWVP;
uniform vec4 boneMat[MAX_BONE_REG];

varying vec4 vvColor;
varying vec2 vvTexCoord;
varying vec3 vvTexCoordCube;
	
void main(void)
{
    float alpha = lightInfo.x;
	float ambient = lightInfo.y;
	float shadeLight = lightInfo.z;
	float aniTime = lightInfo.w;
	int boneIdx = int(vaPosition.w);
	float eLightRadius2 = eLightPos.w;
	float envBrightMul = colorMix.w;
	
	vec4 pos = vec4(vaPosition.xyz, 1);
	vec4 boneCol0 = boneMat[boneIdx * 3];
	vec4 boneCol1 = boneMat[boneIdx * 3 + 1];
	vec4 boneCol2 = boneMat[boneIdx * 3 + 2];
	vec4 trnPos;
	trnPos.x = dot(pos, boneCol0);
	trnPos.y = dot(pos, boneCol1);
	trnPos.z = dot(pos, boneCol2);
	trnPos.w = 1;
	gl_Position = muWVP * trnPos;
			
	vec3 normal;
	normal.x = dot(vaNormal, boneCol0.xyz);
	normal.y = dot(vaNormal, boneCol1.xyz);
	normal.z = dot(vaNormal, boneCol2.xyz);
	
	vvColor.w = alpha;		

#ifdef CSO_FULL_DLIGHT
	vvColor.xyz = vec3(1, 1, 1);
#else
    vvColor.xyz = vec3(ambient, ambient, ambient);
    float dotNdL = dot(normal, dLightDir.xyz);
    dotNdL = max(0.0, dotNdL * dMul + dAdd);
    vvColor.xyz -= shadeLight * dotNdL;
#endif

	vvColor.xyz *= colorMix.xyz;
				
#ifdef CSO_ELIGHT
    vec3 lightVec = eLightPos.xyz - trnPos.xyz;
    float attenuation = eLightRadius2 / dot(lightVec, lightVec);
    float dotNeL = max(0.0, dot(normalize(lightVec), normal));
    vvColor.xyz += (dotNeL * attenuation) * eLightColor.xyz;
#endif
   
#ifdef CSO_FINAL_WHITE
    vvColor.xyz = vec3(1, 1, 1);
#endif
    
	vvTexCoord = (vaTexCoord + texOffset.xy) * texOffset.zw;
	
#ifdef CSO_ENV
    vvColor.xyz *= envBrightMul;
	vvTexCoordCube = reflect(trnPos.xyz - worldEye.xyz, normal);
#elif defined(CSO_GLOW)
    vvTexCoordCube = reflect(trnPos.xyz - worldEye.xyz, normal);
#endif
}