#include "file_chooser.h"
#include "gl_3d_main.h"
#include "component/button.h"
#include "component/label.h"
#include "component/list_view.h"
#include "component/text_browser.h"
#include "action_signal_slot.h"
#include "game_std.h"
#include "game_util.h"
#include "game_setting.h"
#include "template/list_template.h"

#include <dirent.h>
#include <sys/stat.h>

#define PAGE_NAME "FileChooser"

#define LIST_VIEW_X 0
#define LIST_VIEW_Y 0
#define LIST_VIEW_W 420
#define LIST_VIEW_H 400
#define LIST_VIEW_BUTTON_W 340
#define LIST_VIEW_BUTTON_H 50

#define TEXT_VIEW_X 450
#define TEXT_VIEW_Y 100
#define TEXT_VIEW_W 400
#define TEXT_VIEW_H 300

#define BTN_W 120
#define BTN_H 60
#define LABEL_H 80

#define IDLE_TIME_DELAY 0.4

#define FILE_SORT_BY_DIR_FIRST NL_MASK(0)
#define FILE_SORT_BY_NAME NL_MASK(1)
#define FILE_SORT_BY_EXT NL_MASK(2)

#define FILE_SORT_ASC 0
#define FILE_SORT_DESC 1

#define FILE_SHOW_FILE NL_MASK(0)
#define FILE_SHOW_DIR NL_MASK(1)
#define FILE_SHOW_HIDDEN NL_MASK(2)
#define FILE_SHOW_DOT NL_MASK(3)

#define DIR_DOT "."
#define DIR_DOTDOT ".."
#define DIR_DOT_SLASH "./"
#define DIR_DOTDOT_SLASH "../"
#define DIR_SLASH '/'

typedef enum _menu_action
{
	enter_action = 0,
	back_action,
	total_action_type
} menu_action;

typedef struct _file_info_s
{
	char *path;
	char *name;
	int is_dir;
} file_info_s;

static int UI_IdleFunc(void);
static int UI_KeyFunc(int k, int a, int p, int x, int y);
static int UI_MouseFunc(int b, int p, int x, int y);
static int UI_ClickFunc(int b, int x, int y);
static int UI_MotionFunc(int b, int p, int x, int y, int dx, int dy);
static void UI_DrawFunc(void);
static void UI_ReshapeFunc(int w, int h);
static void UI_InitFunc(void);
static void UI_FreeFunc(void);
static Main3DStoreFunction_f UI_StoreFunc = NULL;
static Main3DRestoreFunction_f UI_RestoreFunc = NULL;

static void UI_ResetPage(void);
static void UI_MakeListData(void *type);
static void UI_ReadFileInfo(void *fi);
static void UI_BackAction(void *data);
static file_info_s * UI_MakeFileInfo(struct dirent *d);
static file_info_s * UI_MoveFileInfoStruct(file_info_s *src);
static char * UI_MakePath(const char *dir, const char *file);
static void UI_SetPageSize(GLsizei w, GLsizei h);
static int UI_SortFiles(const void *a, const void *b);
static int UI_ReadDir(const char *path, list_t(file_info_s) *lst);
static const char * UI_GetFileExt(const char *path);

static const button_initilizer Btn_Infos[] = {
	{480, 10, BTN_W, BTN_H, "Open", UI_ReadFileInfo, NULL},
	{680, 10, BTN_W, BTN_H, "Back", UI_BackAction, NULL},
};

static FileChooserOpenFile_f open_file_func;
static button btn;
static button btns[total_action_type];
static list_view lst;
static label lb;
static text_browser tb;

static bool_t has_init = 0;

