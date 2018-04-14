#ifndef KARIN_PRIVATE_EGL_H
#define KARIN_PRIVATE_EGL_H

// DO NOT INCLUDE THIS HEADER FILE IN OTHER WHERE !!!

#define KARIN_MAX_CONFIG 4

EGLDisplay eglDisplay;//EGL display
EGLContext eglContext;//EGL context
EGLSurface eglSurface;//EGL surface

static void karinEGLErrorHandle(void)
{
	static char *GLimp_StringErrors[] = {
		"EGL_SUCCESS",
		"EGL_NOT_INITIALIZED",
		"EGL_BAD_ACCESS",
		"EGL_BAD_ALLOC",
		"EGL_BAD_ATTRIBUTE",
		"EGL_BAD_CONFIG",
		"EGL_BAD_CONTEXT",
		"EGL_BAD_CURRENT_SURFACE",
		"EGL_BAD_DISPLAY",
		"EGL_BAD_MATCH",
		"EGL_BAD_NATIVE_PIXMAP",
		"EGL_BAD_NATIVE_WINDOW",
		"EGL_BAD_PARAMETER",
		"EGL_BAD_SURFACE",
		"EGL_CONTEXT_LOST"
	};
	GLint err = eglGetError();

	fprintf(stderr, "%s: 0x%04x: %s\n", __func__, err, GLimp_StringErrors[err - 0x3000]);
}

Bool karinInitGLctxObject(void)
{
	initGL = karinGLInit;
	drawGL = karinGLDraw;
	reshapeGL = karinGLReshape;

	resizeHandler = karinXResizeHandler;

	XSetErrorHandler(karinXErrorHandler);

	//XInitThreads();

	return karinSetGLctxInitAttribute(18, 
			EGL_NATIVE_VISUAL_TYPE, 0,
			EGL_BUFFER_SIZE, 16,
			EGL_RED_SIZE,5,
			EGL_GREEN_SIZE,6,
			EGL_BLUE_SIZE,5,
			EGL_DEPTH_SIZE,8,
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_RENDERABLE_TYPE, 
#ifdef _HARMATTAN_OPENGLES
			EGL_OPENGL_ES_BIT,
#else
			EGL_OPENGL_ES2_BIT,
#endif
			EGL_STENCIL_SIZE, 1
			);
}

Bool karinCreateGLContext(const char* title)
{
	Window root;
	XSetWindowAttributes swa;
	XSetWindowAttributes xattr;
	Atom wm_state;
	Colormap cmap;
	XWMHints hints;
	XVisualInfo *xvi = NULL;

	dpy = XOpenDisplay(NULL);
	if ( dpy == NULL )
		return False;
	root = DefaultRootWindow(dpy);
	//root = RootWindow( dpy, DefaultScreen( dpy ));
	int blackColour = BlackPixel(dpy, DefaultScreen(dpy));
	swa.event_mask = X_MASK;//ExposureMask | PointerMotionMask | KeyPressMask;
	win = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, width, height, 0, blackColour, blackColour);
#ifdef _XI2_MULTI_TOUCH
	karinInitXI2();
#endif
	XSelectInput(dpy, win, X_MASK);
	//Set the window attribute override allowed
	/*
		 xattr.override_redirect = 0;
		 XChangeWindowAttributes ( dpy, win, CWOverrideRedirect, &xattr );
	//Sets the window manager hints that include icon information and location, the initial state of the window, and
	hints.input = 1;
	hints.flags = InputHint;
	XSetWMHints(dpy, win, &hints);
	wm_state = XInternAtom (dpy, "_NET_WM_STATE", 0);
	memset ( &xev, 0, sizeof(xev) );
	xev.type = ClientMessage;
	xev.xclient.window = win;
	xev.xclient.message_type = wm_state;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = 1;
	xev.xclient.data.l[1] = 0;
	XSendEvent (dpy,DefaultRootWindow ( dpy ),0,SubstructureNotifyMask,&xev );
	*/
	//XMoveResizeWindow(dpy, win, 0, 0, esContext -> width, esContext -> height);
	//cmap = XCreateColormap(dpy, root, xvi -> visual,AllocNone);
	//swa.colormap = cmap;
	//win = XCreateWindow(dpy, root,0, 0, width, height, 0, 24, InputOutput, CopyFromParent, CWEventMask,&swa );
	XMapWindow (dpy, win);
	XStoreName (dpy, win, title);
	XFlush(dpy);

