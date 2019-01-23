#include "list_template.h"
#include "nl_std.h"

#include <string.h>
#include <stdlib.h>

#define NEW_LIST_NODE(p) \
	list_node *p = malloc(sizeof(list_node)); \
memset(p, 0, sizeof(list_node)); \
p->prev = NULL; \
p->next = NULL; \
p->data = NULL;

#define NEW_NODE_DATA(p, d, size) \
{ \
	p->data = malloc(size); \
	memcpy(p->data, d, size); \
}

list_template * new_list_template(list_template *lst, unsigned int size)
{
	if(size == 0)
		return NULL;

	RETURN_PTR(l, lst, list_template)

		l->size = size;
	l->data = NULL;
	l->count = 0;
	l->vv = List_Append;
	l->vvv = List_AppendV;
	return l;
}

int List_PushBackV(list_template *lst, void *d)
{
	if(!lst)
		return -1;
	if(!lst->data)
	{
		NEW_LIST_NODE(n);
		if(d)
			n->data = d;
		lst->data = n;
		lst->count++;
		return 0;
	}
	else
	{
		list_node *p = lst->data;
		unsigned int i = 0;
		while(p)
		{
			if(p->next == NULL)
			{
				NEW_LIST_NODE(n);
				if(d)
					n->data = d;
				p->next = n;
				n->prev = p;
				lst->count++;
				i++;
				break;
			}
			else
			{
				p = p->next;
				i++;
			}
		}
		return i;
	}
}

int List_PushBack(list_template *lst, const void *d)
{
	void *pdata;

	if(!lst)
		return -1;
	pdata = malloc(lst->size);
	memcpy(pdata, d, lst->size);
	return List_PushBackV(lst, pdata);
}

list_template * List_Append(list_template *lst, const void *d)
{
	List_PushBack(lst, d);
	return lst;
}

list_template * List_AppendV(list_template *lst, void *d)
{
	List_PushBackV(lst, d);
	return lst;
}

int List_PushFrontV(list_template *lst, void *d)
{
	if(!lst)
		return -1;
	if(!lst->data)
	{
		NEW_LIST_NODE(n);
		if(d)
			n->data = d;
		lst->data = n;
		lst->count++;
	}
	else
	{
		NEW_LIST_NODE(n);
		if(d)
			n->data = d;
		list_node *f = lst->data;
		lst->data = n;
		n->next = f;
		f->prev = n;
		lst->count++;
	}
	return 0;
}

int List_PushFront(list_template *lst, const void *d)
{
	void *pdata;

	if(!lst)
		return -1;
	pdata = malloc(lst->size);
	memcpy(pdata, d, lst->size);
	return List_PushFrontV(lst, pdata);
}

const void * List_GetDataConstByIndex(const list_template *lst, unsigned int index)
{
	if(!lst)
		return NULL;
	if(index >= lst->count)
		return NULL;
	const list_node *p = lst->data;
	unsigned int i = 0;
	while(p)
	{
		if(i == index)
			break;
		p = p->next;
		i++;
	}
	return p ? p->data : NULL;
}

int List_GetDataByData(const list_template *lst, const void *d)
{
	if(!lst)
		return -1;
	const list_node *p = lst->data;
	unsigned int i = 0;
	while(p)
	{
		if((p->data == NULL && d == NULL)
				|| ((p->data && d) && (memcmp(p->data, d, lst->size) == 0)))
			return i;
		p = p->next;
		i++;
	}
	return -1;
}

int List_InsertIntoV(list_template *lst, unsigned int index, void *d)
{
	if(!lst)
		return -1;
	if(index >= lst->count)
	{
		return List_PushBack(lst, d);
	}
	list_node *p = lst->data;
	unsigned int i = 0;
	while(p)
	{
		if(i == index)
		{
			NEW_LIST_NODE(n);
			if(d)
				p->data = d;
			list_node *old_p = p->prev;
			n->prev = old_p;
			n->next = p;
			p->prev = n;
			if(old_p)
				old_p->next = n;
			if(p == lst->data)
				lst->data = n;
			lst->count++;
			return i;
		}
		p = p->next;
		i++;
	}
	return -1;
}

int List_InsertInto(list_template *lst, unsigned int index, const void *d)
{
	void *pdata;

	if(!lst)
		return -1;
	pdata = malloc(lst->size);
	memcpy(pdata, d, lst->size);
	return List_InsertIntoV(lst, index, pdata);
}

void List_DeleteOneByIndex(list_template *lst, unsigned int index)
{
	if(!lst)
		return;
	if(index >= lst->count)
		return;
	list_node *p = lst->data;
	unsigned int i = 0;
	while(p)
	{
		if(i == index)
		{
			list_node *last = p->prev;
			list_node *next = p->next;
			if(last)
				last->next = next;
			if(next)
				next->prev = last;
			free(p->data);
			free(p);
			if(i == 0)
				lst->data = next;
			lst->count--;
			return;
		}
		p = p->next;
		i++;
	}
}

void List_DeleteAll(list_template *lst)
{
	if(!lst)
		return;
	list_node *p = lst->data;
	while(p)
	{
		list_node *next = p->next;
		if(p->data)
			free(p->data);
		free(p);
		p = next;
	}
	lst->data = NULL;
	lst->count = 0;
}

