#ifndef __ILRD_OL127_128_DLINKED_LIST_H__
#define __ILRD_OL127_128_DLINKED_LIST_H__

#include <stddef.h> /* size_t */


typedef struct dlist dlist_ty;
typedef struct node *dlist_iterator_ty;

typedef int (*is_match_ty)(const void *data, void *params);
typedef int (*action_ty)(void *data, void *params);

/*
Description : the DlistCreate() function create new doubly linkedlist.
return value : pointer to the new dlist
time cpmlexity : O(1)
*/
dlist_ty *DlistCreate(void);

/*
Description : the DlistDestroy() function destroy exist doubly linkedlist.
Param : pointer to dlist
return value : void
time cpmlexity : O(1)
*/
void DlistDestroy(dlist_ty *dlist); 

/*
Description : the DlistInsertBefore() function insert new node to exist dlist , before the given position.
Params : position iterator , pointer to data variable 
return value : iterator to the new node in the list.
Bugs : position pointer that point to head of empty list , will cause undefined behavior
time cpmlexity : O(1)
*/
dlist_iterator_ty DlistInsertBefore(dlist_iterator_ty position, void *data);

/*
Description : the DlistRemove() function remove exist node from dlist.
Param : position iterator 
return value : iterator to the next node after position.
Bugs : position pointer that point to end list or head of empty list , will cause undefined behavior
time cpmlexity : O(1)
*/
dlist_iterator_ty DlistRemove(dlist_iterator_ty iterator); 

/*
Description : the DlistBegin() function return iterator to the first node in exist dlist.
Param : pointer to dlist 
return value : iterator to the first node in the list.
Bugs : dlist pointer that point to empty list , will cause undefined behavior
time cpmlexity : O(1)
*/
dlist_iterator_ty DlistBegin(const dlist_ty *dlist); 

/*
Description : the DlistEnd() function return iterator to position that find after the end of list.
Param : pointer to dlist 
return value : iterator to after end of list.
time cpmlexity : O(1)
*/
dlist_iterator_ty DlistEnd(const dlist_ty *dlist);

/*
Description : the DlistNext() function return iterator to the next position after given position.
Param :  iterator to position in dlist
return value : iterator to the next position. NULL if the position is end of the list
Bugs : if the function will get iterator to the end of list , the return value will be NULL
time cpmlexity : O(1)
*/
dlist_iterator_ty DlistNext(dlist_iterator_ty iterator);

/*
Description : the DlistNext() function return iterator to the prev position before given position.
Param :  iterator to position in dlist
return value : iterator to the prev position.
time cpmlexity : O(1)
*/
dlist_iterator_ty DlistPrev(dlist_iterator_ty iterator);

/*
Description : the DlistSetData() function save new data in specific position in dlist.
Param :  iterator to position in dlist
return value : void
Bugs : iterator to the end of list as param , will cause undefined behavior
time cpmlexity : O(1)
*/
void DlistSetData(dlist_iterator_ty iterator, const void *data);

/*
Description : the DlistGetData() function return the data that hold in speciefic position in dlist.
Param :  iterator to position in dlist
return value : void pointer , point to data variable. can be also NULL
Bugs : iterator to the end of list as param , will cause undefined behavior
time cpmlexity : O(1)
*/
void *DlistGetData(dlist_iterator_ty iterator);

/*
Description : the DlistSize() function return the num elements in dlist.
Param : dlist pointer
return value : size_t num 
time cpmlexity : O(1)
*/
size_t DlistSize(const dlist_ty *dlist);

/*
Description : the DlistIsEmpty() function check if dlist is empty.
Param :  dlist pointer
return value : 1 if list is empty , 0 otherwise
time cpmlexity : O(1)
*/
int DlistIsEmpty(const dlist_ty *dlist);

/*
Description : the DlistIterIsEqual() function check if two dlist iterators is equal.
Param :  two dlist iterators
return value : 1 if they are equal , 0 otherwise
time cpmlexity : O(1)
*/
int DlistIterIsEqual(dlist_iterator_ty iterator1, dlist_iterator_ty iterator2);

/*
Description : the DlistForEach() function active given function for each element in dlist.
Param : two dlist iterators for the range , function pointer , void pointer to param value
return value : 0 if the operation of user function succeeded , other num if the function not succeeded.
time cpmlexity : O(n)
*/
int DlistForEach(dlist_iterator_ty from, dlist_iterator_ty to, action_ty action_func, void *param);

/*
Description : the DlistFind() function find specific element in dlist , by match function.
Param : two dlist iterators for the range , function pointer , void pointer to param value
return value : iterator to the match element if exist , else - iterator to "to" position 
Bugs : if the function will get the end of list as "to" and will not find any match element,
the return value will be iterator to the end of function. if the user will try to execute 
operation with this iterator , the program can fail.
time cpmlexity : O(n)
*/
dlist_iterator_ty DlistFind(dlist_iterator_ty from, dlist_iterator_ty to, is_match_ty match_func, void *param);

/*
Description : the DlistMultiFind() function find specific elements in dlist , by match function
and insert them to new dlist.
Param : two dlist iterators for the range , function pointer , void pointer to param value
return value : the number of the match elements. 
time cpmlexity : O(n)
*/
int DlistMultiFind(dlist_iterator_ty from, dlist_iterator_ty to, 
                   dlist_ty *dest_list, is_match_ty match_func, void *param);

/*
Description : the DlistSplice() function cat part of dlist to other list, in given position.
the function insert the segment from "from" iterator to "to" iterator , not including, before
where position in the dest list.
Param : iterator for where the user want to cat , iterator from for start of segment that 
user want to cat , and iterator to for end of this segment
return value : void. 
time cpmlexity : O(1)
*/
void DlistSplice(dlist_iterator_ty where, dlist_iterator_ty from, dlist_iterator_ty to);

#endif /* __ILRD_OL127_128_DLINKED_LIST_H__ */
