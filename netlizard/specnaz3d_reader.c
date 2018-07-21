#include "specnaz3d_reader.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// army ranger 3d guagua cracked glo version

#define dprintfsi(s, d) nlprintf("Specnaz 3D : "#s"->%d\n", d)
#define dprintfsii(s, d, d2) nlprintf("Specnaz 3D : ""%d - "#s"->%d\n", d, d2)
#define dprintfss(s) nlprintf("Specnaz 3D : "#s"\n")

typedef struct _class__g__scene
{
  array *int_array_6__a__vertex; // int 3顶点坐标 3UNUSED DYNAMIC
  array *int_array_7__b__primitive; // int 3索引 3纹理坐标索引(i, i + 1) 1纹理索引
  int c;
  int d;
  int int__e__end; // = 0; 最后一个物品索引
  int int__f__aabb; // AABB盒子
  int int__g__aabb; // AABB盒子
  int int__h__aabb; // AABB盒子
  int int__i__aabb; // AABB盒子
  int int__j__aabb; // AABB盒子
  int int__k__aabb; // AABB盒子
  array *int_array_6__l__plane; // int 碰撞面 1法线索引(i, i + 1, i + 2) 1顶点索引(i, i + 1, i + 2)
  int m;
  int n;
  int int_array_5__o__bsp[5];
  int int__p__bsp; // = 0;
  int int__q__begin; // = 0; // 第一个物品索引
} class__g__scene;

typedef struct _class__c__bsp
{
  byte byte__a__direction;
	int int_array_3__a__normal[3];
  int int_array_4x3__b__plane[4][3]; // l[] b = new l[4];
  int int__c__prev_scene;
  int int__d__next_scene;
  boolean e; // = false;
} class__c__bsp;

typedef struct _class__j__item
{
  array *int_array_6__a__vertex; // int 3顶点坐标 3UNUSED DYNAMIC
  array *int_array_16__b__primitive; // int 3索引 6纹理坐标索引 1纹理索引 3法线 3UNKNOW
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
  int int__m__translation; // 坐标
  int int__n__translation; // 坐标
  int int__o__translation; // 坐标
  int int__p__rotation; // = 0; 旋转
  int int__q__rotation; // = 0; 旋转
  short r;
  boolean s;
  byte byte__t__obj;
  boolean u; // = true;  
} class__j__item;

typedef struct _class__k__lvl
{
  array *class_g_array__q__scene; // 场景
	array *int_array__j__normal; // 法线
	array *int_array__dm__texcoord; // 纹理坐标
  array *class_j_array__l__item; // 物品
  int int_array__cF__translation[3]; // 主角初始坐标
  int int__cC__rotation; // 主角初始视角
  int int__cE__rotation; // 主角初始视角;
	array *class_c_array__o__bsp;
} class__k__lvl;

static class__k__lvl * class_k__function_h_1int__scene(const byte arrayOfByte[]); // 场景解析
static void class_k__function_P_void__item(class__j__item *l, const byte arrayOfByte[]); // 场景物品解析
static void nlReadSpecnaz3DMapItems(array *j_l);

