#include "studio_model.h"

//#include <GL/gl.h>

#include "studio_gl.h"

void FreeModel (StudioModel *mdl)
{
	if(!mdl)
		return;

	int i;
	studiohdr_t			*phdr;

	if (mdl->pSavedTIndexes)
	{
		if(mdl->CoreFile)
		{
			phdr = (studiohdr_t *)((Byte *)mdl->CoreFile);
			glDeleteTextures(phdr->numtextures, mdl->pSavedTIndexes);
		};

		free(mdl->pSavedTIndexes);
	}

	if (mdl->m_pstudiohdr)
		free (mdl->m_pstudiohdr);

	if (mdl->m_ptexturehdr && mdl->m_owntexmodel)
		free (mdl->m_ptexturehdr);

	mdl->m_pstudiohdr = mdl->m_ptexturehdr = 0;
	mdl->m_owntexmodel = false;

	for (i = 0; i < 32; i++)
	{
		if (mdl->m_panimhdr[i])
		{
			free (mdl->m_panimhdr[i]);
			mdl->m_panimhdr[i] = 0;
		}
	}

	// deleting textures
	glDeleteTextures (g_texnum, (const GLuint *) textures);

	g_texnum = 0;

	//printf("[StudioModel]: Free\n");
}

bool LoadModel( StudioModel *mdl, const char *modelname )
{
	if(!mdl || !modelname)
		return false;

	FILE *fp;

	// load the model
	if( (fp = fopen( modelname, "rb" )) == NULL)
	{
		fprintf(stderr, "unable to open %s\n", modelname );
		return false;
		//exit(1);
	}

	fseek( fp, 0, SEEK_END );
	mdl->CoreFileLength = ftell( fp );
	fseek( fp, 0, SEEK_SET );
	mdl->CoreFile = (Byte *)malloc( mdl->CoreFileLength );
	fread( mdl->CoreFile, mdl->CoreFileLength, 1, fp );

	int					i;
	Byte				*pin;
	studiohdr_t			*phdr;
	mstudiotexture_t	*ptexture;

	pin = (Byte *)mdl->CoreFile;
	phdr = (studiohdr_t *)pin;

	ptexture = (mstudiotexture_t *)(pin + phdr->textureindex);
	if (phdr->textureindex > 0)
	{
		mdl->pSavedTIndexes=(int *)malloc(phdr->numtextures * sizeof(int));
		if ( mdl->pSavedTIndexes )
		{
			for (i = 0; i < phdr->numtextures; i++)
			{
				// strcpy( name, mod->name );
				// strcpy( name, ptexture[i].name );
				mdl->pSavedTIndexes[i]=ptexture[i].index;
				UploadTexture( &ptexture[i], pin + ptexture[i].index, pin + ptexture[i].width * ptexture[i].height + ptexture[i].index, i, false );
				mdl->pSavedTIndexes[i]=ptexture[i].index;
			}
		}
		else
		{
			fprintf(stderr, "error on openening %s\n", modelname );
			return false;
		}
	}

	// UNDONE: free texture memory

	fclose( fp );

	//printf("[StudioModel]: Load\n");
	return true;
}

bool SaveModel( const StudioModel *mdl, const char *modelname )
{
	if(!mdl || !modelname)
		return false;

	FILE				*fp;
	int					i;
	studiohdr_t			*pHdr;
	studiohdr_t			*pTmpHdr;
	Byte				*pTmpFile;
	mstudiotexture_t	*pTextures;

	// load the model
	if( (fp = fopen( modelname, "wb" )) == NULL)
	{
		fprintf(stderr, "unable to save %s\n", modelname );
		return false;
	}

	pHdr=(studiohdr_t *)mdl->CoreFile;
	if(pHdr->numtextures!=0)
	{
		// there are textures in this datablock. copy filedata to tempbuffer, reset texture
		// indices and save that block
		pTmpFile=(Byte *)malloc(mdl->CoreFileLength);
		// copy data...
		for(i=0;i<mdl->CoreFileLength;i++)
		{
			pTmpFile[i]=mdl->CoreFile[i];
		}
		// reset indices.
		pTmpHdr=(studiohdr_t *)pTmpFile;
		pTextures=(mstudiotexture_t *)((Byte *)pTmpHdr + pTmpHdr->textureindex);
		for(i=0;i<pHdr->numtextures;i++)
		{
			pTextures[i].index=mdl->pSavedTIndexes[i];
		}
		// save this block
		fwrite(pTmpFile,mdl->CoreFileLength,1,fp);
		// free mem
		free(pTmpFile);
		fclose(fp);
	}
	else
	{
		// No textures here: save the corefile data...
		fwrite(mdl->CoreFile,mdl->CoreFileLength,1,fp);
		// done
		fclose(fp);
	}

	fclose( fp );

	return true;
}

