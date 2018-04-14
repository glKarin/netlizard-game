#include "list_template.h"
#include "nl_std.h"

#include <string.h>
#include <stdlib.h>

#define NEW_LIST_NODE(p) \
	list_node *p = malloc(sizeof(list_node)); \
memset(p, 0, sizeof(list_node)); \
p -> prev = NULL; \
p -> next = NULL; \
p -> data = NULL;

#define NEW_NODE_DATA(p, d, size) \
{ \
	p -> data = malloc(size); \
	memcpy(p -> data, d, size); \
}

list_template * new_list_template(list_template *lst, unsigned int size)
{
	if(size == 0)
		return NULL;

	RETURN_PTR(l, lst, list_template)

		l -> size = size;
	l -> data = NULL;
	l -> count = 0;
	return l;
}

int List_PushBack(list_template *lst, const void *d)
{
	if(!lst)
		return -1;
	if(!lst -> data)
	{
		NEW_LIST_NODE(n);
		if(d)
			NEW_NODE_DATA(n, d, lst -> size)
				lst -> data = n;
		lst -> count++;
		return 0;
	}
	else
	{
		list_node *p = lst -> data;
		unsigned int i = 0;
		while(p)
		{
			if(p -> next == NULL)
			{
				NEW_LIST_NODE(n);
				if(d)
					NEW_NODE_DATA(n, d, lst -> size)
						p -> next = n;
				n -> prev = p;
				lst -> count++;
				i++;
				break;
			}
			else
			{
				p = p -> next;
				i++;
			}
		}
		return i;
	}
}

int List_PushFront(list_template *lst, const void *d)
{
	if(!lst)
		return -1;
	if(!lst -> data)
	{
		NEW_LIST_NODE(n);
		if(d)
			NEW_NODE_DATA(n, d, lst -> size)
				lst -> data = n;
		lst -> count++;
	}
	else
	{
		NEW_LIST_NODE(n);
		if(d)
			NEW_NODE_DATA(n, d, lst -> size)
				list_node *f = lst -> data;
		lst -> data = n;
		n -> next = f;
		f -> prev = n;
		lst -> count++;
	}
	return 0;
}

const void * List_GetDataConstByIndex(const list_template *lst, unsigned int index)
{
	if(!lst)
		return NULL;
	if(index >= lst -> count)
		return NULL;
	const list_node *p = lst -> data;
	unsigned int i = 0;
	while(p)
	{
		if(i == index)
			break;
		p = p -> next;
		i++;
	}
	return p ? p -> data : NULL;
}

int List_GetDataByData(const list_template *lst, const void *d)
{
	if(!lst)
		return -1;
	const list_node *p = lst -> data;
	unsigned int i = 0;
	while(p)
	{
		if((p -> data == NULL && d == NULL)
				|| ((p -> data && d) && (memcmp(p -> data, d, lst -> size) == 0)))
			return i;
		p = p -> next;
		i++;
	}
	return -1;
}

int List_InsertInto(list_template *lst, unsigned int index, const void *d)
{
	if(!lst)
		return -1;
	if(index >= lst -> count)
	{
		return List_PushBack(lst, d);
	}
	list_node *p = lst -> data;
	unsigned int i = 0;
	while(p)
	{
		if(i == index)
		{
			NEW_LIST_NODE(n);
			if(d)
				NEW_NODE_DATA(n, d, lst -> size)
					list_node *old_p = p -> prev;
			n -> prev = old_p;
			n -> next = p;
			p -> prev = n;
			if(old_p)
				old_p -> next = n;
			if(p == lst -> data)
				lst -> data = n;
			lst -> count++;
			return i;
		}
		p = p -> next;
		i++;
	}
	return -1;
}

void List_DeleteOneByIndex(list_template *lst, unsigned int index)
{
	if(!lst)
		return;
	if(index >= lst -> count)
		return;
	list_node *p = lst -> data;
	unsigned int i = 0;
	while(p)
	{
		if(i == index)
		{
			list_node *last = p -> prev;
			list_node *next = p -> next;
			if(last)
				last -> next = next;
			if(next)
				next -> prev = last;
			free(p -> data);
			free(p);
			if(i == 0)
				lst -> data = next;
			lst -> count--;
			return;
		}
		p = p -> next;
		i++;
	}
}

void List_DeleteAll(list_template *lst)
{
	if(!lst)
		return;
	list_node *p = lst -> data;
	while(p)
	{
		list_node *next = p -> next;
		if(p -> data)
			free(p -> data);
		free(p);
		p = next;
	}
	lst -> data = NULL;
	lst -> count = 0;
}

void List_DeleteOneByData(list_template *lst, const void *d)
{
	if(!lst)
		return;
	list_node *p = lst -> data;
	unsigned int i = 0;
	while(p)
	{
		if((p -> data == NULL && d == NULL)
				|| ((p -> data && d) && (memcmp(p -> data, d, lst -> size) == 0)))
		{
			list_node *last = p -> prev;
			list_node *next = p -> next;
			if(last)
				last -> next = next;
			if(next)
				next -> prev = last;
			free(p -> data);
			free(p);
			if(p == lst -> data)
				lst -> data = next;
			lst -> count--;
			return;
		}
		p = p -> next;
		i++;
	}
}

void List_ForEachConst(const list_template *lst, ListForEachConstFunction f)
{
	if(!lst || !f)
		return;
	const list_node *p = lst -> data;
	unsigned int i = 0;
	while(p)
	{
		const list_node *n = p -> next;
		f(i, p -> data);
		p = n;
		i++;
	}
}

void List_ForEach(list_template *lst, ListForEachFunction f)
{
	if(!lst || !f)
		return;
	list_node *p = lst -> data;
	unsigned int i = 0;
	while(p)
	{
		list_node *n = p -> next;
		f(i, p -> data);
		p = n;
		i++;
	}
}

void * List_GetDataByIndex(list_template *lst, unsigned int index)
{
	if(!lst)
		return NULL;
	if(index >= lst -> count)
		return NULL;
	list_node *p = lst -> data;
	unsigned int i = 0;
	while(p)
	{
		if(i == index)
			break;
		p = p -> next;
		i++;
	}
	return p ? p -> data : NULL;
}

void * List_TakeOneByIndex(list_template *lst, unsigned int index)
{
	if(!lst)
		return NULL;
	if(index >= lst -> count)
		return NULL;
	list_node *p = lst -> data;
	unsigned int i = 0;
	while(p)
	{
		if(i == index)
		{
			list_node *last = p -> prev;
			list_node *next = p -> next;
			if(last)
				last -> next = next;
			if(next)
				next -> prev = last;
			void *r = p -> data;
			free(p);
			if(i == 0)
				lst -> data = next;
			lst -> count--;
			return r;
		}
		p = p -> next;
		i++;
	}
	return NULL;
}

void * List_TakeOneByData(list_template *lst, const void *d)
{
	if(!lst)
		return NULL;
	list_node *p = lst -> data;
	unsigned int i = 0;
	while(p)
	{
		if((p -> data == NULL && d == NULL)
				|| ((p -> data && d) && (memcmp(p -> data, d, lst -> size) == 0)))
		{
			list_node *last = p -> prev;
			list_node *next = p -> next;
			if(last)
				last -> next = next;
			if(next)
				next -> prev = last;
			void *r = p -> data;
			free(p);
			if(p == lst -> data)
				lst -> data = next;
			lst -> count--;
			return r;
		}
		p = p -> next;
		i++;
	}
	return NULL;
}

