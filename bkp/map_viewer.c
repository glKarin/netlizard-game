Bool IdleNETLizard3DMapZZZ(GLfloat xp, GLfloat yp, GLfloat zp)
{
#define ROLE_WIDTH 60.0
	fp_y += fp_y_unit;
	if(fp_y % 6 == 0)
		fp_y_unit = - fp_y_unit;
	fp_x += fp_x_unit;
	if(fp_x % 6 == 0)
		fp_x_unit = - fp_x_unit;

	if(is_cross)
	{
		x_t_3d = xp;
		y_t_3d = yp;
		z_t_3d = zp;
		return True;
	}

	GLfloat y = ator(y_r_3d);
	GLint scene = -1;
	GLdouble rgly = 0.0;
	GLdouble h = 0.0;
	int a = 1;
	GLdouble xarr[] = {0, sin(y) * ROLE_WIDTH, cos(y) * ROLE_WIDTH, -sin(y) * ROLE_WIDTH, -cos(y) * ROLE_WIDTH};
	GLdouble zarr[] = {0, cos(y) * ROLE_WIDTH, -sin(y) * ROLE_WIDTH, -cos(y) * ROLE_WIDTH, sin(y) * ROLE_WIDTH};
	GLdouble y_t_3ds[] = {0.0, 0.0, 0.0, 0.0, 0.0};
	int y_t_3ds_mask[] = {0, 0, 0, 0, 0};
	int i;
	for(i = 0; i < 5; i++)
	{
		double rx = xarr[i];
		double rz = zarr[i];
		if(nlNETLizardMapCollisionTest(map_model, x_t_3d + rx, y_t_3d, z_t_3d + rz, xp + rx, yp, zp + rz, COLLISION_WIDTH, &scene))
		{
			if(scene != -1)
			{
				current_scene = scene;
				GLdouble normal[3] = {0.0, 0.0, 0.0};
				if(nlNETLizardItemCollisionTest(map_model, x_t_3d + rx, y_t_3d, z_t_3d + rz, xp + rx, yp, zp + rz, COLLISION_WIDTH, COLLISION_HEIGHT, current_scene, normal, normal + 1, normal + 2))
				{
					if(nlGetFloorCoord(map_model, xp + rx, yp, zp + rz, &scene, &rgly))
					{
						y_t_3ds[i] = rgly;
						y_t_3ds_mask[i] = 1;
						if(1 || current_scene != scene)
						{
							current_scene = scene;
							if(nlNETLizardItemCollisionTest(map_model, x_t_3d + rx, y_t_3d, z_t_3d + rz, xp + rx, yp, zp + rz, COLLISION_WIDTH, 0, current_scene, normal, normal + 1, normal + 2))
							{
								if(nlGetItemCeilCoord(map_model, x_t_3d + rx, y_t_3d, z_t_3d + rz, scene, &rgly, &h))
								{
									y_t_3ds[i] = rgly;
									if(game == nl_contr_terrorism_3d || game == nl_contr_terrorism_3d_episode_2 || game == nl_army_ranger_3d)
										y_t_3ds[i] -= h;
									y_t_3ds_mask[i] = 1;
								}
							}
						}
						y_t_3ds[i] = y_t_3ds[i] - COLLISION_HEIGHT;
						y_t_3ds_mask[i] = 1;
					}
					else
					{
						if(nlGetItemCeilCoord(map_model, x_t_3d + rx, y_t_3d, z_t_3d + rz, current_scene, &rgly, &h))
						{
							y_t_3ds[i] = rgly;
							if(game == nl_contr_terrorism_3d || game == nl_contr_terrorism_3d_episode_2 || game == nl_army_ranger_3d)
								y_t_3ds[i] -= h;
							y_t_3ds_mask[i] = 1;
							y_t_3ds[i] = y_t_3ds[i] - COLLISION_HEIGHT;
						}
						else
						{
							//y_t_3ds[i] = yp;
							//y_t_3ds_mask[i] = 1;
						}
					}
				}
				else
				{
					if(i == 0)
					{
						a = 0;
						break;
					}
				}
			}
			else
			{
				if(i == 0)
				{
					a = 0;
					break;
				}
			}
		}
		else if(nlGetAllItemCeilCoord(map_model, x_t_3d + rx, y_t_3d, z_t_3d + rz, &rgly))
		{
			if(current_scene == -1 || nlNETLizardMapCollisionTest(map_model, x_t_3d + rx, y_t_3d, z_t_3d + rz, xp + rx, yp, zp + rz, COLLISION_WIDTH, &scene))
			{
				y_t_3ds[i] = rgly;
				y_t_3ds[i] = y_t_3d - COLLISION_HEIGHT;
				y_t_3ds_mask[i] = 1;
				printfs("__§_");
			}
			else
			{
				if(i == 0)
				{
					a = 0;
					break;
				}
			}
		}
		else if(current_scene == -1 && 0)
		{
			y_t_3ds[i] = yp;
			y_t_3ds_mask[i] = 1;
		}
		else
		{
			if(i == 0)
			{
				a = 0;
				break;
			}
		}
	}
	if(a)
	{
		GLdouble d = y_t_3ds[0];
		printf("%.2f  ", y_t_3ds[0]);
		for(i = 1; i < 5; i++)
		{
			printf("%.2f  ", y_t_3ds[i]);
			if(!y_t_3ds_mask[i])
				continue;
			if(d > y_t_3ds[i])
				d = y_t_3ds[i];
		}
		ENDL
			x_t_3d = xp;
		y_t_3d = d;
		z_t_3d = zp;
	}

	return True;
	//if(res < 1 || lamda > COLLISION_WIDTH)
}


