/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
****/
// studio_render.cpp: routines for drawing Half-Life 3DStudio models
// updates:
// 1-4-99	fixed AdvanceFrame wraping bug

#include "studio_render.h"

//#include <GL/gl.h>

static void draw_arrays(unsigned type, unsigned int count, float *vertex, unsigned int vc, float *texcoord, unsigned int tc, float * normal, unsigned int nc, float *color, unsigned int cc)
{
	if(!vertex)
		return;

	glEnableClientState(GL_VERTEX_ARRAY);

	if(texcoord)
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	if(normal)
		glEnableClientState(GL_NORMAL_ARRAY);	
	if(color && cc != 0)
		glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(vc, GL_FLOAT, 0, vertex);
	if(texcoord)
		glTexCoordPointer(tc, GL_FLOAT, 0, texcoord);
	if(normal)
		glNormalPointer(GL_FLOAT, 0, normal);
	if(color)
	{
		if(cc != 0)
			glColorPointer(cc, GL_FLOAT, 0, color);
		else
			glColor4fv(color);
	}

	oglDrawArrays(type, 0, count);

	glDisableClientState(GL_VERTEX_ARRAY);

	if(texcoord)
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	if(normal)
		glDisableClientState(GL_NORMAL_ARRAY);	
	if(color && cc != 0)
		glDisableClientState(GL_COLOR_ARRAY);
}

void color3f(float r, float g, float b)
{
	oglColor4f(r, g, b, 1.0);
}

void color4f(float r, float g, float b, float a)
{
	oglColor4f(r, g, b, a);
}

HLSDK_Render_Function karinDrawArrays = draw_arrays;
HLSDK_Color3f karinColor3f = color3f;
HLSDK_Color4f karinColor4f = color4f;

////////////////////////////////////////////////////////////////////////

static GLuint Indices[60] ={
		0,4,1,0,9,4,9,5,4,4,5,8,4,8,1,
		8,10,1,8,3,10,5,3,8,5,2,3,2,7,3,
		7,10,3,7,6,10,7,11,6,11,0,6,0,1,6,
		6,1,10,9,0,11,9,11,2,9,2,5,7,2,11};
////////////////////////////////////////////////////////////////////////
vec3_t			settings_lightcolor = {1.0, 1.0, 1.0};

vec3_t g_vright = { 100, 100, 50 };		// needs to be set to viewer's right in order for chrome to work
float g_lambert = 1.5;		// modifier for pseudo-hemispherical lighting


vec3_t			g_lightvec;						// light vector in model reference frame
int				g_ambientlight;					// ambient world light
float			g_shadelight;					// direct world light
vec3_t			g_lightcolor;



////////////////////////////////////////////////////////////////////////

void CalcBoneAdj( StudioModel *mdl )
{
	if(!mdl)
		return;

	int					i, j;
	float				value;
	mstudiobonecontroller_t *pbonecontroller;
	
	pbonecontroller = (mstudiobonecontroller_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pstudiohdr->bonecontrollerindex);

	for (j = 0; j < mdl->m_pstudiohdr->numbonecontrollers; j++)
	{
		i = pbonecontroller[j].index;
		if (i <= 3)
		{
			// check for 360% wrapping
			if (pbonecontroller[j].type & STUDIO_RLOOP)
			{
				value = mdl->m_controller[i] * (360.0/256.0) + pbonecontroller[j].start;
			}
			else 
			{
				value = mdl->m_controller[i] / 255.0;
				if (value < 0) value = 0;
				if (value > 1.0) value = 1.0;
				value = (1.0 - value) * pbonecontroller[j].start + value * pbonecontroller[j].end;
			}
			// Con_DPrintf( "%d %d %f : %f\n", m_controller[j], m_prevcontroller[j], value, dadt );
		}
		else
		{
			value = mdl->m_mouth / 64.0;
			if (value > 1.0) value = 1.0;
			value = (1.0 - value) * pbonecontroller[j].start + value * pbonecontroller[j].end;
			// Con_DPrintf("%d %f\n", mouthopen, value );
		}
		switch(pbonecontroller[j].type & STUDIO_TYPES)
		{
		case STUDIO_XR:
		case STUDIO_YR:
		case STUDIO_ZR:
			mdl->m_adj[j] = value * (Q_PI / 180.0);
			break;
		case STUDIO_X:
		case STUDIO_Y:
		case STUDIO_Z:
			mdl->m_adj[j] = value;
			break;
		}
	}
}


