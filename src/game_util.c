#include "game_util.h"

#include "netlizard/netlizard.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

action_info Action_Infos[Total_Action] = {
	{Forward_Action, Harmattan_K_w, "forward", "Move Forward"}, 
	{Backward_Action, Harmattan_K_s, "backward", "Move Backward"}, 
	{MoveLeft_Action, Harmattan_K_a, "move_left", "Move Left"}, 
	{MoveRight_Action, Harmattan_K_d, "move_right", "Move Right"}, 
	{MoveUp_Action, Harmattan_K_e, "move_up", "Move Up"}, 
	{MoveDown_Action, Harmattan_K_q, "move_down", "Move Down"}, 
	{TurnUp_Action, Harmattan_K_Up, "turn_up", "Turn Up"}, 
	{TurnDown_Action, Harmattan_K_Down, "turn_down", "Turn Down"}, 
	{TurnLeft_Action, Harmattan_K_Left, "turn_left", "Turn Left"}, 
	{TurnRight_Action, Harmattan_K_Right, "turn_right", "Turn Right"}, 
	{Jump_Action, Harmattan_K_space, "jump", "Jump"}, 
	{Crouch_Action, Harmattan_K_n, "crouch", "Crouch"}, 
	{Attack_Action, Harmattan_K_Return, "attack", "Attack"}, 
	{ZoomIn_Action, Harmattan_K_i, "zoomin", "Zoom In"}, 
	{ZoomOut_Action, Harmattan_K_o, "zoomout", "Zoom Out"}, 
	{PersonMode_Action, Harmattan_K_m, "person_mode", "Person View Mode"}, 
	{ConsoleMode_Action, Harmattan_K_b, "console", "Console"}, 
	{OpenLight_Action, Harmattan_K_f, "open_light", "Open Light"}, 
	{PrevWeapon_Action, Harmattan_K_y, "prev_weapon", "Previous Weapon"}, 
	{NextWeapon_Action, Harmattan_K_u, "next_weapon", "Next Weapon"}, 
	{OperateGo_Action, Harmattan_K_j, "operate_go", "Operate Go"}, 
	{OperateBack_Action, Harmattan_K_k, "operate_back", "Operate Back"}, 
	{OperateStand_Action, Harmattan_K_l, "operate_stand", "Operate Stand"}, 
	{OpenScore_Action, Harmattan_K_t, "open_score", "Open Score Table"}, 
	{FreeViewTurnLeft_Action, Harmattan_K_comma, "free_view_turn_left", "Free View Turn Left"}, 
	{FreeViewTurnRight_Action, Harmattan_K_period, "free_view_turn_right", "Free View Turn Right"}, 
	{FreeViewTurnUp_Action, Harmattan_K_p, "free_view_turn_up", "Free View Turn Up"}, 
	{FreeViewTurnDown_Action, Harmattan_K_apostrophe, "free_view_turn_down", "Free View Turn Down"}, 
	{FreeViewMode_Action, Harmattan_K_z, "free_view_mode", "Free View Mode"}, 
	{OpenRadar_Action, Harmattan_K_x, "open_radar", "Open Radar"}, 
	{Reload_Action, Harmattan_K_r, "reload", "Reload"}, 
	{ViewCenter_Action, Harmattan_K_v, "view_center", "View Center"},
	{Quit_Action, Harmattan_K_BackSpace, "quit", "Quit"}
};