static list_view_data *data = NULL;
static unsigned int data_count = 0;
static GLsizei page_width = HARMATTAN_FULL_WIDTH;
static GLsizei page_height = HARMATTAN_FULL_HEIGHT;
static float idle_time = 0.0f;
static unsigned sort_flag = FILE_SORT_BY_DIR_FIRST | FILE_SORT_BY_NAME | FILE_SORT_BY_EXT;
static unsigned sort_seq = FILE_SORT_ASC;
static unsigned list_flag = FILE_SHOW_FILE | FILE_SHOW_DIR | FILE_SHOW_HIDDEN;

static char *current_path;
static char *current_file;
static int filelist_index = -1;
static float filelist_progress = 0.0;

void UI_SetPageSize(GLsizei w, GLsizei h)
{
	if(page_width == w && page_height == h)
		return;
	page_width = w;
	page_height = h;
	if(has_init)
	{
		UI_ResizeButton(&btn, LIST_VIEW_BUTTON_W, LIST_VIEW_BUTTON_H);
		UI_ResetListViewGeometry(&lst, LIST_VIEW_X, LIST_VIEW_Y, LIST_VIEW_W, LIST_VIEW_H);
		UI_ResetTextBrowserGeometry(&tb, TEXT_VIEW_X, TEXT_VIEW_Y, TEXT_VIEW_W, TEXT_VIEW_H);
		UI_ResetLabelGeometry(&lb, 0.0, page_height - LABEL_H, page_width, LABEL_H);
		int i;
		for(i = 0; i < total_action_type; i++)
			UI_ResetButtonGeometry(btns + i, Btn_Infos[i].x, Btn_Infos[i].y, Btn_Infos[i].w, Btn_Infos[i].h);
	}
}

int UI_IdleFunc(void)
{
	if(!has_init)
		return 0;

	idle_time += delta_time;
	if(idle_time < IDLE_TIME_DELAY)
		return 1;
	while(idle_time - IDLE_TIME_DELAY > 0.0f)
		idle_time -= IDLE_TIME_DELAY;
	if(key_state[Harmattan_K_Up] || key_state[Harmattan_K_w] || key_state[Harmattan_K_W])
		UI_MoveListViewCurrentIndex(&lst, -1);
	else if(key_state[Harmattan_K_Down] || key_state[Harmattan_K_s] || key_state[Harmattan_K_S])
		UI_MoveListViewCurrentIndex(&lst, 1);
	else
		idle_time = 0.0f;

	return 1;
}

void UI_InitFunc(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_SMOOTH);
	oglEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	oglEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	oglEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	oglEnable(GL_TEXTURE_2D);
#ifndef _HARMATTAN_OPENGLES2
	oglDisable(GL_LIGHTING);
#endif
	oglDisable(GL_FOG);
}

void UI_DrawFunc(void)
{
	if(!has_init)
		return;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	OpenGL_Render3DOrtho(0.0, width, 0.0, height);
	{
		//glPolygonMode(GL_FRONT, GL_LINE);
		glPushMatrix();
		{
			glTranslatef(lst.base.x, lst.base.y, lst.base.z);
			UI_RenderListView(&lst);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(tb.base.x, tb.base.y, tb.base.z);
			UI_RenderTextBrowser(&tb);
		}
		glPopMatrix();

		int i;
		for(i = 0; i < total_action_type; i++)
		{
			glPushMatrix();
			{
				glTranslatef(btns[i].base.x, btns[i].base.y, btns[i].base.z);
				UI_RenderButton(btns + i);
			}
			glPopMatrix();
		}

		glPushMatrix();
		{
			glTranslatef(lb.base.x, lb.base.y, lb.base.z);
			UI_RenderLabel(&lb);
		}
		glPopMatrix();
	}

}

void UI_ReshapeFunc(int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	if(!has_init)
		return;
	UI_SetPageSize(w, h);
}

