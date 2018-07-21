#include "particle.h"
#include "game_util.h"
#include "nl_algo.h"
#include "physics/gravity.h"

#include <stdlib.h>
#include <string.h>

#define SPIRIT_MAP_FILE _KARIN_RESOURCE_DIR"resource/cu.png"
#define SPIRIT_TEX_FILE _KARIN_RESOURCE_DIR"resource/u0.png"

#define SPIRIT_TRACK_FILE _KARIN_GAME_DIR"clone3d/o/o56.png"
#define SPIRIT_TRACK_INDEX 56
#define SPIRIT_TRACK2_FILE _KARIN_GAME_DIR"clone3d/o/o57.png"
#define SPIRIT_TRACK2_INDEX 57
#define SPIRIT_BLOOD_FILE _KARIN_GAME_DIR"clone3d/o/o58.png"
#define SPIRIT_BLOOD_INDEX 58
#define SPIRIT_GRENADE_FILE _KARIN_GAME_DIR"ct3dep2/o/o44.png"
#define SPIRIT_GRENADE_INDEX 44

static const particle_effect_type Clone3D_Particle_Effect_Types[] = {
	boom_particle_type, // small
	boom_particle_type, // middle
	boom_particle_type, // large
	trace_particle_type, // large
	other_particle_type, // red ray point
	gunfire_particle_type,
	trace_particle_type, // small
	blood_spot_particle_type, // young
	blood_spot_particle_type, // young 2
	blood_block_particle_type,
	blood_block_particle_type,
	blood_block_particle_type,
	blood_block_particle_type,
	gunfire_particle_type
};

static const GLuint Clone3D_Particle_Effect_Count = 14;

particle_spirit * new_particle_spirit(particle_spirit *sp)
{
	RETURN_PTR(p, sp, particle_spirit)	
	p->spirit = NETLizard_ReadSpirit(SPIRIT_MAP_FILE, SPIRIT_TEX_FILE);

#define MODEL_ITEM_COUNT 4
	GL_NETLizard_3D_Model *models[MODEL_ITEM_COUNT] = {NULL, NULL, NULL, NULL};
	models[0] = NETLizard_ReadGLClone3DItemModelFile(SPIRIT_TRACK_FILE, SPIRIT_TRACK_INDEX);
	models[1] = NETLizard_ReadGLClone3DItemModelFile(SPIRIT_TRACK2_FILE, SPIRIT_TRACK2_INDEX);
	models[2] = NETLizard_ReadGLClone3DItemModelFile(SPIRIT_BLOOD_FILE, SPIRIT_BLOOD_INDEX);
	models[3] = NETLizard_ReadGLCT3DEp2ItemModelFile(SPIRIT_GRENADE_FILE, SPIRIT_GRENADE_INDEX);
	GLuint i;
	for(i = 0; i < MODEL_ITEM_COUNT; i++)
	{
		if(models[i] == NULL)
			break;
	}
	p->spirit_3d = NULL;
	if(i == MODEL_ITEM_COUNT)
	{
		GL_NETLizard_3D_Model *model = NEW(GL_NETLizard_3D_Model);
		ZERO(model, GL_NETLizard_3D_Model);

		GLuint tex_count = 0;
		GLuint tex_indexs[MODEL_ITEM_COUNT] = {0, 0, 0, 0};
		GLuint j;
		for(j = 0; j < MODEL_ITEM_COUNT; j++)
			tex_indexs[j] = models[j]->item_meshes[0].item_mesh.count; 

		for(j = 0; j < MODEL_ITEM_COUNT; j++)
			tex_count += tex_indexs[j];

		model->texes = NEW_II(texture *, tex_count);
		model->tex_count = tex_count;
		GLuint ti = 0;
		for(i = 0; i < MODEL_ITEM_COUNT; i++)
		{
			for(j = 0; j < tex_indexs[0]; j++)
			{
				GLint index = models[i]->item_meshes[0].item_mesh.tex_index[j];
				model->texes[ti] = models[i]->texes[index];
				models[i]->texes[index] = NULL;

				models[i]->item_meshes[0].item_mesh.tex_index[j] = ti;
				models[i]->item_meshes[0].item_mesh.materials[j].tex_index = ti;
				ti++;
			}
		}

		model->item_count = MODEL_ITEM_COUNT;
		model->item_meshes = NEW_II(GL_NETLizard_3D_Item_Mesh, MODEL_ITEM_COUNT);
		for(i = 0; i < MODEL_ITEM_COUNT; i++)
			NETLizard_MoveItemModel(model->item_meshes + i, models[i]->item_meshes);

		for(i = 0; i < MODEL_ITEM_COUNT; i++)
		{
			delete_GL_NETLizard_3D_Model(models[i]);
			free(models[i]);
		}

		NETLizard_MakeGL23DModel(model);
		p->spirit_3d = model;
	}
	p->type_count = Clone3D_Particle_Effect_Count;
	p->types = NEW_II(GLuint, p->type_count);

	for(i = 0; i < p->type_count; i++)
	{
		p->types[i] = Clone3D_Particle_Effect_Types[i];
	}
	return p;
}