#if 0
GLint * nlRayCollisionTest(const GLint *scenes, GLint count, GLint *res_count)
{
	if(!scenes || count == 0)
		return NULL;
	double y_a = 45.0; //x------
	double p = width / height;
	double H = height;
	double W = H * p;
	double h = H / 2;
	double w = W / 2;
	double l = h / tan(ator(y_a / 2));
	double x_a = rtoa(atan(w * tan(ator(y_a / 2)) / h)) * 2; // y------
	GLfloat y = ator(y_r_3d);
	GLfloat x = ator(x_r_3d);
	printff(w);
	printff(h);
	printff(x_a);
	vector3d left = {
		x_t_3d + cos(x) * cos(y) * w,
		y_t_3d - sin(x) * w,
		z_t_3d + cos(x) * sin(y) * w
	};
	vector3d right = {
		x_t_3d - cos(x) * cos(y) * w,
		y_t_3d + sin(x) * w,
		z_t_3d - cos(x) * sin(y) * w
	};
	vector3d top = {
		x_t_3d,
		y_t_3d - h,
		z_t_3d
	};
	vector3d bottom = {
		x_t_3d,
		y_t_3d + h,
		z_t_3d
	};
	GLdouble min_xr = y_r_3d - x_a / 2;
	GLdouble max_xr = y_r_3d + x_a / 2;
	GLdouble min_yr = x_r_3d - y_a / 2;
	GLdouble max_yr = x_r_3d + y_a / 2;
	GLdouble xr_unit = x_a / width;
	GLdouble yr_unit = y_a / width;
	vector3d xt_unit = nlVectorSubtract3d(&right, &left);
	vector3d yt_unit = nlVectorSubtract3d(&top, &bottom);
	glLineWidth(5.0);
	glPointSize(8.0);
	glDisable(GL_DEPTH_TEST);
	glBegin(GL_POINTS);
	{
		glColor3f(1.0, 0.0, 0.0);
		glVertex3d(x_t_3d, y_t_3d, z_t_3d);
		glVertex3d(-625, -180, 1000);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3d(top.x, top.y, top.z);
		glVertex3d(-625, -180, 1000);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3d(bottom.x, bottom.y, bottom.z);
		glVertex3d(-625, -180, 1000);
		glColor3f(1.0, 1.0, 0.0);
		glVertex3d(left.x, left.y, left.z);
		glVertex3d(-625, -180, 1000);
		glColor3f(1.0, 0.0, 1.0);
		glVertex3d(right.x, right.y, right.z);
		glVertex3d(-625, -180, 1000);
	}
	glEnd();
	glEnable(GL_DEPTH_TEST);
	glColor3f(1.0, 1.0, 1.0);
	return NULL;

	GLint *s = NEW_II(GLint, count);
	GLint *scene_tmp = NEW_II(GLint, count);
	memcpy(scene_tmp, scenes, count * sizeof(GLint));
	int o;
	for(o = 0; o < count; o++)
		s[o] = -1;
	GLdouble lamda = 0.0;
	GLint cur = -1;
	GLint available = 0;
	GLint cur_i = 0;
	printff(min_yr);
	printff(max_yr);
	printff(min_xr);
	printff(max_xr);
	printff(xr_unit);
	printff(yr_unit);

	GLdouble i;
	vector3d ii = bottom;
	for(i = min_yr; i <= max_yr; i += yr_unit)
	{
		GLdouble j;
		vector3d jj = left;
		for(j = min_xr; j <= max_xr; j += xr_unit)
		{
			cur = -1;
			GLfloat ty = ator(i);
			GLfloat tx = ator(j);
			vector3d dv = {
				-cos(tx) * sin(ty),
				sin(tx),
				cos(tx) * cos(ty)
			};
			vector3d pvt = nlVectorPlus3d(&ii, &jj);
			//printf("(%f, %f, %f)\n", pv.x, pv.y, pv.z);
			vector3d pv;
			pv.x = -pvt.x;
			pv.y = pvt.z;
			pv.z = -pvt.y;
			lined line = {pv, dv};
#if 0
			glLineWidth(5.0);
			glPointSize(1.0);
			glColor3f(1.0, 0.0, 0.0);
			glDisable(GL_DEPTH_TEST);
			glBegin(GL_LINES);
			{
				glVertex3d(pvt.x, pvt.y, pvt.z);
				glVertex3d(-625, -180, 1000);
			}
			glEnd();
			glEnable(GL_DEPTH_TEST);
			glColor3f(1.0, 1.0, 1.0);
			int k;
			for(k = 0; k < count; k++)
			{
				if(scene_tmp[k] == -1)
					continue;
				const GL_NETLizard_3D_Mesh *mesh = map_model -> meshes + scene_tmp[k];
				vector3d v1 = {mesh -> ortho[3], mesh -> ortho[4], mesh -> ortho[5]};
				vector3d v2 = {mesh -> ortho[0], mesh -> ortho[1], mesh -> ortho[2]};
				int m;
				for(m = 0; m < mesh -> plane_count; m++)
				{
					planed plane = {
						{mesh -> plane[m].position[0], mesh -> plane[m].position[1], mesh -> plane[m].position[2]},
						{mesh -> plane[m].normal[0], mesh -> plane[m].normal[1], mesh -> plane[m].normal[2]}
					};
					double la = 0.0;
					int r = nlLineToPlaneCollisionTest(&line, &plane, &la, NULL);
					if(r > 0)
					{
						vector3d point = {0.0, 0.0, 0.0};
						r = nlLineToPlaneIntersect(&line, &plane, &point);
						if(!nlPointIsInOrtho(&point, &v1, &v2))
							continue;
						printff(la);
						printfi(scene_tmp[k]);
						if(available == 0)
						{
							cur = scene_tmp[k];
							lamda = la;
							available = 1;
						}
						else
						{
							if(la < lamda)
							{
								cur = scene_tmp[k];
								lamda = la;
							}
						}
						scene_tmp[k] = -1;
						break;
					}
				}
			}
			int n;
			for(n = 0; n < count; n++)
			{
				if(s[n] == cur)
					break;
				if(s[n] == -1 && cur != -1)
				{
					s[n] = cur;
					cur_i++;
				}
			}
#endif
			jj = nlVectorPlus3d(&jj, &xt_unit);
		}
		ii = nlVectorPlus3d(&ii, &yt_unit);
	}
	printfi(cur_i);
	int n;
	for(n = 0; n < count; n++)
	{
		printf("%d ", s[n]);
	}
	ENDL
		for(n = 0; n < count; n++)
		{
			printf("%d ", scenes[n]);
		}
	ENDL
		for(n = 0; n < count; n++)
		{
			printf("%d ", scene_tmp[n]);
		}
	ENDL
		free(s);
	free(scene_tmp);
	return NULL;
}
#endif

