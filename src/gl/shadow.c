#include "shadow.h"
#include "base_algo.h"
#include "graph.h"
#include "list_template.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define F_ZERO 0.1

#define Shadow_Vec3cmp Vector3_EqualsVector3
#define Shadow_Linecmp LineSegment_EqualsLineSegment

static int Shadow_EqualsVector3(const vector3_t *a, const vector3_t *b)
{
	float xd, yd, zd;

	if(!a || !b)
		return 0;
	xd = VECTORV_X(a) - VECTORV_X(b);
	yd = VECTORV_Y(a) - VECTORV_Y(b);
	zd = VECTORV_Z(a) - VECTORV_Z(b);

	return(
			(xd <= F_ZERO && xd >= -F_ZERO) &&
			(yd <= F_ZERO && yd >= -F_ZERO) &&
			(zd <= F_ZERO && zd >= -F_ZERO)
			);
}

static int Shadow_EqualsLineSegment(const line_segment_t *l1, const line_segment_t *l2)
{
	if(!l1 || !l2)
		return 0;
	return(((Shadow_EqualsVector3(&l1->a, &l2->a) && Shadow_EqualsVector3(&l1->b, &l2->b)) || (Shadow_EqualsVector3(&l1->a, &l2->b) && Shadow_EqualsVector3(&l1->b, &l2->a))) ? 1 : 0);
}


static void Shadow_Vector3ToArray(GLfloat r[3], const vector3_t *v)
{
	if(!r || !v)
		return;
	r[0] = VECTORV_X(v);
	r[1] = VECTORV_Y(v);
	r[2] = VECTORV_Z(v);
}

static void Shadow_ArrayToVector3(vector3_t *r, const GLfloat v[], int count)
{
	if(!r || !v)
		return;
	if(count >= 4 && v[3] != 0)
	{
		VECTORV_X(r) = v[0] / v[3];
		VECTORV_Y(r) = v[1] / v[3];
		VECTORV_Z(r) = v[2] / v[3];
	}
	else
	{
		VECTORV_X(r) = v[0];
		VECTORV_Y(r) = v[1];
		VECTORV_Z(r) = v[2];
	}
}

static vector3_t * Shadow_MakeHeapVector3From4(const GLfloat v[4])
{
	vector3_t *r;

	if(!v)
		return NULL;

	r = NEW(vector3_t);
	VECTORV_X(r) = v[0] / v[3];
	VECTORV_Y(r) = v[1] / v[3];
	VECTORV_Z(r) = v[2] / v[3];
	return r;
}

vector3_t Algo_LightingDir(const vector3_t *v, const vector3_t *lightpos, int dirlight)
{
	int d;
	vector3_t r = VECTOR3(0, 0, 0);

	if(!lightpos)
		return r;

	d = !v ? 1 : dirlight;

	if(d)
	{
		r = Vector3_Normalizer(lightpos);
		Vector3_InvertSelf(&r);
	}
	else
	{
		r = *v;
		r = Vector3_Direction(lightpos, v);
	}

	return r;
}

