#ifndef KARIN_GAME_SETTING_H
#define KARIN_GAME_SETTING_H

// global setting
#define OPEN_GAME_MUSIC_SETTING "open_game_music"
#define OPEN_GAME_SOUND_SETTING "open_game_sound"
#define ZOOM_AUTO_SETTING "zoom_auto"
#define OPEN_VKB_SETTING "open_virtual_kb"
#define SHOW_FPS_SETTING "show_fps"

#define THIRD_PERSON_VIEW_CROSSHAIR_SETTING "third_person_view_crosshair_setting"
#define THIRD_PERSON_VIEW_X_OFFSET_SETTING "third_person_view_x_offset"
#define THIRD_PERSON_VIEW_Y_OFFSET_SETTING "third_person_view_y_offset"
#define THIRD_PERSON_VIEW_DISTANCE_SETTING "third_person_view_distance"

// run game attributes
#define GROUP_COUNT_SETTING "group_count"
#define CHARACTER_COUNT_SETTING "character_count"
#define GOD_MODE_SETTING "god_mode"
#define GANE_TINE_SETTING "game_time"
#define OPEN_RADAR_SETTING "open_radar"
#define POINT_TARGET_SETTING "point_target"
#define TIME_LIMIT_SETTING "time_limit"
#define FOG_EFFECT_SETTING "fog_effect"
#define LIGHTING_EFFECT_SETTING "lighting_effect"

// special
#define USE_WEAPON_SETTING "use_weapon"
#define USE_CHARACTER_MODEL_SETTING "use_character_model"

typedef enum _setting_value_type
{
	none_value_type = 0,
	integer_value_type,
	boolean_value_type,
	float_value_type,
	character_value_type,
	string_value_type,
	time_value_type
} setting_value_type;

typedef enum _setting_item_type
{
	open_game_music_setting = 0,
	open_game_sound_setting,
	zoom_auto_setting,
	open_vkb_setting,
	show_fps_setting,
	third_person_view_crosshair_setting,
	third_person_view_x_offset_setting,
	third_person_view_y_offset_setting,
	third_person_view_distance_setting,

	group_count_setting,
	character_count_setting,
	lighting_effect_setting,
	fog_effect_setting,
	god_mode_setting,
	open_radar_setting,
	point_target_setting,
	time_limit_setting,

	use_weapon_setting,
	use_character_model_setting,

	total_setting
} setting_item_type;

typedef struct _setting_item
{
	setting_item_type type;
	setting_value_type value_type;
	char *name;
	char *description;
	char *default_value;
	char *min;
	char *max;
} setting_item;

typedef struct _setting_variant
{
	setting_value_type type;
	union
	{
		int i;
		char b;
		float f;
		char *s;
		char c;
		long long ll;
	} value;
} setting_variant;

extern const setting_item Setting_Items[total_setting];

setting_variant Setting_GetSetting(const char *name);
void Setting_SetSetting(const char *name, const setting_variant *v);
void Setting_ReadSetting(const char *file);
void Setting_WriteSetting(const char *file);
void Setting_SetAndWriteSetting(const char *name, const setting_variant *v);
const char * Setting_GetSettingFile(void);
void Setting_PrintSetting(void);
void Setting_FreeSetting(void);

int Setting_GetSettingInteger(const char *name, int *r);
int Setting_GetSettingCharacter(const char *name, char *r);
int Setting_GetSettingString(const char *name, char **r);
int Setting_GetSettingBoolean(const char *name, char *r);
int Setting_GetSettingFloat(const char *name, float *r);
int Setting_GetSettingTime(const char *name, long long *r);
int Setting_GetSettingTemplate(const char *name, setting_value_type type, void *r);

void Setting_SetSettingInteger(const char *name, int r);
void Setting_SetSettingCharacter(const char *name, char r);
void Setting_SetSettingString(const char *name, const char *r);
void Setting_SetSettingBoolean(const char *name, char r);
void Setting_SetSettingFloat(const char *name, float r);
void Setting_SetSettingTime(const char *name, long long time);
void Setting_SetSettingTemplate(const char *name, setting_value_type type, const void *r);

#endif