NETLizard_3D_Model * nlReadSpecnaz3DModelFile(const char* name, int paramInt)
{
	if(!name)
		return NULL;
	array *arr = nlReadFile(name);
	if(!arr)
		return NULL;
	byte *arrayOfByte = (byte *)(arr->array);
	class__k__lvl *lv = class_k__function_h_1int__scene(arrayOfByte);
	if(!lv)
		return NULL;
	int dr = 0;
	if ((paramInt == 1) || paramInt == 2 || paramInt == 6 || paramInt == 8 || paramInt == 9 || paramInt == 10) {
		dr = 1;
	}
	NETLizard_3D_Model *model = NEW(NETLizard_3D_Model);
	ZERO(model, NETLizard_3D_Model);
	array *g_q = lv->class_g_array__q__scene;
	int *dm = (int *)(lv->int_array__dm__texcoord->array);
	int *j_array = (int *)(lv->int_array__j__normal->array);
	model->data = new_array(nl_user, g_q->length, NULL, sizeof(NETLizard_3D_Mesh));
	model->has_sky = dr;
	model->game = Army_Ranger_3D_Map;

	int i;
	for(i = 0; i < g_q->length; i++)
	{
		NETLizard_3D_Mesh *mesh = ((NETLizard_3D_Mesh *)(model->data->array)) + i;
		class__g__scene *obj = ((class__g__scene *)(g_q->array)) + i;
		mesh->vertex = new_array(nl_int, obj->int_array_6__a__vertex->length / 2, NULL, 0);
		int j;
		int *m_v = (int *)(mesh->vertex->array);
		int *s_a = (int *)(obj->int_array_6__a__vertex->array);
		int k = 0;
		for(j = 0; j < obj->int_array_6__a__vertex->length; j += 6)
		{
			m_v[k] = s_a[j] >> 16;
			m_v[k + 1] = s_a[j + 1] >> 16;
			m_v[k + 2] = s_a[j + 2] >> 16;
			k += 3;
		}
		
		mesh->primitive = NULL;
		if(obj->int_array_7__b__primitive)
		{
			mesh->primitive = new_array(nl_user, obj->int_array_7__b__primitive->length / 7, NULL, sizeof(NETLizard_3D_Primitive));
			int *s_b = (int *)(obj->int_array_7__b__primitive->array);
			int k = 0;
			for(j = 0; j < obj->int_array_7__b__primitive->length; j += 7)
			{
				NETLizard_3D_Primitive *p = ((NETLizard_3D_Primitive *)(mesh->primitive->array)) + k;
				p->index[0] = s_b[j] / 6;
				p->index[1] = s_b[j + 1] / 6; 
				p->index[2] = s_b[j + 2] / 6;
				p->texcoord[0] = dm[(s_b[j + 3])];
				p->texcoord[1] = dm[(s_b[j + 3]) + 1];
				p->texcoord[2] = dm[(s_b[j + 4])];
				p->texcoord[3] = dm[(s_b[j + 4]) + 1];
				p->texcoord[4] = dm[(s_b[j + 5])];
				p->texcoord[5] = dm[(s_b[j + 5]) + 1];
				p->tex_index = (s_b[j + 6]) & 0xff;
				k++;
			}
		}
		mesh->plane = NULL;
		if(obj->int_array_6__l__plane)
		{
			mesh->plane = new_array(nl_user, obj->int_array_6__l__plane->length / 2, NULL, sizeof(NETLizard_3D_Plane));
			int *s_p = (int *)(obj->int_array_6__l__plane->array);
			int k = 0;
			for(j = 0; j < obj->int_array_6__l__plane->length; j += 2)
			{
				int normal_index = s_p[j];
				int position_index = s_p[j + 1];
				NETLizard_3D_Plane *plane = ((NETLizard_3D_Plane *)(mesh->plane->array)) + k;
				plane->normal[0] = j_array[normal_index];
				plane->normal[1] = j_array[normal_index + 1];
				plane->normal[2] = j_array[normal_index + 2];
				plane->position[0] = s_a[position_index] >> 16;
				plane->position[1] = s_a[position_index + 1] >> 16;
				plane->position[2] = s_a[position_index + 2] >> 16;
				k++;
			}
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
				bsp_index[j] = obj->int_array_5__o__bsp[j];
			}
		}
	}

	array *j_l = lv->class_j_array__l__item;
	model->item_data = NULL;
	if(j_l)
	{
		model->item_data = new_array(nl_user, j_l->length, NULL, sizeof(NETLizard_3D_Item_Mesh));
		for(i = 0; i < j_l->length; i++)
		{
			NETLizard_3D_Item_Mesh *mesh = ((NETLizard_3D_Item_Mesh *)(model->item_data->array)) + i;
			class__j__item *obj = ((class__j__item *)(j_l->array)) + i;
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
			mesh->item_mesh.ortho[0] = obj->int__f__aabb >> 16;
			mesh->item_mesh.ortho[1] = obj->int__g__aabb >> 16;
			mesh->item_mesh.ortho[2] = obj->int__h__aabb >> 16;
			mesh->item_mesh.ortho[3] = obj->int__i__aabb >> 16;
			mesh->item_mesh.ortho[4] = obj->int__j__aabb >> 16;
			mesh->item_mesh.ortho[5] = obj->int__k__aabb >> 16;
		}
	}

	model->bsp_data = NULL;
	if(lv->class_c_array__o__bsp)
	{
		class__c__bsp *bsp = (class__c__bsp *)(lv->class_c_array__o__bsp->array);
		model->bsp_data = new_array(nl_user, lv->class_c_array__o__bsp->length, NULL, sizeof(NETLizard_BSP_Tree_Node));
		NETLizard_BSP_Tree_Node *bsp_data = (NETLizard_BSP_Tree_Node *)(model->bsp_data->array);
		int j;
		for(j = 0; j < lv->class_c_array__o__bsp->length; j++)
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

	model->start_angle[0] = lv->int__cC__rotation;
	model->start_angle[1] = lv->int__cE__rotation;
	model->start_pos[0] = lv->int_array__cF__translation[0] >> 16;
	model->start_pos[1] = lv->int_array__cF__translation[1] >> 16;
	model->start_pos[2] = lv->int_array__cF__translation[2] >> 16;

	for(i = 0; i < g_q->length; i++)
	{
		class__g__scene *obj = ((class__g__scene *)(g_q->array)) + i;
		delete_array(obj->int_array_6__a__vertex);
		delete_array(obj->int_array_7__b__primitive);
		delete_array(obj->int_array_6__l__plane);
		free(obj->int_array_6__a__vertex);
		free(obj->int_array_7__b__primitive);
		free(obj->int_array_6__l__plane);
	}
	delete_array(g_q);
	free(g_q);
	if(j_l)
	{
		for(i = 0; i < j_l->length; i++)
		{
			class__j__item *obj = ((class__j__item *)(j_l->array)) + i;
			delete_array(obj->int_array_6__a__vertex);
			delete_array(obj->int_array_16__b__primitive);
			free(obj->int_array_6__a__vertex);
			free(obj->int_array_16__b__primitive);
		}
		delete_array(j_l);
		free(j_l);
	}
	delete_array(lv->int_array__j__normal);
	free(lv->int_array__j__normal);
	delete_array(lv->int_array__dm__texcoord);
	free(lv->int_array__dm__texcoord);
	delete_array(lv->class_c_array__o__bsp);
	free(lv->class_c_array__o__bsp);
	free(lv);
	return model;
}

