#ifndef KARIN_GAME_VIEWER_H
#define KARIN_GAME_VIEWER_H

void Game_ViewerRegisterFunction(void);
int Game_ViewerInitMain(const char *game, const char *dir, const char *src, unsigned int lvl);
void Game_AfterGameMenuClosing(void);
void Game_ReplayGame(void);
void Game_CloseGameMenu(void);
void Game_PauseGameAndOpenMenu(void);

#endif
