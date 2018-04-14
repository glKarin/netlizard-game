#include "netlizard_3d.h"
#include "nl_util.h"
#include "texture_v3_reader.h"

#include <stdlib.h>
#include <string.h>

const int Game_Count = nl_total_game;
const char *Game_Names[] = {
	"Racing Evolution 3D",
	"Contr Terrorism 3D",
	"Army Rangers 3D : Operation Arctic",
	"Contr Terrorism 3D Episode 2",
	"Shadows of Egypt 3D",
	"Clone 3D",
	"Contr Terrorism 3D Episode 3"
};
const int Game_Level[] = {
	RE3D_LEVEL, CT3D_LEVEL, SPECNAZ3D_LEVEL, CT3DEP2_LEVEL, EGYPT3D_LEVEL, CLONE3D_LEVEL, CT3DEP3_LEVEL
};

const char *CT3D_Level[] = {
	"Complex",
	"Underground",
	"Yard",
	"Street",
	"Garage",
	"Controls",
	"Station",
	"Office",
	"HeadQuarters",
	"Escape"
};

const char *Specnaz3D_Level[] = {
	"Landing",
	"Gorge",
	"CheckPoint",
	"Passage",
	"Cross-Road",
	"Tower",
	"Storage",
	"Station",
	"Mine",
	"Limit"
};
const char *CT3DEp2_Level[] = {
	"Mine",
	"Yard",
	"Cellar",
	"To The Roof",
	"WareHouse",
	"Office",
	"Street",
	"Prison",
	"Controls"
};
const char *Egypt3D_Level[] = {
	"Shadows of Egypt",
	"Landslide",
	"Spider Lair",
	"Trap",
	"Riddle",
	"Tomb",
	"Lair",
	"Maggot",
	"SkyLine 1",
	"SkyLine 2",
	"Torches",
	"Fight",
	"SkyLine 3",
	"Border",
	"Break-Through",
	"Sanctuary",
	"Highest",
	"Home",
	"Servive"
};
const char *Clone3D_Level[] = {
	"Escape",
	"GreenHouse",
	"Plantation",
	"Mine",
	"Office",
	"Commercial",
	"Commercial 2",
	"Passage",
	"Ventilation",
	"Departament",
	"Exit",
	"Exit"
};
const char *RE3D_Level[] = {
	"Track 1",
	"Track 2",
	"Track 3",
	"Track 4",
	"Track 5",
	"Track 6",
	"Track 7"
};
const char *CT3DEp3_Level[] = {
	"1-Catacombs",
	"2-Collector",
	"3-Cellar",
	"4-Cellar",
	"5-Evacuation",
	"6-Assistance",
	"7-Cruelty",
	"8-Pledge",
	"9-Director",
	"10-Escape",
	"11-Cykl",
	"12-Vault",
	"Level 13",
	"14-Dogma",
	"Level 15"
		/*
			 "1-Катакомбы",
			 "2-Коллектор",
			 "3-Подвал",
			 "4-Погреб",
			 "5-Эвакуация",
			 "6-Содействие",
			 "7-Жестокость",
			 "8-Залог",
			 "9-Директор",
			 "10-Побег",
			 "11-Цыкл",
			 "12-Убежище",
			 "13-",
			 "14-Догма",
			 "15-"
			 */
};

const char **Game_Level_Name[] = {
	RE3D_Level,
	CT3D_Level,
	Specnaz3D_Level,
	CT3DEp2_Level,
	Egypt3D_Level,
	Clone3D_Level,
	CT3DEp3_Level
};

