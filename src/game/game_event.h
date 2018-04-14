#ifndef KARIN_GAME_EVENT_H
#define KARIN_GAME_EVENT_H

#include "nl_gl.h"
#include "nl_event.h"
#include "game/character.h"

typedef struct _Game_Map_Event
{
	NETLizard_Event *event;
	int event_count;
} Game_Map_Event;

extern Game_Map_Event *event;

// 检测是否需要处理地图物品事件，结果发送到state数组
// state数组元素 -1 不处理 0 关闭 1 打开
void Event_ProcessMapItemTriggerEvent(const GL_NETLizard_3D_Model *map_model, NETLizard_Event *event, int event_count, game_character *gamer, int *state);
// 根据state数组，处理地图物品事件
void Event_HandleMapItemTriggerEvent(GL_NETLizard_3D_Model *map_model, NETLizard_Event *event, int event_count, long long time, int *state);
// 检测并处理角色触发的地图事件
void Event_HandleCharacterTriggerEvent(GL_NETLizard_3D_Model *map_model, NETLizard_Event *event, int event_count, game_character *gamer, long long time);
// 加载事件
Game_Map_Event * Event_LoadEvent(const char *file, game_name game, int level);
void Event_FreeEvent(Game_Map_Event *event);

#endif