void UI_FreeFunc(void)
{
	GLuint i;
	file_info_s *fi;

	if(!has_init)
		return;

	delete_button(&btn);
	int m;
	for(m = 0; m < total_action_type; m++)
		delete_button(btns + m);
	delete_label(&lb);
	delete_list_view(&lst);
	delete_text_browser(&tb);
	if(data)
	{
		for(i = 0; i < data_count; i++)
		{
			fi = (file_info_s *)(data[i].args);
			FREE_PTR(data[i].text)
				free(fi->path);
				FREE_PTR(data[i].args)
		}
		free(data);
		data = NULL;
		data_count = 0;
	}
	UI_ResetPage();
	has_init = 0;

	NL_PAGE_DESTROY_DEBUG(PAGE_NAME)
}

// for all X event pointer coord y, Using left-down as ori, like OpenGL, and not left-top of X11. so the y coord need to convert by screen height - y, and delta_y is invert.
int UI_KeyFunc(int key, int act, int pressed, int x, int y)
{
	if(!has_init)
		return 0;
	switch(key)
	{
		case Harmattan_K_Return:
		case Harmattan_K_KP_Enter:
			if(pressed)
			{
				UI_ReadFileInfo(NULL);
				return 1;
			}
			break;
		case Harmattan_K_Up:
		case Harmattan_K_w:
		case Harmattan_K_W:
			if(pressed)
			{
				UI_MoveListViewCurrentIndex(&lst, -1);
				idle_time = 0.0f;
			}
			break;
		case Harmattan_K_Down:
		case Harmattan_K_s:
		case Harmattan_K_S:
			if(pressed)
			{
				UI_MoveListViewCurrentIndex(&lst, 1);
				idle_time = 0.0f;
			}
			break;
		case Harmattan_K_Control_R:
		case Harmattan_K_Control_L:
		case Harmattan_K_BackSpace:
		case Harmattan_K_Escape:
			if(pressed)
			{
				UI_BackAction(NULL);
				return 1;
			}
			break;
	}
	return 0;
}

int UI_MouseFunc(int button, int pressed, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;

	int i;
	for(i = 0; i < total_action_type; i++)
	{
		if(UI_PointInWidget(&btns[i].base, x, gl_y))
		{
			btns[i].highlight = pressed ? GL_TRUE : GL_FALSE;
			return 1;
		}
	}
	return 0;
}

int UI_MotionFunc(int button, int pressed, int x, int y, int dx, int dy)
{
	if(!has_init)
		return 0;
	int res = 0;
	if(pressed)
	{
		int last_x = x - dx;
		int last_gl_y = height - (y - dy);
		int gl_y = height - y;
		if(UI_PointInWidget(&lst.base, x, gl_y))
		{
			res |= UI_SlideListView(&lst, -dy);
		}
		else if(UI_PointInWidget(&tb.base, x, gl_y))
		{
			res |= UI_SlideTextBrowser(&tb, -dy);
		}
		int i;
		for(i = 0; i < total_action_type; i++)
		{
			if(UI_PointInWidget(&btns[i].base, x, gl_y) && !UI_PointInWidget(&btns[i].base, last_x, last_gl_y))
			{
				btns[i].highlight = GL_TRUE;
				res |= 1;
			}
			else if(!UI_PointInWidget(&btns[i].base, x, gl_y) && UI_PointInWidget(&btns[i].base, last_x, last_gl_y))
			{
				btns[i].highlight = GL_FALSE;
				res |= 1;
			}
		}

	}

	return res;
}

void UI_FileChooserRegisterFunction(void)
{
	glk_function func;
	if(!has_init)
		return;

	func = REGISTER_RENDER_FUNCTION(UI);
	Main3D_PushRenderPage(PAGE_NAME, &func);
}

