#include "game_mode.h"
#include "nl_algo.h"
#include "game_event.h"
#include "game/particle.h"
#include "game_sound.h"
#include "game_setting.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

static int Mode_CheckGameOver(death_game_mode *m);

death_game_mode * new_death_game_mode(death_game_mode *mode, person_mode pm, game_mode_win_type win_type, int s, int point, game_mode_relive_type relive_type, int relive_time, int level)
{
	RETURN_PTR(m, mode, death_game_mode)

	m -> mode = death_game_type;
	m -> state = ready_game_type;
	m -> p_mode = pm;
	m -> win_type = win_type;
	m -> finish_reason = win_no_type;
	m -> relive_type = relive_type;
	m -> time_limit = s;
	m -> point_target = point;
	m -> relive_time = relive_time;
	m -> level = level;
	m -> max_point = 0;

	m -> start_time = 0;
	m -> time = 0;
	m -> game_time = 0;
	m -> interval_time = 0;
	m -> group_count = 0;
	m -> group_id = NULL;
	m -> group_person_count = NULL;
	m -> group_character = NULL;
	m -> group_point = NULL;
	m -> relive_scene = NULL;

	m -> characters = NULL;
	m -> character_count = 0;
	m -> current_character = 0;

	m -> map = NULL;
	m -> event = NULL;

	new_list_template(&m -> particle_list, sizeof(particle));
	new_list_template(&m -> bullet_list, sizeof(bullet));
	new_list_template(&m -> sound_list, sizeof(sound_effect));
	return m;
}

void Mode_InitDeathGameMode(death_game_mode *m, game_character *characters, int character_count, GL_NETLizard_3D_Model *model, Game_Map_Event *event)
{
	if(!m || !model || !characters)
		return;
	if(m -> state != ready_game_type)
		return;
	srand(time(NULL));
	m -> start_time = Game_GetGameTime();
	m -> game_time = m -> start_time;

	m -> characters = characters;
	m -> character_count = character_count;

	if(m -> characters)
	{
		int i;
		for(i = 0; i < m -> character_count; i++)
		{
			m -> characters[i].ai.time = m -> game_time;
			m -> characters[i].animation.last_play_time = m -> game_time;
		}
		int *group = NEW_II(int, m -> character_count);
		int g = 0;
		for(i = 0; i < m -> character_count; i++)
		{
			group[i] = -1;
		}
		for(i = 0; i < m -> character_count; i++)
		{
			int j;
			for(j = 0; j < g; j++)
			{
				if(group[j] == -1)
					break;
				if(group[j] == m -> characters[i].group)
					break;
			}
			if(j == g)
			{
				group[g] = m -> characters[i].group;
				g++;
			}
		}
		m -> group_count = g;
		m -> group_id = NEW_II(int, g);
		m -> group_person_count = NEW_II(int, g);
		m -> group_character = NEW_II(game_character **, g);
		m -> group_point = NEW_II(int, g);
		for(i = 0; i < m -> group_count; i++)
		{
			m -> group_id[i] = group[i];
			m -> group_point[i] = 0;
			int c = 0;
			int j;
			for(j = 0; j < m -> character_count; j++)
			{
				if(m -> characters[j].group == m -> group_id[i])
					c++;
			}
			m -> group_person_count[i] = c;
			m -> group_character[i] = NEW_II(game_character *, c);
			c = 0;
			for(j = 0; j < m -> character_count; j++)
			{
				if(m -> characters[j].group == m -> group_id[i])
				{
					m -> group_character[i][c] = m -> characters + j;
					c++;
				}
			}
		}
		free(group);
	}

	m -> map = model;
	m -> event = event;
	if(m -> event)
	{
		int i;
		for(i = 0; i < m -> event -> event_count; i++)
		{
			m -> event -> event[i].any_event.time = m -> game_time;
		}
	}
}

