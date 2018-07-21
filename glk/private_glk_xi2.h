#ifndef KARIN_PRIVATE_XI2_H
#define KARIN_PRIVATE_XI2_H

// DO NOT INCLUDE THIS HEADER FILE IN OTHER WHERE !!!

#ifdef _XI2_MULTI_TOUCH

#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>

#define XI2_X11_ATOM_ID(id,name) id,
#define XI2_X11_ATOM_NAME(id,name) name,
#define ATOM_COUNT 3

static XIDeviceInfo *xi_master = NULL;
static int xi_opcode = 0;

static Bool karinMultiMouseEvent(int which, int button, Bool pressed, int x, int y)
{
	//printf("Finger->%d\n", which);
	if(mouseHandler)
		return mouseHandler(button, pressed, x, y);
	return 0;
}

static Bool karinMultiMouseMotionEvent(int which, int button, Bool pressed, int x, int y, int dx, int dy)
{
<<<<<<< HEAD
	//printf("Finger->%d\n", which);
=======
	//printf("Finger -> %d\n", which);
>>>>>>> 0a5cae165cbe3863c8dbcb6d639ddc9dc4ef6c7f
	if(motionHandler)
		return motionHandler(button, pressed, x, y, dx, dy);
	return 0;
}

enum
{
	XI2_X11_ATOM_ID(AbsMTTrackingID, "Abs MT Tracking ID")
		XI2_X11_ATOM_ID(AbsMTPositionX, "Abs MT Position X")
		XI2_X11_ATOM_ID(AbsMTPositionY, "Abs MT Position Y")
		//ATOM_COUNT
};
static const char * atom_names[ATOM_COUNT] = {
	XI2_X11_ATOM_NAME(AbsMTTrackingID, "Abs MT Tracking ID")
		XI2_X11_ATOM_NAME(AbsMTPositionX, "Abs MT Position X")
		XI2_X11_ATOM_NAME(AbsMTPositionY, "Abs MT Position Y")
};

static Atom atoms[ATOM_COUNT];
#define atom(x) atoms[x]
static int X11_XInput2_SetMasterPointer(int deviceid);

/* These are static for our mouse handling code */
typedef struct
{
	int MouseX;
	int MouseY;
	int DeltaX;
	int DeltaY;
	Bool ButtonState;
}MultiMouse;
#define MAXMOUSE 10
#define MOUSE_MAX_X (width - 1)
#define MOUSE_MAX_Y (height - 1)
static MultiMouse multi_mouses[MAXMOUSE];

static void MouseInit(void)
{
	/* The mouse is at (0,0) */
	int i;
	for (i = 0; i < MAXMOUSE; i++) {
		multi_mouses[i].MouseX = 0;
		multi_mouses[i].MouseY = 0;
		multi_mouses[i].DeltaX = 0;
		multi_mouses[i].DeltaY = 0;
		multi_mouses[i].ButtonState = False;
	}
}

static Bool GetMultiMouseState (int which, int *x, int *y)
{
	const MultiMouse * const mm = &(multi_mouses[which]);
	if ( x ) {
		*x = mm->MouseX;
	}
	if ( y ) {
		*y = mm->MouseY;
	}
	return(mm->ButtonState);
}

static Bool GetRelativeMultiMouseState (int which, int *x, int *y)
{
	MultiMouse * const mm = &(multi_mouses[which]);
	if ( x )
		*x = mm->DeltaX;
	if ( y )
		*y = mm->DeltaY;
	mm->DeltaX = 0;
	mm->DeltaY = 0;
	return(mm->ButtonState);
}

