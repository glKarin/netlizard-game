#include "game_setting.h"
#include "template/list_template.h"
#include "netlizard/nl_util.h"
#include "nl_std.h"
#include "game_util.h"
#include "weapon.h"
#include "character.h"
#include "local/file_system.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define DEFAULT_SETTING_FILE "karin.setting"

typedef enum _setting_status_type
{
	setting_noload_type = 0,
	setting_isdefault_type,
	setting_loaded_type,
	setting_saved_type
} setting_status_type;

typedef struct _setting_pair
{
	char *name;
	setting_variant value;
} setting_pair;

const setting_item Setting_Items[total_setting] = {
	{open_game_music_setting, boolean_value_type, OPEN_GAME_MUSIC_SETTING, "Open game music", "true", NULL, NULL},
	{open_game_sound_setting, boolean_value_type, OPEN_GAME_SOUND_SETTING, "Open game sound", "true", NULL, NULL},
	{zoom_auto_setting, boolean_value_type, ZOOM_AUTO_SETTING, "Auto zoom", "false", NULL, NULL},
	{open_vkb_setting, boolean_value_type, OPEN_VKB_SETTING, "Open virtual keyboard", "true", NULL, NULL},
	{show_fps_setting, boolean_value_type, SHOW_FPS_SETTING, "Show FPS", "true", NULL, NULL},
	{third_person_view_x_offset_setting, integer_value_type, THIRD_PERSON_VIEW_X_OFFSET_SETTING, "Third person view x offset", "10", "-40", "40"},
	{third_person_view_y_offset_setting, integer_value_type, THIRD_PERSON_VIEW_Y_OFFSET_SETTING, "Third person view y offset", "25", "-50", "50"},
	{third_person_view_distance_setting, integer_value_type, THIRD_PERSON_VIEW_DISTANCE_SETTING, "Third person view distance", "300", "0", "600"},

	{group_count_setting, integer_value_type, GROUP_COUNT_SETTING, "Group count", "2", "2", "4"},
	{character_count_setting, integer_value_type, CHARACTER_COUNT_SETTING, "Character count", "4", "1", "8"},
	{lighting_effect_setting, boolean_value_type, LIGHTING_EFFECT_SETTING, "Lighting effect", "false", NULL, NULL},
	{fog_effect_setting, boolean_value_type, FOG_EFFECT_SETTING, "Fog effect", "false", NULL, NULL},
	{god_mode_setting, boolean_value_type, GOD_MODE_SETTING, "God mode", "false", NULL, NULL},
	{open_radar_setting, boolean_value_type, OPEN_RADAR_SETTING, "Open radar", "false", NULL, NULL},
	{point_target_setting, integer_value_type, POINT_TARGET_SETTING, "Point target", "200", "20", "500"},
	{time_limit_setting, time_value_type, TIME_LIMIT_SETTING, "Time limit", "300", "60", "3600"},

	{use_weapon_setting, integer_value_type, USE_WEAPON_SETTING, "Weapon chooser", "29", "0", "29"},
	{use_character_model_setting, integer_value_type, USE_CHARACTER_MODEL_SETTING, "Character model chooser", "23", "7", "24"}
};

static list_template settings;
static setting_status_type setting_loaded = setting_noload_type;
static char *setting_file = NULL;

static void Setting_Print(unsigned int index, const void *data);
setting_variant Setting_MakeVariant(setting_value_type type, const char *ptr);

static void Setting_LoadDefaultSetting(void);
static void Setting_MakeSettingFile(const char *file);

setting_variant Setting_GetSetting(const char *name)
{
	setting_variant v;
	ZERO(&v, setting_variant);
	v.type = none_value_type;
	if(!name)
		return v;
	if(setting_loaded == setting_noload_type)
		Setting_ReadSetting(NULL);
	unsigned int i;
	for(i = 0; i < settings.count; i++)
	{
		const setting_pair *p = List_GetConstDataByIndexT(&settings, i, setting_pair);
		if(p && p->name)
		{
			if(strcmp(p->name, name) == 0)
			{
				memcpy(&v, &p->value, sizeof(setting_variant));
				break;
			}
		}
	}
	return v;
}

