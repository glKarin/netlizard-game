#include "character_status_bar.h"

#include "gl_util.h"
#include "nl_std.h"

static void UI_MakeHealthIcon(GLfloat w, GLfloat bw, GLfloat health[]);
static void UI_MakeAmmoIcon(GLfloat w, GLfloat h, GLfloat ammo[]);
static void UI_MakeClockIcon(GLfloat r, GLfloat clock[]);

character_status_bar * new_character_status_bar(character_status_bar *sb, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat border_width, const GLfloat bg_color[], const GLfloat text_color[], const GLfloat border_color[], const GLfloat icon_color[])
{
	RETURN_PTR(s, sb, character_status_bar)

		s -> x = x;
	s -> y = y;
	s -> z = z;
	s -> width = width;
	s -> height = height;
	s -> border_width = border_width;
	COPY_COLOR4(s -> bg_color, bg_color)
	COPY_COLOR4(s -> border_color, border_color)
	COPY_COLOR4(s -> icon_color, icon_color)
	COPY_COLOR4(s -> text_color, text_color)

	GLfloat vertex[8] = {
		0.0, 0.0,
		s -> width, 0.0,
		0.0, s -> height,
		s -> width, s -> height
	};
	GLushort index[4] = {
		0, 1, 3, 2
	};
	s -> buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, vertex, GL_STATIC_DRAW);
	s -> buffers[index_buffer_type] = new_OpenGL_buffer_object(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 4, index, GL_STATIC_DRAW);

	GLfloat health[8 * 2];
	UI_MakeHealthIcon(s -> height - 4, (s -> height - 4) / 3, health);
	s -> health_buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8 * 2, health, GL_STATIC_DRAW);

	GLfloat clock[363 * 2];
	UI_MakeClockIcon((s -> height - 2) / 2, clock);
	s -> clock_buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 363 * 2, clock, GL_STATIC_DRAW);

	GLfloat ammo[11 * 3 * 2];
	UI_MakeAmmoIcon(s -> height - 4, s -> height - 4, ammo);
	s -> ammo_buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 11 * 3 * 2, ammo, GL_STATIC_DRAW);
	return s;
}

void UI_RenderCharacterStatusBar(const character_status_bar *sb)
{
	if(!sb)
		return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT);
	{
		glBindBuffer(GL_ARRAY_BUFFER, sb -> buffers[vertex_buffer_type]);
		glVertexPointer(2, GL_FLOAT, 0, NULL);
		glColor4fv(sb -> bg_color);
		oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		if(sb -> border_width != 0.0)
		{
			glColor4fv(sb -> border_color);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sb -> buffers[index_buffer_type]);
			oglDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, NULL);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		glPushMatrix();
		{
			glColor4fv(sb -> icon_color);
			glTranslatef(sb -> width / 18, sb -> height / 2, 0.1);
			glBindBuffer(GL_ARRAY_BUFFER, sb -> health_buffers[vertex_buffer_type]);
			glVertexPointer(2, GL_FLOAT, 0, NULL);
			oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			oglDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glColor4fv(sb -> icon_color);
			glTranslatef(sb -> width / 18 * 7, sb -> height / 2, 0.1);
			glBindBuffer(GL_ARRAY_BUFFER, sb -> clock_buffers[vertex_buffer_type]);
			glVertexPointer(2, GL_FLOAT, 0, NULL);
			oglDrawArrays(GL_LINE_LOOP, 0, 360);
			oglDrawArrays(GL_LINE_STRIP, 360, 3);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glColor4fv(sb -> icon_color);
			glTranslatef(sb -> width / 18 * 13, sb -> height / 2, 0.1);
			glBindBuffer(GL_ARRAY_BUFFER, sb -> ammo_buffers[vertex_buffer_type]);
			glVertexPointer(2, GL_FLOAT, 0, NULL);
			int i;
			for(i = 0; i < 3; i++)
			{
				oglDrawArrays(GL_TRIANGLES, i * 11 + 0, 3);
				oglDrawArrays(GL_TRIANGLE_STRIP, i * 11 + 3, 4);
				oglDrawArrays(GL_TRIANGLE_STRIP, i * 11 + 7, 4);
			}
		}
		glPopMatrix();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glPopAttrib();
	if(sb -> fnt && sb -> game_mode)
	{
		char str[100];
		glPushMatrix();
		{
			glTranslatef(sb -> width / 18 * 3, sb -> height / 2 - sb -> fnt -> height / 2, 0.1);
			sprintf(str, "%d", sb -> game_mode -> characters[sb -> game_mode -> current_character].health); 
			Font_RenderString(sb -> fnt, 0, 0, sb -> text_color[0], sb -> text_color[1], sb -> text_color[2], sb -> text_color[3], str);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(sb -> width / 18 * 9, sb -> height / 2 - sb -> fnt -> height / 2, 0.1);
			sprintf(str, "%02lld : %02lld", sb -> game_mode -> time / 60, sb -> game_mode -> time % 60);
			Font_RenderString(sb -> fnt, 0, 0, sb -> text_color[0], sb -> text_color[1], sb -> text_color[2], sb -> text_color[3], str);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(sb -> width / 18 * 15, sb -> height / 2 - sb -> fnt -> height / 2, 0.1);
			sprintf(str, "%d / %d", sb -> game_mode -> characters[sb -> game_mode -> current_character].current_weapon.ammo, sb -> game_mode -> characters[sb -> game_mode -> current_character].current_weapon.ammo_total_count >= 0 ? sb -> game_mode -> characters[sb -> game_mode -> current_character].current_weapon.ammo_total_count - sb -> game_mode -> characters[sb -> game_mode -> current_character].current_weapon.ammo : -1);
			Font_RenderString(sb -> fnt, 0, 0, sb -> text_color[0], sb -> text_color[1], sb -> text_color[2], sb -> text_color[3], str);
		}
		glPopMatrix();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
}

