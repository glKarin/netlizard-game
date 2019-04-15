#include "glk.h"

#include <unistd.h>
#include <sys/time.h>

/* extern variant */
Display *dpy = NULL;
Window win = 0;

int width = HARMATTAN_FULL_WIDTH;
int height = HARMATTAN_HEIGHT;

int x = 0;
int y = 0;

int fps = 0;

static int max_fps = 0;
static double frame_time_us = 1000000.0;

/* static variant */
static int *attr = NULL;
static unsigned int attr_count = 0;

/* register function pointer */
static initGLFunc initGL = NULL;
static drawGLFunc drawGL = NULL;
static reshapeGLFunc reshapeGL = NULL;

static keyHandlerFunc keyHandler = NULL;
static mouseHandlerFunc mouseHandler = NULL;
static resizeHandlerFunc resizeHandler = NULL;
static motionHandlerFunc motionHandler = NULL;

static idleFunc idleHandler = NULL;
static exitXFunc exitX = NULL;

/* static attribute */
// default: auto reshape is GL_TRUE auto swap buffer is GL_TRUE
// if running is GL_TRUE application is in loop
// glCtxHasInit is True when GLX has initial
static GLboolean autoReshape = GL_TRUE;
static GLboolean autoSwapBuffers = GL_TRUE;
static Bool glCtxHasInit = False;
static GLboolean running = GL_FALSE;
static GLboolean single = GL_TRUE;

/* static function */
// default handler
static void karinGLInit(void);
static void karinGLDraw(void);
static void karinGLReshape(int w, int h);

static void karinXResizeHandler(void);
static int karinXErrorHandler(Display *d, XErrorEvent *eev);

// application function
static Bool karinCreateGLContext(const char* title);
static Bool karinXEventLoop(void);
static void karinPrintGLInfo(void);
static const char * karinX11EventString(int e);

//static void GLimp_DisableComposition(void);

#ifdef _XI2_MULTI_TOUCH
#include "private_glk_xi2.h"
#endif

#ifdef _HARMATTAN_OPENGL
#include "private_glk_glx.h"
#define CONFIG_NONE None
#else
#include "private_glk_egl.h"
#define CONFIG_NONE EGL_NONE
#endif

Bool karinSetGLctxInitAttributeArray(const int args[])
{
	size_t len = sizeof(args) / sizeof(int);
	if(len == 0)
	{
		fprintf(stderr, "No configure attritube.\n");
		return False;
	}
	free(attr);
	attr = NULL;
	attr_count = 0;
	void *ptr = calloc(len, sizeof(int));
	if(!ptr)
	{
		fprintf(stderr, "Alloc fail.\n");
		return False;
	}
	attr = (int *)ptr;
	memcpy(attr, args, sizeof(args));
	attr_count = len - 1;
	return True;
}

Bool karinSetGLctxInitAttribute(int param, ...)
{
	if(param < 2)
	{
		fprintf(stderr, "Need 1 pair of configure attritube.\n");
		return False;
	}
	free(attr);
	attr = NULL;
	attr_count = 0;
	void *ptr = calloc(param + 1, sizeof(int));
	if(!ptr)
	{
		fprintf(stderr, "Alloc fail.\n");
		return False;
	}
	attr = (int *)ptr;
	va_list args;
	va_start(args, param);
		int i;
		for(i = 0; i < param; i++)
			attr[i] = va_arg(args, int);
	va_end(args);
	attr[i] = CONFIG_NONE;
	attr_count = param;
	return True;
}

Bool karinAddGLctxInitAttribute(int param, ...)
{
	if(param < 2)
	{
		fprintf(stderr, "Need 1 pair of configure attritube.\n");
		return False;
	}
	void *ptr = NULL;
	if(attr_count == 0)
	{
		int arg_arr[param + 1];
		va_list args;
		va_start(args, param);
		int i;
		for(i = 0; i < param; i++)
			arg_arr[i] = va_arg(args, int);
		va_end(args);
		arg_arr[i] = CONFIG_NONE;
		return karinSetGLctxInitAttributeArray(arg_arr);
	}
	int old_conf[attr_count];
	memcpy(old_conf, attr, sizeof(old_conf));
	ptr = realloc((void *)attr, sizeof(int) * (attr_count + param + 1));
	if(!ptr)
	{
		fprintf(stderr, "ReAlloc fail.\n");
		return False;
	}
	attr = (int *)ptr;
	memcpy(attr, old_conf, sizeof(old_conf));
	va_list args;
	va_start(args, param);
		int i;
		for(i = 0; i < param; i++)
			attr[attr_count + i] = va_arg(args, int);
	va_end(args);
	attr[attr_count + i] = CONFIG_NONE;
	attr_count += param;
	return True;
}