GLint Particle_GetSpiritIndexByType(particle_spirit *p, particle_effect_type t)
{
	if(!p)
		return -1;
	if(t < other_particle_type)
	{
		GLuint c = 0;
		GLint *indexs = NEW_II(GLint, p->type_count);
		GLuint i;
		for(i = 0; i < p->type_count; i++)
		{
			if(t == p->types[i])
			{
				indexs[c] = i;
				c++;
			}
		}
		GLint r = -1;
		if(c > 0)
			r = indexs[rand() % c];
		free(indexs);
		return r;
	}
	else if(t > other_particle_type && t < other_3d_particle_type)
	{
		return t - other_particle_type - 1;
	}
	return -1;
}

void delete_particle_spirit(particle_spirit *p)
{
	if(!p)
		return;
	if(p->spirit)
	{
		delete_GL_NETLizard_Spirit(p->spirit);
		free(p->spirit);
		p->spirit = NULL;
	}
	if(p->spirit_3d)
	{
		delete_GL_NETLizard_3D_Model(p->spirit_3d);
		free(p->spirit_3d);
		p->spirit_3d = NULL;
	}
	FREE_PTR(p->types)
		p->type_count = 0;
}

void Particle_RanderParitcle(particle_spirit *p, particle_effect_type type)
{
	if(!p)
		return;
	if(!p->spirit)
		return;
	GLint index = Particle_GetSpiritIndexByType(p, type);
	if(index != -1)
	{
		if(type < other_particle_type && p->spirit)
		{
			glPushAttrib(GL_POLYGON_BIT);
			{
				oglDisable(GL_CULL_FACE);
				int r = 0;
				switch(type)
				{
					case blood_spot_particle_type:
						r = 1;
						break;
					case gunfire_particle_type:
						r = 2;
						break;
					case blood_block_particle_type:
						r = 2;
						break;
					case boom_particle_type:
					case trace_particle_type:
						r = 4;
						break;
					default:
						return;
				}
				int i;
				for(i = 0; i < r; i++)
				{
					glPushMatrix();
					{
						if(i != 0)
							glRotatef(180.0 / r * i, 0.0f, 1.0f, 0.0f);
						NETLizard_RenderSpirit(p->spirit, index);
					}
					glPopMatrix();
				}
			}
			glPopAttrib();
		}
		else if(type > other_particle_type && type < other_3d_particle_type && p->spirit_3d)
		{
			if(type == track_particle_type || type == blood_particle_type)
			{
				glPushAttrib(GL_POLYGON_BIT);
				{
					oglDisable(GL_CULL_FACE);
					NETLizard_RenderGL3DMesh(&p->spirit_3d->item_meshes[index].item_mesh, p->spirit_3d->texes);
				}
				glPopAttrib();
			}
			else
				NETLizard_RenderGL3DMesh(&p->spirit_3d->item_meshes[index].item_mesh, p->spirit_3d->texes);
		}
	}
}

void Particle_UpdateParticle(const GL_NETLizard_3D_Model *model, particle *p, long long game_time)
{
	if(!p)
		return;
	if(p->finished)
		return;
	if(game_time - p->time >= p->interval)
	{
		p->finished = GL_TRUE;
		return;
	}
	GLboolean update = GL_TRUE;
	int gravity = 0;
	if(p->movement_type == parabola_particle_type)
		gravity = 1;
	else if(p->movement_type == straight_particle_type)
		gravity = 0;
	else
		update = GL_FALSE;

	if(update)
	{
		nl_vector3_t start_pos = {p->start_pos[0], p->start_pos[1], p->start_pos[2]};
		nl_vector3_t last_pos = {p->last_pos[0], p->last_pos[1], p->last_pos[2]};
		nl_vector3_t pos = {0.0, 0.0, 0.0};
		/*float dis = */Physics_GetGravityPosition(p->speed, &start_pos, &last_pos, p->x_dir, p->y_dir, game_time - p->time, gravity, &pos, NULL, NULL/*&p->x_angle, &p->y_angle*/);
		p->last_pos[0] = p->pos[0];
		p->last_pos[1] = p->pos[1];
		p->last_pos[2] = p->pos[2];
		p->pos[0] = pos.x;
		p->pos[1] = pos.y;
		p->pos[2] = pos.z;

		if(p->collision && model)
		{
			nl_vector3_t v = {0.0, 0.0, 0.0};
			nl_vector3_t pos = {p->pos[0], p->pos[1], p->pos[2]};
			nl_vector3_t last_pos = {p->last_pos[0], p->last_pos[1], p->last_pos[2]};
			int r = Algo_ComputePositionInNETLizard3DMapNotGravity(model, &last_pos, &pos, 0, 0, &v, NULL, NULL);
			if(r == 0)
			{
				p->pos[0] = v.x;
				p->pos[1] = v.y;
				p->pos[2] = v.z;
				p->movement_type = fixed_particle_type;
			}
		}
	}
}

particle Particle_MakeParticle(particle_effect_type type, particle_movement_type movetype, GLfloat x, GLfloat y, GLfloat z, GLfloat xr, GLfloat yr, GLfloat xdir, GLfloat ydir, GLfloat s, long long time, long long interval, GLboolean collision)
{
	float xoffset = 0.0;
	if(type < other_particle_type)
		xoffset = -90.0;
	particle p = {
		type, movetype, {x, y, z}, {x, y, z}, {x, y, z}, xr + xoffset, yr, xdir, ydir, s, time, interval, collision, GL_FALSE};
	return p;
}
