#include "gl_3d_main.h"
#include "glk/glk.h"
#include "nl_std.h"
#include "netlizard/nl_util.h"
#include "local/file_system.h"

#include <ctype.h>

#define CLICK_ZERO 5
#define CLICK_TIME 500 //ms 

#define DEFAULT_KEYMAP_FILE "key.map"
#define NETLIZARD_FONT_TEX_FILE _KARIN_RESOURCE_DIR"resource/font/cats_love/fnt.png"
#define NETLIZARD_FONT_MAP_FILE _KARIN_RESOURCE_DIR"resource/font/cats_love/cf.png"

static const int CASE_A_Z = Harmattan_K_a - Harmattan_K_A;

font fnt;

GLboolean init_glk = GL_FALSE;

GLfloat rotation_unit_3d = 1.0;
GLfloat move_unit_3d = 1.0;
GLfloat turn_unit_3d = 1.0;

GLfloat y_a_3d = 0.0;
GLfloat x_a_3d = 0.0;

GLfloat x_t_3d = 0.0;
GLfloat y_t_3d = 0.0;
GLfloat z_t_3d = 0.0;

GLfloat x_r_3d = 0.0;
GLfloat y_r_3d = 0.0;

GLfloat tp_x_t_3d = 0.0;
GLfloat tp_y_t_3d = 0.0;
GLfloat tp_z_t_3d = 0.0;

GLfloat tp_x_r_3d = 0.0;
GLfloat tp_y_r_3d = 0.0;

GLint delta_x_3d = 0;
GLint delta_y_3d = 0;

GLfloat view_y_angle = 0.0;
GLfloat view_x_angle = 0.0;
GLboolean view_free_mode = GL_FALSE;

GLsizei viewport_height = 200;
GLsizei viewport_width = 480;

GLboolean is_cross = GL_FALSE;
GLboolean is_rotate = GL_FALSE;

GLboolean key_ignore_case = GL_TRUE;

int key_action[Harmattan_Total_Key] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int key_state[Harmattan_Total_Key] = {0};

int action_state[Total_Action] = {0};

static int show_comment = 1;
static long long mouse_click_time = 0;
static int mouse_click_x = 0;
static int mouse_click_y = 0;
static char *keymap_file = NULL;

static void Main3D_LoadKeyActionMapFromDefault(void);
static void Main3D_LoadKeyActionMapFromFile(const char *file);
static Harmattan_Key Main3D_ConvertXKey(KeySym key);
static void Main3D_MakeKeyMapFile(const char *file);
static void Main3D_PrintKeyMap(void);

static Main3DInitFunction InitNETLizard3D = NULL;
static Main3DDrawFunction DrawNETLizard3D = NULL;
static Main3DFreeFunction FreeNETLizard3D = NULL;
static Main3DIdleEventFunction IdleNETLizard3D = NULL;
static Main3DKeyEventFunction KeyNETLizard3D = NULL;
static Main3DMouseMotionFunction MotionNETLizard3D = NULL;
static Main3DReshapeFunction ReshapeNETLizard3D = NULL;
static Main3DMouseFunction MouseNETLizard3D = NULL;
static Main3DMouseClickFunction MouseClickNETLizard3D = NULL;

static void Main3D_DrawGLFunc();
static void Main3D_InitGLFunc();
static void Main3D_ReshapeGLFunc(int w, int h);
static void Main3D_FreeGLFunc();
static unsigned Main3D_KeyEventFunc(int key, unsigned pressed, int x,int y);
static unsigned Main3D_MouseEventFunc(int button, unsigned pressed, int x, int y);
static unsigned Main3D_MouseClickEventFunc(int button, int x, int y);
static unsigned Main3D_MouseMotionEventFunc(int button, unsigned pressed, int x, int y, int dx, int dy);
static unsigned Main3D_IdleEventFunc(void);

void Main3D_MainLoop(void)
{
	if(!init_glk)
		return;
	if(karinIsRunning())
		karinPostExit();
	Main3D_RegisterGLKFunction();

	karinMainLoop();
}

void Main3D_Shutdown(void)
{
	if(init_glk)
	{
		if(karinIsRunning())
			karinPostExit();
		if(!karinIsSingle())
			karinShutdown();
		init_glk = GL_FALSE;
	}
}

void Main3D_Stop(void)
{
	if(init_glk)
	{
		if(karinIsSingle())
			karinSetSingle(0);
		if(karinIsRunning())
			karinPostExit();
	}
	Main3D_FreeGLFunc();
}