NETLizard_3D_Model * nlReadSpecnaz3DItemModelFile(const char* name, int index)
{
	if(!name)
		return NULL;
	array *arr = nlReadFile(name);
	if(!arr)
		return NULL;
	NETLizard_3D_Model *model = NEW(NETLizard_3D_Model);
	ZERO(model, NETLizard_3D_Model);

	class__j__item obj;
	class_k__function_P_void__item(&obj, arr->array);
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
	model->game = Army_Ranger_3D_Item;
	return model;
}

void nlReadSpecnaz3DMapItems(array *j_l)
{
	if(!j_l)
		return;
	int i;
	for(i = 0; i < j_l->length; i++)
	{
		class__j__item *l = ((class__j__item *)(j_l->array)) + i;
		int i11 = l->byte__t__obj;
		char subfix[strlen(SPECNAZ3D_OBJ_SUBFIX) + 1];
		memset(subfix, '\0', sizeof(char) * (strlen(subfix) + 1));
		sprintf(subfix, SPECNAZ3D_OBJ_SUBFIX, i11);
		char *name = NULL;
		if(game_resource_path[nl_army_ranger_3d])
		{
			name = NEW_II(char, strlen(subfix) + strlen(game_resource_path[nl_army_ranger_3d]) + 1 + 1);
			memset(name, '\0', sizeof(char) * ((strlen(subfix) + strlen(game_resource_path[nl_army_ranger_3d]) + 1 + 1)));
			sprintf(name, "%s/%s", game_resource_path[nl_army_ranger_3d], subfix);
		}
		else
			name = strdup(subfix);
		array *arr = nlReadFile(name);
		free(name);
		if(arr)
		{
			class_k__function_P_void__item(l, arr->array);
			delete_array(arr);
			free(arr);
		}
		else
		{
			l->int_array_6__a__vertex = NULL;
			l->int_array_16__b__primitive = NULL;
		}
	}
}
/* ****** static ****** */

