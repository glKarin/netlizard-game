#include "studio_game.h"
#include "nl_std.h"

extern vec3_t g_vright;
extern float g_lambert;
extern vec3_t			g_lightvec;
extern int				g_ambientlight;
extern float			g_shadelight;
extern vec3_t			g_lightcolor;

static const unsigned Parts[] = {
	LEG_PART,
	BODY_PART,
};

static char *Body_Bones[] = {
	"Bip01",
	"Bip01 Pelvis",
	"Bip01 Spine",
	"Bip01 Spine1",
	"Bip01 Spine2",
	"Bip01 Spine3",
	"Bip01 Neck",
	"Bip01 Head",
	"Bip01 Neck_Sub",
	"Bip01 L Clavicle",
	"Bip01 L UpperArm",
	"Bip01 L Forearm",
	"Bip01 L Hand",
	"L UpperArm_Sub",
	"Bip01 L Clavicle_Sub",
	"Bip01 R Clavicle",
	"Bip01 R UpperArm",
	"Bip01 R Forearm",
	"Bip01 R Hand",
	"Bip01 R Forearm_Sub",
	"R UpperArm_Sub",
	"Bip01 R Clavicle_Sub",
	"Breast_Sub",
	"Spine_Sub",
};

static char *Leg_Bones[] = {
	"Bip01 L Thigh",
	"Bip01 L Calf",
	"Bip01 L Foot",
	"Bip01 L Toe0",
	"L Hip_Sub",
	"L Calf_Sub",
	"Bip01 R Thigh",
	"Bip01 R Calf",
	"Bip01 R Foot",
	"Bip01 R Toe0",
	"R Hip_Sub",
	"R Calf_Sub",
};

void CSOL_SetUpBones ( GameStudioModel *gmdl )
{
	if(!gmdl)
		return;
	
	if(gmdl->part == ALL_PART)
	{
		SetUpBones(&gmdl->mdl);
		return;
	}

	int					i;

	mstudiobone_t		*pbones;
	mstudioseqdesc_t	*pseqdesc, *pseqdesc2;
	mstudioanim_t		*panim, *panim2;

	static vec3_t		pos[MAXSTUDIOBONES];
	float				bonematrix[3][4];
	static vec4_t		q[MAXSTUDIOBONES];

#if 0
	static vec3_t		pos2[MAXSTUDIOBONES];
	static vec4_t		q2[MAXSTUDIOBONES];
	static vec3_t		pos3[MAXSTUDIOBONES];
	static vec4_t		q3[MAXSTUDIOBONES];
	static vec3_t		pos4[MAXSTUDIOBONES];
	static vec4_t		q4[MAXSTUDIOBONES];
#endif
	int m;

	for(m = 0; m < All_Part_Count; m++)
	{
		if (gmdl->sequences[m] >=  gmdl->mdl.m_pstudiohdr->numseq) {
			gmdl->sequences[m] = 0;
		}
	}

		pseqdesc = (mstudioseqdesc_t *)((Byte *)gmdl->mdl.m_pstudiohdr + gmdl->mdl.m_pstudiohdr->seqindex) + gmdl->sequences[Leg_Part_Index];
		pseqdesc2 = (mstudioseqdesc_t *)((Byte *)gmdl->mdl.m_pstudiohdr + gmdl->mdl.m_pstudiohdr->seqindex) + gmdl->sequences[Body_Part_Index];

		panim = GetAnim( &gmdl->mdl, pseqdesc );
		panim2 = GetAnim( &gmdl->mdl, pseqdesc2 );
		CSOL_CalcRotations( &gmdl->mdl, pos, q, pseqdesc, panim, gmdl->frames[Leg_Part_Index], pseqdesc2, panim2, gmdl->frames[Body_Part_Index] );

#if 0
		if (pseqdesc->numblends > 1)
		{
			printf("blendddddddd\n");
			float				s;

			panim += gmdl->mdl.m_pstudiohdr->numbones;
			CalcRotations( &gmdl->mdl, pos2, q2, pseqdesc, panim, fra );
			s = gmdl->mdl.m_blending[0] / 255.0;

			SlerpBones( &gmdl->mdl, q, pos, q2, pos2, s );

			if (pseqdesc->numblends == 4)
			{
				panim += gmdl->mdl.m_pstudiohdr->numbones;
				CalcRotations( &gmdl->mdl, pos3, q3, pseqdesc, panim, fra );

				panim += gmdl->mdl.m_pstudiohdr->numbones;
				CalcRotations( &gmdl->mdl, pos4, q4, pseqdesc, panim, fra );

				s = gmdl->mdl.m_blending[0] / 255.0;
				SlerpBones( &gmdl->mdl, q3, pos3, q4, pos4, s );

				s = gmdl->mdl.m_blending[1] / 255.0;
				SlerpBones( &gmdl->mdl, q, pos, q3, pos3, s );
			}
		}
#endif

		pbones = (mstudiobone_t *)((Byte *)gmdl->mdl.m_pstudiohdr + gmdl->mdl.m_pstudiohdr->boneindex);

		for (i = 0; i < gmdl->mdl.m_pstudiohdr->numbones; i++)
		{
			QuaternionMatrix( q[i], bonematrix );

			bonematrix[0][3] = pos[i][0];
			bonematrix[1][3] = pos[i][1];
			bonematrix[2][3] = pos[i][2];

			if (pbones[i].parent == -1) {
				memcpy(gmdl->mdl.g_bonetransform[i], bonematrix, sizeof(float) * 12);
			} 
			else {
				R_ConcatTransforms (gmdl->mdl.g_bonetransform[pbones[i].parent], bonematrix, gmdl->mdl.g_bonetransform[i]);
			}
		}

}

