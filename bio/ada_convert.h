#ifndef KARIN_ADA_CONVERT_H
#define KARIN_ADA_CONVERT_H

#include "ada_pmd_struct.h"
#include "ada_smd_struct.h"

int Ada_Pmd2Smd(ADA_smd *smd, const ADA_pmd *pmd);
int Ada_Smd2pmd(ADA_pmd *pmd, const ADA_smd *smd);

#endif
