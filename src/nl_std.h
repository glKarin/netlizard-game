#ifndef KARIN_NL_STD_H
#define KARIN_NL_STD_H

#include "math3d/vector.h"

typedef unsigned char bool_t; // GLboolean
typedef unsigned long mask_t; // GLbitfield
typedef unsigned int enum_t; // GLenum
typedef signed char byte_t; // GLbyte
//typedef wchar_t uchar_t;

#define _true 1
#define _false 0


typedef struct _vector3_t gl_vector3_t;
typedef struct _vector3_t nl_vector3_t;
typedef struct _vector2_t gl_vector2_t;
typedef struct _vector2_t nl_vector2_t;

#define CONVERT_VECTOR3_GL_TO_NL(glv, nlv) { \
	(nlv).x = -(glv).x; \
	(nlv).y = (glv).z; \
	(nlv).z = -(glv).y; \
}

#define CONVERT_VECTOR3_POINTER_GL_TO_NL(glvp, nlvp) { \
	(nlvp) -> x = -(glvp) -> x; \
	(nlvp) -> y = (glvp) -> z; \
	(nlvp) -> z = -(glvp) -> y; \
}

#define CONVERT_VECTOR3_NL_TO_GL(nlv, glv) { \
	(glv).x = -(nlv).x; \
	(glv).y = -(nlv).z; \
	(glv).z = (nlv).y; \
}

#define CONVERT_VECTOR3_POINTER_NL_TO_GL(nlvp, glvp) { \
	(glvp) -> x = -(nlvp) -> x; \
	(glvp) -> y = -(nlvp) -> z; \
	(glvp) -> z = (nlvp) -> y; \
}

#define RETURN_PTR(ptr, p, T) \
	T *ptr = NULL; \
	if(p) { \
		memset(p, 0, sizeof(T)); \
		ptr = p; \
	} else { \
		ptr = malloc(sizeof(T)); \
		memset(ptr, 0, sizeof(T)); \
	}

#define FREE_PTR(p) \
	if(p) \
{ \
	free(p); \
	p = NULL; \
}

#define FLOAT_ZERO 0.000001

int equalsf(float a, float b);
int iszerof(float f);
nl_vector3_t Algo_GLToNLVector3(const gl_vector3_t *glv, int *res);
gl_vector3_t Algo_NLToGLVector3(const nl_vector3_t *nlv, int *res);
void Algo_MakeGLVector3(vector3_t *v);
void Algo_MakeNLVector3(vector3_t *v);
char * itostr(int i);
char * lltostr(long long i);
char * ftostr(float f);
float rand_f(float min, float max, unsigned int per);
double Math_Round(double n);
char * lltotime_second(long long time);

#endif
