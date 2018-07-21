#include "gl/glut.h"
#include "gl_util.h"
#include "mesh.h"
#include "SOIL.h"

#include "netlizard/nl_util.h"
#include "netlizard/png_reader.h"
#include "netlizard/texture_v3_reader.h"

#include <unistd.h>
#define NEW(type, count) malloc(sizeof(type) * count)

#define TRACK_VER "../track01.png"
#define TRACK_TEX "../map1.png"
typedef struct _r
{
	size_t a1_length;
	size_t a2_length;
  short **a;
	size_t b_length;
  short *b;
	size_t c1_length;
	size_t c2_length;
  char **c;
  int d;
} r;

r *i = NULL;
static int egypt_3d_f_a(int paramInt1, int paramInt2);
static void egypt_3d_e_aa();
static void egypt_3d_print_r(r *a);

static int * ct3d_h_color_tex_l(char paramArrayOfByte[]);
static char * ct3d_h_index_tex_l(char paramArrayOfByte[], int paramBoolean, int paramInt1, int paramInt2, int paramInt3, int paramInt4);
static void ct3d_h_a2_tex_l(char paramArrayOfByte[]);
static void LoadCT3DTexL(Tex *g_tex, const char *data);

static const GLfloat rotation_unit = 2;
static const GLfloat move_unit = 2;
static const GLfloat turn_unit = 10;

static float yAxisRotate = 0;
static float xAxisRotate = 0;

static float x_t = 0;
static float y_t = -200.0;
static float z_t = 0;

static float x_r = 0;
static float y_r = 0;

static GLint delta_x = 0;
static GLint delta_y = 0;

GLuint textureId;
GLuint rboId;
GLuint fboId;
GLuint buffers[TotalBuffer];

Tex sky_tex;

int enable_framebuffer_object = 0;

typedef enum _Position
{
	Up,
	Down,
	Left,
	Right,
	Forward,
	Backward,
	TotalPosition
} Position;

typedef enum _Orientation
{
	TurnUp,
	TurnDown,
	TurnLeft,
	TurnRight,
	TotalOrientation
} Orientation;

static GLboolean move[TotalPosition] = {GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE};
static GLboolean turn[TotalOrientation] = {GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE};

static void DrawGL();
static void InitGL();
static void ReshapeGL(int w, int h);
static void Clear();
static Bool KeyEvent(KeySym key, Bool pressed, int x,int y);
static Bool MouseEvent(int button, Bool pressed, int x, int y);
static Bool MotionEvent(int button, Bool pressed, int x, int y, int dx, int dy);
static Bool IdleEvent();

static void RenderNLMesh();

int main(int argc, char **argv)
{
	karinInitX11GLObjectAndGLUT(&argc, argv);
	karinSetWindowPosiotionAndSize(0, 0, 480, 360);
	karinCreateGLXWindow("GL Racing Evolution 3D");
	karinRegisterInitFunc(InitGL);
	karinRegisterDrawFunc(DrawGL);
	karinRegisterReshapeFunc(ReshapeGL);
	karinRegisterExitFunc(Clear);
	karinRegisterMouseFunc(MouseEvent);
	karinRegisterKeyFunc(KeyEvent);
	karinRegisterMotionFunc(MotionEvent);
	karinRegisterIdleFunc(IdleEvent);
	karinFullscreen(True);
	karinMainLoop();

	return 0;
}

