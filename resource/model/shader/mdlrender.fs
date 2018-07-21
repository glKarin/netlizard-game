uniform sampler2D texDiffuseMap;
uniform samplerCube texEnvMap;
uniform vec4 glowColor;
varying vec4 vvColor;
varying vec2 vvTexCoord;
varying vec3 vvTexCoordCube;

void main (void)
{
    vec4 vDiffuse = texture2D(texDiffuseMap, vvTexCoord).rgba * vvColor;
#ifdef CSO_ENV
    vec3 cubeColor = textureCube(texEnvMap, vvTexCoordCube).rgb;
    vDiffuse.xyz = (vDiffuse.xyz + glowColor.www) * cubeColor;
#elif defined(CSO_GLOW)
    vec3 cubeColor = textureCube(texEnvMap, vvTexCoordCube).rgb;
    vDiffuse.xyz = vDiffuse.xyz + (cubeColor * glowColor.xyz);        
#endif

    gl_FragColor = vDiffuse;
}