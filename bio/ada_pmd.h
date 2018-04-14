#ifndef KARIN_ADA_PMD_H
#define KARIN_ADA_PMD_H

#include "ada_pmd_struct.h"

#include <stdio.h>

void Ada_FreePmd(ADA_pmd *pmd);

int Ada_ReadPmd(ADA_pmd *pmd, FILE *is);
int Ada_ReadPmdFile(ADA_pmd *pmd, const char *file);

#endif
