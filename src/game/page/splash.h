#ifndef KARIN_GAME_SPLASH_H
#define KARIN_GAME_SPLASH_H

void UI_SplashRegisterFunction(void);
void Splash_SetSplashImageFile(const char *f);
void Splash_SetSplashShowFinishedAction(const char *signal);
void Splash_SetSplashShowTimeInterval(float out, float in);

#endif