static Bool PrivateMultiMouseMotion(int which, Bool buttonstate, int relative, int x, int y)
{
	int X, Y;
	int Xrel;
	int Yrel;

	MultiMouse * const mm = &(multi_mouses[which]);
	/* Default buttonstate is the current one */
	if ( ! buttonstate ) {
		buttonstate = mm->ButtonState;
	}

	Xrel = x;
	Yrel = y;
	if ( relative ) {
		/* Push the cursor around */
		x = (mm->MouseX + x);
		y = (mm->MouseY + y);
	} else {
		/* Do we need to clip {x,y} ? */
		//ClipOffset(&x, &y);
	}

	/* Mouse coordinates range from 0 - width-1 and 0 - height-1 */
	if ( x < 0 )
		X = 0;
	else
	if ( x >= MOUSE_MAX_X )
		X = MOUSE_MAX_X-1;
	else
		X = x;

	if ( y < 0 )
		Y = 0;
	else
	if ( y >= MOUSE_MAX_Y )
		Y = MOUSE_MAX_Y-1;
	else
		Y = y;

	/* If not relative mode, generate relative motion from clamped X/Y.
	   This prevents lots of extraneous large delta relative motion when
	   the screen is windowed mode and the mouse is outside the window.
	*/
	if ( ! relative ) {
		Xrel = X - mm->MouseX;
		Yrel = Y - mm->MouseY;
	}

	/* Drop events that don't change state */
	if ( ! Xrel && ! Yrel ) {
#if 0
printf("Mouse event didn't change state - dropped!\n");
#endif
		return(False);
	}

	/* Update internal mouse state */
	mm->ButtonState = buttonstate;
	mm->MouseX = X;
	mm->MouseY = Y;
	mm->DeltaX += Xrel;
	mm->DeltaY += Yrel;
	/*
	if (which == 0) {
		// Redraw main pointer
		//SDL_MoveCursor(X, Y);
		//WILLTODO
	}
*/

	//CheckMultiMove(X, Y, X - Xrel, Y - Yrel, buttonstate);
	karinMultiMouseMotionEvent(which, 1, buttonstate, X, Y, Xrel, Yrel);

	/* Post the event, if desired */
	/*
	if ( SDL_ProcessEvents[SDL_MOUSEMOTION] == SDL_ENABLE ) {
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event));
		event.type = SDL_MOUSEMOTION;
		event.motion.which = which;
		event.motion.state = buttonstate;
		event.motion.x = X;
		event.motion.y = Y;
		event.motion.xrel = Xrel;
		event.motion.yrel = Yrel;
		if ( (SDL_EventOK == NULL) || (*SDL_EventOK)(&event) ) {
			posted = 1;
			SDL_PushEvent(&event);
		}
	}
	return(posted);
	*/
	return(True);
}

static Bool PrivateMultiMouseButton(int which, Bool state, int button/*left button*/, int x, int y)
{
	int move_mouse;
	Bool buttonstate;
	MultiMouse * const mm = &(multi_mouses[which]);

	/* Check parameters */
	if ( x || y ) {
		//ClipOffset(&x, &y);
		move_mouse = 1;
		/* Mouse coordinates range from 0 - width-1 and 0 - height-1 */
		if ( x < 0 )
			x = 0;
		else
		if ( x >= MOUSE_MAX_X )
			x = MOUSE_MAX_X-1;

		if ( y < 0 )
			y = 0;
		else
		if ( y >= MOUSE_MAX_Y )
			y = MOUSE_MAX_Y-1;
	} else {
		move_mouse = 0;
	}
	if ( ! x )
		x = mm->MouseX;
	if ( ! y )
		y = mm->MouseY;

	/* Figure out which event to perform */
	buttonstate = mm->ButtonState;
	buttonstate = state;

	/* Update internal mouse state */
	mm->ButtonState = buttonstate;
	if ( move_mouse ) {
		mm->MouseX = x;
		mm->MouseY = y;
		/*
		if (which == 0) {
			//SDL_MoveCursor(x, y);
			//WILLTODO
		}
		*/
	}

	karinMultiMouseEvent(which, 1, buttonstate, x, y);
	//CheckMultiButton(x, y, buttonstate);
	
	/* Post the event, if desired */
	/*
	if ( SDL_ProcessEvents[event.type] == SDL_ENABLE ) {
		event.button.which = which;
		event.button.state = state;
		event.button.button = button;
		event.button.x = x;
		event.button.y = y;
		if ( (SDL_EventOK == NULL) || (*SDL_EventOK)(&event) ) {
			posted = 1;
			SDL_PushEvent(&event);
		}
	}
	*/
	return(True);
}

static void ResetMultiMouse(int which)
{
	if( !multi_mouses[which].ButtonState )
		return;

	PrivateMultiMouseButton(which, False, 1/*left button*/, 0, 0);
}

static void ResetMouse(void)
{
	int i;
	for (i = 0; i < MAXMOUSE; i++) {
		ResetMultiMouse(i);
	}
}

