#include "camera.h"
#include "gl_util.h"

#include <math.h>
#include <stdlib.h>

void newcam(camera_s *cam)
{
	if(!cam)
		return;

	// not use memcpy
	VECTOR_X(cam->position) = VECTOR_Y(cam->position) = VECTOR_Z(cam->position) = 0;
	VECTOR_X(cam->rotation) = VECTOR_Y(cam->rotation) = VECTOR_Z(cam->rotation) = 0;
	VECTOR_X(cam->up) = VECTOR_Z(cam->up) = 0;
	VECTOR_Y(cam->up) = 1;
	VECTOR_X(cam->direction) = VECTOR_Y(cam->direction) = 0;
	VECTOR_Z(cam->direction) = -1;
}

void initcam(camera_s *cam, const vector3_s *pos, const vector3_s *rot)
{
	if(!cam)
		return;

	if(pos)
	{
		VECTOR_X(cam->position) = VECTOR_X(*pos);
		VECTOR_Y(cam->position) = VECTOR_Y(*pos);
		VECTOR_Z(cam->position) = VECTOR_Z(*pos);
	}

	if(rot)
	{
		VECTOR_X(cam->rotation) = Algo_FormatAngle(VECTOR_X(*rot));
		VECTOR_Y(cam->rotation) = Algo_FormatAngle(VECTOR_Y(*rot));
		//VECTOR_Z(cam->rotation) = Algo_FormatAngle(VECTOR_Z(*rot));
		angtodir(&cam->direction, &cam->rotation);
	}
	VECTOR_X(cam->up) = VECTOR_Z(cam->up) = 0;
	VECTOR_Y(cam->up) = 1;
}

void cammove(camera_s *cam, const vector3_s *unit)
{
	vector3_s v;
	vector3_s left;

	if(!unit)
		return;

	Vector3_CrossVector3v(&left, &cam->direction, &cam->up);

	v = Vector3_Scale(&left, VECTOR_X(*unit));
	cam->position = Vector3_PlusVector3(&cam->position, &v);

	v = Vector3_Scale(&cam->up, VECTOR_Y(*unit));
	cam->position = Vector3_PlusVector3(&cam->position, &v);

	v = Vector3_Scale(&cam->direction, VECTOR_Z(*unit));
	cam->position = Vector3_PlusVector3(&cam->position, &v);
}

void camrot(camera_s *cam, const vector3_s *unit)
{
	if(!unit)
		return;

	VECTOR_X(cam->rotation) = Algo_FormatAngle(VECTOR_X(cam->rotation) + VECTOR_X(*unit));
	VECTOR_Y(cam->rotation) = Algo_FormatAngle(VECTOR_Y(cam->rotation) + VECTOR_Y(*unit));
	//VECTOR_Z(cam->rotation) = Algo_FormatAngle(VECTOR_Z(cam->rotation) + VECTOR_Z(unit));
	angtodir(&cam->direction, &cam->rotation);
}

void angtodir(vector3_s *r, const vector3_s *a)
{
	float xrad, yrad;
	float x, y, z;
	float xz;

	if(!r || !a)
		return;

	xrad = ator(VECTOR_X(*a));
	yrad = ator(VECTOR_Y(*a));
	y = sin(xrad);
	xz = cos(xrad);
	x = -sin(yrad) * xz;
	z = cos(yrad) * xz;
	VECTOR_X(*r) = -x;
	VECTOR_Y(*r) = -y;
	VECTOR_Z(*r) = -z;
	Vector3_Normalize(r);
}

void camtrans_gl(const camera_s *cam)
{
#define USING_GLU 0
	if(!cam)
		return;
#if USING_GLU
	vector3_s forward = vector3_add(&cam->position, &cam->direction);
	gluLookAt(
			VECTOR_X(cam->position),
			VECTOR_Y(cam->position),
			VECTOR_Z(cam->position),
			VECTOR_X(forward),
			VECTOR_Y(forward),
			VECTOR_Z(forward),
			VECTOR_X(cam->up),
			VECTOR_Y(cam->up),
			VECTOR_Z(cam->up)
			);
#else
	glRotatef(VECTOR_X(cam->rotation), 1, 0, 0);
	glRotatef(VECTOR_Y(cam->rotation), 0, 1, 0);
	glTranslatef(
			-VECTOR_X(cam->position),
			-VECTOR_Y(cam->position),
			-VECTOR_Z(cam->position)
			);
#endif
}