bool LoadTextures( StudioModel *mdl, const char *modelname )
{
	if(!mdl || !modelname)
		return false;

	FILE *fp;

	// load the model
	if( (fp = fopen( modelname, "rb" )) == NULL)
	{
		fprintf(stderr, "unable to open %s\n", modelname );
		return false;
	}

	fseek( fp, 0, SEEK_END );
	mdl->TextureFileLength = ftell( fp );
	fseek( fp, 0, SEEK_SET );
	mdl->TextureFile = (Byte *)malloc( mdl->TextureFileLength );
	fread( mdl->TextureFile, mdl->TextureFileLength, 1, fp );

	int					i;
	Byte				*pin;
	studiohdr_t			*phdr;
	mstudiotexture_t	*ptexture;

	pin = (Byte *)mdl->TextureFile;
	phdr = (studiohdr_t *)pin;

	ptexture = (mstudiotexture_t *)(pin + phdr->textureindex);
	if (phdr->textureindex != 0)
	{
		for (i = 0; i < phdr->numtextures; i++)
		{
			// strcpy( name, mod->name );
			// strcpy( name, ptexture[i].name );
			UploadTexture( &ptexture[i], pin + ptexture[i].index, pin + ptexture[i].width * ptexture[i].height + ptexture[i].index, i, false );
				// ??? mdl->pSavedTIndexes[i]=ptexture[i].index;
		}
	}

	// UNDONE: free texture memory

	fclose( fp );

	return true;
}


bool LoadDemandSequence( StudioModel *mdl, const char *modelname, int index )
{
	if(!mdl || !modelname)
		return false;

	FILE *fp;

	// load the model
	if( (fp = fopen( modelname, "rb" )) == NULL)
	{
		fprintf( stderr, "unable to open %s\n", modelname );
		return false;
	}

	fseek( fp, 0, SEEK_END );
	mdl->SequenceFilesLength[index] = ftell( fp );
	fseek( fp, 0, SEEK_SET );
	mdl->SequenceFiles[index] = (Byte *)malloc( mdl->SequenceFilesLength[index] );
	fread( mdl->SequenceFiles[index], mdl->SequenceFilesLength[index], 1, fp );

	fclose( fp );

	return true;
}

