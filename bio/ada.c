#include "ada.h"

#include <string.h>
#include <stdlib.h>

int Ada_LoadPmdModel(ADA_GL_Model *model, const char *files[], int len, const char *path)
{
	if(!model || !files)
		return 0;
	const char **end;
	if(len < 0)
		end = NULL;
	else
		end = files + len + 1;
	ADA_pmd *pmds = NULL;
	unsigned int count = 0;
	const char **p = files;
	while(p != end && *p != NULL)
	{
		ADA_pmd pmd;
		memset(&pmd, 0, sizeof(ADA_pmd));
		int b = Ada_ReadPmdFile(&pmd, *p);
		if(b)
		{
			if(pmds)
			{
				ADA_pmd *tp = calloc(count + 1, sizeof(ADA_pmd));
				memcpy(tp, pmds, sizeof(ADA_pmd) * count);
				tp[count] = pmd;
				count++;
				free(pmds);
				pmds = tp;
			}
			else
			{
				pmds = calloc(1, sizeof(ADA_pmd));
				pmds[0] = pmd;
				count++;
			}
		}
		p++;
	}
	if(!pmds)
		return 0;
	model -> model_count = count;
	model -> models = calloc(model -> model_count, sizeof(ADA_GL_Material_List));
	int i;
	for(i = 0; i < model -> model_count; i++)
	{
		Ada_MakeGLPmd(model -> models + i, pmds + i, path);
		Ada_FreePmd(pmds + i);
	}
	free(pmds);
	return 1;
}

void Ada_RenderStaticModel(const ADA_GL_Model *model)
{
	if(!model)
		return;
	int i;
	for(i = 0; i < model -> model_count; i++)
		Ada_RenderStaticMaterials(model -> models + i);
}
