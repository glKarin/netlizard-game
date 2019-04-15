#include "studio_export.h"

bool BMP_ExportTexture(const StudioModel *mdl, const char *Texname, const char *Filename)
{
	if(!mdl || !Texname || !Filename)
		return false;

	Byte			*pColorData;
	Byte			*pBitData;
	const studiohdr_t		*pHdr;
	mstudiotexture_t *pTextures;
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
			return BMP_WriteTexture(pBitData,pColorData,Filename, &pTextures[i]);
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
// Purpose: does the actual saving of the bitmap data
// Additional info: based on iD's WriteBMP(), which is an example of very awefull code. 
bool BMP_WriteTexture(const Byte *pBitData, const Byte *pColorData, const char *sFilename, const mstudiotexture_t *pTexture)
{
	if(!pBitData || !pColorData || !sFilename || !pTexture)
		return false;

	FILE				*fp;
	BITMAPFILEHEADER	bmfh;
	BITMAPINFOHEADER	bmih;
	RGBQUAD				rgbPalette[256];
	ULONG				cbBmpBits;
	BYTE*				pbBmpBits;
	const Byte				*pb, *pbPal = NULL;
	ULONG				cbPalBytes;
	ULONG				biTrueWidth;
	int					i;


	if((fp=fopen(sFilename,"wb"))==NULL)
	{
		// open didn't succeed...
		return false;
	}
	// write data into file. First define all structures, then recalc offsets and sizes in those structures, then
	// write the data to disk..
	// we support only 8 bit, 256color, uncompressed WINDOWS bmp files. OS/2 users should go to IBM and whine.

	// fill file header

	biTrueWidth = ((pTexture->width + 3) & ~3);
	cbBmpBits = biTrueWidth * pTexture->height;
	cbPalBytes = 256 * sizeof( RGBQUAD );

	// Bogus file header check
	bmfh.bfType = MAKEWORD( 'B', 'M' );
	bmfh.bfSize = sizeof bmfh + sizeof bmih + cbBmpBits + cbPalBytes;
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof bmfh + sizeof bmih + cbPalBytes;

	// Write file header
	fwrite(&bmfh, sizeof bmfh, 1, fp);

	// Size of structure
	bmih.biSize = sizeof bmih;
	// Width
	bmih.biWidth = biTrueWidth;
	// Height
	bmih.biHeight = pTexture->height;
	// Only 1 plane 
	bmih.biPlanes = 1;
	// Only 8-bit supported.
	bmih.biBitCount = 8;
	// Only non-compressed supported.
	bmih.biCompression = BI_RGB;
	bmih.biSizeImage = 0;

	// [OTIS] ahahah :) the next comment is done by a valve-programmer :) I let it stay for fun ;)
	// huh?
	bmih.biXPelsPerMeter = 0;
	bmih.biYPelsPerMeter = 0;

	// Always full palette
	bmih.biClrUsed = 256;
	bmih.biClrImportant = 0;
	
	// Write info header
	fwrite(&bmih, sizeof bmih, 1, fp);

	// convert to expanded palette
	pb = pColorData;

	// Copy over used entries
	for (i = 0; i < (int)bmih.biClrUsed; i++)
	{
		rgbPalette[i].rgbRed   = *pb++;
		rgbPalette[i].rgbGreen = *pb++;
		rgbPalette[i].rgbBlue  = *pb++;
        rgbPalette[i].rgbReserved = 0;
	}

	// Write palette (bmih.biClrUsed entries)
	cbPalBytes = bmih.biClrUsed * sizeof( RGBQUAD );
	fwrite(rgbPalette, cbPalBytes, 1, fp);

	pbBmpBits = (Byte *)malloc(cbBmpBits*sizeof(Byte));

	pb = pBitData;
	// reverse the order of the data.
	pb += (pTexture->height - 1) * pTexture->width;
	for(i = 0; i < bmih.biHeight; i++)
	{
		memmove(&pbBmpBits[biTrueWidth * i], pb, pTexture->width);
		pb -= pTexture->width;
	}

	// Write bitmap bits (remainder of file)
	fwrite(pbBmpBits, cbBmpBits, 1, fp);

	free(pbBmpBits);

	// done
	fclose(fp);
	return true;
}

bool SMD_ExportSequence(const StudioModel *mdl, const char *Seqname, const char *filename)
{
	if(!mdl || !Seqname || !filename)
		return false;

	FILE				*smdfile;
	char				smdfilename[_MAX_PATH];
	int					i,j,ii;
	studiohdr_t			*phdr;
	mstudioseqdesc_t	*pseqdesc;
	mstudioanim_t		*panim;
	mstudioseqgroup_t	*pseqgroup;
	
	phdr = (studiohdr_t *)mdl->CoreFile;

	for (i = 0; i < phdr->numseq; i++) 
	{
		pseqdesc = (mstudioseqdesc_t *)((Byte *)phdr + phdr->seqindex + (sizeof(mstudioseqdesc_t) * i));
		pseqgroup = (mstudioseqgroup_t *)((Byte *)phdr + phdr->seqgroupindex) + pseqdesc->seqgroup;

		for (ii = 0; ii < pseqdesc->numblends; ii++) 
		{
			//get anim from sequence files if needed (What is pseqgroup->data?)
			if (pseqdesc->seqgroup == 0)
			{
				panim =  (mstudioanim_t *)((Byte *)phdr + pseqgroup->data + pseqdesc->animindex);
			}
			else
			{
				panim = (mstudioanim_t *)((Byte *)mdl->m_panimhdr[pseqdesc->seqgroup] + pseqdesc->animindex);
			}
			panim += (phdr->numbones * ii); //points panim by current blend
			
			//set filename
/*
			if (pseqdesc->numblends == 1)
			{
				sprintf(smdfilename, "%s%s.smd", DestPath, pseqdesc->label);
			}
			else
			{
				sprintf(smdfilename, "%s%s_blend%i.smd", DestPath, pseqdesc->label, ii+1);
			}
			// open 
*/			
			smdfile = fopen( filename, "w" );
			if (!smdfile)
			{
				fprintf(stderr,"ERROR: Can't write %s\r\n", smdfilename);
				return false;
			}

			fprintf(smdfile,"version 1\n");
			SMD_WriteNodes(mdl, smdfile);
			fprintf(smdfile,"skeleton\n");

			//printf("%s \n", smdfilename);
			//printf("sequence %s seqgroup %i animindex %i frames %i fps %.0f\n", pseqdesc->label, pseqdesc->seqgroup, pseqdesc->animindex, pseqdesc->numframes, pseqdesc->fps);
			//printf("cache %i data %i name %s label %s\n", pseqgroup->cache , pseqgroup->data, pseqgroup->label,pseqgroup->name);
			
			for (j = 0; j < pseqdesc->numframes; j++) 
			{
				SMD_WriteFrame( mdl, smdfile, j, panim, pseqdesc);
			}

			fprintf(smdfile,"end\n");
			fclose(smdfile);
			//printf( "Sequence: %s\n", smdfilename);
		}
	}
	return true;
}

/*
==============================================================

	Half-Life MDL Decompiler
	2002, Kratisto. Based on code from HL SDK

==============================================================
*/
void SMD_WriteFrame(const StudioModel *mdl, FILE *smdfile, int frame, const mstudioanim_t *panim, const mstudioseqdesc_t *pseqdesc)
{
	if(!mdl || !smdfile || !panim || !pseqdesc)
		return;

	int					j,k,kf;
	studiohdr_t			*phdr;
	mstudiobone_t		*pbone;
	mstudioanimvalue_t	*panimvalue;

	vec3_t				pos;
	vec3_t				Eulers;
	vec3_t				angle1, angle2;
	float				s;

	s = 0.0;

	phdr = (studiohdr_t *)mdl->CoreFile;
	pbone = (mstudiobone_t *)((Byte *)phdr + phdr->boneindex);

	fprintf(smdfile,"time %i\n",frame);

	for (k = 0; k < phdr->numbones; k++, pbone++, panim++) 
	{
		// pos loop 
		for (j = 0; j < 3; j++)
		{
			pos[j] = pbone->value[j]; // default;
			if (panim->offset[j] != 0)
			{
				panimvalue = (mstudioanimvalue_t *)((Byte *)panim + panim->offset[j]);
				
				kf = frame;
				// find span of values that includes the frame we want
				while (panimvalue->num.total <= kf)
				{
					kf -= panimvalue->num.total;
					panimvalue += panimvalue->num.valid + 1;
				}
				// if we're inside the span
				if (panimvalue->num.valid > kf)
				{
					// and there's more data in the span
					if (panimvalue->num.valid > kf + 1)
					{
						pos[j] += (panimvalue[kf+1].value * (1.0 - s) + s * panimvalue[kf+2].value)  * pbone->scale[j];
					}
					else
					{
						pos[j] += panimvalue[kf+1].value * pbone->scale[j];
					}
				}
				else
				{
					// are we at the end of the repeating values section and there's another section with data?
					if (panimvalue->num.total <= kf + 1)
					{
						pos[j] += (panimvalue[panimvalue->num.valid].value * (1.0 - s) + s * panimvalue[panimvalue->num.valid + 2].value) * pbone->scale[j];
					}
					else
					{
						pos[j] += panimvalue[panimvalue->num.valid].value  * pbone->scale[j];
					}
				}
			}
		}

		//Eulers loop
		for (j = 0; j < 3; j++)
		{
			if (panim->offset[j+3] == 0)
			{
				angle2[j] = angle1[j] = pbone->value[j+3]; // default;
			}
			else
			{
				panimvalue = (mstudioanimvalue_t *)((Byte *)panim + panim->offset[j+3]);
				kf = frame;
				while (panimvalue->num.total <= kf)
				{
					kf -= panimvalue->num.total;
					panimvalue += panimvalue->num.valid + 1;
				}
				// Bah, missing blend!
				if (panimvalue->num.valid > kf)
				{
					angle1[j] = panimvalue[kf+1].value;

					if (panimvalue->num.valid > kf + 1)
					{
						angle2[j] = panimvalue[kf+2].value;
					}
					else
					{
						if (panimvalue->num.total > kf + 1)
							angle2[j] = angle1[j];
						else
							angle2[j] = panimvalue[panimvalue->num.valid+2].value;
					}
				}
				else
				{
					angle1[j] = panimvalue[panimvalue->num.valid].value;
					if (panimvalue->num.total > kf + 1)
					{
						angle2[j] = angle1[j];
					}
					else
					{
						angle2[j] = panimvalue[panimvalue->num.valid + 2].value;
					}
				}
				angle1[j] = pbone->value[j+3] + angle1[j] * pbone->scale[j+3];
				angle2[j] = pbone->value[j+3] + angle2[j] * pbone->scale[j+3];
			}
		}

		/*

		vec4_t				q, q1, q2;

		if (!VectorCompare( angle1, angle2 ))
		{
			AngleQuaternion( angle1, q1 );
			AngleQuaternion( angle2, q2 );
			QuaternionSlerp( q1, q2, s, q );
		}
		else
		{
			AngleQuaternion( angle1, q );
		}

		Eulers[0] = angle1[0];
		Eulers[1] = angle1[1];
		Eulers[2] = angle1[2];

		*/

		VectorCopy( angle1, Eulers);

		if (pbone->parent == -1)
		{
			vec3_t		temppos;
			
			//restore linear movement for sequences with
			//STUDIO_LX, STUDIO_LY and STUDIO_LZ
			VectorScale( pseqdesc->linearmovement, frame * 1.0 / pseqdesc->numframes, temppos );
			VectorAdd( pos, temppos, pos );

			//studiomdl rotates sequence smds +90 in the z axis,
			//see Grab_Animation in studiomdl.c
			//FIX: find a more elegant way to do this.

			float		zrotation, cz, sz;

			zrotation = -90.0 * (Q_PI / 180.0);
			cz = cos( zrotation );
			sz = sin( zrotation );
			VectorCopy(pos, temppos);

			pos[0] = cz * temppos[0] - sz * temppos[1];
			pos[1] = sz * temppos[0] + cz * temppos[1];
			pos[2] = temppos[2];
			Eulers[2] += zrotation; 

			//clip_rotations(Eulers);

			// This is [void clip_rotations( vec3_t rot )] taken from studiomdl.c :
			// clip everything to : -Q_PI <= x < Q_PI
			int jj;
			for (jj = 0; jj < 3; jj++) {
				while (Eulers[jj] >= Q_PI) 
					Eulers[jj] -= Q_PI*2;
				while (Eulers[jj] < -Q_PI) 
					Eulers[jj] += Q_PI*2;
			}

		} 
		
		fprintf(smdfile,"%3i   " ,k);
		fprintf(smdfile,"%f %f %f %f %f %f\n" ,pos[0],pos[1],pos[2],Eulers[0],Eulers[1],Eulers[2]);
	}
}

void SMD_WriteNodes(const StudioModel *mdl, FILE *smd)
{
	if(!mdl || !smd)
		return;

	int					i;
	studiohdr_t			*phdr;
	mstudiobone_t		*pbone;

	phdr=(studiohdr_t *)mdl->CoreFile;
	//write nodes
	fprintf(smd,"nodes\n");
	for (i = 0; i < phdr->numbones ; i++) 
	{
		pbone = (mstudiobone_t *)((Byte *)phdr + phdr->boneindex + (sizeof(mstudiobone_t) * i));
		fprintf(smd,"%3i \"%s\" %i\n", i , pbone->name , pbone->parent );
	}
	fprintf(smd,"end\n");
}



/*
==============================================================

	Half-Life MDL Decompiler
	2002, Kratisto. Based on code from HL SDK

==============================================================
*/
bool SMD_GenerateReferences(const StudioModel *mdl, int Bodyindex, const char *Refname, const char *Filename)
{
	if(!mdl || !Refname || !Filename)
		return false;

	FILE				*smdfile;
	int					i,k,ii,iii,iiii,jj;
	studiohdr_t			*phdr;
	mstudiobodyparts_t	*pbodyparts;
	mstudiomodel_t		*pmodel;
	mstudiomesh_t		*pmesh;
	mstudiotexture_t	*ptexture;
	mstudiobone_t		*pbone;

	short				*ptris;
	short				*pA = NULL; // -----> mstudiotrivert_t
	short				*pB = NULL; // 
	short				*pC = NULL; // 

	float		bonematrix[3][4];

	vec3_t		BoneEulers;
	vec4_t		q[MAXSTUDIOBONES];


	phdr=(studiohdr_t *)mdl->CoreFile;


	pbone = (mstudiobone_t *)((Byte *)phdr + phdr->boneindex);
	for (jj = 0; jj < phdr->numbones ; jj++) 
	{

		BoneEulers[0] = pbone[jj].value[3];
		BoneEulers[1] = pbone[jj].value[4];
		BoneEulers[2] = pbone[jj].value[5];

		AngleQuaternion(BoneEulers, q[jj] );
		QuaternionMatrix( q[jj], bonematrix );

		bonematrix[0][3] = pbone[jj].value[0];
		bonematrix[1][3] = pbone[jj].value[1];
		bonematrix[2][3] = pbone[jj].value[2];

		//FIX: this takes the assumption that the bones are already sorted by parent number in the mdl,
		if (pbone[jj].parent == -1)
		{
			memcpy(mdl->g_bonetransform[jj], bonematrix, sizeof(float) * 12);
		} 
		else
		{
			R_ConcatTransforms (mdl->g_bonetransform[pbone[jj].parent], bonematrix, mdl->g_bonetransform[jj]);
		}
		//g_bonetransform is ready to be used by SMD_WriteTriangle
	}


	for (i = 0; i < phdr->numbodyparts; i++) 
	{
		pbodyparts = (mstudiobodyparts_t *)((Byte *)phdr + phdr->bodypartindex + (sizeof(mstudiobodyparts_t) * i));
		if ( strcmp(pbodyparts->name, Refname) == 0 )
		{
			pmodel = (mstudiomodel_t *)((Byte *)phdr + pbodyparts->modelindex + (sizeof(mstudiomodel_t) * Bodyindex));
			
			//Write SMD
			smdfile = fopen( Filename, "w" );
			if (!smdfile)
			{
				//LogMessage (MDLDEC_MSG_ERROR , "ERROR: Can't write %s\r\n", smdfilename);
				//printf( "ERROR: Can't write %s\n", smdfilename);
				return false;
			}

			fprintf(smdfile,"version 1\n");

			//Nodes
			SMD_WriteNodes(mdl, smdfile);

			//write default position of the nodes
			fprintf(smdfile,"skeleton\n");
			fprintf(smdfile,"time 0\n");
			for (iiii = 0; iiii < phdr->numbones ; iiii++) 
			{
				pbone = (mstudiobone_t *)((Byte *)phdr + phdr->boneindex + (sizeof(mstudiobone_t) * iiii));
				fprintf(smdfile,"%3i %f %f %f",iiii, pbone->value[0], pbone->value[1], pbone->value[2] );
				fprintf(smdfile," %f %f %f\n", pbone->value[3], pbone->value[4], pbone->value[5] );
			}
			fprintf(smdfile,"end\n");

			//Read and decompress OpenGL triangles
			fprintf(smdfile,"triangles\n");

			for (k = 0; k < pmodel->nummesh ; k++) 
			{

				pmesh = (mstudiomesh_t *)((Byte *)phdr + pmodel->meshindex + (sizeof(mstudiomesh_t) * k));
				//
				if(phdr->numtextures==0){
					phdr=(studiohdr_t *)mdl->TextureFile; // textures are stored in a separated *t.mdl file
				}
				ptexture=(mstudiotexture_t *)((Byte *)phdr + phdr->textureindex + sizeof(mstudiotexture_t) * pmesh->skinref);
				phdr=(studiohdr_t *)mdl->CoreFile; //restore pointer 					
				//
				ptris = (short *)((Byte *)phdr + pmesh->triindex);

				while (ii = *(ptris++))
				{
					
					if (ii < 0)
					{
						//GL_TRIANGLE_FAN :012 023 034 045 056 067 078 089 091
						//inverse GL_TRIANGLE_FAN :021 032 043 054 065 076 087 098 019

						//fprintf(smdfile,"GL_TRIANGLE_FAN : ii %i %s\n",ii,ptexture->name);
						ii = -ii;iii = 0;
						for( ; ii > 0; ii--, ptris += 4, iii++)
						{
							//fprintf(smdfile,"ii %i iii %i vertindex %i normindex %i ",ii,iii,ptris[0],ptris[1]);
							//pA = ptris;
							//SMD_WriteTriangle(smdfile,pmodel,ptexture,pA,pB,pC);
							
							switch( iii ) 
							{
								case 0 : pA = ptris; break;
								case 1 : pC = ptris; break;	
								case 2 :
									pB = ptris; //first triangle of fan
									//fprintf(smdfile,"iii %i ",iii);
									SMD_WriteTriangle(mdl, smdfile,pmodel,ptexture,pA,pB,pC);
									break;
								default:
									pC = pB ; pB = ptris; // pA = no change, pC = pB , pB = new
									//fprintf(smdfile,"iii %i ",iii);
									SMD_WriteTriangle(mdl, smdfile,pmodel,ptexture,pA,pB,pC);
							}
						}
					}
					else
					{
						//GL_TRIANGLE_STRIP : 012 213 234 435 456 
						// 021 123 243 345 465 567 687
						//fprintf(smdfile,"GL_TRIANGLE_STRIP : ii %i %s\n",ii,ptexture->name);
						iii = 0;
						for( ; ii > 0; ii--, ptris += 4, iii++)
						{
							//fprintf(smdfile,"ii %i iii %i vertindex %i normindex %i ",ii,iii,ptris[0],ptris[1]);
							//pA = ptris;
							//SMD_WriteTriangle(smdfile,pmodel,ptexture,pA,pB,pC);
							
							switch( iii ) 
							{
								case 0 : pA = ptris; break;
								case 1 : pC = ptris; break;
								case 2 :
									pB = ptris; //first triangle of strip
									//fprintf(smdfile,"iii %i ",iii);
									SMD_WriteTriangle(mdl, smdfile,pmodel,ptexture,pA,pB,pC);
									break;
								default:
									if ((iii % 2) == 0)
									{
										pA = pB; pB = ptris; // pA = pC, pB = new , pC = no change 
										//fprintf(smdfile,"iii %i ",iii);
										SMD_WriteTriangle(mdl, smdfile,pmodel,ptexture,pA,pB,pC);
									}
									else
									{
										pA = pC; pC = ptris; // pA = pC, pB no change, pC = new
										//fprintf(smdfile,"iii %i ",iii);
										SMD_WriteTriangle(mdl, smdfile,pmodel,ptexture,pA,pB,pC);
									}
							}
						}
					}
				}
			}
			fprintf(smdfile,"end\n");
			//LogMessage (MDLDEC_MSG_INFO , "Reference: %s\r\n", smdfilename);
			//printf( "Reference: %s\n", smdfilename);

			fclose(smdfile);
			return true;
		}
	}
	return false;
}


void SMD_WriteTriangle(const StudioModel *mdl, FILE *smdfile, const mstudiomodel_t *pmodel, const mstudiotexture_t *ptexture, const short *pA, const short *pB, const short *pC)
{
	if(!mdl || !smdfile || !pmodel || !ptexture || !pA || !pB || !pC)
		return;

	float				s,t;
	studiohdr_t			*phdr;
	Byte				*pvertbone;
	Byte				*pnormbone;
	vec3_t				*pverts;
	vec3_t				*pnorms;
	vec3_t				refvertex;
	vec3_t				refnormal;

	phdr = (studiohdr_t *)mdl->CoreFile;
	pverts = (vec3_t *)((Byte *)phdr + pmodel->vertindex);
	pnorms = (vec3_t *)((Byte *)phdr + pmodel->normindex);
	pvertbone = ((Byte *)phdr + pmodel->vertinfoindex);
	pnormbone = ((Byte *)phdr + pmodel->norminfoindex);

	fprintf(smdfile,"%s\n",ptexture->name);

	s = 1.0f/(float)ptexture->width;
	t = 1.0f/(float)ptexture->height;

	//put this in a loop or keep it unrolled?

	VectorTransform (pverts[pA[0]], mdl->g_bonetransform[pvertbone[pA[0]]], refvertex);
	VectorRotate ( pnorms[pA[1]], mdl->g_bonetransform[pvertbone[pA[0]]], refnormal);
	VectorNormalize ( refnormal );
	//fprintf( smdfile, "%3i %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f\n"
	fprintf( smdfile, "%3i %f %f %f %f %f %f %f %f\n"
			,pvertbone[pA[0]]
			,refvertex[0], refvertex[1], refvertex[2]
			,refnormal[0], refnormal[1], refnormal[2]
			,pA[2]*s, 1-(pA[3]*t));

	VectorTransform( pverts[pB[0]], mdl->g_bonetransform[pvertbone[pB[0]]], refvertex);
	VectorRotate( pnorms[pB[1]], mdl->g_bonetransform[pvertbone[pB[0]]], refnormal);
	VectorNormalize( refnormal );
	//fprintf( smdfile, "%3i %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f\n"
	fprintf( smdfile, "%3i %f %f %f %f %f %f %f %f\n"
			,pvertbone[pB[0]]
			,refvertex[0], refvertex[1], refvertex[2]
			,refnormal[0], refnormal[1], refnormal[2]
			,pB[2]*s, 1-(pB[3]*t));

	VectorTransform( pverts[pC[0]], mdl->g_bonetransform[pvertbone[pC[0]]], refvertex);
	VectorRotate( pnorms[pC[1]], mdl->g_bonetransform[pvertbone[pC[0]]], refnormal);
	VectorNormalize( refnormal );
	//fprintf( smdfile, "%3i %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f\n"
	fprintf( smdfile, "%3i %f %f %f %f %f %f %f %f\n"
			,pvertbone[pC[0]]
			,refvertex[0], refvertex[1], refvertex[2]
			,refnormal[0], refnormal[1], refnormal[2]
			,pC[2]*s, 1-(pC[3]*t));
}

