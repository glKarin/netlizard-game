#ifndef KARIN_OPENGLU1_H
#define KARIN_OPENGLU1_H

#ifdef _HARMATTAN_OPENGLES

#include "../opengl/opengl1.h"
#ifndef GLAPIENTRY
#define GLAPIENTRY GL_APIENTRY
#endif
/* ErrorCode */
#define GLU_INVALID_ENUM                   100900
#define GLU_INVALID_VALUE                  100901
#define GLU_OUT_OF_MEMORY                  100902
#define GLU_INCOMPATIBLE_GL_VERSION        100903
#define GLU_INVALID_OPERATION              100904

// error
const GLubyte* GLAPIENTRY gluErrorString(GLenum errorCode);

// project
void gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
void gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez, GLdouble centerx, GLdouble centery, GLdouble centerz, GLdouble upx, GLdouble upy, GLdouble upz);
GLint GLAPIENTRY gluProject(GLdouble objx, GLdouble objy, GLdouble objz, const GLdouble modelMatrix[16], const GLdouble projMatrix[16], const GLint viewport[4], GLdouble *winx, GLdouble *winy, GLdouble *winz);
GLint GLAPIENTRY gluUnProject(GLdouble winx, GLdouble winy, GLdouble winz, const GLdouble modelMatrix[16], const GLdouble projMatrix[16], const GLint viewport[4], GLdouble *objx, GLdouble *objy, GLdouble *objz);

void GLAPIENTRY gluPickMatrix(GLdouble x, GLdouble y, GLdouble deltax, GLdouble deltay, GLint viewport[4]);

// mipmap
GLint GLAPIENTRY gluScaleImage(GLenum format, GLsizei widthin, GLsizei heightin, GLenum typein, const void *datain, GLsizei widthout, GLsizei heightout, GLenum typeout, void *dataout);

#endif

#endif
