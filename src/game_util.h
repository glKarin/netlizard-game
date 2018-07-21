#ifndef KARIN_GAME_UTIL_H
#define KARIN_GAME_UTIL_H

#include "gl_util.h"
#include "nl_std.h"

// 自定义按键
typedef enum _Harmattan_Key
{
	Harmattan_K_Multi_key, // 0
	Harmattan_K_F1, Harmattan_K_F2, Harmattan_K_F3, Harmattan_K_F4, Harmattan_K_F5, Harmattan_K_F6, Harmattan_K_F7, // 1 - 7
	Harmattan_K_BackSpace, Harmattan_K_Tab, Harmattan_K_KP_Enter, // 9 - 10
	Harmattan_K_F11, Harmattan_K_F12, Harmattan_K_Return, // 11 - 13
	Harmattan_K_F8, Harmattan_K_F9, Harmattan_K_F10, // 14 - 16
	Harmattan_K_Control_L, Harmattan_K_Control_R, Harmattan_K_Shift_L, Harmattan_K_Shift_R, // 17 - 20
	Harmattan_K_sterling, Harmattan_K_EuroSign, // // 21 - 22 £ €
	Harmattan_K_Up, Harmattan_K_Down, Harmattan_K_Left, Harmattan_K_Right, // 23 - 26
	Harmattan_K_Escape, // 27
	Harmattan_K_Home, Harmattan_K_End, Harmattan_K_Page_Up, Harmattan_K_Page_Down, // 28 - 31
	Harmattan_K_space, // 32
	Harmattan_K_exclam, Harmattan_K_quotedbl, Harmattan_K_numbersign, Harmattan_K_dollar, Harmattan_K_percent, Harmattan_K_ampersand, Harmattan_K_apostrophe, Harmattan_K_parenleft, Harmattan_K_parenright, Harmattan_K_asterisk, Harmattan_K_plus, Harmattan_K_comma, Harmattan_K_minus, Harmattan_K_period, Harmattan_K_slash, // 33 - 47 ! " # $ % & ' ( ) * + , - . /
	Harmattan_K_0, Harmattan_K_1, Harmattan_K_2, Harmattan_K_3, Harmattan_K_4, Harmattan_K_5, Harmattan_K_6, Harmattan_K_7, Harmattan_K_8, Harmattan_K_9, // 48 - 57 0 - 9
	Harmattan_K_colon, Harmattan_K_semicolon, Harmattan_K_less, Harmattan_K_equal, Harmattan_K_greater, Harmattan_K_question, Harmattan_K_at, // 58 - 64 : ; < = > ? @
	Harmattan_K_A, Harmattan_K_B, Harmattan_K_C, Harmattan_K_D, Harmattan_K_E, Harmattan_K_F, Harmattan_K_G,
	Harmattan_K_H, Harmattan_K_I, Harmattan_K_J, Harmattan_K_K, Harmattan_K_L, Harmattan_K_M, Harmattan_K_N,
	Harmattan_K_O, Harmattan_K_P, Harmattan_K_Q, Harmattan_K_R, Harmattan_K_S, Harmattan_K_T,
	Harmattan_K_U, Harmattan_K_V, Harmattan_K_W, Harmattan_K_X, Harmattan_K_Y, Harmattan_K_Z, // 65 - 90 A - Z
	Harmattan_K_bracketleft, Harmattan_K_backslash, Harmattan_K_bracketright, Harmattan_K_asciicircum, Harmattan_K_underscore, Harmattan_K_grave, // 91 - 96 [ \ ] ^ _ `
	Harmattan_K_a, Harmattan_K_b, Harmattan_K_c, Harmattan_K_d, Harmattan_K_e, Harmattan_K_f, Harmattan_K_g,
	Harmattan_K_h, Harmattan_K_i, Harmattan_K_j, Harmattan_K_k, Harmattan_K_l, Harmattan_K_m, Harmattan_K_n,
	Harmattan_K_o, Harmattan_K_p, Harmattan_K_q, Harmattan_K_r, Harmattan_K_s, Harmattan_K_t,
	Harmattan_K_u, Harmattan_K_v, Harmattan_K_w, Harmattan_K_x, Harmattan_K_y, Harmattan_K_z, // 97 - 122 a - z
	Harmattan_K_braceleft, Harmattan_K_bar, Harmattan_K_braceright, Harmattan_K_asciitilde, // 123 - 126 { | } ~
	Harmattan_K_Delete, // 127
	Harmattan_K_ISO_Level3_Shift, // 128
	Harmattan_Board_Key, // 129
	Harmattan_M_LeftButton, Harmattan_M_RightButton, Harmattan_M_MiddleButton, // 3
	Harmattan_Mouse_Key,
	Harmattan_Other_Key,
	Harmattan_Total_Key // 135
} Harmattan_Key;

// 按键预置动作
typedef enum _Game_Action
{
	Forward_Action = 0,
	Backward_Action,
	MoveLeft_Action,
	MoveRight_Action,
	MoveUp_Action,
	MoveDown_Action,
	TurnUp_Action,
	TurnDown_Action,
	TurnLeft_Action,
	TurnRight_Action,
	Jump_Action,
	Crouch_Action,
	Attack_Action,
	ZoomIn_Action,
	ZoomOut_Action,
	PersonMode_Action,
	ConsoleMode_Action,
	OpenLight_Action,
	PrevWeapon_Action,
	NextWeapon_Action,
	OperateGo_Action,
	OperateBack_Action,
	OperateStand_Action,
	OpenScore_Action,
	FreeViewTurnLeft_Action,
	FreeViewTurnRight_Action,
	FreeViewTurnUp_Action,
	FreeViewTurnDown_Action,
	FreeViewMode_Action,
	OpenRadar_Action,
	Reload_Action,
	ViewCenter_Action,
	Quit_Action,
	Total_Action
} Game_Action;

