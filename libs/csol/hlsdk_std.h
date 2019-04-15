#ifndef _KARIN_HLSDK_STD_H
#define _KARIN_HLSDK_STD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <stdint.h>
#include "opengl/opengl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define COPY_ARR(a, b, n) \
	{ \
		int karin_i; \
		for(karin_i = 0; karin_i < (n); karin_i++) \
		{ \
			(a)[karin_i] = (b)[karin_i]; \
		} \
	}

#define _mkdir(p) mkdir(p, 0755)
#define _MAX_PATH 256
#define MAX_PATH 256
#define PATH_SEPARATOR_STR "/"

#define MAKEWORD(a, b) ((WORD)(((BYTE)((DWORD_PTR)(a))) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))

#define BI_RGB 0
#define BI_RLE8 1
#define BI_RLE4 2
#define BI_BITFIELDS 3

// Fixed
typedef uint32_t DWORD;
typedef uint16_t WORD;
typedef uintptr_t DWORD_PTR;

// Volatile
typedef unsigned char BYTE;
typedef unsigned int UINT;
typedef long LONG;
typedef unsigned long ULONG;

// has defined
typedef unsigned char Byte;

typedef enum _bool_t
{
	false = 0,
	true
} bool;

typedef struct tagBITMAPFILEHEADER
{
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
} BITMAPINFOHEADER;

typedef struct tagRGBQUAD
{
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
} RGBQUAD;

typedef struct tagRECT
{
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
} RECT;

typedef struct tagPOINT
{
	LONG x;
	LONG y;
} POINT;

typedef struct tagWINDOWPLACEMENT
{
	UINT length;
	UINT flags;
	UINT showCmd;
	POINT ptMinPosition;
	POINT ptMaxPosition;
	RECT rcNormalPosition;
} WINDOWPLACEMENT;

char * strset(char *str, char ch);

#ifdef __cplusplus
}
#endif

#endif
