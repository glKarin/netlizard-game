#include "ct3d_reader.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// ct 3d konon version by serviak

#define dprintfsi(s, d) nlprintf("CT 3D : "#s" -> %d\n", d)
#define dprintfsii(s, d, d2) nlprintf("CT 3D : ""%d - "#s" -> %d\n", d, d2)
#define dprintfss(s) nlprintf("CT 3D : "#s"\n")

typedef struct _class__f__scene
{
  array* int_array_6__a__vertex;
  array* int_array_10__b__primitive;
  int c;
  int d;
  int int__e__end;// = 0; 最后一个物品索引
  int int__f__aabb;
  int int__g__aabb;
  int int__h__aabb;
  int int__i__aabb;
  int int__j__aabb;
  int int__k__aabb;
  array* int_array_6__l__plane;
  int m;
  int n;
  int o;
  int int_array_5__p__bsp[5];
  int int__q__bsp;// = 0;
  int int__r__begin;// = 0; 第一个物品索引
} class__f__scene;

typedef struct _class__b__bsp
{
  byte byte__a__direction;
	int int_array_3__a__normal[3];
  int int_array_4x3__b__plane[4][3]; //i[] b = new i[4];
  int int__c__prev_scene;
  int int__d__next_scene;
  boolean e; // = false;
} class__b__bsp;

typedef struct _class__g__item
{
  array *int_array_6__a__vertex;
  array *int_array_16__b__primitive;
  int** c;
  short d;
  int e;
  int int__f__aabb;
  int int__g__aabb;
  int int__h__aabb;
  int int__i__aabb;
  int int__j__aabb;
  int int__k__aabb;
  byte l;// = -1;
  int int__m__translation;// = 40960000;
  int int__n__translation;// = 40960000;
  int int__o__translation;// = 8192000;
  int int__p__rotation;// = 0;
  int int__q__rotation;// = 0;
  short r;
  byte byte__s__obj;
  int t;//boolean t = true;
} class__g__item;

typedef struct _class__h__lvl
{
	array *class_f_array__l__scene;
	array *class_g_array__h__item;
	int int_array__dg__translation[3];
	int int__dd__rotation;
	int int__df__rotation;
	array *class_b_array__j__bsp;
} class__h__lvl;

static class__h__lvl * class_h__function_k_void__scene(const byte arrayOfByte[]);
static void class_h__function_S_void__item(class__g__item *h, const byte arrayOfByte[]);
static void nlReadCT3DMapItems(array *class_g_array__h__item);

#if 0
void testtt4(class__f__scene *l, class__b__bsp *j, int scene, int max, int *scenes, byte dir)
{
	int ii;
	for(ii = 0; ii < l[scene].int__q__bsp; ii++)
	{
		int bsp_i = l[scene].int_array_5__p__bsp[ii];
		int p = j[bsp_i].int__c__prev_scene;
		int n = j[bsp_i].int__d__next_scene;
		byte a = j[bsp_i].byte__a__direction;
		if(a == dir)
		{
			int k;
			for(k = 0; k < max; k++)
			{
				if(scenes[k] == p)
					break;
				if(scenes[k] == -1)
				{
					scenes[k] = p;
					testtt4(l, j, p, max, scenes, a);
					break;
				}
			}
			for(k = 0; k < max; k++)
			{
				if(scenes[k] == n)
					break;
				if(scenes[k] == -1)
				{
					scenes[k] = n;
					testtt4(l, j, n, max, scenes, a);
					break;
				}
			}
		}
	}
}

void testtt3(class__f__scene *l, class__b__bsp *j, int scene, int max, int *scenes)
{
	int ii;
	for(ii = 0; ii < l[scene].int__q__bsp; ii++)
	{
		int bsp_i = l[scene].int_array_5__p__bsp[ii];
		int p = j[bsp_i].int__c__prev_scene;
		int n = j[bsp_i].int__d__next_scene;
		byte a = j[bsp_i].byte__a__direction;
		int k;
		for(k = 0; k < max; k++)
		{
			if(scenes[k] == p)
				break;
			if(scenes[k] == -1)
			{
				scenes[k] = p;
				testtt4(l, j, p, max, scenes, a);
				break;
			}
		}
		for(k = 0; k < max; k++)
		{
			if(scenes[k] == n)
				break;
			if(scenes[k] == -1)
			{
				scenes[k] = n;
				testtt4(l, j, n, max, scenes, a);
				break;
			}
		}
	}
}

void testtt2(class__f__scene *l, class__b__bsp *j, int scene, int max, int *scenes)
{
	int ii;
	for(ii = 0; ii < l[scene].int__q__bsp; ii++)
	{
		int bsp_i = l[scene].int_array_5__p__bsp[ii];
		int p = j[bsp_i].int__c__prev_scene;
		int n = j[bsp_i].int__d__next_scene;
		byte a = j[bsp_i].byte__a__direction;
		int k;
		for(k = 0; k < max; k++)
		{
			if(scenes[k] == p)
				break;
			if(scenes[k] == -1)
			{
				scenes[k] = p;
				testtt3(l, j, p, max, scenes);
				break;
			}
		}
		for(k = 0; k < max; k++)
		{
			if(scenes[k] == n)
				break;
			if(scenes[k] == -1)
			{
				scenes[k] = n;
				testtt3(l, j, n, max, scenes);
				break;
			}
		}
	}
}

