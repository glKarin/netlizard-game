#include "anim_reader.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <math.h>

#define IN_CHUNK 1024
#define CHUNK 16384

static void LOL_ReadAnimationData(FILE *data, LOL_Anim *anim);
static int LOL_InflateZ(FILE *data, FILE* dest);

LOL_Anim * new_LOL_Anim(const char *file)
{
	if(!file)
		return NULL;
	FILE *in = fopen(file, "rb");
	if(!in)
		return NULL;
	unsigned int magic = 0;
	fread(&magic, 4, 1, in);
	if(magic != 604210092)
	{
		fclose(in);
		return NULL;
	}
	LOL_Anim *anim = malloc(sizeof(LOL_Anim));
	memset(anim, 0, sizeof(LOL_Anim));

	anim->magic = magic;
	fread(&anim->version, 4, 1, in);
	if(anim->version >= 2 && anim->version != 4) // 2018
	{
		//FILE *out = tmpfile();
		size_t str_len = 0;
		char *home = getenv("HOME");
		if(home)
		{
			str_len += (strlen(home) + 1);
			str_len += (strlen(_KARIN_HOME) + 1);
		}
		const char Tmp_File_Name[] = "lol.inflate_anim.tmp";
		str_len += (strlen(Tmp_File_Name) + 1);
		char *tmpf = calloc(str_len, sizeof(char));
		memset(tmpf, '\0', sizeof(char) * str_len);
		char *p = tmpf;
		if(home)
		{
			strcat(p, home);
			p += strlen(home);
			strcat(p, "/");
			p += 1;
			strcat(p, _KARIN_HOME);
			p += strlen(_KARIN_HOME);
			strcat(p, "/");
			p += 1;
		}
		strcat(p, Tmp_File_Name);
		tmpf[str_len - 1] = '\0';
		//printfs(tmpf);
		FILE *out = fopen(tmpf, "wb");
		if(!out)
		{
			free(anim);
			return NULL;
		}
		LOL_InflateZ(in, out);
		fflush(out);
		freopen(NULL, "rb", out);
		fseek(out, 0, SEEK_SET);
		LOL_ReadAnimationData(out, anim);
		fclose(out);
		//remove(tmpf);
		free(tmpf);
	}
	else
		LOL_ReadAnimationData(in, anim);

	fclose(in);
	return anim;
}

void LOL_ReadAnimationData(FILE *data, LOL_Anim *anim)
{
	if(!data && !anim)
		return;
	fread(&anim->animation_count, 4, 1, data);
	anim->animation = calloc(anim->animation_count, sizeof(LOL_Animation));
	unsigned int i;
	for(i = 0; i < anim->animation_count; i++)
	{
		LOL_Animation *animation = anim->animation + i;
		animation->name = LOL_ReadLowerStringData(data, 0);
		fread(&animation->fps, 4, 1, data);
		// 2018
		if(anim->version >= 4)
			fread(&animation->duration, 4, 1, data);
		animation->duration *= 1e3;
		// end
		fread(&animation->bone_count, 4, 1, data);

		animation->animation_bone = calloc(animation->bone_count, sizeof(LOL_Animation_Bone));

		unsigned int j;
		for(j = 0; j < animation->bone_count; j++)
		{
			LOL_Animation_Bone *animBone = animation->animation_bone + j;
			fread(&animBone->frame_count, 4, 1, data);
			animBone->bone = LOL_ReadLowerStringData(data, 0);
			fread(&animBone->flag, 4, 1, data);
			animBone->frame = calloc(animBone->frame_count, sizeof(LOL_Frame));
			if(anim->version >= 3)
			{
				fread(animBone->frame, sizeof(LOL_Frame), animBone->frame_count, data);
			}
			else
			{
				unsigned int k;
				for(k = 0; k < animBone->frame_count; k++)
				{
					fread(&animBone->frame[k].pos, 4, 3, data);
					fread(&animBone->frame[k].rot, 4, 4, data);
					animBone->frame[k].scale[0] = 
						animBone->frame[k].scale[1] = 
						animBone->frame[k].scale[2] = 1.0f;
				}
			}
		}

		if(animation->bone_count == 0 || animation->fps <= 1)
			animation->duration = 1e3;
		else
			animation->duration = floor(1e3 * (animation->animation_bone[0].frame_count / animation->fps));
	}
}

void delete_LOL_Anim(LOL_Anim *anim)
{
	if(!anim)
		return;
	unsigned int i;
	for(i = 0; i < anim->animation_count; i++)
	{
		LOL_Animation *animation = anim->animation + i;
		free(animation->name);
		unsigned int j;
		for(j = 0; j < animation->bone_count; j++)
		{
			free(animation->animation_bone[j].bone);
			free(animation->animation_bone[j].frame);
		}
		free(animation->animation_bone);
	}
	free(anim->animation);
}

int LOL_InflateZ(FILE *data, FILE* dest)
{
	if(!data || !dest)
		return 0;
	int ret;
	unsigned have;
	z_stream strm;
	unsigned char in[IN_CHUNK];
	unsigned char out[CHUNK];

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = 0;
	strm.next_in = Z_NULL;
	ret = inflateInit2(&strm, 15 + 32); // 2018
	if (ret != Z_OK)
		return ret;
	do
	{
		if(feof(data))
			break;
		strm.avail_in = fread(in, 1, IN_CHUNK, data);
		//strm.avail_in = fread(in,1,CHUNK,source);
		if (0 == strm.avail_in)
			break;
		strm.next_in = in;
		do
		{
			strm.avail_out = CHUNK;
			strm.next_out = out;

			ret = inflate(&strm, Z_NO_FLUSH);
			switch(ret)
			{
				case Z_NEED_DICT:
					ret = Z_DATA_ERROR;
				case Z_DATA_ERROR:
				case Z_MEM_ERROR:
					(void)inflateEnd(&strm);
					return ret;
			}
			have = CHUNK - strm.avail_out;
			if (fwrite(out, 1, have, dest) != have || ferror(dest))
			{
				(void)inflateEnd(&strm);
				return Z_ERRNO;
			}
		}while (strm.avail_out == 0);
	}while(ret != Z_STREAM_END);
	(void)inflateEnd(&strm);
	return ret = Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

