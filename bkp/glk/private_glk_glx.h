#ifndef KARIN_PRIVATE_GLX_H
#define KARIN_PRIVATE_GLX_H

// DO NOT INCLUDE THIS HEADER FILE IN OTHER WHERE !!!

GLXWindow glw = 0;
GLXContext glc = 0;

static void karinGLXErrorHandler(void);

void karinGLXErrorHandler(void)
{
	fprintf(stderr, "glx error.\n");
}

Bool karinInitGLctxObject(void)
{
	initGL = karinGLInit;
	drawGL = karinGLDraw;
	reshapeGL = karinGLReshape;

	resizeHandler = karinXResizeHandler;

	XSetErrorHandler(karinXErrorHandler);

	//XInitThreads();

	return karinSetGLctxInitAttribute(16, 
			GLX_RENDER_TYPE, GLX_RGBA_BIT,
			GLX_DOUBLEBUFFER, True,
			GLX_STENCIL_SIZE, 1,
			GLX_RED_SIZE, 0,
			GLX_GREEN_SIZE, 0,
			GLX_BLUE_SIZE, 0,
			GLX_DEPTH_SIZE, 24,
			GLX_BUFFER_SIZE, 16
			);
}

Bool karinInitGLCtxObjectAndGLUT(int *argc, char *argv[])
{
	if(karinInitGLctxObject())
	{
		glutInit(argc, argv);
		return True;
	}
	return False;
}

Bool karinCreateGLContext(const char* title)
{
	Window root;
	XSetWindowAttributes swa;
	XSetWindowAttributes xattr;
	Atom wm_state;
	Colormap cmap;
	XWMHints hints;

	dpy = XOpenDisplay(NULL);
	if ( dpy == NULL )
		return False;
	//root = DefaultRootWindow(dpy);
	root = RootWindow( dpy, DefaultScreen( dpy ));
	//int blackColour = BlackPixel(dpy, DefaultScreen(dpy));
	swa.event_mask = X_MASK;//ExposureMask | PointerMotionMask | KeyPressMask;
	//win = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, esContext.width, esContext.height, 0, blackColour, blackColour);
	//XSelectInput(dpy, win, X_MASK);
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

	int numConfigs;
	GLXFBConfig *config = NULL;
	GLXFBConfig *configs = NULL;
	XVisualInfo *xvi = NULL;
	//init glx
	if (!glXQueryExtension(dpy, NULL, NULL))
	{
		karinGLXErrorHandler();
		return False;
	}
	/*
	//get configs
	configs = glXGetFBConfigs(dpy, DefaultScreen(dpy), &numConfigs);
	if (!configs)
	{
		karinGLXErrorHandler();
		return False;
	}
	printf("%d___\n", numConfigs);
	*/
	//choose config
	config = glXChooseFBConfig(dpy, DefaultScreen(dpy), attr, &numConfigs);
	if(!config)
	{
		karinGLXErrorHandler();
		return False;
	}
	int i;
	printf("glX config -> %d\n", numConfigs);
	for(i = 0; i < numConfigs; i++)
	{
		xvi = glXGetVisualFromFBConfig (dpy, config[i]);
		if(!xvi)
		{
			karinGLXErrorHandler();
			continue;
		}
		else
			break;
	}
	cmap = XCreateColormap(dpy, root, xvi -> visual,AllocNone);
	swa.colormap = cmap;
	win = XCreateWindow(dpy, RootWindow(dpy, xvi -> screen),0, 0, width, height, 0, xvi -> depth, InputOutput,xvi -> visual, CWEventMask,&swa );
	XMapWindow (dpy, win);
	XStoreName (dpy, win, title);
	XFlush(dpy);
	glw = glXCreateWindow (dpy, config[i], win, NULL);
	glc = glXCreateNewContext (dpy, config[i], GLX_RGBA_TYPE, NULL, GL_TRUE);
	printf("glX window -> %x\nglX context -> %ld\n", glw, glc);
	glXMakeContextCurrent (dpy, win, win, glc);

	return True;
}

void karinShutdown(void)
{
	if(!glCtxHasInit)
		return;
	if(exitX)
		exitX();

	glXDestroyContext(dpy, glc);
	glXDestroyWindow(dpy, glw);
	glXMakeContextCurrent (dpy, 0, 0, 0);

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
		glXSwapBuffers(dpy, glw);
}

Bool karinUseXFont(const char *name, int start, int size, GLuint list_start, unsigned int *w, unsigned int *h)
{
	if(glCtxHasInit)
	{
		XFontStruct *fontStruct = XLoadQueryFont(dpy, name);
		if(!fontStruct)
			return False;
		if(w)
			*w = fontStruct -> max_bounds.rbearing - fontStruct -> max_bounds.lbearing;
		if(h)
			*h = fontStruct -> max_bounds.ascent - fontStruct -> max_bounds.descent;
		//printf("%d %d %d %d %d\n", fontStruct -> min_bounds.lbearing, fontStruct -> min_bounds.rbearing, fontStruct -> min_bounds.width, fontStruct -> min_bounds.ascent, fontStruct -> min_bounds.descent);
		//printf("%d %d %d %d %d\n", fontStruct -> max_bounds.lbearing, fontStruct -> max_bounds.rbearing, fontStruct -> max_bounds.width, fontStruct -> max_bounds.ascent, fontStruct -> max_bounds.descent);
		glXUseXFont(fontStruct -> fid, start, size, list_start);
		XFreeFont(dpy, fontStruct);
		return True;
	}
	return False;
}

void (*karinGetProcAddress(const GLubyte *procname))(void)
{
	if(glCtxHasInit)
		return glXGetProcAddress(procname);
	else
		return NULL;
}

Bool karinCreateGLRenderWindow(const char *title)
{
	if(!attr)
		return False;
	if(glCtxHasInit)
	{
		glXDestroyContext(dpy, glc);
		glXDestroyWindow(dpy, glw);
		glXMakeContextCurrent (dpy, 0, 0, 0);
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
