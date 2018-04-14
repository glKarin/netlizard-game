#include "racingevolution3d_reader.h"
#include "nl_util.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define dprintfsi(s, d) nlprintf("RE 3D : "#s" -> %d\n", d)
#define dprintfsii(s, d, d2) nlprintf("RE 3D : ""%d - "#s" -> %d\n", d, d2)
#define dprintfss(s) nlprintf("RE 3D : "#s"\n")
#define dprintfsss(s, s2) nlprintf("RE 3D : "#s" -> %s""\n", s2)

static int class_b__function_a__1byte_2byte(byte paramByte1, byte paramByte2);
static int class_b__function_c__1byte_array_2int(const char paramArrayOfByte[], int paramInt);
static int class_e__function_a__1Appearance_2int_3byte_array_4int(char *name[], int paramInt1, const char paramArrayOfByte[], int paramInt2);
static int class_e__function_a__1class_k_array_2int_array_3int_4byte_array_5int(RE3D_Mesh *m, int paramArrayOfInt[], int paramInt1, const char paramArrayOfByte[], int paramInt2);
static float class_b__function_a__1byte_array_2int(const char paramArrayOfByte[], int paramInt);

int nlIsRE3DMeshFile(const char *name)
{
	if(!name)
		return 0;
	array *arr = nlReadFile(name);
	if(!arr)
		return 0;
	int res = nlIsRE3DMesh(arr);
	delete_array(arr);
	free(arr);
	return res;
}

int nlIsRE3DMesh(const array *arr)
{
	static const char b[] = { 78, 76, 95, 77, 69, 83, 72 }; // NL_MESH
	static const size_t b_length = 7;

	if(!arr)
		return 0;
	
	size_t l = arr -> length;
	if(l < b_length)
		return 0;
	byte *arrayOfByte = (byte *)(arr -> array);
	int i2 = (strncmp(arrayOfByte, b, b_length) == 0) ? b_length : 0;
	return i2; // 7
}

RE3D_Model * nlReadRE3DMesh(const array *arr)
{
	if(!arr)
		return NULL;
	int paramInt = nlIsRE3DMesh(arr);
	if(!paramInt)
		return NULL;
	byte *paramArrayOfByte = (byte *)(arr -> array);
	int i1 = paramInt; // 7
	int i2 = 0;
	int i3 = paramArrayOfByte[(i1++)];
	dprintfsi("Map texture file count", i3);
	int i4;
	//k[] arrayOfk = new k[i4 = b_a(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)])];
	i4 = class_b__function_a__1byte_2byte(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]);
	dprintfsi("Map scene count", i4);
	//Appearance[] arrayOfAppearance = new Appearance[i3];
	int *arrayOfInt = NEW_II(int, i4);
	array *texes = new_array(nl_pointer, i3, NULL, 0);
	char **filenames = (char **)(texes -> array);
	//t = new String[i3];
	//s = new Texture2D[i3];
	//r = 0;
	int i5 = 0;
	int i7;
	int i6;
	for (i6 = 0; i6 < i3; i6++) {
		if ((i2 = paramArrayOfByte[(i1++)] & 0xFF) == 225) {
			i1 = class_e__function_a__1Appearance_2int_3byte_array_4int(filenames + i6, i5++, paramArrayOfByte, i1);
			dprintfsss("Map texture file", ((char **)(texes -> array))[i6]);
		}
	}
	i5 = 0;
	array *meshes = new_array(nl_user, i4, NULL, sizeof(RE3D_Mesh));
	for (i7 = 0; i7 < i4; i7++) {
		if ((i2 = paramArrayOfByte[(i1++)] & 0xFF) == 241) {
			RE3D_Mesh *mesh = ((RE3D_Mesh *)(meshes -> array)) + i7;
			i1 = class_e__function_a__1class_k_array_2int_array_3int_4byte_array_5int(mesh, arrayOfInt, i5++, paramArrayOfByte, i1);
		}
	}
	for (i6 = 0; i6 < i4; i6++) {
		RE3D_Mesh *mesh = ((RE3D_Mesh *)(meshes -> array)) + i6;
		if ((i7 = arrayOfInt[i6]) < 127)
		{
			mesh -> tex_index = i7;
			/*
			int i8;
			if (((i8 = arrayOfAppearance[i7].getUserID()) & 0x4) != 0) {
				arrayOfk[i6].a = true;
			}
			*/
		}
		else
			mesh -> tex_index = -1;
	}
	free(arrayOfInt);
	RE3D_Model *model = NEW(RE3D_Model);
	ZERO(model, RE3D_Model);
	model -> meshes = meshes;
	model -> texes = texes;
	return model;
}

