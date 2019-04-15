#include "studio_import.h"

#include "studio_gl.h"

bool BMP_ImportTexture(const StudioModel *mdl, const char *Texname, const char *Filename)
{
	if(!mdl || !Texname || !Filename)
		return false;

	Byte			*pColorData;
	Byte			*pBitData;
	studiohdr_t		*pHdr;
	mstudiotexture_t *pTextures;
	bool			bResult;
	int i;

	pHdr=(studiohdr_t *)mdl->CoreFile;

	if(pHdr->numtextures==0)
	{
		pHdr=(studiohdr_t *)mdl->TextureFile; // textures are stored in a separated t.mdl/dol file
	}

	for ( i = 0; i < pHdr->numtextures; i++ )
	{
		pTextures=(mstudiotexture_t *)((Byte *)pHdr + pHdr->textureindex);
		if ( strcmp(pTextures[i].name, Texname) == 0 )
		{
			pBitData=(Byte *)pHdr + mdl->pSavedTIndexes[i];
			pColorData=(Byte *)pHdr + pTextures[i].width * pTextures[i].height + mdl->pSavedTIndexes[i];
			bResult = BMP_ReadTexture(pBitData,pColorData,Filename, &pTextures[i]);
			if(bResult)
			{
				Byte				*pin;
				studiohdr_t			*phdr;

				pin = (Byte *)mdl->CoreFile;
				phdr = (studiohdr_t *)pin;
				UploadTexture( &pTextures[i], pBitData, pColorData, i, true );
				return true;
			}
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////
// Code by Otis is (c)1999 Solutions Design, http://www.sd.nl
// Code by Ascent is (c)1999 Greg Dunn.
// Code by Dark Yoda is (c)1999 Volker Sch鰊efeld.
// All rights reserved.
////////////////////////////////////////////////////////////////////
// Purpose: does the actual loading of the bitmap data
// Additional info: based on iD's LoadBMP(), which is an example of very awefull code. 
bool BMP_ReadTexture(Byte *pBitData, Byte *pColorData, const char *sFilename, const mstudiotexture_t *pTexture)
{
	if(!pBitData || !pColorData || !sFilename || !pTexture)
		return false;

	int					i;
	FILE				*fp;
	BITMAPFILEHEADER	bmfh;
	BITMAPINFOHEADER	bmih;
	RGBQUAD				rgbPalette[256];
	ULONG				cbBmpBits;
	Byte				*pb, *pbPal = NULL;
	ULONG				cbPalBytes;
	ULONG				biTrueWidth;

	// File exists?
	if ((fp = fopen(sFilename, "rb")) == NULL)
	{
		// open didn't succeed
		//AfxMessageBox("Load failed. Could not open file.",MB_OK);
		return false;
	}
	
	// Read file header
	fread(&bmfh, sizeof bmfh, 1, fp);

	// Bogus file header check
	if (!(bmfh.bfReserved1 == 0 && bmfh.bfReserved2 == 0))
	{
		fclose(fp);
		//AfxMessageBox("Invalid BMP file.",MB_OK);
		return false;
	}

	// Read info header
	fread(&bmih, sizeof bmih, 1, fp);

	// Bogus info header check
	if (!(bmih.biSize == sizeof bmih && bmih.biPlanes == 1))
	{
		fclose(fp);
		//AfxMessageBox("Invalid BMP file.",MB_OK);
		return false;
	}

	// Bogus bit depth?  Only 8-bit supported.
	if (bmih.biBitCount != 8)
	{
		fclose(fp);
		//AfxMessageBox("Invalid BMP file. Only 8bit (256colors) bmp files supported.",MB_OK);
		return false;
	}
	
	// Bogus compression?  Only non-compressed supported.
	if (bmih.biCompression != BI_RGB)
	{
		fclose(fp);
		//AfxMessageBox("Invalid BMP file. This file is compressed. Only UNCOMPRESSED BMP files supported.",MB_OK);
		return false;
	}

	biTrueWidth = (bmih.biWidth + 3) & ~3;

	// test size. We cannot crop, because the texture has to fit exactly. If the user wants to load a smaller image,
	// the user has to stick that smaller image on a large image. It won't scale anyway.
	if((pTexture->width!=(int)biTrueWidth)||(pTexture->height!=bmih.biHeight))
	{
		// too large.
		fclose(fp);
		//sError.Format("Invalid BMP file. The bitmap is not of the right size.\nWidth should be %i and height should be %i.\nTextures won't scale anyway, so it's of no use to load smaller or larger pictures", pTexture->width, pTexture->height);
		//AfxMessageBox(sError,MB_OK);
		return false;
	}

	// Figure out how many entries are actually in the table
	if (bmih.biClrUsed == 0)
	{
		bmih.biClrUsed = 256;
		cbPalBytes = (1 << bmih.biBitCount) * sizeof( RGBQUAD );
	}
	else 
	{
		cbPalBytes = bmih.biClrUsed * sizeof( RGBQUAD );
	}

	// Read palette (bmih.biClrUsed entries)
	fread(rgbPalette, cbPalBytes, 1,fp);

	// convert to a packed 768 Byte palette
	pbPal = pColorData;

	// Copy over used entries
	for (i = 0; i < (int)bmih.biClrUsed; i++)
	{
		*pbPal++ = rgbPalette[i].rgbRed;
		*pbPal++ = rgbPalette[i].rgbGreen;
		*pbPal++ = rgbPalette[i].rgbBlue;
	}

	// Fill in unused entires will 0,0,0
	for (i = bmih.biClrUsed; i < 256; i++) 
	{
		*pbPal++ = (Byte)0;
		*pbPal++ = (Byte)0;
		*pbPal++ = (Byte)0;
	}

	// Read bitmap bits (remainder of file)
	cbBmpBits = bmfh.bfSize - ftell(fp);
	pb = (Byte *)malloc(cbBmpBits * sizeof(Byte));

	// load bitmapdata
	fread(pb, cbBmpBits, 1,fp);

	// reverse the order of the data.
	pb += (bmih.biHeight - 1) * biTrueWidth;
	for(i = 0; i < bmih.biHeight; i++)
	{
		memmove(&pBitData[biTrueWidth * i], pb, biTrueWidth);
		pb -= biTrueWidth;
	}
	pb += biTrueWidth;
	free(pb);
	fclose(fp);
	return true;
}

