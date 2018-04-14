#ifndef KARIN_GAME_LOADING_H
#define KARIN_GAME_LOADING_H

#include "opengl.h"

void Menu_LoadingUpdateProgressFunc(int has_err, int progress, const char *info);
void Menu_RegisterLoadingFunction(void);
void Menu_SetLoadingFinishedAction(const char *signal);
void Menu_SetLoadingFailAction(const char *signal);
void Menu_SetLoadingTitle(const char *str);
void Menu_SetLoadingAuto(GLboolean b);

#endif