void Mode_DeathGameModeMain(death_game_mode *m, int fps)
{
	if(!m)
		return;
	if(m -> state != running_game_type)
		return;
	if(!Mode_CheckDeathGameMode(m))
		return;
	if(Mode_CheckGameOver(m))
		return;

	m -> game_time = Game_GetGameTime();
	m -> time = (m -> game_time - m -> start_time - m -> interval_time) / 1000;
	
	List_DeleteAll(&m -> sound_list);
	unsigned int k;
	for(k = 0; k < m -> particle_list.count;)
	{
		particle *p = List_GetDataByIndexT(&m -> particle_list, k, particle);
		if(p)
		{
			Particle_UpdateParticle(m -> map, p, m -> game_time);
			if(p -> finished)
			{
				List_DeleteOneByIndex(&m -> particle_list, k);
			}
			else
			{
				k++;
			}
		}
		else
		{
			k++;
		}
	}

	for(k = 0; k < m -> bullet_list.count;)
	{
		bullet *b = List_GetDataByIndexT(&m -> bullet_list, k, bullet);
		if(b)
		{
			if(b -> finished == 1)
			{
				List_DeleteOneByIndex(&m -> bullet_list, k);
			}
			else
			{
				k++;
			}
		}
		else
		{
			k++;
		}
	}

	Game_AIRelive(m -> map, m -> characters, 0, m -> character_count, m -> relive_time, m -> game_time);

	Game_HandleCharacterAction(m -> map, m -> characters, 0, m -> character_count, m -> game_time);

	char b = 0;
	int s = (!Setting_GetSettingBoolean(OPEN_GAME_MUSIC_SETTING, &b) || b) ? 1 : 0;

	Game_AttackEvent(m -> map, m -> characters, m -> current_character, 0, m -> character_count, m -> game_time, &m -> particle_list, &m -> bullet_list, s ? &m -> sound_list : NULL);

	for(k = 0; k < m -> bullet_list.count; k++)
	{
		bullet *b = List_GetDataByIndexT(&m -> bullet_list, k, bullet);
		if(b)
		{
			if(b -> finished == 0 && b -> type != no_bullet_type)
			{
				int type = b -> type == normal_bullet_type ? track_particle_type : (b -> type == grenade_bullet_type ? grenade_particle_type : track2_particle_type);
				particle p = Particle_MakeParticle(type, fixed_particle_type, b -> position[0], b -> position[1], b -> position[2], b -> x_dir, b -> y_dir, 0.0, 0.0, 0.0, m -> game_time, 1000, GL_FALSE);
				p.finished = GL_TRUE;
				List_PushBack(&m -> particle_list, &p);
			}
		}
	}

	int i;
	for(i = 0; i < m -> group_count; i++)
	{
		m -> group_point[i] = 0;
		int j;
		for(j = 0; j < m -> group_person_count[i]; j++)
		{
			m -> group_point[i] += m -> group_character[i][j] -> score.kill;
		}
	}

	if(m -> event)
	{
		int *state = NEW_II(int, m -> event -> event_count);
		int i; // -1 no trigger 0 close 1 open
		for(i = 0; i < m -> event -> event_count; i++)
		{
			state[i] = -1;
		}

		for(i = 0; i < m -> character_count; i++)
			Event_ProcessMapItemTriggerEvent(m -> map, m -> event -> event, m -> event -> event_count, m -> characters + i, state);

		Event_HandleMapItemTriggerEvent(m -> map, m -> event -> event, m -> event -> event_count, m -> game_time, state);

		for(i = 0; i < m -> character_count; i++)
			Event_HandleCharacterTriggerEvent(m -> map, m -> event -> event, m -> event -> event_count, m -> characters + i, m -> game_time);

		free(state);
		for(i = 0; i < m -> event -> event_count; i++)
		{
			m -> event -> event[i].any_event.time = m -> game_time;
		}
	}

	Game_UpdateAIAnimation(m -> characters, 0, m -> character_count, m -> game_time, fps);
	for(i = 0; i < m -> character_count; i++)
		m -> characters[i].ai.time = m -> game_time;
}

void delete_death_game_mode(death_game_mode *mode)
{
	if(!mode)
		return;
	int i;
	for(i = 0; i < mode -> group_count; i++)
	{
		free(mode -> group_character[i]);
	}
	FREE_PTR(mode -> group_character)
	FREE_PTR(mode -> group_id)
	FREE_PTR(mode -> group_person_count)
	FREE_PTR(mode -> group_point)

	mode -> characters = NULL;
	mode -> character_count = 0;

	mode -> event = NULL;

	mode -> map = NULL;

	List_DeleteAll(&mode -> particle_list);
	List_DeleteAll(&mode -> bullet_list);
	List_DeleteAll(&mode -> sound_list);
}

int Mode_CheckDeathGameMode(const death_game_mode *m)
{
	if(!m)
		return 0;
#define CHECK_IF_TRUE_RETURN_FALSE(c) if(c) return 0;
#define CHECK_IF_NULL_RETURN_FALSE(c) if((c) == NULL) return 0;
#define CHECK_IF_NONE_RETURN_FALSE(c) if((c) == 0) return 0;
	CHECK_IF_TRUE_RETURN_FALSE(m -> mode != death_game_type)
	CHECK_IF_NULL_RETURN_FALSE(m -> group_id)
	CHECK_IF_NULL_RETURN_FALSE(m -> group_person_count)
	CHECK_IF_NULL_RETURN_FALSE(m -> group_point)
	CHECK_IF_NULL_RETURN_FALSE(m -> characters)
	CHECK_IF_NONE_RETURN_FALSE(m -> character_count)
	CHECK_IF_NULL_RETURN_FALSE(m -> map)
	// CHECK_IF_NULL_RETURN_FALSE(m -> event)
	
	return 1;
#undef CHECK_IF_TRUE_RETURN_FALSE
#undef CHECK_IF_NULL_RETURN_FALSE
#undef CHECK_IF_NONE_RETURN_FALSE
}