void Setting_ReadSetting(const char *file)
{
	Setting_MakeSettingFile(file);
	Setting_FreeSetting();
	Setting_LoadDefaultSetting();

	array *arr = nlReadFile(setting_file);
	if(arr)
	{
		printf("Read setting file: %s\n", setting_file);
		int show_comment = 0;
		char *data = (char *)(arr->array);
		char ch;
		int i = 0;
		while(i < arr->length)
		{
			while((ch = data[i]) == '\n') i++;
			if(ch == '[')
			{
				i += 1;
				int j = 0;
				while(data[i + j] != ']' && i + j < arr->length)
					j++;
				char *title = NEW_II(char, j + 1);
				memcpy(title, data + i, sizeof(char) * (j + 1));
				title[j] = '\0';
				//printf("[%s]\n", title);
				free(title);
				j++;
				i += j;
				while((ch = data[i]) != '\n') i++;
			}
			else if(ch == '#')
			{
				i += 1;
				while(isspace((ch = data[i]))) i++;
				int j = 0;
				while(data[i + j] != '\n' && i + j < arr->length)
					j++;
				if(show_comment)
				{
					char *str = NEW_II(char, j + 1);
					memcpy(str, data + i, sizeof(char) * (j + 1));
					str[j] = '\0';
					//printf("# %s\n", str);
					free(str);
				}
				j++;
				i += j;
			}
			else
			{
				int j = 0;
				while(data[i + j] != '\n' && i + j < arr->length)
					j++;
				char *str = NEW_II(char, j + 1);
				memcpy(str, data + i, sizeof(char) * (j + 1));
				str[j] = '\0';
				char *ptr = strtok(str, ":");
				if(ptr){
					setting_value_type type;
					if(strcasecmp(ptr, "c") == 0)
						type = character_value_type;
					else if(strcasecmp(ptr, "i") == 0)
						type = integer_value_type;
					else if(strcasecmp(ptr, "s") == 0)
						type = string_value_type;
					else if(strcasecmp(ptr, "b") == 0)
						type = boolean_value_type;
					else if(strcasecmp(ptr, "f") == 0)
						type = float_value_type;
					else if(strcasecmp(ptr, "t") == 0)
						type = time_value_type;
					else
						type = none_value_type;
					char *name = NULL;
					setting_variant v;
					ZERO(&v, setting_variant);
					v.type = type;

					if(type != none_value_type)
					{
						ptr = strtok(NULL, ":");
						if(ptr)
						{
							ptr = strtok(ptr, "=");
							if(ptr)
							{
								name = strdup(ptr);
								ptr = strtok(NULL, "=");
								if(ptr)
								{
									v = Setting_MakeVariant(type, ptr);
								}
							}
						}
					}
					Setting_SetSetting(name, &v);
					free(name);
					if(v.type == string_value_type)
						free(v.value.s);
				}
				free(str);
				j++;
				i += j;
			}
		}
		setting_loaded = setting_loaded_type;
		delete_array(arr);
		free(arr);
	}
	Setting_PrintSetting();
}

void Setting_LoadDefaultSetting(void)
{
	if(setting_loaded != setting_noload_type)
		return;
	new_list_template(&settings, sizeof(setting_pair));
	int i;
	for(i = open_game_music_setting; i < total_setting; i++)
	{
		setting_variant v = Setting_MakeVariant(Setting_Items[i].value_type, Setting_Items[i].default_value);
		setting_pair p;
		p.name = strdup(Setting_Items[i].name);
		p.value = v;
		List_PushBack(&settings, &p);
	}

	setting_loaded = setting_isdefault_type;
}

