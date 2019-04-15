#ifndef KARIN_LOL_MESH_READER_H
#define KARIN_LOL_MESH_READER_H

#include "lol_struct.h"

LOL_Mesh * new_LOL_Mesh(const char *file);
void delete_LOL_Mesh(LOL_Mesh *mesh);
void LOL_MakeGL2Mesh(LOL_Mesh *mesh);

#endif
