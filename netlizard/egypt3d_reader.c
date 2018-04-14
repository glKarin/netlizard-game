#include "egypt3d_reader.h"
#include "nl_util.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// egypt 3d

#define dprintfsi(s, d) nlprintf("Egypt 3D : "#s" -> %d\n", d)
#define dprintfsii(s, d, d2) nlprintf("Egypt 3D : ""%d - "#s" -> %d\n", d, d2)
#define dprintfss(s) nlprintf("Egypt 3D : "#s"\n")

typedef struct _class__a__scene // map
{
  array *short_array_3__a__vertex; // short 3顶点坐标
  array *short_array_7__b__primitive; // short 3索引 3纹理坐标索引(i, i + 1) 1纹理索引
  short short__c__end; // = 0; // 最后一个物品索引
  int int__d__aabb; // AABB盒子
  int int__e__aabb; // AABB盒子
  int int__f__aabb; // AABB盒子
  int int__g__aabb; // AABB盒子
  int int__h__aabb; // AABB盒子
  int int__i__aabb; // AABB盒子
  array *int_array_2__j__plane; //int []; int 碰撞面 1法线索引(i, i + 1, i + 2) 2顶点索引(i, i + 1, i + 2)
  int k;
  int l; // = 0;
  byte byte_array_9__m__bsp[9]; // -1, -1, -1, -1, -1, -1, -1, ?, ?
  int int__n__bsp; // = 0;
  short short__o__begin; // = 0; // 第一个物品索引
} class__a__scene;

typedef struct _class__h__bsp
{
  byte byte__a__direction;
	int int_array_3__a__normal[3];
  int int_array_4x3__b__plane[4][3]; // c[] b = new c[4];
  short short__c__prev_scene;
  short short__d__next_scene;
  boolean e; // = false;
} class__h__bsp;

typedef struct _class__g__item // item
{
  array *short_array_3__a__vertex; // short
  array *short_array_16__b__primitive; //short
  boolean c;
  short d;
  int int__e__aabb;
  int int__f__aabb;
  int int__g__aabb;
  int int__h__aabb;
  int int__i__aabb;
  int int__j__aabb;
  boolean k;
  int int__l__translation;
  int int__m__translation;
  int int__n__translation;
  int int__o__rotation;
  int int__p__rotation;
  short q;
  boolean r;
  byte byte__s__obj; // 33 - 36 大背景盒子
  boolean t; // = true;
} class__g__item;

typedef struct _class__r__role // role
{
  array *short_2_array_3__a__vertex; // short[][]
  array *short_array_16__b__primitive; // short[]
  array *c; // byte[][]
  int d;
} class__r__role;

typedef struct _class__e__lvl
{
	array *class_a_array__h__scene; // 场景
	array *short_array__bh__texcoord; // 纹理坐标
	array *class_g_array__f__item; // 物品
	array *int_array__d__normal; // 法线
  int int_array__aN__translation[3];
  int int__aL__rotation;
  int int__aM__rotation;
	array *class_h_array__g__bsp;
} class__e__lvl;

static class__e__lvl * class_e__function_h_1int__scene(const byte arrayOfByte1[]);
static void nlReadEgypt3DMapItems(array *g_f);
static void class_e__function_Y_void__item(class__g__item *f, const byte arrayOfByte1[]);
static void class_e__function_aa_void__role(class__r__role *obj, const byte arrayOfByte[]);

NETLizard_3D_Model * nlReadEgypt3DRoleModelFile(const char* name, int index)
{
	if(!name)
		return NULL;
	array *arr = nlReadFile(name);
	if(!arr)
		return NULL;
	NETLizard_3D_Model *model = NEW(NETLizard_3D_Model);
	ZERO(model, NETLizard_3D_Model);

	class__r__role obj;
	class_e__function_aa_void__role(&obj, arr -> array);
	array *item_meshes = new_array(nl_user, obj.short_2_array_3__a__vertex -> length, NULL, sizeof(NETLizard_3D_Item_Mesh));
	int i;
	for(i = 0; i < obj.short_2_array_3__a__vertex -> length; i++)
	{
		NETLizard_3D_Item_Mesh *mesh = ((NETLizard_3D_Item_Mesh *)(item_meshes -> array)) + i;
		mesh -> item_mesh.vertex = NULL;
		mesh -> item_mesh.primitive = NULL;
		mesh -> pos[0] = 0;
		mesh -> pos[1] = 0;
		mesh -> pos[2] = 0;
		mesh -> angle[0] = 0;
		mesh -> angle[1] = 0;
		mesh -> obj_index = index;
		array *a = ((array **)(obj.short_2_array_3__a__vertex -> array))[i];
		if(a && obj.short_array_16__b__primitive)
		{
			mesh -> item_mesh.vertex = new_array(nl_int, a -> length, NULL, 0);
			int *m_v = (int *)(mesh -> item_mesh.vertex -> array);
			short *r_a = (short *)(a -> array);
			int j;
			for(j = 0; j < a -> length; j++)
			{
				m_v[j] = r_a[j];
			}
			mesh -> item_mesh.primitive = new_array(nl_user, obj.short_array_16__b__primitive -> length / 16, NULL, sizeof(NETLizard_3D_Primitive));
			short *r_b = (short *)(obj.short_array_16__b__primitive -> array);
			int k = 0;
			for(j = 0; j < obj.short_array_16__b__primitive -> length; j += 16)
			{
				NETLizard_3D_Primitive *p = ((NETLizard_3D_Primitive *)(mesh -> item_mesh.primitive -> array)) + k;
				p -> index[0] = r_b[j];
				p -> index[1] = r_b[j + 1];
				p -> index[2] = r_b[j + 2];
				p -> texcoord[0] = r_b[j + 3];
				p -> texcoord[1] = r_b[j + 4];
				p -> texcoord[2] = r_b[j + 5];
				p -> texcoord[3] = r_b[j + 6];
				p -> texcoord[4] = r_b[j + 7];
				p -> texcoord[5] = r_b[j + 8];
				p -> tex_index = r_b[j + 9];
				k++;
			}
		}
	}

	for(i = 0; i < obj.short_2_array_3__a__vertex -> length; i++)
	{
		delete_array(((array **)(obj.short_2_array_3__a__vertex -> array))[i]);
	}
	delete_array(obj.short_2_array_3__a__vertex);
	free(obj.short_2_array_3__a__vertex);
	delete_array(obj.short_array_16__b__primitive);
	free(obj.short_array_16__b__primitive);
	for(i = 0; i < obj.c -> length; i++)
	{
		delete_array(((array **)(obj.c -> array))[i]);
	}
	delete_array(obj.c);
	free(obj.c);
	delete_array(arr);
	free(arr);
	model -> data = NULL;
	model -> item_data = item_meshes;
	model -> has_sky = 0;
	model -> game = Egypt_3D_Role;
	return model;
}