void InitGL()
{
	glClearColor(1.0, 1.0, 1.0 ,1.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 854, 480, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenRenderbuffersEXT(1, &rboId);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rboId);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, 854, 480);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

	glGenFramebuffersEXT(1, &fboId);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);

	// attach the texture to FBO color attachment point
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,        // 1. fbo target: GL_FRAMEBUFFER 
			GL_COLOR_ATTACHMENT0_EXT,  // 2. attachment point
			GL_TEXTURE_2D,         // 3. tex target: GL_TEXTURE_2D
			textureId,             // 4. tex ID
			0);                    // 5. mipmap level: 0(base)

	// attach the renderbuffer to depth attachment point
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,      // 1. fbo target: GL_FRAMEBUFFER
			GL_DEPTH_ATTACHMENT_EXT, // 2. attachment point
			GL_RENDERBUFFER_EXT,     // 3. rbo target: GL_RENDERBUFFER
			rboId);              // 4. rbo ID

	// check FBO status
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
		printf("status err\n");

	// switch back to window-system-provided framebuffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	GLbyte arrayOfByte[36];
	GLuint index[18] = {
		0, 1, 2, 1, 2, 3,
		4, 5, 6, 5, 6, 7,
		8, 9, 10, 9, 10, 11
	};
	int k;
	for(k = 0; k < 36; k++) {
		arrayOfByte[k] = 0;
	}
	float f1 = 0.095F;
	arrayOfByte[0] = -7;
	arrayOfByte[2] = 12;
	arrayOfByte[3] = -6;
	arrayOfByte[5] = 14;
	arrayOfByte[6] = 7;
	arrayOfByte[8] = 12;
	arrayOfByte[9] = 6;
	arrayOfByte[11] = 14;
	arrayOfByte[12] = -7;
	arrayOfByte[13] = 0;
	arrayOfByte[14] = -12;
	arrayOfByte[15] = -7;
	arrayOfByte[16] = 0;
	arrayOfByte[17] = 12;
	arrayOfByte[18] = 7;
	arrayOfByte[19] = 0;
	arrayOfByte[20] = -12;
	arrayOfByte[21] = 7;
	arrayOfByte[22] = 0;
	arrayOfByte[23] = 12;
	arrayOfByte[24] = -6;
	arrayOfByte[25] = 0;
	arrayOfByte[26] = -14;
	arrayOfByte[27] = -7;
	arrayOfByte[28] = 0;
	arrayOfByte[29] = -12;
	arrayOfByte[30] = 6;
	arrayOfByte[31] = 0;
	arrayOfByte[32] = -14;
	arrayOfByte[33] = 7;
	arrayOfByte[34] = 0;
	arrayOfByte[35] = -12;
	GLfloat vertex[36];
	for(k = 0; k < 36; k++)
		vertex[k] = f1 * (GLfloat)arrayOfByte[k];

	GLfloat scene_vertex[8] = {
		0.0, 0.0,
		854.0, 0.0,
		0.0, 480.0,
		854.0, 480.0
	};

	GLfloat scene_texcoord[8] = {
		1.0, 1.0,
		0.0, 1.0,
		1.0, 0.0,
		0.0, 0.0,
	};
	buffers[VertexBuffer] = GLNewBuffer(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, scene_vertex, GL_STATIC_DRAW);
	buffers[TexcoordBuffer] = GLNewBuffer(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, scene_texcoord, GL_STATIC_DRAW);

	memset(&mesh, 0, sizeof(NL_Mesh));
	const char *obj_file = TRACK_VER;
	const char *tex_file = TRACK_TEX;
	const char *sky_tex_file = "../sky.png";
	a_ReadMeshFile(obj_file);
	if(IsPNGFile(tex_file))
		LoadTex(&mesh.tex, tex_file);
	else
	{
		printf("not png. try parse.\n");
		unsigned long len = 0;
		char *data = ReadFile(tex_file, &len);
		ParsePNG(data, len);
		LoadTexFromMemory(&mesh.tex, data, len);
	}
	if(IsPNGFile(sky_tex_file))
		LoadTex(&sky_tex, sky_tex_file);
	else
	{
		printf("not png. try parse.\n");
		unsigned long len = 0;
		char *data = ReadFile(sky_tex_file, &len);
		ParsePNG(data, len);
		LoadTexFromMemory(&sky_tex, data, len);
	}


	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	char *texl = ReadFile("l2.png", NULL);
	int *color = ct3d_h_color_tex_l(texl);
	char *indexs = ct3d_h_index_tex_l(texl, 0, 0, 0, 0, 0);
	ct3d_h_a2_tex_l(indexs);
	GLubyte *data = malloc(64 * 64 * 3 * sizeof(GLubyte));
	int i;
	for(i = 0; i < 64 * 64; i++)
	{
		data[i * 3] = color[indexs[i]] << 8 >> 24;
		data[i * 3 + 1] = color[indexs[i + 1]] << 16 >> 24;
		data[i * 3 + 2] = color[indexs[i + 2]] << 24 >> 24;
	};
	//LoadCT3DTexL(&sky_tex, data);
	printf("glistexture -> %d\n", glIsTexture(sky_tex.texid));
	free(texl);
	free(data);
	free(indexs);
	free(color);
	//egypt_3d_e_aa();
	/*
  int h[] = { 1668246830, 1852795753, 1630432617, 1680766313, 776369516, 1816355182, 1986097920 };
	array *a = new_array(nl_int, 7, h);
	printf("___%s\n", nlParseString(a));
	*/
	//nlHandlePNGFromFileToFile("un1.png", "ps.png");
	png_texture *t = nlReadTexturePNGV3FromFile("w1.png", -1);
	unsigned char * d = nlMakeOpenGLTextureDataRGBA(t);
	LoadCT3DTexL(&sky_tex, d);
	nlSaveTextureImageV3FromFile("w1.png", -1, "tst.bmp", SOIL_SAVE_TYPE_BMP);
	nlSaveTexturePNGV3FromFileToFile("tst.bmp", -1, "untst.png");
	nlSaveTextureImageV3FromFile("untst.png", -1, "ununtst.bmp", SOIL_SAVE_TYPE_BMP);
}