void Main3D_InitGLK(int x, int y, int w, int h, const char *title, int f, int fs)
{
	if(!init_glk)
	{
		karinInitGLctxObject();
		karinSetWindowPosiotionAndSize(x, y, w, h);
		karinCreateGLRenderWindow(title);
		karinFullscreen(fs);
		init_glk = karinHasInitGLctx();
	}
	if(init_glk && !karinIsRunning())
	{
		karinSetSingle(1);
		if(f > 0)
			karinSetMaxFPS(f);
		//Main3D_Reset();
	}
	Main3D_LoadKeyActionMapFromDefault();
	Main3D_LoadKeyActionMapFromFile(NULL);
	Main3D_PrintKeyMap();
}

void Main3D_RegisterGLKFunction(void)
{
	karinRegisterInitFunc(Main3D_InitGLFunc);
	karinRegisterDrawFunc(Main3D_DrawGLFunc);
	karinRegisterReshapeFunc(Main3D_ReshapeGLFunc);
	karinRegisterExitFunc(Main3D_FreeGLFunc);
	karinRegisterMouseFunc(Main3D_MouseEventFunc);
	karinRegisterKeyFunc(Main3D_KeyEventFunc);
	karinRegisterMotionFunc(Main3D_MouseMotionEventFunc);
	karinRegisterIdleFunc(Main3D_IdleEventFunc);
}

void Main3D_InitGLFunc(void)
{
	new_netlizard_font(&fnt, NETLIZARD_FONT_MAP_FILE, NETLIZARD_FONT_TEX_FILE);
	//new_x_font(&fnt, "fixed", 1, '~');

	if(InitNETLizard3D)
		InitNETLizard3D();
}

void Main3D_DrawGLFunc(void)
{
	if(DrawNETLizard3D)
	{
		DrawNETLizard3D();
		glFlush();
	}
}

void Main3D_ReshapeGLFunc(int w, int h)
{
	if(ReshapeNETLizard3D)
		ReshapeNETLizard3D(w, h);
}

void Main3D_FreeGLFunc(void)
{
	if(FreeNETLizard3D)
		FreeNETLizard3D();
	delete_font(&fnt);
	FREE_PTR(keymap_file)
}

unsigned Main3D_KeyEventFunc(int key, unsigned pressed, int x, int y)
{
	Harmattan_Key k = Main3D_ConvertXKey(key);
	if(k != Harmattan_Total_Key)
		key_state[k] = pressed ? 1 : 0;
	Game_Action a = Main3D_GetActionOfKey(k);
	if(a != Total_Action)
	{
		Harmattan_Key ck = k;
		if(key_ignore_case)
		{
			if(k >= Harmattan_K_A && k <= Harmattan_K_Z)
			{
				ck += CASE_A_Z;
			}
		}
		action_state[a] = pressed ? 1 : 0;
		// TODO RESET
		/*
		if(pressed)
			action_state[a] += 1;
		else
			action_state[a] -= 1;
			*/
	}
	int res = 0;
#if 0
			case Harmattan_K_r:
				if(pressed)
				{
					is_rotate ^= 1;
					return True;
				}
				break;
#endif
	if(KeyNETLizard3D)
		res = KeyNETLizard3D(k, a, pressed, x, y);

	return res;
}

unsigned Main3D_MouseEventFunc(int button, unsigned pressed, int x, int y)
{
	int res = 0;
	// check mouse single click event
	if(pressed)
	{
		mouse_click_x = x;
		mouse_click_y = y;
		struct timeval cur_time;
		gettimeofday(&cur_time, NULL);
		mouse_click_time = (long long)cur_time.tv_sec * (long long)1000 + (long long)cur_time.tv_usec / 1000;
	}
	else
	{
		if(abs(x - mouse_click_x) <= CLICK_ZERO && abs(y - mouse_click_y) <= CLICK_ZERO)
		{
			struct timeval cur_time;
			gettimeofday(&cur_time, NULL);
			long long time = (long long)cur_time.tv_sec * (long long)1000 + (long long)cur_time.tv_usec / 1000;
			if(time - mouse_click_time <= 1000 * CLICK_TIME)
				res = Main3D_MouseClickEventFunc(button, x, y);
		}
	}
	if(!pressed)
	{
		delta_x_3d = 0;
		delta_y_3d = 0;
	}

	if(MouseNETLizard3D)
		res = MouseNETLizard3D(button, pressed, x, y);
	return res;
}

