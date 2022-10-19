/*****************************************************   
 * Author : Avia Avikasis                            *
 * Reviewer: Ahron                                   *
 * 16/06/2022                                        *
 * Description : imlementation of doubly             *
 * linkedlist                                        *
 *                                                   *
 *****************************************************/

#include <stdlib.h> /* malloc */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include "dlist.h"  /* dlist functions */


typedef struct node
{
	void *data;
	struct node *next;
	struct node *prev;
}node_ty;

struct dlist
{
	node_ty head;
	node_ty tail;
};


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++*/


dlist_ty *DlistCreate(void)
{
	node_ty head = {NULL , NULL , NULL};
	node_ty tail = {NULL , NULL , NULL};
		
	dlist_ty *dlist = (dlist_ty*)malloc(sizeof(dlist_ty));
	if(NULL == dlist)
	{
		return NULL;
	}

	dlist->head = head;
	dlist->tail = tail;
	(dlist->head).next = &dlist->tail;
	(dlist->head).prev = NULL;
	(dlist->head).data = NULL;
	(dlist->tail).prev = &dlist->head;
	(dlist->tail).next = NULL;
	(dlist->tail).data = dlist;
		
	return dlist;
}


void DlistDestroy(dlist_ty *dlist)
{
	assert(NULL != dlist);
	
	while(!DlistIsEmpty(dlist))
	{
		DlistRemove(DlistBegin(dlist));
	}
	free(dlist);
}


dlist_iterator_ty DlistInsertBefore(dlist_iterator_ty position, void *data)
{
	node_ty *new_node = NULL;
	assert(NULL != position);
	assert(NULL != position -> prev);
	
	new_node = (node_ty*)malloc(sizeof(node_ty));
	if (NULL == new_node)
	{
		return NULL;
	}
	new_node -> data = data;
	position -> prev -> next = new_node;
	new_node -> prev = position -> prev;
	position -> prev = new_node;
	new_node -> next = position;
	
	return new_node;
}


dlist_iterator_ty DlistRemove(dlist_iterator_ty iterator)
{
	dlist_iterator_ty save_next = NULL;
	assert(NULL != iterator);
	
	save_next = iterator -> next;
	iterator -> prev -> next = iterator -> next;
	iterator -> next -> prev = iterator -> prev;
	free(iterator);
	return save_next;
}


dlist_iterator_ty DlistBegin(const dlist_ty *dlist) 
{
	assert(NULL != dlist);
	return (dlist->head).next;
}

dlist_iterator_ty DlistEnd(const dlist_ty *dlist) 
{
	assert(NULL != dlist);
	return (node_ty*)&(dlist->tail);
}


dlist_iterator_ty DlistNext(dlist_iterator_ty iterator)
{
	assert(NULL != iterator);
	return iterator->next;
}


dlist_iterator_ty DlistPrev(dlist_iterator_ty iterator)
{
	assert(NULL != iterator);
	return iterator->prev;
}

void DlistSetData(dlist_iterator_ty iterator, const void *data)
{
	assert(NULL != iterator);
	
	if(NULL != iterator->next)
	{
		iterator->data = (void*)data;
	}
}


void *DlistGetData(dlist_iterator_ty iterator)
{
	assert(NULL != iterator);
	return (NULL != iterator -> next) ? iterator -> data : NULL;
}


size_t DlistSize(const dlist_ty *dlist)
{
	size_t counter = 0;
	node_ty *run_ptr = NULL;
	assert(NULL != dlist);
	run_ptr = (dlist->head).next;
	
	while(dlist != run_ptr -> data)
	{
		++counter;
		run_ptr = run_ptr -> next; 
	}
	return counter;
}


int DlistIsEmpty(const dlist_ty *dlist)
{
	assert(NULL != dlist);
	return ((dlist->head).next == &(dlist->tail));
}


int DlistIterIsEqual(dlist_iterator_ty iterator1, dlist_iterator_ty iterator2)
{
	assert(NULL != iterator1);
	assert(NULL != iterator2);
	return (iterator1 == iterator2);
}


int DlistForEach(dlist_iterator_ty from, dlist_iterator_ty to, action_ty action_func, void *param)
{

	int return_function = 0;
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action_func);
	
	while(!DlistIterIsEqual(from , to))
	{
		return_function = action_func(DlistGetData(from) , param);
		if(0 != return_function)
		{
			return return_function;
		}
		from = DlistNext(from);	
	}
	return return_function;
}


dlist_iterator_ty DlistFind(dlist_iterator_ty from, dlist_iterator_ty to, is_match_ty match_func, void *param)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != match_func);
	
	while(!DlistIterIsEqual(from , to) && match_func(DlistGetData(from), param) != 1)
	{
		from = DlistNext(from);	
	}	
	return from;
}



void DlistSplice(dlist_iterator_ty where, dlist_iterator_ty from, dlist_iterator_ty to)
{
	dlist_iterator_ty save_to_prev = NULL;
	assert(NULL != where);
	assert(NULL != from);
	assert(NULL != to);
	
	save_to_prev = DlistPrev(to);
	from -> prev -> next = to;
	to -> prev = DlistPrev(from);
	where -> prev -> next = from;
	from -> prev = DlistPrev(where);
	save_to_prev -> next = where;
}


int DlistMultiFind(dlist_iterator_ty from, dlist_iterator_ty to, dlist_ty *dest_list, is_match_ty match_func, void *param)
{
	int count = 0;
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != match_func);

	while(!DlistIterIsEqual(from -> next, to))
	{
		if(match_func(DlistGetData(from) , param) == 1)
		{
			DlistInsertBefore(DlistEnd(dest_list) , DlistGetData(from));	
			++count;
		}
		from = DlistNext(from);
	}
	return count;
}

