static cube4_scene *cube_scene = NULL;
static GLuint *querys = NULL;
static void RenderScene(void);
//static frame_buffer_object *fbo = NULL;

// 2017 06 17
#if 0
int HandlePositionCoord_ZZZ(NLfloat *xt, NLfloat *yt, NLfloat *zt, NLfloat xo, NLfloat yo, NLfloat zo, NLfloat xp, NLfloat yp, NLfloat zp)
{
#define ROLE_WIDTH 30.0
#define ROLE_POINT 9
	GLint scene = -1;
	GLdouble rgly = 0.0;
	GLdouble h = 0.0;
	int res = 0;
	current_index = -1;
	GLfloat y = ator(y_r_3d);
	int available = 1;
	GLdouble xarr[] = {0, sin(y) * ROLE_WIDTH, cos(y) * ROLE_WIDTH, -sin(y) * ROLE_WIDTH, -cos(y) * ROLE_WIDTH, sin(y + 45.0) * ROLE_WIDTH, cos(y + 45.0) * ROLE_WIDTH, -sin(y + 45.0) * ROLE_WIDTH, -cos(y + 45.0) * ROLE_WIDTH};
	GLdouble zarr[] = {0, cos(y) * ROLE_WIDTH, -sin(y) * ROLE_WIDTH, -cos(y) * ROLE_WIDTH, sin(y) * ROLE_WIDTH, cos(y + 45.0) * ROLE_WIDTH, -sin(y + 45.0) * ROLE_WIDTH, -cos(y + 45.0) * ROLE_WIDTH, sin(y + 45.0) * ROLE_WIDTH};
	vector3_t vs[ROLE_POINT];
	int y_t_3ds_mask[] = {0, 0, 0, 0, 0};
	int i;
	for(i = 0; i < ROLE_POINT; i++)
	{
		double rx = xarr[i];
		double rz = zarr[i];
		vector3_t v1 = {xo + rx, yo, zo + rz};
		vector3_t v2 = {xp + rx, yp, zp + rz};
		vector3_t v = v1;
		res = nlNETLizardMapCollisionTest(map_model, &v1, &v2, COLLISION_WIDTH, &scene);
		//printfi(res);
		if(res == 2)
		{
			if(scene != -1)
			{
				current_scene = scene;
				vector3_t normal = {0.0, 0.0, 0.0};
				if(nlNETLizardItemCollisionTest(map_model, &v1, &v2, COLLISION_WIDTH, COLLISION_HEIGHT - 1, current_scene, &normal, &current_index))
				{
					if(is_elevator)
					{
						if(current_index != -1)
						{
							if(map_model -> item_meshes[current_index].item_type == Item_Elevator_Type)
							{
								double rgly2 = 0.0;
								int s = scene;
								if(nlGetFloorCoord2(map_model, &v1, &s, &rgly2))
								{
									//printf("%d %d, %f\n", scene, s, rgly2);
									scene = s;
									current_scene = scene;
									v2.y = rgly2;
									v2.x = v1.x; // xo ?
									v2.z = v1.z; // zo ?
								}
							}
						}
					}
					if(nlGetFloorCoord(map_model, &v2, &scene, &rgly))
					{
						v1.y = rgly;
						vector3_t vt = v2;
						if(/* 1 || */current_scene != scene)
						{
							current_scene = scene;
							current_index = -1;
							if(nlNETLizardItemCollisionTest(map_model, &v1, &v2, COLLISION_WIDTH, 0, current_scene, &normal, &current_index))
							{
								vt.y = v1.y;
							}
						}
						if(nlGetItemCeilCoord(map_model, &vt, scene, &rgly, &current_index, &h))
						{
							v1.y = rgly;
							if(game == nl_contr_terrorism_3d || game == nl_contr_terrorism_3d_episode_2 || game == nl_army_ranger_3d)
								v1.y -= h;
						}
						v.x = v2.x;
						v.z = v2.z;
						v.y = v1.y - COLLISION_HEIGHT;
					}
					else
					{
						if(nlGetItemCeilCoord(map_model, &v2, current_scene, &rgly, &current_index, &h))
						{
							v.x = v2.x;
							v.z = v2.z;
							v.y = rgly;
							if(game == nl_contr_terrorism_3d || game == nl_contr_terrorism_3d_episode_2 || game == nl_army_ranger_3d)
								v.y -= h;
							v.y = v.y - COLLISION_HEIGHT;
						}
						else
						{
							available = 0;
							break;
						}
					}
				}
				else
				{
					available = 0;
					break;
					//else printf("%f %f %f\n", normal[0], normal[1], normal[2]);
				}
			}
		}
		else if(res == 3)
		{
			current_scene = scene;
			if(nlGetItemCeilCoord(map_model, &v2, current_scene, &rgly, &current_index, &h))
			{
				v.x = v2.x;
				v.z = v2.z;
				v.y = rgly;
				v.y = v.y - COLLISION_HEIGHT;
			}
			else
			{
				v.x = xp;
				v.z = zp;
				v.y = yp;
			}
		}
		else if(res == 1)
		{
			available = 0;
			break;
		}
		else if(res == 4)
		{
			if(scene != -1 && current_scene != scene)
			{
				current_scene = scene;
				v.x = xp;
				v.z = zp;
				v.y = yo;
			}
			else if(scene != -1)
			{
				vector3_t normal = {0.0, 0.0, 0.0};
				if(nlNETLizardItemCollisionTest(map_model, &v1, &v1, COLLISION_WIDTH, COLLISION_HEIGHT - 1, current_scene, &normal, &current_index))
				{
					if(nlGetFloorCoord(map_model, &v1, &scene, &rgly))
					{
						v1.y = rgly;
						vector3_t vt = v1;
						if(/* 1 || */current_scene != scene)
						{
							current_scene = scene;
							current_index = -1;
							if(nlNETLizardItemCollisionTest(map_model, &v1, &v1, COLLISION_WIDTH, 0, current_scene, &normal, &current_index))
							{
								vt.y = v1.y;
							}
						}
						if(nlGetItemCeilCoord(map_model, &vt, scene, &rgly, &current_index, &h))
						{
							v1.y = rgly;
							if(game == nl_contr_terrorism_3d || game == nl_contr_terrorism_3d_episode_2 || game == nl_army_ranger_3d)
								v1.y -= h;
						}
						v.x = v1.x;
						v.z = v1.z;
						v.y = v1.y - COLLISION_HEIGHT;
					}
					else
					{
						if(nlGetItemCeilCoord(map_model, &v2, current_scene, &rgly, &current_index, &h))
						{
							v.x = v1.x;
							v.z = v1.z;
							v.y = rgly;
							if(game == nl_contr_terrorism_3d || game == nl_contr_terrorism_3d_episode_2 || game == nl_army_ranger_3d)
								v.y -= h;
							v.y = v.y - COLLISION_HEIGHT;
						}
						else
						{
							available = 0;
							break;
						}
					}
				}
				else
				{
					available = 0;
					break;
					//else printf("%f %f %f\n", normal[0], normal[1], normal[2]);
				}
			}
		}
		else
		{
			available = 0;
			break;
		}
		vs[i].x = v.x;
		vs[i].y = v.y;
		vs[i].z = v.z;
	}
	if(available)
	{
		GLdouble d = vs[0].y;
		printf("%.2f  ", vs[0].y);
		for(i = 1; i < ROLE_POINT; i++)
		{
			printf("%.2f  ", vs[i].y);
			/*
				 if(!y_t_3ds_mask[i])
				 continue;
				 */
			if(d > vs[i].y)
				d = vs[i].y;
		}
		ENDL
			if(xt)
				*xt = vs[0].x;
		if(yt)
			*yt = d;
		if(zt)
			*zt = vs[0].z;
		return 1;
	}
	else
	{
		printfs("_");
		return 0;
	}
}
#endif