char *game_resource_path[nl_total_game] = 
{
	NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

void delete_NETLizard_3D_Mesh(NETLizard_3D_Mesh *mesh)
{
	if(!mesh)
		return;
	delete_array(mesh -> vertex);
	free(mesh -> vertex);
	delete_array(mesh -> primitive);
	free(mesh -> primitive);
	delete_array(mesh -> plane);
	free(mesh -> plane);
	delete_array(mesh -> bsp);
	free(mesh -> bsp);
}

void delete_NETLizard_3D_Item_Mesh(NETLizard_3D_Item_Mesh *mesh)
{
	if(!mesh)
		return;
	delete_NETLizard_3D_Mesh(&mesh -> item_mesh);
}

void delete_NETLizard_3D_Model(NETLizard_3D_Model *model)
{
	if(!model)
		return;
	int i;
	if(model -> data)
	{
		for(i = 0; i < model -> data -> length; i++)
			delete_NETLizard_3D_Mesh(((NETLizard_3D_Mesh *)(model -> data -> array)) + i);
		delete_array(model -> data);
		free(model -> data);
	}
	if(model -> item_data)
	{
		for(i = 0; i < model -> item_data -> length; i++)
			delete_NETLizard_3D_Item_Mesh(((NETLizard_3D_Item_Mesh *)(model -> item_data -> array)) + i);
		delete_array(model -> item_data);
		free(model -> item_data);
	}
	if(model -> bsp_data)
	{
		delete_array(model -> bsp_data);
		free(model -> bsp_data);
	}
}

NETLizard_Texture_Type nlCheckPNGType(const array *data)
{
	if(!data || !data -> array)
		return Texture_Unknow_Type;
	if(nlIsPNG(data))
		return Texture_NormalPNG_Type;
	else if(nlIsNLPNG(data))
		return Texture_EncodePNG_Type;
	else if(nlIsNL3DV2Texture(data))
		return Texture_3DEngineV2_Type;
	else if(nlIsNL3DV3Texture(data))
	{
		png_texture *t = nlReadTextureV3_Memory(data, -1);
		if(t)
		{
			array *arr = t -> color_index;
			NETLizard_Texture_Type type = Texture_3DEngineV3_Type;
			int i;
			for(i = 0; i < arr -> length; i++)
			{
				if(((signed char*)(arr -> array))[i] < 0)
				{
					type = Texture_3DEngineV3Compress_Type;
					break;
				}
			}
			delete_png_texture(t);
			free(t);
			return type;
		}
		else
		{
			return Texture_Unknow_Type;
		}
	}
	else
		return Texture_Unknow_Type;
}

NETLizard_Texture_Type nlCheckPNGFileType(const char *name)
{
	if(!name)
		return Texture_Unknow_Type;
	array *arr = nlReadFile(name);
	if(!arr)
		return Texture_Unknow_Type;
	NETLizard_Texture_Type type = nlCheckPNGType(arr);
	delete_array(arr);
	free(arr);
	return type;
}

const char *nlGetAnimationName(NETLizard_3D_Animation_Type anim)
{
	if(anim >= Animation_Total_Type)
		return NULL;
	static const char *names[Animation_Total_Type] = {
		"Idel Animation",
		"Walk Animation",
		"Run Animation",
		"Fighting-1 Animation",
		"Fighting-2 Animation",
		"Attack-1 Animation",
		"Attack-2 Animation",
		"Dead-1 Animation",
		"Dead-2 Animation"
	};
	return names[anim];
}


int nlGetAnimationBeginAndEnd(game_name game, int index, int animation[])
{
	const int anim[2][8][Animation_Total_Type * 2] = {
		{
			{
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			}, // unused
			{
				0, 0, -1, -1, 1, 7, 8, 11, -1, -1, 8, 11, -1, -1, 12, 13, -1, -1
			}, // 1
			{
				0, 0, -1, -1, 1, 7, 8, 10, -1, -1, 8, 10, -1, -1, 12, 13, -1, -1
			}, // 2
			{
				0, 0, -1, -1, 0, 0, 1, 5, -1, -1, 1, 5, -1, -1, 6, 6, -1, -1
			}, // 3
			{
				2, 2, -1, -1, 0, 8, 0, 8, -1, -1, 0, 8, -1, -1, 2, 2, -1, -1
			}, // 4
			{
				0, 0, -1, -1, 1, 9, 10, 14, -1, -1, 10, 14, -1, -1, 14, 17, 14, 20
			}, // 5
			{
				0, 0, -1, -1, 1, 7, 8, 13, -1, -1, 8, 13, -1, -1, 14, 17, -1, -1
			}, // 6
			{
				0, 8, -1, -1, 0, 8, 8, 18, -1, -1, 18, 26, -1, -1, 12, 12, 17, 17
			} // 7
		}, // egypt 3d 7
		{
			{
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			}, // unused
			{
				26, 26, 27, 35, 36, 42, 1, 7, 9, 15, 0, 0, 8, 8, 16, 20, 21, 25
			}, // 1
			{
				0, 0, -1, -1, 1, 9, 10, 19, 20, 29, 10, 10, 20, 20, 30, 34, -1, -1
			}, // 2
			{
				0, 0, -1, -1, 1, 9, 10, 11, -1, -1, 10, 11, -1, -1, 0, 0, -1, -1
			}, // 3
			{
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 3, -1, -1
			}, // 4
			{
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			}, // unused
			{
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			}, // unused
			{
				-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			} // unused
		} // clone 3d 4
	};

	const int anim_count[2][8] = {
		{0, 5, 5, 5, 5, 6, 5, 6}, // egypt 3d 7
		{0, 9, 7, 5, 1, 0, 0, 0}, // clone 3d 4
	};
	if(game == nl_shadow_of_egypt_3d)
	{
		if(animation)
			memcpy(animation, anim[0][index], sizeof(int) * Animation_Total_Type * 2);
		return anim_count[0][index];
	}
	else if(game == nl_clone_3d)
	{
		if(animation)
			memcpy(animation, anim[1][index], sizeof(int) * Animation_Total_Type * 2);
		return anim_count[1][index];
	}
	return -1;
}

int nlGetItemType(game_name game, int index)
{
	switch(game)
	{
		case nl_clone_3d:
			if(index == 3 || index == 4 || index == 5 || index == 6)
				return Item_DoorV_Type;
			else if(index == 34 || index == 35 || index == 36 || index == 37)
				return Item_DoorH_Type;
			else if(index == 52 || index == 53 || index == 54 || index == 55)
				return Item_Weapon_Type;
			else if(index == 38 || index == 39)
				return Item_Ladder_Type;
			else if(index == 40 || index == 41 || index == 42 || index == 43)
				return Item_Elevator_Type;
			else if(index == 19 || index == 20)
				return Item_DoorV_Type;
			else if(index == 29)
				return Item_FanH_Type;
			else if(index == 31) // 机枪
				return Item_FanV_Type;
			else if(index == 32 || index == 33)
				return Item_DoorH_Type;
			else if(index == 26)
				return Item_Switcher_Type;
			break;

		case nl_shadow_of_egypt_3d:
			if(index == 20 || index == 21)
				return Item_DoorV_Type;
			if(index == 5 || index == 6)
				return Item_Skyline_Type;
			else if(index == 24 || index == 25 || index == 26 || index == 27 || index == 28 || index == 29)
				return Item_Weapon_Type | Item_FanV_Type;
			else if(index == 33 || index == 34 || index == 35 || index == 36)
				return Item_Box_Type;
			else if(index == 14)
				return Item_FanV_Type | Item_Portal_Type;
			else if(index == 8)
				return Item_FanV_Type;
			break;

		case nl_contr_terrorism_3d:
			if(index == 52 || index == 53 || index == 54 || index == 55)
				return Item_DoorV_Type;
			else if(index == 16 || index == 21 || index == 26)
				return Item_FanV_Type;
			else if(index == 23)
				return Item_FanH_Type;
			else if(index == 17)
				return Item_Other_Type;
			break;

		case nl_contr_terrorism_3d_episode_2:
			if(index == 1 || index == 2 || index == 3 || index == 4 || index == 5 || index == 6 || index == 7)
				return Item_Weapon_Type;
			else if(index == 38 || index == 39 || index == 40 || index == 41)
				return Item_DoorV_Type;
			else if(index == 43)
				return Item_Ladder_Type;
			else if(index == 12 || index == 15)
				return Item_FanV_Type;
			else if(index == 13)
				return Item_FanH_Type;
			break;

		case nl_army_ranger_3d:
			if(index == 1 || index == 2 || index == 3 || index == 4 || index == 5)
				return Item_Weapon_Type | Item_FanV_Type;
			else if(index == 6 || index == 7 || index == 8 || index == 9 || index == 10 || index == 11)
				return Item_Tiny_Type | Item_FanV_Type;
			else if(index == 40 || index == 41 || index == 42 || index == 43)
				return Item_DoorV_Type;
			else if(index == 34 || index == 49)
				return Item_FanV_Type;
			else if(index == 35)
				return Item_FanH_Type;
			break;

		case nl_contr_terrorism_3d_episode_3:
			if(index == 1 || index == 2 || index == 3 || index == 4 || index == 5 || index == 6 || index == 7)
				return Item_Weapon_Type;
			else if(index == 38 || index == 39 || index == 40 || index == 41)
				return Item_DoorV_Type;
			else if(index == 12 || index == 15)
				return Item_FanV_Type;
			else if(index == 13)
				return Item_FanH_Type;
			else if(index == 43)
				return Item_Ladder_Type;
			break;

		default:
			break;
	}
	return Item_Other_Type;
}

void nlSetResourcePath(game_name name, const char *path)
{
	if(!path)
	{
		free(game_resource_path[name]);
		return;
	}
	if(name >= nl_total_game)
		return;
	char *new_path = strdup(path);
	free(game_resource_path[name]);
	game_resource_path[name] = new_path;
}

int nlCheckLevelIsAvailable(game_name game, int level)
{
	switch(game)
	{
		case nl_racing_evolution_3d:
		case nl_contr_terrorism_3d:
		case nl_army_ranger_3d:
		case nl_contr_terrorism_3d_episode_2:
		case nl_clone_3d:
		case nl_contr_terrorism_3d_episode_3:
			return(level >= 1 && level <= Game_Level[game] ? 1 : 0);
		case nl_shadow_of_egypt_3d:
			return(level >= 0 && level < EGYPT3D_LEVEL ? 1 : 0);
			break;
		default:
			break;
	}
	return 0;
}
