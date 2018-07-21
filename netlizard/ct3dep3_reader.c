#include "ct3dep3_reader.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define dprintfsi(s, d) nlprintf("CT 3D Ep3 : "#s"->%d\n", d)
#define dprintfsii(s, d, d2) nlprintf("CT 3D Ep3 : ""%d - "#s"->%d\n", d, d2)
#define dprintfss(s) nlprintf("CT 3D Ep3 : "#s"\n")
#define dprintfs(s) nlprintf("CT 3D Ep3 : %s\n", s)

// ct3d ep3 no jad

void ct3dep3_a(array *data, int paramInt1, int paramInt2);
typedef struct _class__f__scene
{
  array *short_array_3__a__vertex;
  array *int_array_7__b__primitive;
  int c;
  int d;
  int int__e__end; // = 0;
  int int__f__aabb;
  int int__g__aabb;
  int int__h__aabb;
  int int__i__aabb;
  int int__j__aabb;
  int int__k__aabb;
  array *int_array_2__l__plane;
  int m;
  int n;
  int int_array_7__o__bsp[7]; // = new int[7];
  int int__p__bsp; // = 0;
  int int__q__begin; // = 0;
} class__f__scene;

typedef struct _class__a__bsp
{
  byte byte__a__direction;
	int int_array_3__a__normal[3];
  int int_array_4x3__b__plane[4][3]; // u[] b = new u[4];
  int int__c__prev_scene;
  int int__d__next_scene;
  boolean e; // = false;
} class__a__bsp;

typedef struct _class__i__item
{
  array *int_array_6__a__vertex;
  array *int_array_16__b__primitive;
  boolean c;
  boolean d;
  short e; // = 0;
  int int__f__aabb;
  int int__g__aabb;
  int int__h__aabb;
  int int__i__aabb;
  int int__j__aabb;
  int int__k__aabb;
  boolean l;
  int int__m__translation;
  int int__n__translation;
  int int__o__translation;
  int int__p__rotation; // = 0;
  int int__q__rotation; // = 0;
  short r;
  boolean s;
  byte byte__t__obj;
  boolean u; // = true;
} class__i__item;

typedef struct _class__t__lvl
{
	int int_array__fd__translation[3];
	int int__fa__rotation;
	int int__fc__rotation;
	array *int_array__o__normal;
	array *int_array__gg__texcoord;
	array *class_f_array__v__scene;
	array *class_i_array__q__item;
	array *class_a_array__t__bsp;
} class__t__lvl;

static class__t__lvl * class_t__function_b_1int_2bool__scene(const byte arrayOfByte[], boolean online);
static void class_t__function_av_void__item(class__i__item *p, const byte arrayOfByte1[]);
static void nlReadCT3DEp3MapItems(array *i_q);
static void ct3dep3_god_mode_version__class_b__function_a_1string_2int__decode_recordstore_record(array *arr);