void Setting_FreeSetting(void)
{
	if(setting_loaded == setting_noload_type)
		return;
	unsigned int i;
	for(i = 0; i < settings.count; i++)
	{
		setting_pair *p = List_GetDataByIndexT(&settings, i, setting_pair);
		if(p)
		{
			free(p->name);
			if(p->value.type == string_value_type)
				free(p->value.value.s);
		}
	}
	List_DeleteAll(&settings);
	setting_loaded = setting_noload_type;
}

void Setting_SetSetting(const char *name, const setting_variant *v)
{
	if(setting_loaded == setting_noload_type)
		return;
	if(!name || !v)
		return;
	if(v->type == none_value_type)
		return;
	unsigned int i;
	for(i = 0; i < settings.count; i++)
	{
		setting_pair *p = List_GetDataByIndexT(&settings, i, setting_pair);
		if(p && p->name)
		{
			if(strcasecmp(p->name, name) == 0)
			{
				if(p->value.type == string_value_type)
					free(p->value.value.s);
				if(v->type == string_value_type)
				{
					p->value.type = v->type;
					p->value.value.s = strdup(v->value.s);
				}
				else
					memcpy(&p->value, v, sizeof(setting_variant));
				return;
			}
		}
	}

	setting_pair n;
	ZERO(&n, setting_pair);
	if(v->type == string_value_type)
	{
		n.value.type = v->type;
		n.value.value.s = strdup(v->value.s);
	}
	else
		memcpy(&n.value, v, sizeof(setting_variant));
	n.name = strdup(name);
	char *ptr = NULL;
	while((ptr = strpbrk(n.name, " :=\n")))
	{
		*ptr = '_';
	}
	List_PushBack(&settings, &n);
}

const char * Setting_GetSettingFile(void)
{
	return setting_file;
}

void Setting_WriteSetting(const char *file)
{
	if(setting_loaded == setting_noload_type)
		return;
	Setting_MakeSettingFile(file);
	FILE *out = fopen(setting_file, "wb");
	if(!out)
		return;
	char head[] = "[karin.config]";
	fwrite(head, sizeof(char), strlen(head), out);
	unsigned int i;
	for(i = 0; i < settings.count; i++)
	{
		setting_pair *p = List_GetDataByIndexT(&settings, i, setting_pair);
		if(p && p->name && p->value.type != none_value_type)
		{
			char ch = 'u';
			switch(p->value.type)
			{
				case integer_value_type:
					ch = 'i';
					break;
				case character_value_type:
					ch = 'c';
					break;
				case boolean_value_type:
					ch = 'b';
					break;
				case float_value_type:
					ch = 'f';
					break;
				case string_value_type:
					ch = 's';
					break;
				case time_value_type:
					ch = 't';
					break;
				default:
					continue;
			}
			char *str = NULL;
			switch(p->value.type)
			{
				case integer_value_type:
					str = itostr(p->value.value.i);
					break;
				case character_value_type:
					str = NEW_II(char, 2);
					str[0] = p->value.value.c;
					str[1] = '\0';
					break;
				case boolean_value_type:
					if(p->value.value.b)
						str = strdup("true");
					else
						str = strdup("false");
					break;
				case float_value_type:
					str = ftostr(p->value.value.f);
					break;
				case string_value_type:
					str = strdup(p->value.value.s);
					break;
				case time_value_type:
					str = lltostr(p->value.value.ll);
					break;
				default:
					continue;
			}
			char ln = '\n';
			fwrite(&ln, sizeof(char), 1, out);
			fwrite(&ch, sizeof(char), 1, out);
			ln = ':';
			fwrite(&ln, sizeof(char), 1, out);
			fwrite(p->name, sizeof(char), strlen(p->name), out);
			ln = '=';
			fwrite(&ln, sizeof(char), 1, out);
			fwrite(str, sizeof(char), strlen(str), out);
			free(str);
		}
	}
	fflush(out);
	fclose(out);
	setting_loaded = setting_saved_type;
}