void testtt(class__f__scene *l, class__b__bsp *j, int scene, int max)
{
	int *scenes = NEW_II(int, max);
	int i;
	for(i = 0; i < max; i++)
		scenes[i] = -1;
	printf("[");
	printf("  %d ----> \n", scene);
	// get under the target bsp node
	int ii;
	for(ii = 0; ii < l[scene].int__q__bsp; ii++)
	{
		int bsp_i = l[scene].int_array_5__p__bsp[ii];
		int p = j[bsp_i].int__c__prev_scene;
		int n = j[bsp_i].int__d__next_scene;
		int k;
		for(k = 0; k < max; k++)
		{
			if(scenes[k] == p)
				break;
			if(scenes[k] == -1)
			{
				scenes[k] = p;
				testtt2(l, j, p, max, scenes);
				break;
			}
		}

		for(k = 0; k < max; k++)
		{
			if(scenes[k] == n)
				break;
			if(scenes[k] == -1)
			{
				scenes[k] = n;
				testtt2(l, j, n, max, scenes);
				break;
			}
		}
		byte a = j[bsp_i].byte__a__direction;
	}
	int k;
	for(k = 0; k < max; k++)
	{
		if(scenes[k] != -1 && scenes[k] != scene)
		{
			printf(" %d", scenes[k]);
		}
	}
	printf("\n]\n");
}
#endif

