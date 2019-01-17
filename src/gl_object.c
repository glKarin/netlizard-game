#include "gl_object.h"

#include "nl_std.h"

#define VEC3_X(v) ((v)[0])
#define VEC3_Y(v) ((v)[1])
#define VEC3_Z(v) ((v)[2])
/*
	 1  3  |  5  7
	 0  2  |  4  6
	 */
static const GLushort CubePlane4Index[] = 
{
	// 正
	0, 2, 1, 1, 2, 3,
	// 背
	4, 5, 6, 6, 5, 7,
	// 左
	4, 0, 5, 5, 0, 1,
	// 右
	2, 6, 3, 3, 6, 7,
	// 上
	1, 3, 5, 5, 3, 7,
	// 下
	0, 4, 2, 2, 4, 6
};

static const GLfloat CubePlane4Texcoord[] = 
{
	// 正
	0.0, 1.0,  1.0, 1.0,  0.0, 0.0,  0,0, 1.0,  1.0, 1.0,  0.0, 0.0,
	// 背
	1.0, 1.0,  1.0, 0.0,  0.0, 0.0,  0.0, 0.0,  1.0, 0.0,  1.0, 1.0,
	// 左
	0.0, 0.0,  1.0, 0.0,  0.0, 1.0,  0.0, 1.0,  1.0, 0.0,  1.0, 1.0,
	// 右
	0.0, 0.0,  1.0, 1.0,  0.0, 1.0,  0.0, 1.0,  1.0, 1.0,  1.0, 0.0,
	// 上
	0.0, 0.0,  1.0, 0.0,  0.0, 1.0,  0.0, 1.0,  1.0, 0.0,  1.0, 1.0,
	// 下
	0.0, 1.0,  0.0, 0.0,  1.0, 1.0,  1.0, 1.0,  0.0, 0.0,  1.0, 0.0
};

static const GLfloat CubePlane4Normal[] = 
{
	// 正
	0.0, 0.0, 1.0,
	// 背
	0.0, 0.0, -1.0,
	// 左
	-1.0, 0.0, 0.0,
	// 右
	1.0, 0.0, 0.0,
	// 上
	0.0, 1.0, 0.0,
	// 下
	0.0, -1.0, 0.0
};

static void OpenGL_CubeVertex(const GLfloat v1[3], const GLfloat v2[3], GLfloat vertex[24])
{
	if(!v1 || !v2 || !vertex)
		return;
	double minx = v1[0];
	double miny = v1[1];
	double minz = v1[2];
	double maxx = v2[0];
	double maxy = v2[1];
	double maxz = v2[2];
	// 前左下 0
	vertex[0] = minx;
	vertex[1] = miny;
	vertex[2] = maxz;
	// 前左上 1
	vertex[3] = minx;
	vertex[4] = maxy;
	vertex[5] = maxz;
	// 前右下 2
	vertex[6] = maxx;
	vertex[7] = miny;
	vertex[8] = maxz;
	// 前右上 3
	vertex[9] = maxx;
	vertex[10] = maxy;
	vertex[11] = maxz;
	// 后左下 4
	vertex[12] = minx;
	vertex[13] = miny;
	vertex[14] = minz;
	// 后左上 5
	vertex[15] = minx;
	vertex[16] = maxy;
	vertex[17] = minz;
	// 后右下 6
	vertex[18] = maxx;
	vertex[19] = miny;
	vertex[20] = minz;
	// 后右上 7
	vertex[21] = maxx;
	vertex[22] = maxy;
	vertex[23] = minz;
}

void OpenGL_Cube_MinMax_VI(const GLfloat v1[3], const GLfloat v2[3], GLfloat *vertex, GLushort *indexs)
{
	if(!vertex || !indexs || !v1 || !v2)
		return;
	OpenGL_CubeVertex(v1, v2, vertex);
	unsigned int i;
	unsigned int count = countof(CubePlane4Index);
	for(i = 0; i < count; i++)
		indexs[i] = (GLushort)CubePlane4Index[i];
}