void Shadow_CaleTrans(material_s *r, const GL_NETLizard_3D_Mesh *nl_mesh, const glmatrix44_t *mat)
{
	glmatrix44_t nor_mat;
	int count;
	unsigned int i, j;
	int m, n;
	point_s *point;
	const GL_NETLizard_3D_Vertex *nl_vertex;
	GLushort *nl_indexs;
	const GL_NETLizard_3D_Material *nl_mat;
	vector3_t v;

	if(!r || !nl_mesh || !mat)
		return;

	count = 0;
	for(i = 0; i < nl_mesh->count; i++)
	{
		count += nl_mesh->materials[i].index_count;
	}
	newmat(r, count);
	n = 0;
	nl_indexs = nl_mesh->vertex_array.vertex_data.index;
	for(i = 0; i < nl_mesh->count; i++)
	{
		nl_mat = nl_mesh->materials + i;
		for(j = nl_mat->index_start; j < nl_mat->index_count; j++)
		{
			point = r->points + n;
			m = nl_indexs[j];
			nl_vertex = nl_mesh->vertex_array.vertex_data.vertex + m;

			memcpy(point->vertex, nl_vertex->position, sizeof(GLfloat) * 3);
			point->vertex[3] = 1;
			memcpy(point->texcoord, nl_vertex->texcoord, sizeof(GLfloat) * 2);
			memcpy(point->normal, nl_vertex->normal, sizeof(GLfloat) * 3);

			n++;
		}
	}
	r->use_color = 0;
	r->texture = 0;
	r->color[0] = r->color[1] = r->color[2] = 1;
	r->color[3] = 1;
	
	Math3D_glMatrix44InverseTransposev(&nor_mat, mat);
	for(i = 0; i < (unsigned int)r->count; i++)
	{
		point = r->points + i;
		Shadow_ArrayToVector3(&v, point->vertex, 4);
		v = Math3D_Vector3MultiplyMatrix44(&v, mat);
		Shadow_Vector3ToArray(point->vertex, &v);
		point->vertex[3] = 1;

		Shadow_ArrayToVector3(&v, point->normal, 3);
		v = Math3D_Vector3MultiplyMatrix44_3x3(&v, &nor_mat);
		Vector3_Normalize(&v);
		Shadow_Vector3ToArray(point->normal, &v);
	}

#if 0
	glDisable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glLineWidth(4);
	glPointSize(25);
	GLfloat nv[6];
	for(i = 0; i < r->count; i++)
	{
		vector3_t rv = VECTOR3V(r->points[i].vertex);
		nv[0] = VECTOR_X(rv);
		nv[1] = VECTOR_Y(rv);
		nv[2] = VECTOR_Z(rv);

		vector3_t rv2 = VECTOR3V(r->points[i].normal);
		Vector3_ScaleSelf(&rv2, 20);
		rv2 = Vector3_PlusVector3(&rv, &rv2);
		nv[3] = VECTOR_X(rv2);
		nv[4] = VECTOR_Y(rv2);
		nv[5] = VECTOR_Z(rv2);
		glVertexPointer(3, GL_FLOAT, 0, nv);
		glColor4f(1.0, 0.0, 1.0, 1.0);
		glDrawArrays(GL_LINES, 0, 2);
		glColor4f(0.0, 0.0, 1.0, 1.0);
		glDrawArrays(GL_POINTS, 0, 1);
	}
	glEnable(GL_DEPTH_TEST);
	glLineWidth(1);
	glPointSize(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glDisableClientState(GL_VERTEX_ARRAY);
#endif
#if 0
	glDisable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glPointSize(20);
	GLfloat nv[3];
	for(i = 0; i < r->count; i++)
	{
	glColor4f(0.0, 1.0, 1.0, 1.0);
		vector3_t rv0 = VECTOR3(0, 0, 0);
		rv0 = Math3D_Vector3MultiplyMatrix44(&rv0, mat);
		nv[0] = VECTOR_X(rv0);
		nv[1] = VECTOR_Y(rv0);
		nv[2] = VECTOR_Z(rv0);
		glVertexPointer(3, GL_FLOAT, 0, nv);
		glDrawArrays(GL_POINTS, 0, 1);

	glColor4f(0.0, 1.0, 0.0, 1.0);
		vector3_t rv = VECTOR3V(r->points[i].vertex);
		nv[0] = VECTOR_X(rv);
		nv[1] = VECTOR_Y(rv);
		nv[2] = VECTOR_Z(rv);
		glVertexPointer(3, GL_FLOAT, 0, nv);
		glDrawArrays(GL_POINTS, 0, 1);
	}
	glPointSize(1);
	glEnable(GL_DEPTH_TEST);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glDisableClientState(GL_VERTEX_ARRAY);
#endif
}

// cale shadow volume
void Shadow_MakeVolume(mesh_s *r, const vector3_t *lightpos, const material_s *mat)
{
	int has;
	line_segment_t lp, *lpptr;
	int i, k, n, o;
	point_s *pa;
	material_s *m;
	list_t(line_segment_t) lines; // line_s
#if ZFAIL_SHADOW
	list_t(vector3_t) tops, bottoms; // vector3_t
#endif
	GLfloat *v;

	if(!r || !lightpos || !mat || !mat->count)
		return;

	LIST(&lines, line_segment_t);
#if ZFAIL_SHADOW
	LIST(&tops, vector3_t);
	LIST(&bottoms, vector3_t);
#endif
#if ZFAIL_SHADOW
	newmesh(r, 3); // top[1] bottom[2] caps, and side[0]
#else
	newmesh(r, 1); // top[1] bottom[2] caps, and side[0]
#endif
	for(i = 0; i < mat->count / 3; i++) // cale triangle
	{
		pa = mat->points + (i * 3);
		v = pa->vertex;
		vector3_t nor = VECTOR3V(pa->normal);
		vector3_t p = VECTOR3V(v);
		vector3_t p2l = Algo_LightingDir(&p, lightpos, DIR_LIGHTING);
#if 0
	glDisable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor4f(0.0, 1.0, 0.0, 1.0);
	{
		GLfloat nv[6];
		nv[0] = VECTOR_X(p);
		nv[1] = VECTOR_Y(p);
		nv[2] = VECTOR_Z(p);

		nv[3] = VECTORV_X(lightpos);
		nv[4] = VECTORV_Y(lightpos);
		nv[5] = VECTORV_Z(lightpos);
		glVertexPointer(3, GL_FLOAT, 0, nv);
		glDrawArrays(GL_LINES, 0, 2);
	}
	glEnable(GL_DEPTH_TEST);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glDisableClientState(GL_VERTEX_ARRAY);
#endif
		Vector3_InvertSelf(&p2l);
		float dot_p = Vector3_DotVector3(&p2l, &nor);
#if 0
	glDisable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	if(dot_p > 0.0) // face to light source
		glColor4f(1.0, 0.0, 0.0, 1.0);
	else
		glColor4f(0.0, 1.0, 0.0, 1.0);
	{
		GLfloat nv[6];
		nv[0] = VECTOR_X(p);
		nv[1] = VECTOR_Y(p);
		nv[2] = VECTOR_Z(p);
		vector3_t p2 = p;
		vector3_t p3 = Vector3_Scale(&p2l, 200);
		p2 = Vector3_PlusVector3(&p2, &p3);

		nv[3] = VECTOR_X(p2);
		nv[4] = VECTOR_Y(p2);
		nv[5] = VECTOR_Z(p2);
		glVertexPointer(3, GL_FLOAT, 0, nv);
		glDrawArrays(GL_LINES, 0, 2);
	}
	glEnable(GL_DEPTH_TEST);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glDisableClientState(GL_VERTEX_ARRAY);
#endif
		//qDebug()<<i<<nor<<p<<dot_p;
		if(dot_p > 0.0) // face to light source
		{
			for(n = 0; n < 3; n++) // 3 points of triangle
			{
				Shadow_ArrayToVector3(&lp.a, pa[n].vertex, 4);
				Shadow_ArrayToVector3(&lp.b, pa[(n + 1) % 3].vertex, 4);
				has = 0;
				for(o = 0; o < lines.count; o++) // find in lines list
				{
					if(Shadow_Linecmp(&lp, List_GetConstDataByIndexT(&lines, o, line_segment_t))) // if exists, remove this line, then continue
					{
						//printf("%d exist\n", i);
						List_DeleteOneByIndex(&lines, o);
						has = 1;
#if 0
	glDisable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor4f(1.0, 0.0, 1.0, 1.0);
	glDepthFunc(GL_LEQUAL);
	glLineWidth(4.0);
	glPushMatrix();
	{
		GLfloat vs[6];
			printf("%d %d\n", o, lines.count);
			vs[0] = VECTOR_X(lp.a);
			vs[1] = VECTOR_Y(lp.a);
			vs[2] = VECTOR_Z(lp.a);

			vs[3] = VECTOR_X(lp.b);
			vs[4] = VECTOR_Y(lp.b);
			vs[5] = VECTOR_Z(lp.b);
			glVertexPointer(3, GL_FLOAT, 0, vs);
			glDrawArrays(GL_LINES, 0, 2);
	}
	glPopMatrix();
	glLineWidth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glDisableClientState(GL_VERTEX_ARRAY);
#endif
						break;
					}
				}
				if(!has) // if not exists, add new line to list
				{
					lpptr = NEW(line_segment_t);
					lpptr->a = lp.a;
					lpptr->b = lp.b;
					List_PushBackV(&lines, lpptr);
#if 0
	glDisable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor4f(0.0, 0.0, 1.0, 1.0);
	glDepthFunc(GL_LEQUAL);
	glLineWidth(4.0);
	glPushMatrix();
	{
		GLfloat vs[6];
			printf("%d %d\n", o, lines.count);
			lpptr = List_GetConstDataByIndexT(&lines, o, line_segment_t);
			vs[0] = VECTOR_X(lpptr->a);
			vs[1] = VECTOR_Y(lpptr->a);
			vs[2] = VECTOR_Z(lpptr->a);

			vs[3] = VECTOR_X(lpptr->b);
			vs[4] = VECTOR_Y(lpptr->b);
			vs[5] = VECTOR_Z(lpptr->b);
			glVertexPointer(3, GL_FLOAT, 0, vs);
			glDrawArrays(GL_LINES, 0, 2);
	}
	glPopMatrix();
	glLineWidth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glDisableClientState(GL_VERTEX_ARRAY);
#endif
				}
			}
#if ZFAIL_SHADOW
			// top cap triangle
			tops.vvv(&tops, Shadow_MakeHeapVector3From4(pa[0].vertex))->vvv(&tops, Shadow_MakeHeapVector3From4(pa[1].vertex))->vvv(&tops, Shadow_MakeHeapVector3From4(pa[2].vertex));
#endif
		}
		else
		{
#if ZFAIL_SHADOW
			// bottom cap triangle
			bottoms.vvv(&bottoms, Shadow_MakeHeapVector3From4(pa[0].vertex))->vvv(&bottoms, Shadow_MakeHeapVector3From4(pa[1].vertex))->vvv(&bottoms, Shadow_MakeHeapVector3From4(pa[2].vertex));
#endif
		}
	}
#if 0
	glDisable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor4f(0.0, 0.0, 1.0, 1.0);
	glDepthFunc(GL_LEQUAL);
	glLineWidth(4.0);
	glPushMatrix();
	{
		GLfloat vs[6];
		for(o = 0; o < lines.count; o++) // find in lines list
		{
			//printf("%d %d\n", o, lines.count);
			lpptr = List_GetConstDataByIndexT(&lines, o, line_segment_t);
			vs[0] = VECTOR_X(lpptr->a);
			vs[1] = VECTOR_Y(lpptr->a);
			vs[2] = VECTOR_Z(lpptr->a);

			vs[3] = VECTOR_X(lpptr->b);
			vs[4] = VECTOR_Y(lpptr->b);
			vs[5] = VECTOR_Z(lpptr->b);
			glVertexPointer(3, GL_FLOAT, 0, vs);
			glDrawArrays(GL_LINES, 0, 2);
		}
	}
	glPopMatrix();
	glLineWidth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glDisableClientState(GL_VERTEX_ARRAY);
#endif

	// cale sides of shadow volume
	m = r->materials;
	newmat(m, lines.count * 6); // 2 triangles(6 points) every a line
	k = 0;
	// TODO: cale clock wise, now the lighting source must be above all cubes
	for(i = 0; i < lines.count; i++)
	{
		lpptr = List_GetDataByIndexT(&lines, i, line_segment_t);
		// point lighting
		vector3_t dir_a = Algo_LightingDir(&lpptr->a, lightpos, DIR_LIGHTING);
		Vector3_ScaleSelf(&dir_a, SHADOW_VOLUME_LENGTH);
		dir_a = Vector3_PlusVector3(&lpptr->a, &dir_a);
		vector3_t dir_b = Algo_LightingDir(&lpptr->b, lightpos, DIR_LIGHTING);
		Vector3_ScaleSelf(&dir_b, SHADOW_VOLUME_LENGTH);
		dir_b = Vector3_PlusVector3(&lpptr->b, &dir_b);

#if 0
	glDisable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor4f(0.0, 0.0, 1.0, 1.0);
	glDepthFunc(GL_LEQUAL);
	glLineWidth(4.0);
	glPushMatrix();
	{
		GLfloat vs[6];
			//printf("%d %d\n", o, lines.count);
			vs[0] = VECTOR_X(lpptr->a);
			vs[1] = VECTOR_Y(lpptr->a);
			vs[2] = VECTOR_Z(lpptr->a);

			vs[3] = VECTOR_X(dir_a);
			vs[4] = VECTOR_Y(dir_a);
			vs[5] = VECTOR_Z(dir_a);
			glVertexPointer(3, GL_FLOAT, 0, vs);
			glDrawArrays(GL_LINES, 0, 2);

			vs[0] = VECTOR_X(lpptr->b);
			vs[1] = VECTOR_Y(lpptr->b);
			vs[2] = VECTOR_Z(lpptr->b);

			vs[3] = VECTOR_X(dir_b);
			vs[4] = VECTOR_Y(dir_b);
			vs[5] = VECTOR_Z(dir_b);
			glVertexPointer(3, GL_FLOAT, 0, vs);
			glDrawArrays(GL_LINES, 0, 2);
	}
	glPopMatrix();
	glLineWidth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glDisableClientState(GL_VERTEX_ARRAY);
#endif
#if 0
	//glDisable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor4f(0.0, 1.0, 1.0, 0.2);
	glDepthFunc(GL_LEQUAL);
	glLineWidth(4.0);
	glPushMatrix();
	{
		GLfloat vs[18];
			//printf("%d %d\n", o, lines.count);
			vs[0] = VECTOR_X(lpptr->a);
			vs[1] = VECTOR_Y(lpptr->a);
			vs[2] = VECTOR_Z(lpptr->a);

			vs[3] = VECTOR_X(dir_a);
			vs[4] = VECTOR_Y(dir_a);
			vs[5] = VECTOR_Z(dir_a);

			vs[6] = VECTOR_X(lpptr->b);
			vs[7] = VECTOR_Y(lpptr->b);
			vs[8] = VECTOR_Z(lpptr->b);

			vs[9] = VECTOR_X(dir_a);
			vs[10] = VECTOR_Y(dir_a);
			vs[11] = VECTOR_Z(dir_a);

			vs[12] = VECTOR_X(dir_b);
			vs[13] = VECTOR_Y(dir_b);
			vs[14] = VECTOR_Z(dir_b);

			vs[15] = VECTOR_X(lpptr->b);
			vs[16] = VECTOR_Y(lpptr->b);
			vs[17] = VECTOR_Z(lpptr->b);

			glVertexPointer(3, GL_FLOAT, 0, vs);
			glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	glPopMatrix();
	glLineWidth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glDisableClientState(GL_VERTEX_ARRAY);
#endif
		// triangle 1
		pa = m->points + k * 6;
		Shadow_Vector3ToArray(pa->vertex, &lpptr->a);
		pa->vertex[3] = 1;
		pa = m->points + k * 6 + 1;
		Shadow_Vector3ToArray(pa->vertex, &dir_a);
		pa->vertex[3] = SHADOW_VOLUME_FAR_W;
		pa = m->points + k * 6 + 2;
		Shadow_Vector3ToArray(pa->vertex, &lpptr->b);
		pa->vertex[3] = 1;

		// triangle 2
		pa = m->points + k * 6 + 3;
		Shadow_Vector3ToArray(pa->vertex, &dir_a);
		pa->vertex[3] = SHADOW_VOLUME_FAR_W;
		pa = m->points + k * 6 + 4;
		Shadow_Vector3ToArray(pa->vertex, &dir_b);
		pa->vertex[3] = SHADOW_VOLUME_FAR_W;
		pa = m->points + k * 6 + 5;
		Shadow_Vector3ToArray(pa->vertex, &lpptr->b);
		pa->vertex[3] = 1;

#if 0
	//glDisable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor4f(0.0, 1.0, 1.0, 0.2);
	glDepthFunc(GL_LEQUAL);
	glLineWidth(4.0);
	glPushMatrix();
	{
		GLfloat vs[18];
		// triangle 1
		pa = m->points + k * 6;
		memcpy(vs, pa->vertex, sizeof(GLfloat) * 3);
		pa = m->points + k * 6 + 1;
		memcpy(vs + 3, pa->vertex, sizeof(GLfloat) * 3);
		pa = m->points + k * 6 + 2;
		memcpy(vs + 6, pa->vertex, sizeof(GLfloat) * 3);

		// triangle 2
		pa = m->points + k * 6 + 3;
		memcpy(vs + 9, pa->vertex, sizeof(GLfloat) * 3);
		pa = m->points + k * 6 + 4;
		memcpy(vs + 12, pa->vertex, sizeof(GLfloat) * 3);
		pa = m->points + k * 6 + 5;
		memcpy(vs + 15, pa->vertex, sizeof(GLfloat) * 3);

			glVertexPointer(3, GL_FLOAT, 0, vs);
			glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	glPopMatrix();
	glLineWidth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glDisableClientState(GL_VERTEX_ARRAY);
#endif
		k++;
	}

#if ZFAIL_SHADOW
	// cale top cap of shadow volume
	// using triangles of the mesh faces to lighting source
	m = r->materials + 1;
	newmat(m, tops.count);
	for(k = 0; k < tops.count; k += 3)
	{
		const vector3_t *first = List_GetDataByIndexT(&tops, k, vector3_t);
		const vector3_t *sec = List_GetDataByIndexT(&tops, k + 1, vector3_t);
		const vector3_t *third = List_GetDataByIndexT(&tops, k + 2, vector3_t);
		pa = m->points + k;
		Shadow_Vector3ToArray(pa->vertex, first);
		pa = m->points + k + 1;
		Shadow_Vector3ToArray(pa->vertex, sec);
		pa = m->points + k + 2;
		Shadow_Vector3ToArray(pa->vertex, third);
	}

	// cale bottom cap of shadow volume
	// using triangles of the mesh not faces to lighting source
	m = r->materials + 2;
	newmat(m, bottoms.count);
	for(k = 0; k < bottoms.count; k += 3)
	{
		const vector3_t *first = List_GetDataByIndexT(&bottoms, k, vector3_t);
		const vector3_t *sec = List_GetDataByIndexT(&bottoms, k + 1, vector3_t);
		const vector3_t *third = List_GetDataByIndexT(&bottoms, k + 2, vector3_t);

		// point lighting
		vector3_t dir_a = Algo_LightingDir(first, lightpos, DIR_LIGHTING);
		Vector3_ScaleSelf(&dir_a, SHADOW_VOLUME_LENGTH);
		vector3_t dir_b = Algo_LightingDir(sec, lightpos, DIR_LIGHTING);
		Vector3_ScaleSelf(&dir_b, SHADOW_VOLUME_LENGTH);
		vector3_t dir_c = Algo_LightingDir(third, lightpos, DIR_LIGHTING);
		Vector3_ScaleSelf(&dir_c, SHADOW_VOLUME_LENGTH);

		pa = m->points + k;
		Shadow_Vector3ToArray(pa->vertex, &dir_a);
		pa->vertex[3] = SHADOW_VOLUME_FAR_W;
		pa = m->points + k + 1;
		Shadow_Vector3ToArray(pa->vertex, &dir_b);
		pa->vertex[3] = SHADOW_VOLUME_FAR_W;
		pa = m->points + k + 2;
		Shadow_Vector3ToArray(pa->vertex, &dir_c);
		pa->vertex[3] = SHADOW_VOLUME_FAR_W;
	}
#endif

#if 0
	//glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	//glDisable(GL_CULL_FACE);
	//glDepthFunc(GL_LEQUAL);
	//glDisable(GL_BLEND);

	glEnableClientState(GL_VERTEX_ARRAY);

//printf("%d %d %d\n", lines.count, r->count, r->materials->count);
	r->materials->use_color = 1;
	r->materials->color[0] = 
	r->materials->color[1] = 
	r->materials->color[2] = 0.0;
	r->materials->color[3] = 0.2;
	glColor4f(1,0,0,1);
	rendermesh(r);
	//rendermat(r->materials);

#if ZFAIL_SHADOW
	glColor4f(0,1,0,1);
	rendermat(r->materials + 1);
	glColor4f(0,0,1,1);
	rendermat(r->materials + 2);
#endif

	glColor4f(1,1,1,1);

	glDepthFunc(GL_LESS);
	glLineWidth(1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	glDisableClientState(GL_VERTEX_ARRAY);
#endif

__Exit:
	List_DeleteAll(&lines);
#if ZFAIL_SHADOW
	List_DeleteAll(&tops);
	List_DeleteAll(&bottoms);
#endif
}

void Shadow_RenderVolume(const material_s *nl_mesh, const vector3_t *lpos, int render_count)
{
	mesh_s *vol;

	if(!nl_mesh || !lpos)
		return;

	vol = (mesh_s *)calloc(1, sizeof(mesh_s));

	Shadow_MakeVolume(vol, lpos, nl_mesh);

	// render
	// 1: get depth buffer of scene
#if 0
	glClearStencil(0);
	glClear(GL_STENCIL_BUFFER_BIT);
	if(render_count == 0)
	{
		glDisable(GL_BLEND);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

		//rendermat(nl_mesh);
	}
#endif
	//goto __Exit;

	glEnableClientState(GL_VERTEX_ARRAY);
	//glDepthFunc(GL_LEQUAL);
#if ZFAIL_SHADOW
	// 2: Z-Fail
#ifdef GL_ARB_depth_clamp
	glEnable(GL_DEPTH_CLAMP);
#endif
	glDepthMask(GL_FALSE);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 0, ~0U);

	// 2-1: cale front faces of shadow volume
#ifdef _HARMATTAN_OPENGLES
	glStencilOp(GL_KEEP, GL_INCR_WRAP, GL_KEEP);
	glCullFace(GL_FRONT);
	rendermesh(vol);

	// 2-1: cale back faces of shadow volume
	glStencilOp(GL_KEEP, GL_DECR_WRAP, GL_KEEP);
	glCullFace(GL_BACK);
	rendermesh(vol);
#else
	glDisable(GL_CULL_FACE);
	glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
	glStencilOpSeparate(GL_BACK, GL_KEEP, GL_DECR_WRAP, GL_KEEP);
	rendermesh(vol);
	glEnable(GL_CULL_FACE);
#endif

#ifdef GL_ARB_depth_clamp
	glDisable(GL_DEPTH_CLAMP);
#endif
#else
	// 2: Z-Pass
#if 0
	glDepthMask(GL_FALSE);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 0, ~0U);
#endif

#if 0
	vol->materials->use_color = 1;
	vol->materials->color[0] = 
	vol->materials->color[1] = 
	vol->materials->color[2] = 0.0;
	vol->materials->color[3] = 0.2;
#endif
	// 2-1: cale front faces of shadow volume
#ifdef _HARMATTAN_OPENGLES
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR_WRAP);
	glCullFace(GL_BACK);
	rendermesh(vol);

	// 2-1: cale back faces of shadow volume
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR_WRAP);
	glCullFace(GL_FRONT);
	rendermesh(vol);
#else
	glDisable(GL_CULL_FACE);
	glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_KEEP, GL_INCR_WRAP);
	glStencilOpSeparate(GL_BACK, GL_KEEP, GL_KEEP, GL_DECR_WRAP);
	rendermesh(vol);
	glEnable(GL_CULL_FACE);