NETLizard_3D_Model * nlReadCT3DModelFile(const char* name, int level)
{
	if(!name)
		return NULL;
	array *arr = nlReadFile(name);
	if(!arr)
		return NULL;
	int paramInt = level;
	int dr = 0;
	if ((paramInt == 3) || (paramInt == 4) || (paramInt == 5) || (paramInt == 7)) {
		dr = 1;
	}
	byte *arrayOfByte = (byte *)(arr -> array);
	class__h__lvl *lv = class_h__function_k_void__scene(arrayOfByte);
	if(!lv)
		return NULL;
	NETLizard_3D_Model *model = NEW(NETLizard_3D_Model);
	ZERO(model, NETLizard_3D_Model);
	array *l = lv -> class_f_array__l__scene;
	model -> data = new_array(nl_user, l -> length, NULL, sizeof(NETLizard_3D_Mesh));
	model -> has_sky = dr;
	model -> game = CT_3D_Map;

	int i;
	for(i = 0; i < l -> length; i++)
	{
		NETLizard_3D_Mesh *mesh = ((NETLizard_3D_Mesh *)(model -> data -> array)) + i;
		class__f__scene *obj = ((class__f__scene *)(l -> array)) + i;
		mesh -> vertex = new_array(nl_int, obj -> int_array_6__a__vertex -> length / 2, NULL, 0);
		int j;
		int *m_v = (int *)(mesh -> vertex -> array);
		int *s_a = (int *)(obj -> int_array_6__a__vertex -> array);
		int k = 0;
		for(j = 0; j < obj -> int_array_6__a__vertex -> length; j += 6)
		{
			m_v[k] = s_a[j] >> 16;
			m_v[k + 1] = s_a[j + 1] >> 16;
			m_v[k + 2] = s_a[j + 2] >> 16;
			k += 3;
		}
		mesh -> primitive = new_array(nl_user, obj -> int_array_10__b__primitive -> length / 10, NULL, sizeof(NETLizard_3D_Primitive));
		int *s_b = (int *)(obj -> int_array_10__b__primitive -> array);
		k = 0;
		for(j = 0; j < obj -> int_array_10__b__primitive -> length; j += 10)
		{
			NETLizard_3D_Primitive *p = ((NETLizard_3D_Primitive *)(mesh -> primitive -> array)) + k;
			p -> index[0] = s_b[j] / 6;
			p -> index[1] = s_b[j + 1] / 6;
			p -> index[2] = s_b[j + 2] / 6;
			p -> texcoord[0] = s_b[j + 3];
			p -> texcoord[1] = s_b[j + 4];
			p -> texcoord[2] = s_b[j + 5];
			p -> texcoord[3] = s_b[j + 6];
			p -> texcoord[4] = s_b[j + 7];
			p -> texcoord[5] = s_b[j + 8];
			p -> tex_index = s_b[j + 9];
			k++;
		}
		mesh -> plane = new_array(nl_user, obj -> int_array_6__l__plane -> length / 6, NULL, sizeof(NETLizard_3D_Plane));
		int *s_l = (int *)(obj -> int_array_6__l__plane -> array);
		k = 0;
		for(j = 0; j < obj -> int_array_6__l__plane -> length; j += 6)
		{
			NETLizard_3D_Plane *p = ((NETLizard_3D_Plane *)(mesh -> plane -> array)) + k;
			p -> position[0] = s_l[j] >> 16;
			p -> position[1] = s_l[j + 1] >> 16;
			p -> position[2] = s_l[j + 2] >> 16;
			p -> normal[0] = s_l[j + 3];
			p -> normal[1] = s_l[j + 4];
			p -> normal[2] = s_l[j + 5];
			k++;
		}
		mesh -> ortho[0] = obj -> int__f__aabb >> 16;
		mesh -> ortho[1] = obj -> int__g__aabb >> 16;
		mesh -> ortho[2] = obj -> int__h__aabb >> 16;
		mesh -> ortho[3] = obj -> int__i__aabb >> 16;
		mesh -> ortho[4] = obj -> int__j__aabb >> 16;
		mesh -> ortho[5] = obj -> int__k__aabb >> 16;
		mesh -> item_index_range[0] = obj -> int__r__begin;
		mesh -> item_index_range[1] = obj -> int__e__end;

		mesh -> bsp = NULL;
		if(obj -> int__q__bsp)
		{
			mesh -> bsp = new_array(nl_int, obj -> int__q__bsp, NULL, 0);
			int *bsp_index = (int *)(mesh -> bsp -> array);
			for(j = 0; j < obj -> int__q__bsp; j++)
			{
				bsp_index[j] = obj -> int_array_5__p__bsp[j];
			}
		}
	}

	array *h = lv -> class_g_array__h__item;
	model -> item_data = new_array(nl_user, h -> length, NULL, sizeof(NETLizard_3D_Item_Mesh));
	for(i = 0; i < h -> length; i++)
	{
		NETLizard_3D_Item_Mesh *mesh = ((NETLizard_3D_Item_Mesh *)(model -> item_data -> array)) + i;
		class__g__item *obj = ((class__g__item *)(h -> array)) + i;
		if(!obj -> int_array_6__a__vertex || !obj -> int_array_16__b__primitive)
		{
			mesh -> item_mesh.vertex = NULL;
			mesh -> item_mesh.primitive = NULL;
			continue;
		}
		mesh -> pos[0] = obj -> int__m__translation >> 16;
		mesh -> pos[1] = obj -> int__n__translation >> 16;
		mesh -> pos[2] = obj -> int__o__translation >> 16;
		mesh -> angle[0] = obj -> int__p__rotation;
		mesh -> angle[1] = obj -> int__q__rotation;
		mesh -> obj_index = obj -> byte__s__obj;
		mesh -> item_mesh.vertex = new_array(nl_int, obj -> int_array_6__a__vertex -> length / 2, NULL, 0);
		int j;
		int *im_a = (int *)(mesh -> item_mesh.vertex -> array);
		int *i_a = (int *)(obj -> int_array_6__a__vertex -> array);
		int k = 0;
		for(j = 0; j < obj -> int_array_6__a__vertex -> length; j += 6)
		{
			im_a[k] = i_a[j] >> 16;
			im_a[k + 1] = i_a[j + 1] >> 16;
			im_a[k + 2] = i_a[j + 2] >> 16;
			k += 3;
		}
		mesh -> item_mesh.primitive = new_array(nl_user, obj -> int_array_16__b__primitive -> length / 16, NULL, sizeof(NETLizard_3D_Primitive));
		k = 0;
		int *i_b = (int *)(obj -> int_array_16__b__primitive -> array);
		for(j = 0; j < obj -> int_array_16__b__primitive -> length; j += 16)
		{
			NETLizard_3D_Primitive *p = ((NETLizard_3D_Primitive *)(mesh -> item_mesh.primitive -> array)) + k;
			p -> index[0] = i_b[j] / 6;
			p -> index[1] = i_b[j + 1] / 6;
			p -> index[2] = i_b[j + 2] / 6;
			p -> texcoord[0] = i_b[j + 3];
			p -> texcoord[1] = i_b[j + 4];
			p -> texcoord[2] = i_b[j + 5];
			p -> texcoord[3] = i_b[j + 6];
			p -> texcoord[4] = i_b[j + 7];
			p -> texcoord[5] = i_b[j + 8];
			p -> tex_index = i_b[j + 9];
			p -> plane.position[0] = i_a[p -> index[0]] >> 16;
			p -> plane.position[1] = i_a[p -> index[0] + 1] >> 16;
			p -> plane.position[2] = i_a[p -> index[0] + 2] >> 16;
			p -> plane.normal[0] = i_b[j + 10];
			p -> plane.normal[1] = i_b[j + 11];
			p -> plane.normal[2] = i_b[j + 12];
			k++;
		}
		mesh -> item_mesh.ortho[0] = obj -> int__f__aabb >> 16;
		mesh -> item_mesh.ortho[1] = obj -> int__g__aabb >> 16;
		mesh -> item_mesh.ortho[2] = obj -> int__h__aabb >> 16;
		mesh -> item_mesh.ortho[3] = obj -> int__i__aabb >> 16;
		mesh -> item_mesh.ortho[4] = obj -> int__j__aabb >> 16;
		mesh -> item_mesh.ortho[5] = obj -> int__k__aabb >> 16;
	}

	model -> bsp_data = NULL;
	if(lv -> class_b_array__j__bsp)
	{
		class__b__bsp *bsp = (class__b__bsp *)(lv -> class_b_array__j__bsp -> array);
		model -> bsp_data = new_array(nl_user, lv -> class_b_array__j__bsp -> length, NULL, sizeof(NETLizard_BSP_Tree_Node));
		NETLizard_BSP_Tree_Node *bsp_data = (NETLizard_BSP_Tree_Node *)(model -> bsp_data -> array);
		int j;
		for(j = 0; j < lv -> class_b_array__j__bsp -> length; j++)
		{
			int k;
			for(k = 0; k < 4; k++)
			{
				bsp_data[j].plane[k][0] = bsp[j].int_array_4x3__b__plane[k][0] >> 16;
				bsp_data[j].plane[k][1] = bsp[j].int_array_4x3__b__plane[k][1] >> 16;
				bsp_data[j].plane[k][2] = bsp[j].int_array_4x3__b__plane[k][2] >> 16;
			}
			bsp_data[j].direction = bsp[j].byte__a__direction;
			bsp_data[j].prev_scene = bsp[j].int__c__prev_scene;
			bsp_data[j].next_scene = bsp[j].int__d__next_scene;
			bsp_data[j].normal[0] = bsp[j].int_array_3__a__normal[0];
			bsp_data[j].normal[1] = bsp[j].int_array_3__a__normal[1];
			bsp_data[j].normal[2] = bsp[j].int_array_3__a__normal[2];
		}
	}

	model -> start_angle[0] = lv -> int__dd__rotation;
	model -> start_angle[1] = lv -> int__df__rotation;
	model -> start_pos[0] = lv -> int_array__dg__translation[0] >> 16;
	model -> start_pos[1] = lv -> int_array__dg__translation[1] >> 16;
	model -> start_pos[2] = lv -> int_array__dg__translation[2] >> 16;

	for(i = 0; i < l -> length; i++)
	{
		class__f__scene *obj = ((class__f__scene *)(l -> array)) + i;
		delete_array(obj -> int_array_6__a__vertex);
		delete_array(obj -> int_array_10__b__primitive);
		delete_array(obj -> int_array_6__l__plane);
		free(obj -> int_array_6__a__vertex);
		free(obj -> int_array_10__b__primitive);
		free(obj -> int_array_6__l__plane);
	}
	delete_array(l);
	free(l);
	for(i = 0; i < h -> length; i++)
	{
		class__g__item *obj = ((class__g__item *)(h -> array)) + i;
		delete_array(obj -> int_array_6__a__vertex);
		delete_array(obj -> int_array_16__b__primitive);
		free(obj -> int_array_6__a__vertex);
		free(obj -> int_array_16__b__primitive);
	}
	delete_array(lv -> class_b_array__j__bsp);
	free(lv -> class_b_array__j__bsp);
	delete_array(h);
	free(h);
	free(lv);
	return model;
}

