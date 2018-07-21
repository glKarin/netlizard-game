#include "clone3d_reader.h"

#include "nl_util.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// clone 3d glo version

#define dprintfsi(s, d) nlprintf("Clone 3D : "#s"->%d\n", d)
#define dprintfsii(s, d, d2) nlprintf("Clone 3D : ""%d - "#s"->%d\n", d, d2)
#define dprintfss(s) nlprintf("Clone 3D : "#s"\n")

typedef struct _class__c__scene
{
  array *short_array_3__a__vertex; // short[]
  array *short_array_7__b__primitive; // short[]
  short short__c__end; // = 0;  最后一个物品索引
  int int__d__aabb;
  int int__e__aabb;
  int int__f__aabb;
  int int__g__aabb;
  int int__h__aabb;
  int int__i__aabb;
  array *int_array_2__j__plane; // int[]
  int int__k__vertex_count; // a
  int int__l__primitive_count; // b = 0;
  byte byte_array_9__m__bsp[9]; // -1, -1, -1, -1, -1, -1, -1, ?, ?
  int int__n__bsp; // = 0;
  short short__o__begin; // = 0; 第一个物品索引
} class__c__scene;

typedef struct _class__k__bsp
{
  byte byte__a__direction;
	int int_array_3__a__normal[3];
  int int_array_4x3__b__plane[4][3]; //e[] b = new e[4];
  short short__c__prev_scene;
  short short__d__next_scene;
  boolean e; // = false;
} class__k__bsp;

typedef struct _class__i__item
{
  array *short_array_3__a__vertex; // short[]
  array *short_array_16__b__primitive; // short[]
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
  byte byte__s__obj;
  boolean t; // = true;
} class__i__item;

typedef struct _class__t__role
{
  array *short_2_array_3__a__vertex; // short[][]
  array *short_array_16__b__primitive; // short[]
  array *c; // byte[][]
  int d;
  int e;
} class__t__role;

typedef struct _class__g__lvl
{
  int int__aa__rotation;
  int int__Z__rotation;
  int int_array__ab__translation[3];
	array *class_c_array__g__scene;
	array *short_array__bG__texcoord;
	array *class_i_array__e__item;
	array *int_array__c__normal;
	array *class_k_array__f__bsp;
} class__g__lvl;

static class__g__lvl * class_g__function_i_1int__scene(const byte paramInt[]);
static void class_g__function_P_void__item(class__i__item *e, const byte arrayOfByte1[], int i7);
static void class_g__function_b_1int__role(class__t__role *obj, const byte arrayOfByte[], int index);
static void nlReadClone3DMapItems(array *i_e);


NETLizard_3D_Model * nlReadClone3DItemModelFile(const char* name, int index)
{
	if(!name)
		return NULL;
	array *arr = nlReadFile(name);
	if(!arr)
		return NULL;
	NETLizard_3D_Model *model = NEW(NETLizard_3D_Model);
	ZERO(model, NETLizard_3D_Model);

	class__i__item obj;
	class_g__function_P_void__item(&obj, arr->array, index);
	array *item_meshes = new_array(nl_user, 1, NULL, sizeof(NETLizard_3D_Item_Mesh));
	NETLizard_3D_Item_Mesh *mesh = ((NETLizard_3D_Item_Mesh *)(item_meshes->array));
	mesh->item_mesh.vertex = NULL;
	mesh->item_mesh.primitive = NULL;
	mesh->pos[0] = 0;
	mesh->pos[1] = 0;
	mesh->pos[2] = 0;
	mesh->angle[0] = 0;
	mesh->angle[1] = 0;
	mesh->obj_index = index;
	if(obj.short_array_3__a__vertex && obj.short_array_16__b__primitive)
	{
		mesh->item_mesh.vertex = new_array(nl_int, obj.short_array_3__a__vertex->length, NULL, 0);
		int *im_v = (int *)(mesh->item_mesh.vertex->array);
		short *i_a = (short *)(obj.short_array_3__a__vertex->array);
		int j;
		for(j = 0; j < obj.short_array_3__a__vertex->length; j++)
		{
			im_v[j] = i_a[j];
		}
		mesh->item_mesh.primitive = new_array(nl_user, obj.short_array_16__b__primitive->length / 16, NULL, sizeof(NETLizard_3D_Primitive));
		short *i_b = (short *)(obj.short_array_16__b__primitive->array);
		int k = 0;
		for(j = 0; j < obj.short_array_16__b__primitive->length; j += 16)
		{
			NETLizard_3D_Primitive *p = ((NETLizard_3D_Primitive *)(mesh->item_mesh.primitive->array)) + k;
			p->index[0] = i_b[j];
			p->index[1] = i_b[j + 1];
			p->index[2] = i_b[j + 2];
			p->texcoord[0] = i_b[j + 3];
			p->texcoord[1] = i_b[j + 4];
			p->texcoord[2] = i_b[j + 5];
			p->texcoord[3] = i_b[j + 6];
			p->texcoord[4] = i_b[j + 7];
			p->texcoord[5] = i_b[j + 8];
			p->tex_index = i_b[j + 9];
			p->plane.position[0] = i_a[p->index[0]];
			p->plane.position[1] = i_a[p->index[0] + 1];
			p->plane.position[2] = i_a[p->index[0] + 2];
			p->plane.normal[0] = i_b[j + 10];
			p->plane.normal[1] = i_b[j + 11];
			p->plane.normal[2] = i_b[j + 12];
			k++;
		}
		mesh->item_mesh.ortho[0] = obj.int__e__aabb >> 16;
		mesh->item_mesh.ortho[1] = obj.int__f__aabb >> 16;
		mesh->item_mesh.ortho[2] = obj.int__g__aabb >> 16;
		mesh->item_mesh.ortho[3] = obj.int__h__aabb >> 16;
		mesh->item_mesh.ortho[4] = obj.int__i__aabb >> 16;
		mesh->item_mesh.ortho[5] = obj.int__j__aabb >> 16;
	}

	delete_array(obj.short_array_3__a__vertex);
	delete_array(obj.short_array_16__b__primitive);
	free(obj.short_array_3__a__vertex);
	free(obj.short_array_16__b__primitive);
	delete_array(arr);
	free(arr);
	model->data = NULL;
	model->item_data = item_meshes;
	model->game = Clone_3D_Item;
	model->has_sky = 0;
	return model;
}