void delete_character_status_bar(character_status_bar *sb)
{
	if(!sb)
		return;
	sb -> fnt = NULL;
	sb -> game_mode = NULL;

	int i;
	for(i = vertex_buffer_type; i < total_buffer_type; i++)
	{
		if(glIsBuffer(sb -> buffers[i]))
			glDeleteBuffers(1, sb -> buffers + i);
		if(glIsBuffer(sb -> health_buffers[i]))
			glDeleteBuffers(1, sb -> health_buffers + i);
		if(glIsBuffer(sb -> clock_buffers[i]))
			glDeleteBuffers(1, sb -> clock_buffers + i);
		if(glIsBuffer(sb -> ammo_buffers[i]))
			glDeleteBuffers(1, sb -> ammo_buffers + i);
	}
}

void UI_MakeHealthIcon(GLfloat w, GLfloat bw, GLfloat health[])
{
	if(w <= 0.0 || bw <= 0.0 || !health)
		return;
	health[0] = -w / 2;
	health[1] = -bw / 2;
	health[2] = w / 2;
	health[3] = -bw / 2;
	health[4] = -w / 2;
	health[5] = bw / 2;
	health[6] = w / 2;
	health[7] = bw / 2;

	health[8] = -bw / 2;
	health[9] = -w / 2;
	health[10] = bw / 2;
	health[11] = -w / 2;
	health[12] = -bw / 2;
	health[13] = w / 2;
	health[14] = bw / 2;
	health[15] = w / 2;
}

void UI_MakeClockIcon(GLfloat r, GLfloat clock[])
{
	if(r <= 0.0 || !clock)
		return;
	GLfloat c1_x = 0;
	GLfloat c1_y = 0;
	GLfloat c2_x = 0;
	GLfloat c2_y = 0;
	int j;
	for(j = 0; j < 360; j++)
	{
		GLfloat p = ator(Algo_FormatAngle(j));
		if(j == 160)
		{
			c1_x = r * 0.5 * cos(p);
			c1_y = r * 0.5 * sin(p);
		}
		if(j == 60)
		{
			c2_x = r * 0.8 * cos(p);
			c2_y = r * 0.8 * sin(p);
		}
		clock[j * 2] = cos(p) * r;
		clock[j * 2 + 1] = sin(p) * r;
	}
	clock[j * 2] = c2_x;
	clock[j * 2 + 1] = c2_y;
	clock[j * 2 + 2] = 0;
	clock[j * 2 + 3] = 0;
	clock[j * 2 + 4] = c1_x;
	clock[j * 2 + 5] = c1_y;
}

void UI_MakeAmmoIcon(GLfloat w, GLfloat h, GLfloat ammo[])
{
	if(w <= 0.0 || h <= 0.0 || !ammo)
		return;
	ammo[0] = 0;
	ammo[1] = h / 2;
	ammo[2] = - (w - 2 * 2) / 3 / 2;
	ammo[3] = h / 2 - h / 2 / 3;
	ammo[4] = (w - 2 * 2) / 3 / 2;
	ammo[5] = h / 2 - h / 2 / 3;

	ammo[6] = - (w - 2 * 2) / 3 / 2;
	ammo[7] = -h / 2;
	ammo[8] = (w - 2 * 2) / 3 / 2;
	ammo[9] = -h / 2;
	ammo[10] = - (w - 2 * 2) / 3 / 2;
	ammo[11] = -h / 2 + h / 2 / 4;
	ammo[12] = (w - 2 * 2) / 3 / 2;
	ammo[13] = -h / 2 + h / 2 / 4;

	ammo[14] = - (w - 2 * 2) / 3 / 2;
	ammo[15] = -h / 2 + h / 2 / 4 + 1;
	ammo[16] = (w - 2 * 2) / 3 / 2;
	ammo[17] = -h / 2 + h / 2 / 4 + 1;
	ammo[18] = - (w - 2 * 2) / 3 / 2;
	ammo[19] = h / 2 - h / 2 / 3 - 1;
	ammo[20] = (w - 2 * 2) / 3 / 2;
	ammo[21] = h / 2 - h / 2 / 3 - 1;

	int i;
	for(i = 0; i < 22; i++)
	{
		if(i % 2 == 0)
			ammo[22 + i] = ammo[i] - ((w - 2 * 2) / 3 + 2);
		else
			ammo[22 + i] = ammo[i];
	}
	for(i = 0; i < 22; i++)
	{
		if(i % 2 == 0)
			ammo[44 + i] = ammo[i] + ((w - 2 * 2) / 3 + 2);
		else
			ammo[44 + i] = ammo[i];
	}
}

