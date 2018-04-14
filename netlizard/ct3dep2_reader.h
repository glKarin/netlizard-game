#ifndef KARIN_CT3DEP2_READER_H
#define KARIN_CT3DEP2_READER_H

#include "netlizard_3d.h"
#include "nl_util.h"

NETLizard_3D_Model * nlReadCT3DEp2ModelFile(const char* name, int level);
NETLizard_3D_Model * nlReadCT3DEp2ItemModelFile(const char* name, int index);

#endif