void nlReadClone3DMapItems(array *i_e)
{
	if(!i_e)
		return;
	int i;
	for(i = 0; i < i_e->length; i++)
	{
		class__i__item *e = ((class__i__item *)(i_e->array)) + i;
		int i11 = e->byte__s__obj;
		char subfix[strlen(CLONE3D_OBJ_SUBFIX) + 1];
		memset(subfix, '\0', sizeof(char) * (strlen(subfix) + 1));
		sprintf(subfix, CLONE3D_OBJ_SUBFIX, i11);
		char *name = NULL;
		if(game_resource_path[nl_clone_3d])
		{
			name = NEW_II(char, strlen(subfix) + strlen(game_resource_path[nl_clone_3d]) + 1 + 1);
			memset(name, '\0', sizeof(char) * ((strlen(subfix) + strlen(game_resource_path[nl_clone_3d]) + 1 + 1)));
			sprintf(name, "%s/%s", game_resource_path[nl_clone_3d], subfix);
		}
		else
			name = strdup(subfix);
		array *arr = nlReadFile(name);
		free(name);
		if(arr)
		{
			class_g__function_P_void__item(e, arr->array, i11);
			delete_array(arr);
			free(arr);
		}
		else
		{
			e->short_array_3__a__vertex = NULL;
			e->short_array_16__b__primitive = NULL;
		}
	}
}

