#ifndef KARIN_GLUT_H
#define KARIN_GLUT_H

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
#include "../opengl/opengl.h"
#include "../opengl/openglu.h"
#ifdef _HARMATTAN_OPENGL
#ifdef _NOT_USE_MESAGLUT
#include <GL/freeglut.h>
#else
#include <GL/glut.h> // mesa glut header file
#endif
#endif

/* GLX or EGL*/
#ifdef _HARMATTAN_OPENGL
#include <GL/glx.h>
#else
#include <EGL/egl.h>
#endif

#define HARMATTAN_FULL_HEIGHT 480
#define HARMATTAN_FULL_WIDTH 854
#define HARMATTAN_HEIGHT 376
#define HARMATTAN_WIDTH 800
/* Macros */
// utility macros
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
typedef Bool (*keyHandlerFunc) (KeySym key, Bool pressed, int x, int y);
typedef Bool (*mouseHandlerFunc) (int button, Bool pressed, int x, int y);
typedef Bool (*motionHandlerFunc) (int button, int pressed, int x, int y, int dx, int dy);
// window resize event function
typedef void (*resizeHandlerFunc) (void);
// atexit function
typedef void (*exitXFunc) (void);
// idle function
// return True if need re-draw GL
typedef Bool (*idleFunc) (void);

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

/* extern function */
// GLX init function
Bool karinSetGLctxInitAttributeArray(const int args[]);
Bool karinSetGLctxInitAttribute(int param, ...);
Bool karinAddGLctxInitAttribute(int param, ...);
Bool karinInitGLctxObject(void);
Bool karinCreateGLRenderWindow(const char *title);
#ifdef _HARMATTAN_OPENGL
Bool karinInitGLctxObjectAndGLUT(int *argc, char *argv[]);
#endif
void karinSetWindowPosiotionAndSize(int lx, int ly, int w, int h);
void karinSetAutoReshapeWhenResize(GLboolean b);

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

// application function
void karinPostExit(void);
void karinMainLoop(void);
void karinFullscreen(Bool fs);
void karinSetMaxFPS(int i);
void karinSetSingle(GLboolean s);
void karinShutdown(void);
GLboolean karinIsRunning(void);
GLboolean karinIsSingle(void);
Bool karinHasInitGLctx(void);

// GL function
void karinSwapBuffers(void);
void karinSetAutoSwapBuffers(GLboolean b);
GLboolean karinQueryExtension(const char *extName);
void karinPostDrawGL(void);
void (*karinGetProcAddress(const GLubyte *procname))(void);
Bool karinUseXFont(const char *name, int start, int size, GLuint list_start, unsigned int *w, unsigned int *h);

// utility function
float karinCastFPS(void);
const GLubyte * karinGetGLErrorString(void);

#endif
