#include "game_event.h"
#include "nl_algo.h"
#include "math3d/algo.h"

#include <stdlib.h>
#include <string.h>

Game_Map_Event *event = NULL;

void Event_ProcessMapItemTriggerEvent(const GL_NETLizard_3D_Model *map_model, NETLizard_Event *event, int event_count, game_character *gamer, int *state)
{
	if(!map_model || event_count == 0 || event == NULL || !gamer || !state)
		return;
	if(gamer->health == health_death_type)
		return;
	int e;
	for(e = 0; e < event_count; e++)
	{
		if(state[e] == 1)
			continue;
		if(event[e].event_type == Event_DoorV)
		{
			nl_vector3_s pos = {gamer->position[0], gamer->position[1], gamer->position[2]};
			GL_NETLizard_3D_Item_Mesh *model = map_model->item_meshes + event[e].doorv_event.item_id;
			bound_s aabb = {
				{model->item_mesh.ortho[3] + model->pos[0] - gamer->width, model->item_mesh.ortho[4] + model->pos[1] - gamer->width, 0},
				{model->item_mesh.ortho[0] + model->pos[0] + gamer->width, model->item_mesh.ortho[1] + model->pos[1] + gamer->width, 0}
			};
			if(Math3D_PointInAABB2D(&pos, &aabb) || (gamer->collision_item != -1 && event[e].doorv_event.item_id == gamer->collision_item))
			{
				state[e] = 1;
			}
			else
			{
				if(state[e] == -1)
					state[e] = 0;
			}
		}
		else if(event[e].event_type == Event_Double_DoorV)
		{
			nl_vector3_s pos = {gamer->position[0], gamer->position[1], gamer->position[2]};
			GL_NETLizard_3D_Item_Mesh *model = map_model->item_meshes + event[e].double_doorv_event.item_id;
			GL_NETLizard_3D_Item_Mesh *model2 = map_model->item_meshes + event[e].double_doorv_event.item_id_pair;
			nl_vector3_s minv = {0.0, 0.0, 0.0};
			nl_vector3_s maxv = {0.0, 0.0, 0.0};
			minv.x = KARIN_MIN(model->item_mesh.ortho[3] + model->pos[0] - gamer->width, model2->item_mesh.ortho[3] + model2->pos[0] - gamer->width);
			minv.y = KARIN_MIN(model->item_mesh.ortho[4] + model->pos[1] - gamer->width, model2->item_mesh.ortho[4] + model2->pos[1] - gamer->width);
			minv.z = KARIN_MIN(model->item_mesh.ortho[5] + model->pos[2], model2->item_mesh.ortho[5] + model2->pos[2]);
			maxv.x = KARIN_MAX(model->item_mesh.ortho[0] + model->pos[0] + gamer->width, model2->item_mesh.ortho[0] + model2->pos[0] + gamer->width);
			maxv.y = KARIN_MAX(model->item_mesh.ortho[1] + model->pos[1] + gamer->width, model2->item_mesh.ortho[1] + model2->pos[1] + gamer->width);
			maxv.z = KARIN_MAX(model->item_mesh.ortho[2] + model->pos[2], model2->item_mesh.ortho[2] + model2->pos[2]);
			bound_s aabb = {minv, maxv};
			if(Math3D_PointInAABB(&pos, &aabb) || (gamer->collision_item != -1 && (event[e].double_doorv_event.item_id == gamer->collision_item || event[e].double_doorv_event.item_id_pair == gamer->collision_item)))
			{
				state[e] = 1;
			}
			else
			{
				if(state[e] == -1)
					state[e] = 0;
			}
		}
		else if(event[e].event_type == Event_Double_DoorH)
		{
			nl_vector3_s pos = {gamer->position[0], gamer->position[1], gamer->position[2]};
			GL_NETLizard_3D_Item_Mesh *model = map_model->item_meshes + event[e].double_doorh_event.item_id;
			GL_NETLizard_3D_Item_Mesh *model2 = map_model->item_meshes + event[e].double_doorh_event.item_id_pair;
			nl_vector3_s minv = {0.0, 0.0, 0.0};
			nl_vector3_s maxv = {0.0, 0.0, 0.0};
			minv.x = KARIN_MIN(model->item_mesh.ortho[3] + model->pos[0] - gamer->width, model2->item_mesh.ortho[3] + model2->pos[0] - gamer->width);
			minv.y = KARIN_MIN(model->item_mesh.ortho[4] + model->pos[1] - gamer->width, model2->item_mesh.ortho[4] + model2->pos[1] - gamer->width);
			minv.z = KARIN_MIN(model->item_mesh.ortho[5] + model->pos[2], model2->item_mesh.ortho[5] + model2->pos[2]);
			maxv.x = KARIN_MAX(model->item_mesh.ortho[0] + model->pos[0] + gamer->width, model2->item_mesh.ortho[0] + model2->pos[0] + gamer->width);
			maxv.y = KARIN_MAX(model->item_mesh.ortho[1] + model->pos[1] + gamer->width, model2->item_mesh.ortho[1] + model2->pos[1] + gamer->width);
			maxv.z = KARIN_MAX(model->item_mesh.ortho[2] + model->pos[2], model2->item_mesh.ortho[2] + model2->pos[2]);
			bound_s aabb = {minv, maxv};
			if(Math3D_PointInAABB(&pos, &aabb) || (gamer->collision_item != -1 && (event[e].double_doorh_event.item_id == gamer->collision_item || event[e].double_doorh_event.item_id_pair == gamer->collision_item)))
			{
				state[e] = 1;
			}
			else
			{
				if(state[e] == -1)
					state[e] = 0;
			}
		}
		else if(event[e].event_type == Event_Elevator)
		{
			nl_vector3_s pos = {gamer->position[0], gamer->position[1], gamer->position[2]};
			GL_NETLizard_3D_Item_Mesh *model = map_model->item_meshes + event[e].elevator_event.item_id;
			bound_s aabb = {
				{model->item_mesh.ortho[3] + model->pos[0], model->item_mesh.ortho[4] + model->pos[1], event[e].elevator_event.min_z},
				{model->item_mesh.ortho[0] + model->pos[0], model->item_mesh.ortho[1] + model->pos[1], event[e].elevator_event.max_z + 2}
			};
			if(Math3D_PointInAABB(&pos, &aabb))
			{
				state[e] = 1;
			}
			else
			{
				//NETLizard_HandleElevatorEvent(map_model, &(event[e].elevator_event), 0);
			}
		}
		else if(event[e].event_type == Event_Fan)
		{
			state[e] = 1;
		}
		else if(event[e].event_type == Event_Prop)
		{
			state[e] = 1;
		}
		else if(event[e].event_type == Event_Machine)
		{
			nl_vector3_s pos = {gamer->position[0], gamer->position[1], gamer->position[2] + gamer->height};

			GL_NETLizard_3D_Item_Mesh *model = map_model->item_meshes + event[e].machine_event.machine_gun_event.item_id;
			nl_vector3_s pos2 = {model->pos[0], model->pos[1], model->pos[2] - 125};
			float d = 0.0;
			int r = Algo_PointCanViewPointInNETLizard3DMap(map_model, &pos, &pos2, &d);
			if(r && (event[e].machine_event.machine_gun_event.range < 0 || d <= event[e].machine_event.machine_gun_event.range))
			{
				state[e] = 1;
				event[e].machine_event.target_x = gamer->position[0];
				event[e].machine_event.target_y = gamer->position[1];
				event[e].machine_event.target_z = gamer->position[2] + gamer->height;
			}
			else
			{
				if(state[e] == -1)
					state[e] = 0;
			}
		}
	}
}

