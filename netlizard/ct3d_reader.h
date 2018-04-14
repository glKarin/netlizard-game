#ifndef KARIN_CT3D_READER_H
#define KARIN_CT3D_READER_H

#include "netlizard_3d.h"
#include "nl_util.h"

NETLizard_3D_Model * nlReadCT3DModelFile(const char* name, int level);
NETLizard_3D_Model * nlReadCT3DItemModelFile(const char* name, int index);

#endif
