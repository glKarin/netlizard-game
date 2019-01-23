#include "studio_game.h"


void Shadow_DrawPoints(const StudioModel *mdl)
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

#define _COPY_NORMAL(v, i, x, y, z) \
(v)[(i) * 3] = (x); \
(v)[(i) * 3 + 1] = (y); \
(v)[(i) * 3 + 2] = (z);

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

#undef _COPY_VERTEX3
#undef _COPY_NORMAL
}

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