void RenderScene(void)
{
	nlExtractFrustum(frustum);
	GLuint count = 0;
	GLint *scenes = nlGetRenderScenes(map_model, &count, frustum);
	if(!scenes)
		return;
	unsigned int t;
	for(t = 0; t < count; t++)
		printf(" %d", scenes[t]);
	ENDL
		querys = NEW_II(GLuint, count);
	glGenQueries(count, querys);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	nlRenderCube4(cube_scene, (GLuint *)scenes, querys, count);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLuint *s = NEW_II(GLuint, count);
	unsigned int c = 0;
	unsigned int i;
	for(i = 0; i < count; i++)
	{
		GLuint available = GL_FALSE;

		glGetQueryObjectuiv(querys[i], GL_QUERY_RESULT_AVAILABLE, &available);
		if(available)
		{
			GLint samples = 0;
			glGetQueryObjectiv(querys[i], GL_QUERY_RESULT, &samples);
			printf("  %d - %d\n", i, samples);
			if(samples != 0)
			{
				s[c] = scenes[i];
				c++;
			}
		}
	}

	GLint *s2 = NEW_II(GLint, c);
	memcpy(s2, s, sizeof(GLint) * c);
	free(s);
	nlRenderGLNETLizard3DModelScene(map_model, s2, c);
	for(i = 0; i < c; i++)
		printf("%d^ ", s2[i]);

	ENDL
		free(scenes);
	free(s2);
	glDeleteQueries(count, querys);
	free(querys);
}

