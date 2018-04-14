#include "setting_component.h"

#include "switcher.h"
#include "spin_box.h"
#include "time_spin_box.h"

void UI_RenderFlickableItem(const GLvoid *comp)
{
	if(!comp)
		return;
	flickable_setting_item *item = (flickable_setting_item *)comp;
	UI_RenderComponent(item -> type, item -> component);
}

void UI_GetFlickableItemGeometry(const GLvoid *comp, float *w, float *h)
{
	if(!comp)
		return;
	flickable_setting_item *item = (flickable_setting_item *)comp;
	UI_GetWidgetGeometry(item -> component, w, h);
}

void UI_SettingItemChecked(GLvoid *comp, GLfloat x, GLfloat y)
{
	if(!comp)
		return;
	flickable_setting_item *item = (flickable_setting_item *)comp;
	switcher *sw = NULL;
	spin_box *sb = NULL;
	time_spin_box *tsb = NULL;
	switch(item -> type)
	{
		case widget_switcher_type:
			sw = (switcher *)(item -> component);
			if(UI_PointInRect2(&sw -> btn, x, y))
			{
				sw -> open = !sw -> open;
				Setting_SetSettingBoolean(Setting_Items[item -> index].name, sw -> open);
			}
			break;
		case widget_spin_box_type:
			sb = (spin_box *)(item -> component);
			if(UI_ClickSpinBox(sb, x, y))
				Setting_SetSettingInteger(Setting_Items[item -> index].name, sb -> value);
			break;
		case widget_time_spin_box_type:
			tsb = (time_spin_box *)(item -> component);
			if(UI_ClickTimeSpinBox(tsb, x, y))
				Setting_SetSettingTime(Setting_Items[item -> index].name, tsb -> time);
			break;
		default:
			break;
	}
}

flickable_item * UI_MakeSettingItems(setting_item_type *types, unsigned int item_count, GLfloat w, GLfloat h, const font *fnt)
{
	if(!types || item_count == 0)
		return NULL;
	flickable_item *items = NEW_II(flickable_item, item_count);
	unsigned int i;
	for(i = 0; i < item_count; i++)
	{
		flickable_setting_item *item = NEW(flickable_setting_item);
		ZERO(item, flickable_setting_item);
		void *comp = NULL;
		widget_type t = widget_base_type;
		switch(Setting_Items[types[i]].value_type)
		{
			case boolean_value_type:
				comp = new_switcher(NULL, 0.0, 0.0, 0.3, w, h, Color_GetColor(black_color, 0.0), X11_COLOR(green), X11_COLOR(darkgreen), Color_GetColor(black_color, 0.0), X11_COLOR(lightgreen), X11_COLOR(gray), X11_COLOR(seagreen), Setting_Items[types[i]].description);
				((switcher *)comp) -> fnt = fnt;
				char b = 0;
				Setting_GetSettingBoolean(Setting_Items[types[i]].name, &b);
				((switcher *)comp) -> open = b ? GL_TRUE : GL_FALSE;
				t = widget_switcher_type;
				break;
			case integer_value_type:
				comp = new_spin_box(NULL, 0.0, 0.0, 0.3, w, h, Color_GetColor(black_color, 0.0), X11_COLOR(green), X11_COLOR(darkgreen), X11_COLOR(green), X11_COLOR(gray), X11_COLOR(seagreen), 0, 1, 20, 1, Setting_Items[types[i]].description);
				int in = 0;
				Setting_GetSettingInteger(Setting_Items[types[i]].name, &in);
				((spin_box *)comp) -> fnt = fnt;
				((spin_box *)comp) -> value = in;
				((spin_box *)comp) -> min = atoi(Setting_Items[types[i]].min);
				((spin_box *)comp) -> max = atoi(Setting_Items[types[i]].max);
				t = widget_spin_box_type;
				break;
			case time_value_type:
				comp = new_time_spin_box(NULL, 0.0, 0.0, 0.3, w, h * 3, Color_GetColor(black_color, 0.0), X11_COLOR(green), X11_COLOR(darkgreen), X11_COLOR(green), X11_COLOR(gray), X11_COLOR(seagreen), 1, 60, 3600, 300, Setting_Items[types[i]].description);
				long long tm = 0;
				Setting_GetSettingTime(Setting_Items[types[i]].name, &tm);
				((time_spin_box *)comp) -> fnt = fnt;
				((time_spin_box *)comp) -> min = atoll(Setting_Items[types[i]].min);
				((time_spin_box *)comp) -> max = atoll(Setting_Items[types[i]].max);
				UI_SetTimeSpinBoxTime(((time_spin_box *)comp), tm);
				t = widget_time_spin_box_type;
				break;
			default:
				break;
		}
		item -> component = comp;
		item -> index = Setting_Items[types[i]].type;
		item -> type = t;
		items[i].component = item;
		items[i].render_func = UI_RenderFlickableItem;
		items[i].get_geometry_func = UI_GetFlickableItemGeometry;
		items[i].action_func = UI_SettingItemChecked;
	}
	return items;
}

void UI_FreeSettingComponent(flickable_item *items, unsigned int item_count)
{
	if(!items || item_count == 0)
		return;
	unsigned int i;
	for(i = 0; i < item_count; i++)
	{
		flickable_setting_item *item = (flickable_setting_item *)(items[i].component);
		switcher *sw = NULL;
		spin_box *sb = NULL;
		time_spin_box *tsb = NULL;
		switch(item -> type)
		{
			case widget_switcher_type:
				sw = (switcher *)(item -> component);
				delete_switcher(sw);
				free(sw);
				break;
			case widget_spin_box_type:
				sb = (spin_box *)(item -> component);
				delete_spin_box(sb);
				free(sb);
				break;
			case widget_time_spin_box_type:
				tsb = (time_spin_box *)(item -> component);
				delete_time_spin_box(tsb);
				free(tsb);
				break;
			default:
				break;
		}
		free(items[i].component);
	}
}
