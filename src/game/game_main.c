#include "game_main.h"

#include "game_std.h"
#include "gl_3d_main.h"
#include "netlizard/netlizard_3d.h"
#include "menu.h"
#include "splash.h"
#include "loading.h"
#include "game_viewer.h"
#include "racing_game_viewer.h"
#include "about.h"
#include "game_menu.h"
#include "action_signal_slot.h"
#include "sound/sdlk_sound.h"
#include "game_music.h"
#include "game_setting.h"
#include "setting.h"
#include "keymap_setting.h"
#include "run_setting.h"
#include "game_std.h"
#include "local/file_system.h"
#include "weapon_chooser.h"
#include "character_model_chooser.h"
#include "mdl_viewer.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static game_state game_current_state = game_in_splash_state;

static void MainGame_OpenRunSetting(int game, int level);
static void MainGame_BackToMainMenu(void);
static void MainGame_OpenSetting(void);
static void MainGame_OpenKeyMapSetting(void);
static void MainGame_OpenWeaponChooser(void);
static void MainGame_OpenCharacterModelChooser(void);
static void MainGame_OpenMDLViewer(void);
static void MainGame_OpenAbout(void);
static void MainGame_OpenHelp(void);
static void MainGame_Quit(void);
static void MainGame_PlayMenuMusic(int game);
static void MainGame_PlayLevelMusic(int game, int level);
game_state MainGame_GetGameState(void);
static void MainGame_SetGameState(game_state s);
static void MainGame_WriteSetting(void);
static void MainGame_SaveKeyMap(void);
static void MainGame_OpenMainMenu(void);

void MainGame_Run(void)
{
	Main3D_InitGLK(0, 0, 854, 480, "OpenGL NETLizard 3D Game - karin", 30, 1);

	char *path = System_GetPathFromHome(_KARIN_HOME);
	System_mkdir(path);
	printf("NETLizard Game HOME: %s\n", path);
	free(path);

	nl_debug_mode = 0;
	nlSetResourcePath(nl_clone_3d, CLONE3D_DIR);
	nlSetResourcePath(nl_shadow_of_egypt_3d, EGYPT3D_DIR);
	nlSetResourcePath(nl_contr_terrorism_3d_episode_2, CT3DEP2_DIR);
	nlSetResourcePath(nl_contr_terrorism_3d_episode_3, CT3DEP3_DIR);
	nlSetResourcePath(nl_army_ranger_3d, SPECNAZ3D_DIR);
	nlSetResourcePath(nl_contr_terrorism_3d, CT3D_DIR);
	nlSetResourcePath(nl_racing_evolution_3d, RE3D_DIR);

	SignalSlot_Init();
	SignalSlot_AddAction(OPEN_WEAPON_CHOOSER, MainGame_OpenWeaponChooser);
	SignalSlot_AddAction(OPEN_CHARACTER_MODEL_CHOOSER, MainGame_OpenCharacterModelChooser);
	SignalSlot_AddAction(OPEN_MDL_VIEWER, MainGame_OpenMDLViewer);
	SignalSlot_AddAction(OPEN_KEYMAP_SETTING, MainGame_OpenKeyMapSetting);
	SignalSlot_AddAction(OPEN_SETTING, MainGame_OpenSetting);
	SignalSlot_AddAction(OPEN_RUN_SETTING, MainGame_OpenRunSetting);
	SignalSlot_AddAction(OPEN_ABOUT, MainGame_OpenAbout);
	SignalSlot_AddAction(OPEN_HELP, MainGame_OpenHelp);
	SignalSlot_AddAction(OPEN_MAIN_MENU, MainGame_GoToMainMenu);
	SignalSlot_AddAction(LOAD_GAME, MainGame_RunGameLevel);
	SignalSlot_AddAction(QUIT, MainGame_Quit);
	SignalSlot_AddAction(BACK_MAIN_MENU, MainGame_BackToMainMenu);
	SignalSlot_AddAction(START_GAME, Game_ViewerRegisterFunction);
	SignalSlot_AddAction(START_RACING_GAME, Game_RacingViewerRegisterFunction);
	SignalSlot_AddAction(LOADING_PROGRESS_CALLBACK, UI_LoadingUpdateProgressFunc);
	SignalSlot_AddAction(CLOSE_GAME_MENU, Game_CloseGameMenu);
	SignalSlot_AddAction(OPEN_GAME_MENU, Game_PauseGameAndOpenMenu);
	SignalSlot_AddAction(CONTINUE_GAME, Game_AfterGameMenuClosing);
	SignalSlot_AddAction(PLAY_MENU_MUSIC, MainGame_PlayMenuMusic);
	SignalSlot_AddAction(PLAY_LEVEL_MUSIC, MainGame_PlayLevelMusic);
	SignalSlot_AddAction(GET_GAME_STATE, MainGame_GetGameState);
	SignalSlot_AddAction(SET_GAME_STATE, MainGame_SetGameState);
	SignalSlot_AddAction(REPLAY_GAME, Game_ReplayGame);
	SignalSlot_AddAction(INIT_MAIN_MENU, MainGame_OpenMainMenu);

	Splash_SetSplashImageFile(_SPLASH_FILE);
	Splash_SetSplashShowFinishedAction(INIT_MAIN_MENU);
	UI_SplashRegisterFunction();
	MainGame_SetGameState(game_in_splash_state);

	Setting_ReadSetting(NULL);
	atexit(MainGame_WriteSetting);
	atexit(MainGame_SaveKeyMap);
	SDLK_Init();
	Main3D_MainLoop();
	printf("Exiting...\n");
}