NETLizard_3D_Model * nlReadCT3DItemModelFile(const char* name, int index)
{
	if(!name)
		return NULL;
	array *arr = nlReadFile(name);
	if(!arr)
		return NULL;
	NETLizard_3D_Model *model = NEW(NETLizard_3D_Model);
	ZERO(model, NETLizard_3D_Model);

	class__g__item obj;
	class_h__function_S_void__item(&obj, arr -> array);
	array *item_meshes = new_array(nl_user, 1, NULL, sizeof(NETLizard_3D_Item_Mesh));
	NETLizard_3D_Item_Mesh *mesh = ((NETLizard_3D_Item_Mesh *)(item_meshes -> array));
	mesh -> item_mesh.vertex = NULL;
	mesh -> item_mesh.primitive = NULL;
	mesh -> pos[0] = 0;
	mesh -> pos[1] = 0;
	mesh -> pos[2] = 0;
	mesh -> angle[0] = 0;
	mesh -> angle[1] = 0;
	mesh -> obj_index = index;
	if(obj.int_array_6__a__vertex && obj.int_array_16__b__primitive)
	{
		mesh -> item_mesh.vertex = new_array(nl_int, obj.int_array_6__a__vertex -> length / 2, NULL, 0);
		int j;
		int *im_v = (int *)(mesh -> item_mesh.vertex -> array);
		int *i_a = (int *)(obj.int_array_6__a__vertex -> array);
		int k = 0;
		for(j = 0; j < obj.int_array_6__a__vertex -> length; j += 6)
		{
			im_v[k] = i_a[j] >> 16;
			im_v[k + 1] = i_a[j + 1] >> 16;
			im_v[k + 2] = i_a[j + 2] >> 16;
			k += 3;
		}
		mesh -> item_mesh.primitive = new_array(nl_user, obj.int_array_16__b__primitive -> length / 16, NULL, sizeof(NETLizard_3D_Primitive));
		int *i_b = (int *)(obj.int_array_16__b__primitive -> array);
		k = 0;
		for(j = 0; j < obj.int_array_16__b__primitive -> length; j += 16)
		{
			NETLizard_3D_Primitive *p = ((NETLizard_3D_Primitive *)(mesh -> item_mesh.primitive -> array)) + k;
			p -> index[0] = i_b[j] / 6;
			p -> index[1] = i_b[j + 1] / 6;
			p -> index[2] = i_b[j + 2] / 6;
			p -> texcoord[0] = i_b[j + 3];
			p -> texcoord[1] = i_b[j + 4];
			p -> texcoord[2] = i_b[j + 5];
			p -> texcoord[3] = i_b[j + 6];
			p -> texcoord[4] = i_b[j + 7];
			p -> texcoord[5] = i_b[j + 8];
			p -> tex_index = i_b[j + 9];
			p -> plane.position[0] = i_a[p -> index[0]] >> 16;
			p -> plane.position[1] = i_a[p -> index[0] + 1] >> 16;
			p -> plane.position[2] = i_a[p -> index[0] + 2] >> 16;
			p -> plane.normal[0] = i_b[j + 10];
			p -> plane.normal[1] = i_b[j + 11];
			p -> plane.normal[2] = i_b[j + 12];
			k++;
		}
		mesh -> item_mesh.ortho[0] = obj.int__f__aabb >> 16;
		mesh -> item_mesh.ortho[1] = obj.int__g__aabb >> 16;
		mesh -> item_mesh.ortho[2] = obj.int__h__aabb >> 16;
		mesh -> item_mesh.ortho[3] = obj.int__i__aabb >> 16;
		mesh -> item_mesh.ortho[4] = obj.int__j__aabb >> 16;
		mesh -> item_mesh.ortho[5] = obj.int__k__aabb >> 16;
	}

	delete_array(obj.int_array_6__a__vertex);
	delete_array(obj.int_array_16__b__primitive);
	free(obj.int_array_6__a__vertex);
	free(obj.int_array_16__b__primitive);
	delete_array(arr);
	free(arr);
	model -> data = NULL;
	model -> item_data = item_meshes;
	model -> has_sky = 0;
	model -> game = CT_3D_Item;
	return model;
}

void nlReadCT3DMapItems(array *class_g_array__h__item)
{
	if(!class_g_array__h__item)
		return;
	int i;
	for(i = 0; i < class_g_array__h__item -> length; i++)
	{
		class__g__item *h = ((class__g__item *)(class_g_array__h__item -> array)) + i;
		int i11 = h -> byte__s__obj;
		if ((i11 != 0) || (i11 == 55))
		{
			char subfix[strlen(CT3D_OBJ_SUBFIX) + 1];
			memset(subfix, '\0', sizeof(char) * (strlen(subfix) + 1));
			sprintf(subfix, CT3D_OBJ_SUBFIX, i11);
			char *name = NULL;
			if(game_resource_path[nl_contr_terrorism_3d])
			{
				name = NEW_II(char, strlen(subfix) + strlen(game_resource_path[nl_contr_terrorism_3d]) + 1 + 1);
				memset(name, '\0', sizeof(char) * ((strlen(subfix) + strlen(game_resource_path[nl_contr_terrorism_3d]) + 1 + 1)));
				sprintf(name, "%s/%s", game_resource_path[nl_contr_terrorism_3d], subfix);
			}
			else
				name = strdup(subfix);
			array *arr = nlReadFile(name);
			free(name);
			if(arr)
			{
				class_h__function_S_void__item(h, arr -> array);
				delete_array(arr);
				free(arr);
			}
			else
			{
				h -> int_array_6__a__vertex = NULL;
				h -> int_array_16__b__primitive = NULL;
			}
		}
		else
		{
			h -> int_array_6__a__vertex = NULL;
			h -> int_array_16__b__primitive = NULL;
		}
	}
}

