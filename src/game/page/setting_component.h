#ifndef KARIN_GAME_SETTING_COMPONENT_H
#define KARIN_GAME_SETTING_COMPONENT_H

#include "game_setting.h"
#include "component/comp_util.h"
#include "component/flickable.h"

typedef struct _flickable_setting_item
{
	widget_type type;
	void *component;
	setting_item_type index;
} flickable_setting_item;

void UI_SettingItemChecked(GLvoid *comp, GLfloat x, GLfloat y);
void UI_GetFlickableItemGeometry(const GLvoid *comp, float *w, float *h);
void UI_RenderFlickableItem(const GLvoid *comp);
flickable_item * UI_MakeSettingItems(setting_item_type *types, unsigned int count, GLfloat w, GLfloat h, const font *fnt);
void UI_FreeSettingComponent(flickable_item *items, unsigned int item_count);

#endif