void DrawGL()
{
	if(enable_framebuffer_object)
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
		glViewport(0, 0, width, height);
		Render2D(0.0, width, 0.0, height);
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindTexture(GL_TEXTURE_2D, sky_tex.texid);
			//glColor3f(0.01 * i, 0.02 * i, 0.03 * i);
			glBindBuffer(GL_ARRAY_BUFFER, buffers[TexcoordBuffer]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
			glBindBuffer(GL_ARRAY_BUFFER, buffers[VertexBuffer]);
			glVertexPointer(2, GL_FLOAT, 0, NULL);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
		Render3D(/*0.3926991*/45, width, height, 0.25, 500);
		{
			glPushMatrix();
			{
				//gluLookAt(x_t, z_t, y_t, 0, 0, 0, 0, 1, 0);
				glRotatef(y_r,0,1,0);
				glRotatef(x_r,1,0,0);

				glTranslatef(x_t, z_t, y_t);

				//glScalef(1.0, 1.5, 1.0);

				glRotatef(yAxisRotate,0,1,0);
				glRotatef(xAxisRotate,1,0,0);

				glPushMatrix();
				{
					RenderNLMesh();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

		glViewport(0, 0, width, height);
		Render2D(0.0, width, 0.0, height);
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindTexture(GL_TEXTURE_2D, textureId);
			//glColor3f(0.01 * i, 0.02 * i, 0.03 * i);
			glBindBuffer(GL_ARRAY_BUFFER, buffers[TexcoordBuffer]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
			glBindBuffer(GL_ARRAY_BUFFER, buffers[VertexBuffer]);
			glVertexPointer(2, GL_FLOAT, 0, NULL);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
	}
	else
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);
		Render2D(0.0, width, 0.0, height);
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindTexture(GL_TEXTURE_2D, sky_tex.texid);
			//glColor3f(0.01 * i, 0.02 * i, 0.03 * i);
			glBindBuffer(GL_ARRAY_BUFFER, buffers[TexcoordBuffer]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
			glBindBuffer(GL_ARRAY_BUFFER, buffers[VertexBuffer]);
			glVertexPointer(2, GL_FLOAT, 0, NULL);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
		Render3D(/*0.3926991*/45, width, height, 0.25, 500);
		{
			glPushMatrix();
			{
				//gluLookAt(x_t, z_t, y_t, 0, 0, 0, 0, 1, 0);
				glRotatef(y_r,0,1,0);
				glRotatef(x_r,1,0,0);
				glTranslatef(x_t, z_t, y_t);


				//glScalef(1.0, 1.5, 1.0);

				//glRotatef(yAxisRotate,0,1,0);
				//glRotatef(xAxisRotate,1,0,0);

				RenderNLMesh();
			}
			glPopMatrix();
		}
	}

	glFlush();
}

void ReshapeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	glLoadIdentity();
}

void Clear()
{
	int i;
	for(i = 0; i < mesh.mesh_count; i++)
	{
		Mesh *m = mesh.meshes + i;
		int j;
		for(j = 0; j < TotalBuffer; j++)
			if(glIsBuffer(m -> buffers[j]))
				glDeleteBuffers(1, &m -> buffers[j]);
		free(m -> strips);
	}
	if(glIsTexture(mesh.tex.texid))
		glDeleteTextures(1, &(mesh.tex.texid));
}

Bool KeyEvent(KeySym key, Bool pressed, int x, int y)
{
	Position p = TotalPosition;
	Orientation o = TotalOrientation;
	switch(key)
	{
		case 'h':
			//exit(EXIT_SUCCESS);
			karinPostExit();
			return True;
		case 'w':
			p = Forward;
			break;
		case 's':
			p = Backward;
			break;
		case 'a':
			p = Left;
			break;
		case 'd':
			p = Right;
			break;
		case 'e':
			p = Up;
			break;
		case 'q':
			p = Down;
			break;
		case XK_Up:
			o = TurnUp;
			break;
		case XK_Down:
			o = TurnDown;
			break;
		case XK_Left:
			o = TurnLeft;
			break;
		case XK_Right:
			o = TurnRight;
			break;
		default:
			return False;
	}
	if(p != TotalPosition)
		move[p] = (GLboolean)pressed;
	if(o != TotalOrientation)
		turn[o] = (GLboolean)pressed;
	return True;
}

Bool MouseEvent(int button, Bool pressed, int x, int y)
{
	if(!pressed)
	{
		delta_x = 0;
		delta_y = 0;
		return True;
	}
	return False;
}

Bool MotionEvent(int button, Bool pressed, int x, int y, int dx, int dy)
{
	if(pressed)
	{
		delta_x = dx;
		delta_y = dy;
		return True;
	}
	return False;
}

Bool IdleEvent()
{
	//usleep(3000);
	if(turn[TurnUp])
		x_r -= turn_unit;
	if(turn[TurnDown])
		x_r += turn_unit;
	if(turn[TurnLeft])
		y_r -= turn_unit;
	if(turn[TurnRight])
		y_r += turn_unit;
	y_r = formatAngle(y_r);
	x_r = formatAngle(x_r);
	if(move[Forward])
		y_t += abs(y_r) < 90 || abs(y_r) >= 270  ? move_unit : -move_unit;
	if(move[Backward])
		y_t -= abs(y_r) < 90 || abs(y_r) >= 270 ? move_unit : -move_unit;
	if(move[Left])
		x_t += abs(x_r) < 90 || abs(x_r) >= 270  ? move_unit : -move_unit;
	if(move[Right])
		x_t -= abs(x_r) < 90 || abs(x_r) >= 270  ? move_unit : -move_unit;
	if(move[Up])
		z_t -= move_unit;
	if(move[Down])
		z_t += move_unit;

	if(delta_x != 0 || delta_y != 0)
	{
		xAxisRotate += delta_y * rotation_unit;
		yAxisRotate += delta_x * rotation_unit;
		return True;
	}

	int i;
	for(i = 0; i < TotalPosition; i++)
		if(move[i])
			return True;
	for(i = 0; i < TotalOrientation; i++)
		if(turn[i])
			return True;
	return False;
}

void RenderNLMesh()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D, mesh.tex.texid);
	int i;
	for(i = 0; i < mesh.mesh_count; i++)
	//for(i = 1; i < 44; i++)
	{
		glPushMatrix();
		{
		//glColor3f(0.01 * i, 0.02 * i, 0.03 * i);
		Mesh *m = mesh.meshes + i;
		glTranslatef(m -> translate.x, 0, m -> translate.y);
		int valid = 1;
		int j;
		for(j = 0; j < TotalBuffer; j++)
		{
			if(!glIsBuffer(m -> buffers[j]))
			{
				valid = 0;
				break;
			};
		}
		if(!valid)
			continue;
		glBindBuffer(GL_ARRAY_BUFFER, m -> buffers[TexcoordBuffer]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, m -> buffers[VertexBuffer]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m -> buffers[IndexBuffer]);
		int k;
		int l = 0;
		for(k = 0; k < m -> primitive; k++)
		{
			GLuint s = m -> strips[k];
			glDrawElements(GL_TRIANGLE_STRIP, s, GL_UNSIGNED_INT, (GLfloat *)NULL + sizeof(GLuint) * l);
			l += s;
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		//glTranslatef(m -> translate.x, m -> translate.y, m -> translate.z);
		}
		glPopMatrix();
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

int * ct3d_h_color_tex_l(char paramArrayOfByte[])
{
	int i2 = 3;
	int i3 = 0;
	if (paramArrayOfByte[3] == 1) {
		i3 = 1;
	}
	i2++;
	int i1;
	if ((i1 = paramArrayOfByte[4]) < 0) {
		i1 += 256;
	}
	int* arrayOfInt = NEW(int, i1);
	if (i3 == 0)
	{
		int i4 = 0;
		//tmpTernaryOp = paramArrayOfByte;
		while (i4 < i1)
		{
			arrayOfInt[i4] = ((paramArrayOfByte[(++i2)] << 16) + (paramArrayOfByte[(++i2)] << 8) + paramArrayOfByte[(++i2)]);
			i4++;
		}
	}
	else
	{
		int i5;
		for (i5 = 0; i5 < i1; i5++) {
			if (paramArrayOfByte[(++i2)] != 0)
			{
				arrayOfInt[i5] = (-16777216 + (paramArrayOfByte[(++i2)] << 16) + (paramArrayOfByte[(++i2)] << 8) + paramArrayOfByte[(++i2)]);
			}
			else
			{
				i2 += 3;
				arrayOfInt[i5] = 0;
			}
		}
	}
	return arrayOfInt;
}

char * ct3d_h_index_tex_l(char paramArrayOfByte[], int paramBoolean, int paramInt1, int paramInt2, int paramInt3, int paramInt4)
{
	int i2 = 0;
	int i3 = 0;
	if (paramArrayOfByte[3] == 1) {
		i3 = 1;
	}
	int i4;
	if ((i4 = paramArrayOfByte[4]) < 0) {
		i4 += 256;
	}
	if (i3 != 0) {
		i2 = 4 + i4 * 4;
	} else {
		i2 = 4 + i4 * 3;
	}
	int i5;
	int i6;
	char *arrayOfByte;
	int i7;
	if (!paramBoolean)
	{
		i5 = paramArrayOfByte[(++i2)];
		i6 = paramArrayOfByte[(++i2)];
		if (i5 < 0) {
			i5 += 256;
		}
		if (i6 < 0) {
			i6 += 256;
		}
		if (i5 == 0) {
			i5 = 256;
		}
		if (i6 == 0) {
			i6 = 256;
		}
		int i1;
		i1 = i5 * i6;
		printf("i5 * i6 = %d * %d\n", i5, i6);
		arrayOfByte = NEW(char, i1);
		for (i7 = 0; i7 < i1; i7++) {
			arrayOfByte[i7] = paramArrayOfByte[(++i2)];
		}
	}
	else
	{
		i5 = paramArrayOfByte[(++i2)];
		i2++;
		i6 = 0;
		if (i5 < 0) {
			i5 += 256;
		}
		i7 = 0;
		arrayOfByte = NEW(char, paramInt3 * paramInt4);
		i2 += paramInt2 * i5 + paramInt1;
		i2++;
		int i9;
		for (i9 = 0; i9 < paramInt4; i9++)
		{
			int i8 = i9 * i5 + i2;
			int i10;
			for (i10 = 0; i10 < paramInt3; i10++)
			{
				arrayOfByte[i7] = paramArrayOfByte[(i8 + i10)];
				i7++;
			}
		}
	}
	return arrayOfByte;
}

void ct3d_h_a2_tex_l(char paramArrayOfByte[])
{
	int i2;
	int i3;
	for (i2 = 63; i2 >= 0; i2--) {
		for (i3 = 31; i3 >= 0; i3--)
		{
			int i1 = paramArrayOfByte[(i3 * 64 + i2)];
			paramArrayOfByte[(i3 * 64 + i2)] = paramArrayOfByte[((63 - i3) * 64 + i2)];
			paramArrayOfByte[((63 - i3) * 64 + i2)] = i1;
		}
	}
}

void LoadCT3DTexL(Tex *g_tex, const char *data)
{
	if(!g_tex || !data)
		return;

	g_tex -> format = GL_RGBA;
	g_tex -> width = 256;
	g_tex -> height = 256;
	// SOIL_load_OGL_texture()
	glGenTextures(1, &(g_tex -> texid));
	glBindTexture(GL_TEXTURE_2D, g_tex -> texid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, g_tex -> width, g_tex -> height, 0, g_tex -> format, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);

}

int egypt_3d_f_a(int paramInt1, int paramInt2)
{
	if (paramInt1 < 0) {
		paramInt1 += 256;
	}
	if (paramInt2 < 0) {
		paramInt2 += 256;
	}
	return paramInt1 + paramInt2 * 256;
}

void egypt_3d_e_aa()
{
	i = NEW(r, 8);
	int i6;
	for (i6 = 0; i6 < 1; i6++) {
		if (1)
		{
			int i1 = -2;
			char *arrayOfByte = ReadFile("un1.png", NULL);
			r *localr = &(i[i6]);
			i1 += 2;
			i1 += 2;
			i1 += 2;
			i1 += 2;
			i1 += 2;
			i1 += 2;
			i1 += 2;
			int i3 = egypt_3d_f_a(arrayOfByte[12], arrayOfByte[13]);
			i1 += 2;
			int i2 = egypt_3d_f_a(arrayOfByte[14], arrayOfByte[15]);
			i1 += 2;
			int i4 = egypt_3d_f_a(arrayOfByte[16], arrayOfByte[17]);
			i1 += 2;
			int i5 = egypt_3d_f_a(arrayOfByte[18], arrayOfByte[19]);
			localr -> a = NEW(short *, i5);
			localr -> c = NEW(char *, i5);
			localr -> d = i3;
			localr -> a1_length = i5;
			localr -> c1_length = i5;
			int i7;
			for (i7 = 0; i7 < i5; i7++)
			{
				localr -> c2_length = i2 * 3;
				localr -> c[i7] = NEW(char, i2 * 3);
				localr -> a2_length = i3 * 3;
				localr -> a[i7] = NEW(short, i3 * 3);
			}
			localr -> b_length = i2 * 16;
			localr -> b = NEW(short, i2 * 16);
			i4 *= 2;
			short *arrayOfShort = NEW(short, i4);
			int i8;
			int i9;
			for (i8 = 0; i8 < i5; i8++) {
				for (i9 = 0; i9 < i3; i9++)
				{
					i1 += 2;
					localr -> a[i8][(i9 * 3)] = ((short)egypt_3d_f_a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
					i1 += 2;
					localr -> a[i8][(i9 * 3 + 1)] = ((short)egypt_3d_f_a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
					i1 += 2;
					localr -> a[i8][(i9 * 3 + 2)] = ((short)egypt_3d_f_a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
				}
			}
			int i10 = i2 * 16;
			int i11;
			for (i11 = 0; i11 < i10; i11 += 16)
			{
				i1 += 2;
				localr -> b[i11] = ((short)(egypt_3d_f_a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 3));
				i1 += 2;
				localr -> b[(i11 + 1)] = ((short)(egypt_3d_f_a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 3));
				i1 += 2;
				localr -> b[(i11 + 2)] = ((short)(egypt_3d_f_a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 3));
			}
			i10 = i2 * 3;
			i1++;
			int i12;
			int i13;
			for (i12 = 0; i12 < i5; i12++) {
				for (i13 = 0; i13 < i10; i13 += 3)
				{
					i1++;
					localr -> c[i12][i13] = arrayOfByte[i1];
					i1++;
					localr -> c[i12][(i13 + 1)] = arrayOfByte[i1];
					i1++;
					localr -> c[i12][(i13 + 2)] = arrayOfByte[i1];
				}
			}
			i1--;
			int i14;
			for (i14 = 0; i14 < i4; i14 += 2)
			{
				i1 += 2;
				arrayOfShort[i14] = ((short)(int)(256L * egypt_3d_f_a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 1000L));
				i1 += 2;
				arrayOfShort[(i14 + 1)] = ((short)(int)(256L * egypt_3d_f_a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 1000L));
			}
			i2 *= 16;
			int i15;
			for (i15 = 0; i15 < i2; i15 += 16)
			{
				i1 += 2;
				localr -> b[(i15 + 3)] = arrayOfShort[(egypt_3d_f_a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)];
				localr -> b[(i15 + 4)] = arrayOfShort[(egypt_3d_f_a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)];
				i1 += 2;
				localr -> b[(i15 + 5)] = arrayOfShort[(egypt_3d_f_a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)];
				localr -> b[(i15 + 6)] = arrayOfShort[(egypt_3d_f_a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)];
				i1 += 2;
				localr -> b[(i15 + 7)] = arrayOfShort[(egypt_3d_f_a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)];
				localr -> b[(i15 + 8)] = arrayOfShort[(egypt_3d_f_a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)];
			}
			int i16;
			for (i16 = 0; i16 < i2; i16 += 16)
			{
				i1 += 2;
				localr -> b[(i16 + 9)] = ((short)(char)egypt_3d_f_a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
				//T[localr.b[(i16 + 9)]] = true;
			}
			egypt_3d_print_r(localr);
		}
	}
	//U();
}

void egypt_3d_print_r(r *a)
{
	int i;
	int j;
	printf("a[%d][%d] ------>\n", a -> a1_length, a -> a2_length);
	for(i = 0; i < a -> a1_length; i++)
	{
		for(j = 0; j < a -> a2_length; j++)
			printf("%d ", a -> a[i][j]);
		printf("\n");
	}
	printf("---------\n");
	printf("b[%d] ------>\n", a -> b_length);
	for(i = 0; i < a -> b_length; i++)
	{
		printf("%d ", a -> b[i]);
	}
	printf("\n");
	printf("---------\n");
	printf("c[%d][%d] ------>\n", a -> c1_length, a -> c2_length);
	for(i = 0; i < a -> c1_length; i++)
	{
		for(j = 0; j < a -> c2_length; j++)
			printf("%d ", a -> c[i][j]);
		printf("\n");
	}
	printf("---------\n");
	printf("d = %d ------->\n", a -> d);
}