void UI_MakeListData(void *args)
{
	GLuint i;
	file_info_s *f;
	file_info_s *fi;
	list_t(file_info_s) filist;

	if(!has_init)
		return;

	fi = (file_info_s *)args;
	LIST(&filist, file_info_s);

	if(fi && fi->path)
	{
		if(fi->is_dir)
		{
			FREE_PTR(current_path)
			current_path = UI_MakePath(fi->path, NULL);
			printf("Open dir -> %s\n", current_path);
		}
		else
		{
			FREE_PTR(current_file)
			current_file = strdup(fi->path);
			printf("Open file -> %s\n", current_file);
			UI_ReadFileInfo(fi);
			goto __Exit;
		}
	}
	else
	{
		//k current_path = strdup("/");
	}

	if(data)
	{
		for(i = 0; i < data_count; i++)
		{
			f = (file_info_s *)(data[i].args);
			FREE_PTR(data[i].text)
				free(f->path);
			FREE_PTR(data[i].args)
		}
		free(data);
		data = NULL;
		data_count = 0;
	}

	UI_ReadDir(current_path, &filist);

	data_count = filist.count;
	data = NEW_II(list_view_data, data_count);
	for(i = 0; i < data_count; i++)
	{
		f = List_GetDataByIndexT(&filist, i, file_info_s);
		data[i].text = strdup(f->name);
		data[i].func = UI_MakeListData;
		data[i].args = UI_MoveFileInfoStruct(f);
	}

	qsort(data, data_count, sizeof(list_view_data), UI_SortFiles);

	lst.data = data;
	lst.count = data_count;
	lst.current_index = 0;
	lst.progress = 0.0;

__Exit:
	List_DeleteAll(&filist);
}

void UI_ReadFileInfo(void *args)
{
	file_info_s *fi;
	struct stat st;
	char str[512];
	int res;

	UI_SetBrowserText(&tb, NULL);
	if(!has_init)
		return;
	if(!args)
		return;

	fi = (file_info_s *)args;
	if(!fi->path)
		return;

	res = stat(fi->path, &st);
	if(res == 0)
	{
		memset(str, '\0', 512 * sizeof(char));
		sprintf(str, "%s\n\nMode: %o\nOwner: %d : %d\nSize: %d\nAccess time: %d\nModify time: %d\nChange time: %d",
				fi->path,
				st.st_mode,
				st.st_uid, st.st_gid,
				st.st_size,
				st.st_atim.tv_sec,
				st.st_mtim.tv_sec,
				st.st_ctim.tv_sec
				);
		if(!tb.text || strcmp(tb.text, str))
			UI_SetBrowserText(&tb, str);
	}
}

void UI_BackAction(void *data)
{
	const void *slot;

	if(!has_init)
		return;
	slot = SignalSlot_GetAction(BACK_MAIN_MENU);
	if(slot)
	{
		((void__func__void)slot)();
	}
}

int UI_ClickFunc(int button, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	if(UI_PointInWidget(&lst.base, x, gl_y))
	{
		UI_ClickListView(&lst, x - lst.base.x, gl_y - lst.base.y);
		return 1;
	}
	int i;
	for(i = 0; i < total_action_type; i++)
	{
		if(UI_PointInWidget(&btns[i].base, x, gl_y))
		{
			if(Btn_Infos[i].func)
			{
				Btn_Infos[i].func(Btn_Infos[i].data);
			}
			return 1;
		}
	}
	return 0;
}