NETLizard_3D_Model * nlReadClone3DModelFile(const char* name)
{
	if(!name)
		return NULL;
	array *arr = nlReadFile(name);
	if(!arr)
		return NULL;
	byte *arrayOfByte = (byte *)(arr->array);
	class__g__lvl * lv = class_g__function_i_1int__scene(arrayOfByte);
	if(lv)
	{
		NETLizard_3D_Model *model = NEW(NETLizard_3D_Model);
		ZERO(model, NETLizard_3D_Model);
		array *c_g = lv->class_c_array__g__scene;
		array *meshes = new_array(nl_user, c_g->length, NULL, sizeof(NETLizard_3D_Mesh));
		short *bG = (short *)(lv->short_array__bG__texcoord->array);
		int i;
		for(i = 0; i < c_g->length; i++)
		{
			class__c__scene *obj = (class__c__scene *)(c_g->array) + i;
			NETLizard_3D_Mesh *mesh = ((NETLizard_3D_Mesh *)(meshes->array)) + i;
			mesh->vertex = new_array(nl_int, obj->short_array_3__a__vertex->length, NULL, 0);
			int *m_v = (int *)(mesh->vertex->array);
			short *s_a = (short *)(obj->short_array_3__a__vertex->array);
			int j;
			for(j = 0; j < obj->short_array_3__a__vertex->length; j++)
			{
				m_v[j] = s_a[j];
			}
			mesh->primitive = NULL;
			if(obj->short_array_7__b__primitive)
			{
				mesh->primitive = new_array(nl_user, obj->short_array_7__b__primitive->length / 7, NULL, sizeof(NETLizard_3D_Primitive));
				short *s_b = (short *)(obj->short_array_7__b__primitive->array);
				int k = 0;
				for(j = 0; j < obj->short_array_7__b__primitive->length; j += 7)
				{
					NETLizard_3D_Primitive *p = ((NETLizard_3D_Primitive *)(mesh->primitive->array)) + k;
					p->index[0] = s_b[j];
					p->index[1] = s_b[j + 1];
					p->index[2] = s_b[j + 2];
					p->texcoord[0] = bG[(s_b[j + 3])];
					p->texcoord[1] = bG[(s_b[j + 3]) + 1];
					p->texcoord[2] = bG[(s_b[j + 4])];
					p->texcoord[3] = bG[(s_b[j + 4]) + 1];
					p->texcoord[4] = bG[(s_b[j + 5])];
					p->texcoord[5] = bG[(s_b[j + 5]) + 1];
					p->tex_index = (s_b[j + 6]) & 0xff;
					k++;
				}
			}
			mesh->plane = NULL;
			if(obj->int_array_2__j__plane)
			{
				mesh->plane = new_array(nl_user, obj->int_array_2__j__plane->length / 2, NULL, sizeof(NETLizard_3D_Plane));
				int *c = (int *)(lv->int_array__c__normal->array);
				int *j_array = (int *)(obj->int_array_2__j__plane->array);
				int k = 0;
				for(j = 0; j < obj->int_array_2__j__plane->length; j += 2)
				{
					int normal_index = j_array[j];
					int position_index = j_array[j + 1];
					NETLizard_3D_Plane *plane = ((NETLizard_3D_Plane *)(mesh->plane->array)) + k;
					plane->normal[0] = c[normal_index];
					plane->normal[1] = c[normal_index + 1];
					plane->normal[2] = c[normal_index + 2];
					plane->position[0] = s_a[position_index];
					plane->position[1] = s_a[position_index + 1];
					plane->position[2] = s_a[position_index + 2];
					k++;
				}
			}
			mesh->ortho[0] = obj->int__d__aabb >> 16;
			mesh->ortho[1] = obj->int__e__aabb >> 16;
			mesh->ortho[2] = obj->int__f__aabb >> 16;
			mesh->ortho[3] = obj->int__g__aabb >> 16;
			mesh->ortho[4] = obj->int__h__aabb >> 16;
			mesh->ortho[5] = obj->int__i__aabb >> 16;
			mesh->item_index_range[0] = obj->short__o__begin;
			mesh->item_index_range[1] = obj->short__c__end;

			mesh->bsp = NULL;
			if(obj->int__n__bsp)
			{
				mesh->bsp = new_array(nl_int, obj->int__n__bsp, NULL, 0);
				int *bsp_index = (int *)(mesh->bsp->array);
				for(j = 0; j < obj->int__n__bsp; j++)
				{
					bsp_index[j] = obj->byte_array_9__m__bsp[j];
				}
			}
		}

		array *i_e = lv->class_i_array__e__item;
		array *item_meshes = new_array(nl_user, i_e->length, NULL, sizeof(NETLizard_3D_Item_Mesh));
		for(i = 0; i < i_e->length; i++)
		{
			NETLizard_3D_Item_Mesh *mesh = ((NETLizard_3D_Item_Mesh *)(item_meshes->array)) + i;
			class__i__item *obj = ((class__i__item *)(i_e->array)) + i;
			if(!obj->short_array_3__a__vertex || !obj->short_array_16__b__primitive)
			{
				mesh->item_mesh.vertex = NULL;
				mesh->item_mesh.primitive = NULL;
				continue;
			}
			mesh->pos[0] = obj->int__l__translation >> 16;
			mesh->pos[1] = obj->int__m__translation >> 16;
			mesh->pos[2] = obj->int__n__translation >> 16;
			mesh->angle[0] = obj->int__o__rotation;
			mesh->angle[1] = obj->int__p__rotation;
			mesh->obj_index = obj->byte__s__obj;
			mesh->item_mesh.vertex = new_array(nl_int, obj->short_array_3__a__vertex->length, NULL, 0);
			int *im_v = (int *)(mesh->item_mesh.vertex->array);
			short *i_a = (short *)(obj->short_array_3__a__vertex->array);
			int j;
			for(j = 0; j < obj->short_array_3__a__vertex->length; j++)
			{
				im_v[j] = i_a[j];
			}
			mesh->item_mesh.primitive = new_array(nl_user, obj->short_array_16__b__primitive->length / 16, NULL, sizeof(NETLizard_3D_Primitive));
			short *i_b = (short *)(obj->short_array_16__b__primitive->array);
			int k = 0;
			for(j = 0; j < obj->short_array_16__b__primitive->length; j += 16)
			{
				NETLizard_3D_Primitive *p = ((NETLizard_3D_Primitive *)(mesh->item_mesh.primitive->array)) + k;
				p->index[0] = i_b[j];
				p->index[1] = i_b[j + 1];
				p->index[2] = i_b[j + 2];
				p->texcoord[0] = i_b[j + 3];
				p->texcoord[1] = i_b[j + 4];
				p->texcoord[2] = i_b[j + 5];
				p->texcoord[3] = i_b[j + 6];
				p->texcoord[4] = i_b[j + 7];
				p->texcoord[5] = i_b[j + 8];
				p->tex_index = i_b[j + 9];
				p->plane.position[0] = i_a[p->index[0]];
				p->plane.position[1] = i_a[p->index[0] + 1];
				p->plane.position[2] = i_a[p->index[0] + 2];
				p->plane.normal[0] = i_b[j + 10];
				p->plane.normal[1] = i_b[j + 11];
				p->plane.normal[2] = i_b[j + 12];
				k++;
			}
			mesh->item_mesh.ortho[0] = obj->int__e__aabb >> 16;
			mesh->item_mesh.ortho[1] = obj->int__f__aabb >> 16;
			mesh->item_mesh.ortho[2] = obj->int__g__aabb >> 16;
			mesh->item_mesh.ortho[3] = obj->int__h__aabb >> 16;
			mesh->item_mesh.ortho[4] = obj->int__i__aabb >> 16;
			mesh->item_mesh.ortho[5] = obj->int__j__aabb >> 16;
		}

	model->bsp_data = NULL;
	if(lv->class_k_array__f__bsp)
	{
		class__k__bsp *bsp = (class__k__bsp *)(lv->class_k_array__f__bsp->array);
		model->bsp_data = new_array(nl_user, lv->class_k_array__f__bsp->length, NULL, sizeof(NETLizard_BSP_Tree_Node));
		NETLizard_BSP_Tree_Node *bsp_data = (NETLizard_BSP_Tree_Node *)(model->bsp_data->array);
		int j;
		for(j = 0; j < lv->class_k_array__f__bsp->length; j++)
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

		model->data = meshes;
		model->item_data = item_meshes;
		model->start_angle[0] = lv->int__Z__rotation;
		model->start_angle[1] = lv->int__aa__rotation;
		model->start_pos[0] = lv->int_array__ab__translation[0] >> 16;
		model->start_pos[1] = lv->int_array__ab__translation[1] >> 16;
		model->start_pos[2] = lv->int_array__ab__translation[2] >> 16;
		model->game = Clone_3D_Map;
		model->has_sky = 0;

		for(i = 0; i < lv->class_c_array__g__scene->length; i++)
		{
			class__c__scene *obj = ((class__c__scene *)(lv->class_c_array__g__scene->array)) + i;
			delete_array(obj->short_array_3__a__vertex);
			delete_array(obj->short_array_7__b__primitive);
			delete_array(obj->int_array_2__j__plane);
			free(obj->short_array_3__a__vertex);
			free(obj->short_array_7__b__primitive);
			free(obj->int_array_2__j__plane);
		}
		delete_array(lv->class_c_array__g__scene);
		free(lv->class_c_array__g__scene);
		delete_array(lv->int_array__c__normal);
		free(lv->int_array__c__normal);
		for(i = 0; i < lv->class_i_array__e__item->length; i++)
		{
			class__i__item *obj = ((class__i__item *)(lv->class_i_array__e__item->array)) + i;
			delete_array(obj->short_array_3__a__vertex);
			delete_array(obj->short_array_16__b__primitive);
			free(obj->short_array_3__a__vertex);
			free(obj->short_array_16__b__primitive);
		}
		delete_array(lv->class_i_array__e__item);
		free(lv->class_i_array__e__item);
		delete_array(lv->short_array__bG__texcoord);
		free(lv->short_array__bG__texcoord);
		delete_array(lv->class_k_array__f__bsp);
		free(lv->class_k_array__f__bsp);
		free(lv);
		return model;
	}
	return NULL;
}

NETLizard_3D_Model * nlReadClone3DRoleModelFile(const char* name, int index)
{
	if(!name)
		return NULL;
	array *arr = nlReadFile(name);
	if(!arr)
		return NULL;
	NETLizard_3D_Model *model = NEW(NETLizard_3D_Model);
	ZERO(model, NETLizard_3D_Model);

	class__t__role obj;
	class_g__function_b_1int__role(&obj, arr->array, index);
	array *item_meshes = new_array(nl_user, obj.short_2_array_3__a__vertex->length, NULL, sizeof(NETLizard_3D_Item_Mesh));
	int i;
	for(i = 0; i < obj.short_2_array_3__a__vertex->length; i++)
	{
		NETLizard_3D_Item_Mesh *mesh = ((NETLizard_3D_Item_Mesh *)(item_meshes->array)) + i;
		mesh->item_mesh.vertex = NULL;
		mesh->item_mesh.primitive = NULL;
		mesh->pos[0] = 0;
		mesh->pos[1] = 0;
		mesh->pos[2] = 0;
		mesh->angle[0] = 0;
		mesh->angle[1] = 0;
		mesh->obj_index = index;
		array *a = ((array **)(obj.short_2_array_3__a__vertex->array))[i];
		if(a && obj.short_array_16__b__primitive)
		{
			mesh->item_mesh.vertex = new_array(nl_int, a->length, NULL, 0);
			int *m_v = (int *)(mesh->item_mesh.vertex->array);
			short *r_a = (short *)(a->array);
			int j;
			for(j = 0; j < a->length; j++)
			{
				m_v[j] = r_a[j];
			}
			mesh->item_mesh.primitive = new_array(nl_user, obj.short_array_16__b__primitive->length / 16, NULL, sizeof(NETLizard_3D_Primitive));
			short *r_b = (short *)(obj.short_array_16__b__primitive->array);
			int k = 0;
			for(j = 0; j < obj.short_array_16__b__primitive->length; j += 16)
			{
				NETLizard_3D_Primitive *p = ((NETLizard_3D_Primitive *)(mesh->item_mesh.primitive->array)) + k;
				p->index[0] = r_b[j];
				p->index[1] = r_b[j + 1];
				p->index[2] = r_b[j + 2];
				p->texcoord[0] = r_b[j + 3];
				p->texcoord[1] = r_b[j + 4];
				p->texcoord[2] = r_b[j + 5];
				p->texcoord[3] = r_b[j + 6];
				p->texcoord[4] = r_b[j + 7];
				p->texcoord[5] = r_b[j + 8];
				p->tex_index = r_b[j + 9];
				k++;
			}
		}
	}

	for(i = 0; i < obj.short_2_array_3__a__vertex->length; i++)
	{
		delete_array(((array **)(obj.short_2_array_3__a__vertex->array))[i]);
	}
	delete_array(obj.short_2_array_3__a__vertex);
	free(obj.short_2_array_3__a__vertex);
	delete_array(obj.short_array_16__b__primitive);
	free(obj.short_array_16__b__primitive);
	for(i = 0; i < obj.c->length; i++)
	{
		delete_array(((array **)(obj.c->array))[i]);
	}
	delete_array(obj.c);
	free(obj.c);
	delete_array(arr);
	free(arr);
	model->data = NULL;
	model->item_data = item_meshes;
	model->game = Clone_3D_Role;
	model->has_sky = 0;
	return model;
}

/* ****** static ****** */

class__g__lvl * class_g__function_i_1int__scene(const byte paramInt[])
{
	//byte *bg = NULL;
	int Z = 0;
	int aa = 0;
	int ab[3] = {0, 0, 0};
	int bn = 0;
	short Y = 0;
	array *int_c = NULL;
	array *c_g = NULL;
	//byte *Q = NULL;
	array *i_e = NULL;
	//short *bb = NULL;
	short N = 0;
	array *short_bG = NULL;
	/*
		 b = 0;
		 if (paramInt == 9) {
		 b = 61;
		 }
		 */
	int i1 = -2;
	int i4;
	i1 += 2;
	if ((i4 = nlMargeDigit(paramInt[0], paramInt[1])) != 0) {
		//bg = NEW_II(byte, i4);
	}
	int i2;
	for (i2 = 0; i2 < i4; i2++)
	{
		i1 += 2;
		//bg[i2] = ((byte)nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]));
	}
	i1 += 2;
	ab[0] = (nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 16);
	i1 += 2;
	ab[1] = (nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 16);
	i1 += 2;
	ab[2] = (nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 16);
	i1 += 2;
	Z = nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]);
	i1 += 2;
	if ((aa = nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)])) > 361) {
		aa -= 65536;
	}
	if (Z > 361) {
		Z -= 65536;
	}
	if (aa < 0) {
		aa = -aa;
	} else {
		aa = 360 - aa;
	}
	if (aa == 360) {
		aa = 0;
	}
	if (Z < 0) {
		Z = 270 + Z;
	} else {
		Z = 270 - Z;
	}
	if (Z == 360) {
		Z = 0;
	}
	bn = 270;
	dprintfss("Get start position and axis");
	i1 += 2;
	Y = (short)nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]);
	dprintfsi("Map scene count", Y);
	i1 += 2;
	i2 = nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]);
	dprintfsi("Map normal count", i2);
	int_c = new_array(nl_int, i2, NULL, 0);
	int *c = (int *)(int_c->array);
	for (i4 = 0; i4 < i2; i4 += 3)
	{
		i1 += 2;
		c[i4] = ((int)(65536 * nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) / 10000L));
		i1 += 2;
		c[(i4 + 1)] = ((int)(65536 * nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) / 10000L));
		i1 += 2;
		c[(i4 + 2)] = ((int)(65536 * nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) / 10000L));
	}
	dprintfss("Get map normal");
	i1 += 2;
	i2 = nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]);
	dprintfsi("Texcoord count", i2);
	short_bG = new_array(nl_short, i2, NULL, 0);
	short *bG = (short *)(short_bG->array);
	for (i4 = 0; i4 < i2; i4 += 2)
	{
		i1 += 2;
		bG[i4] = ((short)(int)(128 * nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) / 100L));
		i1 += 2;
		bG[(i4 + 1)] = ((short)(int)(128 * nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) / 100L));
	}
	dprintfss("Get map texcoord");
	c_g = new_array(nl_user, Y, NULL, sizeof(class__c__scene));
	class__c__scene *g = (class__c__scene *)(c_g->array);
	//Q = NEW_II(byte, Y);
	int i5;
	for (i5 = 0; i5 < Y; i5++)
	{
		dprintfsi("Get map scene data", i5);
		i1 += 2;
		g[i5].int__d__aabb = (nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 16);
		i1 += 2;
		g[i5].int__e__aabb = (nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 16);
		i1 += 2;
		g[i5].int__f__aabb = (nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 16);
		i1 += 2;
		g[i5].int__g__aabb = (nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 16);
		i1 += 2;
		g[i5].int__h__aabb = (nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 16);
		i1 += 2;
		g[i5].int__i__aabb = (nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 16);
		dprintfss("Get scene AABB");
		i1 += 2;
		i4 = nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]);
		dprintfsi("Scene vertex coord count", i4);
		i1 += 2;
		i2 = nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]);
		dprintfsi("Scene primitive count", i2);
		g[i5].short_array_3__a__vertex = new_array(nl_short, i4 * 3, NULL, 0);
		short *a = (short *)(g[i5].short_array_3__a__vertex->array);
		g[i5].int__k__vertex_count = i4;
		g[i5].short_array_7__b__primitive = NULL;
		short *b = NULL;
		if(i2 != 0)
		{
			g[i5].short_array_7__b__primitive = new_array(nl_short, i2 * 7, NULL, 0);
			b = (short *)(g[i5].short_array_7__b__primitive->array);
		}
		g[i5].int__l__primitive_count = i2;
		int i6;
		for (i6 = 0; i6 < i4; i6++)
		{
			i1 += 2;
			a[(i6 * 3)] = ((short)nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]));
			i1 += 2;
			a[(i6 * 3 + 1)] = ((short)nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]));
			i1 += 2;
			a[(i6 * 3 + 2)] = ((short)nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]));
		}
		dprintfss("Get scene vertex coord");
		short *arrayOfShort = NULL;
		if(g[i5].short_array_7__b__primitive)
			arrayOfShort = ((short *)(g[i5].short_array_7__b__primitive->array));
		for (i6 = 0; i6 < i2; i6++)
		{
			i4 = i6 * 7;
			i1 += 2;
			b[i4] = ((short)(nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) * 3));
			i1 += 2;
			b[(i4 + 1)] = ((short)(nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) * 3));
			i1 += 2;
			b[(i4 + 2)] = ((short)(nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) * 3));
		}
		dprintfss("Get scene primitive vertex coord index");
		i1 += 2;
		i4 = nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]);
		dprintfsi("Scene plane count", i4);
		g[i5].int_array_2__j__plane = NULL;
		if(i4)
		{
			g[i5].int_array_2__j__plane = new_array(nl_int, i4 << 1, NULL, 0);
			int *j = (int *)(g[i5].int_array_2__j__plane->array);
			for (i6 = 0; i6 < i4; i6++)
			{
				i1 += 2;
				j[(i6 << 1)] = (nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) * 3);
				i1 += 2;
				j[((i6 << 1) + 1)] = arrayOfShort[(nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) * 7)];
			}
			dprintfss("Get scene plane normal index and point vertex coord index");
		}
		int i7;
		for (i7 = 0; i7 < i2; i7++)
		{
			i4 = i7 * 7;
			i1 += 2;
			b[(i4 + 3)] = ((short)(nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 1));
			i1 += 2;
			b[(i4 + 4)] = ((short)(nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 1));
			i1 += 2;
			b[(i4 + 5)] = ((short)(nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 1));
		}
		dprintfss("Get scene texcoord index");
		i1++;
		int i4;
		for (i4 = 0; i4 < i2; i4++)
		{
			i1++;
			int i8;
			if ((i8 = paramInt[i1]) < 0) {
				i8 += 256;
			}
			b[(i4 * 7 + 6)] = ((short)i8);
			if (b[(i4 * 7 + 6)] < 50) {
				//aN[g[i5].b[(i4 * 7 + 6)]] = true;
			}
		}
		for (i7 = 0; i7 < i2; i7++)
		{
			i1++;
			if ((i4 = (i4 = nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)])) & 0xFF) < 70) {
				i4 = 70;
			}
			int i8;
			i8 = b[(i7 * 7 + 6)] & 0xFF;
			b[(i7 * 7 + 6)] = ((short)(i4 << 8 | i8));
		}
		dprintfss("Get primitive texture index");
		i1--;
	}
	i1 += 2;
	i2 = nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]);
	array *class_k_array__f__bsp = new_array(nl_user, i2, NULL, sizeof(class__k__bsp));
	class__k__bsp *f = (class__k__bsp *)(class_k_array__f__bsp->array);
	dprintfsi("Map BSP tree node count", i2);
	int i7;
	for (i7 = 0; i7 < i2; i7++)
	{
		for (i4 = 0; i4 < 4; i4++)
		{
			i1 += 2;
			f[i7].int_array_4x3__b__plane[i4][0]= (nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 16);
			i1 += 2;
			f[i7].int_array_4x3__b__plane[i4][1]= (nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 16);
			i1 += 2;
			f[i7].int_array_4x3__b__plane[i4][2]= (nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 16);
		}
		i1 += 2;
		i4 = (int)(65536 * nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) / 10000L);
		i1 += 2;
		i5 = (int)(65536 * nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) / 10000L);
		i1 += 2;
		int i6 = (int)(65536 * nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) / 10000L);
		i1 += 2;
		f[i7].short__c__prev_scene = ((short)(nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) - 1));
		i1 += 2;
		f[i7].short__d__next_scene = ((short)(nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) - 1));
		if (i4 != 0) {
			f[i7].byte__a__direction = 1;
		} else if (i5 != 0) {
			f[i7].byte__a__direction = 2;
		} else if (i6 != 0) {
			f[i7].byte__a__direction = 3;
		}
	}
	for (i4 = 0; i4 < i2; i4++)
	{
		if (f[i4].short__c__prev_scene < 999)
		{
			g[f[i4].short__c__prev_scene].byte_array_9__m__bsp[g[f[i4].short__c__prev_scene].int__n__bsp] = ((byte)i4);
			g[f[i4].short__c__prev_scene].int__n__bsp += 1;
		}
		if (f[i4].short__d__next_scene < 999)
		{
			g[f[i4].short__d__next_scene].byte_array_9__m__bsp[g[f[i4].short__d__next_scene].int__n__bsp] = ((byte)i4);
			g[f[i4].short__d__next_scene].int__n__bsp += 1;
		}
	}
	dprintfss("Get map BSP tree node");
	i1 += 2;
	N = (short)nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]);
	dprintfsi("Map item count", N);
	i_e = new_array(nl_user, N, NULL, sizeof(class__i__item));
	class__i__item *e = (class__i__item *)(i_e->array);
	//bb = NEW_II(short, Y);
	int i6 = 0;
	for (i7 = 0; i7 < Y; i7++)
	{
		i1 += 2;
		i4 = nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]);
		dprintfsii("Scene item count", i7, i4);
		g[i7].short__o__begin = ((short)i6);
		g[i7].short__c__end = ((short)(i6 + i4));
		int i8;
		for (i8 = 0; i8 < i4; i8++)
		{
			e[i6].q = ((short)i7);
			i1 += 2;
			e[i6].int__l__translation = (nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 16);
			i1 += 2;
			e[i6].int__m__translation = (nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 16);
			i1 += 2;
			e[i6].int__n__translation = (nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]) << 16);
			i1 += 2;
			e[i6].int__o__rotation = nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]);
			i1 += 2;
			e[i6].int__p__rotation = ((short)nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]));
			if (e[i6].int__p__rotation > 360) {
				e[i6].int__p__rotation = (65536 - e[i6].int__p__rotation);
			}
			if (e[i6].int__o__rotation > 360) {
				e[i6].int__o__rotation = (65536 - e[i6].int__o__rotation);
			}
			if (e[i6].int__p__rotation < 0) {
				e[i6].int__p__rotation = (360 + e[i6].int__p__rotation);
			}
			if (e[i6].int__o__rotation < 0) {
				e[i6].int__o__rotation = (360 + e[i6].int__o__rotation);
			} else {
				e[i6].int__o__rotation = (360 - e[i6].int__o__rotation);
			}
			if (e[i6].int__o__rotation == 360) {
				e[i6].int__o__rotation = 0;
			}
			i1 += 2;
			e[i6].byte__s__obj = ((byte)nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]));
			if (((e[i6].byte__s__obj > 2) && (e[i6].byte__s__obj < 7)) || ((e[i6].byte__s__obj > 33) && (e[i6].byte__s__obj < 38)))
			{
				//Q[i7] = 1;
				if (e[i6].byte__s__obj < 10) {
					//bb[i7] = ((short)((e[i6].n >> 16) + 150));
				} else if (e[i6].byte__s__obj < 36) {
					//bb[i7] = ((short)((e[i6].m >> 16) + 300));
				} else {
					//bb[i7] = ((short)((e[i6].l >> 16) + 300));
				}
			}
			//aL[e[i6].byte__s__obj] = true;
			i1 += 2;
			e[i6].d = ((short)nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]));
			if (e[i6].d < 0)
			{
				class__i__item *tmp2756_2755 = e + i6;
				tmp2756_2755->d = ((short)(tmp2756_2755->d + 256));
			}
			class__i__item *tmp2774_2773 = e + i6;
			tmp2774_2773->d = ((short)(tmp2774_2773->d & 0xFF));
			if (e[i6].d < 70) {
				e[i6].d = 70;
			}
			i1 += 2;
			i6++;
		}
	}

