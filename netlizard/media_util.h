#ifndef KARIN_MEDIA_UTIL_H
#define KARIN_MEDIA_UTIL_H

#include "netlizard.h"

#define RE3D_MIDI_COUNT 4
#define CT3D_MIDI_COUNT 0
#define EGYPT3D_MIDI_COUNT 6
#define CLONE3D_MIDI_COUNT 3
#define CT3DEP2_MIDI_COUNT 5
#define CT3DEP3_MIDI_COUNT 5
#define SPECNAZ3D_MIDI_COUNT 5

char * nlGetMenuMusicFileName(game_name game);
char * nlGetLevelMusicFileName(game_name game, int level);
char * nlGetMenuMusicFilePath(game_name game);
char * nlGetLevelMusicFilePath(game_name game, int level);

#endif
