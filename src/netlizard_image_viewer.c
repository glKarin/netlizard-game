#include "netlizard_viewer.h"
#include "glk/glk.h"
#include "nl_gl.h"
#include "gl_3d_main.h"

#include "netlizard/texture_v2_reader.h"
#include "netlizard/texture_v3_reader.h"
#include "netlizard/texture_reader.h"
#include "netlizard/png_reader.h"

#define PAGE_NAME "NETLizardImageViewer"

#define MOVE_UNIT 0.05
#define MOUSE_MOVE_UNIT 0.001
#define SCALE_UNIT 0.1

#define MAX_SCALE_LIMIT 2.0
#define MIN_SCALE_LIMIT 0.1

static int Viewer_IdleFunc(void);
static int Viewer_KeyFunc(int k, int a, int p, int x, int y);
static int Viewer_MouseFunc(int b, int p, int x, int y);
static int Viewer_MotionFunc(int b, int p, int x, int y, int dx, int dy);
static void Viewer_DrawFunc(void);
static void Viewer_ReshapeFunc(int w, int h);
static void Viewer_InitFunc(void);
static void Viewer_FreeFunc(void);
static Main3DStoreFunction_f Viewer_StoreFunc = NULL;
static Main3DRestoreFunction_f Viewer_RestoreFunc = NULL;
static Main3DMouseClickFunction Viewer_ClickFunc = NULL;


static void Viewer_InitBufferObject(void);
static void Viewer_InitTexture(void);

#define KARIN_CASEANDEQUAL(value, index) \
	case value:\
		i = index;\
		break;

static char *image_file = NULL;
static texture * image_texture = NULL;
static int compress = 0;

static GLfloat instX = 0.0f;
static GLfloat instY = 0.0f;
static GLfloat scale = 1.0f;

static GLboolean mouseFirstMove = GL_TRUE;
static GLuint bufferIDs[total_buffer_type];

static int game;

int Viewer_IdleFunc(void)
{
	if(action_state[MoveUp_Action] || action_state[TurnUp_Action])
		instY += MOVE_UNIT;
	if(action_state[MoveDown_Action] || action_state[TurnDown_Action])
		instY -= MOVE_UNIT;
	if(action_state[MoveLeft_Action] || action_state[TurnLeft_Action])
		instX -= MOVE_UNIT;
	if(action_state[MoveRight_Action] || action_state[TurnRight_Action])
		instX += MOVE_UNIT;

	if((action_state[Forward_Action] || action_state[ZoomOut_Action]) && scale < MAX_SCALE_LIMIT)
		scale = KARIN_MIN(scale + SCALE_UNIT, MAX_SCALE_LIMIT);
	if((action_state[Backward_Action] || action_state[ZoomIn_Action]) && scale > MIN_SCALE_LIMIT)
		scale = KARIN_MAX(scale - SCALE_UNIT, MIN_SCALE_LIMIT);

	return 1;
}

//OpenGL Init
void Viewer_InitBufferObject(void)
{
	GLfloat per = (GLfloat)image_texture->width / (GLfloat)image_texture->height;
	GLdouble ortho_per = (GLdouble)height / (GLdouble)width;
	GLfloat vertex[] = {
		-per / 2, -ortho_per,
		-per / 2, ortho_per,
		per / 2, -ortho_per,
		per / 2, ortho_per
	};

	/*
	 * GL_REPEAT 纹理坐标大于1.0 重复绘制多个纹理拷贝。
	 * GL_CLAMP 纹理坐标大于1.0，将裁剪到1.0，对于大表面，只绘制左下角的一份纹理拷贝。
	 */
	GLfloat texcoord[] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};
	
	bufferIDs[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, vertex, GL_STATIC_DRAW);
	bufferIDs[texcoord_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, texcoord, GL_STATIC_DRAW);
}

void Viewer_InitTexture(void)
{
	if(!image_file)
		return;
	new_netlizard_texture_from_file new_image_texture;
	NETLizard_Texture_Type type;
	switch(game)
	{
		case nl_shadow_of_egypt_3d:
		case nl_clone_3d:
		case nl_contr_terrorism_3d_episode_3:
			type = compress ? Texture_3DEngineV3Compress_Type : Texture_3DEngineV3_Type;
			break;
		case nl_contr_terrorism_3d:
		case nl_contr_terrorism_3d_episode_2:
		case nl_army_ranger_3d:
			type = Texture_3DEngineV2_Type;
			break;
		case nl_racing_evolution_3d:
		case nl_2d_game:
			type = Texture_EncodePNG_Type;
			break;
		case nl_old_game:
			type = Texture_NormalPNG_Type;
		default:
			type = nlCheckPNGFileType(image_file);
			break;
	}
	switch(type)
	{
		case Texture_3DEngineV3Compress_Type:
			new_image_texture = new_texture_from_nl_v3_3d_compress_file;
			break;
		case Texture_3DEngineV3_Type:
			new_image_texture = new_texture_from_nl_v3_3d_file;
			break;
		case Texture_3DEngineV2_Type:
			new_image_texture = new_texture_from_nl_v2_3d_file;
			break;
		case Texture_EncodePNG_Type:
			new_image_texture = new_texture_from_nl_file;
			break;
		case Texture_NormalPNG_Type:
			new_image_texture = new_OpenGL_texture_2d;
			break;
		default:
			new_image_texture = new_OpenGL_texture_2d;
			break;
	}
	image_texture = new_image_texture(image_file);
}