void MainGame_RunGameLevel(int game, int level)
{
	char *g = NULL;
	switch(game)
	{
		case nl_racing_evolution_3d:
			//g = strdup("re3d");
			break;
		case nl_contr_terrorism_3d:
			g = strdup("ct3d");
			break;
		case nl_army_ranger_3d:
			g = strdup("specnaz3d");
			break;
		case nl_contr_terrorism_3d_episode_2:
			g = strdup("ct3dep2");
			break;
		case nl_shadow_of_egypt_3d:
			g = strdup("egypt3d");
			break;
		case nl_clone_3d:
			g = strdup("clone3d");
			break;
		case nl_contr_terrorism_3d_episode_3:
			g = strdup("ct3dep3");
			break;
		default:
			break;
	}
	if(!g)
		return;
	char *lvl = NULL;
	int lv = -1;
	size_t len = strlen(g) + 1 + 3 + 2 + 4 + 1 + strlen(_KARIN_GAME_DIR) + 1;
	lvl = NEW_II(char, len);
	memset(lvl, '\0', sizeof(char) * len);
	if(game == 4)
	{
		lv = level;
		if(level <= 17)
			sprintf(lvl, "%s/%s/lvl%d.png", _KARIN_GAME_DIR, g, lv);
		else
			sprintf(lvl, "%s/%s/%s.png", _KARIN_GAME_DIR, g, "dm1");
	}
	else
	{
		lv = level + 1;
		sprintf(lvl, "%s/%s/lvl%d.png", _KARIN_GAME_DIR, g, lv);
	}
	char *str = NEW_II(char, strlen(Game_Names[game]) + 3 + 2 + 1 + 1 + strlen(Game_Level_Name[game][level]) + 1);
	sprintf(str, "%s - %d. %s", Game_Names[game], lv, Game_Level_Name[game][level]);
	Menu_SetMenuSaveState(menu_init_state);
	UI_LoadingRegisterFunction();
	MainGame_SetGameState(game_in_loading_state);
	Menu_SetLoadingTitle(str);
	Menu_SetLoadingAuto(GL_FALSE);
	Menu_SetLoadingFinishedAction(START_GAME);
	Menu_SetLoadingFailAction(BACK_MAIN_MENU);
	printf("Run Game: %s\n", str);
	free(str);
	if(Game_ViewerInitMain(g, g, lvl, lv))
	{
	}

	free(lvl);
	free(g);
}

