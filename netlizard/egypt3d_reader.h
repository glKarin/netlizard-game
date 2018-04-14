#ifndef KARIN_EGYPT_3D_READER_H
#define KARIN_EGYPT_3D_READER_H

#include "netlizard_3d.h"

NETLizard_3D_Model * nlReadEgypt3DItemModelFile(const char* name, int index);
NETLizard_3D_Model * nlReadEgypt3DModelFile(const char* name);
NETLizard_3D_Model * nlReadEgypt3DRoleModelFile(const char* name, int index);

#endif
