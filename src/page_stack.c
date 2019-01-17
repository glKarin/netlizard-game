#include "page_stack.h"
#include "list_template.h"
#include "nl_std.h"
#include "netlizard.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _page_stack
{
	list_t(page_3d_s) pages;
	int inited;
	int depth;
} page_stack;

static page_stack stack;

static page_3d_s * Main3D_MakeHeapPage3DStruct(const char *name, const glk_function *func)
{
	page_3d_s *page;

	page = NEW(page_3d_s);
	ZERO(page, page_3d_s);
	page->name = strdup(name);
	page->func = *func;

	return page;
}

static int Main3D_PageNameCmpFunc(const void *data, const void *user_data) // data: page_3d_s *, user_data: const char *name
{
	const page_3d_s *p;
	const char *a, *b;

	p = (const page_3d_s *)data;
	b = (const char *)user_data;

	if(p)
	{
		a = p->name;
		if(a)
		{
			if(b)
				return strcmp(a, b);
			else
				return 1;
		}
		else
		{
			if(b)
				return -1;
			else
				return 0;
		}
	}
	else
	{
		if(b)
			return -1;
		else
			return 0;
	}
}

void Main3D_InitPageStack(void)
{
	if(stack.inited)
		return;

	LIST(&stack.pages, page_3d_s);

	stack.depth = -1;
	stack.inited = 1;
}

void Main3D_ClearPageStack(void)
{
	unsigned int i;
	page_3d_s *page;

	if(!stack.inited)
		return;

	for(i = 0; i < stack.pages.count; i++)
	{
		page = List_GetDataByIndexT(&stack.pages, i, page_3d_s);
		FREE_PTR(page->name)
	}
	List_DeleteAll(&stack.pages);
	stack.depth = -1;
	stack.inited = 0;
}

const glk_function * Main3D_GetTopFunction(char **r)
{
	page_3d_s *page;

	if(!stack.inited)
		return NULL;

	page = List_FrontT(&stack.pages, page_3d_s);

	stack.depth = stack.pages.count == 0 ? -1 : 0; // reset depth to stack top

	if(page)
	{
		if(r)
			*r = page->name;
		return &page->func;
	}
	return NULL;
}

const glk_function * Main3D_GetFunction(const char *name)
{
	page_3d_s *page;

	if(!stack.inited)
		return NULL;

	if(!name)
		return NULL;

	page = List_FindT(&stack.pages, Main3D_PageNameCmpFunc, name, NULL, page_3d_s);

	if(page)
		return &page->func;
	return NULL;
}

int Main3D_PushPage(const char *name, const glk_function *func)
{
	page_3d_s *page;

	if(!stack.inited)
		return 0;
	if(!name || !func)
		return 0;

	if(List_FindT(&stack.pages, Main3D_PageNameCmpFunc, name, NULL, page_3d_s))
		return 0;

	page = Main3D_MakeHeapPage3DStruct(name, func);

	List_PushFrontV(&stack.pages, page);

	if(stack.pages.count == 1)
		stack.depth = 0;
	else if(stack.pages.count > 1 && stack.depth != 0)
		stack.depth++;
	else if(stack.pages.count == 0)
		stack.depth = -1;

	return 1;
}

int Main3D_PopPage(void)
{
	if(!stack.inited)
		return 0;

	List_PopFront(&stack.pages);

	if(stack.pages.count == 1)
		stack.depth = 0;
	else if(stack.pages.count > 1 && stack.depth != 0)
		stack.depth--;
	else if(stack.pages.count == 0)
		stack.depth = -1;

	return 1;
}

int Main3D_SetPage(const char *name, const glk_function *func)
{
	unsigned int i;
	page_3d_s *page;
	
	if(!stack.inited)
		return 0;
	if(!name || !func)
		return 0;

	for(i = 0; i < stack.pages.count; i++)
	{
		page = List_GetDataByIndexT(&stack.pages, i, page_3d_s);
		FREE_PTR(page->name)
	}
	List_DeleteAll(&stack.pages);

	stack.depth = -1;

	page = Main3D_MakeHeapPage3DStruct(name, func);

	List_PushFrontV(&stack.pages, page);

	stack.depth = 0;

	return 1;
}

