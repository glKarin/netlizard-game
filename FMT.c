// abc_xyz.h
#ifndef _KARIN_ABC_XYZ_H
#define _KARIN_ABC_XYZ_H

#define NL_XXX_XXX_XXX

typedef unsigned long mask_t;

typedef int (* Xxx_Xxx_Xxx_f)(const char *a, int b);

typedef enum _Abc_Xxx_Xyz_e
{
	Abc_Aaa_Xyz = 0,
	Abc_Bbb_Xyz,
	Abc_Ccc_Xyz,
} Abc_Xxx_Xyz_e;

typedef struct _Xxx_Xxx_Xxx_s
{
	type_a member_a;
	type_b member_b;
	type_c member_c;
} Xxx_Xxx_Xxx_s;

typedef union _Xxx_Xxx_Xxx_u
{
	type_a member_a;
	type_b member_b;
	type_c member_c;
} Xxx_Xxx_Xxx_u;

int Module_XxxYyyyZzzzz(const char *a, int b);

void nlXxxYyyyZzzzz(void);

float strtof(const char *str);

Xxx_Xxx_Xxx_f xxx_xxx_func;
int Module_XxxXxxFunc(const char *a, int b);

int Rev_r(int parent, int level)
{
	if(parent < 0)
		return 0;
	Rev_r(parent - 1, level + 1);
	return 1;
}

#include "xxx_yyy_zzz_inc.c"

#endif
