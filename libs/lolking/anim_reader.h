#ifndef KARIN_LOL_ANIM_READER_H
#define KARIN_LOL_ANIM_READER_H

#include "lol_struct.h"

LOL_Anim * new_LOL_Anim(const char *file);
void delete_LOL_Anim(LOL_Anim *anim);

#endif

