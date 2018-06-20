#ifndef _KARIN_NL_EVENT_H
#define _KARIN_NL_EVENT_H

#include "nl_gl.h"

typedef enum _NETLizard_Event_Type
{
	Event_AnyType = 0,
	Event_Portal = 1,
	Event_DoorV = 1 << 1,
	Event_Double_DoorV = 1 << 2,
	Event_Double_DoorH = 1 << 3,
	Event_Elevator = 1 << 4,
	Event_Switcher = 1 << 5,
	Event_Fan = 1 << 6,
	Event_Prop = 1 << 7,
	Event_Machine = 1 << 8,
	Event_General = 1 << 9
} NETLizard_Event_Type;

typedef struct _AnyType_Event
{
	NETLizard_Event_Type event_type;
	GLint handle;
	GLint item_id;
} AnyType_Event;

typedef struct _Portal_Event
{
	NETLizard_Event_Type event_type;
	GLint handle;
	GLint item_id;
	GLuint mask;
	GLfloat xt;
	GLfloat yt;
	GLfloat zt;
	GLfloat xr;
	GLfloat yr;
} Portal_Event;

typedef struct _DoorV_Event
{
	NETLizard_Event_Type event_type;
	GLint handle;
	GLint item_id;
	GLclampf unit; // 0 - 1
	GLfloat progress; // 0 - 100
} DoorV_Event;

typedef struct _Double_DoorV_Event
{
	NETLizard_Event_Type event_type;
	GLint handle;
	GLint item_id; // up
	GLint item_id_pair; // down
	GLclampf unit; // 0 - 1
	GLfloat progress; // 0 - 100
	GLint invert;
} Double_DoorV_Event;

typedef struct _Double_DoorH_Event
{
	NETLizard_Event_Type event_type;
	GLint handle;
	GLint item_id;
	GLint item_id_pair;
	GLclampf unit; // 0 - 1
	GLfloat progress; // 0 - 100
	GLuint orientation;
	GLuint invert;
} Double_DoorH_Event;

typedef struct _Switcher_Event
{
	NETLizard_Event_Type event_type;
	GLint handle;
	GLint item_id;
	GLfloat x_factory;
	GLfloat y_factory;
	GLfloat z_factory;
	GLint key;
	NETLizard_Event_Type operation_event_type;
	GLvoid *operation_event;
} Switcher_Event;

typedef struct _Elevator_Event
{
	NETLizard_Event_Type event_type;
	GLint handle;
	GLint item_id;
	GLclampf unit; // 0 - 1
	GLfloat progress; // 0 - 100
	GLfloat min_z;
	GLfloat max_z;
	GLuint state;
} Elevator_Event;

typedef struct _Fan_Event
{
	NETLizard_Event_Type event_type;
	GLint handle;
	GLint item_id;
	GLclampf unit; // 0 - 1
	GLfloat progress; // 0 - 100
	GLuint wise;
	GLfloat min_angle;
	GLfloat max_angle;
	GLuint orientation;
	GLint state;
} Fan_Event;

typedef struct _Prop_Event
{
	NETLizard_Event_Type event_type;
	GLint handle;
	GLint item_id;
	struct
	{
		GLclampf unit; // 0 - 1
		GLfloat progress; // 0 - 100
		GLfloat min_z;
		GLfloat max_z;
		GLuint state;
	} prop_move_event;
	struct 
	{
		GLclampf unit; // 0 - 1
		GLfloat progress; // 0 - 100
		GLuint wise;
		GLfloat min_angle;
		GLfloat max_angle;
		GLuint orientation;
		GLint state;
	} prop_fan_event;
} Prop_Event;

typedef struct _Machine_Event
{
	NETLizard_Event_Type event_type;
	GLint handle;
	struct
	{
		GLint item_id;
		GLfloat range;
		struct
		{
			GLclampf unit; // 0 - 1
			GLfloat progress; // 0 - 100
			GLfloat min_z;
			GLfloat max_z;
			GLuint state;
		} machine_gun_move_event;
		struct 
		{
			GLclampf unit; // 0 - 1
			GLfloat progress; // 0 - 100
			GLuint wise;
			GLfloat min_angle;
			GLfloat max_angle;
			GLint state;
		} machine_gun_fan_event;
	} machine_gun_event;
	struct
	{
		GLint item_id;
		GLint item_id_pair; // down
		GLfloat width;
		GLclampf unit; // 0 - 1
		GLfloat progress; // 0 - 100
		GLuint invert;
		GLuint state;
	} machine_window_event;
	GLuint sync;
	GLfloat target_x;
	GLfloat target_y;
	GLfloat target_z;
} Machine_Event;

typedef struct _General_Event
{
	NETLizard_Event_Type event_type;
	GLint handle;
	NETLizard_3D_Item_Type item_type;
	NETLizard_Event_Type operation_event_type;
	GLvoid *operation_event;
} General_Event;

typedef union _NETLizard_Event
{
	NETLizard_Event_Type event_type;
	AnyType_Event any_event;
	Portal_Event portal_event;
	DoorV_Event doorv_event;
	Double_DoorV_Event double_doorv_event;
	Double_DoorH_Event double_doorh_event;
	Elevator_Event elevator_event;
	Switcher_Event switcher_event;
	Fan_Event fan_event;
	Prop_Event prop_event;
	Machine_Event machine_event;
	General_Event general_event;
} NETLizard_Event;

GLvoid NETLizard_HandleDoorEvent(GL_NETLizard_3D_Model *model, DoorV_Event *event, GLint state, GLfloat per);
GLvoid NETLizard_HandleDoubleVDoorEvent(GL_NETLizard_3D_Model *model, Double_DoorV_Event *event, GLint state, GLfloat per);
GLvoid NETLizard_HandleDoubleHDoorEvent(GL_NETLizard_3D_Model *model, Double_DoorH_Event *event, GLint state, GLfloat per);
GLvoid NETLizard_HandleElevatorEvent(GL_NETLizard_3D_Model *model, Elevator_Event *event, GLint state, GLfloat per);
GLvoid NETLizard_HandleFanEvent(GL_NETLizard_3D_Model *model, Fan_Event *event, GLint state, GLfloat per);
GLvoid NETLizard_HandlePropEvent(GL_NETLizard_3D_Model *model, Prop_Event *event, GLint state, GLfloat per);
GLvoid NETLizard_HandleMachineEvent(GL_NETLizard_3D_Model *map_model, Machine_Event *event, GLint state, int mode, GLfloat per);
// event

NETLizard_Event * NETLizard_LoadEventFile(const char *file, game_name g, int lvl, int *event_count);
GLvoid NETLizard_DeleteEvent(NETLizard_Event *event, GLuint count);

#endif