RE3D_Model * nlReadRE3DMeshFile(const char *name)
{
	if(!name)
		return NULL;
	array *arr = nlReadFile(name);
	if(!arr)
		return NULL;
	RE3D_Model *model = nlReadRE3DMesh(arr);
	delete_array(arr);
	free(arr);
	return model;
}

void delete_RE3D_Mesh(RE3D_Mesh *mesh)
{
	if(!mesh)
		return;
	delete_array(mesh -> vertex);
	free(mesh -> vertex);
	delete_array(mesh -> texcoord);
	free(mesh -> texcoord);
	delete_array(mesh -> index);
	free(mesh -> index);
	delete_array(mesh -> strip);
	free(mesh -> strip);
}

void delete_RE3D_Model(RE3D_Model *model)
{
	if(!model)
		return;
	int i;
	for(i = 0; i < model -> meshes -> length; i++)
	{
		delete_RE3D_Mesh(((RE3D_Mesh *)(model -> meshes -> array)) + i);
	}
	delete_array(model -> meshes);
	free(model -> meshes);
	for(i = 0; i < model -> texes -> length; i++)
		free(((char **)(model -> texes -> array))[i]);
	delete_array(model -> texes);
	free(model -> texes);
}

/* ****** static ****** */

int class_b__function_a__1byte_2byte(byte paramByte1, byte paramByte2)
{
	int i = paramByte1 & 0xFF;
	int j;
	return (((j = paramByte2 & 0xFF) & 0xFF) << 8) + (i & 0xFF);
}

int class_e__function_a__1Appearance_2int_3byte_array_4int(char *name[], int paramInt1, const char paramArrayOfByte[], int paramInt2)
{
	int i1 = paramInt2;
	//Appearance localAppearance = new Appearance();
	//new Material();
	i1 += 13;
	//int i2 = class_b__function_c__1byte_array_2int(paramArrayOfByte, i1);
	i1 += 4;
	char *arrayOfChar = NULL; // java char type
	int i3;
	//Object localObject;
	if ((i3 = paramArrayOfByte[(i1++)] & 0xFF) > 0)
	{
		char localObject[32]; // java char type
		int i4 = 0;
		int i5;
		for (i5 = paramArrayOfByte[(i1++)]; i5 != 0; i5 = paramArrayOfByte[(i1++)])
		{
			if (i5 < 0) {
				i5 = 256 + i5;
			}
			if ((i5 >= 192) && (i5 <= 255)) {
				i5 += 848;
			}
			if ((i5 >= 65) && (i5 <= 90)) {
				i5 += 32;
			}
			localObject[(i4++)] = ((char)i5); // java char type
		}
		arrayOfChar = NEW_II(char, i4 + 1); // java char type
		memcpy(arrayOfChar, localObject, sizeof(char) * i4);
		arrayOfChar[i4] = '\0';
		//System.arraycopy(localObject, 0, arrayOfChar, 0, i4);
	}
	*name = arrayOfChar;
	/*
		 (localObject = new PolygonMode()).setCulling(160);
		 ((PolygonMode)localObject).setPerspectiveCorrectionEnable(false);
		 localAppearance.setPolygonMode((PolygonMode)localObject);
		 CompositingMode localCompositingMode;
		 (localCompositingMode = new CompositingMode()).setDepthWriteEnable(true);
		 localCompositingMode.setDepthTestEnable(true);
		 localAppearance.setCompositingMode(localCompositingMode);
		 localAppearance.setUserID(i2);
		 */
	/*
		 if (arrayOfChar != null) {
		 String str1 = new String(arrayOfChar);
		 String str2 = "/" + str1;
		 int i6 = 0;
		 if (str1.endsWith("a.png")) {
		 i6 = 1;
		 }
		 int i7 = -1;
		 for (int i8 = 0; i8 < r; i8++) {
		 if (str2.compareTo(t[i8]) == 0)
		 {
		 i7 = i8;
		 break;
		 }
		 }
		 Texture2D localTexture2D;
		 if (i7 >= 0)
		 {
		 localTexture2D = s[i7];
		 }
		 else
		 {
		 int i9 = 99;
		 if (i6 != 0) {
		 i9 = 100;
		 }
		 Image2D localImage2D = new Image2D(i9, d.a(str2));
		 localTexture2D = new Texture2D(localImage2D);
		 s[r] = localTexture2D;
		 t[r] = str2;
		 r += 1;
		 }
		 if (i6 != 0)
		 {
		 localCompositingMode.setAlphaWriteEnable(true);
		 localAppearance.getCompositingMode().setBlending(64);
		 }
		 localTexture2D.setBlending(228);
		 localTexture2D.setFiltering(210, 210);
		 localTexture2D.setWrapping(240, 240);
		 localAppearance.setTexture(0, localTexture2D);
		 }
		 paramArrayOfAppearance[paramInt1] = localAppearance;
		 */
	return i1;
}

