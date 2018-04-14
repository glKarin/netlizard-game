#include "netlizard_converter.h"

#include "nl_gl.h"

#include "netlizard/texture_v2_reader.h"
#include "netlizard/texture_v3_reader.h"
#include "netlizard/png_reader.h"
#include "netlizard/nl_util.h"
#include "SOIL/SOIL.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void Converter_ImageFree(void);

static char *src_file = NULL;
char *dst_file = NULL;
char *dst_format = NULL;
int compress;

static int game;

void Converter_ImageFree(void)
{
	if(src_file)
		free(src_file);
	if(dst_file)
		free(dst_file);
	if(dst_format)
		free(dst_format);
}

int Converter_DecodeImageFile(const char *g, const char *src, const char *to, const char *format)
{
	if(!src)
		return 0;
	if(!g)
		game = -1;
	else if(strcasecmp(g, "egypt3d") == 0)
		game = nl_shadow_of_egypt_3d;
	else if(strcasecmp(g, "ct3d") == 0)
		game = nl_contr_terrorism_3d;
	else if(strcasecmp(g, "ct3dep2") == 0)
		game = nl_contr_terrorism_3d;
	else if(strcasecmp(g, "specnaz3d") == 0)
		game = nl_contr_terrorism_3d;
	else if(strcasecmp(g, "clone3d") == 0)
		game = nl_clone_3d;
	else if(strcasecmp(g, "ct3dep3") == 0)
		game = nl_contr_terrorism_3d_episode_3;
	else if(strcasecmp(g, "re3d") == 0)
		game = nl_racing_evolution_3d;
	else if(strcasecmp(g, "2d") == 0)
		game = nl_racing_evolution_3d;
	else if(strcasecmp(g, "tex_v2") == 0)
		game = nl_contr_terrorism_3d;
	else if(strcasecmp(g, "tex_v3") == 0)
		game = nl_clone_3d;
	else if(strcasecmp(g, "tex_v3z") == 0)
	{
		game = nl_clone_3d;
		compress = 1;
	}
	else
		game = nl_old_game;
	src_file = strdup(src);
	if(game == nl_racing_evolution_3d || game == nl_2d_game || game == nl_old_game)
		dst_format = strdup("png");
	else
	{
		if(format)
		{
			if(strcasecmp(format, "tga") == 0 
					|| strcasecmp(format, "bmp")
					|| strcasecmp(format, "dds"))
				dst_format = strdup(format);
			else
			{
				fprintf(stderr, "Unsupport output format - %s.\n", format);
				Converter_ImageFree();
				return 0;
			}
		}
		else
			dst_format = strdup("bmp");
	}

	if(to)
		dst_file = strdup(to);
	else
	{
		char *subfix = strstr(src_file, dst_format);
		if(subfix != src_file + strlen(src_file) - strlen(dst_format))
		{
			size_t len = strlen(src_file) + 1 + strlen(dst_format) + 1;
			dst_file = NEW_II(char, len);
			sprintf(dst_file, "%s.%s", src_file, dst_format);
		}
		else
		{
			const char *end = "_nlp_dec_";
			size_t len = strlen(src_file) + strlen(end) + 1;
			dst_file = NEW_II(char, len);
			strncat(dst_file, src_file, subfix - src_file - 1);
			strcat(dst_file, end);
			strcat(dst_file, ".");
			strcat(dst_file, dst_format);
		}
	}
	printfs(dst_file);
	printfs(dst_format);

	int soil_format = SOIL_SAVE_TYPE_BMP;
	if(strcasecmp(dst_format, "dds") == 0)
		soil_format = SOIL_SAVE_TYPE_DDS;
	else if(strcasecmp(dst_format, "tga") == 0)
		soil_format = SOIL_SAVE_TYPE_TGA;
	else if(strcasecmp(dst_format, "bmp") == 0)
		soil_format = SOIL_SAVE_TYPE_BMP;
	else
	{
		if(game != nl_racing_evolution_3d && game && nl_2d_game && game != nl_old_game)
		{
			fprintf(stderr, "Unsupport image file format.\n");
			Converter_ImageFree();
			return 0;
		}
	}
	
	int res = 0;
	NETLizard_Texture_Type type;
	switch(game)
	{
		case nl_shadow_of_egypt_3d:
		case nl_clone_3d:
		case nl_contr_terrorism_3d_episode_3:
			type = compress ? Texture_3DEngineV3Compress_Type : Texture_3DEngineV3_Type;
			break;
		case nl_contr_terrorism_3d:
		case nl_contr_terrorism_3d_episode_2:
		case nl_army_ranger_3d:
			type = Texture_3DEngineV2_Type;
			break;
		case nl_racing_evolution_3d:
		case nl_2d_game:
			type = Texture_EncodePNG_Type;
			break;
		case nl_old_game:
			type = Texture_NormalPNG_Type;
		default:
			type = nlCheckPNGFileType(src_file);
			break;
	}
	if(type == Texture_3DEngineV3_Type)
	{
		if(nlIsNL3DV3TextureFile(src_file))
			printf("The file is NETLizard 3D engine V3 texture image.\n");
		else
			printf("The file is not NETLizard 3D engine V3 texture image.\n");
		res = nlSaveImage_V3File(src_file, -1, dst_file, soil_format);
	}
	else if(type == Texture_3DEngineV3Compress_Type)
	{
		if(nlIsNL3DV3TextureFile(src_file))
			printf("The file is NETLizard 3D engine V3 texture image.\n");
		else
			printf("The file is not NETLizard 3D engine V3 texture image.\n");
		res = nlSaveCompressImage_V3File(src_file, dst_file, soil_format);
	}
	else if(type == Texture_3DEngineV2_Type)
	{
		if(nlIsNL3DV2TextureFile(src_file))
			printf("The file is NETLizard 3D engine V2 texture image.\n");
		else
			printf("The file is not NETLizard 3D engine V2 texture image.\n");
		res = nlSaveImage_V2File(src_file, dst_file, soil_format);
	}
	else if(type == Texture_EncodePNG_Type)
	{
		if(nlIsNLPNGFile(src_file))
			printf("The file is NETLizard normal encode png image.\n");
		else
			printf("The file is not NETLizard normal encode png image.\n");
		res = nlHandlePNG_File2File(src_file, dst_file);
	}
	else
	{
		fprintf(stderr, "Unknow image file.\n");
		res = 0;
	}
	return res;
}