//OpenGL
void Viewer_InitFunc(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	oglDisable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	oglEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glCullFace(GL_BACK);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	oglEnable(GL_TEXTURE_2D);
	oglEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Viewer_InitTexture();
	Viewer_InitBufferObject();
}

void Viewer_DrawFunc(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor4f(1.0, 1.0, 1.0, 1.0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glPushMatrix();
	{
		oglBindTexture(GL_TEXTURE_2D, image_texture->texid);

		glBindBuffer(GL_ARRAY_BUFFER, bufferIDs[texcoord_buffer_type]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, bufferIDs[vertex_buffer_type]);
		glVertexPointer(2, GL_FLOAT, 0, NULL);

		glTranslatef(-instX, -instY, 0);
		glScalef(1.0 * scale, 1.0 * scale, 1.0);
		oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	}
	glPopMatrix();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	oglBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Viewer_ReshapeFunc(int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLdouble per = (GLdouble)h / (GLdouble)w;
	gluOrtho2D(-1.0, 1.0f, -per, per);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//Event Callback
void Viewer_FreeFunc(void)
{
	int i;
	for(i = 0; i < total_buffer_type; i++)
	{
		if(glIsBuffer(bufferIDs[i]))
		glDeleteBuffers(1, bufferIDs + i);
	}
	if(image_texture)
	{
		glDeleteTextures(1, &image_texture->texid);
		free(image_texture);
	}
	if(image_file)
		free(image_file);
}

int Viewer_KeyFunc(int key, int a, int pressed, int x, int y)
{
	int res = 0;
	switch(a)
	{
		case Quit_Action:
			if(pressed)
			{
				Main3D_Shutdown();
				res |= 1;
			}
			break;
		default:
			break;
	}
	return res;
}

int Viewer_MouseFunc(int button, int pressed, int x, int y)
{
	mouseFirstMove = GL_TRUE;
	return 0;
}

int Viewer_MotionFunc(int button, int pressed, int x, int y, int dx, int dy)
{
	if(mouseFirstMove)
	{
		mouseFirstMove = GL_FALSE;
		return 0;
	}
	if(delta_x_3d != 0)
		instX += (- delta_x_3d * MOUSE_MOVE_UNIT);
	if(delta_y_3d != 0)
		instY += (delta_y_3d * MOUSE_MOVE_UNIT);

	return 1;
}

int Viewer_NETLizardImageInitMain(const char *g, const char *src)
{
	if(!src)
		return 0;
	if(!g)
		game = -1;
	else if(strcasecmp(g, "egypt3d") == 0)
		game = nl_shadow_of_egypt_3d;
	else if(strcasecmp(g, "ct3d") == 0)
		game = nl_contr_terrorism_3d;
	else if(strcasecmp(g, "ct3dep2") == 0)
		game = nl_contr_terrorism_3d_episode_2;
	else if(strcasecmp(g, "specnaz3d") == 0)
		game = nl_army_ranger_3d;
	else if(strcasecmp(g, "clone3d") == 0)
		game = nl_clone_3d;
	else if(strcasecmp(g, "ct3dep3") == 0)
		game = nl_contr_terrorism_3d_episode_3;
	else if(strcasecmp(g, "re3d") == 0)
		game = nl_racing_evolution_3d;
	else if(strcasecmp(g, "2d") == 0)
		game = nl_2d_game;
	else if(strcasecmp(g, "tex_v2") == 0)
		game = nl_contr_terrorism_3d;
	else if(strcasecmp(g, "tex_v3") == 0)
		game = nl_clone_3d;
	else if(strcasecmp(g, "tex_v3z") == 0)
	{
		game = nl_clone_3d;
		compress = 1;
	}
	else
		game = nl_old_game;
	image_file = strdup(src);
	return 1;
}

void Viewer_NETLizardImageRegisterFunction(void)
{
	glk_function func;

	func = REGISTER_RENDER_FUNCTION(Viewer);
	Main3D_InitRenderPage(PAGE_NAME, &func);
}

