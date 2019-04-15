#ifndef _KARIN_GLUT_H
#define _KARIN_GLUT_H

/* ASCI-C std */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

/* GNU Unix std */
#include <sys/time.h>

/* X11 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

/* OpenGL & GLX & GLU */
#include "GL/gl.h"
#include "GL/glu.h"
#ifdef _NOT_USE_MESAGLUT
#include <GL/freeglut.h>
#else
#include <GL/glut.h> // mesa glut header file
#endif

/* GLX or EGL*/
#include <GL/glx.h>

/* CONSTANT */
#define HARMATTAN_FULL_HEIGHT 480
#define HARMATTAN_FULL_WIDTH 854
#define HARMATTAN_HEIGHT 376
#define HARMATTAN_WIDTH 800

/* Type */
#define _true 1
#define _false 0
typedef unsigned char _bool_t;

/* Macros */
// utility macros
#define countof(arr) (sizeof(arr) / sizeof(arr[0]))

#define KARIN_BUFFER_OFFSET(x, y) ((GLubyte *)NULL + sizeof(y) * (x))
#define KARIN_ENDL printf("\n");
#define KARIN_CASEANDEQUAL(value, index) \
	case value:\
		i = index;\
		break;

// X11
#define KEY_MASK	(KeyPressMask | KeyReleaseMask)
#define MOUSE_MASK	(ButtonPressMask | ButtonReleaseMask | PointerMotionMask | ButtonMotionMask)
#define X_MASK		(KEY_MASK | MOUSE_MASK | VisibilityChangeMask | StructureNotifyMask)
#define _NET_WM_STATE_REMOVE        0	/* remove/unset property */
#define _NET_WM_STATE_ADD           1	/* add/set property */
#define _NET_WM_STATE_TOGGLE        2	/* toggle property  */

/* function pointer typedef*/
// init function
typedef void (*initGLFunc) (void);
// draw GL function
typedef void (*drawGLFunc) (void);
// reshape function
typedef void (*reshapeGLFunc) (int w, int h);
// mouse and key event function
// return True if event has been handled
// key: key sym
// x, y: mouse x and y
// pressed: mouse or key is pressed
// dx, dy: mouse motion delta position
typedef unsigned (*keyHandlerFunc) (int key, unsigned pressed, int x, int y);
typedef unsigned (*mouseHandlerFunc) (int button, unsigned pressed, int x, int y);
typedef unsigned (*motionHandlerFunc) (int button, unsigned pressed, int x, int y, int dx, int dy);
// window resize event function
typedef void (*resizeHandlerFunc) (void);
// atexit function
typedef void (*exitXFunc) (void);
// idle function
// return True if need re-draw GL
typedef unsigned (*idleFunc) (float time_delta);

/* extern variant */
extern Display *dpy;
extern Window win;

// not see
/*
#ifdef _HARMATTAN_OPENGLES
extern EGLDisplay eglDisplay;//EGL display
extern EGLContext eglContext;//EGL context
extern EGLSurface eglSurface;//EGL surface
#else
extern GLXWindow glw;
extern GLXContext glc;
#endif
*/

extern int width;
extern int height;

extern int x;
extern int y;

extern int fps;
extern float delta_time;
extern unsigned long long time_usec;

/* extern function */
// GLX init function
unsigned karinSetGLctxInitAttributeArray(const int args[], unsigned int size);
unsigned karinSetGLctxInitAttribute(int param, ...);
unsigned karinAddGLctxInitAttribute(int param, ...);
unsigned karinInitGLctxObject(void);
unsigned karinCreateGLRenderWindow(const char *title);
unsigned karinInitGLctxObjectAndGLUT(int *argc, char *argv[]);
void karinSetWindowPosiotionAndSize(int lx, int ly, int w, int h);

// register function
void karinRegisterDrawFunc(drawGLFunc f);
void karinRegisterReshapeFunc(reshapeGLFunc f);
void karinRegisterInitFunc(initGLFunc f);
void karinRegisterKeyFunc(keyHandlerFunc f);
void karinRegisterMouseFunc(mouseHandlerFunc f);
void karinRegisterIdleFunc(idleFunc f);
void karinRegisterExitFunc(exitXFunc f);
void karinRegisterMotionFunc(motionHandlerFunc f);
void karinRegisterResizeFunc(resizeHandlerFunc f);

// state function
unsigned karinIsRunning(void);
unsigned karinIsSingle(void);
unsigned karinHasInitGLctx(void);
void karinFullscreen(unsigned fs);

// GL function
unsigned karinQueryExtension(const char *extName);
void (*karinGetProcAddress(const char *procname))(void);
unsigned karinUseXFont(const char *name, int start, int size, unsigned list_start, unsigned int *w, unsigned int *h);

// control function
void karinSetAutoReshapeWhenResize(unsigned b);
void karinSetAutoSwapBuffers(unsigned b);
void karinPostDrawGL(void);
void karinSwapBuffers(void);
void karinPostExit(void);
void karinSetSingle(unsigned s);
void karinSetMaxFPS(int i);
void karinMainLoop(void);
void karinShutdown(void);
void karinSetMustCallIdleFuncInLoop(unsigned b);

// utility function
float karinCastFPS(void);
const char * karinGetGLErrorString(void);

#endif

