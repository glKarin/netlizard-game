#ifndef KARIN_LIST_TEMPLATR_H
#define KARIN_LIST_TEMPLATR_H

#define List_FrontT(lst, T) (T *)List_Front(lst)
#define List_EndT(lst, T) (T *)List_End(lst)
#define List_FrontTValue(lst, T) *((T *)List_Front(lst))
#define List_EndTValue(lst, T) *((T *)List_End(lst))

#define List_FindT(lst, cmp, user_data, index, T) (T *)List_Find(lst, cmp, user_data, index)
#define List_FindTValue(lst, cmp, user_data, index, T) *((T *)List_Find(lst, cmp, user_data, index))

#define List_GetDataByIndexT(lst, index, T) (T *)List_GetDataByIndex(lst, index)
#define List_GetConstDataByIndexT(lst, index, T) (const T *)List_GetDataByIndex(lst, index)
#define List_TakeOneByDataT(lst, data, T) (T *)List_TakeOneByData(lst, data)
#define List_TakeOneByIndexT(lst, index, T) (T *)List_TakeOneByIndex(lst, index)

#define List_GetDataByIndexTValue(lst, index, T) *((T *)List_GetDataByIndex(lst, index))
#define List_GetConstDataByIndexTValue(lst, index, T) *((const T *)List_GetDataByIndex(lst, index))
#define List_TakeOneByDataTValue(lst, data, T) *((T *)List_TakeOneByData(lst, data))
#define List_TakeOneByIndexTValue(lst, index, T) *((T *)List_TakeOneByIndex(lst, index))

#define list_t(T) list_template
#define LIST(l, T) new_list_template(l, sizeof(T))

struct _list_template;
typedef struct _list_template * (* ListV_vv_f)(struct _list_template *lst, void *data);
typedef struct _list_template * (* List_vv_f)(struct _list_template *lst, const void *data);
typedef int (* List_cmp_f)(const void *lst_data, const void *data);

typedef struct _list_node
{
	struct _list_node *prev;
	void *data; // allow NULL
	struct _list_node *next;
} list_node;

typedef struct _list_template
{
	unsigned int size; // sizeof()
	list_node *data; // first node pointer
	unsigned int count;

	// function
	List_vv_f vv;
	ListV_vv_f vvv;
} list_template;

// 遍历函数指针 参数为索引和数据 const和非const版本
typedef void (*ListForEachFunction)(unsigned int index, void *data);
typedef void (*ListForEachConstFunction)(unsigned int index, const void *data);

list_template * new_list_template(list_template *lst, unsigned int size);
// 添加一个新数据到表尾
int List_PushBack(list_template *lst, const void *d);
int List_PushBackV(list_template *lst, void *d);
list_template * List_Append(list_template *lst, const void *d);
list_template * List_AppendV(list_template *lst, void *d);
// 添加一个新数据到表头
int List_PushFront(list_template *lst, const void *d);
int List_PushFrontV(list_template *lst, void *d);
// 根据索引获取数据 const和非conat
const void * List_GetConstDataByIndex(const list_template *lst, unsigned int index);
void * List_GetDataByIndex(list_template *lst, unsigned int index);
// 根据数据获取索引
int List_GetDataByData(const list_template *lst, const void *d);
// 插入新数据到表中
int List_InsertInto(list_template *lst, unsigned int index, const void *d);
int List_InsertIntoV(list_template *lst, unsigned int index, void *d);
// 通过索引删除一个数据
void List_DeleteOneByIndex(list_template *lst, unsigned int index);
// 清空列表
void List_DeleteAll(list_template *lst);
// 通过数据删除一个数据
void List_DeleteOneByData(list_template *lst, const void *d);
// const遍历
void List_ForEachConst(const list_template *lst, ListForEachConstFunction f);
// 非conat遍历
void List_ForEach(list_template *lst, ListForEachFunction f);
// 根据数据从表中取出数据
void * List_TakeOneByData(list_template *lst, const void *d);
// 根据索引从表中取出数据
void * List_TakeOneByIndex(list_template *lst, unsigned int index);
// 头，尾
void * List_Front(list_template *lst);
void * List_End(list_template *lst);
// 删除头，尾
int List_PopFront(list_template *lst);
int List_PopEnd(list_template *lst);
// 查找
void * List_Find(list_template *lst, List_cmp_f cmp, const void *user_data, int *index);

#endif