key_info Key_Infos[Harmattan_Total_Key] = {
	{Harmattan_K_Multi_key,       "Multi_key",        "Multi Key"},
	{Harmattan_K_F1,              "F1",               "Function 1"},
	{Harmattan_K_F2,              "F2",               "Function 2"},
	{Harmattan_K_F3,              "F3",               "Function 3"},
	{Harmattan_K_F4,              "F4",               "Function 4"},
	{Harmattan_K_F5,              "F5",               "Function 5"},
	{Harmattan_K_F6,              "F6",               "Function 6"},
	{Harmattan_K_F7,              "F7",               "Function 7"},
	{Harmattan_K_BackSpace,       "BackSpace",        "BackSpace"},
	{Harmattan_K_Tab,             "Tab",              "Tab"},
	{Harmattan_K_KP_Enter,        "KP_Enter",         "KeyPad Enter"},
	{Harmattan_K_F11,             "F11",              "Function 11"},
	{Harmattan_K_F12,             "F12",              "Function 12"},
	{Harmattan_K_Return,          "Return",           "Return"},
	{Harmattan_K_F8,              "F8",               "Function 8"},
	{Harmattan_K_F9,              "F9",               "Function 9"},
	{Harmattan_K_F10,             "F10",              "Function 10"},
	{Harmattan_K_Control_L,       "Control_L",        "Left Control"},
	{Harmattan_K_Control_R,       "Control_R",        "Right Control"},
	{Harmattan_K_Shift_L,         "Shift_L",          "Left Shift"},
	{Harmattan_K_Shift_R,         "Shift_R",          "Right Shift"},
	{Harmattan_K_sterling,        "sterling",         "sterling £"},
	{Harmattan_K_EuroSign,        "EuroSign",         "Europe Sign €"},
	{Harmattan_K_Up,              "Up",               "Up"},
	{Harmattan_K_Down,            "Down",             "Down"},
	{Harmattan_K_Left,            "Left",             "Left"},
	{Harmattan_K_Right,           "Right",            "Right"},
	{Harmattan_K_Escape,          "Escape",           "Escape"},
	{Harmattan_K_Home,            "Home",             "Home"},
	{Harmattan_K_End,             "End",              "End"},
	{Harmattan_K_Page_Up,         "Page_Up",          "Page Up"},
	{Harmattan_K_Page_Down,       "Page_Down",        "Page Down"},
	{Harmattan_K_space,           "space",            "space"},
	{Harmattan_K_exclam,          "exclam",           "!"},
	{Harmattan_K_quotedbl,        "quotedbl",         "\""},
	{Harmattan_K_numbersign,      "numbersign",       "#"},
	{Harmattan_K_dollar,          "dollar",           "$"},
	{Harmattan_K_percent,         "percent",          "%"},
	{Harmattan_K_ampersand,       "ampersand",        "&"},
	{Harmattan_K_apostrophe,      "apostrophe",       "'"},
	{Harmattan_K_parenleft,       "parenleft",        "("},
	{Harmattan_K_parenright,      "parenright",       ")"},
	{Harmattan_K_asterisk,        "asterisk",         "*"},
	{Harmattan_K_plus,            "plus",             "+"},
	{Harmattan_K_comma,           "comma",            ","},
	{Harmattan_K_minus,           "minus",            "-"},
	{Harmattan_K_period,          "period",           "."},
	{Harmattan_K_slash,           "slash",            "/"},
	{Harmattan_K_0,               "0",                "0"},
	{Harmattan_K_1,               "1",                "1"},
	{Harmattan_K_2,               "2",                "2"},
	{Harmattan_K_3,               "3",                "3"},
	{Harmattan_K_4,               "4",                "4"},
	{Harmattan_K_5,               "5",                "5"},
	{Harmattan_K_6,               "6",                "6"},
	{Harmattan_K_7,               "7",                "7"},
	{Harmattan_K_8,               "8",                "8"},
	{Harmattan_K_9,               "9",                "9"},
	{Harmattan_K_colon,           "colon",            ":"},
	{Harmattan_K_semicolon,       "semicolon",        ";"},
	{Harmattan_K_less,            "less",             "<"},
	{Harmattan_K_equal,           "equal",            "="},
	{Harmattan_K_greater,         "greater",          ">"},
	{Harmattan_K_question,        "question",         "?"},
	{Harmattan_K_at,              "at",               "@"},
	{Harmattan_K_A,               "A",                "A"},
	{Harmattan_K_B,               "B",                "B"},
	{Harmattan_K_C,               "C",                "C"},
	{Harmattan_K_D,               "D",                "D"},
	{Harmattan_K_E,               "E",                "E"},
	{Harmattan_K_F,               "F",                "F"},
	{Harmattan_K_G,               "G",                "G"},
	{Harmattan_K_H,               "H",                "H"},
	{Harmattan_K_I,               "I",                "I"},
	{Harmattan_K_J,               "J",                "J"},
	{Harmattan_K_K,               "K",                "K"},
	{Harmattan_K_L,               "L",                "L"},
	{Harmattan_K_M,               "M",                "M"},
	{Harmattan_K_N,               "N",                "N"},
	{Harmattan_K_O,               "O",                "O"},
	{Harmattan_K_P,               "P",                "P"},
	{Harmattan_K_Q,               "Q",                "Q"},
	{Harmattan_K_R,               "R",                "R"},
	{Harmattan_K_S,               "S",                "S"},
	{Harmattan_K_T,               "T",                "T"},
	{Harmattan_K_U,               "U",                "U"},
	{Harmattan_K_V,               "V",                "V"},
	{Harmattan_K_W,               "W",                "W"},
	{Harmattan_K_X,               "X",                "X"},
	{Harmattan_K_Y,               "Y",                "Y"},
	{Harmattan_K_Z,               "Z",                "Z"},
	{Harmattan_K_bracketleft,     "bracketleft",      "["},
	{Harmattan_K_backslash,       "backslash",        "\\"},
	{Harmattan_K_bracketright,    "bracketright",     "]"},
	{Harmattan_K_asciicircum,     "asciicircum",      "^"},
	{Harmattan_K_underscore,      "underscore",       "_"},
	{Harmattan_K_grave,           "grave",            "`"},
	{Harmattan_K_a,               "a",                "a"},
	{Harmattan_K_b,               "b",                "b"},
	{Harmattan_K_c,               "c",                "c"},
	{Harmattan_K_d,               "d",                "d"},
	{Harmattan_K_e,               "e",                "e"},
	{Harmattan_K_f,               "f",                "f"},
	{Harmattan_K_g,               "g",                "g"},
	{Harmattan_K_h,               "h",                "h"},
	{Harmattan_K_i,               "i",                "i"},
	{Harmattan_K_j,               "j",                "j"},
	{Harmattan_K_k,               "k",                "k"},
	{Harmattan_K_l,               "l",                "l"},
	{Harmattan_K_m,               "m",                "m"},
	{Harmattan_K_n,               "n",                "n"},
	{Harmattan_K_o,               "o",                "o"},
	{Harmattan_K_p,               "p",                "p"},
	{Harmattan_K_q,               "q",                "q"},
	{Harmattan_K_r,               "r",                "r"},
	{Harmattan_K_s,               "s",                "s"},
	{Harmattan_K_t,               "t",                "t"},
	{Harmattan_K_u,               "u",                "u"},
	{Harmattan_K_v,               "v",                "v"},
	{Harmattan_K_w,               "w",                "w"},
	{Harmattan_K_x,               "x",                "x"},
	{Harmattan_K_y,               "y",                "y"},
	{Harmattan_K_z,               "z",                "z"},
	{Harmattan_K_braceleft,       "braceleft",        "{"},
	{Harmattan_K_bar,             "bar",              "|"},
	{Harmattan_K_braceright,      "braceright",       "}"},
	{Harmattan_K_asciitilde,      "asciitilde",       "~"},
	{Harmattan_K_Delete,          "Delete",           "Delete"},
	{Harmattan_K_ISO_Level3_Shift,"ISO_Level3_Shift", "ISO Level3 Shift"},
	{Harmattan_Board_Key,      "Board_Key",        "Other Board Key"},
	{Harmattan_M_LeftButton,      "LeftButton",       "Left Mouse Button"},
	{Harmattan_M_RightButton,     "RightButton",      "Right Mouse Button"},
	{Harmattan_M_MiddleButton,    "MiddleButton",     "Middle Mouse Button"},
	{Harmattan_Mouse_Key,      "Mouse_Key",        "Other Mouse Key"},
	{Harmattan_Other_Key,      "Other_Key",         "Other Key"}
};

