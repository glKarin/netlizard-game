#ifndef KARIN_PAGE_STACK_H
#define KARIN_PAGE_STACK_H

#define REGISTER_RENDER_FUNCTION(m) \
	Main3D_RegisterRenderFunction( \
			m##_InitFunc, \
			m##_DrawFunc, \
			m##_FreeFunc, \
			m##_IdleFunc, \
			m##_KeyFunc, \
			m##_MotionFunc, \
			m##_ReshapeFunc, \
			m##_MouseFunc, \
			m##_ClickFunc, \
			m##_StoreFunc, \
			m##_RestoreFunc \
			)

struct _glk_function;

typedef int (*Main3DMouseMotionFunction)(int btn, int p, int x, int t, int dx, int dy);
typedef void (*Main3DInitFunction)(void);
typedef void (*Main3DReshapeFunction)(int w, int h);
typedef void (*Main3DDrawFunction)(void);
typedef void (*Main3DFreeFunction)(void);
typedef int (*Main3DIdleEventFunction)(void);
typedef int (*Main3DKeyEventFunction)(int k, int act, int p, int x, int y);
typedef int (*Main3DMouseFunction)(int button, int pressed, int x, int y);
typedef int (*Main3DMouseClickFunction)(int button, int x, int y);
typedef void (*Main3DStoreFunction_f)(void);
typedef void (*Main3DRestoreFunction_f)(void);

typedef void (*Main3DPageForEachFunction_f)(const char *name, const struct _glk_function *func);
typedef void (*Main3DRegisterRenderFunction_f)(void);

typedef struct _glk_function
{
	Main3DInitFunction init_func;
	Main3DDrawFunction draw_func;
	Main3DFreeFunction free_func;
	Main3DIdleEventFunction idle_func;
	Main3DKeyEventFunction key_func;
	Main3DMouseMotionFunction motion_func;
	Main3DReshapeFunction reshape_func;
	Main3DMouseFunction mouse_func;
	Main3DMouseClickFunction click_func;

	Main3DStoreFunction_f store_func;
	Main3DRestoreFunction_f restore_func;
} glk_function;

typedef struct _page_3d_s
{
	char *name;
	glk_function func;
} page_3d_s;

const glk_function * Main3D_GetTopFunction(char **r);
const glk_function * Main3D_GetFunction(const char *name);
void Main3D_InitPageStack(void);
void Main3D_ClearPageStack(void);
int Main3D_PushPage(const char *name, const glk_function *func);
int Main3D_PopPage(void);
int Main3D_SetPage(const char *name, const glk_function *func);
int Main3D_ReplacePage(int depth, const char *name, const glk_function *func);
int Main3D_InsertPage(int depth, const char *name, const glk_function *func);
int Main3D_RemovePage(const char *name);
int Main3D_GetStackDepth(void);
int Main3D_GetStackLength(void);
void Main3D_ForeachPage(Main3DPageForEachFunction_f f);
const glk_function * Main3D_GetCurFunction(char **r);

glk_function Main3D_RegisterRenderFunction(
		Main3DInitFunction init_func,
		Main3DDrawFunction draw_func,
		Main3DFreeFunction free_func,
		Main3DIdleEventFunction idle_func,
		Main3DKeyEventFunction key_func,
		Main3DMouseMotionFunction motion_func,
		Main3DReshapeFunction reshape_func,
		Main3DMouseFunction mouse_func,
		Main3DMouseClickFunction click_func,
		Main3DStoreFunction_f store_func,
		Main3DRestoreFunction_f restore_func
		);

#endif