// 视角模式
typedef enum _person_mode
{
	first_person_mode = 0,
	third_person_mode
} person_mode;

typedef enum _view_free_type
{
	view_auto_free_type = 1,
	view_force_free_type = 2,
	view_game_free_type = 4 
} view_free_type;

// 方位
typedef enum _position_type
{
	center_position_type = 0,
	forward_position_type = 1,
	backward_position_type = 1 << 1,
	left_position_type = 1 << 2,
	right_position_type = 1 << 3,
	up_position_type = 1 << 4,
	down_position_type = 1 << 5
} position_type;

// 旋转
typedef enum _orientation_type
{
	center_orientation_type = 0,
	up_orientation_type = 1,
	down_orientation_type = 1 << 1,
	left_orientation_type = 1 << 2,
	right_orientation_type = 1 << 3,
} orientation_type;

// 锚定
typedef enum _anchor_type
{
	unavailable_anchor_type = 0,
	left_anchor_type = 1,
	right_anchor_type = 1 << 1,
	bottom_anchor_type = 1 << 2,
	top_anchor_type = 1 << 3,
	horizontal_center_anchor_type = 1 << 4,
	vertical_center_anchor_type = 1 << 5,
	left_top_anchor_type = left_anchor_type | top_anchor_type,
	left_bottom_anchor_type = left_anchor_type | bottom_anchor_type,
	right_top_anchor_type = right_anchor_type | top_anchor_type,
	right_bottom_anchor_type = right_anchor_type | bottom_anchor_type,
	center_anchor_type = horizontal_center_anchor_type | vertical_center_anchor_type,
} anchor_type;

typedef struct _action_info
{
	Game_Action action;
	Harmattan_Key def_key;
	char *flag;
	char *desc;
} action_info;

typedef struct _key_info
{
	Harmattan_Key key;
	char *name;
	char *symbol;
} key_info;

extern action_info Action_Infos[Total_Action];
extern key_info Key_Infos[Harmattan_Total_Key];

// 2D纹理场景
typedef struct _scene_2d
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat width;
	GLfloat height;
	GLfloat scale;
	anchor_type align;
	GLuint buffers[total_buffer_type];
	GLfloat color[4];
	texture *tex;
} scene_2d;

// 3D
typedef struct _scene_3d
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat width;
	GLfloat height;
	anchor_type align;
	GLuint buffers[total_buffer_type];
	GLfloat color[4];
	texture *tex;
	struct{
		GLfloat xt;
		GLfloat yt;
		GLfloat zt;
	} translate;
	struct{
		GLfloat xs;
		GLfloat ys;
		GLfloat zs;
	} scale;
	struct{
		GLfloat xr;
		GLfloat yr;
		GLfloat zr;
	} rotate;
	GLdouble foxy;
	GLdouble frustum_width;
	GLdouble frustum_height;
	GLdouble near;
	GLdouble far;
	void (*draw_func)(void);
} scene_3d;

extern const char *Harmattan_Key_Name[Harmattan_Total_Key];
extern const char *Harmattan_Key_Symbol[Harmattan_Total_Key];

scene_2d * new_scene_2d(scene_2d *scene, GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat scale, anchor_type a, const GLfloat color[], const char *file);
void UI_RenderScene2D(const scene_2d *scene);
void delete_scene_2d(scene_2d *s);

scene_3d * new_scene_3d(scene_3d *scene, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, anchor_type a, const GLfloat color[], const char *file, GLdouble foxy, GLdouble fw, GLdouble fh, GLdouble near, GLdouble far, void (*df)(void));
void UI_RenderScene3D(const scene_3d *scene);
void delete_scene_3d(scene_3d *s);

// 计算NETLizard 3D场景中位置角度变换结果
void Algo_TransformPositionAndAngle(position_type p, const nl_vector3_t *ov, float tunit, nl_vector3_t *rv, orientation_type o, float oxr, float oyr, float runit, float *rxr, float *ryr, int corss);
// 计算OpenGL视觉坐标位置角度变换结果
void Algo_GLTransformPositionAndAngle(position_type p, const gl_vector3_t *ov, float tunit, gl_vector3_t *rv, orientation_type o, float oxr, float oyr, float runit, float *rxr, float *ryr, int cross);
// NETLizard 3D 场景中按角度计算方向
vector3_t Algo_GLComputeDirection(float y, float x);
// OpenGL 视觉坐标系按角度计算方向
vector3_t Algo_ComputeDirection(float yr, float xr);
void Algo_GetNormalAngle2D(const vector2_t *normal, float *yr);
// 获取当前事件 微秒
unsigned long long Game_GetGameTimeUS(void);
// 毫秒
unsigned long long Game_GetGameTime(void);
void UI_ResizeScene2D(scene_2d *s, GLfloat w, GLfloat h);
void Algo_GetNormalAngle(const nl_vector3_t *normal, float *yr, float *xr);
const char * Console_PrintLine(const char *title, char ch);
void UI_ResizeScene3D(scene_3d *s, GLfloat w, GLfloat h, GLfloat fw, GLfloat fh);

#endif