int Main3D_ReplacePage(int depth, const char *name, const glk_function *func)
{
	page_3d_s *page;

	if(!stack.inited)
		return 0;
	if(!name || !func)
		return 0;

	if(List_FindT(&stack.pages, Main3D_PageNameCmpFunc, name, NULL, page_3d_s))
		return 0;

	page = List_GetDataByIndexT(&stack.pages, depth, page_3d_s);
	if(page)
	{
		free(page->name);
		page->name = strdup(name);
		page->func = *func;
	}
	return 1;
}

int Main3D_InsertPage(int depth, const char *name, const glk_function *func)
{
	page_3d_s *page;

	if(!stack.inited)
		return 0;
	if(!name || !func)
		return 0;

	if(List_FindT(&stack.pages, Main3D_PageNameCmpFunc, name, NULL, page_3d_s))
		return 0;

	page = Main3D_MakeHeapPage3DStruct(name, func);
	List_InsertIntoV(&stack.pages, depth, page);

	if(stack.pages.count == 1)
		stack.depth = 0;
	else if(stack.pages.count > 1 && stack.depth != 0 && depth <= stack.depth)
		stack.depth++;
	else if(stack.pages.count == 0)
		stack.depth = -1;

	return 1;
}

int Main3D_RemovePage(const char *name)
{
	int d;

	if(!stack.inited)
		return 0;
	if(!name)
		return 0;

	
	if(!List_FindT(&stack.pages, Main3D_PageNameCmpFunc, name, &d, page_3d_s))
		return 0;

	List_DeleteOneByIndex(&stack.pages, d);

	if(stack.pages.count == 1)
		stack.depth = 0;
	else if(stack.pages.count > 1 && stack.depth != 0 && d <= stack.depth)
		stack.depth--;
	else if(stack.pages.count == 0)
		stack.depth = -1;

	return 1;
}

glk_function Main3D_RegisterRenderFunction(
		Main3DInitFunction init_func,
		Main3DDrawFunction draw_func,
		Main3DFreeFunction free_func,
		Main3DIdleEventFunction idle_func,
		Main3DKeyEventFunction key_func,
		Main3DMouseMotionFunction motion_func,
		Main3DReshapeFunction reshape_func,
		Main3DMouseFunction mouse_func,
		Main3DMouseClickFunction click_func,
		Main3DStoreFunction_f store_func,
		Main3DRestoreFunction_f restore_func
		)
{
	glk_function r;

	r.init_func = init_func;
	r.draw_func = draw_func;
	r.free_func = free_func;
	r.idle_func = idle_func;
	r.key_func = key_func;
	r.motion_func = motion_func;
	r.reshape_func = reshape_func;
	r.mouse_func = mouse_func;
	r.click_func = click_func;
	r.store_func = store_func;
	r.restore_func = restore_func;

	return r;
}

void Main3D_ForeachPage(Main3DPageForEachFunction_f f)
{
	int i;
	const page_3d_s *page;

	if(!f)
		return;
	if(!stack.inited)
		return;
	
	for(i = stack.pages.count - 1; i >= 0; i--)
	{
		page = List_GetConstDataByIndexT(&stack.pages, i, page_3d_s);
		f(page ? page->name : NULL, page ? &page->func : NULL);
	}
}

int Main3D_GetStackLength(void)
{
	if(!stack.inited)
		return -1;
	return stack.pages.count;
}

int Main3D_GetStackDepth(void)
{
	if(!stack.inited)
		return -1;
	return stack.depth;
}

const glk_function * Main3D_GetCurFunction(char **r)
{
	const page_3d_s *page;

	if(!stack.inited)
		return NULL;
	if(stack.depth < 0)
		return NULL;
	if(stack.depth >= (int)stack.pages.count)
		return NULL;

	page = List_GetConstDataByIndexT(&stack.pages, stack.depth, page_3d_s);
	if(page)
	{
		if(r)
			*r = page->name;
		return &page->func;
	}
	return NULL;
}