int X11_XInput2_SetMasterPointer(int deviceid)
{
	int device_count = 0, i;
	if (xi_master) {
		XIFreeDeviceInfo(xi_master);
		xi_master = NULL;
	}

	xi_master = XIQueryDevice(dpy, deviceid, &device_count);
	if (!xi_master) {
		/* Master deviceid no longer exists? */
		return -1;
	}

	for (i = 0; i < xi_master->num_classes; i++) {
		if (xi_master->classes[i]->type == XIValuatorClass) {
			XIValuatorClassInfo *valuator = (XIValuatorClassInfo*)(xi_master->classes[i]);
			if (valuator->label == atom(AbsMTTrackingID)) {
				break;
			}
		}
	}

	return 0;
}
/* Ack!  XPending() actually performs a blocking read if no events available */
static int X11_Pending(Display *display)
{
	/* Flush the display connection and look to see if events are queued */
	XFlush(display);
	if ( XEventsQueued(display, QueuedAlready) ) {
		return(1);
	}

	/* More drastic measures are required -- see if X is ready to talk */
	{
		static struct timeval zero_time;	/* static == 0 */
		int x11_fd;
		fd_set fdset;

		x11_fd = ConnectionNumber(display);
		FD_ZERO(&fdset);
		FD_SET(x11_fd, &fdset);
		if ( select(x11_fd+1, &fdset, NULL, NULL, &zero_time) == 1 ) {
			return(XPending(display));
		}
	}

	/* Oh well, nothing is ready .. */
	return(0);
}

static inline void X11_XInput2_ClipTouch(int* val, int min, int size)
{
	if (*val < min || *val > (min + size)) {
		*val = -1;
	} else {
		*val -= min;
	}
}

static int X11_XInput2_DispatchTouchDeviceEvent(XIDeviceEvent *e)
{
	double v;
	int x, y;
	int active;
	int i;

	/* Sadly, we need to scale and clip the coordinates on our own. Prepare for this. */
	//const int screen_w = DisplayWidth(SDL_Display, SDL_Screen);
	//const int screen_h = DisplayHeight(SDL_Display, SDL_Screen);
	const int screen_w = width;
	const int screen_h = height;

	active = 0;
	for (i = 0; i < xi_master->num_classes; i++) {
		XIAnyClassInfo* any = xi_master->classes[i];
		//if (xi_master->classes[i]->type == XIValuatorClass) {
		if (any->type == XIValuatorClass) {
			XIValuatorClassInfo *valuator = (XIValuatorClassInfo*)(any);
			int n = valuator->number;

			if (!XIMaskIsSet(e->valuators.mask, n)) {
				/* This event does not contain this evaluator's value. */
				continue;
			}

			if (valuator->label == atom(AbsMTPositionX)) {
				v = e->valuators.values[n];
				v = (v - valuator->min) / (valuator->max - valuator->min);
				x = round(screen_w * v);
				//X11_XInput2_ClipTouch(&x, win_x, SCREEN_WIDTH); // No Use in full screen mode.
			} else if (valuator->label == atom(AbsMTPositionY)) {
				v = e->valuators.values[n];
				v = (v - valuator->min) / (valuator->max - valuator->min);
				y = round(screen_h * v);
				//X11_XInput2_ClipTouch(&y, win_y, SCREEN_HEIGHT); // No Use in full screen mode.
			} else if (valuator->label == atom(AbsMTTrackingID)) {
				/* Tracking ID is always the last valuator for a contact point,
				 * and indicates which finger we have been talking about previously. */
				int id = e->valuators.values[n];
				if (id >= MAXMOUSE) {
					/* Too many contact points! Discard! */
					continue;
				}
				if (x == -1 || y == -1) {
					/* Outside of the window, discard. */
					continue;
				}
				active |= 1 << id;
				if (GetMultiMouseState(id, NULL, NULL)) {
					/* We already knew about this finger; therefore, this is motion. */
					PrivateMultiMouseMotion(id, True, 0, x, y);
				} else {
					/* We did not know about this finger; therefore, this is a button press. */
					PrivateMultiMouseMotion(id, False, 0, x, y);
					PrivateMultiMouseButton(id, True, 1/*left button*/, 0, 0);
				}
			}
		}
	}

	/* Now enumerate all mouses and kill those that are not active. */
	for (i = 0; i < MAXMOUSE; i++) {
		if (!(active & (1 << i))) {
			ResetMultiMouse(i); /* Will send released events for pressed buttons. */
		}
	}

	return 1;
}

