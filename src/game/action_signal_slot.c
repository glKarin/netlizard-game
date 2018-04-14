#include "action_signal_slot.h"
#include "template/list_template.h"
#include "nl_std.h"

#include <stdlib.h>
#include <string.h>

static list_template action_list;
static int list_has_init = 0;

typedef struct _signal_slot
{
	char *signal;
	const void *slot;
} signal_slot;

void SignalSlot_Init(void)
{
	if(list_has_init)
		return;
	new_list_template(&action_list, sizeof(signal_slot));
	list_has_init = 1;
}

const void * SignalSlot_GetAction(const char *signal)
{
	if(!list_has_init)
		return NULL;
	if(!signal)
		return NULL;
	unsigned int i;
	for(i = 0; i < action_list.count; i++)
	{
		const signal_slot *ss = List_GetConstDataByIndexT(&action_list, i, signal_slot);
		if(ss -> signal)
		{
			if(strcmp(ss -> signal, signal) == 0)
				return ss -> slot;
		}
	}
	return NULL;
}

int SignalSlot_AddAction(const char *signal, const void *slot)
{
	if(!list_has_init)
		return -1;
	if(!signal || !slot)
		return -1;
	unsigned int i;
	for(i = 0; i < action_list.count; i++)
	{
		const signal_slot *ss = List_GetConstDataByIndexT(&action_list, i, signal_slot);
		if(ss -> signal)
		{
			if(strcmp(ss -> signal, signal) == 0)
				return -2;
		}
	}
	signal_slot ss;
	ss.signal = strdup(signal);
	ss.slot = slot;
	return List_PushBack(&action_list, &ss);
}

void SignalSlot_ClearAction(void)
{
	if(!list_has_init)
		return;
	unsigned int i;
	for(i = 0; i < action_list.count; i++)
	{
		signal_slot *ss = List_GetDataByIndexT(&action_list, i, signal_slot);
		FREE_PTR(ss -> signal)
	}
	List_DeleteAll(&action_list);
}

