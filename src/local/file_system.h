#ifndef KARIN_LOCAL_FILE_SYSTEM_H
#define KARIN_LOCAL_FILE_SYSTEM_H

#define FILE_SIZE_B 1
#define FILE_SIZE_K 2
#define FILE_SIZE_M 3
#define FILE_SIZE_G 4
#define FILE_SIZE_T 5

#define FILE_SIZE_FLOAT 0
#define FILE_SIZE_INT 1

#define FILE_SIZE_K_SIZE 1024
#define FILE_SIZE_M_SIZE (FILE_SIZE_K_SIZE * 1024)
#define FILE_SIZE_G_SIZE (FILE_SIZE_M_SIZE * 1024)
#define FILE_SIZE_T_SIZE (FILE_SIZE_G_SIZE * 1024)

typedef struct _file_size_s
{
	int unit;
	int type;
	union{
		struct {
			int t, g, m, k, b;
		} i;
		float f;
	} data;
} file_size_s;

int System_mkdir(const char *p);
char * System_GetPathFromHome(const char *p);
void File_GetSize(unsigned long bytes, int max_unit, file_size_s *r);

#endif
