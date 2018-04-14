#ifndef KARIN_OPENGLU_H
#define KARIN_OPENGLU_H

#ifdef _HARMATTAN_OPENGLES
	#include "gles1.1/openglu/openglu1.h"
	#define _OPENGLUES
#elif defined(_HARMATTAN_OPENGLES2)
	#include "gles2.0/openglu/openglu2.h"
	#define _OPENGLUES2
#else
	#include <GL/glu.h>
	#define _OPENGLU
#endif

#endif