void CalcBoneQuaternion( const StudioModel *mdl, int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *q )
{
	if(!mdl || !pbone || !panim)
		return;

	int					j, k;
	vec4_t				q1, q2;
	vec3_t				angle1, angle2;
	mstudioanimvalue_t	*panimvalue;

	for (j = 0; j < 3; j++)
	{
		if (panim->offset[j+3] == 0)
		{
			angle2[j] = angle1[j] = pbone->value[j+3]; // default;
		}
		else
		{
			panimvalue = (mstudioanimvalue_t *)((Byte *)panim + panim->offset[j+3]);
			k = frame;
			while (panimvalue->num.total <= k)
			{
				k -= panimvalue->num.total;
				panimvalue += panimvalue->num.valid + 1;
			}
			// Bah, missing blend!
			if (panimvalue->num.valid > k)
			{
				angle1[j] = panimvalue[k+1].value;

				if (panimvalue->num.valid > k + 1)
				{
					angle2[j] = panimvalue[k+2].value;
				}
				else
				{
					if (panimvalue->num.total > k + 1)
						angle2[j] = angle1[j];
					else
						angle2[j] = panimvalue[panimvalue->num.valid+2].value;
				}
			}
			else
			{
				angle1[j] = panimvalue[panimvalue->num.valid].value;
				if (panimvalue->num.total > k + 1)
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

		if (pbone->bonecontroller[j+3] != -1)
		{
			angle1[j] += mdl->m_adj[pbone->bonecontroller[j+3]];
			angle2[j] += mdl->m_adj[pbone->bonecontroller[j+3]];
		}
	}

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
}


void CalcBonePosition( const StudioModel *mdl, int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *pos )
{
	if(!mdl || !pbone || !panim || !pos)
		return;

	int					j, k;
	mstudioanimvalue_t	*panimvalue;

	for (j = 0; j < 3; j++)
	{
		pos[j] = pbone->value[j]; // default;
		if (panim->offset[j] != 0)
		{
			panimvalue = (mstudioanimvalue_t *)((Byte *)panim + panim->offset[j]);
			
			k = frame;
			// find span of values that includes the frame we want
			while (panimvalue->num.total <= k)
			{
				k -= panimvalue->num.total;
				panimvalue += panimvalue->num.valid + 1;
			}
			// if we're inside the span
			if (panimvalue->num.valid > k)
			{
				// and there's more data in the span
				if (panimvalue->num.valid > k + 1)
				{
					pos[j] += (panimvalue[k+1].value * (1.0 - s) + s * panimvalue[k+2].value) * pbone->scale[j];
				}
				else
				{
					pos[j] += panimvalue[k+1].value * pbone->scale[j];
				}
			}
			else
			{
				// are we at the end of the repeating values section and there's another section with data?
				if (panimvalue->num.total <= k + 1)
				{
					pos[j] += (panimvalue[panimvalue->num.valid].value * (1.0 - s) + s * panimvalue[panimvalue->num.valid + 2].value) * pbone->scale[j];
				}
				else
				{
					pos[j] += panimvalue[panimvalue->num.valid].value * pbone->scale[j];
				}
			}
		}
		if (pbone->bonecontroller[j] != -1)
		{
			pos[j] += mdl->m_adj[pbone->bonecontroller[j]];
		}
	}
}


void CalcRotations ( StudioModel *mdl, vec3_t *pos, vec4_t *q, mstudioseqdesc_t *pseqdesc, mstudioanim_t *panim, float f )
{
	if(!mdl || !pos || !q || !pseqdesc || !panim)
		return;

	int					i;
	int					frame;
	mstudiobone_t		*pbone;
	float				s;

	frame = (int)f;
	s = (f - frame);

	// add in programatic controllers
	CalcBoneAdj(mdl);

	pbone		= (mstudiobone_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pstudiohdr->boneindex);
	for (i = 0; i < mdl->m_pstudiohdr->numbones; i++, pbone++, panim++) 
	{
		CalcBoneQuaternion( mdl, frame, s, pbone, panim, q[i] );
		CalcBonePosition( mdl, frame, s, pbone, panim, pos[i] );
	}

	if (pseqdesc->motiontype & STUDIO_X)
		pos[pseqdesc->motionbone][0] = 0.0;
	if (pseqdesc->motiontype & STUDIO_Y)
		pos[pseqdesc->motionbone][1] = 0.0;
	if (pseqdesc->motiontype & STUDIO_Z)
		pos[pseqdesc->motionbone][2] = 0.0;
}


mstudioanim_t * GetAnim( StudioModel *mdl, mstudioseqdesc_t *pseqdesc )
{
	if(!mdl || !pseqdesc)
		return NULL;

	mstudioseqgroup_t	*pseqgroup;
	pseqgroup = (mstudioseqgroup_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pstudiohdr->seqgroupindex) + pseqdesc->seqgroup;

	if (pseqdesc->seqgroup == 0)
	{
		return (mstudioanim_t *)((Byte *)mdl->m_pstudiohdr + pseqgroup->data + pseqdesc->animindex);
	}

	return (mstudioanim_t *)((Byte *)mdl->m_panimhdr[pseqdesc->seqgroup] + pseqdesc->animindex);
}


void SlerpBones( const StudioModel *mdl, vec4_t q1[], vec3_t pos1[], vec4_t q2[], vec3_t pos2[], float s )
{
	if(!mdl || !q1 || !pos1 || !q2 || !pos2)
		return;

	int			i;
	vec4_t		q3;
	float		s1;

	if (s < 0) s = 0;
	else if (s > 1.0) s = 1.0;

	s1 = 1.0 - s;

	for (i = 0; i < mdl->m_pstudiohdr->numbones; i++)
	{
		QuaternionSlerp( q1[i], q2[i], s, q3 );
		q1[i][0] = q3[0];
		q1[i][1] = q3[1];
		q1[i][2] = q3[2];
		q1[i][3] = q3[3];
		pos1[i][0] = pos1[i][0] * s1 + pos2[i][0] * s;
		pos1[i][1] = pos1[i][1] * s1 + pos2[i][1] * s;
		pos1[i][2] = pos1[i][2] * s1 + pos2[i][2] * s;
	}
}


float AdvanceFrame( StudioModel *mdl, float dt )
{
	if(!mdl)
		return 0.0;

	mstudioseqdesc_t	*pseqdesc;
	pseqdesc = (mstudioseqdesc_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pstudiohdr->seqindex) + mdl->m_sequence;

	if (dt > 0.1)
		dt = (float)0.1;
	mdl->m_frame += dt * pseqdesc->fps;

	if (pseqdesc->numframes <= 1)
	{
		mdl->m_frame = 0;
	}
	else
	{
		// wrap
		mdl->m_frame -= (int)(mdl->m_frame / (pseqdesc->numframes - 1)) * (pseqdesc->numframes - 1);
	}
	return mdl->m_frame;
}


void SetUpBones ( StudioModel *mdl )
{
	if(!mdl)
		return;

	int					i;

	mstudiobone_t		*pbones;
	mstudioseqdesc_t	*pseqdesc;
	mstudioanim_t		*panim;

	static vec3_t		pos[MAXSTUDIOBONES];
	float				bonematrix[3][4];
	static vec4_t		q[MAXSTUDIOBONES];

	static vec3_t		pos2[MAXSTUDIOBONES];
	static vec4_t		q2[MAXSTUDIOBONES];
	static vec3_t		pos3[MAXSTUDIOBONES];
	static vec4_t		q3[MAXSTUDIOBONES];
	static vec3_t		pos4[MAXSTUDIOBONES];
	static vec4_t		q4[MAXSTUDIOBONES];


	if (mdl->m_sequence >=  mdl->m_pstudiohdr->numseq) {
		mdl->m_sequence = 0;
	}

	pseqdesc = (mstudioseqdesc_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pstudiohdr->seqindex) + mdl->m_sequence;

	panim = GetAnim( mdl, pseqdesc );
	CalcRotations( mdl, pos, q, pseqdesc, panim, mdl->m_frame );

	if (pseqdesc->numblends > 1)
	{
		float				s;

		panim += mdl->m_pstudiohdr->numbones;
		CalcRotations( mdl, pos2, q2, pseqdesc, panim, mdl->m_frame );
		s = mdl->m_blending[0] / 255.0;

		SlerpBones( mdl, q, pos, q2, pos2, s );

		if (pseqdesc->numblends == 4)
		{
			panim += mdl->m_pstudiohdr->numbones;
			CalcRotations( mdl, pos3, q3, pseqdesc, panim, mdl->m_frame );

			panim += mdl->m_pstudiohdr->numbones;
			CalcRotations( mdl, pos4, q4, pseqdesc, panim, mdl->m_frame );

			s = mdl->m_blending[0] / 255.0;
			SlerpBones( mdl, q3, pos3, q4, pos4, s );

			s = mdl->m_blending[1] / 255.0;
			SlerpBones( mdl, q, pos, q3, pos3, s );
		}
	}

	pbones = (mstudiobone_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pstudiohdr->boneindex);

	for (i = 0; i < mdl->m_pstudiohdr->numbones; i++) {
		QuaternionMatrix( q[i], bonematrix );

		bonematrix[0][3] = pos[i][0];
		bonematrix[1][3] = pos[i][1];
		bonematrix[2][3] = pos[i][2];

		if (pbones[i].parent == -1) {
			memcpy(mdl->g_bonetransform[i], bonematrix, sizeof(float) * 12);
		} 
		else {
			R_ConcatTransforms (mdl->g_bonetransform[pbones[i].parent], bonematrix, mdl->g_bonetransform[i]);
		}
	}
}



/*
================
StudioModel::TransformFinalVert
================
*/
void Lighting (StudioModel *mdl, float *lv, int bone, int flags, vec3_t normal)
{
	if(!mdl || !lv)
		return;

	float 	illum;
	float	lightcos;

	illum = g_ambientlight;

	if (flags & STUDIO_NF_FLATSHADE)
	{
		illum += g_shadelight * 0.8;
	} 
	else 
	{
		float r;
		lightcos = DotProduct (normal, mdl->g_blightvec[bone]); // -1 colinear, 1 opposite

		if (lightcos > 1.0)
			lightcos = 1;

		illum += g_shadelight;

		r = g_lambert;
		if (r <= 1.0) r = 1.0;

		lightcos = (lightcos + (r - 1.0)) / r; 		// do modified hemispherical lighting
		if (lightcos > 0.0) 
		{
			illum -= g_shadelight * lightcos; 
		}
		if (illum <= 0)
			illum = 0;
	}

	if (illum > 255) 
		illum = 255;
	*lv = illum / 255.0;	// Light from 0 to 1.0
}


void Chrome (StudioModel *mdl, int *pchrome, int bone, vec3_t normal)
{
	if(!mdl || !pchrome)
		return;

	float n;

	if (mdl->g_chromeage[bone] != mdl->g_smodels_total)
	{
		// calculate vectors from the viewer to the bone. This roughly adjusts for position
		vec3_t chromeupvec;		// mdl->g_chrome t vector in world reference frame
		vec3_t chromerightvec;	// mdl->g_chrome s vector in world reference frame
		vec3_t tmp;				// vector pointing at bone in world reference frame
		VectorScale( mdl->m_origin, -1, tmp );
		tmp[0] += mdl->g_bonetransform[bone][0][3];
		tmp[1] += mdl->g_bonetransform[bone][1][3];
		tmp[2] += mdl->g_bonetransform[bone][2][3];
		VectorNormalize( tmp );
		CrossProduct( tmp, g_vright, chromeupvec );
		VectorNormalize( chromeupvec );
		CrossProduct( tmp, chromeupvec, chromerightvec );
		VectorNormalize( chromerightvec );

		VectorIRotate( chromeupvec, mdl->g_bonetransform[bone], mdl->g_chromeup[bone] );
		VectorIRotate( chromerightvec, mdl->g_bonetransform[bone], mdl->g_chromeright[bone] );

		mdl->g_chromeage[bone] = mdl->g_smodels_total;
	}

	// calc s coord
	n = DotProduct( normal, mdl->g_chromeright[bone] );
	pchrome[0] = (n + 1.0) * 32; // FIX: make this a float

	// calc t coord
	n = DotProduct( normal, mdl->g_chromeup[bone] );
	pchrome[1] = (n + 1.0) * 32; // FIX: make this a float
}


/*
================
StudioModel::SetupLighting
	set some global variables based on entity position
inputs:
outputs:
	g_ambientlight
	g_shadelight
================
*/
void SetupLighting (const StudioModel *mdl)
{
	if(!mdl)
		return;

	int i;
	g_ambientlight = 32;
	g_shadelight = 192;

	g_lightvec[0] = 0;
	g_lightvec[1] = 0;
	g_lightvec[2] = -1.0;

	g_lightcolor[0] = settings_lightcolor[0];
	g_lightcolor[1] = settings_lightcolor[1];
	g_lightcolor[2] = settings_lightcolor[2];

	// TODO: only do it for bones that actually have textures
	for (i = 0; i < mdl->m_pstudiohdr->numbones; i++)
	{
		VectorIRotate( g_lightvec, mdl->g_bonetransform[i], mdl->g_blightvec[i] );
	}
}


/*
=================
StudioModel::SetupModel
	based on the body part, figure out which mesh it should be using.
inputs:
	currententity
outputs:
	pstudiomesh
	pmdl
=================
*/

void SetupModel ( StudioModel *mdl, int bodypart )
{
	if(!mdl)
		return;

	int index;

	if (bodypart > mdl->m_pstudiohdr->numbodyparts)
	{
		// Con_DPrintf ("StudioModel::SetupModel: no such bodypart %d\n", bodypart);
		bodypart = 0;
	}

	mstudiobodyparts_t   *pbodypart = (mstudiobodyparts_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pstudiohdr->bodypartindex) + bodypart;

	index = mdl->m_bodynum / pbodypart->base;
	index = index % pbodypart->nummodels;

	mdl->m_pmodel = (mstudiomodel_t *)((Byte *)mdl->m_pstudiohdr + pbodypart->modelindex) + index;
}

void drawBoxFill (const vec3_t *v)
{
	if(!v)
		return;

	int i;
	float vs[10 * 3];

	//glBegin (GL_QUAD_STRIP);
	for (i = 0; i < 10; i++)
		COPY_ARR (vs + 3 * i, v[i & 7], 3)
	karinDrawArrays(GL_TRIANGLE_STRIP, 10, vs, 3, NULL, 2, NULL, 3, NULL, 0);
	
	//glBegin  (GL_QUAD_STRIP);
	COPY_ARR(vs, v[6], 3)
	COPY_ARR(vs + 3, v[0], 3)
	COPY_ARR(vs + 6, v[4], 3)
	COPY_ARR(vs + 9, v[2], 3)
	karinDrawArrays(GL_TRIANGLE_STRIP, 4, vs, 3, NULL, 2, NULL, 3, NULL, 0);

	//glBegin  (GL_QUAD_STRIP);
	COPY_ARR(vs, v[1], 3)
	COPY_ARR(vs + 3, v[7], 3)
	COPY_ARR(vs + 6, v[3], 3)
	COPY_ARR(vs + 9, v[5], 3)
	karinDrawArrays(GL_TRIANGLE_STRIP, 4, vs, 3, NULL, 2, NULL, 3, NULL, 0);

}

void drawBox (const vec3_t *v)
{
	if(!v)
		return;

	int i;
	float rects[10 * 3];
	float vs[4 * 3];

	//glBegin (GL_QUAD_STRIP);
	for (i = 0; i < 10; i++)
		COPY_ARR (rects + 3 * i, v[i & 7], 3)
	//karinDrawArrays(GL_LINE_STRIP, 10, vs, 3, NULL, 2, NULL, 3, NULL, 0);

	for(i = 0; i < 6; i += 2)
	{
		COPY_ARR(vs, rects + 3 * i, 3)
		COPY_ARR(vs + 3, rects + 3 * (i + 1), 3)
		COPY_ARR(vs + 9, rects + 3 * (i + 2), 3)
		COPY_ARR(vs + 6, rects + 3 * (i + 3), 3)
		karinDrawArrays(GL_LINE_LOOP, 4, vs, 3, NULL, 2, NULL, 3, NULL, 0);
	}
	
	//glBegin  (GL_QUAD_STRIP);
	COPY_ARR(vs, v[6], 3)
	COPY_ARR(vs + 3, v[0], 3)
	COPY_ARR(vs + 9, v[4], 3)
	COPY_ARR(vs + 6, v[2], 3)
	karinDrawArrays(GL_LINE_LOOP, 4, vs, 3, NULL, 2, NULL, 3, NULL, 0);

	//glBegin  (GL_QUAD_STRIP);
	COPY_ARR(vs, v[1], 3)
	COPY_ARR(vs + 3, v[7], 3)
	COPY_ARR(vs + 9, v[3], 3)
	COPY_ARR(vs + 6, v[5], 3)
	karinDrawArrays(GL_LINE_LOOP, 4, vs, 3, NULL, 2, NULL, 3, NULL, 0);

}

/*
================
StudioModel::DrawModel
inputs:
	currententity
	r_entorigin
================
*/
void DrawModel(StudioModel *mdl)
{
	if(!mdl)
		return;

	int i;

	mdl->g_smodels_total++; // render data cache cookie
	mdl->m_polycount = 0;

	mdl->g_pxformverts = &mdl->g_xformverts[0];
	mdl->g_pvlightvalues = &mdl->g_lightvalues[0];

	if (mdl->m_pstudiohdr->numbodyparts == 0)
		return;

	glPushMatrix ();

	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//glHint (GL_LINE_SMOOTH_HINT, GL_NICEST );

	SetUpBones (mdl);

	SetupLighting(mdl);

	for (i=0 ; i < mdl->m_pstudiohdr->numbodyparts ; i++) 
	{
		SetupModel( mdl, i );
		DrawPoints(mdl);
	}
	glPopMatrix();
}

/*
================

================
*/
//////////////////////////////////////////////////////////////////////
// Code by Otis is (c)1999 Solutions Design, http://www.sd.nl
// Code by Ascent is (c)1999 Greg Dunn.
// Code by Dark Yoda is (c)1999 Volker Sch鰊efeld.
// All rights reserved.
//////////////////////////////////////////////////////////////////////
void DrawIcosahedron(float x,float y,float z,float size)
{
	float a = 0.525731112119133606 * size;
	float b = 0.850650808352039932 * size;

	GLfloat Vertices[12][3] = {
		{ -a,0.0,  b},{  a,0.0,  b},{ -a,0.0,  -b},{  a,0.0, -b},
		{0.0,  b,  a},{0.0,  b, -a},{0.0, -b,  a},{0.0, -b, -a},
		{  b,  a,0.0},{ -b,  a,0.0},{  b, -a,0.0},{ -b, -a,0.0}		
	};

	glPushMatrix();

	glTranslatef(x,y,z);

	int i;
	float vs[20 * 3 * 3];

	//glBegin(GL_LINES);
		for(i=0;i<20;i++)
		{
			COPY_ARR(vs + 9 * i, &Vertices[Indices[i*3]][0], 3)
			COPY_ARR(vs + 9 * i + 3, &Vertices[Indices[i*3+1]][0], 3)
			COPY_ARR(vs + 9 * i + 6, &Vertices[Indices[i*3+2]][0], 3)
		};
		karinDrawArrays(GL_LINES, 20 * 3, vs, 3, NULL, 2, NULL, 3, NULL, 0);

	glPopMatrix();
}
//////////////////////////////////////////////////////////////////////


void DrawBones (const StudioModel *mdl)
{
	if(!mdl)
		return;

	int i;
	float vs[2 * 3];

	mstudiobone_t *pbones = (mstudiobone_t *) ((Byte *) mdl->m_pstudiohdr + mdl->m_pstudiohdr->boneindex);
	glDisable (GL_TEXTURE_2D);
	glDisable (GL_DEPTH_TEST);
	glDisable (GL_BLEND);

	for (i = 0; i < mdl->m_pstudiohdr->numbones; i++)
	{
		if (pbones[i].parent >= 0)
		{
			if ( i == mdl->m_selbone )
			{
				karinColor3f (0.7f, 0.0f, 0.2f);
				glLineWidth (2.5f);
			}
			else
			{
				karinColor3f (0.0f, 0.6f, 0.2f);
				glLineWidth (1.0f);
			}

			//glBegin (GL_LINES);
				vs[0] = mdl->g_bonetransform[pbones[i].parent][0][3];
				vs[1] = mdl->g_bonetransform[pbones[i].parent][1][3];
				vs[2] = mdl->g_bonetransform[pbones[i].parent][2][3];

				vs[3] = mdl->g_bonetransform[i][0][3];
				vs[4] = mdl->g_bonetransform[i][1][3];
				vs[5] = mdl->g_bonetransform[i][2][3];
				karinDrawArrays(GL_LINES, 2, vs, 3, NULL, 2, NULL, 3, NULL, 0);

			if ( i == mdl->m_selbone )
			{
				karinColor3f (0.7f, 0.0f, 0.2f);
				glPointSize (6.0f);
			}
			else
			{
				karinColor3f (0.0f, 0.2f, 0.6f);
				glPointSize (4.0f);
			}
			DrawIcosahedron(mdl->g_bonetransform[i][0][3],mdl->g_bonetransform[i][1][3],mdl->g_bonetransform[i][2][3],0.25f);
		}
		else
		{
			// draw parent bone node
			glPointSize (7.0f);
			karinColor3f (0.8f, 0.0f, 0.0f);
			DrawIcosahedron(mdl->g_bonetransform[i][0][3],mdl->g_bonetransform[i][1][3],mdl->g_bonetransform[i][2][3],1.0f);
		}
	}

	// karin
	glEnable (GL_TEXTURE_2D);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	glPointSize (1.0f);
}

/*
================

================
*/
void DrawHitboxes (const StudioModel *mdl)
{
	if(!mdl)
		return;

	int i;

	glDisable (GL_TEXTURE_2D);
	glDisable (GL_CULL_FACE);
	glEnable (GL_DEPTH_TEST);

	glLineWidth (2.0f); 

	//CAP glPolygonMode (GL_FRONT, GL_FILL);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (i = 0; i < mdl->m_pstudiohdr->numhitboxes; i++)
	{
		mstudiobbox_t *pbboxes = (mstudiobbox_t *) ((Byte *) mdl->m_pstudiohdr + mdl->m_pstudiohdr->hitboxindex);
		
		if ( i == mdl->m_selhitbox )
			karinColor4f (0.7f, 0.0f, 0.2f, 0.8f);
		else if ( pbboxes[i].bone == mdl->m_selbone )
			karinColor4f (0.8f, 0.4f, 0.2f, 0.8f);
		else
			karinColor4f (0.0f, 0.6f, 0.2f, 0.3f);

		vec3_t v[8], v2[8], bbmin, bbmax;
		VectorCopy (pbboxes[i].bbmin, bbmin);
		VectorCopy (pbboxes[i].bbmax, bbmax);

		v[0][0] = bbmin[0];
		v[0][1] = bbmax[1];
		v[0][2] = bbmin[2];

		v[1][0] = bbmin[0];
		v[1][1] = bbmin[1];
		v[1][2] = bbmin[2];

		v[2][0] = bbmax[0];
		v[2][1] = bbmax[1];
		v[2][2] = bbmin[2];

		v[3][0] = bbmax[0];
		v[3][1] = bbmin[1];
		v[3][2] = bbmin[2];

		v[4][0] = bbmax[0];
		v[4][1] = bbmax[1];
		v[4][2] = bbmax[2];

		v[5][0] = bbmax[0];
		v[5][1] = bbmin[1];
		v[5][2] = bbmax[2];

		v[6][0] = bbmin[0];
		v[6][1] = bbmax[1];
		v[6][2] = bbmax[2];

		v[7][0] = bbmin[0];
		v[7][1] = bbmin[1];
		v[7][2] = bbmax[2];

		VectorTransform (v[0], mdl->g_bonetransform[pbboxes[i].bone], v2[0]);
		VectorTransform (v[1], mdl->g_bonetransform[pbboxes[i].bone], v2[1]);
		VectorTransform (v[2], mdl->g_bonetransform[pbboxes[i].bone], v2[2]);
		VectorTransform (v[3], mdl->g_bonetransform[pbboxes[i].bone], v2[3]);
		VectorTransform (v[4], mdl->g_bonetransform[pbboxes[i].bone], v2[4]);
		VectorTransform (v[5], mdl->g_bonetransform[pbboxes[i].bone], v2[5]);
		VectorTransform (v[6], mdl->g_bonetransform[pbboxes[i].bone], v2[6]);
		VectorTransform (v[7], mdl->g_bonetransform[pbboxes[i].bone], v2[7]);
		
		drawBox (v2);
	}

	// karin
	glEnable (GL_TEXTURE_2D);
	glEnable (GL_CULL_FACE);

	glLineWidth (1.0f); 
}

/*
================

================
*/
void DrawAtachments (const StudioModel *mdl)
{
	if(!mdl)
		return;

	int i;
	float vs[6 * 3];
	float cs[6 * 4]; // OpenGL ES1.1 glColorPointer(4, ...)
#define _COPY_COLOR3(c, i, r, g, b) \
	(c)[(i) * 4] = (r); \
	(c)[(i) * 4 + 1] = (g); \
	(c)[(i) * 4 + 2] = (b); \
	(c)[(i) * 4 + 3] = 1.0;

	glDisable (GL_TEXTURE_2D);
	glDisable (GL_CULL_FACE);
	glDisable (GL_DEPTH_TEST);
	for (i = 0; i < mdl->m_pstudiohdr->numattachments; i++)
	{
		mstudioattachment_t *pattachments = (mstudioattachment_t *) ((Byte *) mdl->m_pstudiohdr + mdl->m_pstudiohdr->attachmentindex);
		vec3_t v[4];
		VectorTransform (pattachments[i].org, mdl->g_bonetransform[pattachments[i].bone], v[0]);
		VectorTransform (pattachments[i].vectors[0], mdl->g_bonetransform[pattachments[i].bone], v[1]);
		VectorTransform (pattachments[i].vectors[1], mdl->g_bonetransform[pattachments[i].bone], v[2]);
		VectorTransform (pattachments[i].vectors[2], mdl->g_bonetransform[pattachments[i].bone], v[3]);
		//glBegin (GL_LINES);
		_COPY_COLOR3(cs, 0, 1, 0, 0);
		COPY_ARR(vs, v[0], 3)
		_COPY_COLOR3(cs, 1, 1, 1, 1);
		COPY_ARR(vs + 3, v[1], 3)
		_COPY_COLOR3(cs, 2, 1, 0, 0);
		COPY_ARR(vs + 6, v[0], 3)
		_COPY_COLOR3(cs, 3, 1, 1, 1);
		COPY_ARR(vs + 9, v[2], 3)
		_COPY_COLOR3(cs, 4, 1, 0, 0);
		COPY_ARR(vs + 12, v[0], 3)
		_COPY_COLOR3(cs, 5, 1, 1, 1);
		COPY_ARR(vs + 15, v[3], 3)
		karinDrawArrays(GL_LINES, 6, vs, 3, NULL, 2, NULL, 3, cs, 4);

		glPointSize (5);
		karinColor3f (0, 1, 0);
		//glBegin (GL_POINTS);
		COPY_ARR(vs, v[0], 3)
		karinDrawArrays(GL_POINTS, 1, vs, 3, NULL, 2, NULL, 3, NULL, 0);
		glPointSize (1);
	}

	// karin
	glEnable (GL_TEXTURE_2D);
	glEnable (GL_CULL_FACE);
	glEnable (GL_DEPTH_TEST);
#undef _COPY_COLOR3
}

/*
================

================
*/
void DrawMaterial( StudioModel *mdl, int skin, int nWidth, int nHeight )
{
	if(!mdl)
		return;

	float				w, h;
	float				x, y;
	studiohdr_t			*hdr;
	mstudiotexture_t	*ptextures;

	mdl->m_polycount = 0;

	hdr = mdl->m_ptexturehdr;
	ptextures = (mstudiotexture_t *) ((Byte *) hdr + hdr->textureindex);

	w = (float) ptextures[skin].width;
	h = (float) ptextures[skin].height;

	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
	glLoadIdentity ();

	glDisable (GL_CULL_FACE);

	glDisable(GL_BLEND);
	oglDisable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER,0.5f);
	if ( ptextures[skin].flags & STUDIO_NF_TRANSPARANT )
	{
		oglEnable(GL_ALPHA_TEST);
	}

	//CAP glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	x = ((float) nWidth - w) / 2;
	y = ((float) nHeight - h) / 2;

	glEnable (GL_TEXTURE_2D);
	karinColor4f (1.0f, 1.0f, 1.0f, 1.0f);
	oglBindTexture (GL_TEXTURE_2D, skin);

	//glBegin (GL_TRIANGLE_STRIP);

	float vs[8] = {
		x, y,
		x + w, y,
		x, y + h,
		x + w, y + h,
	};

	float ts[8] = {
		0, 0,
		1, 0,
		0, 1,
		1, 1,
	};
	karinDrawArrays(GL_TRIANGLE_STRIP, 4, vs, 2, ts, 2, NULL, 3, NULL, 0);

	mdl->m_polycount++;

	// TEXTURE
	glDisable (GL_TEXTURE_2D);
	karinColor4f (1.0f, 1.0f, 1.0f, 1.0f);
	//CAP glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);

	// UV MAP
	DrawUVMap(mdl, skin, nWidth, nHeight);
	// END UV MAP

	oglBindTexture (GL_TEXTURE_2D, 0);
	glPopMatrix();
	// karin
	glEnable (GL_CULL_FACE);
	glEnable (GL_TEXTURE_2D);
	glEnable(GL_BLEND);
}

/*
================

================
*/
void DrawUVMap(const StudioModel *mdl, int skin, int nWidth, int nHeight )
{}

/*
================

================
*/
void DrawPoints (StudioModel *mdl)
{
	if(!mdl)
		return;

	int					i, j;
	mstudiomesh_t		*pmesh;
	Byte				*pvertbone;
	Byte				*pnormbone;
	vec3_t				*pstudioverts;
	vec3_t				*pstudionorms;
	mstudiotexture_t	*ptexture;
	float 				*av;
	float				*lv;
	float				lv_tmp;
	float				fAlpha;
	short				*pskinref;
	float *vs;
	float *ts;
	float *cs;
	int vertex_count;
	unsigned primitive_type;

#define _COPY_VERTEX3(v, i, x, y, z) \
	(v)[(i) * 3] = (x); \
	(v)[(i) * 3 + 1] = (y); \
	(v)[(i) * 3 + 2] = (z);

#define _COPY_TEXCOORD2(v, i, s, t) \
(v)[(i) * 2] = (s); \
(v)[(i) * 2 + 1] = (t);

#define _COPY_COLOR4(v, i, r, g, b, a) \
(v)[(i) * 4] = (r); \
(v)[(i) * 4 + 1] = (g); \
(v)[(i) * 4 + 2] = (b); \
(v)[(i) * 4 + 3] = (a);

	pvertbone = ((Byte *)mdl->m_pstudiohdr + mdl->m_pmodel->vertinfoindex);
	pnormbone = ((Byte *)mdl->m_pstudiohdr + mdl->m_pmodel->norminfoindex);
	ptexture = (mstudiotexture_t *)((Byte *)mdl->m_ptexturehdr + mdl->m_ptexturehdr->textureindex);

	pmesh = (mstudiomesh_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pmodel->meshindex);

	pstudioverts = (vec3_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pmodel->vertindex);
	pstudionorms = (vec3_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pmodel->normindex);

	pskinref = (short *)((Byte *)mdl->m_ptexturehdr + mdl->m_ptexturehdr->skinindex);
	if (mdl->m_skinnum != 0 && mdl->m_skinnum < mdl->m_ptexturehdr->numskinfamilies)
		pskinref += (mdl->m_skinnum * mdl->m_ptexturehdr->numskinref);

	for (i = 0; i < mdl->m_pmodel->numverts; i++)
	{
		VectorTransform (pstudioverts[i], mdl->g_bonetransform[pvertbone[i]], mdl->g_pxformverts[i]);
	}

//
// clip and draw all triangles
//

	lv = (float *)mdl->g_pvlightvalues;
	for (j = 0; j < mdl->m_pmodel->nummesh; j++) 
	{
		int flags;
		flags = ptexture[pskinref[pmesh[j].skinref]].flags;
		for (i = 0; i < pmesh[j].numnorms; i++, lv += 3, pstudionorms++, pnormbone++)
		{
			Lighting (mdl, &lv_tmp, *pnormbone, flags, (float *)pstudionorms);

			// FIX: move this check out of the inner loop
			if (flags & STUDIO_NF_CHROME)
				Chrome( mdl, mdl->g_chrome[(float (*)[3])lv - mdl->g_pvlightvalues], *pnormbone, (float *)pstudionorms );

			lv[0] = lv_tmp * g_lightcolor[0];
			lv[1] = lv_tmp * g_lightcolor[1];
			lv[2] = lv_tmp * g_lightcolor[2];
		}
	}

	glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	for (j = 0; j < mdl->m_pmodel->nummesh; j++) 
	{
		float s, t;
		short		*ptricmds;

		pmesh = (mstudiomesh_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pmodel->meshindex) + j;
		ptricmds = (short *)((Byte *)mdl->m_pstudiohdr + pmesh->triindex);

		mdl->m_polycount += pmesh->numtris;

		s = 1.0/(float)ptexture[pskinref[pmesh->skinref]].width;
		t = 1.0/(float)ptexture[pskinref[pmesh->skinref]].height;

		oglBindTexture( GL_TEXTURE_2D, ptexture[pskinref[pmesh->skinref]].index );

		fAlpha = 1.0f;
		glBlendFunc(GL_ONE,GL_ONE);
		glDisable(GL_BLEND);
		glAlphaFunc(GL_GREATER,0.5f);
		oglDisable(GL_ALPHA_TEST);

		if ( ptexture[pskinref[pmesh->skinref]].flags & STUDIO_NF_ADDITIVE )
		{
			fAlpha =  0.1f;
			glEnable(GL_BLEND);
		}
		if ( ptexture[pskinref[pmesh->skinref]].flags & STUDIO_NF_TRANSPARANT )
			oglEnable(GL_ALPHA_TEST);

		if (ptexture[pskinref[pmesh->skinref]].flags & STUDIO_NF_CHROME)
		{
			while (i = *(ptricmds++))
			{
				if (i < 0)
				{
					//glBegin( GL_TRIANGLE_FAN );
					primitive_type = GL_TRIANGLE_FAN;
					i = -i;
				}
				else
				{
					//glBegin( GL_TRIANGLE_STRIP );
					primitive_type = GL_TRIANGLE_STRIP;
				}

				vs = calloc(i * 3, sizeof(float));
				ts = calloc(i * 2, sizeof(float));
				cs = calloc(i * 4, sizeof(float));
				vertex_count = 0;

				for( ; i > 0; i--, ptricmds += 4)
				{
					// FIX: put these in as integer coords, not floats
					_COPY_TEXCOORD2(ts, vertex_count, mdl->g_chrome[ptricmds[1]][0]*s, mdl->g_chrome[ptricmds[1]][1]*t);
					
					lv = mdl->g_pvlightvalues[ptricmds[1]];
					_COPY_COLOR4( cs, vertex_count, lv[0], lv[1], lv[2], fAlpha );
					
					av = mdl->g_pxformverts[ptricmds[0]];
					_COPY_VERTEX3(vs, vertex_count, av[0], av[1], av[2]);

					vertex_count++;
				}
				karinDrawArrays(primitive_type, vertex_count, vs, 3, ts, 2, NULL, 3, cs, 4);
				free(vs);
				free(ts);
				free(cs);
			}	
		} 
		else 
		{		
			while (i = *(ptricmds++))
			{
				if (i < 0)
				{
					//glBegin( GL_TRIANGLE_FAN );
					primitive_type = GL_TRIANGLE_FAN;
					i = -i;
				}
				else
				{
					//glBegin( GL_TRIANGLE_STRIP );
					primitive_type = GL_TRIANGLE_STRIP;
				}

				vs = calloc(i * 3, sizeof(float));
				ts = calloc(i * 2, sizeof(float));
				cs = calloc(i * 4, sizeof(float));
				vertex_count = 0;

				for( ; i > 0; i--, ptricmds += 4)
				{
					// FIX: put these in as integer coords, not floats
					_COPY_TEXCOORD2(ts, vertex_count, ptricmds[2]*s, ptricmds[3]*t);
					
					lv = mdl->g_pvlightvalues[ptricmds[1]];
					_COPY_COLOR4(cs, vertex_count, lv[0], lv[1], lv[2], fAlpha );

					av = mdl->g_pxformverts[ptricmds[0]];
					_COPY_VERTEX3(vs, vertex_count, av[0], av[1], av[2]);
					vertex_count++;
				}
				karinDrawArrays(primitive_type, vertex_count, vs, 3, ts, 2, NULL, 3, cs, 4);
				free(vs);
				free(ts);
				free(cs);
			}	
		}
	}

	// karin
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glDepthFunc(GL_LESS);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#undef _COPY_VERTEX3
#undef _COPY_TEXCOORD2
#undef _COPY_COLOR4
}

mstudiotexture_t * GetMaterial(StudioModel *mdl, const char *name )
{
	if(!mdl || !name)
		return NULL;

	int i;

	mstudiotexture_t *pTextures;

	pTextures=(mstudiotexture_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pstudiohdr->textureindex);
	for ( i = 0; i < mdl->m_pstudiohdr->numtextures; i++ )
	{
		if ( strcmp(pTextures[i].name, name) == 0 )
		{
			return &pTextures[i];
		}
	}
	return NULL;
}

float SetFrame( StudioModel *mdl, float frame)
{
	if(!mdl)
		return 0.0;
	mstudioseqdesc_t	*pseqdesc;
	pseqdesc = (mstudioseqdesc_t *)((Byte *)mdl->m_pstudiohdr + mdl->m_pstudiohdr->seqindex) + mdl->m_sequence;

	if (pseqdesc->numframes <= 1)
	{
		mdl->m_frame = 0;
	}
	else
	{
		float mframe = frame;
		if(mframe > pseqdesc->numframes - 1)
			mdl->m_frame = pseqdesc->numframes - 1;
		else if(mframe < 0)
			mdl->m_frame = 0;
		else
			mdl->m_frame = frame;
	}
	return mdl->m_frame;
}

