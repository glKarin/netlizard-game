#include "media_util.h"
#include "netlizard_3d.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char * nlGetLevelMusicFileName(game_name game, int level)
{
	if(!nlCheckLevelIsAvailable(game, level))
		return NULL;
#define GET_MIDI_NAME_BY_LEVEL(str, level, count) \
	{ \
		str = NEW_II(char, 8); \
		memset(str, '\0', sizeof(char) * 8); \
		int l = level % count - 1; \
		if(l == -1) \
		l = count - 1; \
		sprintf(str, "mm%d.mid", l); \
	}

	char *file = NULL;
	switch(game)
	{
		case nl_racing_evolution_3d:
			file = NEW_II(char, 6);
			memset(file, '\0', sizeof(char) * 6);
			int l = level % RE3D_MIDI_COUNT;
			if(l == -1)
				l = RE3D_MIDI_COUNT + 1;
			sprintf(file, "%d.mid", l);
			break;
		case nl_contr_terrorism_3d:
			file = strdup("mm.mid");
			break;
		case nl_army_ranger_3d:
			GET_MIDI_NAME_BY_LEVEL(file, level, SPECNAZ3D_MIDI_COUNT)
				break;
		case nl_contr_terrorism_3d_episode_2:
			GET_MIDI_NAME_BY_LEVEL(file, level, CT3DEP2_MIDI_COUNT)
				break;
		case nl_shadow_of_egypt_3d:
			if(level == 0)
				file = strdup("mm.mid");
			else if(level == 18)
				file = strdup("mm1.mid");
			else
				GET_MIDI_NAME_BY_LEVEL(file, level, EGYPT3D_MIDI_COUNT)
			break;
		case nl_clone_3d:
			GET_MIDI_NAME_BY_LEVEL(file, level, CLONE3D_MIDI_COUNT)
				break;
		case nl_contr_terrorism_3d_episode_3:
			GET_MIDI_NAME_BY_LEVEL(file, level, CT3DEP3_MIDI_COUNT)
				break;
		default:
			break;
	}
	return file;
}

char * nlGetMenuMusicFileName(game_name game)
{
	char *file = NULL;
	switch(game)
	{
		case nl_racing_evolution_3d:
			file = strdup("1.mid");
			break;
		case nl_contr_terrorism_3d:
		case nl_army_ranger_3d:
		case nl_contr_terrorism_3d_episode_2:
		case nl_shadow_of_egypt_3d:
		case nl_clone_3d:
		case nl_contr_terrorism_3d_episode_3:
			file = strdup("mm.mid");
			break;
		default:
			break;
	}
	return file;
}

char * nlGetMenuMusicFilePath(game_name game)
{
	char *file = nlGetMenuMusicFileName(game);
	if(file)
	{
		char *path = game_resource_path[game];
		if(!path)
			return file;
		size_t len = strlen(path) + 1 + strlen(file) + 1;
		char *full = NEW_II(char, len);
		memset(full, '\0', len * sizeof(char));
		sprintf(full, "%s/%s", path, file);
		free(file);
		return full;
	}
	return NULL;
}

char * nlGetLevelMusicFilePath(game_name game, int level)
{
	char *file = nlGetLevelMusicFileName(game, level);
	if(file)
	{
		char *path = game_resource_path[game];
		if(!path)
			return file;
		size_t len = strlen(path) + 1 + strlen(file) + 1;
		char *full = NEW_II(char, len);
		memset(full, '\0', len * sizeof(char));
		sprintf(full, "%s/%s", path, file);
		free(file);
		return full;
	}
	return NULL;
}
