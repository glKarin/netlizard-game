#ifndef KARIN_CAITLYN_SKN_READER_H
#define	KARIN_CAITLYN_SKN_READER_H

#include "caitlyn.h"

Caitlyn_Skn_Model * caitlynReadSknModel(const char *file);
void free_Caitlyn_Skn_model(Caitlyn_Skn_Model *headerPtr);

#endif