int Converter_EncodeImageFile(const char *g, const char *src, const char *to)
{
	if(!src)
		return 0;
	if(!g)
		return 0;
	if(strcasecmp(g, "egypt3d") == 0)
		game = nl_shadow_of_egypt_3d;
	else if(strcasecmp(g, "ct3d") == 0)
		game = nl_contr_terrorism_3d;
	else if(strcasecmp(g, "ct3dep2") == 0)
		game = nl_contr_terrorism_3d;
	else if(strcasecmp(g, "specnaz3d") == 0)
		game = nl_contr_terrorism_3d;
	else if(strcasecmp(g, "clone3d") == 0)
		game = nl_clone_3d;
	else if(strcasecmp(g, "ct3dep3") == 0)
		game = nl_contr_terrorism_3d_episode_3;
	else if(strcasecmp(g, "re3d") == 0)
		game = nl_racing_evolution_3d;
	else if(strcasecmp(g, "2d") == 0)
		game = nl_racing_evolution_3d;
	else
		return 0;
	src_file = strdup(src);

	const char *format = "png";

	if(to)
		dst_file = strdup(to);
	else
	{
		char *subfix = strstr(src_file, format);
		if(subfix != src_file + strlen(src_file) - strlen(format))
		{
			size_t len = strlen(src_file) + 1 + strlen(format) + 1;
			dst_file = NEW_II(char, len);
			sprintf(dst_file, "%s.%s", src_file, format);
		}
		else
		{
			const char *end = "_nlp_enc_";
			size_t len = strlen(src_file) + strlen(end) + 1;
			dst_file = NEW_II(char, len);
			strncat(dst_file, src_file, subfix - src_file - 1);
			strcat(dst_file, end);
			strcat(dst_file, ".");
			strcat(dst_file, format);
		}
	}
	printfs(dst_file);

	int res = 0;
	NETLizard_Texture_Type type;
	switch(game)
	{
		case nl_shadow_of_egypt_3d:
		case nl_clone_3d:
		case nl_contr_terrorism_3d_episode_3:
			type = Texture_3DEngineV3_Type;
			break;
		case nl_contr_terrorism_3d:
		case nl_contr_terrorism_3d_episode_2:
		case nl_army_ranger_3d:
			type = Texture_3DEngineV2_Type;
			break;
		case nl_racing_evolution_3d:
		case nl_2d_game:
			type = Texture_EncodePNG_Type;
			break;
		case nl_old_game:
			type = Texture_NormalPNG_Type;
		default:
			type = Texture_Unknow_Type;
			break;
	}
	if(type == Texture_3DEngineV3_Type)
	{
		dst_format = strdup("NETLizard 3D engine v3 texture");
		res = nlSaveTextureV3_File(src_file, -1, dst_file);
	}
	else if(type == Texture_3DEngineV2_Type)
	{
		dst_format = strdup("NETLizard 3D engine v2 texture");
		res = nlSaveTextureV2_File(src_file, dst_file);
	}
	else if(type == Texture_EncodePNG_Type)
	{
		dst_format = strdup("NETLizard normal image");
		res = nlHandlePNG_File2File(src_file, dst_file);
	}
	else
	{
		fprintf(stderr, "Unsupport encode file.\n");
		res = 0;
	}
	return res;
}
