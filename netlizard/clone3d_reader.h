#ifndef KARIN_CLONE_3D_READER_H
#define KARIN_CLONE_3D_READER_H

#include "netlizard_3d.h"

NETLizard_3D_Model * nlReadClone3DItemModelFile(const char* name, int index);
NETLizard_3D_Model * nlReadClone3DModelFile(const char* name);
NETLizard_3D_Model * nlReadClone3DRoleModelFile(const char* name, int index);

#endif