bool Init( StudioModel *mdl, const char *modelname )
{ 
	if(!mdl || !modelname)
		return false;

	int i;

	if ( LoadModel( mdl, modelname ) )
		mdl->m_pstudiohdr = (studiohdr_t *)mdl->CoreFile;

	// test for the IDST tag...
	if(memcmp(mdl->CoreFile,"IDST",4)!=0)
	{
		free(mdl->CoreFile);
		mdl->CoreFileLength=0;

		fprintf( stderr, "ERROR: %s isn't is a valid HL model file.", modelname);
		return false;
	}

	if ( !mdl->m_pstudiohdr )
	{
		fprintf( stderr, "ERROR: Couldn't open the Model right.\n" );
		return false;
	}
	// preload textures
	if (mdl->m_pstudiohdr->numtextures == 0)
	{
		char texturename[256];

		strcpy( texturename, modelname );
		strcpy( &texturename[strlen(texturename) - 4], "T.mdl" );

		if(LoadModel( mdl, texturename ))
			mdl->m_ptexturehdr = (studiohdr_t *)mdl->CoreFile;
		if ( !mdl->m_ptexturehdr )
		{
			fprintf( stderr, "ERROR: Couldn't open the Textures right.\n" );
			return false;
		}
	}
	else
	{
		mdl->m_ptexturehdr = mdl->m_pstudiohdr;
	}

	// preload animations
	if (mdl->m_pstudiohdr->numseqgroups > 1)
	{
		for (i = 1; i < mdl->m_pstudiohdr->numseqgroups; i++)
		{
			char seqgroupname[256];

			strcpy( seqgroupname, modelname );
			sprintf( &seqgroupname[strlen(seqgroupname) - 4], "%02d.mdl", i );

			if(LoadDemandSequence( mdl, seqgroupname, i ))
				mdl->m_panimhdr[i] = (studioseqhdr_t *)mdl->SequenceFiles[i];
			if ( !mdl->m_panimhdr[i] )
			{
				fprintf( stderr, "ERROR: Couldn't open the Sequences right.\n" );
				return false;
			}
		}
	}
	//printf("[StudioModel]: Init\n");
	return true;
}
////////////////////////////////////////////////////////////////////////

mstudioseqdesc_t * GetSequence( StudioModel *mdl, const char *name, int *index )
{
	if(!mdl || !name)
		return NULL;

	int i;

	mstudioseqdesc_t *pseqdescs = (mstudioseqdesc_t *) ((Byte *) mdl->m_pstudiohdr + mdl->m_pstudiohdr->seqindex);
	for ( i = 0; i < mdl->m_pstudiohdr->numseq; i++ )
	{
		if ( strcmp(pseqdescs[i].label, name) == 0 )
		{
			if(index)
				*index = i;
			return &pseqdescs[i];
		}
	}
	return NULL;
}

mstudioevent_t * GetEvent( StudioModel *mdl, const char *seqname )
{
	if(!mdl || !seqname)
		return NULL;

	int i;

	mstudioseqdesc_t *pseqdescs = (mstudioseqdesc_t *) ((Byte *) mdl->m_pstudiohdr + mdl->m_pstudiohdr->seqindex);
	for ( i = 0; i < mdl->m_pstudiohdr->numseq; i++ )
	{
		if ( strcmp(pseqdescs[i].label, seqname) == 0 )
		{
			return(mstudioevent_t *)((Byte *)mdl->m_pstudiohdr + pseqdescs[i].eventindex);
		}
	}
	return NULL;
}

int SetSequence( StudioModel *mdl, int iSequence )
{
	if(!mdl)
		return 0;

	if (iSequence > mdl->m_pstudiohdr->numseq)
		iSequence = 0;
	if (iSequence < 0)
		iSequence = mdl->m_pstudiohdr->numseq-1;

	mdl->m_sequence = iSequence;
	mdl->m_frame = 0;

	return mdl->m_sequence;
}

void ExtractBbox( const StudioModel *mdl, float *mins, float *maxs )
{
	if(!mdl || !mins || !maxs)
		return;

	mstudioseqdesc_t	*pseqdesc;

	pseqdesc = (mstudioseqdesc_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pstudiohdr->seqindex);
	
	mins[0] = pseqdesc[ mdl->m_sequence ].bbmin[0];
	mins[1] = pseqdesc[ mdl->m_sequence ].bbmin[1];
	mins[2] = pseqdesc[ mdl->m_sequence ].bbmin[2];

	maxs[0] = pseqdesc[ mdl->m_sequence ].bbmax[0];
	maxs[1] = pseqdesc[ mdl->m_sequence ].bbmax[1];
	maxs[2] = pseqdesc[ mdl->m_sequence ].bbmax[2];
}