unsigned Main3D_MouseMotionEventFunc(int button, unsigned pressed, int x, int y, int dx, int dy)
{
	int res = 0;
	if(pressed)
	{
		delta_x_3d = dx;
		delta_y_3d = dy;
		res = 1;
	}
	if(MotionNETLizard3D)
		res |= MotionNETLizard3D(button, pressed, x, y, dx, dy);
	return res;
}

unsigned Main3D_IdleEventFunc(void)
{
	int res = 0;
	if(IdleNETLizard3D)
		res = IdleNETLizard3D();
	return res;
}

void Main3D_ModelViewTransform(person_mode mode, GLfloat tps_y_angle/*left is less 0, right is greater than 0, equals 0 is in middle.*/ ,GLfloat tps_x_angle, GLfloat tps_factory, int auto_cast)
{
	if(mode == third_person_mode)
	{
		if(auto_cast)
		{
			vector3_t d = Algo_ComputeDirection(y_r_3d + tps_y_angle, x_r_3d + tps_x_angle);
			vector3_t dir = {
				-d.x * tps_factory,
				-d.y * tps_factory,
				-d.z * tps_factory
			};
			tp_x_t_3d = x_t_3d + dir.x;
			tp_y_t_3d = y_t_3d + dir.y;
			tp_z_t_3d = z_t_3d + dir.z;
		}
		glRotatef(tp_x_r_3d, 1.0, 0.0, 0.0);
		glRotatef(tp_y_r_3d, 0.0, 1.0, 0.0);
		glTranslatef(tp_x_t_3d, tp_y_t_3d, tp_z_t_3d);
	}
	else
	{
		tp_x_t_3d = x_t_3d;
		tp_y_t_3d = y_t_3d;
		tp_z_t_3d = z_t_3d;
		glRotatef(x_r_3d, 1.0, 0.0, 0.0);
		glRotatef(y_r_3d, 0.0, 1.0, 0.0);
		glTranslatef(x_t_3d, y_t_3d, z_t_3d);
	}
	// NEED FIX
	/*
		 tp_y_r_3d = Algo_FormatAngle(y_r_3d + tps_y_angle);
		 tp_x_r_3d = Algo_FormatAngle(x_r_3d + tps_x_angle);
		 */
	// NEED FIX

	glRotatef(y_a_3d, 0.0, 1.0, 0.0);
	glRotatef(x_a_3d, 1.0, 0.0, 0.0);
}

void Main3D_SetInitFunction(Main3DInitFunction f)
{
	InitNETLizard3D = f;
	if(InitNETLizard3D && karinIsRunning())
		InitNETLizard3D();
}

void Main3D_SetDrawFunction(Main3DDrawFunction f)
{
	DrawNETLizard3D = f;
	if(DrawNETLizard3D && karinIsRunning())
		karinPostDrawGL();
}

void Main3D_SetFreeFunction(Main3DFreeFunction f)
{
	if(FreeNETLizard3D && karinIsRunning())
		FreeNETLizard3D();
	FreeNETLizard3D = f;
}

void Main3D_SetIdleEventFunction(Main3DIdleEventFunction f)
{
	IdleNETLizard3D = f;
}

void Main3D_SetKeyEventFunction(Main3DKeyEventFunction f)
{
	KeyNETLizard3D = f;
}

void Main3D_SetMouseMotionEventFunction(Main3DMouseMotionFunction f)
{
	MotionNETLizard3D = f;
}

void Main3D_SetReshapeFunction(Main3DReshapeFunction f)
{
	ReshapeNETLizard3D = f;
	if(ReshapeNETLizard3D && karinIsRunning())
		ReshapeNETLizard3D(width, height);
}

void Main3D_SetMouseEventFunction(Main3DMouseFunction f)
{
	MouseNETLizard3D = f;
}

void Main3D_SetMouseClickEventFunction(Main3DMouseClickFunction f)
{
	MouseClickNETLizard3D = f;
}

void Main3D_Reset(void)
{
	rotation_unit_3d = 1.0;
	move_unit_3d = 1.0;
	turn_unit_3d = 1.0;
	y_a_3d = 0.0;
	x_a_3d = 0.0;
	x_t_3d = 0.0;
	y_t_3d = 0.0;
	z_t_3d = 0.0;
	x_r_3d = 0.0;
	y_r_3d = 0.0;
	tp_x_t_3d = 0.0;
	tp_y_t_3d = 0.0;
	tp_z_t_3d = 0.0;
	tp_x_r_3d = 0.0;
	tp_y_r_3d = 0.0;
	delta_x_3d = 0;
	delta_y_3d = 0;
	viewport_height = 200;
	viewport_width = 480;
	is_cross = GL_FALSE;
	is_rotate = GL_FALSE;

	Main3D_SetDrawFunction(NULL);
	Main3D_SetInitFunction(NULL);
	Main3D_SetFreeFunction(NULL);
	Main3D_SetIdleEventFunction(NULL);
	Main3D_SetKeyEventFunction(NULL);
	Main3D_SetMouseMotionEventFunction(NULL);
	Main3D_SetReshapeFunction(NULL);
	Main3D_SetMouseEventFunction(NULL);
	Main3D_SetMouseClickEventFunction(NULL);
}