void Event_HandleMapItemTriggerEvent(GL_NETLizard_3D_Model *map_model, NETLizard_Event *event, int event_count, float delta, int *state)
{
	if(!map_model || event_count == 0 || event == NULL || !state)
		return;
	int e;
	for(e = 0; e < event_count; e++)
	{
		if(event[e].event_type == Event_Fan)
		{
			NETLizard_HandleFanEvent(map_model, &(event[e].fan_event), 1, delta);
		}
		else if(event[e].event_type == Event_Prop)
		{
			NETLizard_HandlePropEvent(map_model, &(event[e].prop_event), 1, delta);
		}
		else if(event[e].event_type == Event_DoorV)
		{
			if(state[e] == 1)
			{
				NETLizard_HandleDoorEvent(map_model, &(event[e].doorv_event), 1, delta);
			}
			else if(state[e] == 0)
			{
				NETLizard_HandleDoorEvent(map_model, &(event[e].doorv_event), 0, delta);
			}
		}
		else if(event[e].event_type == Event_Double_DoorV)
		{
			if(state[e] == 1)
			{
				NETLizard_HandleDoubleVDoorEvent(map_model, &(event[e].double_doorv_event), 1, delta);
			}
			else if(state[e] == 0)
			{
				NETLizard_HandleDoubleVDoorEvent(map_model, &(event[e].double_doorv_event), 0, delta);
			}
		}
		else if(event[e].event_type == Event_Double_DoorH)
		{
			if(state[e] == 1)
			{
				NETLizard_HandleDoubleHDoorEvent(map_model, &(event[e].double_doorh_event), 1, delta);
			}
			else if(state[e] == 0)
			{
				NETLizard_HandleDoubleHDoorEvent(map_model, &(event[e].double_doorh_event), 0, delta);
			}
		}
		else if(event[e].event_type == Event_Elevator)
		{
			if(state[e] == 1)
			{
				NETLizard_HandleElevatorEvent(map_model, &(event[e].elevator_event), 1, delta);
			}
			else
			{
				//NETLizard_HandleElevatorEvent(map_model, &(event[e].elevator_event), 0, delta);
			}
		}
		else if(event[e].event_type == Event_Machine)
		{
			if(state[e] == 1)
			{
				NETLizard_HandleMachineEvent(map_model, &(event[e].machine_event), 1, 1, delta);
			}
			else if(state[e] == 0)
			{
				NETLizard_HandleMachineEvent(map_model, &(event[e].machine_event), 0, 0, delta);
			}
		/*
			 else
			 NETLizard_HandleMachineEvent(map_model, &(event[e].machine_event), 1, 0, 0.0, 0.0, 0.0);
			 */
		}
	}
}

