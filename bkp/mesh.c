#include "mesh.h"
#include "file_io.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const char b[] = { 78, 76, 95, 77, 69, 83, 72 }; // NL_MESH
static const size_t b_length = 7;

NL_Mesh mesh;

void a_ReadMeshFile(const char *paramString)
{
	char *arrayOfByte = ReadFile(paramString, NULL);
	int i1;
	for(i1 = 0; i1 < b_length; i1++)
	{
		if(arrayOfByte[i1] != b[i1]) {
			free(arrayOfByte);
			return;
		}
	}
	int i2 = b_length;
	/*return*/ a_ParseFile(arrayOfByte, i2);
}

void a_ParseFile(char paramArrayOfByte[], int paramInt)
{
	int i1 = paramInt; // 7
	int i2 = 0;
	int i3 = paramArrayOfByte[(i1++)];
	printf("i1 = %d\n", i1);
	printf("i3 = %d\n", i3);
	int i4;
	//k[] arrayOfk = new k[i4 = b_a(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)])];
	i4 = b_a(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]);
	printf("i4 = %d\n", i4);
	//Appearance[] arrayOfAppearance = new Appearance[i3];
	int *arrayOfInt = malloc(sizeof(int) * i4);
	//t = new String[i3];
	//s = new Texture2D[i3];
	//r = 0;
	int i5 = 0;
	int i7;
	int i6;
	for (i6 = 0; i6 < i3; i6++) {
		if ((i2 = paramArrayOfByte[(i1++)] & 0xFF) == 225) {
			i1 = a_Appearance(i5++, paramArrayOfByte, i1);
			printf("aaaaai1 = %d\n", i1);
		}
	}
	i5 = 0;
	mesh.mesh_count = i4;
	mesh.meshes = malloc(sizeof(Mesh) * i4);
	memset(mesh.meshes, 0, sizeof(Mesh) * i4);
	for (i7 = 0; i7 < i4; i7++) {
		if ((i2 = paramArrayOfByte[(i1++)] & 0xFF) == 241) {
			i1 = a_k(&(mesh.meshes[i7]), arrayOfInt, i5++, paramArrayOfByte, i1);
		}
	}
	/*
		 for (int i6 = 0; i6 < i4; i6++) {
		 if ((i7 = arrayOfInt[i6]) < 127)
		 {
		 arrayOfk[i6].e = arrayOfAppearance[i7];
		 int i8;
		 if (((i8 = arrayOfAppearance[i7].getUserID()) & 0x4) != 0) {
		 arrayOfk[i6].a = true;
		 }
		 }
		 }
		 return arrayOfk;
		 */
	free(arrayOfInt);
}

int a_Appearance(int paramInt1, char paramArrayOfByte[], int paramInt2)
{
	int i1 = paramInt2;
	//Appearance localAppearance = new Appearance();
	//new Material();
	i1 += 13;
	int i2 = b_c(paramArrayOfByte, i1);
	i1 += 4;
	short *arrayOfChar = NULL; // java char type
	int i3;
	//Object localObject;
	if ((i3 = paramArrayOfByte[(i1++)] & 0xFF) > 0)
	{
		short localObject[32]; // java char type
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
			localObject[(i4++)] = ((short)i5); // java char type
		}
		arrayOfChar = malloc(sizeof(short) * i4); // java char type
		memcpy(localObject, arrayOfChar, sizeof(short) * i4);
		//System.arraycopy(localObject, 0, arrayOfChar, 0, i4);
		int i;
		printf("a i4 = %d\n", i4);
		for(i = 0; i < i4; i++)
			printf("%d : %d %d %d\n", localObject[i], 'm', 'a', 'p');
		printf("\n");
	}
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
	free(arrayOfChar);
	return i1;
}