#endif
#endif
	//glDepthFunc(GL_LESS);
	glDisableClientState(GL_VERTEX_ARRAY);

#if 0
#if SHADOW_MASK
#if 0	
	if(render_count != -1)
	{
		// 3: final render scene again
		glCullFace(GL_BACK);
		glDepthFunc(GL_EQUAL); // GL_LESS will not pass depth-testing
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glStencilFunc(GL_NOTEQUAL, 0, ~0U);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glEnable(GL_BLEND);

		glDisable(GL_DEPTH_TEST);
		Shadow_RenderMask();

		// 4: reset OpenGL state
		glDisable(GL_STENCIL_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
	}
#else
		glCullFace(GL_BACK);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDisable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glDepthMask(GL_TRUE);
#endif
#else
	if(render_count != -1)
	{
		// 3: final render scene again
		glCullFace(GL_BACK);
		glDepthFunc(GL_EQUAL); // GL_LESS will not pass depth-testing
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glStencilFunc(GL_EQUAL, 0, ~0U);
		glBlendFunc(GL_ONE, GL_ONE);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glEnable(GL_BLEND);

		rendermat(nl_mesh);

		// 4: reset OpenGL state
		glDepthMask(GL_TRUE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
		glDisable(GL_STENCIL_TEST);
		glDisable(GL_BLEND);
		glDepthFunc(GL_LESS);
	}
#endif
#endif

__Exit:
	freemesh(vol);
	free(vol);
}

void Shadow_RenderShadow(const GL_NETLizard_3D_Item_Mesh *mesh, const vector3_t *lightpos)
{
	material_s m;
	glmatrix44_t mat;

	if(!mesh)
		return;

	memset(&m, 0, sizeof(material_s));

	Matrix44_glIdentity(&mat);
#if 1
	Matrix44_glTranslateSelf(&mat, mesh->pos[0], mesh->pos[1], mesh->pos[2]);
	Matrix44_glRotateSelf(&mat, mesh->angle[0], 1.0f, 0.0f, 0.0f);
	Matrix44_glRotateSelf(&mat, mesh->angle[1], 0.0f, 0.0f, 1.0f);
#else
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(mesh->pos[0], mesh->pos[1], mesh->pos[2]);
	glRotatef(mesh->angle[0], 1.0f, 0.0f, 0.0f);
	glRotatef(mesh->angle[1], 0.0f, 0.0f, 1.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, mat.x);
	glPopMatrix();
#endif

	Shadow_CaleTrans(&m, &mesh->item_mesh, &mat);

	Shadow_RenderVolume(&m, lightpos, 0);

__Exit:
	freemat(&m);
}