void UI_InitFileChooser(const char *path)
{
	if(has_init)
		return;

	new_button(&btn, 0.0, 0.0, 0.0, LIST_VIEW_BUTTON_W, LIST_VIEW_BUTTON_H, 2.0, X11_COLOR(lightskyblue), X11_COLOR(green), X11_COLOR(lightseagreen), X11_COLOR(pink), X11_COLOR(darkgreen), X11_COLOR(seagreen), NULL);
	btn.base.clip = GL_FALSE;
	int m;
	for(m = 0; m < total_action_type; m++)
	{
		new_button(btns + m, Btn_Infos[m].x, Btn_Infos[m].y, 0.3, Btn_Infos[m].w, Btn_Infos[m].h, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(gray), Btn_Infos[m].label);
		btns[m].fnt = &fnt;
	}
	btn.fnt = &fnt;
	new_list_view(&lst, LIST_VIEW_X, LIST_VIEW_Y, 0.0, LIST_VIEW_W, LIST_VIEW_H, 10, 20, 15, Color_GetColor(black_color, 0.0), X11_COLOR(lightgreen), X11_COLOR(darkgreen));
	lst.delegate.component = &btn;
	lst.delegate.update_func = UI_ButtonUpdateText;
	lst.delegate.render_func = UI_RenderButtonItem;
	lst.delegate.get_geometry_func = UI_GetWidgetGeometry;

	new_text_browser(&tb, TEXT_VIEW_X, TEXT_VIEW_Y, 0.0, TEXT_VIEW_W, TEXT_VIEW_H, 4.0, 2.0, X11_COLOR(orange), X11_COLOR(black), X11_COLOR(lightgreen), X11_COLOR(darkgreen), X11_COLOR(green), NULL);
	tb.fnt = &fnt;

	new_label(&lb, 0.0, page_height - LABEL_H, 0.2, page_width, LABEL_H, 0, Color_GetColor(white_color, 0.4), X11_COLOR(green), Color_GetColor(black_color, 0.0), "File Chooser", NULL);
	lb.fnt = &fnt;
	has_init = 1;
	FREE_PTR(current_file)
	FREE_PTR(current_path)
	current_path = path ? strdup(path) : NULL;
	UI_MakeListData(NULL);
}

void UI_ResetPage(void)
{
	page_width = width;
	page_height = height;
	FREE_PTR(current_path)
	idle_time = 0.0f;
}

void UI_SetFileChooserOpenFileFunction(FileChooserOpenFile_f f)
{
	open_file_func = f;
}

file_info_s * UI_MoveFileInfoStruct(file_info_s *src)
{
	file_info_s *r;

	if(!src)
		return NULL;

	r = NEW(file_info_s);
	NL_MOVE(r->path, src->path);
	NL_MOVE(r->name, src->name);
	r->is_dir = src->is_dir;

	return r;
}

file_info_s * UI_MakeFileInfo(struct dirent *d)
{
	file_info_s *r;
	size_t name_len;
	size_t len;

	if(!d)
		return NULL;

	name_len = strlen(d->d_name);
	len = name_len + 1 + (d->d_type == DT_DIR ? 1 : 0);
	r = NEW(file_info_s);
	r->name = NEW_II(char, len);
	strcpy(r->name, d->d_name);
	if(d->d_type == DT_DIR)
		r->name[name_len] = '/';
	r->is_dir = d->d_type == DT_DIR;
	r->path = UI_MakePath(current_path, d->d_name);

	return r;
}

char * UI_MakePath(const char *dir, const char *file)
{
	size_t len;
	const char *d;
	char *r;
	int hasnot_splash;
	char *ptr;
	const char *cptr;
	int d_len;
	int i;

	d = dir ? dir : DIR_DOT;
	d_len = strlen(d);
	if(!file || strcmp(file, DIR_DOT) == 0 || strcmp(file, DIR_DOT_SLASH) == 0) // cur dir
	{
		len = d[d_len - 1] == DIR_SLASH && d_len > 1 ? d_len - 1 : d_len;
		r = NEW_II(char, len + 1);
		strncpy(r, d, len);
	}
	else if(file && (strcmp(file, DIR_DOTDOT) == 0 || strcmp(file, DIR_DOTDOT_SLASH) == 0)) // parent dir
	{
		for(i = d[d_len - 1] == DIR_SLASH ? d_len - 2 : d_len - 1; i >= 0; i--)
		{
			cptr = d + i;
			if(*cptr == DIR_SLASH)
				break;
		}
		len = i == 0 ? 1 : (i == -1 ? 1 : i);
		r = NEW_II(char, len + 1);
		if(i != -1)
			strncpy(r, d, len);
		else
			r[0] = DIR_SLASH;
	}
	else // add
	{
		len = d_len;
		hasnot_splash = d[strlen(d) - 1] != DIR_SLASH && (file && file[0] != DIR_SLASH);
		if(hasnot_splash)
			len++;
		len += strlen(file);
		r = NEW_II(char, len + 1);
		strcpy(r, d);
		ptr = r + d_len;
		if(hasnot_splash)
		{
			*ptr = DIR_SLASH;
			ptr++;
		}
		strcpy(ptr, file);
	}
	return r;
}

