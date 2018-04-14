#ifndef KARIN_OPENGL_H
#define KARIN_OPENGL_H

#ifdef _HARMATTAN_OPENGLES
	#include "gles1.1/opengl/opengl1.h"
//	#include <EGL/egl.h>
	#define _OPENGLES
	#define oglDrawArrays(m, f, s) glDrawArrays(m, f, s)
	#define oglDrawElements(m, c, t, i) glDrawElements(m, c, t, i)
	#define oglEnable(e) glEnable(e)
	#define oglDisable(e) glDisable(e)
	#define oglIsEnabled(e) glIsEnabled(e)
	#define oglGetFloatv(n, p) glGetFloatv(n, p)
	#define oglGetIntegerv(n, p) glGetIntegerv(n, p)
	#define oglBindTexture(o, t) glBindTexture(o, t)
#elif defined(_HARMATTAN_OPENGLES2)
	#include "gles2.0/opengl/opengl2.h"
//	#include <EGL/egl.h>
	#define _OPENGLES2
	#define oglDrawArrays(m, f, s) gl2DrawArrays(m, f, s)
	#define oglDrawElements(m, c, t, i) gl2DrawElements(m, c, t, i)
	#define oglEnable(e) gl2Enable(e)
	#define oglDisable(e) gl2Disable(e)
	#define oglIsEnabled(e) gl2IsEnabled(e)
	#define oglGetFloatv(n, p) gl2GetFloatv(n, p)
	#define oglGetIntegerv(n, p) gl2GetIntegerv(n, p)
	#define oglBindTexture(o, t) gl2BindTexture(o, t)
#else
	#include <GL/gl.h>
	#include <GL/glext.h>
//	#include <GL/glx.h>
	#define _OPENGL
	#define oglDrawArrays(m, f, s) glDrawArrays(m, f, s)
	#define oglDrawElements(m, c, t, i) glDrawElements(m, c, t, i)
	#define oglEnable(e) glEnable(e)
	#define oglDisable(e) glDisable(e)
	#define oglIsEnabled(e) glIsEnabled(e)
	#define oglGetFloatv(n, p) glGetFloatv(n, p)
	#define oglGetIntegerv(n, p) glGetIntegerv(n, p)
	#define oglBindTexture(o, t) glBindTexture(o, t)
#endif

#endif