NETLizard_3D_Model * nlReadEgypt3DItemModelFile(const char* name, int index)
{
	if(!name)
		return NULL;
	array *arr = nlReadFile(name);
	if(!arr)
		return NULL;
	NETLizard_3D_Model *model = NEW(NETLizard_3D_Model);
	ZERO(model, NETLizard_3D_Model);

	class__g__item obj;
	class_e__function_Y_void__item(&obj, arr -> array);
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
	if(obj.short_array_3__a__vertex && obj.short_array_16__b__primitive)
	{
		mesh -> item_mesh.vertex = new_array(nl_int, obj.short_array_3__a__vertex -> length, NULL, 0);
		int *im_v = (int *)(mesh -> item_mesh.vertex -> array);
		short *i_a = (short *)(obj.short_array_3__a__vertex -> array);
		int j;
		for(j = 0; j < obj.short_array_3__a__vertex -> length; j++)
		{
			im_v[j] = i_a[j];
		}
		mesh -> item_mesh.primitive = new_array(nl_user, obj.short_array_16__b__primitive -> length / 16, NULL, sizeof(NETLizard_3D_Primitive));
		short *i_b = (short *)(obj.short_array_16__b__primitive -> array);
		int k = 0;
		for(j = 0; j < obj.short_array_16__b__primitive -> length; j += 16)
		{
			NETLizard_3D_Primitive *p = ((NETLizard_3D_Primitive *)(mesh -> item_mesh.primitive -> array)) + k;
			p -> index[0] = i_b[j];
			p -> index[1] = i_b[j + 1];
			p -> index[2] = i_b[j + 2];
			p -> texcoord[0] = i_b[j + 3];
			p -> texcoord[1] = i_b[j + 4];
			p -> texcoord[2] = i_b[j + 5];
			p -> texcoord[3] = i_b[j + 6];
			p -> texcoord[4] = i_b[j + 7];
			p -> texcoord[5] = i_b[j + 8];
			p -> tex_index = i_b[j + 9];
			p -> plane.position[0] = i_a[p -> index[0]];
			p -> plane.position[1] = i_a[p -> index[0] + 1];
			p -> plane.position[2] = i_a[p -> index[0] + 2];
			p -> plane.normal[0] = i_b[j + 10];
			p -> plane.normal[1] = i_b[j + 11];
			p -> plane.normal[2] = i_b[j + 12];
			k++;
		}
		mesh -> item_mesh.ortho[0] = obj.int__e__aabb >> 16;
		mesh -> item_mesh.ortho[1] = obj.int__f__aabb >> 16;
		mesh -> item_mesh.ortho[2] = obj.int__g__aabb >> 16;
		mesh -> item_mesh.ortho[3] = obj.int__h__aabb >> 16;
		mesh -> item_mesh.ortho[4] = obj.int__i__aabb >> 16;
		mesh -> item_mesh.ortho[5] = obj.int__j__aabb >> 16;
	}

	delete_array(obj.short_array_3__a__vertex);
	delete_array(obj.short_array_16__b__primitive);
	free(obj.short_array_3__a__vertex);
	free(obj.short_array_16__b__primitive);
	delete_array(arr);
	free(arr);
	model -> data = NULL;
	model -> item_data = item_meshes;
	model -> has_sky = 0;
	model -> game = Egypt_3D_Item;
	return model;
}