void Setting_PrintSetting(void)
{
	if(setting_loaded == setting_noload_type)
	{
		fprintf(stderr, "Setting is not load.\n");
	}
	printf(Console_PrintLine("SETTING PROPERTY", '*'));
	List_ForEachConst(&settings, Setting_Print);
	printf(Console_PrintLine(NULL, '*'));
}

void Setting_Print(unsigned int index, const void *data)
{
	if(!data)
		return;
	setting_pair *p = (setting_pair *)data;
	switch(p->value.type)
	{
		case integer_value_type:
			printf("%d : %s = %d\n", index, p->name, p->value.value.i);
			break;
		case character_value_type:
			printf("%d : %s = %c\n", index, p->name, p->value.value.c);
			break;
		case boolean_value_type:
			printf("%d : %s = %s\n", index, p->name, p->value.value.b ? "true" : "false");
			break;
		case float_value_type:
			printf("%d : %s = %f\n", index, p->name, p->value.value.f);
			break;
		case string_value_type:
			printf("%d : %s = %s\n", index, p->name, p->value.value.s);
			break;
		case time_value_type:
			printf("%d : %s = ", index, p->name);
			char *str = lltotime_second(p->value.value.ll);
			printf("%s\n", str);
			free(str);
			break;
		default:
			break;
	}
}

void Setting_SetAndWriteSetting(const char *name, const setting_variant *v)
{
	if(!name || !v)
		return;
	Setting_SetSetting(name, v);
	Setting_WriteSetting(NULL);
}

int Setting_GetSettingInteger(const char *name, int *r)
{
	if(!name || !r)
		return 0;
	setting_variant v = Setting_GetSetting(name);
	if(v.type == integer_value_type)
	{
		*r = v.value.i;
		return 1;
	}
	else
		return 0;
}

int Setting_GetSettingCharacter(const char *name, char *r)
{
	if(!name || !r)
		return 0;
	setting_variant v = Setting_GetSetting(name);
	if(v.type == character_value_type)
	{
		*r = v.value.c;
		return 1;
	}
	else
		return 0;
}

int Setting_GetSettingString(const char *name, char **r)
{
	if(!name || !r)
		return 0;
	setting_variant v = Setting_GetSetting(name);
	if(v.type == string_value_type)
	{
		*r = v.value.s;
		return 1;
	}
	else
		return 0;
}

int Setting_GetSettingBoolean(const char *name, char *r)
{
	if(!name || !r)
		return 0;
	setting_variant v = Setting_GetSetting(name);
	if(v.type == boolean_value_type)
	{
		*r = v.value.b;
		return 1;
	}
	else
		return 0;
}

int Setting_GetSettingFloat(const char *name, float *r)
{
	if(!name || !r)
		return 0;
	setting_variant v = Setting_GetSetting(name);
	if(v.type == float_value_type)
	{
		*r = v.value.f;
		return 1;
	}
	else
		return 0;
}

int Setting_GetSettingTime(const char *name, long long *r)
{
	if(!name || !r)
		return 0;
	setting_variant v = Setting_GetSetting(name);
	if(v.type == time_value_type)
	{
		*r = v.value.ll;
		return 1;
	}
	else
		return 0;
}

int Setting_GetSettingTemplate(const char *name, setting_value_type type, void *r)
{
	if(!name || !r || type == none_value_type)
		return 0;
	switch(type)
	{
		case integer_value_type:
			return Setting_GetSettingInteger(name, (int *)r);
		case character_value_type:
			return Setting_GetSettingCharacter(name, (char *)r);
		case boolean_value_type:
			return Setting_GetSettingBoolean(name, (char *)r);
		case float_value_type:
			return Setting_GetSettingFloat(name, (float *)r);
		case string_value_type:
			return Setting_GetSettingString(name, (char **)r);
		case time_value_type:
			return Setting_GetSettingTime(name, (long long *)r);
		default:
			return 0;
	}
}

