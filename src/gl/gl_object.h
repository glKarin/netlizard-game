#ifndef _KARIN_GL_OBJECT_H
#define _KARIN_GL_OBJECT_H

#include "opengl/opengl.h"

void OpenGL_Cube_MinMax_VI(const GLfloat v1[3], const GLfloat v2[3], GLfloat *vertex, GLushort *indexs);
void OpenGL_Cube_CenterLength_VI(const GLfloat center[3], const GLfloat length[3], GLfloat *vertex, GLushort *indexs);
void OpenGL_Cube_MinMax_VTN(const GLfloat v1[3], const GLfloat v2[3], GLfloat *vertex, GLfloat *texcoord, GLfloat *normal);
void OpenGL_Cube_CenterLength_VTN(const GLfloat center[3], const GLfloat length[3], GLfloat *vertex, GLfloat *texcoord, GLfloat *normal);
void OpenGL_Plane_MinMax_VTN(const GLfloat v1[3], const GLfloat v2[3], GLfloat *vertex, GLfloat *texcoord, GLfloat *normal);
void OpenGL_Plane_CenterLength_VTN(const GLfloat center[3], const GLfloat length[2], GLfloat *vertex, GLfloat *texcoord, GLfloat *normal);

void OpenGL_Cube(const GLfloat length[3]);
void OpenGL_CubeSimple(const GLfloat length[3]);
void OpenGL_Plane(const GLfloat length[2]);


#endif