NETLizard_3D_Model * nlReadEgypt3DModelFile(const char* name)
{
	if(!name)
		return NULL;
	array *arr = nlReadFile(name);
	if(!arr)
		return NULL;
	byte *arrayOfByte = (byte *)(arr -> array);
	class__e__lvl * lv = class_e__function_h_1int__scene(arrayOfByte);
	if(!lv)
		return NULL;
	NETLizard_3D_Model *model = NEW(NETLizard_3D_Model);
	ZERO(model, NETLizard_3D_Model);
	array *a_h = lv -> class_a_array__h__scene;
	array *meshes = new_array(nl_user, a_h -> length, NULL, sizeof(NETLizard_3D_Mesh));
	short *bh = NULL;
	int i;
	if(lv -> short_array__bh__texcoord)
		bh = (short *)(lv -> short_array__bh__texcoord -> array);
	for(i = 0; i < a_h -> length; i++)
	{
		class__a__scene *obj = (class__a__scene *)(a_h -> array) + i;
		NETLizard_3D_Mesh *mesh = ((NETLizard_3D_Mesh *)(meshes -> array)) + i;
		mesh -> vertex = new_array(nl_int, obj -> short_array_3__a__vertex -> length, NULL, 0);
		int *m_v = (int *)(mesh -> vertex -> array);
		short *s_a = (short *)(obj -> short_array_3__a__vertex -> array);
		int j;
		for(j = 0; j < obj -> short_array_3__a__vertex -> length; j++)
		{
			m_v[j] = s_a[j];
		}
		mesh -> primitive = NULL;
		if(obj -> short_array_7__b__primitive)
		{
			mesh -> primitive = new_array(nl_user, obj -> short_array_7__b__primitive -> length / 7, NULL, sizeof(NETLizard_3D_Primitive));
			short *s_b = (short *)(obj -> short_array_7__b__primitive -> array);
			int k = 0;
			for(j = 0; j < obj -> short_array_7__b__primitive -> length; j += 7)
			{
				NETLizard_3D_Primitive *p = ((NETLizard_3D_Primitive *)(mesh -> primitive -> array)) + k;
				p -> index[0] = s_b[j];
				p -> index[1] = s_b[j + 1];
				p -> index[2] = s_b[j + 2];
				p -> texcoord[0] = bh[(s_b[j + 3])];
				p -> texcoord[1] = bh[(s_b[j + 3]) + 1];
				p -> texcoord[2] = bh[(s_b[j + 4])];
				p -> texcoord[3] = bh[(s_b[j + 4]) + 1];
				p -> texcoord[4] = bh[(s_b[j + 5])];
				p -> texcoord[5] = bh[(s_b[j + 5]) + 1];
				p -> tex_index = (s_b[j + 6]) & 0xff;
				k++;
			}
		}
		mesh -> plane = NULL;
		if(obj -> int_array_2__j__plane)
		{
			mesh -> plane = new_array(nl_user, obj -> int_array_2__j__plane -> length / 2, NULL, sizeof(NETLizard_3D_Plane));
			int *d = (int *)(lv -> int_array__d__normal -> array);
			int *j_array = (int *)(obj -> int_array_2__j__plane -> array);
			int k = 0;
			for(j = 0; j < obj -> int_array_2__j__plane -> length; j += 2)
			{
				int normal_index = j_array[j];
				int position_index = j_array[j + 1];
				NETLizard_3D_Plane *plane = ((NETLizard_3D_Plane *)(mesh -> plane -> array)) + k;
				plane -> normal[0] = d[normal_index];
				plane -> normal[1] = d[normal_index + 1];
				plane -> normal[2] = d[normal_index + 2];
				plane -> position[0] = s_a[position_index];
				plane -> position[1] = s_a[position_index + 1];
				plane -> position[2] = s_a[position_index + 2];
				k++;
			}
		}
		mesh -> ortho[0] = obj -> int__d__aabb >> 16;
		mesh -> ortho[1] = obj -> int__e__aabb >> 16;
		mesh -> ortho[2] = obj -> int__f__aabb >> 16;
		mesh -> ortho[3] = obj -> int__g__aabb >> 16;
		mesh -> ortho[4] = obj -> int__h__aabb >> 16;
		mesh -> ortho[5] = obj -> int__i__aabb >> 16;
		mesh -> item_index_range[0] = obj -> short__o__begin;
		mesh -> item_index_range[1] = obj -> short__c__end;

		mesh -> bsp = NULL;
		if(obj -> int__n__bsp)
		{
			mesh -> bsp = new_array(nl_int, obj -> int__n__bsp, NULL, 0);
			int *bsp_index = (int *)(mesh -> bsp -> array);
			for(j = 0; j < obj -> int__n__bsp; j++)
			{
				bsp_index[j] = obj -> byte_array_9__m__bsp[j];
			}
		}
	}

	array *g_f = lv -> class_g_array__f__item;
	array *item_meshes = new_array(nl_user, g_f -> length, NULL, sizeof(NETLizard_3D_Item_Mesh));
	for(i = 0; i < g_f -> length; i++)
	{
		NETLizard_3D_Item_Mesh *mesh = ((NETLizard_3D_Item_Mesh *)(item_meshes -> array)) + i;
		class__g__item *obj = ((class__g__item *)(g_f -> array)) + i;
		if(!obj -> short_array_3__a__vertex || !obj -> short_array_16__b__primitive)
		{
			mesh -> item_mesh.vertex = NULL;
			mesh -> item_mesh.primitive = NULL;
			continue;
		}
		mesh -> pos[0] = obj -> int__l__translation >> 16;
		mesh -> pos[1] = obj -> int__m__translation >> 16;
		mesh -> pos[2] = obj -> int__n__translation >> 16;
		mesh -> angle[0] = obj -> int__o__rotation;
		mesh -> angle[1] = obj -> int__p__rotation;
		mesh -> obj_index = obj -> byte__s__obj;
		mesh -> item_mesh.vertex = new_array(nl_int, obj -> short_array_3__a__vertex -> length, NULL, 0);
		int *im_v = (int *)(mesh -> item_mesh.vertex -> array);
		short *i_a = (short *)(obj -> short_array_3__a__vertex -> array);
		int j;
		for(j = 0; j < obj -> short_array_3__a__vertex -> length; j++)
		{
			im_v[j] = i_a[j];
		}
		mesh -> item_mesh.primitive = new_array(nl_user, obj -> short_array_16__b__primitive -> length / 16, NULL, sizeof(NETLizard_3D_Primitive));
		short *i_b = (short *)(obj -> short_array_16__b__primitive -> array);
		int k = 0;
		for(j = 0; j < obj -> short_array_16__b__primitive -> length; j += 16)
		{
			NETLizard_3D_Primitive *p = ((NETLizard_3D_Primitive *)(mesh -> item_mesh.primitive -> array)) + k;
			p -> index[0] = i_b[j];
			p -> index[1] = i_b[j + 1];
			p -> index[2] = i_b[j + 2];
			p -> texcoord[0] = i_b[j + 3];
			p -> texcoord[1] = i_b[j + 4];
			p -> texcoord[2] = i_b[j + 5];
			p -> texcoord[3] = i_b[j + 6];
			p -> texcoord[4] = i_b[j + 7];
			p -> texcoord[5] = i_b[j + 8];
			p -> tex_index = i_b[j + 9];
			p -> plane.position[0] = i_a[p -> index[0]];
			p -> plane.position[1] = i_a[p -> index[0] + 1];
			p -> plane.position[2] = i_a[p -> index[0] + 2];
			p -> plane.normal[0] = i_b[j + 10];
			p -> plane.normal[1] = i_b[j + 11];
			p -> plane.normal[2] = i_b[j + 12];
			k++;
		}
		mesh -> item_mesh.ortho[0] = obj -> int__e__aabb >> 16;
		mesh -> item_mesh.ortho[1] = obj -> int__f__aabb >> 16;
		mesh -> item_mesh.ortho[2] = obj -> int__g__aabb >> 16;
		mesh -> item_mesh.ortho[3] = obj -> int__h__aabb >> 16;
		mesh -> item_mesh.ortho[4] = obj -> int__i__aabb >> 16;
		mesh -> item_mesh.ortho[5] = obj -> int__j__aabb >> 16;
	}

	model -> bsp_data = NULL;
	if(lv -> class_h_array__g__bsp)
	{
		class__h__bsp *bsp = (class__h__bsp *)(lv -> class_h_array__g__bsp -> array);
		model -> bsp_data = new_array(nl_user, lv -> class_h_array__g__bsp -> length, NULL, sizeof(NETLizard_BSP_Tree_Node));
		NETLizard_BSP_Tree_Node *bsp_data = (NETLizard_BSP_Tree_Node *)(model -> bsp_data -> array);
		int j;
		for(j = 0; j < lv -> class_h_array__g__bsp -> length; j++)
		{
			int k;
			for(k = 0; k < 4; k++)
			{
				bsp_data[j].plane[k][0] = bsp[j].int_array_4x3__b__plane[k][0] >> 16;
				bsp_data[j].plane[k][1] = bsp[j].int_array_4x3__b__plane[k][1] >> 16;
				bsp_data[j].plane[k][2] = bsp[j].int_array_4x3__b__plane[k][2] >> 16;
			}
			bsp_data[j].direction = bsp[j].byte__a__direction;
			bsp_data[j].prev_scene = bsp[j].short__c__prev_scene;
			bsp_data[j].next_scene = bsp[j].short__d__next_scene;
			bsp_data[j].normal[0] = bsp[j].int_array_3__a__normal[0];
			bsp_data[j].normal[1] = bsp[j].int_array_3__a__normal[1];
			bsp_data[j].normal[2] = bsp[j].int_array_3__a__normal[2];
		}
	}

	model -> data = meshes;
	model -> item_data = item_meshes;
	model -> start_angle[0] = lv -> int__aL__rotation;
	model -> start_angle[1] = lv -> int__aM__rotation;
	model -> start_pos[0] = lv -> int_array__aN__translation[0] >> 16;
	model -> start_pos[1] = lv -> int_array__aN__translation[1] >> 16;
	model -> start_pos[2] = lv -> int_array__aN__translation[2] >> 16;
	model -> game = Egypt_3D_Map;
	model -> has_sky = 0;

	for(i = 0; i < lv -> class_a_array__h__scene -> length; i++)
	{
		class__a__scene *obj = ((class__a__scene *)(lv -> class_a_array__h__scene -> array)) + i;
		delete_array(obj -> short_array_3__a__vertex);
		delete_array(obj -> short_array_7__b__primitive);
		delete_array(obj -> int_array_2__j__plane);
		free(obj -> short_array_3__a__vertex);
		free(obj -> short_array_7__b__primitive);
		free(obj -> int_array_2__j__plane);
	}
	delete_array(lv -> class_a_array__h__scene);
	free(lv -> class_a_array__h__scene);
	for(i = 0; i < lv -> class_g_array__f__item -> length; i++)
	{
		class__g__item *obj = ((class__g__item *)(lv -> class_g_array__f__item -> array)) + i;
		delete_array(obj -> short_array_3__a__vertex);
		delete_array(obj -> short_array_16__b__primitive);
		free(obj -> short_array_3__a__vertex);
		free(obj -> short_array_16__b__primitive);
	}
	delete_array(lv -> class_g_array__f__item);
	free(lv -> class_g_array__f__item);
	delete_array(lv -> short_array__bh__texcoord);
	free(lv -> short_array__bh__texcoord);
	delete_array(lv -> int_array__d__normal);
	free(lv -> int_array__d__normal);
	delete_array(lv -> class_h_array__g__bsp);
	free(lv -> class_h_array__g__bsp);
	free(lv);
	return model;
}