void karinSetAutoReshapeWhenResize(GLboolean b)
{
	autoReshape = b;
}

void karinGLInit(void)
{
	/*
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glShadeModel(GL_SMOOTH);
	*/
	//glEnable(GL_DEPTH_TEST);
}

void karinXResizeHandler(void)
{
	if(autoReshape)
		if(reshapeGL)
			reshapeGL((GLsizei)width, (GLsizei)height);
}

void karinGLDraw(void)
{
	/*
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glFlush();
	*/
}

void karinGLReshape(int w, int h)
{
	/*
	if(w < 1)
		w = 1;
	if(h < 1)
		h = 1;
	glViewport (0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, 0.0f, 10.0f);
	gluPerspective(45.0, 2, 0.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/
}

int karinXErrorHandler(Display *d, XErrorEvent *eev)
{
	char str[200];
	XGetErrorText(d, eev -> error_code, str, 99);
	str[199] = '\0';
	fprintf(stderr, "[ err -> %d - %s (%s)]\n", eev -> error_code, str, __func__);
	return 0;
}

Bool karinXEventLoop(void)
{
	if(!dpy)
	{
		fprintf(stderr, "X is not initialized!\n");
		return False;
	}
	XEvent xev;
	KeySym key;
	char text;
	Bool pressed;
	static char buf[64];
	KeySym keysym;

	static int mx = 0;
	static int my = 0;
	int dx = 0;
	int dy = 0;
	static Bool mousePressed = False;
	Bool handle = False;

#ifdef _XI2_MULTI_TOUCH
	while (X11_Pending(dpy)) 
#else
	while (XPending(dpy))
#endif
	{
		XNextEvent(dpy, &xev);
		switch(xev.type)
		{
			case KeyPress:
			case KeyRelease:
				pressed = (xev.xkey.type == KeyPress ? True : False);
				XLookupString(&(xev.xkey), buf, sizeof buf, &keysym, 0);
				if(keyHandler)
				{
					keyHandler(keysym, pressed, mx, my);
					//handle = True;
				}
					/*
				if (XLookupString(&xev.xkey,&text,1,&key,0)==1)
				{
					if (esContext.keyFunc != NULL)
						esContext.keyFunc(text, 0, 0);
				}
						*/
				break;
			case CreateNotify:
				x = xev.xcreatewindow.x;
				y = xev.xcreatewindow.y;
				width = xev.xcreatewindow.width;
				height = xev.xcreatewindow.height;
				if(resizeHandler)
					resizeHandler();
				handle = True;
				break;
			case ConfigureNotify:
				x = xev.xconfigure.x;
				y = xev.xconfigure.y;
				width = xev.xconfigure.width;
				height = xev.xconfigure.height;
				if(resizeHandler)
					resizeHandler();
				handle = True;
				break;
#ifndef _XI2_MULTI_TOUCH
			case MotionNotify:
				dx = xev.xmotion.x - mx;
				dy = xev.xmotion.y - my;
				mx = xev.xmotion.x;
				my = xev.xmotion.y;
				if(motionHandler)
				{
					motionHandler(xev.xmotion.state, mousePressed, mx, my, dx, dy);
					//handle = True;
				}
				break;
			case ButtonPress:
			case ButtonRelease:
				mx = xev.xbutton.x;
				my = xev.xbutton.y;
				mousePressed = (xev.xbutton.type == ButtonPress ? True : False);
				if(mouseHandler)
				{
					mouseHandler(xev.xbutton.button, mousePressed, mx, my);
					//handle = True;
				}
				break;
#endif
			case DestroyNotify:
				printf("Window will distroying\n");
				break;
			case Expose:
				handle = True;
				break;
			case VisibilityNotify:
				if(xev.xvisibility.state)
					handle = True;
				break;
				/*
				printf(" f %d t %lu\n", xev.xclient.format, xev.xclient.message_type);
				char *str = XGetAtomName(dpy, xev.xclient.message_type);
				printf("%s\n,", str);
				XFree(str);
				*/
				break;
#ifdef _XI2_MULTI_TOUCH
			case GenericEvent:
				if(!karinXI2Event(&xev))
					printf("Unhandle XGenericEvent\n");
				break;
#endif
			default:
				printf("Unhandle XEvent -> %d - %s\n", xev.type, karinX11EventString(xev.type));
				break;
		}
	}
	return handle;
}

void karinRegisterDrawFunc(drawGLFunc f)
{
	drawGL = f;
}

void karinRegisterReshapeFunc(reshapeGLFunc f)
{
	reshapeGL = f;
}

void karinRegisterInitFunc(initGLFunc f)
{
	initGL = f;
}

