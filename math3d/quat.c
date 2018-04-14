#include "quat.h"

#include <stdio.h>

quat_t Quat_Make()
{
	quat_t q = {
		1.0,
		{0.0, 0.0, 0.0}
	};
	return q;
}

void Quat_Print(const quat_t *q)
{
	if(!q)
		return;
	printf("quat (r = %f, v = %f, %f, %f)\n", q -> r, q -> v.x, q -> v.y, q -> v.z);
}