void nlReadEgypt3DMapItems(array *g_f)
{
	if(!g_f)
		return;
	int i;
	for(i = 0; i < g_f -> length; i++)
	{
		class__g__item *f = ((class__g__item *)(g_f -> array)) + i;
		int i11 = f -> byte__s__obj;
		char subfix[strlen(EGYPT3D_OBJ_SUBFIX) + 1];
		memset(subfix, '\0', sizeof(char) * (strlen(subfix) + 1));
		sprintf(subfix, EGYPT3D_OBJ_SUBFIX, i11);
		char *name = NULL;
		if(game_resource_path[nl_shadow_of_egypt_3d])
		{
			name = NEW_II(char, strlen(subfix) + strlen(game_resource_path[nl_shadow_of_egypt_3d]) + 1 + 1);
			memset(name, '\0', sizeof(char) * ((strlen(subfix) + strlen(game_resource_path[nl_shadow_of_egypt_3d]) + 1 + 1)));
			sprintf(name, "%s/%s", game_resource_path[nl_shadow_of_egypt_3d], subfix);
		}
		else
			name = strdup(subfix);
		array *arr = nlReadFile(name);
		free(name);
		if(arr)
		{
			class_e__function_Y_void__item(f, arr -> array);
			delete_array(arr);
			free(arr);
		}
		else
		{
			f -> short_array_3__a__vertex = NULL;
			f -> short_array_16__b__primitive = NULL;
		}
	}
}

/* ****** static ****** */

