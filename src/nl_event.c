#include "nl_event.h"
#include "gl_util.h"
#include "nl_std.h"
#include "netlizard/nl_util.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

GLvoid NETLizard_HandleDoorEvent(GL_NETLizard_3D_Model *map_model, DoorV_Event *event, GLint state, GLfloat per)
{
	if(!map_model || !event)
		return;
	if(event->handle)
		return;
	if(event->item_id >= (GLint)map_model->item_count)
		return;
	if(state == 1 && event->progress == 100)
		return;
	if(state == 0 && event->progress == 0)
		return;
	GLfloat unit = event->unit * per;
	GLfloat progress = state ? event->progress + 100.0 * unit : event->progress - 100.0 * unit;
	if(progress < 0.0)
	{
		progress = 0.0;
	}
	else if(progress > 100.0)
	{
		progress = 100.0;
	}
	if(progress == event->progress)
		return;
	GL_NETLizard_3D_Item_Mesh *model = map_model->item_meshes + (event->item_id);
	if(!model)
	{
		event->progress = progress;
		return;
	}
	GLfloat h = model->item_mesh.ortho[2] - model->item_mesh.ortho[5];
	h *= ((progress - event->progress) / 100.0);
	event->progress = progress;
	model->pos[2] += h;
}

GLvoid NETLizard_HandleDoubleVDoorEvent(GL_NETLizard_3D_Model *map_model, Double_DoorV_Event *event, GLint state, GLfloat per)
{
	if(!map_model || !event)
		return;
	if(event->handle)
		return;
	GLint i = event->invert ? event->item_id_pair : event->item_id;
	GLint j = event->invert ? event->item_id : event->item_id_pair;
	if(i >= (GLint)map_model->item_count)
		return;
	if(j >= (GLint)map_model->item_count)
		return;
	if(state == 1 && event->progress == 100)
		return;
	if(state == 0 && event->progress == 0)
		return;
	GLfloat unit = event->unit * per;
	GLfloat progress = state ? event->progress + 100.0 * unit : event->progress - 100.0 * unit;
	if(progress < 0.0)
	{
		progress = 0.0;
	}
	else if(progress > 100.0)
	{
		progress = 100.0;
	}
	if(progress == event->progress)
		return;
	GL_NETLizard_3D_Item_Mesh *model = map_model->item_meshes + i;
	if(!model)
	{
		event->progress = progress;
		return;
	}
	GLfloat h = model->item_mesh.ortho[2] - model->item_mesh.ortho[5];
	h *= ((progress - event->progress) / 100.0);
	model->pos[2] -= h;
	model = map_model->item_meshes + j;
	if(!model)
	{
		event->progress = progress;
		return;
	}
	h = model->item_mesh.ortho[2] - model->item_mesh.ortho[5];
	h *= ((progress - event->progress) / 100.0);
	model->pos[2] += h;
	event->progress = progress;
}

GLvoid NETLizard_HandleDoubleHDoorEvent(GL_NETLizard_3D_Model *map_model, Double_DoorH_Event *event, GLint state, GLfloat per)
{
	if(!map_model || !event)
		return;
	if(event->handle)
		return;
	GLint i = event->invert ? event->item_id_pair : event->item_id;
	GLint j = event->invert ? event->item_id : event->item_id_pair;
	if(i >= (GLint)map_model->item_count)
		return;
	if(j >= (GLint)map_model->item_count)
		return;
	if(state == 1 && event->progress == 100)
		return;
	if(state == 0 && event->progress == 0)
		return;
	GLfloat unit = event->unit * per;
	GLfloat progress = state ? event->progress + 100.0 * unit : event->progress - 100.0 * unit;
	if(progress < 0.0)
	{
		progress = 0.0;
	}
	else if(progress > 100.0)
	{
		progress = 100.0;
	}
	if(progress == event->progress)
		return;
	GLuint x1 = event->orientation == 1 ? 1 : 0;
	GLuint x2 = event->orientation == 1 ? 4 : 3;
	GLuint y = event->orientation == 1 ? 1 : 0;
	GLint z = event->orientation == 1 ? 1 : -1;
	GL_NETLizard_3D_Item_Mesh *model = map_model->item_meshes + i;
	if(!model)
	{
		event->progress = progress;
		return;
	}
	GLfloat w = model->item_mesh.ortho[x1] - model->item_mesh.ortho[x2];
	w *= ((progress - event->progress) / 100.0);
	model->pos[y] -= w * z;
	model = map_model->item_meshes + j;
	if(!model)
	{
		event->progress = progress;
		return;
	}
	w = model->item_mesh.ortho[x1] - model->item_mesh.ortho[x2];
	w *= ((progress - event->progress) / 100.0);
	model->pos[y] += w * z;
	event->progress = progress;
}

