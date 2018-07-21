#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define glFunc_2_nglFunc_d(f) n##f##d

int main(int argc, char *argv[])
{
	glFunc_2_nglFunc_d(glRotate)(2, r, t);
			float angle = -400;
	int i = (int)angle;
	float f = angle - i;
	float r = angle;
	if(angle > 360)
	{
		f = i % 360 + f;
	}
	else if(angle < 0)
	{
		f = 360 - abs(i % 360 + f);
	}
	printf("%d   %f\n", i % 360, f);
	return 0;;
	int d = atoi(argv[1]);
	printf("%d\n", ((unsigned int)d) >> 16);
	printf("%d\n", 1<<10);
	printf("%f\n", 480.0 * (854.0 - 36.0) / 854.0);
	return 0;
}