void GetSequenceInfo( const StudioModel *mdl, float *pflFrameRate, float *pflGroundSpeed )
{
	if(!mdl || !pflFrameRate || !pflGroundSpeed)
		return;

	mstudioseqdesc_t	*pseqdesc;

	pseqdesc = (mstudioseqdesc_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pstudiohdr->seqindex) + (int)mdl->m_sequence;

	if (pseqdesc->numframes > 1)
	{
		*pflFrameRate = 256 * pseqdesc->fps / (pseqdesc->numframes - 1);
		*pflGroundSpeed = sqrt( pseqdesc->linearmovement[0]*pseqdesc->linearmovement[0]+ pseqdesc->linearmovement[1]*pseqdesc->linearmovement[1]+ pseqdesc->linearmovement[2]*pseqdesc->linearmovement[2] );
		*pflGroundSpeed = *pflGroundSpeed * pseqdesc->fps / (pseqdesc->numframes - 1);
	}
	else
	{
		*pflFrameRate = 256.0;
		*pflGroundSpeed = 0.0;
	}
}


float SetController( StudioModel *mdl, int iController, float flValue )
{
	if(!mdl)
		return 0.0;

	mstudiobonecontroller_t	*pbonecontroller = (mstudiobonecontroller_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pstudiohdr->bonecontrollerindex);

    int i = 0;
	// find first controller that matches the index
    for (; i < mdl->m_pstudiohdr->numbonecontrollers; i++, pbonecontroller++)
	{
		if (pbonecontroller->index == iController)
			break;
	}
	if (i >= mdl->m_pstudiohdr->numbonecontrollers)
		return flValue;

	// wrap 0..360 if it's a rotational controller
	if (pbonecontroller->type & (STUDIO_XR | STUDIO_YR | STUDIO_ZR))
	{
		// ugly hack, invert value if end < start
		if (pbonecontroller->end < pbonecontroller->start)
			flValue = -flValue;

		// does the controller not wrap?
		if (pbonecontroller->start + 359.0 >= pbonecontroller->end)
		{
			if (flValue > ((pbonecontroller->start + pbonecontroller->end) / 2.0) + 180)
				flValue = flValue - 360;
			if (flValue < ((pbonecontroller->start + pbonecontroller->end) / 2.0) - 180)
				flValue = flValue + 360;
		}
		else
		{
			if (flValue > 360)
				flValue = flValue - (int)(flValue / 360.0) * 360.0;
			else if (flValue < 0)
				flValue = flValue + (int)((flValue / -360.0) + 1) * 360.0;
		}
	}

	int setting = 255 * (flValue - pbonecontroller->start) / (pbonecontroller->end - pbonecontroller->start);

	if (setting < 0) setting = 0;
	if (setting > 255) setting = 255;
	mdl->m_controller[iController] = setting;

	return setting * (1.0 / 255.0) * (pbonecontroller->end - pbonecontroller->start) + pbonecontroller->start;
}


float SetMouth( StudioModel *mdl, float flValue )
{
	if(!mdl)
		return 0.0;

	int i;

	mstudiobonecontroller_t	*pbonecontroller = (mstudiobonecontroller_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pstudiohdr->bonecontrollerindex);

	// find first controller that matches the mouth
	for (i = 0; i < mdl->m_pstudiohdr->numbonecontrollers; i++, pbonecontroller++)
	{
		if (pbonecontroller->index == 4)
			break;
	}

	// wrap 0..360 if it's a rotational controller
	if (pbonecontroller->type & (STUDIO_XR | STUDIO_YR | STUDIO_ZR))
	{
		// ugly hack, invert value if end < start
		if (pbonecontroller->end < pbonecontroller->start)
			flValue = -flValue;

		// does the controller not wrap?
		if (pbonecontroller->start + 359.0 >= pbonecontroller->end)
		{
			if (flValue > ((pbonecontroller->start + pbonecontroller->end) / 2.0) + 180)
				flValue = flValue - 360;
			if (flValue < ((pbonecontroller->start + pbonecontroller->end) / 2.0) - 180)
				flValue = flValue + 360;
		}
		else
		{
			if (flValue > 360)
				flValue = flValue - (int)(flValue / 360.0) * 360.0;
			else if (flValue < 0)
				flValue = flValue + (int)((flValue / -360.0) + 1) * 360.0;
		}
	}

	int setting = 0;
	if ( ( pbonecontroller->end - pbonecontroller->start ) != 0 )
		setting = 64 * (flValue - pbonecontroller->start) / (pbonecontroller->end - pbonecontroller->start);

	if (setting < 0) setting = 0;
	if (setting > 64) setting = 64;
	mdl->m_mouth = setting;

	return setting * (1.0 / 64.0) * (pbonecontroller->end - pbonecontroller->start) + pbonecontroller->start;
}


