#ifndef KARIN_GAME_MAP_VIEWER_H
#define KARIN_GAME_MAP_VIEWER_H

typedef void (* MapViewerEnterAction_f)(int game, int level);

void UI_MapViewerRegisterFunction(void);
void UI_InitMapViewer(void);
void UI_SetMapViewerEnterActionFunction(MapViewerEnterAction_f f);

#endif
