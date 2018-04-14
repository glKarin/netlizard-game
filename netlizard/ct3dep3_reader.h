#ifndef KARIN_CT3DEP3_READER_H
#define KARIN_CT3DEP3_READER_H

#include "netlizard_3d.h"
#include "nl_util.h"

NETLizard_3D_Model * nlReadCT3DEp3ModelFile(const char* name, int level);
NETLizard_3D_Model * nlReadCT3DEp3ItemModelFile(const char* name, int index);

#endif