#if UNPARSED
	V = null;
	W = null;
	int i8 = 0;
	for (i4 = 0; i4 < e.length; i4++) {
		if (e[i4].s == 31) {
			i8++;
		}
	}
	V = new byte[i8 * 5];
	W = new short[i8];
	i8 = 0;
	for (i4 = 0; i4 < e.length; i4++) {
		if (e[i4].s == 31)
		{
			V[(i8 * 5)] = ((byte)i4);
			V[(i8 * 5 + 1)] = ((byte)e[i4].q);
			V[(i8 * 5 + 3)] = 0;
			V[(i8 * 5 + 4)] = 1;
			i8++;
		}
	}
	Object localObject;
	for (i7 = 0; i7 < g.length; i7++)
	{
		localObject = g[i7].m;
		g[i7].m = null;
		i2 = g[i7].n;
		g[i7].m = new byte[i2];
		for (i5 = 0; i5 < i2; i5++) {
			g[i7].m[i5] = localObject[i5];
		}
	}
#endif
	i1 += 2;
#if UNPARSED
	ah = (short)(h.b(paramInt[i1], paramInt[(i1 + 1)]) + 1);
	if (p) {
		ah = (short)(ah + 1);
	}
	aA = new byte[ah];
	i = new q[ah];
	for (i2 = 0; i2 < ah; i2++)
	{
		i[i2] = new q();
		i[i2].n = ((byte)i2);
	}
	i6 = 1;
	i[0].w = ab[0];
	i[0].x = ab[1];
	i[0].y = ab[2];