Harmattan_Key Main3D_ConvertXKey(KeySym k)
{
#define XK2HarmK(n, k) case XK_##k: n = Harmattan_K_##k; break;
	Harmattan_Key key;
	switch(k)
	{
		XK2HarmK(key, Multi_key)
			XK2HarmK(key, F1)
			XK2HarmK(key, F2)
			XK2HarmK(key, F3)
			XK2HarmK(key, F4)
			XK2HarmK(key, F5)
			XK2HarmK(key, F6)
			XK2HarmK(key, F7)
			XK2HarmK(key, BackSpace)
			XK2HarmK(key, Tab)
			XK2HarmK(key, KP_Enter)
			XK2HarmK(key, F11)
			XK2HarmK(key, F12)
			XK2HarmK(key, Return)
			XK2HarmK(key, F8)
			XK2HarmK(key, F9)
			XK2HarmK(key, F10)
			XK2HarmK(key, Control_L)
			XK2HarmK(key, Control_R)
			XK2HarmK(key, Shift_L)
			XK2HarmK(key, Shift_R)
			XK2HarmK(key, sterling)
			XK2HarmK(key, EuroSign)
			XK2HarmK(key, Up)
			XK2HarmK(key, Down)
			XK2HarmK(key, Left)
			XK2HarmK(key, Right)
			XK2HarmK(key, Escape)
			XK2HarmK(key, Home)
			XK2HarmK(key, End)
			XK2HarmK(key, Page_Up)
			XK2HarmK(key, Page_Down)
			XK2HarmK(key, space)
			XK2HarmK(key, exclam)
			XK2HarmK(key, quotedbl)
			XK2HarmK(key, numbersign)
			XK2HarmK(key, dollar)
			XK2HarmK(key, percent)
			XK2HarmK(key, ampersand)
			XK2HarmK(key, apostrophe)
			XK2HarmK(key, parenleft)
			XK2HarmK(key, parenright)
			XK2HarmK(key, asterisk)
			XK2HarmK(key, plus)
			XK2HarmK(key, comma)
			XK2HarmK(key, minus)
			XK2HarmK(key, period)
			XK2HarmK(key, slash)
			XK2HarmK(key, 0)
			XK2HarmK(key, 1)
			XK2HarmK(key, 2)
			XK2HarmK(key, 3)
			XK2HarmK(key, 4)
			XK2HarmK(key, 5)
			XK2HarmK(key, 6)
			XK2HarmK(key, 7)
			XK2HarmK(key, 8)
			XK2HarmK(key, 9)
			XK2HarmK(key, colon)
			XK2HarmK(key, semicolon)
			XK2HarmK(key, less)
			XK2HarmK(key, equal)
			XK2HarmK(key, greater)
			XK2HarmK(key, question)
			XK2HarmK(key, at)
			XK2HarmK(key, A)
			XK2HarmK(key, B)
			XK2HarmK(key, C)
			XK2HarmK(key, D)
			XK2HarmK(key, E)
			XK2HarmK(key, F)
			XK2HarmK(key, G)
			XK2HarmK(key, H)
			XK2HarmK(key, I)
			XK2HarmK(key, J)
			XK2HarmK(key, K)
			XK2HarmK(key, L)
			XK2HarmK(key, M)
			XK2HarmK(key, N)
			XK2HarmK(key, O)
			XK2HarmK(key, P)
			XK2HarmK(key, Q)
			XK2HarmK(key, R)
			XK2HarmK(key, S)
			XK2HarmK(key, T)
			XK2HarmK(key, U)
			XK2HarmK(key, V)
			XK2HarmK(key, W)
			XK2HarmK(key, X)
			XK2HarmK(key, Y)
			XK2HarmK(key, Z)
			XK2HarmK(key, bracketleft)
			XK2HarmK(key, backslash)
			XK2HarmK(key, bracketright)
			XK2HarmK(key, asciicircum)
			XK2HarmK(key, underscore)
			XK2HarmK(key, grave)
			XK2HarmK(key, a)
			XK2HarmK(key, b)
			XK2HarmK(key, c)
			XK2HarmK(key, d)
			XK2HarmK(key, e)
			XK2HarmK(key, f)
			XK2HarmK(key, g)
			XK2HarmK(key, h)
			XK2HarmK(key, i)
			XK2HarmK(key, j)
			XK2HarmK(key, k)
			XK2HarmK(key, l)
			XK2HarmK(key, m)
			XK2HarmK(key, n)
			XK2HarmK(key, o)
			XK2HarmK(key, p)
			XK2HarmK(key, q)
			XK2HarmK(key, r)
			XK2HarmK(key, s)
			XK2HarmK(key, t)
			XK2HarmK(key, u)
			XK2HarmK(key, v)
			XK2HarmK(key, w)
			XK2HarmK(key, x)
			XK2HarmK(key, y)
			XK2HarmK(key, z)
			XK2HarmK(key, braceleft)
			XK2HarmK(key, bar)
			XK2HarmK(key, braceright)
			XK2HarmK(key, asciitilde)
			XK2HarmK(key, Delete)
			XK2HarmK(key, ISO_Level3_Shift)
		default:
			key = Harmattan_Other_Key;
			break;
	}
	return key;
#undef XK2HarmK
}

