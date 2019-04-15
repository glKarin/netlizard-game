#ifndef _KARIN_SHADOW_H
#define _KARIN_SHADOW_H

#include "math3d/vector.h"
#include "mesh.h"
#include "math3d/matrix.h"
#include "nl_gl.h"
#include "lightsource.h"

#define SHADOW_VOLUME_LENGTH 500000
#define SHADOW_VOLUME_FAR_W 1
#define DIR_LIGHTING 0
#define ZFAIL_SHADOW 0 // using Z-Fail
#define SHADOW_MASK 1 // 
#define SHADOW_MASK_LIGHT 0 // 

#define SHADOW_Z_PASS 0
#define SHADOW_Z_FAIL 1

vector3_s Algo_LightingDir(const vector3_s *v, const vector3_s *lightpos, int dirlight);
void Shadow_MakeVolume(mesh_s *r, const Light_Source_s *light, const material_s *mat, int m);
void Shadow_RenderVolume(const material_s *nl_mesh, const Light_Source_s *l, int method);

void Shadow_CaleTrans(material_s *r, const GL_NETLizard_3D_Mesh *src, const matrix44_s *mat, int invert);
void Shadow_RenderItemShadow(const GL_NETLizard_3D_Item_Mesh *mesh, const Light_Source_s *light, int method);
void Shadow_RenderShadow(const GL_NETLizard_3D_Mesh *mesh, const Light_Source_s *light, int method);

#endif
