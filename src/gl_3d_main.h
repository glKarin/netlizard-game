#ifndef KARIN_GL_3D_MAIN_H
#define KARIN_GL_3D_MAIN_H

#include "game_util.h"
#include "font.h"
#include "page_stack.h"

#include <X11/Xlib.h>

extern font fnt;
extern GLboolean init_glk;
// 记录每个按键对应的动作 -1 / Game_Action
extern int key_action[Harmattan_Total_Key];
// 记录每个按键的状态 0, 1
extern int key_state[Harmattan_Total_Key];
// 记录每个动作的状态 0, 1
extern int action_state[Total_Action];

extern GLfloat rotation_unit_3d;
extern GLfloat move_unit_3d;
extern GLfloat turn_unit_3d;

extern GLfloat y_a_3d;
extern GLfloat x_a_3d;

extern GLfloat x_t_3d;
extern GLfloat y_t_3d;
extern GLfloat z_t_3d;

extern GLfloat x_r_3d;
extern GLfloat y_r_3d;

extern GLint delta_x_3d;
extern GLint delta_y_3d;

extern GLfloat view_y_angle;
extern GLfloat view_x_angle;
extern GLboolean view_free_mode;

extern GLsizei viewport_width;
extern GLsizei viewport_height;

extern GLfloat tp_x_t_3d;
extern GLfloat tp_y_t_3d;
extern GLfloat tp_z_t_3d;

extern GLfloat tp_x_r_3d;
extern GLfloat tp_y_r_3d;

extern GLboolean is_cross;
extern GLboolean key_ignore_case;

void Main3D_InitGLK(int x, int y, int w, int h, const char *title, int fps, int fs);
void Main3D_ModelViewTransform(person_mode mode, GLfloat tps_y/*left is less 0, right is greater than 0, equals 0 is in middle.*/, GLfloat tps_x, GLfloat tps_factory, int auto_cast);

#if 0
void Main3D_SetDrawFunction(Main3DDrawFunction f);
void Main3D_SetInitFunction(Main3DInitFunction f);
void Main3D_SetFreeFunction(Main3DFreeFunction f);
void Main3D_SetIdleEventFunction(Main3DIdleEventFunction f);
void Main3D_SetKeyEventFunction(Main3DKeyEventFunction f);
void Main3D_SetMouseMotionEventFunction(Main3DMouseMotionFunction f);
void Main3D_SetReshapeFunction(Main3DReshapeFunction f);
void Main3D_SetMouseEventFunction(Main3DMouseFunction f);
void Main3D_SetMouseClickEventFunction(Main3DMouseClickFunction f);
#endif

void Main3D_RegisterGLKFunction(void);
void Main3D_Reset(void);
void Main3D_MainLoop(void);
void Main3D_Shutdown(void);
void Main3D_Stop(void);
void Main3D_SsveKeyMap(const char *file);

Game_Action Main3D_GetActionOfKey(Harmattan_Key key);
int Main3D_BaseTransform(void);
void Main3D_ResetKeyAndActionState(void);

// page stack
void Main3D_PushRenderPage(const char *name, const glk_function *func);	
void Main3D_InitRenderPage(const char *name, const glk_function *func);	
void Main3D_PopRenderPage(void);
void Main3D_FreePageStack(void);
void Main3D_SetExistsRenderPage(const char *name);
void Main3D_SetCurRenderPage(const char *name, const glk_function *func);

#endif