const char * Console_PrintLine(const char *title, char ch)
{
	static const size_t LineLength = 47;
	static char TextLine[] = "-----------------------------------------------";
	// strlen = 47, sizeof = 48

	unsigned int i;
	for(i = 0; i < LineLength; i++)
		TextLine[i] = ch;
	TextLine[LineLength] = '\0';
	if(title)
	{
		size_t len = strlen(title);
		if(len > LineLength)
			return title;
		int j = LineLength / 2 - len / 2;
		for(i = 0; i < len; i++)
			TextLine[i + j] = title[i];
	}

	return TextLine;
}

scene_2d * new_scene_2d(scene_2d *scene, GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat scale, anchor_type a, const GLfloat color[], const char *file)
{
	RETURN_PTR(s, scene, scene_2d)

		s->x = x;
	s->y = y;
	s->z = 0.0;
	s->scale = scale;
	s->align = a;
	if(file)
		s->tex = new_OpenGL_texture_2d(file);
	GLfloat w = width;
	GLfloat h = height;
	if(w <= 0.0)
	{
		if(s->tex)
			w = s->tex->width;
		else
			w = 1.0;
	}
	if(h <= 0.0)
	{
		if(s->tex)
			h = s->tex->height;
		else
			h = 1.0;
	}
	s->width = w;
	s->height = h;
	COPY_COLOR4(s->color, color)

	GLfloat scene_vertex[8] = {
		0.0, 0.0,
		s->width, 0.0,
		0.0, s->height,
		s->width, s->height
	};

	GLfloat scene_texcoord[8] = {
		0.0, 1.0,
		1.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,
	};
	s->buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, scene_vertex, GL_DYNAMIC_DRAW);
	s->buffers[texcoord_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, scene_texcoord, GL_STATIC_DRAW);

	return s;
}

