#ifndef KARIN_ACTION_SIGNAL_SLOT_H
#define KARIN_ACTION_SIGNAL_SLOT_H

const void * SignalSlot_GetAction(const char *signal);
int SignalSlot_AddAction(const char *signal, const void *func);
void SignalSlot_ClearAction(void);
void SignalSlot_Init(void);

#endif