int a_k(Mesh *m, int paramArrayOfInt[], int paramInt1, char paramArrayOfByte[], int paramInt2)
{
	int i1 = paramInt2;
	int i2 = b_a(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]);
	i1++;
	i1++;
	int i3 = b_a(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]);
	int i4 = b_a(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]);
	int i5 = paramArrayOfByte[(i1++)] & 0xFF;
	int i6;
	float arrayOfFloat[3];
	for (i6 = 0; i6 < 3; i6++)
	{
		arrayOfFloat[i6] = b_a_2(paramArrayOfByte, i1);
		i1 += 4;
	}
	float f1 = b_a_2(paramArrayOfByte, i1);
	i1 += 4;
	//paramArrayOfk[paramInt1] = new k();
	//paramArrayOfk[paramInt1].h = b.a(paramArrayOfByte, i1);
	float k_h = b_a_2(paramArrayOfByte, i1);
	i1 += 4;
	b_a_2(paramArrayOfByte, i1);
	i1 += 4;
	//paramArrayOfk[paramInt1].i = b.a(paramArrayOfByte, i1);
	float k_i = b_a_2(paramArrayOfByte, i1);
	i1 += 4;
	//paramArrayOfk[paramInt1].f = b.a(paramArrayOfByte, i1);
	float k_f = b_a_2(paramArrayOfByte, i1);
	i1 += 4;
	//paramArrayOfk[paramInt1].b = ((int)(paramArrayOfk[paramInt1].h * 4095.0F));
	//paramArrayOfk[paramInt1].c = ((int)(paramArrayOfk[paramInt1].h * 4095.0F));
	int k_b = ((int)(k_h * 4095.0F));
	int k_c = ((int)(k_h * 4095.0F));
	printf("(%f, %f, %f) %d\n", k_h, k_i, k_f, k_b);
	//VertexBuffer localVertexBuffer = new VertexBuffer();
	float f2 = 3.051851E-5F * f1;
	m -> translate.x = k_h;
	m -> translate.y = k_i;
	m -> translate.z = k_f;
	int i7 = paramArrayOfByte[(i1++)] & 0xFF;
	int i8 = 0;
	int i9;
	short *localObject = NULL;
	printf("i7 = %d ? 242\n", i7);
	if (i7 == 242)
	{
		printf("i2 = %d\n", i2);
		//VertexArray localVertexArray1 = new VertexArray(i2, 3, 2);
		localObject = malloc(sizeof(short) * i2 * 3);
		memset(localObject, 0, sizeof(short) * i2 * 3);
		GLfloat *vertex = malloc(sizeof(GLfloat) * i2 * 3);
		memset(vertex, 0, sizeof(GLfloat) * i2 * 3);
		for (i9 = 0; i9 < i2 * 3; i9++)
		{
			i8 = b_a(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]) - 32767;
			localObject[i9] = ((short)i8);
			/*
			if(i9 % 3 == 0)
				printf(" | ");
			printf("%f ", f2 * (float)i8);
			*/
			vertex[i9] = f2 * (float)i8;
		}
		//printf("<%f %f %f>\n", vertex[0], vertex[1], vertex[2]);
		m -> buffers[VertexBuffer] = GLNewBuffer(GL_ARRAY_BUFFER, sizeof(GLfloat) * i2 * 3, vertex, GL_STATIC_DRAW);
		free(localObject);
		free(vertex);
		printf("f2 = %f\n", f2);
		//localVertexArray1.set(0, i2, (short[])localObject);
		//localVertexBuffer.setPositions(localVertexArray1, f2, arrayOfFloat);
		i7 = paramArrayOfByte[(i1++)] & 0xFF;
	}
	printf("i7 = %d ? 244\n", i7);
	if (i7 == 244)
	{
		//VertexArray localVertexArray2 = new VertexArray(i2, 2, 2);
		printf("i2 = %d\n", i2);
		localObject = malloc(sizeof(short) * i2 * 2);
		memset(localObject, 0, sizeof(short) * i2 * 2);
		GLfloat *texcoord = malloc(sizeof(GLfloat) * i2 * 2);
		memset(texcoord, 0, sizeof(GLfloat) * i2 * 2);
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
		m -> buffers[TexcoordBuffer] = GLNewBuffer(GL_ARRAY_BUFFER, sizeof(GLfloat) * i2 * 2, texcoord, GL_STATIC_DRAW);
		free(localObject);
		free(texcoord);
		//localVertexArray2.set(0, i2, (short[])localObject);
		//localVertexBuffer.setTexCoords(0, localVertexArray2, 0.003921569F, null);
		i7 = paramArrayOfByte[(i1++)] & 0xFF;
	}
	int *localObject2 = malloc(sizeof(int) * i3);
	memset(localObject2, 0, sizeof(int) * i3);
	printf("i3 = %d\n", i3);
	printf("i7 = %d ? 245\n", i7);
	if (i7 == 245)
	{
		for (i9 = 0; i9 < i3; i9++) {
			localObject2[i9] = b_a(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]);
			//printf("%d ", localObject2[i9]);
		}
		i7 = paramArrayOfByte[(i1++)] & 0xFF;
	}
	m -> buffers[IndexBuffer] = GLNewBuffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * i3, localObject2, GL_STATIC_DRAW);
	free(localObject2);
	printf("i4 = %d\n", i4);
	int *arrayOfInt = malloc(sizeof(int) * i4);
	memset(arrayOfInt, 0, sizeof(int) * i4);
	m -> strips = malloc(sizeof(GLuint) * i4);
	memset(m -> strips, 0, sizeof(GLuint) * i4);
	printf("i7 = %d ? 246, i4 = %d\n", i7, i4);
	m -> primitive = i4;
	if (i7 == 246) {
		int i10;
		for (i10 = 0; i10 < i4; i10++) {
			arrayOfInt[i10] = b_a(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]);
			m -> strips[i10] = (GLuint)arrayOfInt[i10];
			//printf("%d ", arrayOfInt[i10]);
		}
	}
	printf("\n-----------\n");
	free(arrayOfInt);
	//TriangleStripArray localTriangleStripArray = new TriangleStripArray((int[])localObject, arrayOfInt);
	//paramArrayOfk[paramInt1].d = new Mesh(localVertexBuffer, localTriangleStripArray, null);
	paramArrayOfInt[paramInt1] = i5;
	return i1;
}