void UI_ResizeScene2D(scene_2d *s, GLfloat w, GLfloat h)
{
	if(!s)
		return;
	if(w < 0.0 && h < 0.0)
		return;
	if(w == s->width && h == s->height)
		return;
	if(w > 0)
		s->width = w;
	if(h > 0)
		s->height = h;
	GLfloat scene_vertex[8] = {
		0.0, 0.0,
		s->width, 0.0,
		0.0, s->height,
		s->width, s->height
	};

	glBindBuffer(GL_ARRAY_BUFFER, s->buffers[vertex_buffer_type]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 8, scene_vertex);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void UI_RenderScene2D(const scene_2d *scene)
{
	if(!scene)
		return;
	glPushMatrix();
	{
		if(scene->align == left_bottom_anchor_type)
			glTranslatef(scene->x, scene->y, 0);
		else if(scene->align == left_top_anchor_type)
			glTranslatef(scene->x, scene->y - scene->height, 0);
		else if(scene->align == right_bottom_anchor_type)
			glTranslatef(scene->x - scene->width, scene->y, 0);
		else if(scene->align == right_top_anchor_type)
			glTranslatef(scene->x - scene->width, scene->y - scene->height, 0);
		else
			glTranslatef(scene->x - scene->width / 2, scene->y - scene->height / 2, 0);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glPushAttrib(GL_CURRENT_BIT);
		{
			if(scene->tex)
				oglBindTexture(GL_TEXTURE_2D, scene->tex->texid);
			else
				glColor4fv(scene->color);

			glBindBuffer(GL_ARRAY_BUFFER, scene->buffers[texcoord_buffer_type]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
			glBindBuffer(GL_ARRAY_BUFFER, scene->buffers[vertex_buffer_type]);
			glVertexPointer(2, GL_FLOAT, 0, NULL);
			oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			if(scene->tex)
				oglBindTexture(GL_TEXTURE_2D, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		glPopAttrib();
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	glPopMatrix();
}

vector3_t Algo_GLComputeDirection(float yr, float xr)
{
	GLfloat y = ator(yr);
	GLfloat x = ator(xr);
	vector3_t v ={
		-cos(x) * sin(y),
		sin(x),
		cos(x) * cos(y)
	};
	Vector3_Normalize(&v);
	return v;
}

vector3_t Algo_ComputeDirection(float yr, float xr)
{
	GLfloat y = ator(yr);
	GLfloat x = ator(xr);
	vector3_t v ={
		cos(x) * sin(y),
		- cos(x) * cos(y),
		- sin(x)
	};
	Vector3_Normalize(&v);
	return v;
}

void delete_scene_2d(scene_2d *s)
{
	if(!s)
		return;
	if(s->tex)
	{
		if(glIsTexture(s->tex->texid))
			glDeleteTextures(1, &(s->tex->texid));
	}
	GLuint i;
	for(i = 0; i < total_buffer_type; i++)
	{
		glIsBuffer(s->buffers[i]);
		glDeleteBuffers(1, s->buffers + i);
	}
}

void Algo_TransformPositionAndAngle(position_type p, const nl_vector3_t *ov, float tunit, nl_vector3_t *rv, orientation_type o, float oxr, float oyr,  float runit, float *rxr, float *ryr, int cross)
{
	if(!ov)
		return;
	float xp = ov->x;
	float yp = ov->y;
	float zp = ov->z;
	float xrp = oxr;
	float yrp = oyr;

	if(o != center_orientation_type)
	{
		if((o & up_orientation_type) && !(o & down_orientation_type))
		{
			float x = Algo_FormatAngle(oxr - runit);
			if(!cross && (x < 270 && x > 90))
				xrp = 270.0;
			else
				xrp = x;
		}
		else if((o & down_orientation_type) && !(o & up_orientation_type))
		{
			float x = Algo_FormatAngle(oxr + runit);
			if(!cross && (x > 90 && x < 270))
				xrp = 90.0;
			else
				xrp = x;
		}
		if((o & left_orientation_type) && !(o & right_orientation_type))
			yrp += runit;
		else if((o & right_orientation_type) && !(o & left_orientation_type))
			yrp -= runit;
		if(ryr)
			*ryr = Algo_FormatAngle(yrp);
		if(rxr)
			*rxr = Algo_FormatAngle(xrp);
	}

	if(p != center_position_type)
	{
		yrp = Algo_FormatAngle(yrp);
		xrp = Algo_FormatAngle(xrp);

		float y = ator(yrp);
		float x = ator(xrp);
		if(cross)
		{
			if((p & forward_position_type) && !(p & backward_position_type))
			{
				xp += cos(x) * sin(y) * tunit;
				yp -= cos(x) * cos(y) * tunit;
				zp -= sin(x) * tunit;
			}
			else if((p & backward_position_type) && !(p & forward_position_type))
			{
				xp -= cos(x) * sin(y) * tunit;
				yp += cos(x) * cos(y) * tunit;
				zp += sin(x) * tunit;
			}
			if((p & left_position_type) && !(p & right_position_type))
			{
				xp += cos(x) * cos(y) * tunit;
				yp += cos(x) * sin(y) * tunit;
				zp += sin(x) * tunit;
			}
			else if((p & right_position_type) && !(p & left_position_type))
			{
				xp -= cos(x) * cos(y) * tunit;
				yp -= cos(x) * sin(y) * tunit;
				zp -= sin(x) * tunit;
			}
			if((p & up_position_type) && !(p & down_position_type))
				zp += tunit;
			else if((p & down_position_type) && !(p & up_position_type))
				zp -= tunit;
		}
		else
		{
			if((p & forward_position_type) && !(p & backward_position_type)) // y axis
			{
				xp += sin(y) * tunit;
				yp -= cos(y) * tunit;
			}
			else if((p & backward_position_type) && !(p & forward_position_type)) // y axis
			{
				xp -= sin(y) * tunit;
				yp += cos(y) * tunit;
			}
			if((p & left_position_type) && !(p & right_position_type))// y axis
			{
				xp += cos(y) * tunit;
				yp += sin(y) * tunit;
			}
			else if((p & right_position_type) && !(p & left_position_type)) // y axis
			{
				xp -= cos(y) * tunit;
				yp -= sin(y) * tunit;
			}
#if 0
			if((p & up_position_type) && !(p & down_position_type))
				zp += tunit;
			else if((p & down_position_type) && !(p & up_position_type))
				zp -= tunit;
#endif
		}

		if(rv)
		{
			rv->x = xp;
			rv->y = yp;
			rv->z = zp;
		}
	}
}

void Algo_GLTransformPositionAndAngle(position_type p, const gl_vector3_t *ov, float tunit, gl_vector3_t *rv, orientation_type o, float oxr, float oyr, float runit, float *rxr, float *ryr, int cross)
{
	if(!ov)
		return;
	float xp = ov->x;
	float yp = ov->y;
	float zp = ov->z;
	float xrp = oxr;
	float yrp = oyr;

	if(o != center_orientation_type)
	{
		if((o & up_orientation_type) && !(o & down_orientation_type))
		{
			float x = Algo_FormatAngle(oxr - runit);
			if(!cross && (x < 270 && x > 90))
				xrp = 270.0;
			else
				xrp = x;
		}
		else if((o & down_orientation_type) && !(o & up_orientation_type))
		{
			float x = Algo_FormatAngle(oxr + runit);
			if(!cross && (x > 90 && x < 270))
				xrp = 90.0;
			else
				xrp = x;
		}
		if((o & left_orientation_type) && !(o & right_orientation_type))
			yrp -= runit;
		else if((o & right_orientation_type) && !(o & left_orientation_type))
			yrp += runit;
		if(ryr)
			*ryr = Algo_FormatAngle(yrp);
		if(rxr)
			*rxr = Algo_FormatAngle(xrp);
	}

	if(p != center_position_type)
	{
		yrp = Algo_FormatAngle(yrp);
		xrp = Algo_FormatAngle(xrp);

		float y = ator(yrp);
		float x = ator(xrp);
		if(cross)
		{
			if((p & forward_position_type) && !(p & backward_position_type))
			{
				xp -= cos(x) * sin(y) * tunit;
				yp += sin(x) * tunit;
				zp += cos(x) * cos(y) * tunit;
			}
			else if((p & backward_position_type) && !(p & forward_position_type))
			{
				xp += cos(x) * sin(y) * tunit;
				yp -= sin(x) * tunit;
				zp -= cos(x) * cos(y) * tunit;
			}
			if((p & left_position_type) && !(p & right_position_type))
			{
				xp += cos(x) * cos(y) * tunit;
				yp -= sin(x) * tunit;
				zp += cos(x) * sin(y) * tunit;
			}
			else if((p & right_position_type) && !(p & left_position_type))
			{
				xp -= cos(x) * cos(y) * tunit;
				yp += sin(x) * tunit;
				zp -= cos(x) * sin(y) * tunit;
			}
			if((p & up_position_type) && !(p & down_position_type))
				yp -= tunit;
			else if((p & down_position_type) && !(p & up_position_type))
				yp += tunit;
		}
		else
		{
			if((p & forward_position_type) && !(p & backward_position_type)) // y axis
			{
				xp -= sin(y) * tunit;
				zp += cos(y) * tunit;
			}
			else if((p & backward_position_type) && !(p & forward_position_type)) // y axis
			{
				xp += sin(y) * tunit;
				zp -= cos(y) * tunit;
			}
			if((p & left_position_type) && !(p & right_position_type))// y axis
			{
				xp += cos(y) * tunit;
				zp += sin(y) * tunit;
			}
			else if((p & right_position_type) && !(p & left_position_type)) // y axis
			{
				xp -= cos(y) * tunit;
				zp -= sin(y) * tunit;
			}
#if 0
			if((p & up_position_type) && !(p & down_position_type))
				yp -= tunit;
			else if((p & down_position_type) && !(p & up_position_type))
				yp += tunit;
#endif
		}

		if(rv)
		{
			rv->x = xp;
			rv->y = yp;
			rv->z = zp;
		}
	}
}

void Algo_GetNormalAngle2D(const vector2_t *normal, float *yr)
{
	if(!normal)
		return;
	float xl = normal->x;
	float yl = normal->y;
	if(yr)
		*yr = Algo_FormatAngle(rtoa(atan2(yl, xl)) - 90.0);
}

unsigned long long Game_GetGameTimeUS(void)
{
	struct timeval cur_time;
	gettimeofday(&cur_time, NULL);
	unsigned long long t = (unsigned long long)cur_time.tv_sec * (unsigned long long)1000000 + (unsigned long long)cur_time.tv_usec;
	return t;
}

// ms
unsigned long long Game_GetGameTime(void)
{
	struct timeval cur_time;
	gettimeofday(&cur_time, NULL);
	unsigned long long t = (unsigned long long)cur_time.tv_sec * (unsigned long long)1000 + (unsigned long long)cur_time.tv_usec / 1000;
	return t;
}

void Algo_GetNormalAngle(const nl_vector3_t *normal, float *yr, float *xr)
{
	if(!normal)
		return;
	float xl = normal->x;
	float yl = normal->y;
	if(yr)
		*yr = Algo_FormatAngle(rtoa(atan2(yl, xl)) - 90.0);
	if(xr)
	{
		float xyl = sqrt(xl * xl + yl * yl);
		float zl = normal->z;
		*xr = Algo_FormatAngle(rtoa(atan2(zl, xyl)));
	}
}

scene_3d * new_scene_3d(scene_3d *scene, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, anchor_type a, const GLfloat color[], const char *file, GLdouble foxy, GLdouble fw, GLdouble fh, GLdouble near, GLdouble far, void (*df)(void))
{
	RETURN_PTR(s, scene, scene_3d)

		s->x = x;
	s->y = y;
	s->z = z;
	s->align = a;
	if(file)
		s->tex = new_OpenGL_texture_2d(file);
	GLfloat w = width;
	GLfloat h = height;
	if(w <= 0.0)
	{
		if(s->tex)
			w = s->tex->width;
		else
			w = 1.0;
	}
	if(h <= 0.0)
	{
		if(s->tex)
			h = s->tex->height;
		else
			h = 1.0;
	}
	s->width = w;
	s->height = h;
	COPY_COLOR4(s->color, color)

	GLfloat scene_vertex[8] = {
		0.0, 0.0,
		s->width, 0.0,
		0.0, s->height,
		s->width, s->height
	};

	GLfloat scene_texcoord[8] = {
		0.0, 1.0,
		1.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,
	};
	s->buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, scene_vertex, GL_DYNAMIC_DRAW);
	s->buffers[texcoord_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, scene_texcoord, GL_STATIC_DRAW);

	s->translate.xt = s->translate.yt = s->translate.zt = 0;
	s->scale.xs = s->scale.ys = s->scale.zs = 0;
	s->rotate.xr = s->rotate.yr = s->rotate.zr = 0;

	s->draw_func = df; 
	s->foxy = foxy;
	s->near = near;
	s->far = far;
	s->frustum_width = fw;
	s->frustum_height = fh;

	return s;
}

void UI_RenderScene3D(const scene_3d *scene)
{
	if(!scene)
		return;
	glPushAttrib(GL_SCISSOR_BIT);
	{
		oglEnable(GL_SCISSOR_TEST);
		glScissor((GLint)scene->x, (GLint)scene->y, (GLsizei)scene->width, (GLsizei)scene->height);
		OpenGL_Render2D(0.0, scene->frustum_width, 0.0, scene->frustum_height);
		{
			glPushMatrix();
			{
				if(scene->align == left_bottom_anchor_type)
					glTranslatef(scene->x, scene->y, 0);
				else if(scene->align == left_top_anchor_type)
					glTranslatef(scene->x, scene->y - scene->height, 0);
				else if(scene->align == right_bottom_anchor_type)
					glTranslatef(scene->x - scene->width, scene->y, 0);
				else if(scene->align == right_top_anchor_type)
					glTranslatef(scene->x - scene->width, scene->y - scene->height, 0);
				else
					glTranslatef(scene->x - scene->width / 2, scene->y - scene->height / 2, 0);

				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glPushAttrib(GL_CURRENT_BIT);
				{
					if(scene->tex)
						oglBindTexture(GL_TEXTURE_2D, scene->tex->texid);
					else
						glColor4fv(scene->color);

					glBindBuffer(GL_ARRAY_BUFFER, scene->buffers[texcoord_buffer_type]);
					glTexCoordPointer(2, GL_FLOAT, 0, NULL);
					glBindBuffer(GL_ARRAY_BUFFER, scene->buffers[vertex_buffer_type]);
					glVertexPointer(2, GL_FLOAT, 0, NULL);
					oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

					if(scene->tex)
						oglBindTexture(GL_TEXTURE_2D, 0);
					glBindBuffer(GL_ARRAY_BUFFER, 0);
				}
				glPopAttrib();
				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			}
			glPopMatrix();
		}
		if(scene->draw_func)
		{
			OpenGL_Render3D(scene->foxy, scene->frustum_width, scene->frustum_height, scene->near, scene->far);
			{
				double f = (scene->frustum_height / 2) / tan(ator(scene->foxy / 2));

				glTranslatef(-scene->frustum_width / 2 + scene->x + scene->width / 2, -scene->frustum_height / 2 + scene->y + scene->height / 2, -f);

				glTranslatef(scene->translate.xt, scene->translate.yt, scene->translate.zt);

				{
					if(scene->rotate.xr != 0.0)
						glRotatef(scene->rotate.xr, 1.0, 0.0, 0.0);
					if(scene->rotate.yr != 0.0)
						glRotatef(scene->rotate.yr, 0.0, 1.0, 0.0);
					if(scene->rotate.zr != 0.0)
						glRotatef(scene->rotate.zr, 0.0, 0.0, 1.0);
				}

				glScalef(
						(scene->scale.xs != 0.0 && scene->scale.xs != 1.0) ? scene->scale.xs : 1.0,
						(scene->scale.ys != 0.0 && scene->scale.ys != 1.0) ? scene->scale.ys : 1.0,
						(scene->scale.zs != 0.0 && scene->scale.zs != 1.0) ? scene->scale.zs : 1.0
						);

				scene->draw_func();
			}
		}
	}
	glPopAttrib();
}

void delete_scene_3d(scene_3d *s)
{
	if(!s)
		return;
	if(s->tex)
	{
		if(glIsTexture(s->tex->texid))
			glDeleteTextures(1, &(s->tex->texid));
	}
	GLuint i;
	for(i = 0; i < total_buffer_type; i++)
	{
		glIsBuffer(s->buffers[i]);
		glDeleteBuffers(1, s->buffers + i);
	}
}

void UI_ResizeScene3D(scene_3d *s, GLfloat w, GLfloat h, GLfloat fw, GLfloat fh)
{
	if(!s)
		return;
	if(w < 0.0 && h < 0.0)
		return;
	if(w == s->width && h == s->height)
		return;
	if(w > 0)
		s->width = w;
	if(h > 0)
		s->height = h;
	GLfloat scene_vertex[8] = {
		0.0, 0.0,
		s->width, 0.0,
		0.0, s->height,
		s->width, s->height
	};

	glBindBuffer(GL_ARRAY_BUFFER, s->buffers[vertex_buffer_type]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 8, scene_vertex);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	s->frustum_width = fw;
	s->frustum_height = fh;
}