void OpenGL_Cube_MinMax_VTN(const GLfloat v1[3], const GLfloat v2[3], GLfloat *vertex, GLfloat *texcoord, GLfloat *normal)
{
	if(!vertex || !texcoord || !normal || !v1 || !v2)
		return;

	GLfloat v[24];
	OpenGL_CubeVertex(v1, v2, v);

	unsigned int i;
	unsigned int count = countof(CubePlane4Index);
	for(i = 0; i < count; i++)
	{
		vertex[i * 3] = v[CubePlane4Index[i] * 3];
		vertex[i * 3 + 1] = v[CubePlane4Index[i] * 3 + 1];
		vertex[i * 3 + 2] = v[CubePlane4Index[i] * 3 + 2];
		normal[i * 3] = CubePlane4Normal[i / 6 * 3];
		normal[i * 3 + 1] = CubePlane4Normal[i / 6 * 3 + 1];
		normal[i * 3 + 2] = CubePlane4Normal[i / 6 * 3 + 2];
		texcoord[i * 2] = CubePlane4Texcoord[i * 2];
		texcoord[i * 2 + 1] = CubePlane4Texcoord[i * 2 + 1];
	}
}

void OpenGL_Cube_CenterLength_VI(const GLfloat center[3], const GLfloat length[3], GLfloat *vertex, GLushort *indexs)
{
	if(!vertex || !indexs || !center || !length)
		return;
	const GLfloat v1[3] = {
		center[0] + length[0],
		center[1] + length[1],
		center[2] + length[2]
	};
	const GLfloat v2[3] = {
		center[0] - length[0],
		center[1] - length[1],
		center[2] - length[2]
	};
	OpenGL_Cube_MinMax_VI(v1, v2, vertex, indexs);
}

void OpenGL_Cube_CenterLength_VTN(const GLfloat center[3], const GLfloat length[3], GLfloat *vertex, GLfloat *texcoord, GLfloat *normal)
{
	if(!vertex || !texcoord || !normal || !center || !length)
		return;
	const GLfloat v1[3] = {
		center[0] + length[0],
		center[1] + length[1],
		center[2] + length[2]
	};
	const GLfloat v2[3] = {
		center[0] - length[0],
		center[1] - length[1],
		center[2] - length[2]
	};
	OpenGL_Cube_MinMax_VTN(v1, v2, vertex, texcoord, normal);
}

void OpenGL_Cube(const GLfloat length[3])
{
	static unsigned cube_inited = 0;
	static GLfloat vertex[108];
	static GLfloat texcoord[72];
	static GLfloat normal[108];
	static GLfloat color[108];

	GLfloat vertex_draw[108];

	if(!cube_inited)
	{
		const GLfloat cube_colors[] = {
			// 正
			1.0, 0.0, 0.0, 1.0,
			// 背
			0.0, 1.0, 1.0, 1.0,
			// 左
			0.0, 1.0, 0.0, 1.0,
			// 右
			1.0, 0.0, 1.0, 1.0,
			// 上
			0.0, 0.0, 1.0, 1.0,
			// 下
			1.0, 1.0, 0.0, 1.0,
		};
		int i;
		for(i = 0; i < 36; i++)
		{
			color[i * 4] = cube_colors[i / 6 * 4];
			color[i * 4 + 1] = cube_colors[i / 6 * 4 + 1];
			color[i * 4 + 2] = cube_colors[i / 6 * 4 + 2];
			color[i * 4 + 3] = 1.0;
		}

		GLfloat min[] = {-0.5, -0.5, -0.5};
		GLfloat max[] = {0.5, 0.5, 0.5};
		OpenGL_Cube_MinMax_VTN(min, max, vertex, texcoord, normal);

		cube_inited = 1;
	}

	int i;
	for(i = 0; i < 108; i += 3)
	{
		vertex_draw[i] = vertex[i] * VEC3_X(length);
		vertex_draw[i + 1] = vertex[i + 1] * VEC3_Y(length);
		vertex_draw[i + 2] = vertex[i + 2] * VEC3_Z(length);
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertex_draw);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoord);
	glNormalPointer(GL_FLOAT, 0, normal);
	glColorPointer(4, GL_FLOAT, 0, color);

	oglDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void OpenGL_CubeSimple(const GLfloat length[3])
{
	static unsigned cube_inited = 0;
	static GLfloat vertex[108];
	static GLushort index[36];

	GLfloat vertex_draw[108];

	if(!cube_inited)
	{
		GLfloat min[] = {-0.5, -0.5, -0.5};
		GLfloat max[] = {0.5, 0.5, 0.5};
		OpenGL_Cube_MinMax_VI(min, max, vertex, index);

		cube_inited = 1;
	}

	int i;
	for(i = 0; i < 108; i += 3)
	{
		vertex_draw[i] = vertex[i] * VEC3_X(length);
		vertex_draw[i + 1] = vertex[i + 1] * VEC3_Y(length);
		vertex_draw[i + 2] = vertex[i + 2] * VEC3_Z(length);
	}

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertex_draw);

	oglDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, index);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void OpenGL_Plane_MinMax_VTN(const GLfloat v1[3], const GLfloat v2[3], GLfloat *vertexr, GLfloat *texcoordr, GLfloat *normalr)
{
	if(!vertexr || !texcoordr || !normalr || !v1 || !v2)
		return;

	GLfloat avg_y = (VEC3_Y(v1) + VEC3_Y(v2)) / 2.0;

	const GLfloat vertex[] = {
		VEC3_X(v1), avg_y, VEC3_Z(v1),
		VEC3_X(v1), avg_y, VEC3_Z(v2),
		VEC3_X(v2), avg_y, VEC3_Z(v1),
		VEC3_X(v2), avg_y, VEC3_Z(v2),
	};

	const GLfloat texcoord[] = {
		0.0, 0.0,
		0.0, 1.0,
		1.0, 0.0,
		1.0, 1.0,
	};

	const GLfloat normal[] = {
		0.0, 1.0, 0.0,
	};

	int i;
	for(i = 0; i < 4; i++)
	{
		vertexr[i * 3] = vertex[i * 3];
		vertexr[i * 3 + 1] = vertex[i * 3 + 1];
		vertexr[i * 3 + 2] = vertex[i * 3 + 2];

		texcoordr[i * 2] = texcoord[i * 2];
		texcoordr[i * 2 + 1] = texcoord[i * 2 + 1];

		normalr[i * 3] = normal[0];
		normalr[i * 3 + 1] = normal[1];
		normalr[i * 3 + 2] = normal[2];
	}
}