class__e__lvl * class_e__function_h_1int__scene(const byte arrayOfByte1[])
{
	if(!arrayOfByte1)
		return NULL;
	//byte *av = NULL;
	int aL;
	int aM;
	int aN[3];
	short aF;
	array *a_h = NULL;
	//byte *ao = NULL;
	array *int_d = NULL;
	array *short_bh = NULL;
	short ak;
	array *g_f = NULL;

	int i1 = -2;
	i1 += 2;
	int i2;
	if ((i2 = nlMargeDigit(arrayOfByte1[0], arrayOfByte1[1])) != 0) {
		//av = NEW_II(byte, i2);
	}
	int i15;
	int i5;
	for (i5 = 0; i5 < i2; i5++)
	{
		i1 += 2;
		//av[i5] = ((byte)nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]));
	}
	i1 += 2;
	aN[0] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
	i1 += 2;
	aN[1] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
	i1 += 2;
	aN[2] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
	i1 += 2;
	aL = nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]);
	i1 += 2;
	aM = nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]);
	if (aM > 361) {
		aM -= 65536;
	}
	if (aL > 361) {
		aL -= 65536;
	}
	if (aM < 0) {
		aM = -aM;
	} else {
		aM = 360 - aM;
	}
	if (aM == 360) {
		aM = 0;
	}
	if (aL < 0) {
		aL = 270 + aL;
	} else {
		aL = 270 - aL;
	}
	if (aL == 360) {
		aL = 0;
	}
	dprintfss("Get start position and axis");
	i1 += 2;
	aF = (short)nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]);
	dprintfsi("Map scene count", aF);
	i1 += 2;
	int i6;
	i6 = nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]);
	dprintfsi("Map normal count", i6);
	if(i6)
	{
		int_d = new_array(nl_int, i6, NULL, 0);
		int *d = (int *)(int_d -> array);
		int i7;
		for (i7 = 0; i7 < i6; i7 += 3)
		{
			i1 += 2;
			d[i7] = ((int)(65536 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L));
			i1 += 2;
			d[(i7 + 1)] = ((int)(65536 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L));
			i1 += 2;
			d[(i7 + 2)] = ((int)(65536 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L));
		}
		dprintfss("Get map normal");
	}
	i1 += 2;
	i6 = nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]);
	dprintfsi("Texcoord count", i6);
	short_bh = new_array(nl_short, i6, NULL, 0);
	short *bh = NULL;
	if(short_bh)
		bh = (short *)(short_bh -> array);
	int i8;
	for (i8 = 0; i8 < i6; i8 += 2)
	{
		i1 += 2;
		bh[i8] = ((short)(int)(128 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 100L));
		i1 += 2;
		bh[(i8 + 1)] = ((short)(int)(128 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 100L));
	}
	dprintfss("Get map texcoord");
	a_h = new_array(nl_user, aF, NULL, sizeof(class__a__scene));
	class__a__scene *h = (class__a__scene *)(a_h -> array);
	//ao = NEW_II(byte, aF);
	int i18;
	int i13;
	for (i13 = 0; i13 < aF; i13++)
	{
		dprintfsi("Get map scene data", i13);
		i1 += 2;
		h[i13].int__d__aabb = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
		i1 += 2;
		h[i13].int__e__aabb = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
		i1 += 2;
		h[i13].int__f__aabb = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
		i1 += 2;
		h[i13].int__g__aabb = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
		i1 += 2;
		h[i13].int__h__aabb = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
		i1 += 2;
		h[i13].int__i__aabb = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
		dprintfss("Get scene AABB");
		i1 += 2;
		int i11 = nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]);
		dprintfsi("Scene vertex coord count", i11);
		i1 += 2;
		int i10 = nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]);
		dprintfsi("Scene primitive count", i10);
		h[i13].short_array_3__a__vertex = new_array(nl_short, i11 * 3, NULL, 0);
		short *a = ((short *)(h[i13].short_array_3__a__vertex -> array));
		h[i13].k = i11;
		h[i13].short_array_7__b__primitive = new_array(nl_short, i10 * 7, NULL, 0);
		short *b = NULL;
		if(h[i13].short_array_7__b__primitive)
			b = ((short *)(h[i13].short_array_7__b__primitive -> array));
		h[i13].l = i10;
		int i14;
		for (i14 = 0; i14 < i11; i14++)
		{
			i1 += 2;
			a[(i14 * 3)] = ((short)nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]));
			i1 += 2;
			a[(i14 * 3 + 1)] = ((short)nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]));
			i1 += 2;
			a[(i14 * 3 + 2)] = ((short)nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]));
		}
		dprintfss("Get scene vertex coord");
		short *arrayOfShort = h[i13].short_array_7__b__primitive ? h[i13].short_array_7__b__primitive -> array : NULL;
		int i17;
		for (i17 = 0; i17 < i10; i17++)
		{
			int i16 = i17 * 7;
			i1 += 2;
			b[i16] = ((short)(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 3));
			i1 += 2;
			b[(i16 + 1)] = ((short)(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 3));
			i1 += 2;
			b[(i16 + 2)] = ((short)(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 3));
		}
		dprintfss("Get scene primitive vertex coord index");
		i1 += 2;
		i18 = nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]);
		dprintfsi("Scene plane count", i18);
		h[i13].int_array_2__j__plane = NULL;
		//h[i13].j = NEW_II(int, i18 * 2);
		if(i18)
		{
			h[i13].int_array_2__j__plane = new_array(nl_int, i18 * 2, NULL, 0);
			int *j = (int *)(h[i13].int_array_2__j__plane -> array);
			int i19;
			for (i19 = 0; i19 < i18; i19++)
			{
				i1 += 2;
				j[(i19 * 2)] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 3);
				i1 += 2;
				j[(i19 * 2 + 1)] = arrayOfShort[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 7)];
			}
			dprintfss("Get scene plane normal index and point vertex coord index");
		}
		int i20;
		int i16;
		for (i20 = 0; i20 < i10; i20++)
		{
			i16 = i20 * 7;
			i1 += 2;
			b[(i16 + 3)] = ((short)(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2));
			i1 += 2;
			b[(i16 + 4)] = ((short)(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2));
			i1 += 2;
			b[(i16 + 5)] = ((short)(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2));
		}
		dprintfss("Get scene texcoord index");
		i1++;
		int i23;
		int i21;
		for (i23 = 0; i23 < i10; i23++)
		{
			i1++;
			if ((i21 = arrayOfByte1[i1]) < 0) {
				i21 += 256;
			}
			b[(i23 * 7 + 6)] = ((short)i21);
			if (b[(i23 * 7 + 6)] < 50) {
				//T[h[i13].b[(i23 * 7 + 6)]] = true;
			}
			//printf("%d * 7 + 6 = %d\n", i23, ((short *)(h[i13].b -> array))[(i23 * 7 + 6)]);
		}
		int i24;
		for (i24 = 0; i24 < i10; i24++)
		{
			i1++;
			int i22;
			if ((i22 = (i22 = nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)])) & 0xFF) < 70) {
				i22 = 70;
			}
			i21 = b[(i24 * 7 + 6)] & 0xFF;
			b[(i24 * 7 + 6)] = ((short)(i22 << 8 | i21));
		}
		dprintfss("Get primitive texture index");
		i1--;
	}

	i1 += 2;
	int i12;
	i12 = nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]);
	dprintfsi("Map BSP tree node count", i12);
	array *class_h_array__g__bsp = NULL;
	if(i12 > 0)
	{
		class_h_array__g__bsp = new_array(nl_user, i12, NULL, sizeof(class__h__bsp));
		class__h__bsp *g = (class__h__bsp *)(class_h_array__g__bsp -> array);
		for (i15 = 0; i15 < i12; i15++)
		{
			int i16;
			for (i16 = 0; i16 < 4; i16++)
			{
				i1 += 2;
				g[i15].int_array_4x3__b__plane[i16][0] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
				i1 += 2;
				g[i15].int_array_4x3__b__plane[i16][1] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
				i1 += 2;
				g[i15].int_array_4x3__b__plane[i16][2] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
			}
			i1 += 2;
			i2 = (int)(65536 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L);
			i1 += 2;
			int i3 = (int)(65536 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L);
			i1 += 2;
			int i4 = (int)(65536 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L);
			i1 += 2;
			g[i15].short__c__prev_scene = ((short)(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) - 1));
			i1 += 2;
			g[i15].short__d__next_scene = ((short)(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) - 1));
			g[i15].int_array_3__a__normal[0] = i2;
			g[i15].int_array_3__a__normal[1] = i3;
			g[i15].int_array_3__a__normal[2] = i4;
			if (i2 != 0) {
				g[i15].byte__a__direction = 1;
			} else if (i3 != 0) {
				g[i15].byte__a__direction = 2;
			} else if (i4 != 0) {
				g[i15].byte__a__direction = 3;
			}
		}
		int i16;
		for (i16 = 0; i16 < i12; i16++)
		{
			if (g[i16].short__c__prev_scene < 999)
			{
				h[g[i16].short__c__prev_scene].byte_array_9__m__bsp[h[g[i16].short__c__prev_scene].int__n__bsp] = ((byte)i16);
				h[g[i16].short__c__prev_scene].int__n__bsp += 1;
			}
			if (g[i16].short__d__next_scene < 999)
			{
				h[g[i16].short__d__next_scene].byte_array_9__m__bsp[h[g[i16].short__d__next_scene].int__n__bsp] = ((byte)i16);
				h[g[i16].short__d__next_scene].int__n__bsp += 1;
			}
		}
		dprintfss("Get map BSP tree node");
	}
	i1 += 2;
	ak = (short)nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]);
	dprintfsi("Map item count", ak);
	g_f = new_array(nl_user, ak, NULL, sizeof(class__g__item));
	class__g__item *f = (class__g__item *)(g_f -> array);
	//short *an = NEW_II(short, ak);
	int i19 = 0;
	int i20;
	for (i20 = 0; i20 < aF; i20++)
	{
		i1 += 2;
		i18 = nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]);
		dprintfsii("Scene item count", i20, i18);
		h[i20].short__o__begin = ((short)i19);
		h[i20].short__c__end = ((short)(i19 + i18));
		int i21;
		for (i21 = 0; i21 < i18; i21++)
		{
			f[i19].q = ((short)i20);
			i1 += 2;
			f[i19].int__l__translation = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
			i1 += 2;
			f[i19].int__m__translation = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
			i1 += 2;
			f[i19].int__n__translation = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
			i1 += 2;
			f[i19].int__o__rotation = nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]);
			i1 += 2;
			f[i19].int__p__rotation = ((short)nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]));
			if (f[i19].int__p__rotation > 360) {
				f[i19].int__p__rotation = (65536 - f[i19].int__p__rotation);
			}
			if (f[i19].int__o__rotation > 360) {
				f[i19].int__o__rotation = (65536 - f[i19].int__o__rotation);
			}
			if (f[i19].int__p__rotation < 0) {
				f[i19].int__p__rotation = (360 + f[i19].int__p__rotation);
			}
			if (f[i19].int__o__rotation < 0) {
				f[i19].int__o__rotation = (360 + f[i19].int__o__rotation);
			} else {
				f[i19].int__o__rotation = (360 - f[i19].int__o__rotation);
			}
			if (f[i19].int__o__rotation == 360) {
				f[i19].int__o__rotation = 0;
			}
			i1 += 2;
			f[i19].byte__s__obj = ((byte)nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]));
			if (f[i19].byte__s__obj > 50)
			{
				class__g__item *tmp2661_2660 = f + i19;
				tmp2661_2660 -> byte__s__obj = ((byte)(tmp2661_2660 -> byte__s__obj - 50));
				f[i19].t = _true;
			}
			if (f[i19].byte__s__obj == 20)
			{
				// door 石门
				//ao[i20] = 1;
				//an[i19] = ((short)((f[i19].n >> 16) + 300));
			}
			//S[f[i19].byte__s__obj] = true;
			i1 += 2;
			f[i19].d = ((short)nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]));
			if ((f[i19].byte__s__obj == 14) || (f[i19].byte__s__obj == 15)) {
				// 14 传送门光柱
				// 15 传送门光柱底座
				f[i19].d = 255;
			}
			if (f[i19].d < 0)
			{
				class__g__item *tmp2822_2821 = f + i19;
				tmp2822_2821 -> d = ((short)(tmp2822_2821 -> d + 256));
			}
			class__g__item *tmp2840_2839 = f + i19;
			tmp2840_2839 -> d = ((short)(tmp2840_2839 -> d & 0xFF));
			if (f[i19].d < 70) {
				f[i19].d = 70;
			}
			i1 += 2;
			i19++;
		}
	}

