#ifndef KARIN_GAME_MUSIC_H
#define KARIN_GAME_MUSIC_H

int Sound_LoadMenuMusic(int game);
void Sound_PlayMusic(void);
void Sound_StopMusic(void);
void Sound_FreeMusic(void);
int Sound_LoadLevelMusic(int game, int level);

#endif
