#include "lol.h"
#include "mesh_reader.h"
#include "anim_reader.h"
#include "lol_render.h"
#include "SOIL/SOIL.h"

#include <string.h>
#include <stdlib.h>

static const char *lol_animation_type_name[LOL_Total_Type] = {
	"idle1,minigun_idle1",
	"idle2,rlauncher_idle2",
	"idle3,minigun_idle3",
	"idle1,rlauncher_idle3",
	"run,run1,minigun_run",
	"run2,rlauncher_run",
	"run,run1,minigun_run2",
	"run2,rlauncher_run2",
	"spell1,minigun_spell1_weapon2,launcher_spell1_weapon2",
	"spell2,minigun_spell2,rlauncher_spell2",
	"spell3,minigun_spell3,rlauncher_spell3",
	"spell4,minigun_spell4,rlauncher_spell4",
	"attack,attack1,minigun_attack1,minigun_attack2,minigun_attack3,minigun_attack4,minigun_attack5,minigun_attack6",
	"attackselector,rlauncher_attack1,rlauncher_attack2",
	"passive,minigun_spell2,rlauncher_spell2",
	"crit,minigun_spell3,rlauncher_spell3",
	"crit",
	"recall,rlauncher_recall",
	"joke,joke3",
	"taunt,taunt2",
	"dance,dance_loop",
	"laugh,laugh_loop",
	"death,minigun_death,rlauncher_death",
	"channel,channel_spell"
};

static GLuint LOL_LoadOpenGLTexture(const char *dds)
{
	if(!dds)
		return 0;
	int channel;
	int width = 0;
	int height = 0;
	GLuint texid = 0;
	unsigned char *data = SOIL_load_image((char *)dds, &width, &height, &channel, SOIL_LOAD_AUTO);
	if(!data)
		return 0;

	GLenum format = 0;
	switch(channel)
	{
		case SOIL_LOAD_L:
			format = GL_LUMINANCE;
			break;
		case SOIL_LOAD_LA:
			format = GL_LUMINANCE_ALPHA;
			break;
		case SOIL_LOAD_RGB:
			format = GL_RGB;
			break;
		case SOIL_LOAD_RGBA:
			format = GL_RGBA;
			break;
		default:
			break;
	}
	if(format != 0)
	{
		glGenTextures(1, &texid);
		oglBindTexture(GL_TEXTURE_2D, texid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	
#ifdef _HARMATTAN_OPENGLES
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
#else
		glGenerateMipmap(GL_TEXTURE_2D);
#endif
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

		oglBindTexture(GL_TEXTURE_2D, 0);

		free(data);

		return texid;
	}
	else
	{
		free(data);
		return 0;
	}
}

LOL_Model * new_LOL_Model(const char *meshf, const char *animf, const char *texf[], int texc)
{
	if(!meshf)
		return NULL;
	LOL_Mesh *mesh = new_LOL_Mesh(meshf);
	if(!mesh)
		return NULL;
	LOL_MakeGL2Mesh(mesh);
	LOL_Anim *anim = new_LOL_Anim(animf);
	GLuint *t = NULL;
	if(texf && texc)
	{
		t = calloc(texc, sizeof(GLuint));
		int i = 0;
		for(i = 0; i < texc; i++)
		{
			t[i] = LOL_LoadOpenGLTexture(texf[i]);
		}
	}

	LOL_Model *model = malloc(sizeof(LOL_Model));
	model -> mesh = mesh;
	model -> anim = anim;
	model -> tex = t;
	model -> tex_count = texc;
	return model;
}

void LOL_RenderModel(const LOL_Model *model, int animation, int animi, int framei)
{
	if(!model)
		return;
	if(!animation)
		LOL_RenderStaticModel(model -> mesh, model -> tex, model -> tex_count);
	else
	{
		if(!model -> anim)
			return;
		if(animi < 0 || animi >= (int)model -> anim -> animation_count)
			return;
		if(framei < 0 || framei >= (int)model -> anim -> animation[animi].animation_bone[0].frame_count)
			return;
		LOL_UpdateBone(&(model -> mesh -> bone_data), model -> anim -> animation + animi, framei);
		LOL_RenderAnimationModel(model -> mesh, model -> tex, model -> tex_count);
	}
}

void delete_LOL_Model(LOL_Model *model)
{
	if(!model)
		return;
	delete_LOL_Mesh(model -> mesh);
	delete_LOL_Anim(model -> anim);
	if(model -> tex && model -> tex_count)
	{
		unsigned int i;
		for(i = 0; i < model -> tex_count; i++)
		{
			glIsTexture(model -> tex[i]);
			glDeleteTextures(1, model -> tex + i);
		}
		free(model -> tex);
	}
	free(model -> mesh);
	free(model -> anim);
}

int LOL_GetAnimationRangeByName(const LOL_Model *model, const char *name, int *anim, int *count)
{
	if(!model || !name || !model -> anim)
		return -1;

	unsigned int i;
	for(i = 0; i < model -> anim -> animation_count; i++)
	{
		LOL_Animation *animation = model -> anim -> animation + i;
		if(animation -> name && strlen(animation -> name))
		{
			if(strcasecmp(animation -> name, name) == 0)
			{
				if(anim)
					*anim = i;
				if(animation -> animation_bone && animation -> bone_count)
				{
					if(count)
						*count = animation -> animation_bone[0].frame_count;
				}
				int j;
				for(j = LOL_Idle1_Type; j < LOL_Total_Type; j++)
				{
					char *n = strdup(lol_animation_type_name[j]);
					char *ptr = strtok(n, ",");
					do
					{
						if(strncmp(ptr, name, strlen(ptr)) == 0)
						{
							free(n);
							return j;
						}
					}while((ptr = strtok(NULL, ",")) != NULL);
					free(n);
				}
				return LOL_Other_Type;
			}
		}
	}
	return -1;
}

const char * LOL_GetAnimationRangeByType(const LOL_Model *model, LOL_Animation_Type type, int *anim, int *count)
{
	if(!model || !model -> anim)
		return NULL;

	if(type >= LOL_Total_Type)
		return NULL;
	unsigned int i;
	for(i = 0; i < model -> anim -> animation_count; i++)
	{
		LOL_Animation *animation = model -> anim -> animation + i;
		if(animation -> name && strlen(animation -> name))
		{
			char *name = strdup(lol_animation_type_name[type]);
			char *ptr = strtok(name, ",");
			do
			{
				if(strncmp(ptr, animation -> name, strlen(ptr)) == 0)
				{
					if(anim)
						*anim = i;
					if(animation -> animation_bone && animation -> bone_count)
					{
						if(count)
							*count = animation -> animation_bone[0].frame_count;
					}
					free(name);
					return animation -> name;
				}
			}while((ptr = strtok(NULL, ",")) != NULL);
			free(name);
		}
	}
	return NULL;
}