nglRender3D(45, width, height, FRUSTUM_NEAR, frustum_far);
{
	glPushMatrix();
	{
		//glRotatef(x_r,1,0,0);
		//glRotatef(y_r,0,1,0);

		glTranslatef(-100, -150, -300);

		glScalef(0.3, 0.3, 0.3);
		glRotatef(90,0,1,0);
		glRotatef(yAxisRotate,0,1,0);
		glRotatef(xAxisRotate,1,0,0);

		glPushMatrix();
		{
			GLfloat y = ator(y_r);
			GLfloat x = ator(x_r);
			glColor3f(1.0, 0.0, 0.0);
			glLineWidth(2.0);
			glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(cos(x) * sin(y), // x
					sin(x), // y
					-cos(x) * cos(y) // z
					);
			glEnd();
			glColor3f(1.0, 1.0, 1.0);
			static GLuint anim = 0;
			static GLuint frame = 0;
			//nlRenderGLNETLizard3DAnimatonModel(role_model, anim, frame);
			frame++;
			if(frame >= clone3d_role_model -> anim_frame_count[anim])
				frame = 0;
		}
		glPopMatrix();
	}
	glPopMatrix();
}

#if 0
	GLubyte *data = NEW_II(GLubyte, width * height);
	glReadPixels(0, 0, width, height, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, data);
	int i, j;
	for(i = 0; i< height; i++)
	{
		for(j = 0; j < width; j++)
			if(data[i * height + j] == 0)
				printf("%d", data[i * height + j]);
		//printf("\n\n");
	}
	free(data);
#endif


#if 0
	static float dst_y = 0.0;
	if(at)
	{
		yp += Y_UNIT;
		if(HandlePositionCoord(&v.x, &v.y, &v.z, x_t_3d, y_t_3d, z_t_3d, xp, yp, zp))
		{
			x_t_3d = v.x;
			z_t_3d = v.z;
			y_t_3d += Y_UNIT;
		}
		if((dst_y - y_t_3d) < 0.0)
		{
			at = 0;
			dst_y = 0.0;
		}
	}
	else
	{
		if(HandlePositionCoord(&v.x, &v.y, &v.z, x_t_3d, y_t_3d, z_t_3d, xp, yp, zp))
		{
			if(!at)
			{
				float d = v.y - y_t_3d;
				if(d > Y_UNIT)
				{
					at = 1;
					dst_y = v.y;
					y_t_3d += Y_UNIT;
				}
				else
					y_t_3d = v.y;
			}
			x_t_3d = v.x;
			z_t_3d = v.z;
		}
	}
#endif