#endif
	int i9;
	for (i9 = 0; i9 < Y; i9++)
	{
		i1 += 2;
		i5 = nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]);
		int i10;
		for (i10 = 0; i10 < i5; i10++)
		{
			//localObject = i[i6];
			i1 += 2;
			//((q)localObject).w = (h.b(paramInt[i1], paramInt[(i1 + 1)]) << 16);
			i1 += 2;
			//((q)localObject).x = (h.b(paramInt[i1], paramInt[(i1 + 1)]) << 16);
			i1 += 2;
			//((q)localObject).y = (h.b(paramInt[i1], paramInt[(i1 + 1)]) << 16);
			i1 += 2;
			//((q)localObject).M = ((byte)h.b(paramInt[i1], paramInt[(i1 + 1)]));
			//i8 = ((q)localObject).M;
#if UNPARSED
			for (i7 = 0; i7 < N; i7++)
			{
				i locali;
				if (((locali = e[i7]).s > 51) && (locali.s < 56) && (locali.l == ((q)localObject).w) && (locali.m == ((q)localObject).x) && (Math.abs(locali.n - ((q)localObject).y >> 16) <= 30))
				{
					((q)localObject).O = ((byte)(locali.s - 51));
					locali.t = false;
				}
			}
			if (i8 > 30)
			{
				i8 -= 30;
				if (i8 == 1)
				{
					((q)localObject).K = 4;
					aN[4] = true;
				}
			}
			else if (i8 > 20)
			{
				i8 -= 20;
				if (i8 == 1)
				{
					((q)localObject).K = 3;
					aN[3] = true;
				}
			}
			else if (i8 > 10)
			{
				i8 -= 10;
				if (i8 == 1)
				{
					((q)localObject).K = 2;
					aN[2] = true;
				}
			}
			if (i8 == 2) {
				((q)localObject).K = 5;
			}
			if ((i8 == 3) || (i8 == 4)) {
				((q)localObject).K = 6;
			}
			((q)localObject).M = ((byte)i8);
			aO[i8] = true;
#endif
			i1 += 2;
#if UNPARSED
			if ((i3 = h.b(paramInt[i1], paramInt[(i1 + 1)])) > 360) {
				i3 -= 65536;
			}
			if (i3 < 0) {
				i3 = -i3;
			} else {
				i3 = 360 - i3;
			}
			if (i3 == 360) {
				i3 = 0;
			}
			((q)localObject).E[0] = (-h.d[i3]);
			((q)localObject).E[1] = (-h.a[i3]);
			((q)localObject).D = ((short)i3);
			((q)localObject).B = ((short)i9);
			i6++;
#endif
		}
	}
