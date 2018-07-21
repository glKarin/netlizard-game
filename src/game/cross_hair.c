#include "cross_hair.h"

#include "nl_std.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>

cross_hair * new_optical_sight_cross_hair(cross_hair *cross, GLfloat w, GLfloat p, GLfloat cpw, const GLfloat pc[], GLfloat clw, const GLfloat lc[])
{
	RETURN_PTR(c, cross, cross_hair)

		c->optical.type = optical_type;
	GLfloat i;
	GLuint count = 0;
	GLfloat per = p;
	if(per <= 0.0)
		per = 1;
	else if(per > 10.0)
		per = 10.0;
	for(i = 0; i < 360.0; i += p)
		count++;
	GLfloat *vertex = NEW_II(GLfloat, 2 * (count + 1 + 4));
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
	vertex[2 * (count + 1)] = 0;
	vertex[2 * (count + 1) + 1] = w / 2;
	vertex[2 * (count + 1) + 2] = 0;
	vertex[2 * (count + 1) + 3] = -w / 2;
	vertex[2 * (count + 1) + 4] = -w / 2;
	vertex[2 * (count + 1) + 5] = 0;
	vertex[2 * (count + 1) + 6] = w / 2;
	vertex[2 * (count + 1) + 7] = 0;
	index[1 + 1 + count] = count + 1;
	index[1 + 1 + count + 1] = count + 2;
	index[1 + 1 + count + 2] = count + 3;
	index[1 + 1 + count + 3] = count + 4;

	c->optical.pos[0] = 0.0;
	c->optical.pos[1] = 0.0;
	c->optical.pos[2] = 0.0;
	c->optical.radius = w;
	c->optical.front_sight_line_width = clw;
	c->optical.front_sight_point_width = cpw;
	COPY_COLOR4(c->optical.front_sight_line_color, lc);
	COPY_COLOR4(c->optical.front_sight_point_color, pc);
	c->optical.buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * (count + 1 + 4), vertex, GL_STATIC_DRAW);
	c->optical.buffers[index_buffer_type] = new_OpenGL_buffer_object(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * (1 + 1 + count + 4), index, GL_STATIC_DRAW);
	free(vertex);
	free(index);
	c->optical.count = count;
	return c;
}

cross_hair * new_normal_cross_hair(cross_hair *cross, cross_hair_type type, const GLfloat color[], GLfloat step, GLfloat width, GLfloat height)
{
	if(type == ray_type)
		return NULL;

	RETURN_PTR(c, cross, cross_hair)
	c->normal.type = type;
	COPY_COLOR4(c->normal.color, color);
	c->normal.step = step;
	c->normal.width = width;
	c->normal.height = height;
	c->normal.scale = 0.0;
	c->normal.pos[0] = 0.0;
	c->normal.pos[1] = 0.0;
	c->normal.pos[2] = 0.0;
	return c;
}

cross_hair * new_ray_cross_hair(cross_hair *cross, cross_hair_type type, const GLfloat color[], GLfloat line_width, GLfloat point_min_width, GLfloat point_max_width)
{
	if(type != ray_type)
		return NULL;
	RETURN_PTR(c, cross, cross_hair)
	
		c->ray.type = type;
	COPY_COLOR4(c->ray.color, color);
	c->ray.line_width = line_width;
	c->ray.point_min_width = point_min_width;
	c->ray.point_max_width = point_max_width;
	c->ray.start_pos[0] = 0.0;
	c->ray.start_pos[1] = 0.0;
	c->ray.start_pos[2] = 0.0;
	c->ray.target_pos[0] = 0.0;
	c->ray.target_pos[1] = 0.0;
	c->ray.target_pos[2] = 0.0;
	return c;
}