/* ****** static ****** */

class__h__lvl * class_h__function_k_void__scene(const byte arrayOfByte[])
{
	if(!arrayOfByte)
		return NULL;
	byte cO;
	int cZ;
	int cA;
	int dg[3];
	int dd;
	int df;

	int i1 = -2;
	i1 += 2;
	cO = ((byte)(nlMargeDigit(arrayOfByte[0], arrayOfByte[1]) - 1));
	i1 += 2;
	dg[0] = (nlMargeDigit(arrayOfByte[2], arrayOfByte[3]) << 16);
	i1 += 2;
	dg[1] = (nlMargeDigit(arrayOfByte[4], arrayOfByte[5]) << 16);
	i1 += 2;
	dg[2] = (nlMargeDigit(arrayOfByte[6], arrayOfByte[7]) << 16);
	i1 += 2;
	dd = nlMargeDigit(arrayOfByte[8], arrayOfByte[9]);
	i1 += 2;
	df = nlMargeDigit(arrayOfByte[10], arrayOfByte[11]);
	if (df > 361) {
		df -= 65536;
	}
	if (dd > 361) {
		dd -= 65536;
	}
	if (df < 0) {
		df = -df;
	} else {
		df = 360 - df;
	}
	if (df == 360) {
		df = 0;
	}
	if (dd < 0) {
		dd = 270 + dd;
	} else {
		dd = 270 - dd;
	}
	if (dd == 360) {
		dd = 0;
	}
	dprintfss("Get start position and axis");
	i1 += 2;
	cZ = nlMargeDigit(arrayOfByte[12], arrayOfByte[13]);
	dprintfsi("Map scene count", cZ);

	array *class_f_array__l__scene = new_array(nl_user, cZ, NULL, sizeof(class__f__scene));
	class__f__scene *l = (class__f__scene *)(class_f_array__l__scene -> array);
	int i20;
	int i25;
	int i15;
	for (i15 = 0; i15 < cZ; i15++)
	{
		dprintfsi("Get map scene data", i15);
		int i13 = 0;
		i1 += 2;
		l[i15].int__f__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		l[i15].int__g__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		l[i15].int__h__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		l[i15].int__i__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		l[i15].int__j__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		l[i15].int__k__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		dprintfss("Get scene AABB");
		i1 += 2;
		int i9 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
		dprintfsi("Scene vertex coord count", i9);
		i1 += 2;
		int i8 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
		dprintfsi("Scene primitive count", i8);
		i1 += 2;
		int i10 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
		l[i15].int_array_6__a__vertex = new_array(nl_int, i9 * 6, NULL, 0);
		int *a = (int *)(l[i15].int_array_6__a__vertex -> array);
		l[i15].n = i9;
		l[i15].int_array_10__b__primitive = new_array(nl_int, i8 * 10, NULL, 0);
		int *b = (int *)(l[i15].int_array_10__b__primitive -> array);
		l[i15].o = i8;
		i10 *= 2;
		int *arrayOfInt2 = NEW_II(int, i8 * 3);
		int *arrayOfInt1 = NEW_II(int, i10);
		dprintfsi("Map normal count", i8);
		dprintfsi("Texcoord count", i10);
		int i16;
		for (i16 = 0; i16 < i9; i16++)
		{
			i1 += 2;
			a[(i16 * 6)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			a[(i16 * 6 + 1)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			a[(i16 * 6 + 2)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		}
		dprintfss("Get scene vertex coord");
		int i17;
		for (i17 = 0; i17 < i8; i17++)
		{
			i1 += 2;
			b[(i17 * 10)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
			i1 += 2;
			b[(i17 * 10 + 1)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
			i1 += 2;
			b[(i17 * 10 + 2)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
		}
		dprintfss("Get scene primitive vertex coord index");
		int i18;
		for (i18 = 0; i18 < i8; i18++)
		{
			i1 += 2;
			arrayOfInt2[(i18 * 3)] = ((int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
			i1 += 2;
			arrayOfInt2[(i18 * 3 + 1)] = ((int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
			i1 += 2;
			arrayOfInt2[(i18 * 3 + 2)] = ((int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
		}
		dprintfss("Get map normal");
		int i12 = 0;
		int i19;
		for (i19 = 0; i19 < i8; i19++)
		{
			int i14 = 1;
			for (i20 = i19 + 1; i20 < i8; i20++) {
				if ((arrayOfInt2[(i19 * 3)] == arrayOfInt2[(i20 * 3)]) && (arrayOfInt2[(i19 * 3 + 1)] == arrayOfInt2[(i20 * 3 + 1)]) && (arrayOfInt2[(i19 * 3 + 2)] == arrayOfInt2[(i20 * 3 + 2)]))
				{
					arrayOfInt2[(i19 * 3)] = 0;
					arrayOfInt2[(i19 * 3 + 1)] = 0;
					arrayOfInt2[(i19 * 3 + 2)] = 0;
					i14 = 0;
					break;
				}
			}
			if (i14 != 0) {
				i12++;
			}
		}
		dprintfsi("Scene plane count", i12);
		l[i15].int_array_6__l__plane = new_array(nl_int, i12 * 6, NULL, 0);
		int *sub_l = (int *)(l[i15].int_array_6__l__plane -> array);
		l[i15].m = (i12 * 6 - 6);
		int i20;
		for (i20 = 0; i20 < i8; i20++) {
			if ((arrayOfInt2[(i20 * 3)] != 0) || (arrayOfInt2[(i20 * 3 + 1)] != 0) || (arrayOfInt2[(i20 * 3 + 2)] != 0))
			{
				sub_l[(i13 * 6)] = a[b[(i20 * 10)]];
				sub_l[(i13 * 6 + 1)] = a[(b[(i20 * 10)] + 1)];
				sub_l[(i13 * 6 + 2)] = a[(b[(i20 * 10)] + 2)];
				sub_l[(i13 * 6 + 3)] = arrayOfInt2[(i20 * 3)];
				sub_l[(i13 * 6 + 4)] = arrayOfInt2[(i20 * 3 + 1)];
				sub_l[(i13 * 6 + 5)] = arrayOfInt2[(i20 * 3 + 2)];
				i13++;
			}
		}
		dprintfss("Get scene plane normal index and point vertex coord index");
		// ??? + >>
		l[i15].c = ((l[i15].int__f__aabb + l[i15].int__i__aabb) >> 1);
		l[i15].d = ((l[i15].int__g__aabb + l[i15].int__j__aabb) >> 1);
		int *arrayOfInt3 = (int *)(l[i15].int_array_6__l__plane -> array);
		int i25;
		for (i25 = l[i15].m; i25 >= 0; i25 -= 6)
		{
			long l1;
			if ((l1 = (arrayOfInt3[(i25 + 3)] * (l[i15].c - arrayOfInt3[i25]) + arrayOfInt3[(i25 + 4)] * (l[i15].d - arrayOfInt3[(i25 + 1)])) >> 16) < 8192000L)
			{
				long l2 = 8192000L - l1;
				class__f__scene *tmp1584_1583 = l + i15;
				tmp1584_1583 -> c = ((int)(tmp1584_1583 -> c + (arrayOfInt3[(i25 + 3)] * l2 >> 16)));
				class__f__scene *tmp1614_1613 = l + i15;
				tmp1614_1613 -> d = ((int)(tmp1614_1613 -> d + (arrayOfInt3[(i25 + 4)] * l2 >> 16)));
			}
		}
		int i26;
		for (i26 = 0; i26 < i10; i26 += 2)
		{
			i1 += 2;
			arrayOfInt1[i26] = ((int)(64 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 100L));
			i1 += 2;
			arrayOfInt1[(i26 + 1)] = ((int)(64 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 100L));
		}
		dprintfss("Get map texcoord");
		int i27;
		for (i27 = 0; i27 < i8; i27++)
		{
			i1 += 2;
			b[(i27 * 10 + 3)] = ((short)arrayOfInt1[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)]);
			b[(i27 * 10 + 4)] = ((short)arrayOfInt1[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)]);
			i1 += 2;
			b[(i27 * 10 + 5)] = ((short)arrayOfInt1[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)]);
			b[(i27 * 10 + 6)] = ((short)arrayOfInt1[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)]);
			i1 += 2;
			b[(i27 * 10 + 7)] = ((short)arrayOfInt1[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)]);
			b[(i27 * 10 + 8)] = ((short)arrayOfInt1[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)]);
		}
		dprintfss("Get scene texcoord");
		int i28;
		for (i28 = 0; i28 < i8; i28++)
		{
			i1 += 2;
			b[(i28 * 10 + 9)] = ((byte)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
			//bU[l[i15].b[(i28 * 10 + 9)]] = true;
		}
		dprintfss("Get primitive texture index");
		free(arrayOfInt2);
		free(arrayOfInt1);
	}
	i1 += 2;
	int i11;
	i11 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	array *class_b_array__j__bsp = new_array(nl_user, i11, NULL, sizeof(class__b__bsp));
	class__b__bsp *j = (class__b__bsp *)(class_b_array__j__bsp -> array);
	int i2;
	int i3;
	int i4;
	int i17;
	dprintfsi("Map BSP tree node count", i11);
	for (i17 = 0; i17 < i11; i17++)
	{
		int i18;
		for (i18 = 0; i18 < 4; i18++)
		{
			i1 += 2;
			j[i17].int_array_4x3__b__plane[i18][0] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			j[i17].int_array_4x3__b__plane[i18][1] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			j[i17].int_array_4x3__b__plane[i18][2] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		}
		i1 += 2;
		i2 = (int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L);
		i1 += 2;
		i3 = (int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L);
		i1 += 2;
		i4 = (int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L);
		i1 += 2;
		j[i17].int__c__prev_scene = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) - 1);
		i1 += 2;
		j[i17].int__d__next_scene = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) - 1);
		j[i17].int_array_3__a__normal[0] = i2;
		j[i17].int_array_3__a__normal[1] = i3;
		j[i17].int_array_3__a__normal[2] = i4;
		if ((j[i17].int__c__prev_scene == 999) || (j[i17].int__d__next_scene == 999)) {
			//this.dr = true;
		}
		if (i2 != 0) {
			j[i17].byte__a__direction = 1;
		} else if (i3 != 0) {
			j[i17].byte__a__direction = 2;
		} else if (i4 != 0) {
			j[i17].byte__a__direction = 3;
		}
	}
	int i18;
	for (i18 = 0; i18 < i11; i18++)
	{
		if (j[i18].int__c__prev_scene < 999)
		{
			l[j[i18].int__c__prev_scene].int_array_5__p__bsp[l[j[i18].int__c__prev_scene].int__q__bsp] = i18;
			l[j[i18].int__c__prev_scene].int__q__bsp += 1;
		}
		if (j[i18].int__d__next_scene < 999)
		{
			l[j[i18].int__d__next_scene].int_array_5__p__bsp[l[j[i18].int__d__next_scene].int__q__bsp] = i18;
			l[j[i18].int__d__next_scene].int__q__bsp += 1;
		}
	}
	dprintfss("Get map BSP tree node");
	//testtt(l, j, 10, cZ);
	i1 += 2;
	cA = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	dprintfsi("Map item count", cA);
	array *class_g_array__h__item = new_array(nl_user, cA + 1, NULL, sizeof(class__g__item));
	class__g__item *h = (class__g__item *)(class_g_array__h__item -> array);
	int i21 = 0;
	int i24;
	int i22;
	for (i22 = 0; i22 < cZ; i22++)
	{
		i1 += 2;
		i20 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
		dprintfsii("Scene item count", i22, i20);
		l[i22].int__r__begin = i21;
		l[i22].int__e__end = (i21 + i20);
		int i23;
		for (i23 = 0; i23 < i20; i23++)
		{
			h[i21].r = ((short)i22);
			i1 += 2;
			h[i21].int__m__translation = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			h[i21].int__n__translation = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			h[i21].int__o__translation = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			h[i21].int__p__rotation = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
			i1 += 2;
			h[i21].int__q__rotation = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
			if (h[i21].int__q__rotation > 360) {
				h[i21].int__q__rotation = (65536 - h[i21].int__q__rotation);
			}
			if (h[i21].int__p__rotation > 360) {
				h[i21].int__p__rotation = (65536 - h[i21].int__p__rotation);
			}
			if (h[i21].int__q__rotation < 0) {
				h[i21].int__q__rotation = (-h[i21].int__q__rotation);
			}
			if (h[i21].int__q__rotation == 360) {
				h[i21].int__q__rotation = 0;
			}
			if (h[i21].int__p__rotation < 0) {
				h[i21].int__p__rotation = (360 + h[i21].int__p__rotation);
			} else {
				h[i21].int__p__rotation = (360 - h[i21].int__p__rotation);
			}
			if (h[i21].int__p__rotation == 360) {
				h[i21].int__p__rotation = 0;
			}
			i1 += 2;
			h[i21].byte__s__obj = ((byte)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
			//bS[h[i21].s] = true;
			i1 += 2;
			h[i21].d = ((short)(byte)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
			if (h[i21].d != 0)
			{
				h[i21].c = NEW_II(int *, h[i21].d);
				for (i24 = 0; i24 < h[i21].d; i24++) {
					h[i21].c[i24] = NEW_II(int, 4);
				}
				for (i25 = 0; i25 < h[i21].d; i25++)
				{
					i1 += 2;
					h[i21].c[i25][0] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
					i1 += 2;
					h[i21].c[i25][1] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
					i1 += 2;
					h[i21].c[i25][2] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
					i1 += 2;
					h[i21].c[i25][3] = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
				}
				int i26;
				for (i26 = 0; i26 < h[i21].d - 1; i26++)
				{
					int i6;
					if ((i6 = h[i21].c[(i26 + 1)][3] - h[i21].c[i26][3]) > 1)
					{
						i2 = h[i21].c[i26][0];
						i3 = h[i21].c[i26][1];
						i4 = h[i21].c[i26][2];
						int i5 = h[i21].c[i26][3];
						free(h[i21].c[i26]);
						h[i21].c[i26] = NEW_II(int, 7);
						h[i21].c[i26][0] = i2;
						h[i21].c[i26][1] = i3;
						h[i21].c[i26][2] = i4;
						h[i21].c[i26][3] = i5;
						h[i21].c[i26][4] = ((h[i21].c[(i26 + 1)][0] - h[i21].c[i26][0]) / i6);
						h[i21].c[i26][5] = ((h[i21].c[(i26 + 1)][1] - h[i21].c[i26][1]) / i6);
						h[i21].c[i26][6] = ((h[i21].c[(i26 + 1)][2] - h[i21].c[i26][2]) / i6);
					}
				}
				for (i24 = 0; i24 < h[i21].d; i24++) {
					free(h[i21].c[i24]);
				}
				free(h[i21].c);
			}
			i21++;
		}
	}
	nlReadCT3DMapItems(class_g_array__h__item);

	i1 += 2;
#if UNPARSED
	dR = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) + 1;
	al = new byte[dR];
	n = new j[dR];
	for (int i23 = 0; i23 < dR; i23++) {
		n[i23] = new j(null);
	}
	i21 = 1;
	n[0].p = dg[0];
	n[0].q = dg[1];
	n[0].r = dg[2];
#endif
	int i26;
	for (i26 = 0; i26 < cZ; i26++)
	{
		i1 += 2;
		i24 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
		int i27;
		for (i27 = 0; i27 < i24; i27++)
		{
			i1 += 2;
			//n[i21].p = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			//n[i21].z = n[i21].p;
			i1 += 2;
			//n[i21].q = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			//n[i21].A = n[i21].q;
			i1 += 2;
			//n[i21].r = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			//n[i21].C = ((byte)a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
#if UNPARSED
			i25 = n[i21].C;
			bV[i25] = true;
			if ((i25 == 4) || (i25 == 5))
			{
				bt = (byte)(bt + 1);
				this.ei = ((byte)i21);
			}
			else
			{
				dK = (byte)(dK + 1);
			}
			n[i21].t = ((short)i26);
			i21++;
#endif
		}
	}
#if UNPARSED
	for (int i27 = dR - 1; i27 >= 0; i27--)
	{
		f(n[i27]);
		if (i27 == 0)
		{
			cY = n[i27].t;
			b(n[i27].D);
		}
		else
		{
			c(n[i27], 10, 0, 0, 1);
		}
	}
	n[0].t = ((short)cY);
#endif

	class__h__lvl *lv = NEW(class__h__lvl);
	ZERO(lv, class__h__lvl);
	lv -> class_f_array__l__scene = class_f_array__l__scene;
	lv -> class_g_array__h__item = class_g_array__h__item;
	lv -> int__dd__rotation = dd;
	lv -> int__df__rotation = df;
	lv -> int_array__dg__translation[0] = dg[0];
	lv -> int_array__dg__translation[1] = dg[1];
	lv -> int_array__dg__translation[2] = dg[2];
	lv -> class_b_array__j__bsp = class_b_array__j__bsp;
	return lv;
}

void class_h__function_S_void__item(class__g__item *h, const byte arrayOfByte[])
{
	int i1 = -2;
	i1 += 2;
	h -> int__f__aabb = (nlMargeDigit(arrayOfByte[0], arrayOfByte[1]) << 16);
	i1 += 2;
	h -> int__g__aabb = (nlMargeDigit(arrayOfByte[2], arrayOfByte[3]) << 16);
	i1 += 2;
	h -> int__h__aabb = (nlMargeDigit(arrayOfByte[4], arrayOfByte[5]) << 16);
	i1 += 2;
	h -> int__i__aabb = (nlMargeDigit(arrayOfByte[6], arrayOfByte[7]) << 16);
	i1 += 2;
	h -> int__j__aabb = (nlMargeDigit(arrayOfByte[8], arrayOfByte[9]) << 16);
	i1 += 2;
	h -> int__k__aabb = (nlMargeDigit(arrayOfByte[10], arrayOfByte[11]) << 16);
	int i2 = h -> int__f__aabb >> 16;
	int i3 = h -> int__g__aabb >> 16;
	int i4 = h -> int__h__aabb >> 16;
	int i5 = i2 * i2 + i3 * i3 + i4 * i4;
	int i6 = 65536;
	int i7 = 0;
	while (i6 >>= 1 > 0) {
		if ((i7 + i6) * (i7 + i6) <= i5) {
			i7 += i6;
		}
	}
	//h -> d = ((i7 << 1) * 240);
	//h -> c = ((i7 << 1) * 320);
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	int i9 = nlMargeDigit(arrayOfByte[20], arrayOfByte[21]);
	i1 += 2;
	int i8 = nlMargeDigit(arrayOfByte[22], arrayOfByte[23]);
	i1 += 2;
	int i10 = nlMargeDigit(arrayOfByte[24], arrayOfByte[25]);
	//h -> k = i9;
	h -> int_array_6__a__vertex = new_array(nl_int, i9 * 6, NULL, 0);
	h -> int_array_16__b__primitive = new_array(nl_int, i8 * 16, NULL, 0);
	int *a = (int *)(h -> int_array_6__a__vertex -> array);
	int *b = (int *)(h -> int_array_16__b__primitive -> array);
	i10 *= 2;
	int *arrayOfInt = NEW_II(int, i10);
	int i12;
	for (i12 = 0; i12 < i9; i12++)
	{
		i1 += 2;
		a[(i12 * 6)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		a[(i12 * 6 + 1)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		a[(i12 * 6 + 2)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
	}
	int i13;
	for (i13 = 0; i13 < i8; i13++)
	{
		i1 += 2;
		b[(i13 * 16)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
		i1 += 2;
		b[(i13 * 16 + 1)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
		i1 += 2;
		b[(i13 * 16 + 2)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
	}
	int i14;
	for (i14 = 0; i14 < i8; i14++)
	{
		i1 += 2;
		b[(i14 * 16 + 10)] = ((int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
		i1 += 2;
		b[(i14 * 16 + 11)] = ((int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
		i1 += 2;
		b[(i14 * 16 + 12)] = ((int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
	}
	int i15;
	for (i15 = 0; i15 < i10; i15 += 2)
	{
		i1 += 2;
		arrayOfInt[i15] = ((int)(64 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 100L));
		i1 += 2;
		arrayOfInt[(i15 + 1)] = ((int)(64 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 100L));
	}
	int i16;
	for (i16 = 0; i16 < i8; i16++)
	{
		i1 += 2;
		b[(i16 * 16 + 3)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)]);
		b[(i16 * 16 + 4)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)]);
		i1 += 2;
		b[(i16 * 16 + 5)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)]);
		b[(i16 * 16 + 6)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)]);
		i1 += 2;
		b[(i16 * 16 + 7)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)]);
		b[(i16 * 16 + 8)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)]);
	}
	int i17;
	for (i17 = 0; i17 < i8; i17++)
	{
		i1 += 2;
		b[(i17 * 16 + 9)] = ((byte)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
		//bU[g[i11].b[(i17 * 16 + 9)]] = true;
	}
	free(arrayOfInt);
	/*
		 bU[60] = true;
		 for (int i12 = 0; i12 < h.length; i12++) {
		 if (i12 == h.length - 1)
		 {
		 h[i12].a = g[49].a;
		 h[i12].b = g[49].b;
		 h[i12].f = g[49].e;
		 h[i12].i = g[49].h;
		 h[i12].g = g[49].f;
		 h[i12].j = g[49].i;
		 h[i12].h = g[49].g;
		 h[i12].k = g[49].j;
		 }
		 else
		 {
		 h[i12].a = g[h[i12].s].a;
		 h[i12].b = g[h[i12].s].b;
		 h[i12].f = g[h[i12].s].e;
		 h[i12].i = g[h[i12].s].h;
		 h[i12].g = g[h[i12].s].f;
		 h[i12].j = g[h[i12].s].i;
		 h[i12].h = g[h[i12].s].g;
		 h[i12].k = g[h[i12].s].j;
		 if ((h[i12].s == 55) || (h[i12].s == 53)) {
		 h[i12].e = (h[i12].o - h[i12].h - 8192000);
		 }
		 if ((h[i12].s == 54) || (h[i12].s == 52)) {
		 h[i12].e = (h[i12].o + h[i12].h + 8192000);
		 }
		 }
		 }
		 */
}