void Event_HandleCharacterTriggerEvent(GL_NETLizard_3D_Model *map_model, NETLizard_Event *event, int event_count, game_character *gamer, float delta)
{
	if(!map_model || event_count == 0 || event == NULL || !gamer)
		return;
	if(gamer->health == health_death_type)
		return;
	int e;
	for(e = 0; e < event_count; e++)
	{
		if(event[e].event_type == Event_Portal && gamer->collision_item != -1 && event[e].portal_event.item_id == gamer->collision_item)
		{
			if(event[e].portal_event.mask & 1)
				gamer->position[0] = event[e].portal_event.xt;
			if(event[e].portal_event.mask & (1 << 1))
				gamer->position[1] = event[e].portal_event.yt;
			if(event[e].portal_event.mask & (1 << 2))
				gamer->position[2] = event[e].portal_event.zt - (2293760 >> 16);
		}
	}
}

Game_Map_Event * Event_LoadEvent(const char *file, game_name game, int level)
{
	if(!file)
		return NULL;
	Game_Map_Event *ev = NEW(Game_Map_Event);
	ZERO(ev, Game_Map_Event);
	if(level != -1)
	{
		ev->event = NETLizard_LoadEventFile(file, game, level, &ev->event_count);
		if(!ev->event || ev->event_count == 0)
		{
			free(ev);
			return NULL;
		}
		return ev;
	}
	return NULL;
}

void Event_FreeEvent(Game_Map_Event *ev)
{
	if(!ev)
		return;
	NETLizard_DeleteEvent(ev->event, ev->event_count);
	ev->event = NULL;
	ev->event_count = 0;
}
