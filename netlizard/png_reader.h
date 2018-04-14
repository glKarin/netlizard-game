#ifndef KARIN_PNG_READER_H
#define KARIN_PNG_READER_H

#include "netlizard.h"

array * nlHandlePNG_File2Memory(const char *name);
array * nlHandlePNG_Memory2Memory(const array *arr);
int nlHandlePNG_File2File(const char *from, const char *to);
int nlHandlePNG_Memory2File(const array *arr, const char *to);

#endif
