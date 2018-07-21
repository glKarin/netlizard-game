#include "nl_gl.h"

#include "netlizard/netlizard.h"
#include "spirit_reader.h"

#include <string.h>
#include <stdlib.h>

GL_NETLizard_Spirit * NETLizard_ReadSpirit(const char *map_file, const char *tex_file)
{
	if(!map_file || !tex_file)
		return NULL;
	array *ns = nlReadSpiritMap(map_file);
	if(!ns)
		return NULL;
	new_netlizard_texture_from_file new_image_texture;
	NETLizard_Texture_Type type = nlCheckPNGFileType(tex_file);
	switch(type)
	{
		case Texture_3DEngineV3Compress_Type:
			new_image_texture = new_texture_from_nl_v3_3d_compress_file;
			break;
		case Texture_3DEngineV3_Type:
			new_image_texture = new_texture_from_nl_v3_3d_file;
			break;
		case Texture_3DEngineV2_Type:
			new_image_texture = new_texture_from_nl_v2_3d_file;
			break;
		case Texture_EncodePNG_Type:
			new_image_texture = new_texture_from_nl_file;
			break;
		case Texture_NormalPNG_Type:
			new_image_texture = new_OpenGL_texture_2d;
			break;
		default:
			new_image_texture = new_OpenGL_texture_2d;
			break;
	}
	texture *tex = new_image_texture(tex_file);
	if(!tex)
	{
		delete_array(ns);
		free(ns);
		return NULL;
	}
	GL_NETLizard_Spirit *s = NEW(GL_NETLizard_Spirit);
	ZERO(s, GL_NETLizard_Spirit);
	s->tex = tex;
	s->spirit_count = ns->length;
	s->spirits = NEW_II(GL_NETLizard_Spirit_Cell, s->spirit_count);
	NETLizard_Spirit *sp = (NETLizard_Spirit *)(ns->array);
	GLuint i;
	for(i = 0; i < s->spirit_count; i++)
	{
		s->spirits[i].width = sp[i].width;
		s->spirits[i].height = sp[i].height;
		s->spirits[i].private_4 = sp[i].private_4;
		s->spirits[i].private_5 = sp[i].private_5;
		GLfloat vertex[] = {
			-s->spirits[i].width / 2, -s->spirits[i].height / 2,
			s->spirits[i].width / 2, -s->spirits[i].height / 2,
			-s->spirits[i].width / 2, s->spirits[i].height / 2,
			s->spirits[i].width / 2, s->spirits[i].height / 2
		};
		GLfloat texcoord[] = {
			(GLfloat)sp[i].x / tex->width, ((GLfloat)sp[i].y + s->spirits[i].height) / tex->height,
			((GLfloat)sp[i].x + s->spirits[i].width) / tex->width, ((GLfloat)sp[i].y + s->spirits[i].height) / tex->height,
			(GLfloat)sp[i].x / tex->width, ((GLfloat)sp[i].y) / tex->height,
			((GLfloat)sp[i].x + s->spirits[i].width) / tex->width, ((GLfloat)sp[i].y)  / tex->height
		};
			s->spirits[i].buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), vertex, GL_STATIC_DRAW);
			s->spirits[i].buffers[texcoord_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), texcoord, GL_STATIC_DRAW);
	}
	delete_array(ns);
	free(ns);
	return s;
}

GLvoid delete_GL_NETLizard_Spirit(GL_NETLizard_Spirit *s)
{
	if(!s)
		return;
	if(s->tex)
	{
		if(glIsTexture(s->tex->texid))
			glDeleteTextures(1, &s->tex->texid);
		free(s->tex);
	}
	if(s->spirits)
	{
		GLuint i;
		for(i = 0; i < s->spirit_count; i++)
		{
			GLuint j;
			for(j = 0; j < total_buffer_type; j++)
			{
				if(glIsBuffer(s->spirits[i].buffers[j]))
					glDeleteBuffers(1, s->spirits[i].buffers + j);
			}
		}
	}
	free(s->spirits);
}

GLvoid NETLizard_RenderSpirit(const GL_NETLizard_Spirit *s, GLuint i)
{
	if(!s)
		return;
	if(i >= s->spirit_count)
		return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	if(s->tex)
		oglBindTexture(GL_TEXTURE_2D, s->tex->texid);
	const GL_NETLizard_Spirit_Cell *c = s->spirits + i;
	glBindBuffer(GL_ARRAY_BUFFER, c->buffers[vertex_buffer_type]);
	glVertexPointer(2, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, c->buffers[texcoord_buffer_type]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glPushMatrix();
	{
		//glTranslatef(0.0, c->y_strip, 0.0);
		oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	glPopMatrix();
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	oglBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
