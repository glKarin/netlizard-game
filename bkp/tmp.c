
int HandlePositionCoord(const gl_vector3_t *ori_v, const gl_vector3_t *new_v, gl_vector3_t *return_v, int *cs, int *ci)
{
	if(!ori_v || !new_v || !return_v)
		return 0;
	int scene = -1;
	NLfloat rgly = 0.0;
	NLfloat h = 0.0;
	int res = 0;
	int currentindex = -1;
	int currentscene = -1;
	if(cs)
		currentscene = *cs;
	gl_vector3_t v1 = *ori_v;
	gl_vector3_t v2 = *new_v;
	gl_vector3_t v = v1;
	res = nlNETLizardMapCollisionTest(map_model, &v2, COLLISION_WIDTH, &scene);
	//printfi(res);
	if(res == 2)
	{
		if(scene != -1)
		{
			currentscene = scene;
			nl_vector3_t normal = {0.0, 0.0, 0.0};
			if(nlNETLizardItemCollisionTest(map_model, &v1, &v2, COLLISION_WIDTH, COLLISION_HEIGHT - 1, currentscene, &normal, &currentindex))
			{
				if(is_elevator)
				{
					if(currentindex != -1)
					{
						if(map_model -> item_meshes[currentindex].item_type == Item_Elevator_Type)
						{
							NLfloat rgly2 = 0.0;
							int s = scene;
							if(nlGetFloorCoord2(map_model, &v1, &s, &rgly2))
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
				if(nlGetFloorCoord(map_model, &v2, &scene, &rgly))
				{
					gl_vector3_t vt = v2;
					vt.y = v1.y; // 2017 6 20 replace
					v1.y = rgly;
					if(/* 1 || */currentscene != scene)
					{
						currentscene = scene;
						currentindex = -1;
						if(nlNETLizardItemCollisionTest(map_model, &v1, &v2, COLLISION_WIDTH, 0, currentscene, &normal, &currentindex))
						{
							vt.y = -map_model -> meshes[currentscene].ortho[2];
							// vt.y = v1.y; 1017 6 20 replace
						}
					}
					if(nlGetItemCeilCoord(map_model, &vt, scene, COLLISION_WIDTH, &rgly, &currentindex, &h))
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
					if(nlGetItemCeilCoord(map_model, &v2, currentscene, COLLISION_WIDTH, &rgly, &currentindex, &h))
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
						v.x = new_v -> x;
						v.z = new_v -> z;
						v.y = new_v -> y;
					}
				}
			}
			else
			{
				//else printf("%f %f %f\n", normal[0], normal[1], normal[2]);
			}
		}
	}
	else if(res == 3)
	{
		currentscene = scene;
		if(nlGetItemCeilCoord(map_model, &v2, currentscene, COLLISION_WIDTH, &rgly, &currentindex, &h))
		{
			v.x = v2.x;
			v.z = v2.z;
			v.y = rgly;
			v.y = v.y - COLLISION_HEIGHT;
		}
		else
		{
			v.x = new_v -> x;
			v.z = new_v -> z;
			const GL_NETLizard_3D_Mesh *mesh = map_model -> meshes + currentscene;
			v.y = -mesh -> ortho[5] - COLLISION_HEIGHT;
		}
	}
	else if(res == 1)
	{
		return 0;
	}
	else if(res == 4)
	{
		if(scene != -1 && currentscene != scene)
		{
			currentscene = scene;
			v.x = new_v -> x;
			v.z = new_v -> z;
			v.y = ori_v -> y;
		}
		else if(scene != -1)
		{
			nl_vector3_t normal = {0.0, 0.0, 0.0};
			if(nlNETLizardItemCollisionTest(map_model, &v1, &v1, COLLISION_WIDTH, COLLISION_HEIGHT - 1, currentscene, &normal, &currentindex))
			{
				if(nlGetFloorCoord(map_model, &v1, &scene, &rgly))
				{
					v1.y = rgly;
					gl_vector3_t vt = v1;
					if(/* 1 || */currentscene != scene)
					{
						currentscene = scene;
						currentindex = -1;
						if(nlNETLizardItemCollisionTest(map_model, &v1, &v1, COLLISION_WIDTH, 0, currentscene, &normal, &currentindex))
						{
							vt.y = v1.y;
						}
					}
					if(nlGetItemCeilCoord(map_model, &vt, scene, COLLISION_WIDTH, &rgly, &currentindex, &h))
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
					if(nlGetItemCeilCoord(map_model, &v2, currentscene, COLLISION_WIDTH, &rgly, &currentindex, &h))
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
						v.x = new_v -> x;
						v.z = new_v -> z;
						v.y = new_v -> y;
					}
				}
			}
			else
			{
				//else printf("%f %f %f\n", normal[0], normal[1], normal[2]);
			}
		}
	}
	else
		return 0;
#if 0
	else // res = 0
	{
		if(currentscene == -1)
		{
			if(nlGetAllItemCeilCoord(map_model, &v2, &rgly, &currentindex))
			{
				v.x = new_v -> x;
				v.z = new_v -> z;
				v.y = rgly;
				v.y = v.y - COLLISION_HEIGHT;
			}
			else
			{
				v.x = new_v -> x;
				v.z = new_v -> z;
				v.y = new_v -> y;
			}
		}
	}
#endif
	return_v -> x = v.x;
	return_v -> y = v.y;
	return_v -> z = v.z;
	if(cs)
		*cs = currentscene;
	if(ci)
		*ci = currentindex;
	return 1;
}


int HandlePositionCoord(NLfloat *xt, NLfloat *yt, NLfloat *zt, NLfloat xo, NLfloat yo, NLfloat zo, NLfloat xp, NLfloat yp, NLfloat zp)
{
	int scene = -1;
	NLfloat rgly = 0.0;
	NLfloat h = 0.0;
	int res = 0;
	current_index = -1;
	gl_vector3_t v1 = {xo, yo, zo};
	gl_vector3_t v2 = {xp, yp, zp};
	gl_vector3_t v = v1;
	res = nlNETLizardMapCollisionTest(map_model, &v2, COLLISION_WIDTH, &scene);
	//printfi(res);
	if(res == 2)
	{
		if(scene != -1)
		{
			current_scene = scene;
			nl_vector3_t normal = {0.0, 0.0, 0.0};
			if(nlNETLizardItemCollisionTest(map_model, &v1, &v2, COLLISION_WIDTH, COLLISION_HEIGHT - 1, current_scene, &normal, &current_index))
			{
				if(is_elevator)
				{
					if(current_index != -1)
					{
						if(map_model -> item_meshes[current_index].item_type == Item_Elevator_Type)
						{
							NLfloat rgly2 = 0.0;
							int s = scene;
							if(nlGetFloorCoord2(map_model, &v1, &s, &rgly2))
							{
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
					gl_vector3_t vt = v2;
					vt.y = v1.y; // 2017 6 20 replace
					v1.y = rgly;
					if(/* 1 || */current_scene != scene)
					{
						current_scene = scene;
						current_index = -1;
						if(nlNETLizardItemCollisionTest(map_model, &v1, &v2, COLLISION_WIDTH, 0, current_scene, &normal, &current_index))
						{
							vt.y = -map_model -> meshes[current_scene].ortho[2];
							// vt.y = v1.y; 1017 6 20 replace
						}
					}
					if(nlGetItemCeilCoord(map_model, &vt, scene, COLLISION_WIDTH, &rgly, &current_index, &h))
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
					if(nlGetItemCeilCoord(map_model, &v2, current_scene, COLLISION_WIDTH, &rgly, &current_index, &h))
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
						v.x = xp;
						v.z = zp;
						v.y = yp;
					}
				}
			}
			else
			{
				//else printf("%f %f %f\n", normal[0], normal[1], normal[2]);
			}
		}
	}
	else if(res == 3)
	{
		current_scene = scene;
		if(nlGetItemCeilCoord(map_model, &v2, current_scene, COLLISION_WIDTH, &rgly, &current_index, &h))
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
			const GL_NETLizard_3D_Mesh *mesh = map_model -> meshes + current_scene;
			v.y = -mesh -> ortho[5] - COLLISION_HEIGHT;
		}
	}
	else if(res == 1)
	{
		return 0;
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
			nl_vector3_t normal = {0.0, 0.0, 0.0};
			if(nlNETLizardItemCollisionTest(map_model, &v1, &v1, COLLISION_WIDTH, COLLISION_HEIGHT - 1, current_scene, &normal, &current_index))
			{
				if(nlGetFloorCoord(map_model, &v1, &scene, &rgly))
				{
					v1.y = rgly;
					gl_vector3_t vt = v1;
					if(/* 1 || */current_scene != scene)
					{
						current_scene = scene;
						current_index = -1;
						if(nlNETLizardItemCollisionTest(map_model, &v1, &v1, COLLISION_WIDTH, 0, current_scene, &normal, &current_index))
						{
							vt.y = v1.y;
						}
					}
					if(nlGetItemCeilCoord(map_model, &vt, scene, COLLISION_WIDTH, &rgly, &current_index, &h))
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
					if(nlGetItemCeilCoord(map_model, &v2, current_scene, COLLISION_WIDTH, &rgly, &current_index, &h))
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
						v.x = xp;
						v.z = zp;
						v.y = yp;
					}
				}
			}
			else
			{
				//else printf("%f %f %f\n", normal[0], normal[1], normal[2]);
			}
		}
	}
	else
		return 0;
#if 0
	else // res = 0
	{
		if(current_scene == -1)
		{
			if(nlGetAllItemCeilCoord(map_model, &v2, &rgly, &current_index))
			{
				v.x = xp;
				v.z = zp;
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
	}
#endif
	if(xt)
		*xt = v.x;
	if(yt)
		*yt = v.y;
	if(zt)
		*zt = v.z;
	return 1;
}