void MainGame_GoToMainMenu(void)
{
	UI_LoadingRegisterFunction();
	Menu_SetLoadingTitle("NETLizard 3D Game");
	Menu_SetLoadingAuto(GL_TRUE);
	Menu_SetLoadingFinishedAction(BACK_MAIN_MENU);
	Menu_SetLoadingFailAction(BACK_MAIN_MENU);
	Menu_InitMenu();
	MainGame_SetGameState(game_in_main_menu_state);
}

void MainGame_OpenAbout(void)
{
	const char title[] = "About "_KARIN_APPNAME;
	const char content[] = _KARIN_APPNAME
		" is a util for NETLizard game.\n"
		"It has a game resource parse engine, and a game.\n"
		"Feature:\n"
		"Decode / Encode texture of 2D games and 3D games.\n"
		"Decode game text.\n"
		"View 3D map, item and animation.\n"
		"\n"
		"Now support 3D games:\n"
		"Contr Terrorism 3D\n"
		"Army Rangers 3D : Operation Arctic\n"
		"Contr Terrorism 3D Episode-2\n"
		"Shadows of Egypt 3D\n"
		"Clone 3D\n"
		"Contr Terrorism 3D Episode-3\n"
		"Racing Evolution 3D\n"
		"\n"
		"Player models:\n"
		"NETLizard game model\n"
		"Half-Life model(supply by CSOL)\n"
		"LOL model(supply by LOLKing)\n"
		"\n"
		"NETLizard Game is name of the package, and is also a part of package.\n"
		"Is a simple 3D game like death game, use NETLizard 3D model.\n"
		"\n"
		"\n"
		"Package : "_KARIN_APPBIN"\n"
		"Version : "_KARIN_VERSION"\n"
		"Release : "_KARIN_RELEASE"\n"
		"Code : "_KARIN_DEVCODE"\n"
		"Email : "_KARIN_EMAIL"\n"
		"Developer : "_KARIN_DEVELOPER"\n";
	Menu_SetMenuSaveState(menu_last_state);
	Menu_InitAbout();
	Menu_SetAboutTitleAndContent(title, content);
	UI_AboutRegisterFunction();
	MainGame_SetGameState(game_in_about_state);
}

void MainGame_Quit(void)
{
	Main3D_FreePageStack();
	MainGame_SetGameState(game_in_exiting_state);
	SignalSlot_ClearAction();
	SDLK_Exit();
	Main3D_Shutdown();
}

void MainGame_OpenHelp(void)
{
	const char title[] = "Help";
	const char content[] = "The map file of key is in "_KARIN_RESOURCE_DIR"resource/\n"
		"Default key map is :\n"
		"w - Move forward\n"
		"s - Move backward\n"
		"a - move left\n"
		"d - move right\n"
		"space - jump\n"
		"return - Attack\n"
		"x - Open radar\n"
		"t - Open score table\n"
		"r - Reload\n"
		"f - Open light\n"
		"m - Change view between first person and third person\n"
		"i - Zoom in\n"
		"o - Zoom out\n"
		"j - Operate forward\n"
		"k - Operate backward\n"
		"l - Operate standby\n"
		"y - Previous weapon\n"
		"u - Next weapon\n"
		"v - view center\n"
		"z - Free look\n"
		"up - Turn up\n"
		"down - Turn down\n"
		"left - Turn left\n"
		"right - Turn right\n"
		"p - Free look up\n"
		"' - Free look down\n"
		", - Free look left\n"
		". - Free look right\n"
		"\n";
	Menu_SetMenuSaveState(menu_last_state);
	Menu_InitAbout();
	Menu_SetAboutTitleAndContent(title, content);
	UI_AboutRegisterFunction();
	MainGame_SetGameState(game_in_help_state);
}

