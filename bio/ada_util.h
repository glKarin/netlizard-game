#ifndef KARIN_ADA_UTIL_H
#define KARIN_ADA_UTIL_H

#include "ada_std.h"

#include <stdio.h>

char * Ada_ReadLine(FILE *is);
void Ada_SkipLine(FILE *is);
int Ada_ReadString(char *str, char **r, int *count);
int Ada_ReadInt(char *str, int *r, int *count);
int Ada_ReadFloat(char *str, float *r, int *count);

#endif