GLvoid NETLizard_HandleElevatorEvent(GL_NETLizard_3D_Model *map_model, Elevator_Event *event, GLint state, GLfloat per)
{
	if(!map_model || !event)
		return;
	if(event->handle)
		return;
	if(event->item_id >= (GLint)map_model->item_count)
		return;
	if(event->state == 3 && event->progress == 100 && state == 0)
		event->state = 1;
	else if(event->state == 0 && event->progress == 0 && state == 0)
		event->state = 2;
	if(event->state == 0 && event->progress == 0 && state == 1)
		event->state = 2;
	else if(event->state == 3 && event->progress == 100 && state == 1)
		event->state = 1;
	GLfloat unit = event->unit * per;
	GLfloat progress = event->state == 2 ? event->progress + 100.0 * unit : event->progress - 100.0 * unit;
	//event->progress = event->state == 2 ? event->progress + 100 * event->unit : event->progress - 100 * event->unit;
	if(progress < 0.0)
	{
		progress = 0.0;
	}
	else if(progress > 100.0)
	{
		progress = 100.0;
	}
	if(progress == 0)
	{
		event->state = 0;
	}
	else if(progress == 100)
	{
		event->state = 3;
	}
	if(progress == event->progress)
		return;
	GL_NETLizard_3D_Item_Mesh *model = map_model->item_meshes + (event->item_id);
	if(!model)
	{
		event->progress = progress;
		return;
	}
	GLfloat h = event->max_z - event->min_z;
	h *= ((progress - event->progress) / 100.0);
	if(event->state == 2 || event->state == 1)
	{
		model->pos[2] += h;
	}
	event->progress = progress;
}

GLvoid NETLizard_HandleFanEvent(GL_NETLizard_3D_Model *map_model, Fan_Event *event, GLint state, GLfloat per)
{
	if(!map_model || !event)
		return;
	if(event->handle)
		return;
	if(event->item_id >= (GLint)map_model->item_count)
		return;
	GL_NETLizard_3D_Item_Mesh *model = map_model->item_meshes + (event->item_id);
	if(!model)
		return;
	GLuint x = event->orientation == 0 ? 1 : 0;
	GLfloat u = event->unit * per;
	GLfloat angle = event->wise == 0 ? -u : u;
	GLfloat f = Algo_FormatAngle(model->angle[x] + angle);
	model->angle[x] = f;
}

GLvoid NETLizard_HandlePropEvent(GL_NETLizard_3D_Model *map_model, Prop_Event *event, GLint state, GLfloat per)
{
	if(!map_model || !event)
		return;
	if(event->handle)
		return;
	if(event->item_id >= (GLint)map_model->item_count)
		return;
	GL_NETLizard_3D_Item_Mesh *model = map_model->item_meshes + (event->item_id);
	if(!model)
		return;
	GLfloat h = event->prop_move_event.max_z - event->prop_move_event.min_z;
	{
		if(event->prop_move_event.state == 3 && event->prop_move_event.progress == 100 && state == 0)
			event->prop_move_event.state = 1;
		else if(event->prop_move_event.state == 0 && event->prop_move_event.progress == 0 && state == 0)
			event->prop_move_event.state = 2;
		if(event->prop_move_event.state == 0 && event->prop_move_event.progress == 0 && state == 1)
			event->prop_move_event.state = 2;
		else if(event->prop_move_event.state == 3 && event->prop_move_event.progress == 100 && state == 1)
			event->prop_move_event.state = 1;
		GLfloat unit = event->prop_move_event.unit * per;
		GLfloat progress = event->prop_move_event.state == 2 ? event->prop_move_event.progress + 100.0 * unit : event->prop_move_event.progress - 100.0 * unit;
		if(progress < 0.0)
		{
			progress = 0.0;
		}
		else if(progress > 100.0)
		{
			progress = 100.0;
		}
		if(progress == 0)
		{
			event->prop_move_event.state = 0;
		}
		else if(progress == 100)
		{
			event->prop_move_event.state = 3;
		}
		if(progress == event->prop_move_event.progress)
			return;
		h *= ((progress - event->prop_move_event.progress) / 100.0);
		if(event->prop_move_event.state == 2 || event->prop_move_event.state == 1)
		{
			model->pos[2] -= h;
		}
		event->prop_move_event.progress = progress;
	}

	{
		GLuint x = event->prop_fan_event.orientation == 0 ? 1 : 0;
		GLfloat u = event->prop_fan_event.unit > 0.0 ? event->prop_fan_event.unit * per : -event->prop_fan_event.unit * per;
		GLfloat angle = event->prop_fan_event.wise == 0 ? -u : u;
		GLfloat f = Algo_FormatAngle(model->angle[x] + angle);
		model->angle[x] = f;
	}
}