void MainGame_PlayMenuMusic(int game)
{
	char b = 0;
	if(!Setting_GetSettingBoolean(OPEN_GAME_MUSIC_SETTING, &b) || b)
	{
		if(Sound_LoadMenuMusic(game))
			Sound_PlayMusic();
	}
}

void MainGame_PlayLevelMusic(int game, int level)
{
	char b = 0;
	if(!Setting_GetSettingBoolean(OPEN_GAME_MUSIC_SETTING, &b) || b)
	{
		if(Sound_LoadLevelMusic(game, level))
			Sound_PlayMusic();
	}
}

void MainGame_OpenSetting(void)
{
	Menu_SetMenuSaveState(menu_last_state);
	Menu_InitSetting();
	UI_SettingRegisterFunction();
	MainGame_SetGameState(game_in_setting_state);
}

game_state MainGame_GetGameState(void)
{
	return game_current_state;
}

void MainGame_SetGameState(game_state s)
{
	game_current_state = s;
}

void MainGame_OpenRunSetting(int game, int level)
{
	if(game == nl_racing_evolution_3d)
	{
		int lv = level + 1;
		char *str = NEW_II(char, strlen(Game_Names[game]) + 3 + 2 + 1 + 1 + strlen(Game_Level_Name[game][level]) + 1);
		sprintf(str, "%s - %d. %s", Game_Names[game], lv, Game_Level_Name[game][level]);
		Menu_SetMenuSaveState(menu_init_state);
		UI_LoadingRegisterFunction();
		MainGame_SetGameState(game_in_loading_state);
		Menu_SetLoadingTitle(str);
		Menu_SetLoadingAuto(GL_FALSE);
		Menu_SetLoadingFinishedAction(START_RACING_GAME);
		Menu_SetLoadingFailAction(BACK_MAIN_MENU);
		printf("Run Game: %s\n", str);
		free(str);
		const char g[] = "re3d";
		if(Game_RacingViewerInitMain(g, g, NULL, lv))
		{
		}

		return;
	}
	/*
	if(game == nl_contr_terrorism_3d_episode_3 && (level == 13 - 1 || level == 15 - 1))
		return;
		*/
	Menu_SetMenuSaveState(menu_last_state);
	Menu_InitRunSetting(game, level);
	UI_RunSettingRegisterFunction();
	MainGame_SetGameState(game_in_prepare_game_state);
}

void MainGame_WriteSetting(void)
{
	printf("Write setting.\n");
	Setting_WriteSetting(NULL);
}

void MainGame_BackToMainMenu(void)
{
	Main3D_PopRenderPage();
}

void MainGame_SaveKeyMap(void)
{
	printf("Write key map.\n");
	Main3D_SsveKeyMap(NULL);
}

void MainGame_OpenKeyMapSetting(void)
{
	//Menu_SetMenuSaveState(menu_last_state);
	Menu_InitKeyMapSetting();
	UI_KeyMapSettingRegisterFunction();
	MainGame_SetGameState(game_in_setting_state);
}

void MainGame_OpenWeaponChooser(void)
{
	Menu_InitWeaponChooser();
	UI_WeaponChooserRegisterFunction();
	MainGame_SetGameState(game_in_setting_state);
}

void MainGame_OpenCharacterModelChooser(void)
{
	Menu_InitCharacterModelChooser();
	UI_CharacterChooserRegisterFunction();
	MainGame_SetGameState(game_in_setting_state);
}

void MainGame_OpenMDLViewer(void)
{
	Menu_InitMDLViewer();
	UI_MDLViewerRegisterFunction();
	MainGame_SetGameState(game_in_setting_state);
}

void MainGame_OpenMainMenu(void)
{
	Menu_InitMenu();
	UI_MainMenuRegisterFunction();
}

