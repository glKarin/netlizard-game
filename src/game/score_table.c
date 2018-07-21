#include "score_table.h"
#include "nl_std.h"

#include <string.h>
#include <stdlib.h>

#define HEADER_HEIGHT 40
#define LABEL_HEIGHT 30

static const char *Table_Label[] = {
	"Character", "Kill", "Death"
};

score_table * new_score_table(score_table *st, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat cell_w, GLfloat cell_h, GLfloat line_width, const GLfloat line_color[], const GLfloat bg_color[], const GLfloat hl_color[], const GLfloat text_color[])
{
	RETURN_PTR(t, st, score_table)

		t->x = x;
	t->y = y;
	t->z = z;
	t->width = w;
	t->height = h;
	t->visible = GL_FALSE;
	t->cell_width = cell_w;
	t->cell_height = cell_h;
	t->line_width = line_width;
	COPY_COLOR4(t->line_color, line_color)
	COPY_COLOR4(t->bg_color, bg_color)
	COPY_COLOR4(t->hl_color, hl_color)
	COPY_COLOR4(t->text_color, text_color)

	GLfloat vertex[] = {
		0.0, 0.0,
		t->width, 0.0,
		0.0, t->height,
		t->width, t->height
	};

	t->buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, vertex, GL_STATIC_DRAW);

	return t;
}

void delete_score_table(score_table *t)
{
	if(!t)
		return;
	int i;
	for(i = vertex_buffer_type; i < total_buffer_type; i++)
	{
		if(glIsBuffer(t->buffers[i]))
			glDeleteBuffers(1, t->buffers + i);
	}
	t->fnt = NULL;
	t->game_mode = NULL;
}

