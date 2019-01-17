#ifndef KARIN_NETLIZARD_VIEWER_H
#define KARIN_NETLIZARD_VIEWER_H

#include "opengl.h"

void Viewer_NETLizard3DAnimationRegisterFunction(void);
int Viewer_NETLizard3DAnimationInitMain(const char *game, const char *dir, const char *src, unsigned int lvl, int anim);

void Viewer_NETLizard3DMapRegisterFunction(void);
int Viewer_NETLizard3DMapInitMain(const char *game, const char *dir, const char *src, unsigned int lvl);

void Viewer_NETLizard3DItemRegisterFunction(void);
int Viewer_NETLizard3DItemInitMain(const char *game, const char *dir, const char *src, unsigned int lvl);

void Viewer_RE3DRegisterFunction(void);
int Viewer_RE3DInitMain(const char *game, const char *m, const char *dir, const char *src, unsigned int lvl);

void Viewer_NETLizardImageRegisterFunction(void);
int Viewer_NETLizardImageInitMain(const char *game, const char *src);

void Viewer_Init3DFunc(void);

#endif
