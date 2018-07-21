#ifndef _KARIN_HLSDK_STUDIO_MODEL_H
#define _KARIN_HLSDK_STUDIO_MODEL_H

#include "studio.h"

/*
	 studiohdr_t				StudioHeader
	 mstudiomodel_t			StudioModel
	 studiohdr_t				TextureHeader
	 studioseqhdr_t			AnimHeader
	 */
typedef struct _StudioModel
{
		// entity settings
		vec3_t					m_origin;
		vec3_t					m_angles;	
		int						m_sequence;			// sequence index
		float					m_frame;			// frame
		int						m_bodynum;			// bodypart selection	
		int						m_skinnum;			// skin group selection
		Byte					m_controller[4];	// bone controllers
		Byte					m_blending[2];		// animation blending
		Byte					m_mouth;			// mouth position
		bool					m_owntexmodel;		// do we have a modelT.mdl ?
		int						m_selhitbox;
		int						m_selbone;
		long					m_polycount;
		float					g_bonetransform[MAXSTUDIOBONES][3][4];	// bone transformation matrix

		Byte					*CoreFile;
		int						CoreFileLength;

		Byte					*SequenceFiles[32];
		int						SequenceFilesLength[32];

		Byte					*TextureFile;
		int						TextureFileLength;

		int						*pSavedTIndexes;	// pointer to buffer where saved textureindexes are put for modelsave...

		// internal data
		studiohdr_t				*m_pstudiohdr;
		mstudiomodel_t			*m_pmodel;

		studiohdr_t				*m_ptexturehdr;
		studioseqhdr_t			*m_panimhdr[32];

		vec4_t					m_adj;				// FIX: non persistant, make static

		vec3_t			g_xformverts[MAXSTUDIOVERTS];	// transformed vertices
		vec3_t			g_lightvalues[MAXSTUDIOVERTS];	// light surface normals
		vec3_t			*g_pxformverts;
		vec3_t			*g_pvlightvalues;

		vec3_t			g_blightvec[MAXSTUDIOBONES];	// light vectors in bone reference frames

		int				g_smodels_total;				// cookie


		int				g_chrome[MAXSTUDIOVERTS][2];	// texture coords for surface normals
		int				g_chromeage[MAXSTUDIOBONES];	// last time chrome vectors were updated
		vec3_t			g_chromeup[MAXSTUDIOBONES];		// chrome vector "up" in bone reference frames
		vec3_t			g_chromeright[MAXSTUDIOBONES];	// chrome vector "right" in bone reference frames


} StudioModel;

void FreeModel (StudioModel *mdl);
bool LoadModel( StudioModel *mdl, const char *modelname );
bool SaveModel( const StudioModel *mdl, const char *modelname );
bool LoadTextures( StudioModel *mdl, const char *modelname );
bool LoadDemandSequence( StudioModel *mdl, const char *modelname, int index );
bool Init( StudioModel *mdl, const char *modelname );
mstudioseqdesc_t * GetSequence( StudioModel *mdl, const char *name, int *index );
mstudioevent_t * GetEvent( StudioModel *mdl, const char *seqname );
int SetSequence( StudioModel *mdl, int iSequence );
void ExtractBbox( const StudioModel *mdl, float *mins, float *maxs );
void GetSequenceInfo( const StudioModel *mdl, float *pflFrameRate, float *pflGroundSpeed );
float SetController( StudioModel *mdl, int iController, float flValue );
float SetMouth( StudioModel *mdl, float flValue );
float SetBlending( StudioModel *mdl, int iBlender, float flValue );
int SetBodygroup( StudioModel *mdl, int iGroup, int iValue );
int SetSkin( StudioModel *mdl, int iValue );
char ** GetSequenceNames( const StudioModel *mdl, unsigned int *count );

float					GetFrame( void );
//void					SetFrame( int frame );
void					SetSelHitbox( int index );
void					SetSelBone( int index );
long					GetPolyCount();
#endif
