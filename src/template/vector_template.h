#ifndef KARIN_VECTOR_TEMPLATR_H
#define KARIN_VECTOR_TEMPLATR_H

typedef struct _vector_template
{
	unsigned int size;
	void **data;
	unsigned int count;
	unsigned int unit;
	unsigned int group_count;
} vector_template;

#endif