void karinRegisterKeyFunc(keyHandlerFunc f)
{
	keyHandler = f;
}

void karinRegisterMouseFunc(mouseHandlerFunc f)
{
	mouseHandler = f;
}

void karinRegisterIdleFunc(idleFunc f)
{
	idleHandler = f;
}

void karinRegisterExitFunc(exitXFunc f)
{
	exitX = f;
}

void karinRegisterMotionFunc(motionHandlerFunc f)
{
	motionHandler = f;
}

void karinRegisterResizeFunc(resizeHandlerFunc f)
{
	resizeHandler = f;
}

float karinCastFPS(void)
{
	struct timeval t1, t2;
	struct timezone tz;
	float deltatime;
	float totaltime = 0.0f;
	unsigned int frames = 0;
	gettimeofday ( &t1 , &tz );
	gettimeofday(&t2, &tz);
	deltatime = (float)(t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 1e-6);
	t1 = t2;
	totaltime += deltatime;
	frames++;
	if (totaltime > 2.0f)
	{
		printf("%4d frames rendered in %1.4f seconds -> FPS=%3.4f\n", frames, totaltime, frames/totaltime);
		totaltime -= 2.0f;
		frames = 0;
	}
	return frames / totaltime;
}

void karinPostExit(void)
{
	running = GL_FALSE;
}

void karinSetSingle(GLboolean s)
{
	single = s;
}

void karinSetAutoSwapBuffers(GLboolean b)
{
	autoSwapBuffers = b;
}

void karinPostDrawGL(void)
{
	if(!glCtxHasInit)
		return;
	if(!running)
		return;
	if(!drawGL)
		return;
	struct timeval beg_time, end_time;
	double delta_time = 0.0;
	gettimeofday(&beg_time, NULL);

	drawGL();
	if(autoSwapBuffers)
		karinSwapBuffers();

	gettimeofday(&end_time, NULL);
	delta_time = (end_time.tv_sec - beg_time.tv_sec) * 1000000.0 + (end_time.tv_usec - beg_time.tv_usec);
	if(max_fps > 0 && delta_time < frame_time_us)
	{
		usleep(frame_time_us - delta_time);
		//printf("d %f\n", frame_time_us - delta_time);
	}

	double n = 1000000.0 / (double)(delta_time < frame_time_us ? frame_time_us : delta_time);
	double nf = 0.0;
	double nl = modf(n, &nf);
	if(n >= 0.0)
	{
		if(nl >= 0.5)
			nf += 1.0;
	}
	else
	{
		if(nl >= 0.5)
			nf -= 1.0;
	}
	fps = (int)nf;
}

void karinMainLoop(void)
{
	if(!glCtxHasInit)
		return;
	running = GL_TRUE;
#ifdef _HARMATTAN_OPENGLES2
	gl2InitProgram();
#endif
	if(initGL)
		initGL();
	while(running)
	{
		if(karinXEventLoop())
		{
			karinPostDrawGL();
		}
		else
			//karinEventHandler();
		{
			if(idleHandler)
			{
				if(idleHandler())
					karinPostDrawGL();
			}
		}
		//float delta = karinCastFPS();
	}
#ifdef _HARMATTAN_OPENGLES2
	gl2DestroyProgram();
#endif
	if(single)
		karinShutdown();
}

void karinSetWindowPosiotionAndSize(int lx, int ly, int w, int h)
{
	x = lx;
	y = ly;
	if(w < 1)
		w = 1;
	if(h < 1)
		h = 1;
	width = w;
	height = h;
}

void karinPrintGLInfo()
{
	printf("------------------ OpenGL -----------------"); KARIN_ENDL
		printf("Version -> %s", glGetString(GL_VERSION)); KARIN_ENDL
		printf("Vendor -> %s", glGetString(GL_VENDOR)); KARIN_ENDL
		printf("Renderer -> %s", glGetString(GL_RENDERER)); KARIN_ENDL
#ifndef _HARMATTAN_OPENGLES
		printf("Shading Language Version -> %s", glGetString(GL_SHADING_LANGUAGE_VERSION)); KARIN_ENDL
#endif
		printf("Extensions -> "); KARIN_ENDL
		char *gl_extensions = strdup((const char *)glGetString(GL_EXTENSIONS));
	char *s = NULL;
	printf("  %s\n", strtok(gl_extensions, " "));
	while((s = strtok(NULL, " ")))
		printf("  %s\n", s);

#ifdef _HARMATTAN_OPENGL
	printf("------------------ GLU -----------------"); KARIN_ENDL
		printf("Version -> %s", gluGetString(GLU_VERSION)); KARIN_ENDL
		printf("Extensions -> "); KARIN_ENDL
		char *glu_extensions = strdup((const char *)gluGetString(GLU_EXTENSIONS));
	printf("  %s\n", strtok(glu_extensions, " "));
	while((s = strtok(NULL, " ")))
		printf("  %s\n", s);
	printf("----------------------------------------"); KARIN_ENDL
		free(gl_extensions);
	free(glu_extensions);
#endif
}

