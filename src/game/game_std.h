#ifndef KARIN_GAME_STD_H
#define KARIN_GAME_STD_H

#define OPEN_SETTING "open_setting"
#define OPEN_WEAPON_CHOOSER "open_weapon_chooser"
#define OPEN_CHARACTER_MODEL_CHOOSER "open_character_model_chooser"
#define OPEN_MDL_VIEWER "open_mdl_viewer"
#define OPEN_KEYMAP_SETTING "open_keymap_setting"
#define OPEN_ABOUT "open_about"
#define OPEN_MAIN_MENU "open_main_menu"
#define OPEN_HELP "open_help"
#define QUIT "quit"
#define LOAD_GAME "load_game"
#define START_GAME "start_game"
#define START_RACING_GAME "start_racing_game"
#define BACK_MAIN_MENU "back_menu"
#define LOADING_PROGRESS_CALLBACK "loading_progress_callback"
#define CLOSE_GAME_MENU "close_game_menu"
#define OPEN_GAME_MENU "open_game_menu"
#define CONTINUE_GAME "continue_game"
#define PLAY_MENU_MUSIC "play_game_music"
#define PLAY_LEVEL_MUSIC "play_level_music"
#define GET_GAME_STATE "get_game_state"
#define SET_GAME_STATE "set_game_state"
#define OPEN_RUN_SETTING "open_game_setting"
#define REPLAY_GAME "replay_game"
#define OPEN_MAP_VIEWER "open_map_viewer"
#define INIT_MAIN_MENU "init_main_menu"

#ifndef _SPLASH_FILE
#define _SPLASH_FILE _KARIN_RESOURCE_DIR"resource/lz.png"
#endif

#define CT3D_DIR _KARIN_GAME_DIR"ct3d"
#define CT3DEP2_DIR _KARIN_GAME_DIR"ct3dep2"
#define CT3DEP3_DIR _KARIN_GAME_DIR"ct3dep3"
#define SPECNAZ3D_DIR _KARIN_GAME_DIR"specnaz3d"
#define EGYPT3D_DIR _KARIN_GAME_DIR"egypt3d"
#define CLONE3D_DIR _KARIN_GAME_DIR"clone3d"
#define RE3D_DIR _KARIN_GAME_DIR"re3d"

typedef void (*void__func__void)(void);
typedef void (*void__func__int_int)(int, int);
typedef void (*void__func__int)(int);
typedef void (*void__func__int_int_constcharptr)(int, int, const char *);

typedef enum _game_state
{
	game_in_splash_state = 0,
	game_in_loading_state,
	game_in_main_menu_state,
	game_in_about_state,
	game_in_help_state,
	game_in_setting_state,
	game_in_prepare_game_state,
	game_in_game_state,
	game_in_game_menu_state,
	game_in_over_state,
	game_in_exiting_state
} game_state;

typedef enum _menu_save_state
{
	menu_init_state = 0,
	menu_last_state
} menu_save_state;

#endif
