#include "radar.h"

#include "nl_std.h"
#include "game_util.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>

radar * new_radar(radar *ra, GLfloat w, GLfloat angle, GLfloat range, GLfloat p, GLfloat cpw, const GLfloat ppc[], const GLfloat epc[], const GLfloat vpc[], GLfloat clw, const GLfloat lc[], const GLfloat bgc[])
{
	RETURN_PTR(r, ra, radar)

	GLfloat r_angle = ator(90.0 - angle / 2.0);
	GLfloat l_angle = ator(90.0 + angle / 2.0);
	GLfloat i;
	GLuint count = 0;
	GLfloat per = p;
	if(per <= 0.0)
		per = 1;
	else if(per > 10.0)
		per = 10.0;
	for(i = 0; i < 360.0; i += p)
		count++;
	GLfloat *vertex = NEW_II(GLfloat, 2 * (count + 1 + 2));
	GLushort *index = NEW_II(GLushort, 1 + count + 1 + 4);
	unsigned int j = 1;
	vertex[0] = 0.0;
	vertex[1] = 0.0;
	i = 0.0;
	for(j = 1; j <= count; j++)
	{
		GLfloat r = ator(Algo_FormatAngle(i));
		vertex[j * 2] = cos(r) * w;
		vertex[j * 2 + 1] = sin(r) * w;
		i += p;
	}
	for(j = 0; j <= count; j++)
		index[j] = j;
	index[count + 1] = 1;
	vertex[2 * (count + 1)] = cos(l_angle) * w;
	vertex[2 * (count + 1) + 1] = sin(l_angle) * w;
	vertex[2 * (count + 1) + 2] = cos(r_angle) * w;
	vertex[2 * (count + 1) + 3] = sin(r_angle) * w;
	index[1 + 1 + count] = 0;
	index[1 + 1 + count + 1] = count + 1;
	index[1 + 1 + count + 2] = 0;
	index[1 + 1 + count + 3] = count + 2;

	r->pos[0] = 0.0;
	r->pos[1] = 0.0;
	r->pos[2] = 0.0;
	r->radius = w;
	r->rotation = 0.0;
	r->line_width = clw;
	r->point_width = cpw;
	COPY_COLOR4(r->line_color, lc);
	COPY_COLOR4(r->parner_point_color, ppc);
	COPY_COLOR4(r->vip_point_color, vpc);
	COPY_COLOR4(r->enemy_point_color, epc);
	COPY_COLOR4(r->bg_color, bgc);
	r->buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * (count + 1 + 2), vertex, GL_STATIC_DRAW);
	r->buffers[index_buffer_type] = new_OpenGL_buffer_object(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * (1 + 1 + count + 4), index, GL_STATIC_DRAW);
	free(vertex);
	free(index);
	r->count = count;
	r->point_pos = NULL;
	r->point_count = 0;
	r->range = range;
	return r;
}

void delete_radar(radar *r)
{
	if(!r)
		return;
	int i;
	for(i = 0; i < total_buffer_type; i++)
	{
		if(glIsBuffer(r->buffers[i]))
		{
			glDeleteBuffers(1, r->buffers + i);
		}
	}
	if(r->point_pos)
		free(r->point_pos);
}

void UI_RenderRadar(const radar *r)
{
	if(!r)
		return;
	glPushMatrix();
	{
		glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT | GL_POINT_BIT);
		{
			glTranslatef(r->pos[0], r->pos[1], r->pos[2]);
			glEnableClientState(GL_VERTEX_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, r->buffers[vertex_buffer_type]);
			glVertexPointer(2, GL_FLOAT, 0, NULL);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->buffers[index_buffer_type]);
			glColor4fv(r->bg_color);
			oglDrawElements(GL_TRIANGLE_FAN, r->count + 2, GL_UNSIGNED_SHORT, NULL);

			oglEnable(GL_POINT_SMOOTH);
			oglEnable(GL_LINE_SMOOTH);
			glColor4fv(r->line_color);
			glLineWidth(r->line_width);
			oglDrawElements(GL_LINES, 4, GL_UNSIGNED_SHORT, (GLushort *)NULL + r->count + 2);

			if(r->point_pos && r->point_count)
			{
				glPointSize(r->point_width);
				float per = r->radius / r->range;
				unsigned int i;
				for(i = 0; i < r->point_count; i++)
				{
					vector2_t v2 = {r->point_pos[i * 4], r->point_pos[i * 4 + 1]};
					float len = Vector2_Mag(&v2);
					if(len > r->range)
						continue;
					float a = 0.0;
					Algo_GetNormalAngle2D(&v2, &a);
					a = ator(Algo_FormatAngle(-(r->rotation - a - 90.0) - 180.0));
					v2.x = cos(a) * len;
					v2.y = sin(a) * len;
					v2 = Vector2_Scale(&v2, per);
					glPushMatrix();
					{
						glTranslatef(v2.x, v2.y, 0.0);
						if(r->point_pos[i * 4 + 3] == 1)
							glColor4fv(r->parner_point_color);
						else if(r->point_pos[i * 4 + 3] == 2)
							glColor4fv(r->enemy_point_color);
						else
							glColor4fv(r->vip_point_color);
						oglDrawElements(GL_POINTS, 1, GL_UNSIGNED_SHORT, NULL);
					}
					glPopMatrix();
				}
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glDisableClientState(GL_VERTEX_ARRAY);
		}
		glPopAttrib();
	}
	glPopMatrix();
}