GLboolean karinQueryExtension(const char *extName)
{
	const char *ptr = (const char *)glGetString(GL_EXTENSIONS);
	if(!ptr)
		return GL_FALSE;
	const char *const end = ptr + strlen(ptr);
	size_t len = strlen(extName);

	while(ptr < end)
	{
		size_t l = strcspn(ptr, " ");
		if(l == len && strncmp(ptr, extName, l))
			return GL_TRUE;
		else
			ptr += (l + 1);
	}
	return GL_FALSE;
}

GLboolean karinIsRunning(void)
{
	return running;
}

GLboolean karinIsSingle(void)
{
	return single;
}

Bool karinHasInitGLctx(void)
{
	return glCtxHasInit;
}

void karinFullscreen(Bool fs)
{
	XClientMessageEvent xclient;

	xclient.type = ClientMessage;
	xclient.window = win;	//GDK_WINDOW_XID (window);
	xclient.message_type = XInternAtom(dpy, "_NET_WM_STATE", False);
	xclient.format = 32;
	xclient.data.l[0] = fs ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
	xclient.data.l[1] = XInternAtom(dpy, "_NET_WM_STATE_FULLSCREEN", fs);
	xclient.data.l[2] = 0;
	xclient.data.l[3] = 0;
	xclient.data.l[4] = 0;
	XSendEvent(dpy, DefaultRootWindow(dpy), False,
			SubstructureRedirectMask | SubstructureNotifyMask,
			(XEvent *) & xclient);
	/*
	int i;
	for(i = 0; i < 478; i++)
	{
		char *str = XGetAtomName(dpy, i);
		if(str){
		printf("%d - %s\n",i, str);
		XFree(str);}
	}
	*/
}

void karinSetMaxFPS(int i)
{
	if(i > 0)
	{
		max_fps = i;
		frame_time_us = 1.0 * 1000.0 * 1000.0 / (double)max_fps;
	}
	//printf("%f\n", frame_time_us);
}

const GLubyte * karinGetGLErrorString(void)
{
	return gluErrorString(glGetError());
}

const char * karinX11EventString(int e)
{
	static const char *XEvent_String[LASTEvent] = {
		"",
		"",
		"KeyPress",
		"KeyRelease",
		"ButtonPress",
		"ButtonRelease",
		"MotionNotify",
		"EnterNotify",
		"LeaveNotify",
		"FocusIn",
		"FocusOut",
		"KeymapNotify",
		"Expose",
		"GraphicsExpose",
		"NoExpose",
		"VisibilityNotify",
		"CreateNotify",
		"DestroyNotify",
		"UnmapNotify",
		"MapNotify",
		"MapRequest",
		"ReparentNotify",
		"ConfigureNotify",
		"ConfigureRequest",
		"GravityNotify",
		"ResizeRequest",
		"CirculateNotify",
		"CirculateRequest",
		"PropertyNotify",
		"SelectionClear",
		"SelectionRequest",
		"SelectionNotify",
		"ColormapNotify",
		"ClientMessage",
		"MappingNotify",
		"GenericEvent",
	};
	return XEvent_String[e];
}

/*
	 static void GLimp_DisableComposition(void)
	 {
	 XClientMessageEvent xclient;
	 Atom atom;
	 int one = 1;

	 atom = XInternAtom(dpy, "_HILDON_NON_COMPOSITED_WINDOW", False);
	 XChangeProperty(dpy, win, atom, XA_INTEGER, 32, PropModeReplace,
	 (unsigned char *)&one, 1);

	 xclient.type = ClientMessage;
	 xclient.window = win;	//GDK_WINDOW_XID (window);
	 xclient.message_type = XInternAtom(dpy, "_NET_WM_STATE", False);
	 xclient.format = 32;
	 xclient.data.l[0] =
//r_fullscreen->integer ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
//gdk_x11_atom_to_xatom_for_display (display, state1);
//gdk_x11_atom_to_xatom_for_display (display, state2);
xclient.data.l[1] = XInternAtom(dpy, "_NET_WM_STATE_FULLSCREEN", False);
xclient.data.l[2] = 0;
xclient.data.l[3] = 0;
xclient.data.l[4] = 0;
XSendEvent(dpy, DefaultRootWindow(dpy), False, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent *) & xclient);
}
*/