GLvoid NETLizard_HandleMachineEvent(GL_NETLizard_3D_Model *map_model, Machine_Event *event, GLint state, int mode, GLfloat per)
{
	if(!map_model || !event)
		return;
	if(event->handle)
		return;
	if(((event->sync == 0) && (state == 0 && event->machine_gun_event.machine_gun_move_event.state == 0)) || event->sync || state)
	{
		if(state == 0 && event->machine_window_event.progress == 0)
			event->machine_window_event.state = 0;
		else if(state == 1 && event->machine_window_event.progress == 100)
			event->machine_window_event.state = 1;
		else
		{
			GLint i = event->machine_window_event.invert ? event->machine_window_event.item_id_pair : event->machine_window_event.item_id;
			GLint j = event->machine_window_event.invert ? event->machine_window_event.item_id : event->machine_window_event.item_id_pair;
			if(i >= (GLint)map_model->item_count)
				return;
			if(j >= (GLint)map_model->item_count)
				return;
			GLfloat unit = event->machine_window_event.unit * per;
			GLfloat progress = state ? event->machine_window_event.progress + 100.0 * unit : event->machine_window_event.progress - 100.0 * unit;
			if(progress < 0.0)
			{
				progress = 0.0;
			}
			else if(progress > 100.0)
			{
				progress = 100.0;
			}
			if(progress != event->machine_window_event.progress)
			{
				GL_NETLizard_3D_Item_Mesh *model = map_model->item_meshes + i;
				if(!model)
				{
					event->machine_window_event.progress = progress;
					return;
				}
				GLfloat w = event->machine_window_event.width;
				w *= ((progress - event->machine_window_event.progress) / 100.0);
				model->pos[1] -= w;
				model = map_model->item_meshes + j;
				if(!model)
				{
					event->machine_window_event.progress = progress;
					return;
				}
				w = event->machine_window_event.width;
				w *= ((progress - event->machine_window_event.progress) / 100.0);
				model->pos[1] += w;
				event->machine_window_event.progress = progress;
			}
		}
	}

	GLuint state2 = event->machine_window_event.state;
	if(state2 == 0 && event->sync == 0)
		return;

	{
		if(event->machine_gun_event.item_id >= (GLint)map_model->item_count)
			return;
		GL_NETLizard_3D_Item_Mesh *model = map_model->item_meshes + (event->machine_gun_event.item_id);
		if(!model)
			return;
		GLfloat h = event->machine_gun_event.machine_gun_move_event.max_z - event->machine_gun_event.machine_gun_move_event.min_z;
		{
			if(state == 1 && event->machine_gun_event.machine_gun_move_event.progress == 100)
				event->machine_gun_event.machine_gun_move_event.state = 1;
			else if(state == 0 && event->machine_gun_event.machine_gun_move_event.progress == 0)
				event->machine_gun_event.machine_gun_move_event.state = 0;
			else
			{
				GLfloat unit = event->machine_gun_event.machine_gun_move_event.unit * per;
				GLfloat progress = state ? event->machine_gun_event.machine_gun_move_event.progress + 100.0 * unit : event->machine_gun_event.machine_gun_move_event.progress - 100.0 * unit;
				if(progress < 0.0)
				{
					progress = 0.0;
				}
				else if(progress > 100.0)
				{
					progress = 100.0;
				}
				if(progress != event->machine_gun_event.machine_gun_move_event.progress)
				{
					h *= ((progress - event->machine_gun_event.machine_gun_move_event.progress) / 100.0);
					model->pos[2] -= h;
					event->machine_gun_event.machine_gun_move_event.progress  = progress;
				}
			}
		}

		GLuint state3 = event->machine_gun_event.machine_gun_move_event.state;
		if(state3 == 0 || state == 0)
			return;

		{
			if(mode)
			{
				nl_vector3_t vp = {event->target_x, event->target_y, event->target_z};
				nl_vector3_t vg = {model->pos[0], model->pos[1], model->pos[2]};
				nl_vector3_t v = Vector3_SubtractVector3(&vg, &vp);
				float xl = v.x;
				float yl = v.y;
				GLfloat f = Algo_FormatAngle(rtoa(atan2(yl, xl)) - 90.0);
				GLuint x = 1;
				model->angle[x] = f;
			}
			else
			{
				GLuint x = 1;
				GLfloat u = event->machine_gun_event.machine_gun_fan_event.unit > 0.0 ? event->machine_gun_event.machine_gun_fan_event.unit * per : -event->machine_gun_event.machine_gun_fan_event.unit * per;
				GLfloat angle = event->machine_gun_event.machine_gun_fan_event.wise == 0 ? -u : u;
				GLfloat f = Algo_FormatAngle(model->angle[x] + angle);
				model->angle[x] = f;
			}
		}
	}
}

