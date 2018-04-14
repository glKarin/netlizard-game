#include "ada_render.h"

#include <stdlib.h>
#include <string.h>

static void Ada_RenderMaterial(const ADA_GL_Material *material);

void Ada_RenderStaticMaterials(const ADA_GL_Material_List *list)
{
	if(!list)
		return;
	int i;
	for(i = 0; i < list -> material_count; i++)
		Ada_RenderMaterial(list -> materials + i);
}

void Ada_RenderMaterial(const ADA_GL_Material *material)
{
	if(!material)
		return;
	if(!material -> vertex)
		return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	if(glIsTexture(material -> texture))
		glBindTexture(GL_TEXTURE_2D, material -> texture);

	glVertexPointer(3, GL_FLOAT, sizeof(ADA_GL_Vertex), material -> vertex);
	glNormalPointer(GL_FLOAT, sizeof(ADA_GL_Vertex), material -> vertex[0].normal);
	glTexCoordPointer(2, GL_FLOAT, sizeof(ADA_GL_Vertex), material -> vertex[0].texcoord);
	glDrawArrays(GL_TRIANGLES, 0, material -> primitive_count * 3);

	if(glIsTexture(material -> texture))
		glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void arb(const ADA_pmd *pmd)
{
	if(!pmd)
		return;
	glEnableClientState(GL_VERTEX_ARRAY);

	glPushAttrib(GL_POINT_BIT | GL_CURRENT_BIT);
	glDisable(GL_DEPTH_TEST);
	glColor4f(0,0,1,1);
	glPointSize(5);
	ADA_PMD_Bone *bones = calloc(pmd -> bone_list.bone_count, sizeof(ADA_PMD_Bone));
	memcpy(bones, pmd -> bone_list.bones, pmd -> bone_list.bone_count * sizeof(ADA_PMD_Bone));
	int i;
	for(i = 0; i < pmd -> bone_list.bone_count; i++)
	{
		ADA_PMD_Bone *b = bones + i;
		if(b -> parent_bone_id != -1)
		{
			ADA_PMD_Bone *pb = bones + b -> parent_bone_id;
			b -> data[7] += pb -> data[7];
			b -> data[8] += pb -> data[8];
			b -> data[9] += pb -> data[9];
		}
		GLfloat v[3] = {b -> data[7], -b -> data[9], b -> data[8]};
		glVertexPointer(3, GL_FLOAT, 0, v);
		glDrawArrays(GL_POINTS, 0, 1);
	}
	glPopAttrib();
	free(bones);

	glDisableClientState(GL_VERTEX_ARRAY);
}