#if UNPARSED
	aE = -1;
	aj = -1;
	for (int i21 = 0; i21 < ak; i21++) {
		if ((f[i21].s > 32) && (f[i21].s < 37))
		{
			aE = (byte)f[i21].q;
			aj = (byte)i21;
			break;
		}
	}
	int i25;
	for (int i23 = 0; i23 < h.length; i23++)
	{
		arrayOfByte2 = null;
		arrayOfByte2 = h[i23].m;
		h[i23].m = null;
		i24 = h[i23].n;
		h[i23].m = new byte[i24];
		for (i25 = 0; i25 < i24; i25++) {
			h[i23].m[i25] = arrayOfByte2[i25];
		}
	}
	byte[] arrayOfByte2 = null;
#endif
	i1 += 2;
#if UNPARSED
	bn = (short)(f.a(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) + 1);
	s = new byte[bn];
	j = new p[bn];
	for (int i24 = 0; i24 < bn; i24++)
	{
		j[i24] = new p();
		j[i24].l = ((byte)i24);
	}
	i19 = 1;
	j[0].p = aN[0];
	j[0].q = aN[1];
	j[0].r = aN[2];
#endif
	int i26;
	int i28;
	for (i28 = 0; i28 < aF; i28++)
	{
		i1 += 2;
		int i25;
		i25 = nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]);
		int i29;
		for (i29 = 0; i29 < i25; i29++)
		{
			i1 += 2;
			//j[i19].p = (f.a(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
			i1 += 2;
			//j[i19].q = (f.a(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
			i1 += 2;
			//j[i19].r = (f.a(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
			i1 += 2;
			//j[i19].A = ((byte)f.a(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]));
#if UNPARSED
			if ((i26 = j[i19].A) > 30)
			{
				j[i19].w = true;
				j[i19].C = false;
				j[i19].k = true;
				j[i19].m = 0;
				i26 -= 30;
			}
			else if (i26 > 20)
			{
				i26 -= 20;
				j[i19].w = true;
				j[i19].C = false;
			}
			else if (i26 > 10)
			{
				i26 -= 10;
				j[i19].w = true;
			}
			j[i19].A = ((byte)i26);
			U[i26] = true;
#endif
			i1 += 2;
#if UNPARSED
			int i27;
			if ((i27 = f.a(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)])) > 360) {
				i27 -= 65536;
			}
			if (i27 < 0) {
				i27 = -i27;
			} else {
				i27 = 360 - i27;
			}
			if (i27 == 360) {
				i27 = 0;
			}
			j[i19].u[0] = (-f.f[i27]);
			j[i19].u[1] = (-f.a[i27]);
			j[i19].B[0] = (-f.f[i27]);
			j[i19].B[1] = (-f.a[i27]);
			j[i19].t = ((short)i28);
			i19++;
