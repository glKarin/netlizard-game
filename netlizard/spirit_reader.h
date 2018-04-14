#ifndef KARIN_SPIRIT_READER_H
#define KARIN_SPIRIT_READER_H

#include "netlizard.h"

typedef struct _NETLizard_Spirit
{
	short index;
	short x;
	short y;
	short width;
	short height;
	short private_4;
	short private_5;
} NETLizard_Spirit;

array * nlReadSpiritMap(const char *file);

#endif

