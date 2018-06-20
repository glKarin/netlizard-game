#ifndef KARIN_FIRST_PERSON_H
#define KARIN_FIRST_PERSON_H

#include "game_util.h"

typedef enum _first_person_hand_type
{
	fp_right_hand_type = 0,
	fp_left_hand_type,
	fp_mid_hand_type
} first_person_hand_type;

typedef enum _first_person_status_type
{
	fp_fixed_status_type = 0,
	fp_reset_status_type,
	fp_idle_status_type,
	fp_move_status_type,
	fp_turnup_status_type,
	fp_turndown_status_type,
	fp_turnleft_status_type,
	fp_turnright_status_type,
	fp_fight_status_type
} first_person_status_type;

typedef struct _first_person
{
	scene_2d fp;
	float x;
	float y;
	float z;
	first_person_hand_type hand;
	first_person_status_type status;
	float x_offset;
	float y_offset;
	float x_offset_target;
	float y_offset_target;
	int x_com;
	int y_com;
	float x_min_limit;
	float y_min_limit;
	float x_max_limit;
	float y_max_limit;
	float out_speed;
	float in_speed;
	float speed;
} first_person;

first_person * new_first_person(first_person *fp, first_person_hand_type hand, float x, float y, float z, float xmin, float xmax, float ymin, float ymax, float os, float is, float s);
void delete_first_person(first_person *fp);
void UI_UpdateFirstPerson(first_person *fp, float delta);
void UI_RenderFirstPerson(first_person *fp);
void UI_SetFirstPersonTexture(first_person *fp, texture *tex);
void UI_UpdateFirstPersonStatus(first_person *fp, first_person_status_type s);

#endif