void OpenGL_Plane_CenterLength_VTN(const GLfloat center[3], const GLfloat length[2], GLfloat *vertex, GLfloat *texcoord, GLfloat *normal)
{
	if(!vertex || !texcoord || !normal || !center || !length)
		return;
	GLfloat v1[3] = {VEC3_X(center) + VEC3_X(length), VEC3_Y(center), VEC3_Z(center) + VEC3_Y(length)};
	GLfloat v2[3] = {VEC3_X(center) - VEC3_X(length), VEC3_Y(center), VEC3_Z(center) - VEC3_Y(length)};
	OpenGL_Cube_MinMax_VTN(v1, v2, vertex, texcoord, normal);
}

void OpenGL_Plane(const GLfloat length[2])
{
	static unsigned cube_inited = 0;
	static GLfloat vertex[12];
	static GLfloat texcoord[8];
	static GLfloat normal[12];
	static GLfloat color[16];

	GLfloat vertex_draw[12];

	if(!cube_inited)
	{
		const GLfloat cube_colors[] = {
			1.0, 0.0, 0.0, 1.0,
			0.0, 1.0, 0.0, 1.0,
			0.0, 0.0, 1.0, 1.0,
			1.0, 1.0, 0.0, 1.0,
		};
		int i;
		for(i = 0; i < 4; i++)
		{
			color[i * 4] = cube_colors[i * 4];
			color[i * 4 + 1] = cube_colors[i * 4 + 1];
			color[i * 4 + 2] = cube_colors[i * 4 + 2];
			color[i * 4 + 3] = cube_colors[i * 4 + 3];
		}

		GLfloat min[] = {-0.5, 0.0, -0.5};
		GLfloat max[] = {0.5, 0.0, 0.5};
		OpenGL_Plane_MinMax_VTN(min, max, vertex, texcoord, normal);

		cube_inited = 1;
	}

	int i;
	for(i = 0; i < 12; i += 3)
	{
		vertex_draw[i] = vertex[i] * VEC3_X(length);
		vertex_draw[i + 2] = vertex[i + 2] * VEC3_Y(length);
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertex_draw);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoord);
	glNormalPointer(GL_FLOAT, 0, normal);
	glColorPointer(4, GL_FLOAT, 0, color);

	oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
