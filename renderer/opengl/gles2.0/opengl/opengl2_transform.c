#include "opengl2.h"

#include "opengl2_math.h"

extern GL2_Matrix44 * gl2GetTopMatrix(GLvoid);

GLvoid gl2Translate(GLfloat x, GLfloat y, GLfloat z)
{
	GL2_Matrix44 *mat = gl2GetTopMatrix();
	if(!mat)
		return;
	Mesa_glTranslate(mat, x, y, z);
}

GLvoid gl2Rotate(GLfloat a, GLfloat x, GLfloat y, GLfloat z)
{
	GL2_Matrix44 *mat = gl2GetTopMatrix();
	if(!mat)
		return;
	Mesa_glRotate(mat, a, x, y, z);
}

GLvoid gl2Scale(GLfloat x, GLfloat y, GLfloat z)
{
	GL2_Matrix44 *mat = gl2GetTopMatrix();
	if(!mat)
		return;
	Mesa_glScale(mat, x, y, z);
}


GLvoid gl2Frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearval, GLfloat farval)
{
	GL2_Matrix44 *mat = gl2GetTopMatrix();
	if(!mat)
		return;
	Mesa_glFrustum(mat, left, right, bottom, top, nearval, farval);
}

GLvoid gl2Ortho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearval, GLfloat farval)
{
	GL2_Matrix44 *mat = gl2GetTopMatrix();
	if(!mat)
		return;
	Mesa_glOrtho(mat, left, right, bottom, top, nearval, farval);
}


GLvoid gl2LoadIdentity(GLvoid)
{
	GL2_Matrix44 *mat = gl2GetTopMatrix();
	if(!mat)
		return;
	Mesa_glLoadIdentity(mat);
}

GLvoid gl2LoadMatrix(const GLfloat *m)
{
	GL2_Matrix44 *mat = gl2GetTopMatrix();
	if(!mat)
		return;
	Mesa_glLoadMatrix(mat, m);
}

GLvoid gl2MultMatrix(const GLfloat *m)
{
	GL2_Matrix44 *mat = gl2GetTopMatrix();
	if(!mat)
		return;
	Mesa_glMultMatrix(mat, m);
}