float SetBlending( StudioModel *mdl, int iBlender, float flValue )
{
	if(!mdl)
		return 0.0;

	mstudioseqdesc_t	*pseqdesc;

	pseqdesc = (mstudioseqdesc_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pstudiohdr->seqindex) + (int)mdl->m_sequence;

	if (pseqdesc->blendtype[iBlender] == 0)
		return flValue;

	if (pseqdesc->blendtype[iBlender] & (STUDIO_XR | STUDIO_YR | STUDIO_ZR))
	{
		// ugly hack, invert value if end < start
		if (pseqdesc->blendend[iBlender] < pseqdesc->blendstart[iBlender])
			flValue = -flValue;

		// does the controller not wrap?
		if (pseqdesc->blendstart[iBlender] + 359.0 >= pseqdesc->blendend[iBlender])
		{
			if (flValue > ((pseqdesc->blendstart[iBlender] + pseqdesc->blendend[iBlender]) / 2.0) + 180)
				flValue = flValue - 360;
			if (flValue < ((pseqdesc->blendstart[iBlender] + pseqdesc->blendend[iBlender]) / 2.0) - 180)
				flValue = flValue + 360;
		}
	}

	int setting = 255 * (flValue - pseqdesc->blendstart[iBlender]) / (pseqdesc->blendend[iBlender] - pseqdesc->blendstart[iBlender]);

	if (setting < 0) setting = 0;
	if (setting > 255) setting = 255;

	mdl->m_blending[iBlender] = setting;

	return setting * (1.0 / 255.0) * (pseqdesc->blendend[iBlender] - pseqdesc->blendstart[iBlender]) + pseqdesc->blendstart[iBlender];
}



int SetBodygroup( StudioModel *mdl, int iGroup, int iValue )
{
	if(!mdl)
		return -1;

	if (iGroup > mdl->m_pstudiohdr->numbodyparts)
		return -1;

	mstudiobodyparts_t *pbodypart = (mstudiobodyparts_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pstudiohdr->bodypartindex) + iGroup;

	int iCurrent = (mdl->m_bodynum / pbodypart->base) % pbodypart->nummodels;

	if (iValue >= pbodypart->nummodels)
		return iCurrent;

	mdl->m_bodynum = (mdl->m_bodynum - (iCurrent * pbodypart->base) + (iValue * pbodypart->base));

	return iValue;
}


int SetSkin( StudioModel *mdl, int iValue )
{
	if(!mdl)
		return 0;

	if (iValue > mdl->m_pstudiohdr->numskinfamilies)
	{
		return mdl->m_skinnum;
	}

	mdl->m_skinnum = iValue;

	return iValue;
}

char ** GetSequenceNames( const StudioModel *mdl, unsigned int *count )
{
	if(!mdl || !count)
		return NULL;

	if(mdl->m_pstudiohdr->numseq == 0)
		return NULL;

	int i;
	char **ret = calloc(mdl->m_pstudiohdr->numseq, sizeof(char *));

	const mstudioseqdesc_t *pseqdescs = (mstudioseqdesc_t *) ((Byte *) mdl->m_pstudiohdr + mdl->m_pstudiohdr->seqindex);
	for ( i = 0; i < mdl->m_pstudiohdr->numseq; i++ )
	{
		ret[i] = strdup(pseqdescs[i].label);
	}
	*count = mdl->m_pstudiohdr->numseq;
	return ret;
}