#if UNPARSED
	for (int i10 = 0; i10 < i.length; i10++) {
		i[i10].s = H[i[i10].M];
	}
#endif
	i1 += 2;
	/*aJ = */int i8 = (byte)nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]);
	//aK = new short[i8 * 3];
	int i3;
	for (i3 = 0; i3 < i8; i3++)
	{
		i1 += 2;
		//aK[(i3 * 3)] = ((short)h.b(paramInt[i1], paramInt[(i1 + 1)]));
		i1 += 2;
		//aK[(i3 * 3 + 1)] = ((short)h.b(paramInt[i1], paramInt[(i1 + 1)]));
		i1 += 2;
		//aK[(i3 * 3 + 2)] = ((short)h.b(paramInt[i1], paramInt[(i1 + 1)]));
	}
	i1 += 2;
	i1 += 2;
	//m = new byte[i8 = h.b(paramInt[i1], paramInt[(i1 + 1)])];
	i8 = nlMargeDigit(paramInt[i1], paramInt[(i1 + 1)]);
	for (i3 = 0; i3 < i8; i3++)
	{
		i1 += 2;
		//m[i3] = ((byte)h.b(paramInt[i1], paramInt[(i1 + 1)]));
	}
#if UNPARSED
	X = 0;
	for (paramInt = ah - 1; paramInt >= 0; paramInt--)
	{
		h.a(i[paramInt]);
		h.b(i[paramInt]);
		if (paramInt == 0)
		{
			X = i[paramInt].B;
			ab[0] = i[0].w;
			ab[1] = i[0].x;
			ab[2] = (i[0].y + 4587520);
			i[0].D = ((short)aa);
		}
		else
		{
			i[paramInt].A = ((byte)h.a(10));
		}
	}
	i[0].B = ((short)X);
