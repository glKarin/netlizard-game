attribute vec3 vPosition;
attribute vec3 vNormal;
attribute vec2 vTexcoord;

uniform mat4 vModelviewMatrix;
uniform mat4 vProjectionMatrix;

varying vec2 fTexcoord;

void main()
{
	// p v m
	mat4 transform = vProjectionMatrix * vModelviewMatrix;
	gl_Position = transform * vec4(vPosition, 1);
	//gl_Position = vec4(vPosition.x, vPosition.y, 0.0, 1.0);
	fTexcoord = vTexcoord;
}