void Mode_PauseGameMode(death_game_mode *m)
{
	if(!m)
		return;
	if(m -> state != running_game_type)
		return;
	m -> state = pause_game_type;
}

void Mode_ContinueGameMode(death_game_mode *m)
{
	if(!m)
		return;
	if(m -> state != pause_game_type)
		return;
	long long time = Game_GetGameTime();
	long long interval = time - m -> game_time;
	m -> interval_time += interval;
	m -> game_time = m -> time;
	m -> time = (m -> game_time - m -> start_time - m -> interval_time) / 1000;
	if(m -> characters)
	{
		int i;
		for(i = 0; i < m -> character_count; i++)
		{
			m -> characters[i].ai.time += interval;
			m -> characters[i].animation.last_play_time += interval;
		}
	}
	if(m -> event)
	{
		int i;
		for(i = 0; i < m -> event -> event_count; i++)
		{
			m -> event -> event[i].any_event.time += interval;
		}
	}
	unsigned int k;
	for(k = 0; k < m -> particle_list.count; k++)
	{
		particle *p = List_GetDataByIndexT(&m -> particle_list, k, particle);
		if(p)
			p -> time += interval;
	}
	for(k = 0; k < m -> bullet_list.count; k++)
	{
		bullet *b = List_GetDataByIndexT(&m ->	bullet_list, k,	bullet);
		if(b)
			b -> time += interval;
	}
	m -> state = running_game_type;
}

void Mode_ResetGameMode(death_game_mode *m)
{
	if(!m)
		return;
	srand(time(NULL));
	m -> finish_reason = win_no_type;
	m -> start_time = Game_GetGameTime();
	m -> interval_time = 0;
	m -> game_time = m -> start_time;
	m -> time = 0;

	if(m -> characters)
	{
		int i;
		for(i = 0; i < m -> character_count; i++)
		{
			m -> characters[i].ai.time = m -> game_time;
			m -> characters[i].animation.last_play_time = m -> game_time;
		}

		for(i = 0; i < m -> group_count; i++)
		{
			int j;
			for(j = 0; j < m -> group_person_count[i]; j++)
			{
				m -> group_character[i][j] -> score.kill_character = -1;
				m -> group_character[i][j] -> score.killed_character = -1;
				m -> group_character[i][j] -> score.kill = 0;
				m -> group_character[i][j] -> score.death = 0;
				m -> group_character[i][j] -> score.assist = 0;
			}
		}
	}

	if(m -> event)
	{
		int i;
		for(i = 0; i < m -> event -> event_count; i++)
		{
			m -> event -> event[i].any_event.time = m -> game_time;
		}
	}
	List_DeleteAll(&m -> particle_list);
	List_DeleteAll(&m -> bullet_list);
	List_DeleteAll(&m -> sound_list);

	m -> state = running_game_type;
}

int Mode_CheckGameOver(death_game_mode *m)
{
	if(!m)
		return 0;
	if(m -> state != running_game_type)
		return 0;
	switch(m -> win_type)
	{
		case win_point_type:
			if(m -> characters && m -> character_count > 0)
			{
				int i;
				for(i = 0; i < m -> group_count; i++)
				{
					int sum = 0;
					int j;
					for(j = 0; j < m -> group_person_count[i]; j++)
					{
						sum += m -> group_character[i][j] -> score.kill;
					}
					if(sum >= m -> point_target)
					{
						m -> state = finish_game_type;
						m -> finish_reason = win_point_type;
						return 1;
					}
				}
			}
			if(m -> time_limit != -1)
			{
				if(m -> time > m -> time_limit)
				{
					m -> state = finish_game_type;
					m -> finish_reason = win_time_type;
					return 1;
				}
			}
			break;
		case win_time_type:
			if(m -> time_limit != -1)
			{
				if(m -> time > m -> time_limit)
				{
					m -> state = finish_game_type;
					m -> finish_reason = win_time_type;
					return 1;
				}
			}
			break;
		case win_ace_type:
			break;
		case win_no_type:
		default:
			break;
	}
	return 0;
}