#endif
		}
	}
#if UNPARSED
	for (int i29 = 0; i29 < j.length; i29++) {
		j[i29].m = O[j[i29].A];
	}
#endif
	i1 += 2;
	/*P = */i26 = (byte)nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]);
	//Q = new short[i26 * 3];
	int i30;
	for (i30 = 0; i30 < i26; i30++)
	{
		i1 += 2;
		//Q[(i30 * 3)] = ((short)f.a(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]));
		i1 += 2;
		//Q[(i30 * 3 + 1)] = ((short)f.a(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]));
		i1 += 2;
		//Q[(i30 * 3 + 2)] = ((short)f.a(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]));
	}
#if UNPARSED
	aD = 0;
	for (int i31 = bn - 1; i31 >= 0; i31--)
	{
		f.a(j[i31]);
		f.b(j[i31]);
		if (i31 == 0)
		{
			aD = j[i31].t;
			f.a(j[i31].B, aL, aM);
			aN[0] = j[0].p;
			aN[1] = j[0].q;
			aN[2] = (j[0].r + 2293760);
		}
	}
	j[0].t = ((short)aD);
#endif

	nlReadEgypt3DMapItems(g_f);
	class__e__lvl *lv = NEW(class__e__lvl);
	ZERO(lv, class__e__lvl);
	lv -> class_a_array__h__scene = a_h;
	lv -> short_array__bh__texcoord = short_bh;
	lv -> class_g_array__f__item = g_f;
	lv -> int_array__d__normal = int_d;
	lv -> int__aL__rotation = aL;
	lv -> int__aM__rotation = aM;
	lv -> int_array__aN__translation[0] = aN[0];
	lv -> int_array__aN__translation[1] = aN[1];
	lv -> int_array__aN__translation[2] = aN[2];
	lv -> class_h_array__g__bsp = class_h_array__g__bsp;
	return lv;
}

void class_e__function_Y_void__item(class__g__item *f, const byte arrayOfByte1[])
{
	int i14;
	int i17;
	int i1 = -2;
	i1 += 2;
	f -> int__e__aabb = (nlMargeDigit(arrayOfByte1[0], arrayOfByte1[1]) << 16);
	i1 += 2;
	f -> int__f__aabb = (nlMargeDigit(arrayOfByte1[2], arrayOfByte1[3]) << 16);
	i1 += 2;
	f -> int__g__aabb = (nlMargeDigit(arrayOfByte1[4], arrayOfByte1[5]) << 16);
	i1 += 2;
	f -> int__h__aabb = (nlMargeDigit(arrayOfByte1[6], arrayOfByte1[7]) << 16);
	i1 += 2;
	f -> int__i__aabb = (nlMargeDigit(arrayOfByte1[8], arrayOfByte1[9]) << 16);
	i1 += 2;
	f -> int__j__aabb = (nlMargeDigit(arrayOfByte1[10], arrayOfByte1[11]) << 16);
	int i2 = f -> int__e__aabb >> 16;
	int i3 = f -> int__f__aabb >> 16;
	int i4 = f -> int__g__aabb >> 16;
	int i5 = i2 * i2 + i3 * i3 + i4 * i4;
	int i6 = 65536;
	int i7 = 0;
	while (i6 >>= 1 > 0) {
		if ((i7 + i6) * (i7 + i6) <= i5) {
			i7 += i6;
		}
	}
	f -> d = ((i7 << 3) * 240 << 1);
	f -> c = ((i7 << 1) * 260);
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	int i9 = nlMargeDigit(arrayOfByte1[20], arrayOfByte1[21]);
	i1 += 2;
	int i8 = nlMargeDigit(arrayOfByte1[22], arrayOfByte1[23]);
	i1 += 2;
	int i10 = nlMargeDigit(arrayOfByte1[24], arrayOfByte1[25]);
	f -> k = i9;
	f -> short_array_3__a__vertex = new_array(nl_short, i9 * 3, NULL, 0);
	f -> short_array_16__b__primitive = new_array(nl_short, i8 * 16, NULL, 0);
	short *a = (short *)(f -> short_array_3__a__vertex -> array);
	short *b = (short *)(f -> short_array_16__b__primitive -> array);
	i10 *= 2;
	int *arrayOfInt = NEW_II(int, i10);
	int i12;
	for (i12 = 0; i12 < i9; i12++)
	{
		i1 += 2;
		a[(i12 * 3)] = ((short)nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]));
		i1 += 2;
		a[(i12 * 3 + 1)] = ((short)nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]));
		i1 += 2;
		a[(i12 * 3 + 2)] = ((short)nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]));
	}
	int i13;
	for (i13 = 0; i13 < i8; i13++)
	{
		i1 += 2;
		b[(i13 * 16)] = ((short)(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 3));
		i1 += 2;
		b[(i13 * 16 + 1)] = ((short)(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 3));
		i1 += 2;
		b[(i13 * 16 + 2)] = ((short)(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 3));
	}
	int i15;
	for (i15 = 0; i15 < i8; i15++)
	{
		i1 += 2;
		i14 = (int)(65536 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L);
		b[(i15 * 16 + 10)] = ((short)(byte)(int)(i14 * 127L >> 16));
		i1 += 2;
		i14 = (int)(65536 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L);
		b[(i15 * 16 + 11)] = ((short)(byte)(int)(i14 * 127L >> 16));
		i1 += 2;
		i14 = (int)(65536 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L);
		b[(i15 * 16 + 12)] = ((short)(byte)(int)(i14 * 127L >> 16));
	}
	int i16;
	for (i16 = 0; i16 < i10; i16 += 2)
	{
		i1 += 2;
		arrayOfInt[i16] = ((int)(128 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 100L));
		i1 += 2;
		arrayOfInt[(i16 + 1)] = ((int)(128 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 100L));
	}
	for (i17 = 0; i17 < i8; i17++)
	{
		i1 += 2;
		b[(i17 * 16 + 3)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2)]);
		b[(i17 * 16 + 4)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2 + 1)]);
		i1 += 2;
		b[(i17 * 16 + 5)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2)]);
		b[(i17 * 16 + 6)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2 + 1)]);
		i1 += 2;
		b[(i17 * 16 + 7)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2)]);
		b[(i17 * 16 + 8)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2 + 1)]);
	}
	i1 += 2;
	int i18;
	for (i18 = 0; i18 < i8; i18++)
	{
		b[(i18 * 16 + 9)] = ((short)arrayOfByte1[i1]);
		/*
			 if (e[(i18 * 16 + 9)] < 50) {
			 T[e[i11].b[(i18 * 16 + 9)]] = true;
			 }
			 */
		i1++;
	}

	free(arrayOfInt);
	/*
		 byte[] arrayOfByte2 = n.g.b("oi", -1);
		 for (int i16 = 0; i16 < f.length; i16++)
		 {
		 g localg;
		 if ((localg = f[i16]).s < 120)
		 {
		 i14 = localg.s << 2;
		 if (arrayOfByte2[(i14 + 1)] == 1) {
		 localg.r = true;
		 }
		 if (arrayOfByte2[(i14 + 2)] == 1) {
		 localg.c = true;
		 }
		 if (arrayOfByte2[(i14 + 3)] == 1) {
		 localg.k = true;
		 }
		 v localv = e[localg.s];
		 localg.a = localv.a;
		 localg.b = localv.b;
		 localg.e = localv.e;
		 localg.h = localv.h;
		 localg.f = localv.f;
		 localg.i = localv.i;
		 localg.g = localv.g;
		 localg.j = localv.j;
		 }
		 }
		 if (q.H == 10) {
		 for (i17 = 0; i17 < ak; i17++) {
		 if (f[i17].s == 9) {
		 f[i17].c = true;
		 }
		 }
		 }
		 */
}