int CSOL_GetPartBones(StudioModel *mdl, unsigned int ret[], unsigned int count, unsigned part)
{
	if(!mdl)
		return -1;
	if(!ret || count == 0)
		return -1;
	int i;
	int bone = -1;
	unsigned int c = 0;
	unsigned int bi = 0;
	if(part & BODY_PART)
	{
		c = countof(Body_Bones);
		for(i = 0; i < c; i++)
		{
			if(bi >= count)
				break;
			bone = CSOL_FindBone(mdl, Body_Bones[i]);
			if(bone < 0)
				continue;
			ret[bi++] = bone;
		}
	}
	if(part & LEG_PART)
	{
		c = countof(Leg_Bones);
		for(i = 0; i < c; i++)
		{
			if(bi >= count)
				break;
			bone = CSOL_FindBone(mdl, Leg_Bones[i]);
			if(bone < 0)
				continue;
			ret[bi++] = bone;
		}
	}
	return bi;
}

int CSOL_FindBone(const StudioModel *mdl, const char *name)
{
	if(!mdl || !name)
		return -1;
	mstudiobone_t		*pbone;
	pbone	= (mstudiobone_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pstudiohdr->boneindex);
	int i;
	for(i = 0; i < mdl->m_pstudiohdr->numbones; i++)
	{
		//printf("%d %s\n", i, pbone[i].name);
		if(strcasecmp(name, pbone[i].name) == 0)
		{
			return i;
		}
	}
	return -1;
}

void CSOL_DrawModel(GameStudioModel *gmdl)
{
	if(!gmdl)
		return;
	if(gmdl->part == ALL_PART)
	{
		DrawModel(&gmdl->mdl);
		return;
	}

	int i;

	gmdl->mdl.g_smodels_total++; // render data cache cookie
	gmdl->mdl.m_polycount = 0;

	gmdl->mdl.g_pxformverts = &gmdl->mdl.g_xformverts[0];
	gmdl->mdl.g_pvlightvalues = &gmdl->mdl.g_lightvalues[0];

	if (gmdl->mdl.m_pstudiohdr->numbodyparts == 0)
		return;

	glPushMatrix ();

	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//glHint (GL_LINE_SMOOTH_HINT, GL_NICEST );

	CSOL_SetUpBones (gmdl);
	//SetUpBones (gmdl);

	SetupLighting(&gmdl->mdl);

	for (i=0 ; i < gmdl->mdl.m_pstudiohdr->numbodyparts ; i++) 
	{
		SetupModel( &gmdl->mdl, i );
		DrawPoints(&gmdl->mdl);
	}
	glPopMatrix();
}

unsigned CSOL_LoadMDL(GameStudioModel *gmdl, const char *mdlfile)
{
	if(!gmdl || !mdlfile)
		return 0;
	memset(gmdl, 0, sizeof(GameStudioModel));
	unsigned b = Init(&gmdl->mdl, mdlfile);
	gmdl->has_init = b;
	gmdl->part = LEG_PART | BODY_PART;
	return b;
}

void CSOL_FreeMDL(GameStudioModel *gmdl)
{
	if(!gmdl)
		return;
	FreeModel(&gmdl->mdl);
	gmdl->has_init = 0;
}

void CSOL_SetSequence( GameStudioModel *gmdl, unsigned part, int iSequence )
{
	if(!gmdl)
		return;
	if(part == ALL_PART)
	{
		gmdl->part = ALL_PART;
		SetSequence(&gmdl->mdl, iSequence);
		return;
	}

	gmdl->part |= part;
	mstudioseqdesc_t	*pseqdesc;
	if (iSequence > gmdl->mdl.m_pstudiohdr->numseq)
		iSequence = 0;
	if (iSequence < 0)
		iSequence = gmdl->mdl.m_pstudiohdr->numseq-1;

	if(part & BODY_PART)
	{
		gmdl->sequences[Body_Part_Index] = iSequence;
		gmdl->frames[Body_Part_Index] = 0;

		pseqdesc = (mstudioseqdesc_t *)((Byte *)gmdl->mdl.m_pstudiohdr + gmdl->mdl.m_pstudiohdr->seqindex) + (int)iSequence;
		gmdl->fps[Body_Part_Index] = pseqdesc->fps;
	}
	if(part & LEG_PART)
	{
		gmdl->sequences[Leg_Part_Index] = iSequence;
		gmdl->frames[Leg_Part_Index] = 0;
		pseqdesc = (mstudioseqdesc_t *)((Byte *)gmdl->mdl.m_pstudiohdr + gmdl->mdl.m_pstudiohdr->seqindex) + (int)iSequence;
		gmdl->fps[Leg_Part_Index] = pseqdesc->fps;
	}
}