void UI_RenderOpticalSightCrossHair(const optical_sight_cross_hair *c, sight_part p)
{
	if(!c)
		return;
	glPushMatrix();
	{
		glTranslatef(c->pos[0], c->pos[1], c->pos[2]);
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, c->buffers[vertex_buffer_type]);
		glVertexPointer(2, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c->buffers[index_buffer_type]);
		if(p == sight_optical)
			oglDrawElements(GL_TRIANGLE_FAN, c->count + 2, GL_UNSIGNED_SHORT, NULL);
		else
		{
			glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT | GL_POINT_BIT);
			{
				glColor4fv(c->front_sight_line_color);
				glLineWidth(c->front_sight_line_width);
				glPushMatrix();
				{
					glTranslatef(-c->front_sight_line_width / 2, 0.0, 0.0);
					oglDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, (GLushort *)NULL + c->count + 2);
					glTranslatef(0.0, -c->front_sight_line_width / 2, 0.0);
					oglDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, (GLushort *)NULL + c->count + 4);
				}
				glPopMatrix();

				oglEnable(GL_POINT_SMOOTH);
				glColor4fv(c->front_sight_point_color);
				glPointSize(c->front_sight_point_width);
					//glTranslatef(-c->front_sight_point_width / 2, -c->front_sight_point_width / 2, 0.0);
					oglDrawElements(GL_POINTS, 1, GL_UNSIGNED_SHORT, NULL);
				glPopMatrix();
			}
			glPopAttrib();
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	glPopMatrix();
}

void UI_RenderNormalCrossHair(const normal_cross_hair *c)
{
	if(!c)
		return;
	glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT | GL_POINT_BIT | GL_DEPTH_BUFFER_BIT);
	{
		oglDisable(GL_DEPTH_TEST);
		glTranslatef(c->pos[0], c->pos[1], c->pos[2]);
		if(c->type == point_type)
		{
			glPointSize(c->width);
		}
		else
		{
			glLineWidth(c->width);
		}

		glColor4fv(c->color);
		GLfloat strip = c->scale * c->step;
		glEnableClientState(GL_VERTEX_ARRAY);

		if(c->type == point_type)
		{
			GLfloat vertex[] = {
				0.0, strip,
				0.0, -strip,
				-strip, 0.0,
				strip, 0.0
			};
			glVertexPointer(2, GL_FLOAT, 0, vertex);
			oglDrawArrays(GL_POINTS, 0, 4);
		}
		else
		{
			GLfloat vertex[] = {
				-c->width / 2, c->width * 4 + strip,
				-c->width / 2, c->width * 4 + c->height + strip,
				-c->width / 2, -c->width * 4 - strip,
				-c->width / 2, -c->width * 4 - c->height - strip,
				-c->width * 4 - strip, -c->width / 2,
				-c->width * 4 - c->height - strip, -c->width / 2,
				c->width * 4 + strip, -c->width / 2,
				c->width * 4 + c->height + strip, -c->width / 2
			};
			glVertexPointer(2, GL_FLOAT, 0, vertex);
			oglDrawArrays(GL_LINES, 0, 8);
		}
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	glPopAttrib();
}

void UI_RenderRayCrossHair(const ray_cross_hair *c)
{
	if(!c)
		return;
	GLfloat vertex[] = {
		c->start_pos[0],
		c->start_pos[1],
		c->start_pos[2],
		c->target_pos[0],
		c->target_pos[1],
		c->target_pos[2]
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertex);
	if(1)
	{
		glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT);
		{
			oglEnable(GL_LINE_SMOOTH);
			glColor4fv(c->color);
			oglDrawArrays(GL_LINES, 0, 2);
		}
		glPopAttrib();
	}
	glPushAttrib(GL_CURRENT_BIT | GL_POINT_BIT);
	{
#ifndef _HARMATTAN_OPENGLES2
		glPointSize(c->point_max_width);

		glPointParameteri(GL_POINT_SIZE_MAX, c->point_max_width);
		glPointParameteri(GL_POINT_SIZE_MIN, c->point_min_width);
		GLfloat attenuation[] = {0.0, 0.02, 0.0};
		glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, attenuation);
#endif
		oglEnable(GL_POINT_SMOOTH);
		glColor4fv(c->color);
		oglDrawArrays(GL_POINTS, 1, 1);
	}
	glPopAttrib();
	glDisableClientState(GL_VERTEX_ARRAY);
}

void UI_RenderCrossHair(const cross_hair *c)
{
	if(!c)
		return;
	if(c->type == ray_type)
	{
		UI_RenderRayCrossHair(&c->ray);
	}
	else if(c->type == optical_type)
	{
		UI_RenderOpticalSightCrossHair(&c->optical, sight_optical);
	}
	else
	{
		UI_RenderNormalCrossHair(&c->normal);
	}
}

void delete_optical_sight(optical_sight_cross_hair *c)
{
	if(!c)
		return;
	int i;
	for(i = 0; i < total_buffer_type; i++)
	{
		if(glIsBuffer(c->buffers[i]))
		{
			glDeleteBuffers(1, c->buffers + i);
		}
	}
}

