#ifndef KARIN_COMP_UTIL_H
#define KARIN_COMP_UTIL_H

#include "widget_base.h"

#define RENDER_CONST_COMPONENT_DEF(T) GLvoid UI_Render##T##Item(const GLvoid *comp);
#define RENDER_COMPONENT_DEF(T) GLvoid UI_Render##T##Item(GLvoid *comp);

typedef enum _widget_type
{
	widget_base_type = 0,
	widget_button_type,
	widget_slider_bar_type,
	widget_progress_bar_type,
	widget_label_type,
	widget_text_browser_type,
	widget_switcher_type,
	widget_spin_box_type,
	widget_time_spin_box_type,
	widget_list_view_type,
	widget_flickable_type,
} widget_type;

typedef void (* Button_Action_Function)(void *);
typedef struct _button_initilizer
{
	GLfloat x;
	GLfloat y;
	GLfloat w;
	GLfloat h;
	char *label;
	Button_Action_Function func;
	void *data;
} button_initilizer;

typedef GLvoid (*Render_Delegate_Function)(const GLvoid *delegate);
typedef GLvoid (*Get_Geometry_Function)(const GLvoid *comp, GLfloat *w, GLfloat *h);
typedef GLvoid (*Update_Text_Function)(GLvoid *comp, const char *text, GLboolean hl);
typedef GLvoid (*Item_Action_Function)(GLvoid *comp, GLfloat x, GLfloat y);

GLvoid UI_ButtonUpdateText(GLvoid *comp, const char *text, GLboolean hl);
GLvoid UI_GetWidgetGeometry(const GLvoid *comp, GLfloat *w, GLfloat *h);
RENDER_CONST_COMPONENT_DEF(Button)
RENDER_CONST_COMPONENT_DEF(Switcher)
RENDER_CONST_COMPONENT_DEF(SliderBar)
RENDER_CONST_COMPONENT_DEF(ProgressBar)
RENDER_COMPONENT_DEF(TextBrowser)
RENDER_CONST_COMPONENT_DEF(Label)
RENDER_CONST_COMPONENT_DEF(SpinBox)
RENDER_CONST_COMPONENT_DEF(TimeSpinBox)

GLvoid UI_RenderComponent(widget_type type, GLvoid *comp);

#undef RENDER_CONST_COMPONENT_DEF
#undef RENDER_COMPONENT_DEF

#endif