mstudioseqdesc_t * CSOL_GetSequence( GameStudioModel *gmdl, const char *name, int *index )
{
	if(!gmdl || !name)
		return NULL;

	return GetSequence(&gmdl->mdl, name, index);
}

float CSOL_SetFrame(GameStudioModel *gmdl, unsigned part, float frame)
{
	if(!gmdl)
		return 0.0;
	if(part == ALL_PART)
	{
		return SetFrame(&gmdl->mdl, frame);
	}


	int seq;
	int index;
	float fra;
	mstudioseqdesc_t	*pseqdesc;

	if(part == BODY_PART)
		index = Body_Part_Index;
	else if(part == LEG_PART)
		index = Leg_Part_Index;
	else
		return 0.0;
	seq = gmdl->sequences[index];

	pseqdesc = (mstudioseqdesc_t *)((Byte *)gmdl->mdl.m_pstudiohdr + gmdl->mdl.m_pstudiohdr->seqindex) + seq;

	if (pseqdesc->numframes <= 1)
	{
		fra = 0;
	}
	else
	{
		if(frame > pseqdesc->numframes - 1)
			fra = pseqdesc->numframes - 1;
		else if(frame < 0)
			fra = 0;
		else
			fra = frame;
	}
	gmdl->frames[index] = fra;
	return gmdl->frames[index];
}

float CSOL_AdvanceFrame( GameStudioModel *gmdl, unsigned part, float dt )
{
	if(!gmdl)
		return 0.0;

	if(part == ALL_PART)
	{
		gmdl->part = ALL_PART;
		return AdvanceFrame(&gmdl->mdl, dt);
	}

	gmdl->part |= part;
	int index = 0;;
	float fra;
	int seq;
	if(part & BODY_PART)
		index = Body_Part_Index;
	else if(part & LEG_PART)
		index = Leg_Part_Index;
	else
		return 0.0;

	fra = gmdl->frames[index];
	seq = gmdl->sequences[index];

	mstudioseqdesc_t	*pseqdesc;
	pseqdesc = (mstudioseqdesc_t *)((Byte *)gmdl->mdl.m_pstudiohdr + gmdl->mdl.m_pstudiohdr->seqindex) + seq;

	if (dt > 0.1)
		dt = (float)0.1;
	fra += dt * pseqdesc->fps;

	if (pseqdesc->numframes <= 1)
	{
		fra = 0;
	}
	else
	{
		// wrap
		fra -= (int)(fra / (pseqdesc->numframes - 1)) * (pseqdesc->numframes - 1);
	}
	gmdl->frames[index] = fra;
	return fra;
}

void CSOL_CalcRotations ( StudioModel *mdl, vec3_t *pos, vec4_t *q, mstudioseqdesc_t *pseqdesc, mstudioanim_t *panim, float f, mstudioseqdesc_t *pseqdesc2, mstudioanim_t *panim2, float f2 )
{
	if(!mdl || !pos || !q || !pseqdesc || !panim || !pseqdesc2 || !panim)
		return;

	int					i;
	int					frame, frame2;
	mstudiobone_t		*pbone;
	float				s, s2;
	int num, num2;
	unsigned int bones[MAXSTUDIOBONES], bones2[MAXSTUDIOBONES];
	unsigned h = 0;
	int j;

	frame = (int)f;
	s = (f - frame);
	frame2 = (int)f2;
	s2 = (f2 - frame2);

	num = CSOL_GetPartBones(mdl, bones, MAXSTUDIOBONES, Parts[Leg_Part_Index]);
	num2 = CSOL_GetPartBones(mdl, bones2, MAXSTUDIOBONES, Parts[Body_Part_Index]);

	// add in programatic controllers
	CalcBoneAdj(mdl);

	pbone		= (mstudiobone_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pstudiohdr->boneindex);
	for (i = 0; i < mdl->m_pstudiohdr->numbones; i++, pbone++, panim++, panim2++) 
	{
		h = 0;
		for(j = 0; j < num; j++)
		{
			if(i == bones[j])
			{
				h = 1;
				break;
			}
		}
		if(h)
		{
			CalcBoneQuaternion( mdl, frame, s, pbone, panim, q[i] );
			CalcBonePosition( mdl, frame, s, pbone, panim, pos[i] );
		}
		else
		{
			CalcBoneQuaternion( mdl, frame2, s2, pbone, panim2, q[i] );
			CalcBonePosition( mdl, frame2, s2, pbone, panim2, pos[i] );
		}
	}

	if (pseqdesc->motiontype & STUDIO_X)
		pos[pseqdesc->motionbone][0] = 0.0;
	if (pseqdesc->motiontype & STUDIO_Y)
		pos[pseqdesc->motionbone][1] = 0.0;
	if (pseqdesc->motiontype & STUDIO_Z)
		pos[pseqdesc->motionbone][2] = 0.0;
}

