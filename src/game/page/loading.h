#ifndef KARIN_GAME_LOADING_H
#define KARIN_GAME_LOADING_H

void UI_LoadingUpdateProgressFunc(int has_err, int progress, const char *info);
void UI_LoadingRegisterFunction(void);
void Menu_SetLoadingFinishedAction(const char *signal);
void Menu_SetLoadingFailAction(const char *signal);
void Menu_SetLoadingTitle(const char *str);
void Menu_SetLoadingAuto(unsigned b);

#endif