static int X11_XInput2_DispatchDeviceChangedEvent(XIDeviceChangedEvent *e)
{
	if (xi_master && e->deviceid == xi_master->deviceid) {
		/* Only care about slave change events of the master pointer, for now. */
		ResetMouse();
		X11_XInput2_SetMasterPointer(e->deviceid);
		return 1;
	}
	return 0;
}

static void LookupMultiButtonState(void)
{
	printf("------------------------------\n");
	int i;
	for(i = 0; i < MAXMOUSE; i++)
	{
		if(multi_mouses[i].ButtonState)
			printf("Finger->%d ,Mouse X->%d ,Mouse Y->%d , Delta X->%d ,Delta Y->%d ,Button State->%d\n", i, multi_mouses[i].MouseX, multi_mouses[i].MouseY, multi_mouses[i].DeltaX, multi_mouses[i].DeltaY, multi_mouses[i].ButtonState);
	}
	printf("------------------------------\n");
}

void karinInitXI2(void)
{
	int event, error;
	if (XQueryExtension(dpy, "XInputExtension", &xi_opcode, &event, &error)) {
		int major = 2;
		int minor = 0;
		if (XIQueryVersion(dpy, &major, &minor) == Success) {
			printf("XInput2 library version is %d.%d\n", major, minor);
		}
	}
	/* Find the master pointer and keep a reference to it. */
	int device_count = 0;
	XIDeviceInfo *devices = XIQueryDevice(dpy, XIAllMasterDevices, &device_count);
	if (devices) {
		int i;
		for (i = 0; i < device_count; i++) {
			if (devices[i].use == XIMasterPointer) {
				X11_XInput2_SetMasterPointer(devices[i].deviceid);
				break;
			}
		}
		XIFreeDeviceInfo(devices);
	}
	if (!xi_master) {
		/* No master pointer found? Broken XInput configuration. */
		fprintf(stderr, "No master pointer found? Broken XInput configuration.");
	}

	XIEventMask mask;
	unsigned char bitmask[XIMaskLen(XI_LASTEVENT)] = { 0 };
	mask.deviceid = XIAllMasterDevices;
	mask.mask = bitmask;
	mask.mask_len = sizeof(bitmask);

	/* For now, just capture mouse events. */
	XISetMask(bitmask, XI_ButtonPress);
	XISetMask(bitmask, XI_ButtonRelease);
	XISetMask(bitmask, XI_Motion);
	/* As well as new device events. */
	XISetMask(bitmask, XI_DeviceChanged);

	XISelectEvents(dpy, win, &mask, 1);

	/* We are no longer interested in the core protocol events. */
	MouseInit();
}

void karinXI2Atom(void)
{
	XInternAtoms(dpy, (char**) atom_names, ATOM_COUNT, False, atoms);
	//initialize XInput2 atoms.
}

Bool karinXI2Event(XEvent *event)
{
	if(!event)
		return False;
	if(event->type != GenericEvent)
		return False;
	// Only XInput2 event
	Bool res = False;
	if (event->xcookie.extension == xi_opcode) {
		if (XGetEventData(dpy, &event->xcookie)) {
			XIDeviceEvent *xi_event = NULL;
			XIDeviceChangedEvent *xi_changeevent = NULL;
			switch (((XIEvent *)event->xcookie.data) ->evtype) {
				case XI_ButtonPress:
				case XI_ButtonRelease:
				case XI_Motion:
					xi_event = (XIDeviceEvent *)event->xcookie.data;
					X11_XInput2_DispatchTouchDeviceEvent(xi_event);
					res = True;
					break;
				case XI_DeviceChanged:
					xi_changeevent = (XIDeviceChangedEvent *)event->xcookie.data;
					X11_XInput2_DispatchDeviceChangedEvent(xi_changeevent);
					res = True;
					break;
				default:
					printf("Unhandled XInput2 event %d\n", xi_event->evtype);
					break;
			}
			XFreeEventData(dpy, &event->xcookie);
		}
	}
	return res;;
}

#endif

#endif