#endif

	nlReadClone3DMapItems(i_e);
	class__g__lvl *lv = NEW(class__g__lvl);
	ZERO(lv, class__g__lvl);
	lv->int__aa__rotation = aa;
	lv->int__Z__rotation = Z;
	lv->int_array__ab__translation[0] = ab[0];
	lv->int_array__ab__translation[1] = ab[1];
	lv->int_array__ab__translation[2] = ab[2];
	lv->class_c_array__g__scene = c_g;
	lv->short_array__bG__texcoord = short_bG;
	lv->class_i_array__e__item = i_e;
	lv->class_k_array__f__bsp = class_k_array__f__bsp;
	lv->int_array__c__normal = int_c;
	return lv;
}

void class_g__function_P_void__item(class__i__item *e, const byte arrayOfByte1[], int i7)
{
	int i1 = -2;
	i1 += 2;
	e->int__e__aabb = (nlMargeDigit(arrayOfByte1[0], arrayOfByte1[1]) << 16);
	i1 += 2;
	e->int__f__aabb = (nlMargeDigit(arrayOfByte1[2], arrayOfByte1[3]) << 16);
	i1 += 2;
	e->int__g__aabb = (nlMargeDigit(arrayOfByte1[4], arrayOfByte1[5]) << 16);
	i1 += 2;
	e->int__h__aabb = (nlMargeDigit(arrayOfByte1[6], arrayOfByte1[7]) << 16);
	i1 += 2;
	e->int__i__aabb = (nlMargeDigit(arrayOfByte1[8], arrayOfByte1[9]) << 16);
	i1 += 2;
	e->int__j__aabb = (nlMargeDigit(arrayOfByte1[10], arrayOfByte1[11]) << 16);
	int i2 = e->int__e__aabb >> 16;
	int i3 = e->int__f__aabb >> 16;
	int i5 = e->int__g__aabb >> 16;
	i2 = i2 * i2 + i3 * i3 + i5 * i5;
	i3 = 65536;
	i5 = 0;
	while (i3 >>= 1 > 0) {
		if ((i5 + i3) * (i5 + i3) <= i2) {
			i5 += i3;
		}
	}
	e->d = ((i5 << 3) * 240 << 1);
	e->c = ((i5 << 1) * 252);
	//printf("%d %d %d\n", i5, ((i5 << 3) * 240 << 1), ((i5 << 1) * 252));
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i3 = nlMargeDigit(arrayOfByte1[20], arrayOfByte1[21]);
	i1 += 2;
	i2 = nlMargeDigit(arrayOfByte1[22], arrayOfByte1[23]);
	i1 += 2;
	i5 = nlMargeDigit(arrayOfByte1[24], arrayOfByte1[25]);
	e->k = i3;
	e->short_array_3__a__vertex = new_array(nl_short, i3 * 3, NULL, 0);
	e->short_array_16__b__primitive = new_array(nl_short, i2 << 4, NULL, 0);
	short *a = (short *)(e->short_array_3__a__vertex->array);
	short *b = (short *)(e->short_array_16__b__primitive->array);
	i5 <<= 1;
	int *arrayOfInt = NEW_II(int, i5);
	int i6 = 0;
	int i8;
	for (i8 = 0; i8 < i3; i8++)
	{
		i1 += 2;
		a[i6] = ((short)nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]));
		i1 += 2;
		a[(i6 + 1)] = ((short)nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]));
		i1 += 2;
		a[(i6 + 2)] = ((short)nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]));
		i6 += 3;
	}
	i6 = 0;
	for (i3 = 0; i3 < i2; i3++)
	{
		i1 += 2;
		b[i6] = ((short)(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 3));
		i1 += 2;
		b[(i6 + 1)] = ((short)(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 3));
		i1 += 2;
		b[(i6 + 2)] = ((short)(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 3));
		i6 += 16;
	}
	i6 = 0;
	i1++;
	int i9;
	for (i9 = 0; i9 < i2; i9++)
	{
		i1++;
		b[(i6 + 10)] = ((short)arrayOfByte1[i1]);
		i1++;
		b[(i6 + 11)] = ((short)arrayOfByte1[i1]);
		i1++;
		b[(i6 + 12)] = ((short)arrayOfByte1[i1]);
		i6 += 16;
	}
	i1--;
	i6 = 128;
	if ((i7 >= 44) && (i7 <= 51)) {
		i6 = 256;
	}
	for (i3 = 0; i3 < i5; i3 += 2)
	{
		i1 += 2;
		arrayOfInt[i3] = ((int)(i6 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 100L));
		i1 += 2;
		arrayOfInt[(i3 + 1)] = ((int)(i6 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 100L));
	}
	i6 = 0;
	for (i5 = 0; i5 < i2; i5++)
	{
		i1 += 2;
		b[(i6 + 3)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 1)]);
		b[(i6 + 4)] = ((short)arrayOfInt[((nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 1) + 1)]);
		i1 += 2;
		b[(i6 + 5)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 1)]);
		b[(i6 + 6)] = ((short)arrayOfInt[((nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 1) + 1)]);
		i1 += 2;
		b[(i6 + 7)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 1)]);
		b[(i6 + 8)] = ((short)arrayOfInt[((nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 1) + 1)]);
		i6 += 16;
	}
	i6 = 0;
	i1 += 2;
	for (i5 = 0; i5 < i2; i5++)
	{
		b[(i6 + 9)] = ((short)arrayOfByte1[i1]);
		//aN[localx.b[(i6 + 9)]] = true;
		i1++;
		i6 += 16;
	}
	free(arrayOfInt);
	/*
		 byte[] arrayOfByte2 = p.d.b("oi", -1);
		 for (int i6 = 0; i6 < e.length; i6++)
		 {
		 i locali;
		 if ((locali = e[i6]).s < 120)
		 {
		 i9 = locali.s << 2;
		 if (arrayOfByte2[i9] == 1) {
		 locali.c = true;
		 }
		 if (arrayOfByte2[(i9 + 1)] == 1) {
		 locali.r = true;
		 }
		 if (arrayOfByte2[(i9 + 3)] == 1) {
		 locali.k = true;
		 }
		 localx = d[locali.s];
		 locali.a = localx.a;
		 locali.b = localx.b;
		 locali.e = localx.e;
		 locali.h = localx.h;
		 locali.f = localx.f;
		 locali.i = localx.i;
		 locali.g = localx.g;
		 locali.j = localx.j;
		 }
		 }
		 int i4 = 0;
		 for (int i5 = 0; i5 < e.length; i5++) {
		 if ((e[i5].s > 39) && (e[i5].s < 44)) {
		 i4++;
		 }
		 }
		 I = new short[i4 * 3];
		 i4 = 0;
		 for (i5 = 0; i5 < e.length; i5++) {
		 if ((e[i5].s > 39) && (e[i5].s < 44))
		 {
		 I[(i4 * 3)] = ((short)i5);
		 I[(i4 * 3 + 1)] = 0;
		 I[(i4 * 3 + 2)] = 0;
		 i4++;
		 }
		 }
		 */
}