NETLizard_3D_Model * nlReadCT3DEp3ModelFile(const char *name, int paramInt)
{
	if(!name)
		return NULL;
	if(paramInt == 13 || paramInt == 15)
		return NULL; // TODO: Level 13 and 15 is not support now.
	array *arr = nlReadFile(name);
	if(!arr)
		return NULL;
	int dr = 0;
	if (paramInt == 6 || paramInt == 8 || paramInt == 9 || paramInt == 10) {
		dr = 1;
	}
	boolean b = (paramInt >= 8) ? _true : _false;
	/*
	if(b)
		ct3dep3_a(arr, 105, 20); // UNUSED online level(8 - 15), now not support to read.
		*/
	if(b)
		ct3dep3_god_mode_version__class_b__function_a_1string_2int__decode_recordstore_record(arr); // in j2me, it is get record from record store, and decode data.

	byte *arrayOfByte = (byte *)(arr->array);
	class__t__lvl *lv = class_t__function_b_1int_2bool__scene(arrayOfByte, b);
	if(!lv)
		return NULL;
	NETLizard_3D_Model *model = NEW(NETLizard_3D_Model);
	ZERO(model, NETLizard_3D_Model);
	array *f_v = lv->class_f_array__v__scene;
	int *gg = (int *)(lv->int_array__gg__texcoord->array);
	int *o = (int *)(lv->int_array__o__normal->array);
	model->data = new_array(nl_user, f_v->length, NULL, sizeof(NETLizard_3D_Mesh));
	model->has_sky = dr;
	model->game = CT_3D_Ep3_Map;

	int i;
	for(i = 0; i < f_v->length; i++)
	{
		NETLizard_3D_Mesh *mesh = ((NETLizard_3D_Mesh *)(model->data->array)) + i;
		class__f__scene *obj = ((class__f__scene *)(f_v->array)) + i;
		mesh->vertex = new_array(nl_int, obj->short_array_3__a__vertex->length, NULL, 0);
		int *m_v = (int *)(mesh->vertex->array);
		short *s_a = (short *)(obj->short_array_3__a__vertex->array);
		int j;
		for(j = 0; j < obj->short_array_3__a__vertex->length; j++)
		{
			m_v[j] = s_a[j];
		}
		
		mesh->primitive = new_array(nl_user, obj->int_array_7__b__primitive->length / 7, NULL, sizeof(NETLizard_3D_Primitive));
		int *s_b = (int *)(obj->int_array_7__b__primitive->array);
		int k = 0;
		for(j = 0; j < obj->int_array_7__b__primitive->length; j += 7)
		{
			NETLizard_3D_Primitive *p = ((NETLizard_3D_Primitive *)(mesh->primitive->array)) + k;
			p->index[0] = s_b[j];
			p->index[1] = s_b[j + 1]; 
			p->index[2] = s_b[j + 2];
			p->texcoord[0] = gg[(s_b[j + 3])];
			p->texcoord[1] = gg[(s_b[j + 3]) + 1];
			p->texcoord[2] = gg[(s_b[j + 4])];
			p->texcoord[3] = gg[(s_b[j + 4]) + 1];
			p->texcoord[4] = gg[(s_b[j + 5])];
			p->texcoord[5] = gg[(s_b[j + 5]) + 1];
			p->tex_index = (s_b[j + 6]) & 0xff;
			k++;
		}
		mesh->plane = new_array(nl_user, obj->int_array_2__l__plane->length / 2, NULL, sizeof(NETLizard_3D_Plane));
		int *l = (int *)(obj->int_array_2__l__plane->array);
		k = 0;
		for(j = 0; j < obj->int_array_2__l__plane->length; j += 2)
		{
			int normal_index = l[j];
			int position_index = l[j + 1];
			NETLizard_3D_Plane *plane = ((NETLizard_3D_Plane *)(mesh->plane->array)) + k;
			plane->normal[0] = o[normal_index];
			plane->normal[1] = o[normal_index + 1];
			plane->normal[2] = o[normal_index + 2];
			plane->position[0] = s_a[position_index];
			plane->position[1] = s_a[position_index + 1];
			plane->position[2] = s_a[position_index + 2];
			k++;
		}
		mesh->ortho[0] = obj->int__f__aabb >> 16;
		mesh->ortho[1] = obj->int__g__aabb >> 16;
		mesh->ortho[2] = obj->int__h__aabb >> 16;
		mesh->ortho[3] = obj->int__i__aabb >> 16;
		mesh->ortho[4] = obj->int__j__aabb >> 16;
		mesh->ortho[5] = obj->int__k__aabb >> 16;
		mesh->item_index_range[0] = obj->int__q__begin;
		mesh->item_index_range[1] = obj->int__e__end;

		mesh->bsp = NULL;
		if(obj->int__p__bsp)
		{
			mesh->bsp = new_array(nl_int, obj->int__p__bsp, NULL, 0);
			int *bsp_index = (int *)(mesh->bsp->array);
			for(j = 0; j < obj->int__p__bsp; j++)
			{
				bsp_index[j] = obj->int_array_7__o__bsp[j];
			}
		}
	}

	array *i_q = lv->class_i_array__q__item;
	model->item_data = new_array(nl_user, i_q->length, NULL, sizeof(NETLizard_3D_Item_Mesh));
	for(i = 0; i < i_q->length; i++)
	{
		NETLizard_3D_Item_Mesh *mesh = ((NETLizard_3D_Item_Mesh *)(model->item_data->array)) + i;
		class__i__item *obj = ((class__i__item *)(i_q->array)) + i;
		if(!obj->int_array_6__a__vertex || !obj->int_array_16__b__primitive)
		{
			mesh->item_mesh.vertex = NULL;
			mesh->item_mesh.primitive = NULL;
			continue;
		}
		mesh->pos[0] = obj->int__m__translation >> 16;
		mesh->pos[1] = obj->int__n__translation >> 16;
		mesh->pos[2] = obj->int__o__translation >> 16;
		mesh->angle[0] = obj->int__p__rotation;
		mesh->angle[1] = obj->int__q__rotation;
		mesh->obj_index = obj->byte__t__obj;
		mesh->item_mesh.ortho[0] = obj->int__f__aabb >> 16;
		mesh->item_mesh.ortho[1] = obj->int__g__aabb >> 16;
		mesh->item_mesh.ortho[2] = obj->int__h__aabb >> 16;
		mesh->item_mesh.ortho[3] = obj->int__i__aabb >> 16;
		mesh->item_mesh.ortho[4] = obj->int__j__aabb >> 16;
		mesh->item_mesh.ortho[5] = obj->int__k__aabb >> 16;
		mesh->item_mesh.vertex = new_array(nl_int, obj->int_array_6__a__vertex->length / 2, NULL, 0);
		int j;
		int *im_v = (int *)(mesh->item_mesh.vertex->array);
		int *i_a = (int *)(obj->int_array_6__a__vertex->array);
		int k = 0;
		for(j = 0; j < obj->int_array_6__a__vertex->length; j += 6)
		{
			im_v[k] = i_a[j] >> 16;
			im_v[k + 1] = i_a[j + 1] >> 16;
			im_v[k + 2] = i_a[j + 2] >> 16;
			k += 3;
		}
		mesh->item_mesh.primitive = new_array(nl_user, obj->int_array_16__b__primitive->length / 16, NULL, sizeof(NETLizard_3D_Primitive));
		int *i_b = (int *)(obj->int_array_16__b__primitive->array);
		k = 0;
		for(j = 0; j < obj->int_array_16__b__primitive->length; j += 16)
		{
			NETLizard_3D_Primitive *p = ((NETLizard_3D_Primitive *)(mesh->item_mesh.primitive->array)) + k;
			p->index[0] = i_b[j] / 6;
			p->index[1] = i_b[j + 1] / 6;
			p->index[2] = i_b[j + 2] / 6;
			p->texcoord[0] = i_b[j + 3];
			p->texcoord[1] = i_b[j + 4];
			p->texcoord[2] = i_b[j + 5];
			p->texcoord[3] = i_b[j + 6];
			p->texcoord[4] = i_b[j + 7];
			p->texcoord[5] = i_b[j + 8];
			p->tex_index = i_b[j + 9];
			p->plane.position[0] = i_a[p->index[0] * 3] >> 16;
			p->plane.position[1] = i_a[p->index[0] * 3 + 1] >> 16;
			p->plane.position[2] = i_a[p->index[0] * 3 + 2] >> 16;
			p->plane.normal[0] = i_b[j + 10];
			p->plane.normal[1] = i_b[j + 11];
			p->plane.normal[2] = i_b[j + 12];
			k++;
		}
	}

	model->bsp_data = NULL;
	if(lv->class_a_array__t__bsp)
	{
		class__a__bsp *bsp = (class__a__bsp *)(lv->class_a_array__t__bsp->array);
		model->bsp_data = new_array(nl_user, lv->class_a_array__t__bsp->length, NULL, sizeof(NETLizard_BSP_Tree_Node));
		NETLizard_BSP_Tree_Node *bsp_data = (NETLizard_BSP_Tree_Node *)(model->bsp_data->array);
		int j;
		for(j = 0; j < lv->class_a_array__t__bsp->length; j++)
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

	model->start_angle[0] = lv->int__fa__rotation;
	model->start_angle[1] = lv->int__fc__rotation;
	model->start_pos[0] = lv->int_array__fd__translation[0] >> 16;
	model->start_pos[1] = lv->int_array__fd__translation[1] >> 16;
	model->start_pos[2] = lv->int_array__fd__translation[2] >> 16;

	for(i = 0; i < f_v->length; i++)
	{
		class__f__scene *obj = ((class__f__scene *)(f_v->array)) + i;
		delete_array(obj->short_array_3__a__vertex);
		delete_array(obj->int_array_7__b__primitive);
		delete_array(obj->int_array_2__l__plane);
		free(obj->short_array_3__a__vertex);
		free(obj->int_array_7__b__primitive);
		free(obj->int_array_2__l__plane);
	}
	delete_array(f_v);
	free(f_v);
	for(i = 0; i < i_q->length; i++)
	{
		class__i__item *obj = ((class__i__item *)(i_q->array)) + i;
		delete_array(obj->int_array_6__a__vertex);
		delete_array(obj->int_array_16__b__primitive);
		free(obj->int_array_6__a__vertex);
		free(obj->int_array_16__b__primitive);
	}
	delete_array(i_q);
	free(i_q);
	delete_array(lv->int_array__o__normal);
	free(lv->int_array__o__normal);
	delete_array(lv->int_array__gg__texcoord);
	free(lv->int_array__gg__texcoord);
	delete_array(lv->class_a_array__t__bsp);
	free(lv->class_a_array__t__bsp);
	free(lv);
	return model;
}

NETLizard_3D_Model * nlReadCT3DEp3ItemModelFile(const char* name, int index)
{
	if(!name)
		return NULL;
	array *arr = nlReadFile(name);
	if(!arr)
		return NULL;
	NETLizard_3D_Model *model = NEW(NETLizard_3D_Model);
	ZERO(model, NETLizard_3D_Model);

	class__i__item obj;
	class_t__function_av_void__item(&obj, arr->array);
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
	if(obj.int_array_6__a__vertex && obj.int_array_16__b__primitive)
	{
		mesh->item_mesh.vertex = new_array(nl_int, obj.int_array_6__a__vertex->length / 2, NULL, 0);
		int j;
		int *im_v = (int *)(mesh->item_mesh.vertex->array);
		int *i_a = (int *)(obj.int_array_6__a__vertex->array);
		int k = 0;
		for(j = 0; j < obj.int_array_6__a__vertex->length; j += 6)
		{
			im_v[k] = i_a[j] >> 16;
			im_v[k + 1] = i_a[j + 1] >> 16;
			im_v[k + 2] = i_a[j + 2] >> 16;
			k += 3;
		}
		int *i_b = (int *)(obj.int_array_16__b__primitive->array);
		mesh->item_mesh.primitive = new_array(nl_user, obj.int_array_16__b__primitive->length / 16, NULL, sizeof(NETLizard_3D_Primitive));
		k = 0;
		for(j = 0; j < obj.int_array_16__b__primitive->length; j += 16)
		{
			NETLizard_3D_Primitive *p = ((NETLizard_3D_Primitive *)(mesh->item_mesh.primitive->array)) + k;
			p->index[0] = i_b[j] / 6;
			p->index[1] = i_b[j + 1] / 6;
			p->index[2] = i_b[j + 2] / 6;
			p->texcoord[0] = i_b[j + 3];
			p->texcoord[1] = i_b[j + 4];
			p->texcoord[2] = i_b[j + 5];
			p->texcoord[3] = i_b[j + 6];
			p->texcoord[4] = i_b[j + 7];
			p->texcoord[5] = i_b[j + 8];
			p->tex_index = i_b[j + 9];
			p->plane.position[0] = i_a[p->index[0] * 3] >> 16;
			p->plane.position[1] = i_a[p->index[0] * 3 + 1] >> 16;
			p->plane.position[2] = i_a[p->index[0] * 3 + 2] >> 16;
			p->plane.normal[0] = i_b[j + 10];
			p->plane.normal[1] = i_b[j + 11];
			p->plane.normal[2] = i_b[j + 12];
			k++;
		}
		mesh->item_mesh.ortho[0] = obj.int__f__aabb >> 16;
		mesh->item_mesh.ortho[1] = obj.int__g__aabb >> 16;
		mesh->item_mesh.ortho[2] = obj.int__h__aabb >> 16;
		mesh->item_mesh.ortho[3] = obj.int__i__aabb >> 16;
		mesh->item_mesh.ortho[4] = obj.int__j__aabb >> 16;
		mesh->item_mesh.ortho[5] = obj.int__k__aabb >> 16;
	}

	delete_array(obj.int_array_6__a__vertex);
	delete_array(obj.int_array_16__b__primitive);
	free(obj.int_array_6__a__vertex);
	free(obj.int_array_16__b__primitive);
	delete_array(arr);
	free(arr);
	model->data = NULL;
	model->item_data = item_meshes;
	model->has_sky = 0;
	model->game = CT_3D_Ep3_Item;
	return model;
}

void nlReadCT3DEp3MapItems(array *i_q)
{
	if(!i_q)
		return;
	int i;
	for(i = 0; i < i_q->length; /* 45 */i++)
	{
		class__i__item *q = ((class__i__item *)(i_q->array)) + i;
		int i11 = q->byte__t__obj;
		char subfix[strlen(CT3DEP3_OBJ_SUBFIX) + 1];
		memset(subfix, '\0', sizeof(char) * (strlen(subfix) + 1));
		sprintf(subfix, CT3DEP3_OBJ_SUBFIX, i11);
		char *name = NULL;
		if(game_resource_path[nl_contr_terrorism_3d_episode_3])
		{
			name = NEW_II(char, strlen(subfix) + strlen(game_resource_path[nl_contr_terrorism_3d_episode_3]) + 1 + 1);
			memset(name, '\0', sizeof(char) * ((strlen(subfix) + strlen(game_resource_path[nl_contr_terrorism_3d_episode_3]) + 1 + 1)));
			sprintf(name, "%s/%s", game_resource_path[nl_contr_terrorism_3d_episode_3], subfix);
		}
		else
			name = strdup(subfix);
		array *arr = nlReadFile(name);
		free(name);
		if(arr)
		{
			q->int_array_6__a__vertex = NULL;
			q->int_array_16__b__primitive = NULL;
			class_t__function_av_void__item(q, arr->array);
			delete_array(arr);
			free(arr);
		}
		else
		{
			q->int_array_6__a__vertex = NULL;
			q->int_array_16__b__primitive = NULL;
		}
	}
}

/******** static ********/

class__t__lvl * class_t__function_b_1int_2bool__scene(const byte arrayOfByte[], boolean online)
{
	if(!arrayOfByte)
		return NULL;

	int fd[3];
	int fa;
	int fc;
	int eU;
	array *int_o = NULL;
	array *int_gg = NULL;
	array *f_v = NULL;
	array *i_q = NULL;
	int dL;

	int i1 = -2;
	if (online)
	{
		i1 += 20;
	}
	i1 += 2;
	int i2 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	if (i2 != 0) {
		//eA = new short[i2];
	}
	int i5;
	for (i5 = 0; i5 < i2; i5++)
	{
		i1 += 2;
		//eA[i5] = ((short)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
	}
	i1 += 2;
	fd[0] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
	i1 += 2;
	fd[1] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
	i1 += 2;
	fd[2] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
	//eJ = (short)(fd[0] >> 16);
	//eK = (short)(fd[1] >> 16);
	//eL = (short)(fd[2] >> 16);
	i1 += 2;
	fa = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	i1 += 2;
	fc = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	if (fc > 361) {
		fc -= 65536;
	}
	if (fa > 361) {
		fa -= 65536;
	}
	if (fc < 0) {
		fc = -fc;
	} else {
		fc = 360 - fc;
	}
	if (fc == 360) {
		fc = 0;
	}
	if (fa < 0) {
		fa = 270 + fa;
	} else {
		fa = 270 - fa;
	}
	if (fa == 360) {
		fa = 0;
	}
	dprintfss("Get start position and axis");
	i1 += 2;
	eU = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	dprintfsi("Map scene count", eU);
	i1 += 2;
	int i6 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	dprintfsi("Map normal count", i6);
	int_o = new_array(nl_int, i6, NULL, 0);
	int *o = (int *)(int_o->array);
	int i7;
	for (i7 = 0; i7 < i6; i7 += 3)
	{
		i1 += 2;
		o[i7] = ((int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
		i1 += 2;
		o[(i7 + 1)] = ((int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
		i1 += 2;
		o[(i7 + 2)] = ((int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
	}
	dprintfss("Get map normal");
	i1 += 2;
	i6 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	dprintfsi("Texcoord count", i6);
	int_gg = new_array(nl_int, i6, NULL, 0);
	int *gg = (int *)(int_gg->array);
	int i8;
	for (i8 = 0; i8 < i6; i8 += 2)
	{
		i1 += 2;
		gg[i8] = ((int)(64 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 100L));
		i1 += 2;
		gg[(i8 + 1)] = ((int)(64 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 100L));
	}
	dprintfss("Get map texcoord");
	f_v = new_array(nl_user, eU, NULL, sizeof(class__f__scene));
	class__f__scene *v = (class__f__scene *)(f_v->array);
	//dT = new byte[eU];
	int i20;
	int i24;
	int i13;
	for (i13 = 0; i13 < eU; i13++)
	{
		dprintfsi("Get map scene data", i13);
		i1 += 2;
		v[i13].int__f__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		v[i13].int__g__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		v[i13].int__h__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		v[i13].int__i__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		v[i13].int__j__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		v[i13].int__k__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		dprintfss("Get scene AABB");
		i1 += 2;
		int i11 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
		dprintfsi("Scene vertex coord count", i11);
		i1 += 2;
		int i10 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
		dprintfsi("Scene primitive count", i10);
		v[i13].short_array_3__a__vertex = new_array(nl_short, i11 * 3, NULL, 0);
		short *a = (short *)(v[i13].short_array_3__a__vertex->array);
		v[i13].m = i11;
		v[i13].int_array_7__b__primitive = new_array(nl_int, i10 * 7, NULL, 0);
		int *b = (int *)(v[i13].int_array_7__b__primitive->array);
		v[i13].n = i10;
		int i14;
		for (i14 = 0; i14 < i11; i14++)
		{
			i1 += 2;
			a[(i14 * 3)] = ((short)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
			i1 += 2;
			a[(i14 * 3 + 1)] = ((short)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
			i1 += 2;
			a[(i14 * 3 + 2)] = ((short)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
		}
		dprintfss("Get scene vertex coord");
		int *arrayOfInt1 = b;
		int i16 = 0;
		int i17;
		for (i17 = 0; i17 < i10; i17++)
		{
			i16 = i17 * 7;
			i1 += 2;
			b[i16] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 3);
			i1 += 2;
			b[(i16 + 1)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 3);
			i1 += 2;
			b[(i16 + 2)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 3);
		}
		dprintfss("Get scene primitive vertex coord index");
		i1 += 2;
		int i18 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
		dprintfsi("Scene plane count", i18);
		v[i13].int_array_2__l__plane = new_array(nl_int, i18 * 2, NULL, 0);
		int *l = (int *)(v[i13].int_array_2__l__plane->array);
		int i19;
		for (i19 = 0; i19 < i18; i19++)
		{
			i1 += 2;
			l[(i19 * 2)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 3);
			i1 += 2;
			l[(i19 * 2 + 1)] = arrayOfInt1[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 7)];
		}
		dprintfss("Get scene plane normal index and point vertex coord index");
		v[i13].c = (v[i13].int__f__aabb + v[i13].int__i__aabb >> 1);
		v[i13].d = (v[i13].int__g__aabb + v[i13].int__j__aabb >> 1);
		for (i20 = 0; i20 < i10; i20++)
		{
			i16 = i20 * 7;
			i1 += 2;
			b[(i16 + 3)] = ((short)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2);
			i1 += 2;
			b[(i16 + 4)] = ((short)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2);
			i1 += 2;
			b[(i16 + 5)] = ((short)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2);
		}
		dprintfss("Get scene texcoord index");
		i1++;
		int i23;
		for (i23 = 0; i23 < i10; i23++)
		{
			i1++;
			// ??? TODO
			byte i21 = arrayOfByte[i1];
			if (i21 < 0) {
				i21 += 256;
			}
			b[(i23 * 7 + 6)] = i21;
			//cK[v[i13].b[(i23 * 7 + 6)]] = true;
		}
		for (i24 = 0; i24 < i10; i24++)
		{
			i1++;
			int i22 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
			if (i22 < 0) {
				i22 += 256;
			}
			int i21 = b[(i24 * 7 + 6)] & 0xFF;
			b[(i24 * 7 + 6)] = ((i22 << 8) + i21);
		}
		dprintfss("Get primitive texture index");
		i1--;
	}
	i1 += 2;
	int i12 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	dprintfsi("Map BSP tree node count", i12);
	array *class_a_array__t__bsp = new_array(nl_user, i12, NULL, sizeof(class__a__bsp));
	class__a__bsp *t = (class__a__bsp *)(class_a_array__t__bsp->array);
	int i15;
	for (i15 = 0; i15 < i12; i15++)
	{
		int i16;
		for (i16 = 0; i16 < 4; i16++)
		{
			i1 += 2;
			t[i15].int_array_4x3__b__plane[i16][0] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			t[i15].int_array_4x3__b__plane[i16][1] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			t[i15].int_array_4x3__b__plane[i16][2] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		}
		i1 += 2;
		i2 = (int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L);
		i1 += 2;
		int i3 = (int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L);
		i1 += 2;
		int i4 = (int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L);
		i1 += 2;
		t[i15].int__c__prev_scene = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) - 1);
		i1 += 2;
		t[i15].int__d__next_scene = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) - 1);
		t[i15].int_array_3__a__normal[0] = i2;
		t[i15].int_array_3__a__normal[1] = i3;
		t[i15].int_array_3__a__normal[2] = i4;
		if ((t[i15].int__c__prev_scene == 999) || (t[i15].int__d__next_scene == 999)) {
			//fC = true;
		}
		if (i2 != 0) {
			t[i15].byte__a__direction = 1;
		} else if (i3 != 0) {
			t[i15].byte__a__direction = 2;
		} else if (i4 != 0) {
			t[i15].byte__a__direction = 3;
		}
	}
	int i16;
	for (i16 = 0; i16 < i12; i16++)
	{
		if (t[i16].int__c__prev_scene < 999)
		{
			v[t[i16].int__c__prev_scene].int_array_7__o__bsp[v[t[i16].int__c__prev_scene].int__p__bsp] = i16;
			v[t[i16].int__c__prev_scene].int__p__bsp += 1;
		}
		if (t[i16].int__d__next_scene < 999)
		{
			v[t[i16].int__d__next_scene].int_array_7__o__bsp[v[t[i16].int__d__next_scene].int__p__bsp] = i16;
			v[t[i16].int__d__next_scene].int__p__bsp += 1;
		}
	}
#if 0
	int i18;
	for (i18 = 0; i18 < f_v->length; i18++)
	{
		int *arrayOfInt2 = null;
		arrayOfInt2 = v[i18].int_array_7__o__bsp;
		v[i18].int_array_7__o__bsp = null;
		i19 = v[i18].int__p__bsp;
		v[i18].int_array_7__o__bsp = NEW_II(int i19);
		for (i20 = 0; i20 < i19; i20++) {
			v[i18].int_array_7__o__bsp[i20] = arrayOfInt2[i20];
		}
	}
#endif
	dprintfss("Get map BSP tree node");
	i1 += 2;
	dL = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	dprintfsi("Map item count", dL);
	i_q = new_array(nl_user, dL + 1, NULL, sizeof(class__i__item));
	class__i__item *q = (class__i__item *)(i_q->array);
	int i21 = 0;
	int i22;
	for (i22 = 0; i22 < eU; i22++)
	{
		i1 += 2;
		i20 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
		dprintfsii("Scene item count", i21, i20);
		v[i22].int__q__begin = i21;
		v[i22].int__e__end = (i21 + i20);
		int i23;
		for (i23 = 0; i23 < i20; i23++)
		{
			q[i21].r = ((short)i22);
			i1 += 2;
			q[i21].int__m__translation = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			q[i21].int__n__translation = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			q[i21].int__o__translation = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			q[i21].int__p__rotation = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
			i1 += 2;
			q[i21].int__q__rotation = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
			if (q[i21].int__q__rotation > 360) {
				q[i21].int__q__rotation = (65536 - q[i21].int__q__rotation);
			}
			if (q[i21].int__p__rotation > 360) {
				q[i21].int__p__rotation = (65536 - q[i21].int__p__rotation);
			}
			if (q[i21].int__q__rotation < 0) {
				q[i21].int__q__rotation = (-q[i21].int__q__rotation);
			}
			if (q[i21].int__q__rotation == 360) {
				q[i21].int__q__rotation = 0;
			}
			if (q[i21].int__p__rotation < 0) {
				q[i21].int__p__rotation = (360 + q[i21].int__p__rotation);
			} else {
				q[i21].int__p__rotation = (360 - q[i21].int__p__rotation);
			}
			if (q[i21].int__p__rotation == 360) {
				q[i21].int__p__rotation = 0;
			}
			i1 += 2;
			q[i21].byte__t__obj = ((byte)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
			if (q[i21].byte__t__obj == 7) {
				q[i21].byte__t__obj = q[i21].byte__t__obj;
			}
			if (q[i21].byte__t__obj < 120)
			{
				if ((q[i21].byte__t__obj > 37) && (q[i21].byte__t__obj < 42)) {
					//dT[i22] = 1;
				}
				if (q[i21].byte__t__obj >= 90)
				{
					class__i__item *tmp2972_2971 = q + i21;
					tmp2972_2971->byte__t__obj = ((byte)(tmp2972_2971->byte__t__obj - 50));
					//dT[i22] = -1;
				}
			}
			//cJ[q[i21].t] = true;
			i1 += 2;
			q[i21].e = ((short)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
			if (q[i21].e < 0)
			{
				class__i__item *tmp3048_3047 = q + i21;
				tmp3048_3047->e = ((short)(tmp3048_3047->e + 256));
			}
			if (q[i21].e < 100) {
				q[i21].e = 100;
			}
			i1 += 2;
			i21++;
		}
	}

	i1 += 2;
#if UNPARSED
	gC = b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) + 1;
	az = new byte[gC];
	C = new v[gC];
	for (int i23 = 0; i23 < gC; i23++) {
		C[i23] = new v(null);
	}
	i21 = 1;
	C[0].n = fd[0];
	C[0].o = fd[1];
	C[0].p = fd[2];
#endif
	int i27;
	for (i27 = 0; i27 < eU; i27++)
	{
		i1 += 2;
		i24 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
		int i28;
		for (i28 = 0; i28 < i24; i28++)
		{
			i1 += 2;
			//C[i21].n = (b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			//C[i21].v = C[i21].n;
			i1 += 2;
			//C[i21].o = (b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			//C[i21].w = C[i21].o;
			i1 += 2;
			//C[i21].p = (b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			//C[i21].z = ((byte)b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
#if UNPARSED
			i25 = C[i21].z;
			if (i25 > 20)
			{
				i25 -= 20;
				C[i21].u = true;
				C[i21].B = false;
			}
			else if (i25 > 10)
			{
				i25 -= 10;
				C[i21].u = true;
			}
			C[i21].z = ((byte)i25);
			if (C[i21].z == 0) {
				C[i21].z = C[i21].z;
			}
			if (i25 != 7) {
				cL[i25] = true;
			}
#endif
			i1 += 2;
#if UNPARSED
			int i26 = b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
			if (i26 > 360) {
				i26 -= 65536;
			}
			if (i26 < 0) {
				i26 = -i26;
			} else {
				i26 = 360 - i26;
			}
			if (i26 == 360) {
				i26 = 0;
			}
			C[i21].s[0] = (-fA[i26]);
			C[i21].s[1] = (-aZ[i26]);
			C[i21].A[0] = (-fA[i26]);
			C[i21].A[1] = (-aZ[i26]);
			C[i21].r = ((short)i27);
			i21++;
#endif
		}
	}
	i1 += 2;
	int i25 = (byte)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	//cy = i25;
	//cz = new short[i25 * 3];
	int i28;
	for (i28 = 0; i28 < i25; i28++)
	{
		i1 += 2;
		//cz[(i28 * 3)] = ((short)b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
		i1 += 2;
		//cz[(i28 * 3 + 1)] = ((short)b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
		i1 += 2;
		//cz[(i28 * 3 + 2)] = ((short)b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
	}
	i1 += 2;
	i25 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	//em = false;
	if (i25 == 1)
	{
		//em = true;
		//s = new int[7];
		i1 += 2;
		//s[0] = (b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		//s[1] = (b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		//s[2] = (b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		//s[3] = (b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		//s[4] = (b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		//s[5] = (b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		//s[6] = (b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
	}
	//fE = null;
	//eN = null;
	i1 += 2;
	int i29 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
#if UNPARSED
	if (i29 != 0) {
		eN = new short[i29];
	} else {
		eN = null;
	}
#endif
	i1 += 2;
	int i30;
	for (i30 = 0; i30 < i29; i30++)
	{
		//eN[i30] = ((short)b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
		i1 += 2;
	}
	int i31 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
#if UNPARSED
	if (i31 != 0) {
		fE = new byte[v.length];
	} else {
		fE = null;
	}
#endif
	int i32;
	for (i32 = 0; i32 < i31; i32++)
	{
		i1 += 2;
		//int i33 = b(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
		//fE[i33] = 1;
	}
	i1 += 2;
	char *str = NULL;
	int i34;
	for (i34 = 0; i34 < 30; i34++)
	{
		if (arrayOfByte[i1] == 0) {
			break;
		}
		int i35 = arrayOfByte[i1] & 0xFF;
		if ((i35 >= 192) && (i35 <= 255)) {
			i35 += 848;
		}
		if(!str)
		{
			str = NEW_II(char, 1 + 1);
			memset(str, '\0', sizeof(char) * (1 + 1));
			str[0] = (char)i35;
		}
		else
		{
			char *p = str;
			size_t len = strlen(p);
			str = NEW_II(char, len + 1 + 1);
			memset(str, '\0', sizeof(char) * (len + 1 + 1));
			strcpy(str, p);
			free(p);
			str[len + 1] = (char)i35;
		}
		i1++;
	}
	dprintfs(str);
	UNUSED(str)
#if UNPARSED
	cv = str;
	for (int i35 = gC - 1; i35 >= 0; i35--)
	{
		h(C[i35]);
		if (i35 == 0)
		{
			eR = C[i35].r;
			b(C[i35].A);
		}
	}
	C[0].r = ((short)eR);
	byte[] arrayOfByte = null;
	if (es) {
		i((du - 1) % 5);
	}
#endif
	nlReadCT3DEp3MapItems(i_q);
	class__t__lvl *lvl = NEW(class__t__lvl);
	ZERO(lvl, class__t__lvl);
	lvl->int_array__fd__translation[0] = fd[0];
	lvl->int_array__fd__translation[1] = fd[1];
	lvl->int_array__fd__translation[2] = fd[2];
	lvl->int__fa__rotation = fa;;
	lvl->int__fc__rotation = fc;
	lvl->int_array__o__normal = int_o;
	lvl->int_array__gg__texcoord = int_gg;
	lvl->class_f_array__v__scene = f_v;
	lvl->class_i_array__q__item = i_q;
	lvl->class_a_array__t__bsp = class_a_array__t__bsp;
	return lvl;
}

void class_t__function_av_void__item(class__i__item *p, const byte arrayOfByte1[])
{
	// 45
	if(!p || !arrayOfByte1)
		return;
	//if ((cJ[i11] != 0) || (i11 == 44))
	int i1 = -2;
	i1 += 2;
	p->int__f__aabb = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16); // e
	i1 += 2;
	p->int__g__aabb = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16); // f
	i1 += 2;
	p->int__h__aabb = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16); // g
	i1 += 2;
	p->int__i__aabb = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16); // h
	i1 += 2;
	p->int__j__aabb = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16); // i
	i1 += 2;
	p->int__k__aabb = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16); // j
	int i2 = p->int__f__aabb >> 16;
	int i3 = p->int__g__aabb >> 16;
	int i4 = p->int__h__aabb >> 16;
	int i5 = i2 * i2 + i3 * i3 + i4 * i4;
	int i6 = 65536;
	int i7 = 0;
	while (i6 >>= 1 > 0) {
		if ((i7 + i6) * (i7 + i6) <= i5) {
			i7 += i6;
		}
	}
	p->d = ((i7 << 3) * 240 << 1);
	p->c = ((i7 << 1) * 260);
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	int i9 = nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]);
	i1 += 2;
	int i8 = nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]);
	i1 += 2;
	int i10 = nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]);
	//p[i11].k = i9;
	p->int_array_6__a__vertex = new_array(nl_int, i9 * 6, NULL, 0);
	int *a = (int *)(p->int_array_6__a__vertex->array);
	p->int_array_16__b__primitive = new_array(nl_int, i8 * 16, NULL, 0);
	int *b = (int *)(p->int_array_16__b__primitive->array);
	i10 *= 2;
	int *arrayOfInt = NEW_II(int, i10);
	int i12;
	for (i12 = 0; i12 < i9; i12++)
	{
		i1 += 2;
		a[(i12 * 6)] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
		i1 += 2;
		a[(i12 * 6 + 1)] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
		i1 += 2;
		a[(i12 * 6 + 2)] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
	}
	int i13;
	for (i13 = 0; i13 < i8; i13++)
	{
		i1 += 2;
		b[(i13 * 16)] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 6);
		i1 += 2;
		b[(i13 * 16 + 1)] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 6);
		i1 += 2;
		b[(i13 * 16 + 2)] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 6);
	}
	int i14;
	for (i14 = 0; i14 < i8; i14++)
	{
		i1 += 2;
		b[(i14 * 16 + 10)] = ((int)(65536 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L));
		i1 += 2;
		b[(i14 * 16 + 11)] = ((int)(65536 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L));
		i1 += 2;
		b[(i14 * 16 + 12)] = ((int)(65536 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L));
	}
	int i15;
	for (i15 = 0; i15 < i10; i15 += 2)
	{
		i1 += 2;
		arrayOfInt[i15] = ((int)(64 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 100L));
		i1 += 2;
		arrayOfInt[(i15 + 1)] = ((int)(64 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 100L));
	}
	int i16;
	for (i16 = 0; i16 < i8; i16++)
	{
		i1 += 2;
		b[(i16 * 16 + 3)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2)]);
		b[(i16 * 16 + 4)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2 + 1)]);
		i1 += 2;
		b[(i16 * 16 + 5)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2)]);
		b[(i16 * 16 + 6)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2 + 1)]);
		i1 += 2;
		b[(i16 * 16 + 7)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2)]);
		b[(i16 * 16 + 8)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2 + 1)]);
	}
	i1 += 2;
	int i17;
	for (i17 = 0; i17 < i8; i17++)
	{
		b[(i17 * 16 + 9)] = arrayOfByte1[i1];
		//cK[p[i11].b[(i17 * 16 + 9)]] = true;
		i1++;
	}
	free(arrayOfInt);
	/*
		 arrayOfByte1 = null;

		 byte[] arrayOfByte2 = s.k.b(s.a(H), -1);
		 for (int i16 = 0; i16 < q.length; i16++) {
		 if (i16 == q.length - 1)
		 {
		 q[i16].a = p[44].a;
		 q[i16].b = p[44].b;
		 q[i16].f = p[44].e;
		 q[i16].i = p[44].h;
		 q[i16].g = p[44].f;
		 q[i16].j = p[44].i;
		 q[i16].h = p[44].g;
		 q[i16].k = p[44].j;
		 q[i16].t = 44;
		 }
		 else
		 {
		 i locali = q[i16];
		 if ((!dp ? (locali.t > 0) && (locali.t < 8) : locali.t == 21) || (locali.t >= 120)) {
		 continue;
		 }
		 i14 = locali.t << 2;
		 if (arrayOfByte2[i14] == 1) {
		 locali.d = true;
		 }
		 if (arrayOfByte2[(i14 + 1)] == 1) {
		 locali.s = true;
		 }
		 if (arrayOfByte2[(i14 + 2)] == 1) {
		 locali.c = true;
		 }
		 if (arrayOfByte2[(i14 + 3)] == 1) {
		 locali.l = true;
		 }
		 k localk = p[locali.t];
		 locali.a = localk.a;
		 locali.b = localk.b;
		 locali.f = localk.e;
		 locali.i = localk.h;
		 locali.g = localk.f;
		 locali.j = localk.i;
		 locali.h = localk.g;
		 locali.k = localk.j;
		 }
		 }
		 arrayOfByte2 = null;
		 */
}

void ct3dep3_a(array *data, int paramInt1, int paramInt2)
{
	byte *paramArrayOfByte = (byte *)(data->array);
	int i1 = data->length;
	int i3 = (byte)paramInt1;
	int i2;
	for (i2 = paramInt2; i2 < i1; i2++)
	{
		paramArrayOfByte[i2] = ((byte)(paramArrayOfByte[i2] ^ i3));
		printf("%c", paramArrayOfByte[i2]);
		i3 = (byte)(i3 + 1);
	}
}

void ct3dep3_god_mode_version__class_b__function_a_1string_2int__decode_recordstore_record(array *arr)
{
	if(!arr)
		return;
	if(!arr->array)
		return;
	byte *localObject = (byte *)(arr->array);
	int paramInt = 0;
	const char paramString[] = "SonyEricssonW900i175"; // 175 == ((byte)-81) & 0xff
	int i1 = strlen(paramString);
	int i2;
	for (i2 = 0; i2 < arr->length; i2++)
	{
		localObject[i2] = ((byte)(localObject[i2] ^ (byte)paramString[paramInt]));
		paramInt++;
		if (paramInt >= i1) {
			paramInt = 0;
		}
	}
}
