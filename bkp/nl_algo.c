/*
1  3  |  5  7
0  2  |  4  6
*/
static const GLuint CubePlane4Index[] = 
{
	// 正
	0, 2, 1, 1, 2, 3,
	// 背
	4, 6, 5, 5, 6, 7,
	// 左
	4, 0, 1, 1, 5, 4,
	// 右
	6, 7, 2, 7, 3, 2,
	// 上
	1, 3, 7, 3, 7, 5,
	// 下
	0, 2, 4, 4, 2, 6
};
/*
1  3  |  5  7
0  2  |  4  6
*/
static const GLuint Cube4Index[] = 
{
	1, 5, 3, 7,  1, 3, 5, 7,
	0, 4, 2, 6,  0, 2, 4, 6,
	0, 1, 2, 3,  4, 5, 6, 7
};

typedef struct _cube4_scene
{
	GLuint *vertex_buffers;
	GLuint cube_count;
	GLuint index_buffer_type;
} cube4_scene;

void nlRenderCube4(const cube4_scene *scene, const unsigned int *s, const GLuint *query, unsigned int count)
{
	if(!scene || !s)
		return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scene -> index_buffer);
	unsigned int i;
	for(i = 0; i < count; i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, scene -> vertex_buffers[s[i]]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		if(query)
			glBeginQuery(GL_SAMPLES_PASSED, query[i]);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint)NULL);
		if(query)
			glEndQuery(GL_SAMPLES_PASSED);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

#if 0
// backup function UNUSED
int nlNETLizardMapCollisionTest__BACKUP(const GL_NETLizard_3D_Model *netlizard_3d_model, const vector3_t *xyz, const vector3_t *n_xyz, GLdouble width, GLint *scene)
{
	if(!netlizard_3d_model || !xyz || !n_xyz)
		return 0;
	int res = 0;

	double lamda = 0.0;
	double glx = xyz -> x;
	double gly = xyz -> y;
	double glz = xyz -> z;
	double nglx = n_xyz -> x;
	double ngly = n_xyz -> y;
	double nglz = n_xyz -> z;
	vector3_t position = {-glx, glz, -gly};
	vector3_t new_position = {-nglx, nglz, -ngly};
	vector3_t direction = nlVectorSubtract3d(&new_position, &position);
	nlVectorNormalize(&direction);
	line_t line = {new_position, direction};
	unsigned int i;
	for(i = 0; i < netlizard_3d_model -> count; i++)
	{
		const GL_NETLizard_3D_Mesh *mesh = netlizard_3d_model -> meshes + i;
		vector3_t v1 = {mesh -> ortho[3], mesh -> ortho[4], mesh -> ortho[5]};
		vector3_t v2 = {mesh -> ortho[0], mesh -> ortho[1], mesh -> ortho[2]};
		//printf("%.1f %.1f %.1f | %.1f %.1f %.1f | %.1f %.1f %.1f\n", new_position.x, new_position.y, new_position.z, v1.x, v1.y, v1.z, v2.x, v2.y, v2.z);
		// 检测新位置是否在地图中某一场景盒子内
		if(nlPointInBox(&new_position, &v1, &v2))
		{
			res = 1;
			const GL_NETLizard_3D_Mesh *mesh = netlizard_3d_model -> meshes + i;
			unsigned int j;
			// 检测新位置是否在场景盒子中真实场景内
			for(j = 0; j < mesh -> plane_count; j++)
			{
				plane_t plane = {
					{mesh -> plane[j].position[0], mesh -> plane[j].position[1], mesh -> plane[j].position[2]},
					{mesh -> plane[j].normal[0], mesh -> plane[j].normal[1], mesh -> plane[j].normal[2]}
				};
				line_t l = {new_position, {-mesh -> plane[j].normal[0], -mesh -> plane[j].normal[1], -mesh -> plane[j].normal[2]}};
				res = nlLineToPlaneCollisionTest(&l, &plane, NULL, NULL);
				if(res != 1)
				{
					if(scene)
						*scene = -1;
					return res;
				}
			}
			if(scene)
				*scene = i;

			// 与场景中平面进行碰撞测试
			for(j = 0; j < mesh -> plane_count; j++)
			{
				if(mesh -> plane[j].normal[2] > 0.866025)
					continue;
				plane_t plane = {
					{mesh -> plane[j].position[0], mesh -> plane[j].position[1], mesh -> plane[j].position[2]},
					{mesh -> plane[j].normal[0], mesh -> plane[j].normal[1], mesh -> plane[j].normal[2]}
				};
				vector3_t normal = {0.0, 0.0, 0.0};
				res = nlLineToPlaneCollisionTest(&line, &plane, &lamda, &normal);
				if(res > 0 && lamda <= width)
				{
					return res;
				}
			}
			res = 2;
			return res;
		}
	}
	return res;
}
#endif


