#include "comp_util.h"

#include "button.h"
#include "text_browser.h"
#include "slider_bar.h"
#include "progress_bar.h"
#include "switcher.h"
#include "label.h"
#include "spin_box.h"
#include "time_spin_box.h"

#define RENDER_CONST_COMPONENT(T, t) \
	GLvoid UI_Render##T##Item(const GLvoid *comp) \
{ \
	if(!comp) \
	return; \
	const t *c = (const t *)comp; \
	UI_Render##T(c); \
}

#define RENDER_COMPONENT(T, t) \
	GLvoid UI_Render##T##Item(GLvoid *comp) \
{ \
	if(!comp) \
	return; \
	t *c = (t *)comp; \
	UI_Render##T(c); \
}

GLvoid UI_ButtonUpdateText(GLvoid *comp, const char *text, GLboolean hl)
{
	if(!comp)
		return;
	button *btn = (button *)comp;
	SET_TEXT(btn -> text, text)
		btn -> highlight = hl;
}

GLvoid UI_GetWidgetGeometry(const GLvoid *comp, GLfloat *w, GLfloat *h)
{
	if(!comp || (!w && !h))
		return;
	base_widget *b = (base_widget *)comp;
	if(w)
		*w = b -> width;
	if(h)
		*h = b -> height;
}

	RENDER_CONST_COMPONENT(Switcher, switcher)
	RENDER_CONST_COMPONENT(Button, button)
	RENDER_CONST_COMPONENT(Label, label)
	RENDER_CONST_COMPONENT(SliderBar, slider_bar)
	RENDER_CONST_COMPONENT(ProgressBar, progress_bar)
	RENDER_COMPONENT(TextBrowser, text_browser)
	RENDER_CONST_COMPONENT(SpinBox, spin_box)
RENDER_CONST_COMPONENT(TimeSpinBox, time_spin_box)

GLvoid UI_RenderComponent(widget_type type, GLvoid *comp)
{
	if(!comp)
		return;
	switch(type)
	{
		case widget_button_type:
			UI_RenderButtonItem(comp);
			break;
		case widget_switcher_type:
			UI_RenderSwitcherItem(comp);
			break;
		case widget_progress_bar_type:
			UI_RenderProgressBarItem(comp);
			break;
		case widget_slider_bar_type:
			UI_RenderSliderBarItem(comp);
			break;
		case widget_label_type:
			UI_RenderLabelItem(comp);
			break;
		case widget_text_browser_type:
			UI_RenderTextBrowserItem(comp);
			break;
		case widget_spin_box_type:
			UI_RenderSpinBoxItem(comp);
			break;
		case widget_time_spin_box_type:
			UI_RenderTimeSpinBoxItem(comp);
			break;
		default:
			break;
	}
}
