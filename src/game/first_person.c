#include "first_person.h"

#include "nl_std.h"

#include <stdlib.h>
#include <string.h>

first_person * new_first_person(first_person *fp, first_person_hand_type hand, float x, float y, float z, float xmin, float xmax, float ymin, float ymax, float os, float is, float s)
{
	RETURN_PTR(f, fp, first_person)

	anchor_type a;
	if(hand == fp_left_hand_type)
		a = (left_bottom_anchor_type);
	else
		a = (right_bottom_anchor_type);

	GLfloat color[] = {1.0, 1.0, 1.0, 0.0};
	new_scene_2d(&f->fp, 0, 0, 0, 0, 1, a, color, NULL);
	f->status = fp_idle_status_type;
	f->hand = hand;
	f->x_offset = 0;
	f->y_offset = 0;
	f->x_offset_target = 0;
	f->y_offset_target = 0;
	f->x_com = 0;
	f->y_com = 0;
	f->x = x;
	f->y = y;
	f->z = z;
	f->x_min_limit = xmin;
	f->y_min_limit = ymin;
	f->x_max_limit = xmax;
	f->y_max_limit = ymax;
	f->out_speed = os;
	f->in_speed = is;
	f->speed = s;

	return f;
}

void delete_first_person(first_person *fp)
{
	if(!fp)
		return;
	delete_scene_2d(&fp->fp);
}

void UI_UpdateFirstPerson(first_person *fp, float delta)
{
	if(!fp)
		return;
	switch(fp->status)
	{
		case fp_turnright_status_type:
			if(fp->x_offset > fp->x_offset_target)
				fp->x_offset += fp->out_speed * delta * fp->x_com;
			if(fp->x_offset < fp->x_offset_target)
				fp->x_offset = fp->x_offset_target;
			break;
		case fp_turnleft_status_type:
			if(fp->x_offset < fp->x_offset_target)
				fp->x_offset += fp->out_speed * delta * fp->x_com;
			if(fp->x_offset > fp->x_offset_target)
				fp->x_offset = fp->x_offset_target;
			break;
		case fp_turndown_status_type:
			if(fp->y_offset < fp->y_offset_target)
				fp->y_offset += fp->out_speed * delta * fp->y_com;
			if(fp->y_offset > fp->y_offset_target)
				fp->y_offset = fp->y_offset_target;
			break;
		case fp_turnup_status_type:
			if(fp->y_offset > fp->y_offset_target)
				fp->y_offset += fp->out_speed * delta * fp->y_com;
			if(fp->y_offset < fp->y_offset_target)
				fp->y_offset = fp->y_offset_target;
			break;
		case fp_reset_status_type:
			if(fp->x_com == -1)
			{
				if(fp->x_offset > fp->x_offset_target)
					fp->x_offset += fp->in_speed * delta * fp->x_com;
				if(fp->x_offset < fp->x_offset_target)
					fp->x_offset = fp->x_offset_target;
			}
			else if(fp->x_com == 1)
			{
				if(fp->x_offset < fp->x_offset_target)
					fp->x_offset += fp->in_speed * delta * fp->x_com;
				if(fp->x_offset > fp->x_offset_target)
					fp->x_offset = fp->x_offset_target;
			}
			if(fp->y_com == 1)
			{
				if(fp->y_offset < fp->y_offset_target)
					fp->y_offset += fp->in_speed * delta * fp->y_com;
				if(fp->y_offset > fp->y_offset_target)
					fp->y_offset = fp->y_offset_target;
			}
			else if(fp->y_com == -1)
			{
				if(fp->y_offset > fp->y_offset_target)
					fp->y_offset += fp->in_speed * delta * fp->y_com;
				if(fp->y_offset < fp->y_offset_target)
					fp->y_offset = fp->y_offset_target;
			}

			if(fp->x_offset == fp->x_offset_target && fp->y_offset == fp->y_offset_target)
				fp->status = fp_idle_status_type;
			break;
		case fp_move_status_type:
			if(fp->y_com == 1)
			{
				if(fp->y_offset == fp->y_offset_target)
				{
					fp->y_com = -1;
					fp->y_offset_target = fp->y_min_limit;
				}
				else
				{
					if(fp->y_offset < fp->y_offset_target)
						fp->y_offset += fp->in_speed * delta * fp->y_com;
					if(fp->y_offset > fp->y_offset_target)
						fp->y_offset = fp->y_offset_target;
				}
			}
			else if(fp->y_com == -1)
			{
				if(fp->y_offset == fp->y_offset_target)
				{
					fp->y_com = 1;
					fp->y_offset_target = fp->y_max_limit;
				}
				else
				{
					if(fp->y_offset > fp->y_offset_target)
						fp->y_offset += fp->in_speed * delta * fp->y_com;
					if(fp->y_offset < fp->y_offset_target)
						fp->y_offset = fp->y_offset_target;
				}
			}
			break;
		case fp_fight_status_type:
			fp->x_offset = rand() % ((int)(fp->x_max_limit - fp->x_min_limit)) + fp->x_min_limit;
			fp->y_offset = rand() % ((int)(fp->y_max_limit - fp->y_min_limit)) + fp->y_min_limit;
			break;
		case fp_idle_status_type:
			if(fp->x_offset == fp->x_offset_target)
			{
				fp->x_offset_target = rand() % ((int)(fp->x_max_limit - fp->x_min_limit)) + fp->x_min_limit;
				if(fp->x_offset_target > fp->x_offset)
					fp->x_com = 1;
				else if(fp->x_offset_target < fp->x_offset)
					fp->x_com = -1;
			}
			else
			{
				if(fp->x_com == 1)
				{
					if(fp->x_offset < fp->x_offset_target)
						fp->x_offset += fp->speed * fp->x_com * delta;
					if(fp->x_offset > fp->x_offset_target)
						fp->x_offset = fp->x_offset_target;
				}
				else if(fp->x_com == -1)
				{
					if(fp->x_offset > fp->x_offset_target)
						fp->x_offset += fp->speed * fp->x_com * delta;
					if(fp->x_offset < fp->x_offset_target)
						fp->x_offset = fp->x_offset_target;
				}
			}

			if(fp->y_offset == fp->y_offset_target)
			{
				fp->y_offset_target = rand() % ((int)(fp->y_max_limit - fp->y_min_limit)) + fp->y_min_limit;
				if(fp->y_offset_target > fp->y_offset)
					fp->y_com = 1;
				else if(fp->y_offset_target < fp->y_offset)
					fp->y_com = -1;
			}
			else
			{
				if(fp->y_com == 1)
				{
					if(fp->y_offset < fp->y_offset_target)
						fp->y_offset += fp->speed * fp->y_com * delta;
					if(fp->y_offset > fp->y_offset_target)
						fp->y_offset = fp->y_offset_target;
				}
				else if(fp->y_com == -1)
				{
					if(fp->y_offset > fp->y_offset_target)
						fp->y_offset += fp->speed * fp->y_com * delta;
					if(fp->y_offset < fp->y_offset_target)
						fp->y_offset = fp->y_offset_target;
				}
			}
			break;
		default:
			break;
	}
}