#ifdef _XI2_MULTI_TOUCH
	karinXI2Atom();
#endif

	EGLint numConfigs;
	EGLint majorVersion;
	EGLint minorVersion;
	EGLConfig config[KARIN_MAX_CONFIG];
	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
	//eglDisplay = eglGetDisplay(0);
	eglDisplay = eglGetDisplay((EGLNativeDisplayType)dpy);
	if ( eglDisplay == EGL_NO_DISPLAY )
	{
		karinEGLErrorHandle();
		return False;
	}
	//Initialize EGL
	if ( !eglInitialize(eglDisplay, &majorVersion, &minorVersion) )
	{
		karinEGLErrorHandle();
		return False;
	}
	//Get configs !This is NOT mandatory!!
	if ( !eglGetConfigs(eglDisplay, config, KARIN_MAX_CONFIG, &numConfigs) )
	{
		karinEGLErrorHandle();
		return False;
	}
	//Choose config

	if ( !eglChooseConfig(eglDisplay, attr, config, KARIN_MAX_CONFIG, &numConfigs) )
	{
		karinEGLErrorHandle();
		return False;
	}
	//Create a surface
	int i;
	for(i = 0; i < numConfigs; i++)
	{
		eglSurface = eglCreateWindowSurface(eglDisplay, config[i], (EGLNativeWindowType)win, NULL);
		if ( eglSurface != EGL_NO_SURFACE )
		{
			break;
		}
		karinEGLErrorHandle();
	}
	if ( eglSurface == EGL_NO_SURFACE )
		return False;
	//printf("%d %d\n", i, numConfigs);
	//Create a GL context
	eglContext = eglCreateContext(eglDisplay, config[i], EGL_NO_CONTEXT, 
#ifdef _HARMATTAN_OPENGLES
			NULL
#else
			contextAttribs
#endif
			);
	if ( eglContext == EGL_NO_CONTEXT )
	{
		karinEGLErrorHandle();
		return False;
	}
	//Make the context current
	if ( !eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext) )
	{
		karinEGLErrorHandle();
		return False;
	}

	return True;
}

void karinShutdown(void)
{
	if(!glCtxHasInit)
		return;
	if(exitX)
		exitX();

	eglMakeCurrent (eglDisplay, NULL, NULL, NULL);
	eglDestroySurface(eglDisplay, eglSurface);
	eglDestroyContext (eglDisplay, eglContext);

	if(dpy)
	{
		XDestroyWindow(dpy, win);
		XCloseDisplay(dpy);
	}
	glCtxHasInit = False;
}

void karinSwapBuffers(void)
{
	if(glCtxHasInit)
		eglSwapBuffers(eglDisplay, eglSurface);
}

void (*karinGetProcAddress(const GLubyte *procname))(void)
{
	if(glCtxHasInit)
		return eglGetProcAddress((const char *)procname);
	else
		return NULL;
}

Bool karinCreateGLRenderWindow(const char *title)
{
	if(!attr)
		return False;
	if(glCtxHasInit)
	{
		eglMakeCurrent (eglDisplay, NULL, NULL, NULL);
		eglDestroySurface(eglDisplay, eglSurface);
		eglDestroyContext (eglDisplay, eglContext);
		glCtxHasInit = False;
	}
	if(dpy)
	{
		XDestroyWindow(dpy, win);
		XCloseDisplay(dpy);
	}
	glCtxHasInit = karinCreateGLContext(title);
	karinPrintGLInfo();
	return glCtxHasInit;
}

#endif