void List_DeleteOneByData(list_template *lst, const void *d)
{
	if(!lst)
		return;
	list_node *p = lst->data;
	unsigned int i = 0;
	while(p)
	{
		if((p->data == NULL && d == NULL)
				|| ((p->data && d) && (memcmp(p->data, d, lst->size) == 0)))
		{
			list_node *last = p->prev;
			list_node *next = p->next;
			if(last)
				last->next = next;
			if(next)
				next->prev = last;
			free(p->data);
			free(p);
			if(p == lst->data)
				lst->data = next;
			lst->count--;
			return;
		}
		p = p->next;
		i++;
	}
}

void List_ForEachConst(const list_template *lst, ListForEachConstFunction f)
{
	if(!lst || !f)
		return;
	const list_node *p = lst->data;
	unsigned int i = 0;
	while(p)
	{
		const list_node *n = p->next;
		f(i, p->data);
		p = n;
		i++;
	}
}

void List_ForEach(list_template *lst, ListForEachFunction f)
{
	if(!lst || !f)
		return;
	list_node *p = lst->data;
	unsigned int i = 0;
	while(p)
	{
		list_node *n = p->next;
		f(i, p->data);
		p = n;
		i++;
	}
}

void * List_GetDataByIndex(list_template *lst, unsigned int index)
{
	if(!lst)
		return NULL;
	if(index >= lst->count)
		return NULL;
	list_node *p = lst->data;
	unsigned int i = 0;
	while(p)
	{
		if(i == index)
			break;
		p = p->next;
		i++;
	}
	return p ? p->data : NULL;
}

void * List_TakeOneByIndex(list_template *lst, unsigned int index)
{
	if(!lst)
		return NULL;
	if(index >= lst->count)
		return NULL;
	list_node *p = lst->data;
	unsigned int i = 0;
	while(p)
	{
		if(i == index)
		{
			list_node *last = p->prev;
			list_node *next = p->next;
			if(last)
				last->next = next;
			if(next)
				next->prev = last;
			void *r = p->data;
			free(p);
			if(i == 0)
				lst->data = next;
			lst->count--;
			return r;
		}
		p = p->next;
		i++;
	}
	return NULL;
}

void * List_TakeOneByData(list_template *lst, const void *d)
{
	if(!lst)
		return NULL;
	list_node *p = lst->data;
	unsigned int i = 0;
	while(p)
	{
		if((p->data == NULL && d == NULL)
				|| ((p->data && d) && (memcmp(p->data, d, lst->size) == 0)))
		{
			list_node *last = p->prev;
			list_node *next = p->next;
			if(last)
				last->next = next;
			if(next)
				next->prev = last;
			void *r = p->data;
			free(p);
			if(p == lst->data)
				lst->data = next;
			lst->count--;
			return r;
		}
		p = p->next;
		i++;
	}
	return NULL;
}

void * List_Front(list_template *lst)
{
	if(!lst || !lst->data)
		return NULL;

	return lst->data->data;
}

void * List_End(list_template *lst)
{
	list_node *p;

	if(!lst)
		return NULL;

	p = lst->data;
	while(p)
	{
		if(p->next == NULL)
		{
			return p->data;
		}
		else
		{
			p = p->next;
		}
	}
	return NULL;
}

void * List_Find(list_template *lst, List_cmp_f cmp, const void *user_data, int *index)
{
	list_node *p;
	void *r;
	int i;

	if(!lst || !cmp)
		return NULL;

	i = 0;
	p = lst->data;
	r = NULL;
	while(p)
	{
		if(cmp(p->data, user_data) == 0)
		{
			r = p->data;
			break;
		}

		if(p->next == NULL)
		{
			break;
		}
		else
		{
			p = p->next;
			i++;
		}
	}

	if(index)
		*index = i;
	return r;
}

int List_PopFront(list_template *lst)
{
	list_node *p;

	if(!lst || !lst->data)
		return 0;

	p = lst->data;
	lst->data = p->next;
	if(p->next)
		p->next->prev = NULL;

	free(p->data);
	free(p);
	lst->count--;

	return lst->count;
}

int List_PopEnd(list_template *lst)
{
	list_node *p;

	if(!lst)
		return 0;

	p = lst->data;
	while(p)
	{
		if(p->next == NULL)
		{
			if(p->prev)
			{
				p->prev->next = NULL;
			}
			else
			{
				lst->data = NULL;
			}
			free(p->data);
			free(p);
			lst->count--;
			break;
		}
		else
		{
			p = p->next;
		}
	}
	return lst->count;
}

void * List_ToArray(list_template *lst)
{
	char *r;
	const void *d;
	unsigned int i;

	r = NULL;

	if(!lst || lst->count == 0)
		return r;

	r = calloc(lst->count, lst->size);
	for(i = 0; i < lst->count; i++)
	{
		d = List_GetDataConstByIndex(lst, i);
		memcpy(r + i, d, lst->size);
	}

	return r;
}

unsigned int List_ToArrayV(list_template *lst, void *r, unsigned int max)
{
	unsigned int count;
	const void *d;
	char *cr;
	unsigned int i;

	cr = r;
	count = 0;

	if(!lst || lst->count == 0 || !r || max == 0)
		return count;

	for(i = 0; i < lst->count; i++)
	{
		if(count + lst->size > max)
			break;
		d = List_GetDataConstByIndex(lst, i);
		memcpy(cr + (lst->size * i), d, lst->size);
		count += lst->size;
	}

	return count;
}