void class_g__function_b_1int__role(class__t__role *obj, const byte arrayOfByte[], int i8)
{
	int i1 = -2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	int i4 = nlMargeDigit(arrayOfByte[12], arrayOfByte[13]);
	i1 += 2;
	int i3 = nlMargeDigit(arrayOfByte[14], arrayOfByte[15]);
	i1 += 2;
	int i5 = nlMargeDigit(arrayOfByte[16], arrayOfByte[17]);
	i1 += 2;
	int i6 = nlMargeDigit(arrayOfByte[18], arrayOfByte[19]);
	obj->short_2_array_3__a__vertex = new_array(nl_pointer, i6, NULL, 0); // short[][];
	obj->c = new_array(nl_pointer, i6, NULL, 0); // byte[][];
	obj->d = i4;
	obj->e = i3;
	int i7;
	for (i7 = 0; i7 < i6; i7++)
	{
		array **a = (array **)(obj->short_2_array_3__a__vertex->array);
		array **c = (array **)(obj->c->array);
		c[i7] = new_array(nl_byte, i3 * 3, NULL, 0);
		a[i7] = new_array(nl_short, (i4 + 13) * 3, NULL, 0);
	}
	obj->short_array_16__b__primitive = new_array(nl_short, (i3 + 22) << 4, NULL, 0);
	short *b = (short *)(obj->short_array_16__b__primitive->array);
	i5 <<= 1;
	short *arrayOfShort = NEW_II(short, i5);
	int i9 = 1;
	int i10 = 1;
	if (i8 < 3) {
		i9 = -1;
	}
	if (i8 < 3) {
		i10 = -1;
	}
	int i12;
	int i11;
	for (i11 = 0; i11 < i6; i11++) {
		array *arr = ((array **)(obj->short_2_array_3__a__vertex->array))[i11];
		short *a = (short *)(arr->array);
		for (i12 = 0; i12 < i4; i12++)
		{
			i1 += 2;
			a[(i12 * 3)] = ((short)(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * i9));
			i1 += 2;
			a[(i12 * 3 + 1)] = ((short)(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * i10));
			i1 += 2;
			a[(i12 * 3 + 2)] = ((short)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
		}
	}
	i4 = i3 << 4;
	for (i11 = 0; i11 < i4; i11 += 16)
	{
		i1 += 2;
		b[i11] = ((short)(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 3));
		i1 += 2;
		b[(i11 + 1)] = ((short)(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 3));
		i1 += 2;
		b[(i11 + 2)] = ((short)(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 3));
	}
	i4 = i3 * 3;
	i1++;
	for (i11 = 0; i11 < i6; i11++) {
		for (i12 = 0; i12 < i4; i12 += 3)
		{
			byte *c = (byte *)((((array **)(obj->c->array))[i11])->array);
			i1++;
			c[i12] = ((byte)(arrayOfByte[i1] * i9));
			i1++;
			c[(i12 + 1)] = ((byte)(arrayOfByte[i1] * i10));
			i1++;
			c[(i12 + 2)] = arrayOfByte[i1];
		}
	}
	i1--;
	for (i4 = 0; i4 < i5; i4 += 2)
	{
		i1 += 2;
		arrayOfShort[i4] = ((short)(int)(256L * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 1000L));
		i1 += 2;
		arrayOfShort[(i4 + 1)] = ((short)(int)(256L * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 1000L));
	}
	i3 <<= 4;
	for (i4 = 0; i4 < i3; i4 += 16)
	{
		i1 += 2;
		b[(i4 + 3)] = arrayOfShort[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 1)];
		b[(i4 + 4)] = arrayOfShort[((nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 1) + 1)];
		i1 += 2;
		b[(i4 + 5)] = arrayOfShort[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 1)];
		b[(i4 + 6)] = arrayOfShort[((nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 1) + 1)];
		i1 += 2;
		b[(i4 + 7)] = arrayOfShort[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 1)];
		b[(i4 + 8)] = arrayOfShort[((nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 1) + 1)];
	}
	for (i4 = 0; i4 < i3; i4 += 16)
	{
		i1 += 2;
		b[(i4 + 9)] = ((byte)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
		//aN[localt.b[(i4 + 9)]] = true;
	}
	free(arrayOfShort);
}
