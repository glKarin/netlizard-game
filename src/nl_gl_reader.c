#include "nl_gl.h"
#include "netlizard/ct3d_reader.h"
#include "netlizard/ct3dep2_reader.h"
#include "netlizard/ct3dep3_reader.h"
#include "netlizard/egypt3d_reader.h"
#include "netlizard/clone3d_reader.h"
#include "netlizard/specnaz3d_reader.h"
 
#include <stdlib.h>

GL_NETLizard_3D_Model * NETLizard_ReadGLCT3DMapModelFile(const char *name, int i)
{
	if(!name)
		return NULL;
	NETLizard_3D_Model *m = nlReadCT3DModelFile(name, i);
	if(!m)
		return NULL;
	GL_NETLizard_3D_Model *model = NETLizard_MakeGL3DModel(m);
	delete_NETLizard_3D_Model(m);
	free(m);
	return model;
}

GL_NETLizard_3D_Model * NETLizard_ReadGLCT3DEp2MapModelFile(const char *name, int i)
{
	if(!name)
		return NULL;
	NETLizard_3D_Model *m = nlReadCT3DEp2ModelFile(name, i);
	if(!m)
		return NULL;
	GL_NETLizard_3D_Model *model = NETLizard_MakeGL3DModel(m);
	delete_NETLizard_3D_Model(m);
	free(m);
	return model;
}

GL_NETLizard_3D_Animation_Model * NETLizard_ReadGLClone3DRoleModelFile(const char *name, int index)
{
	if(!name)
		return NULL;
	NETLizard_3D_Model *m = nlReadClone3DRoleModelFile(name, index);
	if(!m)
		return NULL;
	GL_NETLizard_3D_Animation_Model *model = NETLizard_MakeGL3DAnimationModel(m);
	delete_NETLizard_3D_Model(m);
	free(m);
	return model;
}

GL_NETLizard_3D_Model * NETLizard_ReadGLClone3DItemModelFile(const char *name, int index)
{
	if(!name)
		return NULL;
	NETLizard_3D_Model *m = nlReadClone3DItemModelFile(name, index);
	if(!m)
		return NULL;
	GL_NETLizard_3D_Model *model = NETLizard_MakeGL3DModel(m);
	delete_NETLizard_3D_Model(m);
	free(m);
	return model;
}

GL_NETLizard_3D_Model * NETLizard_ReadGLClone3DMapModelFile(const char *name)
{
	if(!name)
		return NULL;
	NETLizard_3D_Model *m = nlReadClone3DModelFile(name);
	if(!m)
		return NULL;
	GL_NETLizard_3D_Model *model = NETLizard_MakeGL3DModel(m);
	delete_NETLizard_3D_Model(m);
	free(m);
	return model;
}

GL_NETLizard_3D_Animation_Model * NETLizard_ReadGLEgypt3DRoleModelFile(const char *name, int index)
{
	if(!name)
		return NULL;
	NETLizard_3D_Model *m = nlReadEgypt3DRoleModelFile(name, index);
	if(!m)
		return NULL;
	GL_NETLizard_3D_Animation_Model *model = NETLizard_MakeGL3DAnimationModel(m);
	delete_NETLizard_3D_Model(m);
	free(m);
	return model;
}

GL_NETLizard_3D_Model * NETLizard_ReadGLEgypt3DItemModelFile(const char *name, int index)
{
	if(!name)
		return NULL;
	NETLizard_3D_Model *m = nlReadEgypt3DItemModelFile(name, index);
	if(!m)
		return NULL;
	GL_NETLizard_3D_Model *model = NETLizard_MakeGL3DModel(m);
	delete_NETLizard_3D_Model(m);
	free(m);
	return model;
}

GL_NETLizard_3D_Model * NETLizard_ReadGLEgpyt3DMapModelFile(const char *name)
{
	if(!name)
		return NULL;
	NETLizard_3D_Model *m = nlReadEgypt3DModelFile(name);
	if(!m)
		return NULL;
	GL_NETLizard_3D_Model *model = NETLizard_MakeGL3DModel(m);
	delete_NETLizard_3D_Model(m);
	free(m);
	return model;
}

GL_NETLizard_3D_Model * NETLizard_ReadGLCT3DItemModelFile(const char *name, int index)
{
	if(!name)
		return NULL;
	NETLizard_3D_Model *m = nlReadCT3DItemModelFile(name, index);
	if(!m)
		return NULL;
	GL_NETLizard_3D_Model *model = NETLizard_MakeGL3DModel(m);
	delete_NETLizard_3D_Model(m);
	free(m);
	return model;
}

GL_NETLizard_3D_Model * NETLizard_ReadGLCT3DEp2ItemModelFile(const char *name, int index)
{
	if(!name)
		return NULL;
	NETLizard_3D_Model *m = nlReadCT3DEp2ItemModelFile(name, index);
	if(!m)
		return NULL;
	GL_NETLizard_3D_Model *model = NETLizard_MakeGL3DModel(m);
	delete_NETLizard_3D_Model(m);
	free(m);
	return model;
}

GL_NETLizard_3D_Model * NETLizard_ReadGLSpecnaz3DMapModelFile(const char *name, int level)
{
	if(!name)
		return NULL;
	NETLizard_3D_Model *m = nlReadSpecnaz3DModelFile(name, level);
	if(!m)
		return NULL;
	GL_NETLizard_3D_Model *model = NETLizard_MakeGL3DModel(m);
	delete_NETLizard_3D_Model(m);
	free(m);
	return model;
}

GL_NETLizard_3D_Model * NETLizard_ReadGLSpecnaz3DItemModelFile(const char *name, int index)
{
	if(!name)
		return NULL;
	NETLizard_3D_Model *m = nlReadSpecnaz3DItemModelFile(name, index);
	if(!m)
		return NULL;
	GL_NETLizard_3D_Model *model = NETLizard_MakeGL3DModel(m);
	delete_NETLizard_3D_Model(m);
	free(m);
	return model;
}

GL_NETLizard_3D_Model * NETLizard_ReadGLCT3DEp3MapModelFile(const char *name, int i)
{
	if(!name)
		return NULL;
	NETLizard_3D_Model *m = nlReadCT3DEp3ModelFile(name, i);
	if(!m)
		return NULL;
	GL_NETLizard_3D_Model *model = NETLizard_MakeGL3DModel(m);
	if(model)
	{
		int i;
		for(i = 0; i < model->item_count; i++)
		{
			if(model->item_meshes[i].item_type == Item_DoorV_Type)
				model->item_meshes[i].item_type = Item_Tiny_Type;
			// TODO: now no item event support for this game map's door.
		}
	}
	delete_NETLizard_3D_Model(m);
	free(m);
	return model;
}

GL_NETLizard_3D_Model * NETLizard_ReadGLCT3DEp3ItemModelFile(const char *name, int index)
{
	if(!name)
		return NULL;
	NETLizard_3D_Model *m = nlReadCT3DEp3ItemModelFile(name, index);
	if(!m)
		return NULL;
	GL_NETLizard_3D_Model *model = NETLizard_MakeGL3DModel(m);
	delete_NETLizard_3D_Model(m);
	free(m);
	return model;
}

