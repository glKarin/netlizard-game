#include "studio_gl.h"

//#include <GL/gl.h>

int g_texnum = 0;
int textures[MAXSTUDIOSKINS];

void UploadTexture(mstudiotexture_t *ptexture, const Byte *data, const Byte *pal, int texnum, bool import )
{
	if(!ptexture || !data || !pal)
		return;

	// unsigned *in, int inwidth, int inheight, unsigned *out,  int outwidth, int outheight;
	int		i, j;
	int		row1[256], row2[256], col1[256], col2[256];
	const Byte	*pix1, *pix2, *pix3, *pix4;
	Byte	*tex, *out;

    int outwidth = 1;
	// convert texture to power of 2
    for (; outwidth < ptexture->width; outwidth <<= 1)
		;

	if (outwidth > 256)
		outwidth = 256;

    int outheight = 1;
    for (; outheight < ptexture->height; outheight <<= 1)
		;

	if (outheight > 256)
		outheight = 256;

	tex = out = (Byte *)malloc( outwidth * outheight * 4);

	for (i = 0; i < outwidth; i++)
	{
		col1[i] = (i + 0.25) * (ptexture->width / (float)outwidth);
		col2[i] = (i + 0.75) * (ptexture->width / (float)outwidth);
	}

	for (i = 0; i < outheight; i++)
	{
		row1[i] = (int)((i + 0.25) * (ptexture->height / (float)outheight)) * ptexture->width;
		row2[i] = (int)((i + 0.75) * (ptexture->height / (float)outheight)) * ptexture->width;
	}

	// scale down and convert to 32bit RGB
	for (i=0 ; i<outheight ; i++)
	{
		for (j=0 ; j<outwidth ; j++, out += 4)
		{
			pix1 = &pal[data[row1[i] + col1[j]] * 3];
			pix2 = &pal[data[row1[i] + col2[j]] * 3];
			pix3 = &pal[data[row2[i] + col1[j]] * 3];
			pix4 = &pal[data[row2[i] + col2[j]] * 3];

			out[0] = (pix1[0] + pix2[0] + pix3[0] + pix4[0])>>2;
			out[1] = (pix1[1] + pix2[1] + pix3[1] + pix4[1])>>2;
			out[2] = (pix1[2] + pix2[2] + pix3[2] + pix4[2])>>2;
			if ((out[0]==0) && (out[1]==0) && (out[2]==255))			// Is Pixel Completely Black
				out[3]	=   0;											// Set The Alpha Value To 0
			else															// Otherwise
				out[3]	= 255;
			//out[3] = 0xFF;
		}
	}

	GLuint texid;
	glGenTextures(1, &texid);
	oglBindTexture( GL_TEXTURE_2D, texid );		
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, outwidth, outheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex );
	// CAP glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	// ptexture->width = outwidth;
	// ptexture->height = outheight;
	ptexture->index = texid;

	if(import)
		textures[g_texnum] = texid;
	import?g_texnum:g_texnum++;
	free( tex );
}