cube4_scene * nlGetNETLizardSceneCubes(const GL_NETLizard_3D_Model *model)
{
	if(!model)
		return NULL;
	cube4_scene *scene = NEW(cube4_scene);
	ZERO(scene, cube4_scene);
	scene -> vertex_buffers = NEW_II(GLuint, model -> count);
	scene -> cube_count = model -> count;
	scene -> index_buffer = new_buffer(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), CubePlane4Index, GL_STATIC_DRAW);
	unsigned int i;
	for(i = 0; i < model -> count; i++)
	{
		const GL_NETLizard_3D_Mesh *mesh = model -> meshes + i;
		vector3_t v1 = {mesh -> ortho[3], mesh -> ortho[4], mesh -> ortho[5]};
		vector3_t v2 = {mesh -> ortho[0], mesh -> ortho[1], mesh -> ortho[2]};
		NLfloat vertex[24];
		nlGetAABBVertex(&v1, &v2, vertex);
		scene -> vertex_buffers[i] = new_buffer(GL_ARRAY_BUFFER, 24 * sizeof(NLfloat), vertex, GL_STATIC_DRAW);
	}
	return scene;
}


void nlGetAABBVertex(const nl_vector3_t *v1, const nl_vector3_t *v2, float *vertex)
{
	if(!vertex || !v1 || !v2)
		return;
	float minx = v1 -> x;
	float miny = v1 -> y;
	float minz = v1 -> z;
	float maxx = v2 -> x;
	float maxy = v2 -> y;
	float maxz = v2 -> z;
	// 前左下 0
	vertex[0] = minx;
	vertex[1] = miny;
	vertex[2] = minz;
	// 前左上 1
	vertex[3] = minx;
	vertex[4] = maxy;
	vertex[5] = minz;
	// 前右下 2
	vertex[6] = maxx;
	vertex[7] = miny;
	vertex[8] = minz;
	// 前右上 3
	vertex[9] = maxx;
	vertex[10] = maxy;
	vertex[11] = minz;
	// 后左下 4
	vertex[12] = minx;
	vertex[13] = miny;
	vertex[14] = maxz;
	// 后左上 5
	vertex[15] = minx;
	vertex[16] = maxy;
	vertex[17] = maxz;
	// 后右下 6
	vertex[18] = maxx;
	vertex[19] = miny;
	vertex[20] = maxz;
	// 后右上 7
	vertex[21] = maxx;
	vertex[22] = maxy;
	vertex[23] = maxz;
}
#if 0
				if(is_elevator)
				{
					if(currentindex != -1)
					{
						if(map_model -> item_meshes[currentindex].item_type == Item_Elevator_Type)
						{
							float rgly2 = 0.0;
							int s = scene;
							if(Algo_ComputeTopFloorCoord(map_model, &v1, &s, &rgly2))
							{
								scene = s;
								currentscene = scene;
								v2.y = rgly2;
								v2.x = v1.x; // ori_v -> x ?
								v2.z = v1.z; // ori_v -> z ?
							}
						}
					}
				}
#endif