setting_variant Setting_MakeVariant(setting_value_type type, const char *ptr)
{
	setting_variant v;
	ZERO(&v, setting_variant);
	v.type = none_value_type;
	if(!ptr || type == none_value_type)
		return v;
	v.type = type;
	switch(type)
	{
		case integer_value_type:
			v.value.i = atoi(ptr);
			break;
		case character_value_type:
			if(strlen(ptr))
				v.value.c = ptr[0];
			break;
		case boolean_value_type:
			if(strcasecmp(ptr, "true") == 0)
				v.value.b = 1;
			else if(strcasecmp(ptr, "false") == 0)
				v.value.b = 0;
			break;
		case float_value_type:
			v.value.f = atof(ptr);
			break;
		case string_value_type:
			v.value.s = strdup(ptr);
			break;
		case time_value_type:
			v.value.ll = atoll(ptr);
			break;
		default:
			break;
	}
	return v;
}

void Setting_SetSettingInteger(const char *name, int r)
{
	if(!name)
		return;
	setting_variant v;
	ZERO(&v, setting_variant);
	v.type = integer_value_type;
	v.value.i = r;
	Setting_SetSetting(name, &v);
}

void Setting_SetSettingCharacter(const char *name, char r)
{
	if(!name)
		return;
	setting_variant v;
	ZERO(&v, setting_variant);
	v.type = character_value_type;
	v.value.c = r;
	Setting_SetSetting(name, &v);
}

void Setting_SetSettingString(const char *name, const char *r)
{
	if(!name || !r)
		return;
	setting_variant v;
	ZERO(&v, setting_variant);
	v.type = string_value_type;
	v.value.s = (char *)r;
	Setting_SetSetting(name, &v);
}

void Setting_SetSettingBoolean(const char *name, char r)
{
	if(!name)
		return;
	setting_variant v;
	ZERO(&v, setting_variant);
	v.type = boolean_value_type;
	v.value.b = r;
	Setting_SetSetting(name, &v);
}

void Setting_SetSettingFloat(const char *name, float r)
{
	if(!name)
		return;
	setting_variant v;
	ZERO(&v, setting_variant);
	v.type = float_value_type;
	v.value.f = r;
	Setting_SetSetting(name, &v);
}

void Setting_SetSettingTime(const char *name, long long r)
{
	if(!name)
		return;
	setting_variant v;
	ZERO(&v, setting_variant);
	v.type = time_value_type;
	v.value.ll = r;
	Setting_SetSetting(name, &v);
}

void Setting_MakeSettingFile(const char *file)
{
	if(file == NULL)
	{
		if(setting_file)
			free(setting_file);
		char *path = System_GetPathFromHome(_KARIN_HOME);
		setting_file = NEW_II(char, strlen(path) + strlen(DEFAULT_SETTING_FILE) + 2);
		sprintf(setting_file, "%s/%s", path, DEFAULT_SETTING_FILE);
		free(path);
	}
	else
	{
		if(setting_file)
		{
			if(strcmp(setting_file, file) != 0)
			{
				free(setting_file);
				setting_file = strdup(file);
			}
		}
		else
			setting_file = strdup(file);
	}
}

void Setting_SetSettingTemplate(const char *name, setting_value_type type, const void *r)
{
	if(!name || !r || type == none_value_type)
		return;
	switch(type)
	{
		case integer_value_type:
			Setting_SetSettingInteger(name, *(int *)r);
			break;
		case character_value_type:
			Setting_SetSettingCharacter(name, *(char *)r);
			break;
		case boolean_value_type:
			Setting_SetSettingBoolean(name, *(char *)r);
			break;
		case float_value_type:
			Setting_SetSettingFloat(name, *(float *)r);
			break;
		case string_value_type:
			Setting_SetSettingString(name, *(char **)r);
			break;
		case time_value_type:
			Setting_SetSettingTime(name, *(long long *)r);
			break;
		default:
			break;
	}
}