int class_b__function_c__1byte_array_2int(const char paramArrayOfByte[], int paramInt)
{
	int i = paramArrayOfByte[paramInt] & 0xFF;
	int j = paramArrayOfByte[(paramInt + 1)] & 0xFF;
	int k = paramArrayOfByte[(paramInt + 2)] & 0xFF;
	int m = paramArrayOfByte[(paramInt + 3)] & 0xFF;
	return i + (j << 8) + (k << 16) + (m << 24);
}

int class_e__function_a__1class_k_array_2int_array_3int_4byte_array_5int(RE3D_Mesh *m, int paramArrayOfInt[], int paramInt1, const char paramArrayOfByte[], int paramInt2)
{
	int i1 = paramInt2;
	int i2 = class_b__function_a__1byte_2byte(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]);
	i1++;
	i1++;
	int i3 = class_b__function_a__1byte_2byte(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]);
	int i4 = class_b__function_a__1byte_2byte(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]);
	int i5 = paramArrayOfByte[(i1++)] & 0xFF;
	int i6;
	float arrayOfFloat[3];
	for (i6 = 0; i6 < 3; i6++)
	{
		arrayOfFloat[i6] = class_b__function_a__1byte_array_2int(paramArrayOfByte, i1);
		i1 += 4;
	}
	memcpy(m -> translation, arrayOfFloat, sizeof(float) * 3);
	//printf("RE 3D map primitive position -> x: %f, y: %f, z: %f\n", arrayOfFloat[0], arrayOfFloat[1], arrayOfFloat[2]);
	float f1 = class_b__function_a__1byte_array_2int(paramArrayOfByte, i1);
	i1 += 4;
	//paramArrayOfk[paramInt1] = new k();
	//paramArrayOfk[paramInt1].h = b.a(paramArrayOfByte, i1);
	//float k_h = class_b__function_a__1byte_array_2int(paramArrayOfByte, i1);
	i1 += 4;
	class_b__function_a__1byte_array_2int(paramArrayOfByte, i1);
	i1 += 4;
	//paramArrayOfk[paramInt1].i = b.a(paramArrayOfByte, i1);
	//float k_i = class_b__function_a__1byte_array_2int(paramArrayOfByte, i1);
	i1 += 4;
	//paramArrayOfk[paramInt1].f = b.a(paramArrayOfByte, i1);
	//float k_f = class_b__function_a__1byte_array_2int(paramArrayOfByte, i1);
	i1 += 4;
	//paramArrayOfk[paramInt1].b = ((int)(paramArrayOfk[paramInt1].h * 4095.0F));
	//paramArrayOfk[paramInt1].c = ((int)(paramArrayOfk[paramInt1].h * 4095.0F));
	//int k_b = ((int)(k_h * 4095.0F));
	//int k_c = ((int)(k_h * 4095.0F));
	//VertexBuffer localVertexBuffer = new VertexBuffer();
	float f2 = 3.051851E-5F * f1;
	//printf("(%f, %f, %f) %f - %f\n", k_h, k_i, k_f, (float)k_b * f2, f2);
	int i7 = paramArrayOfByte[(i1++)] & 0xFF;
	int i8 = 0;
	int i9;
	short *localObject = NULL;
	if (i7 == 242)
	{
		//VertexArray localVertexArray1 = new VertexArray(i2, 3, 2);
		dprintfsi("Scene vertex count", i2);
		localObject = NEW_II(short, i2 * 3);
		float *vertex = NEW_II(float, i2 * 3);
		for (i9 = 0; i9 < i2 * 3; i9++)
		{
			i8 = class_b__function_a__1byte_2byte(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]) - 32767;
			localObject[i9] = ((short)i8);
			/*
				 if(i9 % 3 == 0)
				 printf(" | ");
				 printf("%f ", f2 * (float)i8);
				 */
			vertex[i9] = f2 * (float)i8;
		}
		//printf("<%f %f %f>\n", vertex[0], vertex[1], vertex[2]);
		m -> vertex = new_array(nl_float, i2 * 3, vertex, 0);
		free(localObject);
		free(vertex);
		//printf("RE 3D map primitive scale factory -> %f\n", f2);
		//localVertexArray1.set(0, i2, (short[])localObject);
		//localVertexBuffer.setPositions(localVertexArray1, f2, arrayOfFloat);
		i7 = paramArrayOfByte[(i1++)] & 0xFF;
	}
	if (i7 == 244)
	{
		//VertexArray localVertexArray2 = new VertexArray(i2, 2, 2);
		dprintfsi("Scene texcoord count", i2);
		localObject = NEW_II(short, i2 * 2);
		float *texcoord = NEW_II(float, i2 * 2);
		for (i9 = 0; i9 < i2; i9++)
		{
			localObject[(i9 * 2)] = ((short)(paramArrayOfByte[(i1++)] & 0xFF));
			localObject[(i9 * 2 + 1)] = ((short)(255 - (paramArrayOfByte[(i1++)] & 0xFF)));
			/*
				 printf("%f %f | ", 0.003921569F * (float)localObject[i9 * 2], 0.003921569F * (float)localObject[i9 * 2 + 1]);
				 */
			texcoord[i9 * 2] = 0.003921569F * (float)localObject[i9 * 2];
			texcoord[i9 * 2 + 1] = 0.003921569F * (float)localObject[i9 * 2 + 1];
		}
		m -> texcoord = new_array(nl_float, i2 * 2, texcoord, 0);
		free(localObject);
		free(texcoord);
		//localVertexArray2.set(0, i2, (short[])localObject);
		//localVertexBuffer.setTexCoords(0, localVertexArray2, 0.003921569F, null);
		i7 = paramArrayOfByte[(i1++)] & 0xFF;
	}
	int *localObject2 = NEW_II(int, i3);
	dprintfsi("Scene element index count", i3);
	if (i7 == 245)
	{
		for (i9 = 0; i9 < i3; i9++) {
			localObject2[i9] = class_b__function_a__1byte_2byte(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]);
			//printf("%d ", localObject2[i9]);
		}
		i7 = paramArrayOfByte[(i1++)] & 0xFF;
	}
	m -> index = new_array(nl_unsigned_int, i3, localObject2, 0);
	free(localObject2);
	//printf("i4 = %d\n", i4);
	int *arrayOfInt = NEW_II(int, i4);
	unsigned int *strips = NEW_II(unsigned int, i4);
	dprintfsi("Scene element strips count", i4);
	m -> primitive = i4;
	if (i7 == 246) {
		int i10;
		for (i10 = 0; i10 < i4; i10++) {
			arrayOfInt[i10] = class_b__function_a__1byte_2byte(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]);
			strips[i10] = (unsigned int)arrayOfInt[i10];
			//printf("%d ", arrayOfInt[i10]);
		}
	}
	m -> strip = new_array(nl_unsigned_int, i4, strips, 0);
	free(arrayOfInt);
	free(strips);
	//TriangleStripArray localTriangleStripArray = new TriangleStripArray((int[])localObject, arrayOfInt);
	//paramArrayOfk[paramInt1].d = new Mesh(localVertexBuffer, localTriangleStripArray, null);
	//printf("§§§§§§ %d\n", i5);
	paramArrayOfInt[paramInt1] = i5;
	return i1;
}

float class_b__function_a__1byte_array_2int(const char paramArrayOfByte[], int paramInt)
{
	int i = paramArrayOfByte[paramInt] & 0xFF;
	int j = paramArrayOfByte[(paramInt + 1)] & 0xFF;
	int k = paramArrayOfByte[(paramInt + 2)] & 0xFF;
	int m = paramArrayOfByte[(paramInt + 3)] & 0xFF;
	float f;
	return f = nlIntBitsToFloat(i + (j << 8) + (k << 16) + (m << 24));
}
