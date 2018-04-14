#ifndef KARIN_TEXT_READER_H
#define KARIN_TEXT_READER_H

#include "netlizard.h"
#include <wchar.h>

array * nlHandleText_File2Memory(const char *name);
array * nlHandleText_Memory2Memory(const array *arr);
int nlHandleText_File2File(const char *from, const char *to);
int nlHandleText_Memory2File(const array *arr, const char *to);

#endif