void Main3D_LoadKeyActionMapFromFile(const char *file)
{
	Main3D_MakeKeyMapFile(file);
#define STR2HarmK(a, i, p, k) if(strcmp(p, #k) == 0) \
	{ \
		a[Harmattan_K_##k] = i; \
	}
	int i;
	/*
	for(i = Harmattan_K_Multi_key; i < Harmattan_Total_Key; i++)
	{
		key_action[i] = -1;
	}
	*/
	if(!keymap_file)
		return;
	array *arr = nlReadFile(keymap_file);
	if(!arr)
		return;
	printf("Read key map file: %s\n", keymap_file);
	char *data = (char *)(arr->array);
	char ch;
	i = 0;
	while(i < arr->length)
	{
		while((ch = data[i]) == '\n') i++;
		if(ch == '[')
		{
			i += 1;
			int j = 0;
			while(data[i + j] != ']' && i + j < arr->length)
				j++;
			char *title = NEW_II(char, j + 1);
			memcpy(title, data + i, sizeof(char) * (j + 1));
			title[j] = '\0';
			//printf("[%s]\n", title);
			free(title);
			j++;
			i += j;
			while((ch = data[i]) != '\n') i++;
		}
		else if(ch == '#')
		{
			i += 1;
			while(isspace((ch = data[i]))) i++;
			int j = 0;
			while(data[i + j] != '\n' && i + j < arr->length)
				j++;
			if(show_comment)
			{
				char *str = NEW_II(char, j + 1);
				memcpy(str, data + i, sizeof(char) * (j + 1));
				str[j] = '\0';
				//printf("# %s\n", str);
				free(str);
			}
			j++;
			i += j;
		}
		else if(ch == '<')
		{
			i += 1;
			int j = 0;
			while(data[i + j] != '>' && i + j < arr->length)
				j++;
			char *str = NEW_II(char, j + 1);
			memcpy(str, data + i, sizeof(char) * (j + 1));
			str[j] = '\0';
			//printf("<%s>\n", str);
			free(str);
			j++;
			i += j;
			while((ch = data[i]) != '\n') i++;
		}
		else
		{
			int j = 0;
			while(data[i + j] != '\n' && i + j < arr->length)
				j++;
			char *str = NEW_II(char, j + 1);
			memcpy(str, data + i, sizeof(char) * (j + 1));
			str[j] = '\0';
			char *ptr = strtok(str, "=");
			if(ptr){
				int j;
				for(j = Forward_Action; j < Total_Action; j++)
				{
					if(strcasecmp(ptr, Action_Infos[j].flag) == 0)
					{
						ptr = strtok(NULL, "=");
						if(ptr)
						{
							char *p = strtok(ptr, ",");
							if(p)
							{
								do
								{
									STR2HarmK(key_action, j, p, Multi_key)
			else STR2HarmK(key_action, j, p, F1)
			else STR2HarmK(key_action, j, p, F2)
			else STR2HarmK(key_action, j, p, F3)
			else STR2HarmK(key_action, j, p, F4)
			else STR2HarmK(key_action, j, p, F5)
			else STR2HarmK(key_action, j, p, F6)
			else STR2HarmK(key_action, j, p, F7)
			else STR2HarmK(key_action, j, p, BackSpace)
			else STR2HarmK(key_action, j, p, Tab)
			else STR2HarmK(key_action, j, p, KP_Enter)
			else STR2HarmK(key_action, j, p, F11)
			else STR2HarmK(key_action, j, p, F12)
			else STR2HarmK(key_action, j, p, Return)
			else STR2HarmK(key_action, j, p, F8)
			else STR2HarmK(key_action, j, p, F9)
			else STR2HarmK(key_action, j, p, F10)
			else STR2HarmK(key_action, j, p, Control_L)
			else STR2HarmK(key_action, j, p, Control_R)
			else STR2HarmK(key_action, j, p, Shift_L)
			else STR2HarmK(key_action, j, p, Shift_R)
			else STR2HarmK(key_action, j, p, sterling)
			else STR2HarmK(key_action, j, p, EuroSign)
			else STR2HarmK(key_action, j, p, Up)
			else STR2HarmK(key_action, j, p, Down)
			else STR2HarmK(key_action, j, p, Left)
			else STR2HarmK(key_action, j, p, Right)
			else STR2HarmK(key_action, j, p, Escape)
			else STR2HarmK(key_action, j, p, Home)
			else STR2HarmK(key_action, j, p, End)
			else STR2HarmK(key_action, j, p, Page_Up)
			else STR2HarmK(key_action, j, p, Page_Down)
			else STR2HarmK(key_action, j, p, space)
			else STR2HarmK(key_action, j, p, exclam)
			else STR2HarmK(key_action, j, p, quotedbl)
			else STR2HarmK(key_action, j, p, numbersign)
			else STR2HarmK(key_action, j, p, dollar)
			else STR2HarmK(key_action, j, p, percent)
			else STR2HarmK(key_action, j, p, ampersand)
			else STR2HarmK(key_action, j, p, apostrophe)
			else STR2HarmK(key_action, j, p, parenleft)
			else STR2HarmK(key_action, j, p, parenright)
			else STR2HarmK(key_action, j, p, asterisk)
			else STR2HarmK(key_action, j, p, plus)
			else STR2HarmK(key_action, j, p, comma)
			else STR2HarmK(key_action, j, p, minus)
			else STR2HarmK(key_action, j, p, period)
			else STR2HarmK(key_action, j, p, slash)
			else STR2HarmK(key_action, j, p, 0)
			else STR2HarmK(key_action, j, p, 1)
			else STR2HarmK(key_action, j, p, 2)
			else STR2HarmK(key_action, j, p, 3)
			else STR2HarmK(key_action, j, p, 4)
			else STR2HarmK(key_action, j, p, 5)
			else STR2HarmK(key_action, j, p, 6)
			else STR2HarmK(key_action, j, p, 7)
			else STR2HarmK(key_action, j, p, 8)
			else STR2HarmK(key_action, j, p, 9)
			else STR2HarmK(key_action, j, p, colon)
			else STR2HarmK(key_action, j, p, semicolon)
			else STR2HarmK(key_action, j, p, less)
			else STR2HarmK(key_action, j, p, equal)
			else STR2HarmK(key_action, j, p, greater)
			else STR2HarmK(key_action, j, p, question)
			else STR2HarmK(key_action, j, p, at)
			else STR2HarmK(key_action, j, p, A)
			else STR2HarmK(key_action, j, p, B)
			else STR2HarmK(key_action, j, p, C)
			else STR2HarmK(key_action, j, p, D)
			else STR2HarmK(key_action, j, p, E)
			else STR2HarmK(key_action, j, p, F)
			else STR2HarmK(key_action, j, p, G)
			else STR2HarmK(key_action, j, p, H)
			else STR2HarmK(key_action, j, p, I)
			else STR2HarmK(key_action, j, p, J)
			else STR2HarmK(key_action, j, p, K)
			else STR2HarmK(key_action, j, p, L)
			else STR2HarmK(key_action, j, p, M)
			else STR2HarmK(key_action, j, p, N)
			else STR2HarmK(key_action, j, p, O)
			else STR2HarmK(key_action, j, p, P)
			else STR2HarmK(key_action, j, p, Q)
			else STR2HarmK(key_action, j, p, R)
			else STR2HarmK(key_action, j, p, S)
			else STR2HarmK(key_action, j, p, T)
			else STR2HarmK(key_action, j, p, U)
			else STR2HarmK(key_action, j, p, V)
			else STR2HarmK(key_action, j, p, W)
			else STR2HarmK(key_action, j, p, X)
			else STR2HarmK(key_action, j, p, Y)
			else STR2HarmK(key_action, j, p, Z)
			else STR2HarmK(key_action, j, p, bracketleft)
			else STR2HarmK(key_action, j, p, backslash)
			else STR2HarmK(key_action, j, p, bracketright)
			else STR2HarmK(key_action, j, p, asciicircum)
			else STR2HarmK(key_action, j, p, underscore)
			else STR2HarmK(key_action, j, p, grave)
			else STR2HarmK(key_action, j, p, a)
			else STR2HarmK(key_action, j, p, b)
			else STR2HarmK(key_action, j, p, c)
			else STR2HarmK(key_action, j, p, d)
			else STR2HarmK(key_action, j, p, e)
			else STR2HarmK(key_action, j, p, f)
			else STR2HarmK(key_action, j, p, g)
			else STR2HarmK(key_action, j, p, h)
			else STR2HarmK(key_action, j, p, i)
			else STR2HarmK(key_action, j, p, j)
			else STR2HarmK(key_action, j, p, k)
			else STR2HarmK(key_action, j, p, l)
			else STR2HarmK(key_action, j, p, m)
			else STR2HarmK(key_action, j, p, n)
			else STR2HarmK(key_action, j, p, o)
			else STR2HarmK(key_action, j, p, p)
			else STR2HarmK(key_action, j, p, q)
			else STR2HarmK(key_action, j, p, r)
			else STR2HarmK(key_action, j, p, s)
			else STR2HarmK(key_action, j, p, t)
			else STR2HarmK(key_action, j, p, u)
			else STR2HarmK(key_action, j, p, v)
			else STR2HarmK(key_action, j, p, w)
			else STR2HarmK(key_action, j, p, x)
			else STR2HarmK(key_action, j, p, y)
			else STR2HarmK(key_action, j, p, z)
			else STR2HarmK(key_action, j, p, braceleft)
			else STR2HarmK(key_action, j, p, bar)
			else STR2HarmK(key_action, j, p, braceright)
			else STR2HarmK(key_action, j, p, asciitilde)
			else STR2HarmK(key_action, j, p, Delete)
			else STR2HarmK(key_action, j, p, ISO_Level3_Shift)
								}while((p = strtok(NULL, ",")) != NULL);
							}
						}
						break;
					}
				}
			}
			free(str);
			j++;
			i += j;
		}
	}
	delete_array(arr);
	free(arr);
#undef STR2HarmK
}

void Main3D_LoadKeyActionMapFromDefault(void)
{
	int i;
	for(i = Harmattan_K_Multi_key; i < Harmattan_Total_Key; i++)
	{
		key_action[i] = -1;
	}
	for(i = Forward_Action; i < Total_Action; i++)
	{
		key_action[Action_Infos[i].def_key] = i;
	}
}

Game_Action Main3D_GetActionOfKey(Harmattan_Key key)
{
	if(key != Harmattan_Total_Key)
	{
		Harmattan_Key k = key;
		if(key_ignore_case)
		{
			if(key >= Harmattan_K_A && key <= Harmattan_K_Z)
			{
				k += CASE_A_Z;
			}
		}
		return key_action[k] != -1 ? key_action[k] : Total_Action;
	}
	else
		return Total_Action;
}

unsigned Main3D_MouseClickEventFunc(int button, int x, int y)
{
	int res = 0;
	if(MouseClickNETLizard3D)
	{
		res = MouseClickNETLizard3D(button, x, y);
	}
	return res;
}

int Main3D_BaseTransform(void)
{
	int res = 0;
	orientation_type o = center_orientation_type;
	position_type p = center_position_type;
	if(action_state[TurnUp_Action])
		o |= up_orientation_type;
	if(action_state[TurnDown_Action])
		o |= down_orientation_type;
	if(action_state[TurnLeft_Action])
		o |= left_orientation_type;
	if(action_state[TurnRight_Action])
		o |= right_orientation_type;

	if(action_state[Forward_Action])
		p |= forward_position_type;
	if(action_state[Backward_Action])
		p |= backward_position_type;
	if(action_state[MoveLeft_Action])
		p |= left_position_type;
	if(action_state[MoveRight_Action])
		p |= right_position_type;
	if(action_state[MoveUp_Action])
		p |= up_position_type;
	if(action_state[MoveDown_Action])
		p |= down_position_type;

	float oyr = y_r_3d;
	float oxr = x_r_3d;
	float ryr = 0.0;
	float rxr = 0.0;

	gl_vector3_t ov = {x_t_3d, y_t_3d, z_t_3d};
	gl_vector3_t rv = {0.0, 0.0, 0.0};
	Algo_GLTransformPositionAndAngle(p, &ov, move_unit_3d, &rv, o, oxr, oyr, turn_unit_3d, &rxr, &ryr, is_cross);

	if(o != center_orientation_type)
	{
		y_r_3d = ryr;
		x_r_3d = rxr;
		res = 1;
	}
	if(p != center_position_type)
	{
		x_t_3d = rv.x;
		y_t_3d = rv.y;
		z_t_3d = rv.z;
		res = 1;
	}

	int i;
	for(i = Forward_Action; i <= TurnRight_Action; i++)
	{
		if(action_state[i])
		{
			res = 1;
			break;
		}
	}

	if(is_rotate)
	{
		if(delta_x_3d != 0 || delta_y_3d != 0)
		{
			x_a_3d += delta_y_3d * rotation_unit_3d;
			y_a_3d += delta_x_3d * rotation_unit_3d;
			res = 1;
		}
	}
	return res;
}

void Main3D_MakeKeyMapFile(const char *file)
{
	if(file == NULL)
	{
		if(keymap_file)
			free(keymap_file);
		char *path = System_GetPathFromHome(_KARIN_HOME);
		keymap_file = NEW_II(char, strlen(path) + strlen(DEFAULT_KEYMAP_FILE) + 2);
		sprintf(keymap_file, "%s/%s", path, DEFAULT_KEYMAP_FILE);
		free(path);
	}
	else
	{
		if(keymap_file)
		{
			if(strcmp(keymap_file, file) != 0)
			{
				free(keymap_file);
				keymap_file = strdup(file);
			}
		}
		else
			keymap_file = strdup(file);
	}
}

void Main3D_SsveKeyMap(const char *file)
{
	Main3D_MakeKeyMapFile(file);
	FILE *out = fopen(keymap_file, "wb");
	if(!out)
		return;
	char head[] = "[karin.key_map]";
	fwrite(head, sizeof(char), strlen(head), out);

	fwrite("\n", sizeof(char), 1, out);
	fwrite("\n", sizeof(char), 1, out);
	int i;
	for(i = Harmattan_K_Multi_key; i < Harmattan_Total_Key; i++)
	{
		if(i == Harmattan_Board_Key || i == Harmattan_Mouse_Key || i == Harmattan_Other_Key)
			continue;
		fwrite("# ", sizeof(char), 2, out);
		fwrite(Key_Infos[i].name, sizeof(char), strlen(Key_Infos[i].name), out);
		fwrite(": ", sizeof(char), 2, out);
		fwrite(Key_Infos[i].symbol, sizeof(char), strlen(Key_Infos[i].symbol), out);
		fwrite("\n", sizeof(char), 1, out);
	}
	fwrite("\n", sizeof(char), 1, out);

	for(i = Forward_Action; i < Total_Action; i++)
	{
		fwrite(Action_Infos[i].flag, sizeof(char), strlen(Action_Infos[i].flag), out);
		char ch = '=';
		fwrite(&ch, sizeof(char), 1, out);
		int j;
		for(j = Harmattan_K_Multi_key; j < Harmattan_Total_Key; j++)
		{
			if(key_action[j] == -1)
				continue;
			if(key_action[j] == i)
			{
				if(ch == ',')
					fwrite(&ch, sizeof(char), 1, out);
				else
					ch = ',';
				fwrite(Key_Infos[j].name, sizeof(char), strlen(Key_Infos[j].name), out);
			}
		}
		ch = '\n';
		fwrite(&ch, sizeof(char), 1, out);
	}
	fflush(out);
	fclose(out);
}

void Main3D_PrintKeyMap(void)
{
	printf(Console_PrintLine("KEY MAP", '*'));
	int i;
	for(i = Forward_Action; i < Total_Action; i++)
	{
		printf("%s: ", Action_Infos[i].desc);
		int has = 0;
		int j;
		for(j = Harmattan_K_Multi_key; j < Harmattan_Total_Key; j++)
		{
			if(key_action[j] == -1)
				continue;
			if(key_action[j] == i)
			{
				if(has)
					printf(", ");
				else
					has = 1;
				printf("%s", Key_Infos[j].symbol);
			}
		}
		printf("\n");
	}
	printf(Console_PrintLine(NULL, '*'));
}

void Main3D_ResetKeyAndActionState(void)
{
	unsigned int i;
	for(i = Harmattan_K_Multi_key; i < Harmattan_Total_Key; i++)
	{
		key_action[i] = -1;
		key_state[i] = 0;
	}
	for(i = Forward_Action; i < Total_Action; i++)
		action_state[i] = 0;
}
