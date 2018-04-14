#ifndef KARIN_SPECNAZ3D_READER_H
#define KARIN_SPECNAZ3D_READER_H

#include "netlizard_3d.h"
#include "nl_util.h"

NETLizard_3D_Model * nlReadSpecnaz3DModelFile(const char* name, int level);
NETLizard_3D_Model * nlReadSpecnaz3DItemModelFile(const char* name, int index);

#endif

