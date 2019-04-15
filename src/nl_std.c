#include "nl_std.h"

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

nl_vector3_s Algo_GLToNLVector3(const gl_vector3_s *glv, int *res)
{
	nl_vector3_s nlv = {0.0, 0.0, 0.0};
	if(!glv)
	{
		if(res)
			*res = 0;
		return nlv;
	}
	CONVERT_VECTOR3_POINTER_GL_TO_NL(glv, &nlv)
	if(res)
		*res = 1;
	return nlv;
}

gl_vector3_s Algo_NLToGLVector3(const nl_vector3_s *nlv, int *res)
{
	gl_vector3_s glv = {0.0, 0.0, 0.0};
	if(!nlv)
	{
		if(res)
			*res = 0;
		return glv;
	}
	CONVERT_VECTOR3_POINTER_NL_TO_GL(nlv, &glv)
	if(res)
		*res = 1;
	return glv;
}

void Algo_MakeGLVector3(vector3_s *v)
{
	if(!v)
		return;
	vector3_s rv = *v;
	CONVERT_VECTOR3_POINTER_NL_TO_GL(&rv, v)
}

void Algo_MakeNLVector3(vector3_s *v)
{
	if(!v)
		return;
	vector3_s rv = *v;
	CONVERT_VECTOR3_POINTER_GL_TO_NL(&rv, v)
}

char * ftostr(float f)
{
	int o = 1;
	float num = f;
	if(f < 0)
	{
		o = 0;
		num = -num;
	}
	double nf = 0.0;
	double nl = modf(num, &nf);
	int first = (int)nf;
	int size = 1;
	int base = 10;
	for(; first / base; base *= 10)
		size++;
	int has_f = 0;
	int f_size = 0;
	if(nl != 0.0)
	{
		has_f = 1;
		size++;
		double d;
		while(modf(nl, &d) > 0.0)
		{
			nl *= 10.0;
			size++;
			f_size++;
		}
	}
	if(o == 0)
		size++;
	char *str = (char *)malloc(size + 1);
	memset(str, '\0', size + 1);
	if(has_f)
	{
		char fmt[] = "%%.%df";
		char rfmt[7]; // %.2f\0
		memset(rfmt, '\0', sizeof(char) * 7);
		sprintf(rfmt, fmt, f_size);
		sprintf(str, rfmt, f);
	}
	else
		sprintf(str, "%d", first);
	return str;
}

char * itostr(int i)
{
	int o = 1;
	int num = i;
	if(i < 0)
	{
		o = 0;
		num = -num;
	}
	int size = 1;
	int base = 10;
	for(; num / base; base *= 10)
		size++;
	if(o == 0)
		size++;
	char *str = (char *)malloc(size + 1);
	memset(str, '\0', size + 1);
	sprintf(str, "%d", i);
	return str;
}

float rand_f(float min, float max, unsigned int per)
{
	if(max <= min)
		return 0.0f;
	if(per == 0)
		return (max - min) / 2.0f;
	float fper = (float)per;
	int min_i = (int)(min * fper);
	int max_i = (int)(max * fper);
	//printf("%f\n", p);
	int i = max_i - min_i;
	if(i == 0)
		return 0.0;
	int r = rand() % i + min_i;
	return (float)r / fper;
}

double Math_Round(double n)
{
	double nf = 0.0;
	double nl = modf(n, &nf);
	if(n >= 0.0)
	{
		if(nl < 0.5)
			return nf;
		else
			return nf + 1.0;
	}
	else
	{
		if(nl < 0.5)
			return nf;
		else
			return nf - 1.0;
	}
}

char * lltotime_second(long long time)
{
	if(time < 0)
		return NULL;
	char second = time % 60;
	char minute = time / 60 % 60;
	int hour = time / 3600;
	char *h = itostr(hour);
	char *str = calloc(strlen(h) + 7, sizeof(char));
	sprintf(str, "%s:%02d:%02d", h, minute, second);
	free(h);
	return str;
}

char * lltostr(long long i)
{
	int o = 1;
	long long num = i;
	if(i < 0)
	{
		o = 0;
		num = -num;
	}
	int size = 1;
	long long base = 10;
	for(; num / base; base *= 10)
		size++;
	if(o == 0)
		size++;
	char *str = (char *)malloc(size + 1);
	memset(str, '\0', size + 1);
	sprintf(str, "%lld", i);
	return str;
}

int iszerof(float f)
{
	if(f <= FLOAT_ZERO && f >= -FLOAT_ZERO)
		return 1;
	else
		return 0;
}

int equalsf(float a, float b)
{
	float f = a - b;
	return iszerof(f);
}

char * itobin(unsigned n)
{
	int len = sizeof(unsigned) * 8;
	char *ret = calloc(len + 1, sizeof(char));
	int i;
	for(i = 0; i < len; i++)
	{
		ret[len - i - 1] = (n & (1 << i)) ? '1' : '0';
	}
	return ret;
}
