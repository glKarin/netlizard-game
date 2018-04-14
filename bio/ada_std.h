#ifndef KARIN_ADA_STD_H
#define KARIN_ADA_STD_H

typedef float clampf_t;

#define ADA_FREE(ptr) \
	if(ptr) \
{\
	free(ptr); \
	ptr = NULL; \
}

#endif