void class_e__function_aa_void__role(class__r__role *obj, const byte arrayOfByte[])
{
	int i1 = -2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	int i3 = nlMargeDigit(arrayOfByte[12], arrayOfByte[13]);
	i1 += 2;
	int i2 = nlMargeDigit(arrayOfByte[14], arrayOfByte[15]);
	i1 += 2;
	int i4 = nlMargeDigit(arrayOfByte[16], arrayOfByte[17]);
	i1 += 2;
	int i5 = nlMargeDigit(arrayOfByte[18], arrayOfByte[19]);
	obj -> short_2_array_3__a__vertex = new_array(nl_pointer, i5, NULL, 0); // short[][]
	obj -> c = new_array(nl_pointer, i5, NULL, 0); // byte[][]
	obj -> d = i3;
	int i7;
	for (i7 = 0; i7 < i5; i7++)
	{
		array **a = (array **)(obj -> short_2_array_3__a__vertex -> array);
		array **c = (array **)(obj -> c -> array);
		c[i7] = new_array(nl_byte, i2 * 3, NULL, 0);
		a[i7] = new_array(nl_short, i3 * 3, NULL, 0);
	}
	obj -> short_array_16__b__primitive = new_array(nl_short, i2 * 16, NULL, 0);
	short *b = (short *)(obj -> short_array_16__b__primitive -> array);
	i4 *= 2;
	short *arrayOfShort = NEW_II(short, i4);
	int i8;
	for (i8 = 0; i8 < i5; i8++) {
		array *arr = ((array **)(obj -> short_2_array_3__a__vertex -> array))[i8];
		int i9;
		for (i9 = 0; i9 < i3; i9++)
		{
			short *a = (short *)(arr -> array);
			i1 += 2;
			a[(i9 * 3)] = ((short)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
			i1 += 2;
			a[(i9 * 3 + 1)] = ((short)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
			i1 += 2;
			a[(i9 * 3 + 2)] = ((short)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
		}
	}
	int i10 = i2 * 16;
	int i11;
	for (i11 = 0; i11 < i10; i11 += 16)
	{
		i1 += 2;
		b[i11] = ((short)(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 3));
		i1 += 2;
		b[(i11 + 1)] = ((short)(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 3));
		i1 += 2;
		b[(i11 + 2)] = ((short)(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 3));
	}
	i10 = i2 * 3;
	i1++;
	int i12;
	for (i12 = 0; i12 < i5; i12++) {
		int i13;
		for (i13 = 0; i13 < i10; i13 += 3)
		{
			byte *c = (byte *)((((array **)(obj -> c -> array))[i12]) -> array);
			i1++;
			c[i13] = arrayOfByte[i1];
			i1++;
			c[(i13 + 1)] = arrayOfByte[i1];
			i1++;
			c[(i13 + 2)] = arrayOfByte[i1];
		}
	}
	i1--;
	int i14;
	for (i14 = 0; i14 < i4; i14 += 2)
	{
		i1 += 2;
		arrayOfShort[i14] = ((short)(int)(256L * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 1000L));
		i1 += 2;
		arrayOfShort[(i14 + 1)] = ((short)(int)(256L * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 1000L));
	}
	i2 *= 16;
	int i15;
	for (i15 = 0; i15 < i2; i15 += 16)
	{
		i1 += 2;
		b[(i15 + 3)] = arrayOfShort[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)];
		b[(i15 + 4)] = arrayOfShort[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)];
		i1 += 2;
		b[(i15 + 5)] = arrayOfShort[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)];
		b[(i15 + 6)] = arrayOfShort[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)];
		i1 += 2;
		b[(i15 + 7)] = arrayOfShort[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)];
		b[(i15 + 8)] = arrayOfShort[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)];
	}
	int i16;
	for (i16 = 0; i16 < i2; i16 += 16)
	{
		i1 += 2;
		b[(i16 + 9)] = ((short)(byte)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
		//T[localr.b[(i16 + 9)]] = true;
	}
	free(arrayOfShort);
	//U();
}