void UI_RenderScoreTable(const score_table *t)
{
	if(!t)
		return;
	if(!t->fnt || !t->game_mode)
		return;
	int rows = 0;
	int cols = t->game_mode->group_count;
	int i;
	for(i = 0; i < t->game_mode->group_count; i++)
	{
		rows = KARIN_MAX(t->game_mode->group_person_count[i], rows);
	}
	//rows += 1;
	GLfloat cell_width = (cols > 0) ? t->width / cols : t->cell_width;
	GLfloat cell_height = (rows > 0) ? t->height / rows : t->cell_height;
	cell_width = KARIN_MIN(cell_width, t->cell_width);
	cell_height = KARIN_MIN(cell_height, t->cell_height);
	GLfloat width = cell_width * cols;
	GLfloat height = cell_height * rows;

	GLfloat vertex[] = {
		0.0, 0.0, 0.0, -height,
		0.0, 0.0, width, 0.0,
		0.0, 0.0, 0.0, - HEADER_HEIGHT,
		0.0, 0.0, 0.0, - LABEL_HEIGHT,
		0.0, 0.0, 0.0, - cell_height,
	};
	glEnableClientState(GL_VERTEX_ARRAY);

	// draw cell box
	glPushMatrix();
	{
		glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT);
		{
			glColor4fv(t->bg_color);
			glBindBuffer(GL_ARRAY_BUFFER, t->buffers[vertex_buffer_type]);
			glVertexPointer(2, GL_FLOAT, 0, NULL);
			oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glTranslatef(0.0, t->height, 0.0);
			glLineWidth(t->line_width);
			glColor4fv(t->line_color);
			glVertexPointer(2, GL_FLOAT, 0, vertex);
			glTranslatef(0.0, -HEADER_HEIGHT, 0.0);
			glPushMatrix();
			{
				oglDrawArrays(GL_LINES, 2, 2);
				glPushMatrix();
				{
					for(i = 0; i <= cols; i++)
					{
						oglDrawArrays(GL_LINES, 6, 2);
						glTranslatef(cell_width, 0.0, 0.0);
					}
				}
				glPopMatrix();
				glTranslatef(0.0, - LABEL_HEIGHT, 0.0);

				oglDrawArrays(GL_LINES, 2, 2);
				glPushMatrix();
				{
					for(i = 0; i <= cols; i++)
					{
						oglDrawArrays(GL_LINES, 8, 2);
						glTranslatef(cell_width, 0.0, 0.0);
					}
				}
				glPopMatrix();
				glTranslatef(0.0, -cell_height, 0.0);

				oglDrawArrays(GL_LINES, 2, 2);
				glPushMatrix();
				{
					for(i = 0; i < cols; i++)
					{
						glPushMatrix();
						{
							int k;
							for(k = 0; k < 3; k++)
							{
								glTranslatef(cell_width / 3, 0.0, 0.0);
								oglDrawArrays(GL_LINES, 6, 2);
							}
						}
						glPopMatrix();
						oglDrawArrays(GL_LINES, 6, 2);
						glTranslatef(cell_width, 0.0, 0.0);
					}
				}
				glPopMatrix();
				glTranslatef(0.0, - LABEL_HEIGHT, 0.0);
				oglDrawArrays(GL_LINES, 2, 2);
			}
			glPopMatrix();

			glTranslatef(0.0, -(LABEL_HEIGHT * 2 + cell_height), 0);

			glPushMatrix();
			{
				for(i = 0; i < rows; i++)
				{
					glTranslatef(0.0, -cell_height, 0.0);
					oglDrawArrays(GL_LINES, 2, 2);
				}
			}
			glPopMatrix();
			glPushMatrix();
			{
				for(i = 0; i < cols; i++)
				{
					glPushMatrix();
					{
						int j;
						for(j = 0; j < 3; j++)
						{
							glTranslatef(cell_width / 3, 0.0, 0.0);
							oglDrawArrays(GL_LINES, 0, 2);
						}
					}
					glPopMatrix();
					oglDrawArrays(GL_LINES, 0, 2);
					glTranslatef(cell_width, 0.0, 0.0);
				}
			}
			glPopMatrix();
		}
		glPopAttrib();

	}
	glPopMatrix();

	// fill data text
	glPushMatrix();
	{
		glTranslatef(0.0, t->height, 0.0);
		glTranslatef(0.0, -HEADER_HEIGHT, 0.0);
		float x = 0.0;
		float y = 0.0;
		Font_GetStringCenterPosition(t->fnt, 0, 0, t->width, HEADER_HEIGHT, "Score Table", &x, &y);
		Font_RenderString(t->fnt, x, y, t->text_color[0], t->text_color[1], t->text_color[2], t->text_color[3], "Score Table");

		glTranslatef(0.0, - LABEL_HEIGHT, 0.0);
		glPushMatrix();
		{
			int j;
			for(j = 0; j < t->game_mode->group_count; j++)
			{
				char *str = itostr(t->game_mode->group_id[j]);
				size_t len = strlen(str) + strlen("GROUP") + 1 + 1;
				char *text = NEW_II(char, len);
				memset(text, '\0', sizeof(char) * len);
				sprintf(text, "%s-%s", "GROUP", str);
				Font_GetStringCenterPosition(t->fnt, 0, 0, cell_width, LABEL_HEIGHT, text, &x, &y);
				Font_RenderString(t->fnt, x, y, t->text_color[0], t->text_color[1], t->text_color[2], t->text_color[3], text);
				free(text);
				free(str);
				glTranslatef(cell_width, 0.0, 0.0);
			}
		}
		glPopMatrix();

		glTranslatef(0.0, -cell_height, 0.0);
		glPushMatrix();
		{
			for(i = 0; i < t->game_mode->group_count; i++)
			{
				Font_GetDigitCenterPosition(t->fnt, 0, 0, cell_width, cell_height, t->game_mode->group_point[i], &x, &y);
				Font_RenderDigit(t->fnt, x, y, t->text_color[0], t->text_color[1], t->text_color[2], t->text_color[3], t->game_mode->group_point[i]);
				glTranslatef(cell_width, 0.0, 0.0);
			}
		}
		glPopMatrix();

		glTranslatef(0.0, -LABEL_HEIGHT, 0.0);
		glPushMatrix();
		{
			for(i = 0; i < t->game_mode->group_count; i++)
			{
				glPushMatrix();
				{
					int j;
					for(j = 0; j < 3; j++)
					{
						Font_GetStringCenterPosition(t->fnt, 0, 0, cell_width / 3, LABEL_HEIGHT, Table_Label[j], &x, &y);
						Font_RenderString(t->fnt, x, y, t->text_color[0], t->text_color[1], t->text_color[2], t->text_color[3], Table_Label[j]);
						glTranslatef(cell_width / 3, 0.0, 0.0);
					}
				}
				glPopMatrix();
				glTranslatef(cell_width, 0.0, 0.0);
			}
		}
		glPopMatrix();

		glTranslatef(0.0, -cell_height, 0.0);
		glPushMatrix();
		{
			for(i = 0; i < t->game_mode->group_count; i++)
			{
				glPushMatrix();
				{
					int k;
					for(k = 0; k < t->game_mode->group_person_count[i]; k++)
					{
						glPushMatrix();
						{
							Font_GetStringCenterPosition(t->fnt, 0, 0, cell_width / 3, cell_height, t->game_mode->group_character[i][k]->name, &x, &y);
							Font_RenderString(t->fnt, x, y, t->text_color[0], t->text_color[1], t->text_color[2], t->text_color[3], t->game_mode->group_character[i][k]->name);
							glTranslatef(cell_width / 3, 0.0, 0.0);

							Font_GetDigitCenterPosition(t->fnt, 0, 0, cell_width / 3, cell_height, t->game_mode->group_character[i][k]->score.kill, &x, &y);
							Font_RenderDigit(t->fnt, x, y, t->text_color[0], t->text_color[1], t->text_color[2], t->text_color[3], t->game_mode->group_character[i][k]->score.kill);
							glTranslatef(cell_width / 3, 0.0, 0.0);
							
							Font_GetDigitCenterPosition(t->fnt, 0, 0, cell_width / 3, cell_height, t->game_mode->group_character[i][k]->score.death, &x, &y);
							Font_RenderDigit(t->fnt, x, y, t->text_color[0], t->text_color[1], t->text_color[2], t->text_color[3], t->game_mode->group_character[i][k]->score.death);
							glTranslatef(cell_width / 3, 0.0, 0.0);
						}
						glPopMatrix();
						glTranslatef(0.0, -cell_height, 0.0);
					}
				}
				glPopMatrix();
				glTranslatef(cell_width, 0.0, 0.0);
			}
		}
		glPopMatrix();
	}
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
}
