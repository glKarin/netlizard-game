// gcc ada_fcv.c -o fcv.exe && fcv.exe

#include <stdio.h>

#define STRUCT_MEMBER // mark a struct
#define STRUCT_NAME(n) // mark a member of struct

// for debug
#define printfi(a) printf(#a"->%d\n", a)
#define printfx(a) printf(#a"->%x\n", a)
#define printfln(a) printf(#a"\n")
#define printfnl printf("\n")
#define printfs(a) printf(#a"->%s\n", a)
#define printfb(a) printf(#a"->%s\n", a ? "true" : "false")

typedef unsigned char uint8; // default char should be unsigned, may be not
typedef signed char int8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;

int main(int argc, char *argv[])
{
	FILE *is = fopen("e:/pmd/035_pl0b.FCV", "rb");
	if(!is)
		return 0;
	STRUCT_MEMBER uint8 frame_count = 0;
	STRUCT_MEMBER uint8 bone_count = 0;
	STRUCT_MEMBER uint8 animation_id = 0;
	STRUCT_MEMBER uint8 frame_id = 0;

	STRUCT_NAME(fcv)
	fread(&frame_count, sizeof(uint8), 1, is);
	fread(&animation_id, sizeof(uint8), 1, is);
	fread(&bone_count, sizeof(uint8), 1, is);
	fread(&frame_id, sizeof(uint8), 1, is);
	printfi(animation_id);
	printfi(frame_count);
	printfi(frame_id);
	printfi(bone_count);

	printfln(TYPE);
	STRUCT_NAME(type)
	int i;
	for(i = 0; i < bone_count; i++)
	{
		uint16 type = 0;
		fread(&type, sizeof(uint16), 1, is);
		printfx(type);
	}

	printfln(BONE);
	STRUCT_NAME(bone)
	for(i = 0; i < bone_count; i++)
	{
		STRUCT_MEMBER uint32 bone_index = 0;
		STRUCT_MEMBER uint8 bone_id = 0;
		fread(&bone_id, sizeof(uint8), 1, is);
		printf("%d->%d\n", i, bone_id);
	}

	// 现在应该过了你标记的绿色区域， 到了你说要跳过的地方
	// 但是多少字节


	printfb(feof(is) == 0);
	fclose(is);
	return 0;
}