int UI_SortFiles(const void *a, const void *b)
{
	const file_info_s *fia, *fib;
	const char *exta, *extb;
	int r;

	fia = (const file_info_s *)((const list_view_data *)a)->args;
	fib = (const file_info_s *)((const list_view_data *)b)->args;

	if(sort_flag & FILE_SORT_BY_DIR_FIRST)
	{
		if(fia->is_dir != fib->is_dir)
			return -(fia->is_dir - fib->is_dir);
	}

	if(sort_flag & FILE_SORT_BY_EXT)
	{
		if(!fia->is_dir && !fib->is_dir)
		{
			exta = UI_GetFileExt(fia->path);
			extb = UI_GetFileExt(fib->path);
			if(!exta && extb)
				r = -1;
			else if(exta && !extb)
				r = 1;
			else if(!exta || !extb)
				goto __File_Name_Cmp;
			else
			{
				r = strcmp(exta, extb);
				if(r == 0)
					goto __File_Name_Cmp;
				else
					goto __Exit;
			}
		}
	}

__File_Name_Cmp:
	if(sort_flag & FILE_SORT_BY_NAME)
	{
		r = strcmp(fia->name, fib->name);
	}

__Exit:
	if(sort_seq & FILE_SORT_DESC)
		r = -r;

	return r;
}

int UI_ReadDir(const char *path, list_t(file_info_s) *lst)
{
	file_info_s *f;
	DIR *dir;
	struct dirent *d;
	int r;

	if(!path || !lst)
		return -1;

	dir = opendir(current_path);
	if(!dir)
		return -2;

	r = 0;
	while((d = readdir(dir)) != NULL)
	{
		if((list_flag & FILE_SHOW_HIDDEN) == 0)
		{
			if(d->d_name[0] == DIR_DOT[0])
				continue;
		}
		if((list_flag & FILE_SHOW_DIR) == 0)
		{
			if(d->d_type == DT_DIR && strcmp(d->d_name, DIR_DOTDOT) != 0)
				continue;
		}
		if((list_flag & FILE_SHOW_FILE) == 0)
		{
			if(d->d_type != DT_DIR)
				continue;
		}
		if((list_flag & FILE_SHOW_DOT) == 0)
		{
			if(strcmp(d->d_name, DIR_DOT) == 0)
				continue;
		}
		if(strlen(path) == 1 && path[0] == DIR_SLASH && strcmp(d->d_name, DIR_DOTDOT) == 0)
			continue;

		f = UI_MakeFileInfo(d);
		List_PushBackV(lst, f);
		r++;
	}

	closedir(dir);

	return r;
}

const char * UI_GetFileExt(const char *path)
{
	const char *ptr;
	size_t len;
	int i;
	int is_dir;

	is_dir = 0;
	ptr = NULL;
	len = strlen(path);
	if(!path)
		return ptr;

	for(i = path[len - 1] == DIR_SLASH ? len - 2 : len - 1; i >= 0; i--)
	{
		ptr = path + i;
		if(*ptr == DIR_SLASH)
		{
			is_dir = 1;
			break;
		}
		if(*ptr == DIR_DOT[0])
		{
			break;
		}
	}

	if(is_dir)
		ptr = path;
	else
	{
		if(i == 0) // hidden file
			ptr = NULL;
		else if(i == -1) // not dot character
			ptr = NULL;
	}

	return ptr; // include dot character
}

const char * UI_GetLastFilePath(void)
{
	return current_file;
}