void UI_UpdateFirstPersonStatus(first_person *fp, first_person_status_type s)
{
	if(!fp)
		return;
	if(fp->status == s)
		return;
	if(s == fp_idle_status_type && fp->status == fp_reset_status_type)
		return;
	if(s == fp_idle_status_type && (fp->status != fp_idle_status_type))
		fp->status = fp_reset_status_type;
	else
		fp->status = s;
	switch(fp->status)
	{
		case fp_turnleft_status_type:
			fp->x_com = 1;
			fp->x_offset_target = fp->x_max_limit;
			fp->x_offset = 0;
			break;
		case fp_turnright_status_type:
			fp->x_com = -1;
			fp->x_offset_target = fp->x_min_limit;
			fp->x_offset = 0;
			break;
		case fp_turnup_status_type:
			fp->y_com = -1;
			fp->y_offset_target = fp->y_min_limit;
			fp->y_offset = 0;
			break;
		case fp_turndown_status_type:
			fp->y_com = 1;
			fp->y_offset_target = fp->y_max_limit;
			fp->y_offset = 0;
			break;
		case fp_fight_status_type:
			fp->x_com = 0;
			fp->y_com = 0;
			fp->x_offset_target = 0;
			fp->x_offset = 0;
			fp->y_offset_target = 0;
			fp->y_offset = 0;
			break;
		case fp_move_status_type:
			fp->x_com = 0;
			fp->x_offset_target = 0;
			fp->x_offset = 0;
			fp->y_com = -1;
			fp->y_offset_target = fp->y_min_limit;
			fp->y_offset = 0;
			break;
		case fp_reset_status_type:
			if(fp->x_offset != 0)
			{
				if(fp->x_com != 0)
					fp->x_com = -fp->x_com;
				else
					fp->x_com = fp->x_offset > 0.0f ? -1 : 1;
				fp->x_offset_target = 0;
			}
			if(fp->y_offset != 0)
			{
				if(fp->y_com != 0)
					fp->y_com = -fp->y_com;
				else
					fp->y_com = fp->y_offset > 0.0f ? -1 : 1;
				fp->y_offset_target = 0;
			}
			break;
		case fp_idle_status_type:
			fp->x_offset_target = rand() % ((int)(fp->x_max_limit - fp->x_min_limit)) + fp->x_min_limit;
			fp->y_offset_target = rand() % ((int)(fp->y_max_limit - fp->y_min_limit)) + fp->y_min_limit;
			if(fp->x_offset_target > fp->x_offset)
				fp->x_com = 1;
			else if(fp->x_offset_target < fp->x_offset)
				fp->x_com = -1;
			if(fp->y_offset_target > fp->y_offset)
				fp->y_com = 1;
			else if(fp->y_offset_target < fp->y_offset)
				fp->y_com = -1;
			break;
		default:
			break;
	}
}

void UI_RenderFirstPerson(first_person *fp)
{
	if(!fp)
		return;
	if(!fp->fp.tex)
		return;
	glPushMatrix();
	{
		glTranslatef(fp->x, fp->y, fp->z);
		glTranslatef(fp->x_offset, fp->y_offset, 0.0);
		UI_RenderScene2D(&fp->fp);
	}
	glPopMatrix();
}

void UI_SetFirstPersonTexture(first_person *fp, texture *tex)
{
	if(!fp)
		return;
	fp->fp.tex = tex;
	if(fp->fp.tex)
		UI_ResizeScene2D(&fp->fp, fp->fp.tex->width, fp->fp.tex->height);
}
