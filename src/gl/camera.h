#ifndef _KARIN_CAMERA_H
#define _KARIN_CAMERA_H

#include "math3d/vector.h"

#ifdef __cplusplus
extern "C" {
#endif

	// using left-right on X, up-down on Y, forward-backward on Z(far-side is less than near-side)
	// same as OpenGL(right-hand)

	typedef struct _camera_s
	{
		vector3_s position;
		vector3_s direction; // init is to Z(0, 0, -1)
		vector3_s rotation; // Z is always 0(not allow Z-rotation for rolling head)
		vector3_s up; // always up(0, 1, 0) for simple
	} camera_s;

	void cammove(camera_s *cam, const vector3_s *unit);
	void camrot(camera_s *cam, const vector3_s *unit);
	void newcam(camera_s *cam);
	void initcam(camera_s *cam, const vector3_s *pos, const vector3_s *rot);
	void angtodir(vector3_s *r, const vector3_s *a);
	void camtrans_gl(const camera_s *cam);

#ifdef __cplusplus
}
#endif

#endif // CAMERA_H