class__k__lvl * class_k__function_h_1int__scene(const byte arrayOfByte[])
{
	if(!arrayOfByte)
		return NULL;
	//byte *cn = NULL;
	int cF[3];
	int cC;
	int cE;
	int cx;
	array *int_j = NULL;
	array *int_dm = NULL;
	array *g_q = NULL;
	//byte *bX = NULL;
	int bU;
	array *j_l = NULL;

	int i1 = -2;
	i1 += 2;
	int i2;
	if ((i2 = nlMargeDigit(arrayOfByte[0], arrayOfByte[1])) != 0) {
		//cn = NEW_II(byte, i2);
	}
	int i5;
	for (i5 = 0; i5 < i2; i5++)
	{
		i1 += 2;
		//cn[i5] = ((byte)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
	}
	i1 += 2;
	cF[0] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
	i1 += 2;
	cF[1] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
	i1 += 2;
	cF[2] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
	i1 += 2;
	cC = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	i1 += 2;
	cE = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	if (cE > 361) {
		cE -= 65536;
	}
	if (cC > 361) {
		cC -= 65536;
	}
	if (cE < 0) {
		cE = -cE;
	} else {
		cE = 360 - cE;
	}
	if (cE == 360) {
		cE = 0;
	}
	if (cC < 0) {
		cC = 270 + cC;
	} else {
		cC = 270 - cC;
	}
	if (cC == 360) {
		cC = 0;
	}
	dprintfss("Get start position and axis");
	i1 += 2;
	cx = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	dprintfsi("Map scene count", cx);
	i1 += 2;
	int i6 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	int_j = new_array(nl_int, i6, NULL, 0);
	dprintfsi("Map normal count", i6);
	int *j_array = (int *)(int_j->array);
	int i7;
	for (i7 = 0; i7 < i6; i7 += 3)
	{
		i1 += 2;
		j_array[i7] = ((int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
		i1 += 2;
		j_array[(i7 + 1)] = ((int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
		i1 += 2;
		j_array[(i7 + 2)] = ((int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
	}
	dprintfss("Get map normal");
	i1 += 2;
	i6 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	dprintfsi("Texcoord count", i6);
	int_dm = new_array(nl_int, i6, NULL, 0);
	int *dm = (int *)(int_dm->array);
	int i8;
	for (i8 = 0; i8 < i6; i8 += 2)
	{
		i1 += 2;
		dm[i8] = ((int)(64 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 100L));
		i1 += 2;
		dm[(i8 + 1)] = ((int)(64 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 100L));
	}
	dprintfss("Get map texcoord");
	g_q = new_array(nl_user, cx, NULL, sizeof(class__g__scene));
	class__g__scene *q = (class__g__scene *)(g_q->array);
	//bX = NEW_II(byte, cx);
	int i18;
	int i24;
	int i22;
	int i13;
	for (i13 = 0; i13 < cx; i13++)
	{
		dprintfsi("Get map scene data", i13);
		i1 += 2;
		q[i13].int__f__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		q[i13].int__g__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		q[i13].int__h__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		q[i13].int__i__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		q[i13].int__j__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		q[i13].int__k__aabb = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		dprintfss("Get scene AABB");
		i1 += 2;
		int i11 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
		dprintfsi("Scene vertex coord count", i11);
		i1 += 2;
		int i10 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
		dprintfsi("Scene primitive count", i10);
		q[i13].int_array_6__a__vertex = new_array(nl_int, i11 * 6, NULL, 0);
		int *a = (int *)(q[i13].int_array_6__a__vertex->array);
		q[i13].m = i11;
		q[i13].int_array_7__b__primitive = new_array(nl_int, i10 * 7, NULL, 0);
		int *b = NULL;
		if(q[i13].int_array_7__b__primitive)
			b = (int *)(q[i13].int_array_7__b__primitive->array);
		q[i13].n = i10;
		int i14;
		for (i14 = 0; i14 < i11; i14++)
		{
			i1 += 2;
			a[(i14 * 6)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			a[(i14 * 6 + 1)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			a[(i14 * 6 + 2)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		}
		dprintfss("Get scene vertex coord");
		int *arrayOfInt = b;
		int i17;
		int i16;
		for (i17 = 0; i17 < i10; i17++)
		{
			i16 = i17 * 7;
			i1 += 2;
			b[i16] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
			i1 += 2;
			b[(i16 + 1)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
			i1 += 2;
			b[(i16 + 2)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
		}
		dprintfss("Get scene primitive vertex coord index");
		i1 += 2;
		i18 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
		q[i13].int_array_6__l__plane = new_array(nl_int, i18 * 2, NULL, 0);
		dprintfsi("Scene plane count", i8);
		int *l = NULL;
		if(q[i13].int_array_6__l__plane)
			l = (int *)(q[i13].int_array_6__l__plane->array);
		int i19;
		for (i19 = 0; i19 < i18; i19++)
		{
			i1 += 2;
			l[(i19 * 2)] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 3);
			i1 += 2;
			l[(i19 * 2 + 1)] = arrayOfInt[(nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 7)];
		}
		dprintfss("Get scene plane normal index and point vertex coord index");
		q[i13].c = (q[i13].int__f__aabb + q[i13].int__i__aabb >> 1);
		q[i13].d = (q[i13].int__g__aabb + q[i13].int__j__aabb >> 1);
		int i20;
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
			int i21;
			i1++;
			if ((i21 = arrayOfByte[i1]) < 0) {
				i21 += 256;
			}
			b[(i23 * 7 + 6)] = i21;
			//bv[q[i13].b[(i23 * 7 + 6)]] = true;
		}
		for (i24 = 0; i24 < i10; i24++)
		{
			i1++;
			if ((i22 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)])) < 0) {
				i22 += 256;
			}
			int i21 = b[(i24 * 7 + 6)] & 0xFF;
			b[(i24 * 7 + 6)] = ((i22 << 8) + i21);
		}
		dprintfss("Get primitive texture index");
		i1--;
	}
	i1 += 2;
	int i12;
	i12 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	dprintfsi("Map BSP tree node count", i12);
	array *class_c_array__o__bsp = new_array(nl_user, i12, NULL, sizeof(class__c__bsp));
	class__c__bsp *o = (class__c__bsp *)(class_c_array__o__bsp->array);
	int i15;
	for (i15 = 0; i15 < i12; i15++)
	{
		int i16;
		for (i16 = 0; i16 < 4; i16++)
		{
			i1 += 2;
			o[i15].int_array_4x3__b__plane[i16][0] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			o[i15].int_array_4x3__b__plane[i16][1] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			o[i15].int_array_4x3__b__plane[i16][2] = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		}
		i1 += 2;
		i2 = (int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L);
		i1 += 2;
		int i3 = (int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L);
		i1 += 2;
		int i4 = (int)(65536 * nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L);
		i1 += 2;
		o[i15].int__c__prev_scene = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) - 1);
		i1 += 2;
		o[i15].int__d__next_scene = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) - 1);
		o[i15].int_array_3__a__normal[0] = i2;
		o[i15].int_array_3__a__normal[1] = i3;
		o[i15].int_array_3__a__normal[2] = i4;
		if ((o[i15].int__c__prev_scene == 999) || (o[i15].int__d__next_scene == 999)) {
			//this.cW = true;
		}
		if (i2 != 0) {
			o[i15].byte__a__direction = 1;
		} else if (i3 != 0) {
			o[i15].byte__a__direction = 2;
		} else if (i4 != 0) {
			o[i15].byte__a__direction = 3;
		}
	}
	int i16;
	for (i16 = 0; i16 < i12; i16++)
	{
		if (o[i16].int__c__prev_scene < 999)
		{
			q[o[i16].int__c__prev_scene].int_array_5__o__bsp[q[o[i16].int__c__prev_scene].int__p__bsp] = i16;
			q[o[i16].int__c__prev_scene].int__p__bsp += 1;
		}
		if (o[i16].int__d__next_scene < 999)
		{
			q[o[i16].int__d__next_scene].int_array_5__o__bsp[q[o[i16].int__d__next_scene].int__p__bsp] = i16;
			q[o[i16].int__d__next_scene].int__p__bsp += 1;
		}
	}
	dprintfss("Get map BSP tree node");
	i1 += 2;
	bU = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	dprintfsi("Map item count", bU);
	j_l = new_array(nl_user, bU, NULL, sizeof(class__j__item));
	if(j_l)
	{
		class__j__item *l = (class__j__item *)(j_l->array);
		int i19 = 0;
		int i20;
		for (i20 = 0; i20 < cx; i20++)
		{
			i1 += 2;
			i18 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
			dprintfsii("Scene item count", i20, i18);
			q[i20].int__q__begin = i19;
			q[i20].int__e__end = (i19 + i18);
			int i21;
			for (i21 = 0; i21 < i18; i21++)
			{
				l[i19].r = ((short)i20);
				i1 += 2;
				l[i19].int__m__translation = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
				i1 += 2;
				l[i19].int__n__translation = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
				i1 += 2;
				l[i19].int__o__translation = (nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
				i1 += 2;
				l[i19].int__p__rotation = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
				i1 += 2;
				l[i19].int__q__rotation = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
				if (l[i19].int__q__rotation > 360) {
					l[i19].int__q__rotation = (65536 - l[i19].int__q__rotation);
				}
				if (l[i19].int__p__rotation > 360) {
					l[i19].int__p__rotation = (65536 - l[i19].int__p__rotation);
				}
				if (l[i19].int__q__rotation < 0) {
					l[i19].int__q__rotation = (-l[i19].int__q__rotation);
				}
				if (l[i19].int__q__rotation == 360) {
					l[i19].int__q__rotation = 0;
				}
				if (l[i19].int__p__rotation < 0) {
					l[i19].int__p__rotation = (360 + l[i19].int__p__rotation);
				} else {
					l[i19].int__p__rotation = (360 - l[i19].int__p__rotation);
				}
				if (l[i19].int__p__rotation == 360) {
					l[i19].int__p__rotation = 0;
				}
				i1 += 2;
				l[i19].byte__t__obj = ((byte)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
				if (l[i19].byte__t__obj < 120)
				{
					/*
						 if ((l[i19].byte__t__obj > 39) && (l[i19].byte__t__obj < 44)) {
						 bX[i20] = 1;
						 }
						 */
					if (l[i19].byte__t__obj >= 90)
					{
						class__j__item *tmp2767_2766 = l + i19;
						tmp2767_2766->byte__t__obj = ((byte)(tmp2767_2766->byte__t__obj - 50));
						//bX[i20] = -1;
						l[i19].byte__t__obj -= 50;
					}
					//bu[l[i19].byte__t__obj] = true;
				}
				i1 += 2;
				l[i19].e = ((short)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
				if (l[i19].e < 0)
				{
					class__j__item *tmp2841_2840 = l + i19;
					tmp2841_2840->e = ((short)(tmp2841_2840->e + 256));
					l[i19].e += 256;
				}
				i1 += 2;
				i19++;
			}
		}
	}
	//printfi(j_l != NULL);

	i1 += 2;
#if UNPARSED
	dv = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) + 1;
	X = new byte[dv];
	s = new m[dv];
	for (int i21 = 0; i21 < dv; i21++) {
		s[i21] = new m(null);
	}
	i19 = 1;
	if ((bM == 5) && (f.a[3] != 0))
	{
		cF[1] = 0;
		cF[2] = 51511296;
		if (f.a[3] == 1)
		{
			cE = 90;
			cF[0] = 380108800;
		}
		else
		{
			cE = 270;
			cF[0] = -380108800;
		}
	}
	s[0].n = cF[0];
	s[0].o = cF[1];
	s[0].p = cF[2];
#endif
	int i25;
	for (i25 = 0; i25 < cx; i25++)
	{
		i1 += 2;
		i22 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
		int i26;
		for (i26 = 0; i26 < i22; i26++)
		{
			i1 += 2;
			//s[i19].n = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			//s[i19].v = s[i19].n;
			i1 += 2;
			//s[i19].o = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			//s[i19].w = s[i19].o;
			i1 += 2;
			//s[i19].p = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
			i1 += 2;
			//s[i19].y = ((byte)c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
#if UNPARSED
			if ((i23 = s[i19].y) > 20)
			{
				i23 -= 20;
				s[i19].u = true;
				s[i19].A = false;
			}
			else if (i23 > 10)
			{
				i23 -= 10;
				s[i19].u = true;
			}
			s[i19].y = ((byte)i23);
			if (i23 != 7) {
				bw[i23] = true;
			}
#endif
			i1 += 2;
#if UNPARSED
			if ((i24 = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)])) > 360) {
				i24 -= 65536;
			}
			if (i24 < 0) {
				i24 = -i24;
			} else {
				i24 = 360 - i24;
			}
			if (i24 == 360) {
				i24 = 0;
			}
			s[i19].s[0] = (-cU[i24]);
			s[i19].s[1] = (-aq[i24]);
			s[i19].z[0] = (-cU[i24]);
			s[i19].z[1] = (-aq[i24]);
			if ((i23 == 4) || (i23 == 5)) {
				aT = (byte)(aT + 1);
			} else {
				dl = (byte)(dl + 1);
			}
			s[i19].r = ((short)i25);
			i19++;
#endif
		}
	}
	i1 += 2;
	int i23 = (byte)nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	//this.bo = i23;
	//bp = new short[i23 * 3];
	int i26;
	for (i26 = 0; i26 < i23; i26++)
	{
		i1 += 2;
		//bp[(i26 * 3)] = ((short)c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
		i1 += 2;
		//bp[(i26 * 3 + 1)] = ((short)c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
		i1 += 2;
		//bp[(i26 * 3 + 2)] = ((short)c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
	}
	i1 += 2;
	i23 = nlMargeDigit(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
	//ci = false;
	if (i23 == 1)
	{
		//ci = true;
		//n = new int[7];
		i1 += 2;
		//n[0] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		//n[1] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		//n[2] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		//n[3] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		//n[4] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		//n[5] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
		i1 += 2;
		//n[6] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
	}
#if UNPARSED
	for (int i27 = dv - 1; i27 >= 0; i27--)
	{
		g(s[i27]);
		if (i27 == 0)
		{
			cv = s[i27].r;
			b(s[i27].z);
		}
		if (s[i27].y == 4) {
			s[i27].l = 1250;
		}
	}
	s[0].r = ((short)cv);
	x();
	if (ck) {
		l(0);
	}
#endif

	nlReadSpecnaz3DMapItems(j_l);
	class__k__lvl *lv = NEW(class__k__lvl);
	ZERO(lv, class__k__lvl);
	lv->class_g_array__q__scene = g_q;
	lv->class_j_array__l__item = j_l;
	lv->int_array__j__normal = int_j;
	lv->int_array__dm__texcoord = int_dm;
	lv->int__cC__rotation = cC;
	lv->int__cE__rotation = cE;
	lv->int_array__cF__translation[0] = cF[0];
	lv->int_array__cF__translation[1] = cF[1];
	lv->int_array__cF__translation[2] = cF[2];
	lv->class_c_array__o__bsp = class_c_array__o__bsp;
	return lv;
}

void class_k__function_P_void__item(class__j__item *l, const byte arrayOfByte1[])
{
	if(!l || !arrayOfByte1)
		return;
	int i1 = -2;
	i1 += 2;
	l->int__f__aabb = (nlMargeDigit(arrayOfByte1[0], arrayOfByte1[1]) << 16); // c
	i1 += 2;
	l->int__g__aabb = (nlMargeDigit(arrayOfByte1[2], arrayOfByte1[3]) << 16); // d
	i1 += 2;
	l->int__h__aabb = (nlMargeDigit(arrayOfByte1[4], arrayOfByte1[5]) << 16); // e
	i1 += 2;
	l->int__i__aabb = (nlMargeDigit(arrayOfByte1[6], arrayOfByte1[7]) << 16); // f
	i1 += 2;
	l->int__j__aabb = (nlMargeDigit(arrayOfByte1[8], arrayOfByte1[9]) << 16); // g
	i1 += 2;
	l->int__k__aabb = (nlMargeDigit(arrayOfByte1[10], arrayOfByte1[11]) << 16); // h
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	i1 += 2;
	int i3 = nlMargeDigit(arrayOfByte1[20], arrayOfByte1[21]);
	i1 += 2;
	int i2 = nlMargeDigit(arrayOfByte1[22], arrayOfByte1[23]);
	i1 += 2;
	int i4 = nlMargeDigit(arrayOfByte1[24], arrayOfByte1[25]);
	//k[i5].i = i3;
	l->int_array_6__a__vertex = new_array(nl_int, i3 * 6, NULL, 0);
	l->int_array_16__b__primitive = new_array(nl_int, i2 * 16, NULL, 0);
	int *a = (int *)(l->int_array_6__a__vertex->array);
	int *b = (int *)(l->int_array_16__b__primitive->array);
	i4 *= 2;
	int *arrayOfInt = NEW_II(int, i4);
	int i6;
	for (i6 = 0; i6 < i3; i6++)
	{
		i1 += 2;
		a[(i6 * 6)] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
		i1 += 2;
		a[(i6 * 6 + 1)] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
		i1 += 2;
		a[(i6 * 6 + 2)] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
	}
	int i7;
	for (i7 = 0; i7 < i2; i7++)
	{
		i1 += 2;
		b[(i7 * 16)] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 6);
		i1 += 2;
		b[(i7 * 16 + 1)] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 6);
		i1 += 2;
		b[(i7 * 16 + 2)] = (nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 6);
	}
	int i8;
	for (i8 = 0; i8 < i2; i8++)
	{
		i1 += 2;
		b[(i8 * 16 + 10)] = ((int)(65536 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L));
		i1 += 2;
		b[(i8 * 16 + 11)] = ((int)(65536 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L));
		i1 += 2;
		b[(i8 * 16 + 12)] = ((int)(65536 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L));
	}
	int i9;
	for (i9 = 0; i9 < i4; i9 += 2)
	{
		i1 += 2;
		arrayOfInt[i9] = ((int)(64 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 100L));
		i1 += 2;
		arrayOfInt[(i9 + 1)] = ((int)(64 * nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 100L));
	}
	int i10;
	for (i10 = 0; i10 < i2; i10++)
	{
		i1 += 2;
		b[(i10 * 16 + 3)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2)]);
		b[(i10 * 16 + 4)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2 + 1)]);
		i1 += 2;
		b[(i10 * 16 + 5)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2)]);
		b[(i10 * 16 + 6)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2 + 1)]);
		i1 += 2;
		b[(i10 * 16 + 7)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2)]);
		b[(i10 * 16 + 8)] = ((short)arrayOfInt[(nlMargeDigit(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2 + 1)]);
	}
	i1 += 2;
	int i11;
	for (i11 = 0; i11 < i2; i11++)
	{
		b[(i11 * 16 + 9)] = arrayOfByte1[i1];
		//bv[k[i5].b[(i11 * 16 + 9)]] = true;
		i1++;
	}
	free(arrayOfInt);
	/*
		 byte[] arrayOfByte2 = f.g.a(f.a(B), -1);
		 for (int i10 = 0; i10 < l.length; i10++)
		 {
		 j localj;
		 if ((localj = l[i10]).t < 120)
		 {
		 i8 = localj.t << 2;
		 if (arrayOfByte2[i8] == 1) {
		 localj.d = true;
		 }
		 if (arrayOfByte2[(i8 + 1)] == 1) {
		 localj.s = true;
		 }
		 if (arrayOfByte2[(i8 + 2)] == 1) {
		 localj.c = true;
		 }
		 if (arrayOfByte2[(i8 + 3)] == 1) {
		 localj.l = true;
		 }
		 o localo = k[localj.t];
		 localj.a = localo.a;
		 localj.b = localo.b;
		 localj.f = localo.c;
		 localj.i = localo.f;
		 localj.g = localo.d;
		 localj.j = localo.g;
		 localj.h = localo.e;
		 localj.k = localo.h;
		 if (localj.t == 50)
		 {
		 localj.f = 1300;
		 localj.g = 4000;
		 }
		 }
		 }
		 */
}