NETLizard_Event * NETLizard_LoadEventFile(const char *file, game_name g, int lvl, int *event_count)
{
	static const char Split[] = " ";
	if(!file)
		return NULL;
	array *arr = nlReadFile(file);
	if(!arr)
		return NULL;
	printf("Read NETLizard map item event file: %s\n", file);
	char *data = (char *)(arr->array);
	char ch;
	int i = 0;
	int game = -1;
	int level = -1;
	int count = -1;
	int index = 0;
	NETLizard_Event *event = NULL;
	while(i < arr->length)
	{
		while(isspace((ch = data[i]))) i++;
		if(game == -1 && ch == 'g')
		{
			i += 2;
			int j = 0;
			while(data[i + j] != '\n' && i + j < arr->length)
				j++;
			char *str = NEW_II(char, j + 1);
			memcpy(str, data + i, sizeof(char) * (j + 1));
			str[j] = '\0';
			unsigned int tg = atoi(str);
			free(str);
			j++;
			i += j;
			if(tg == g)
			{
				game = tg;
				//printfi(game);
			}
		}
		else if(game != -1 && level == -1 && ch == 'l')
		{
			i += 2;
			int j = 0;
			while(data[i + j] != '\n' && i + j < arr->length)
				j++;
			char *str = NEW_II(char, j + 1);
			memcpy(str, data + i, sizeof(char) * (j + 1));
			str[j] = '\0';
			int tl = atoi(str);
			free(str);
			j++;
			i += j;
			if(tl == lvl)
			{
				level = tl;
				//printfi(level);
				count = 0;
				j = 0;
				while(data[i + j] == 'e')
				{
					while(data[i + j] != '\n')
						j++;
					count++;
					j++;
					while(isspace(data[i + j]))
						j++;
				}
				//printfi(count);
				if(count == 0)
					break;
				event = NEW_II(NETLizard_Event, count);
			}
		}
		else if(level != -1 && count > 0 && index < count && ch == 'e')
		{
			i += 2;
			int j = 0;
			while(data[i + j] != '\n' && i + j < arr->length)
				j++;
			char *str = NEW_II(char, j + 1);
			memcpy(str, data + i, sizeof(char) * (j + 1));
			str[j] = '\0';
			//printfs(str);
			char *ptr = strtok(str, Split);
			if(strcasecmp(ptr, "vdd") == 0)
			{
				Double_DoorV_Event e = {Event_Double_DoorV, 0, -1, -2, 0.0, 0, 0};
				e.handle = 0;
				if((ptr = strtok(NULL, Split)) != NULL)
					e.item_id = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.item_id_pair = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.unit = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.progress = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.invert = atoi(ptr);
				event[index].double_doorv_event = e;
			}
			else if(strcasecmp(ptr, "hdd") == 0)
			{
				Double_DoorH_Event e = {Event_Double_DoorH, 0, -1, -2, 0.0, 0, 0, 0};
				e.handle = 0;
				if((ptr = strtok(NULL, Split)) != NULL)
					e.item_id = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.item_id_pair = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.unit = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.progress = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.orientation = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.invert = atoi(ptr);
				event[index].double_doorh_event = e;
			}
			else if(strcasecmp(ptr, "fan") == 0)
			{
				Fan_Event e = {Event_Fan, 0, -1, 0, 0, 0, 0.0, 360.0, 0, 0};
				e.handle = 0;
				if((ptr = strtok(NULL, Split)) != NULL)
					e.item_id = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.unit = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.progress = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.wise = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.min_angle = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.max_angle = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.orientation = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.state = atoi(ptr);
				event[index].fan_event = e;
			}
			else if(strcasecmp(ptr, "ele") == 0)
			{
				Elevator_Event e = {Event_Elevator, 0,  -1, 0.0, 0, 0.0, 360.0, 0};
				e.handle = 0;
				if((ptr = strtok(NULL, Split)) != NULL)
					e.item_id = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.unit = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.progress = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.min_z = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.max_z = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.state = atoi(ptr);
				event[index].elevator_event = e;
			}
			else if(strcasecmp(ptr, "vd") == 0)
			{
				DoorV_Event e = {Event_DoorV, 0, -1, 0.0, 0};
				e.handle = 0;
				if((ptr = strtok(NULL, Split)) != NULL)
					e.item_id = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.unit = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.progress = atoi(ptr);
				event[index].doorv_event = e;
			}
			else if(strcasecmp(ptr, "portal") == 0)
			{
				Portal_Event e = {Event_Portal, 0, -1, 0, 0.0, 0.0, 0.0, 0.0, 0.0};
				e.handle = 0;
				if((ptr = strtok(NULL, Split)) != NULL)
					e.item_id = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.mask = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.xt = atoi(ptr) >> 16;
				if((ptr = strtok(NULL, Split)) != NULL)
					e.yt = atoi(ptr) >> 16;
				if((ptr = strtok(NULL, Split)) != NULL)
					e.zt = atoi(ptr) >> 16;
				if((ptr = strtok(NULL, Split)) != NULL)
					e.xr = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.yr = atof(ptr);
				event[index].portal_event = e;
			}
			else if(strcasecmp(ptr, "prop") == 0)
			{
				Prop_Event e = {Event_Prop, 0, -1, {0.0, 0, 0.0, 360.0, 0}, {0, 0, 0, 0.0, 360.0, 0, 0}};
				e.handle = 0;
				if((ptr = strtok(NULL, Split)) != NULL)
					e.item_id = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.prop_move_event.unit = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.prop_move_event.progress = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.prop_move_event.min_z = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.prop_move_event.max_z = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.prop_move_event.state = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.prop_fan_event.unit = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.prop_fan_event.progress = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.prop_fan_event.wise = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.prop_fan_event.min_angle = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.prop_fan_event.max_angle = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.prop_fan_event.orientation = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.prop_fan_event.state = atoi(ptr);
				event[index].prop_event = e;
			}
			else if(strcasecmp(ptr, "machine") == 0)
			{
				Machine_Event e = {Event_Machine, 0, {-1, 500.0, {0.0, 0, 0.0, 360.0, 0}, {0.0, 0, 0, 0.0, 360.0, 0}}, {-1, -1, 0.0, 0.0, 0, 0, 0}, 0, 0.0, 0.0, 0.0};
				e.handle = 0;
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_gun_event.item_id = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_gun_event.range = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_gun_event.machine_gun_move_event.unit = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_gun_event.machine_gun_move_event.progress = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_gun_event.machine_gun_move_event.min_z = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_gun_event.machine_gun_move_event.max_z = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_gun_event.machine_gun_move_event.state = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_gun_event.machine_gun_fan_event.unit = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_gun_event.machine_gun_fan_event.progress = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_gun_event.machine_gun_fan_event.wise = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_gun_event.machine_gun_fan_event.min_angle = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_gun_event.machine_gun_fan_event.max_angle = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_gun_event.machine_gun_fan_event.state = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_window_event.item_id = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_window_event.item_id_pair = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_window_event.width = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_window_event.unit = atof(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_window_event.progress = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_window_event.invert = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.machine_window_event.state = atoi(ptr);
				if((ptr = strtok(NULL, Split)) != NULL)
					e.sync = atoi(ptr);
				event[index].machine_event = e;
			}
			free(str);
			j++;
			i += j;
			index++;
			if(index == count)
				break;
		}
		else
		{
			int j = 0;
			while(data[i + j] != '\n')
				j++;
			j++;
			i += j;
		}
	}
	delete_array(arr);
	free(arr);
	if(event_count)
		*event_count = count;
	return event;
}

GLvoid NETLizard_DeleteEvent(NETLizard_Event *event, GLuint count)
{
	if(!event || count == 0)
		return;
	free(event);
}

// clone class g function (void) s (void)

/* egypt 3d class s function (void) p (void) */
