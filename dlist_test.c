#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdio.h>  /* printf */
#include "dlist.h"

#define UNUSED(x) (void)x

void DlistCreateAndDestroyTest(void);
void DlistInsertBeforeAndGetDataTest(void);
void DlistRemoveTest(void); 
void DlistSetDataTest(void);
void DlistSizeTest(void);
void DlistIsEmptyTest(void);
void DlistIterIsEqualTest(void);
void DlistForEachTest(void);
void DlistFindTest(void);
void DlistMultiFindTest(void);
void DlistSpliceTest(void);
void DlistAppendTest(void);

/* help functions for find and foreach tests */
int SumList(void* num , void* result);
int MultList(void* num , void* result);
int FindNumInList(const void* num , void* value);
int FindEvenNumbers(const void* num , void* value);



int main()
{
	DlistCreateAndDestroyTest();
	DlistInsertBeforeAndGetDataTest();
	DlistRemoveTest(); 
	DlistSetDataTest();
	DlistSizeTest();
	DlistIsEmptyTest();
	DlistIterIsEqualTest();
	DlistForEachTest();
	DlistFindTest();
	DlistSpliceTest();
	DlistAppendTest();
	DlistMultiFindTest();
	printf("\n\n->->->->->->->->-> success!!! <-<-<-<-<-<-<-<-<-<\n\n\n");
	
	return 0;
}


void DlistCreateAndDestroyTest(void)
{
	dlist_ty *dlist = DlistCreate();
	DlistDestroy(dlist);
}

void DlistInsertBeforeAndGetDataTest(void)
{
	int a = 3;
	int b = 4;
	dlist_ty *dlist = DlistCreate();
	DlistInsertBefore(DlistEnd(dlist) , (void*)&a);	
	DlistInsertBefore(DlistEnd(dlist) , (void*)&b);
	assert(*((int*)DlistGetData(DlistBegin(dlist))) == 3);
	assert(*((int*)DlistGetData(DlistNext(DlistBegin(dlist)))) == 4);	
	DlistDestroy(dlist);	
}


void DlistRemoveTest(void)
{
	int a = 3;
	int b = 4;
	dlist_ty *dlist = DlistCreate();
	DlistInsertBefore(DlistEnd(dlist) , (void*)&a);	
	DlistInsertBefore(DlistEnd(dlist) , (void*)&b);
	DlistRemove(DlistBegin(dlist));
	assert(*((int*)DlistGetData(DlistBegin(dlist))) == 4);
	DlistDestroy(dlist);
}



void DlistSetDataTest(void)
{
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	int x = 12;
	int i = 0;
	dlist_ty *dlist = DlistCreate();
	
	for(i = 0 ; i < 10 ; ++i)
	{
		DlistInsertBefore(DlistEnd(dlist) , (void*)(arr + i));	
	}
	DlistSetData(DlistPrev(DlistEnd(dlist)) , (void*)&x);
	
	assert(*((int*)DlistGetData(DlistPrev(DlistEnd(dlist)))) == 12);
	DlistDestroy(dlist);
}


void DlistSizeTest(void)
{
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	int i = 0;
	dlist_ty *dlist = DlistCreate();
	
	for(i = 0 ; i < 10 ; ++i)
	{
		DlistInsertBefore(DlistEnd(dlist) , (void*)(arr + i));	
	}

	assert(DlistSize(dlist) == 10);
	DlistRemove(DlistBegin(dlist));
	assert(DlistSize(dlist) == 9);
	DlistDestroy(dlist);	
}


void DlistIsEmptyTest(void)
{
	int a = 3;
	dlist_ty *dlist = DlistCreate();
	assert(DlistIsEmpty(dlist) == 1);
	DlistInsertBefore(DlistEnd(dlist) , (void*)&a);	
	assert(DlistIsEmpty(dlist) == 0);
	DlistDestroy(dlist);

}


void DlistIterIsEqualTest(void)
{
	int a = 3;
	dlist_ty *dlist = DlistCreate();
	dlist_iterator_ty iterator1 = NULL;
	dlist_iterator_ty iterator2 = NULL;
	DlistInsertBefore(DlistEnd(dlist) , (void*)&a);
	iterator1 = DlistBegin(dlist);
	iterator2 = DlistEnd(dlist);	
	assert(DlistIterIsEqual(iterator1 , iterator2) == 0);
	assert(DlistIterIsEqual(DlistNext(iterator1) , iterator2) == 1);
	
	DlistDestroy(dlist);
}


void DlistForEachTest(void)
{
	dlist_ty *dlist = DlistCreate();
	action_ty action_func1 = &SumList;
	action_ty action_func2 = &MultList;
	int i = 0;
	int sum_of_list = 0;
	int mult_of_list = 1;

	int arr[10] = {2,2,2,2,2,2,2,2,2,2};
	
	for (i = 0 ; i < 10 ; ++i)
	{
		DlistInsertBefore(DlistBegin(dlist) , (void*)(arr + i));
	}
	
	DlistForEach(DlistBegin(dlist) , DlistEnd(dlist) , action_func1 ,  (void*)&sum_of_list);
	assert(sum_of_list == 20);
	
	DlistForEach(DlistBegin(dlist) , DlistEnd(dlist) , action_func2 ,  (void*)&mult_of_list);
	assert(mult_of_list == 1024);
	DlistDestroy(dlist);
}


void DlistFindTest(void)
{

	dlist_ty *dlist = DlistCreate();
	is_match_ty match_func = &FindNumInList;
	dlist_iterator_ty iterator = NULL;
	int test_value = 4;
	int i = 0;

	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	
	for (i = 0 ; i < 10 ; ++i)
	{
		DlistInsertBefore(DlistBegin(dlist) , (void*)(arr + i));
	}
	
	iterator = DlistFind(DlistBegin(dlist) , DlistEnd(dlist) , match_func ,  (void*)&test_value);
	assert(*((int*)DlistGetData(iterator)) == 4);
	
	test_value = 11;
	iterator = DlistFind(DlistBegin(dlist) , DlistEnd(dlist) , match_func ,  (void*)&test_value);
	assert(iterator == DlistEnd(dlist));

	DlistDestroy(dlist);

}



void DlistSpliceTest(void)
{

	dlist_ty *dlist1 = DlistCreate();
	dlist_ty *dlist2 = DlistCreate();
	dlist_iterator_ty where = NULL;
	dlist_iterator_ty from = NULL;
	dlist_iterator_ty to = NULL;
	dlist_iterator_ty test_iter = NULL;
	is_match_ty match_func = &FindNumInList;
	
	int where_value = 8;
	int from_value = 4;
	int to_value = 8;
	int i = 0;
	int arr1[10] = {1,2,3,8,9,10,11,12,13,14};
	int arr2[10] = {1,2,3,4,5,6,7,8,9,10};
	
	for (i = 0 ; i < 10 ; ++i)
	{
		DlistInsertBefore(DlistEnd(dlist1) , (void*)(arr1 + i));
	}
	
	for (i = 0 ; i < 10 ; ++i)
	{
		DlistInsertBefore(DlistEnd(dlist2) , (void*)(arr2 + i));
	}	
	
	where = DlistFind(DlistBegin(dlist1) , DlistEnd(dlist1) , match_func ,  (void*)&where_value);
	from = DlistFind(DlistBegin(dlist2) , DlistEnd(dlist2) , match_func ,  (void*)&from_value);
	to = DlistFind(DlistBegin(dlist2) , DlistEnd(dlist2) , match_func ,  (void*)&to_value);
	
	DlistSplice(where , from , to);
	
	test_iter = DlistBegin(dlist1);
	for(i = 1 ; i <= 14 ; ++i)
	{
		assert(*((int*)DlistGetData(test_iter)) == i);
		test_iter = DlistNext(test_iter);
	}
	
	test_iter = DlistBegin(dlist2);
	
	for(i = 1 ; i <= 6 ; ++i)
	{
		assert(*((int*)DlistGetData(test_iter)) != 4);
		assert(*((int*)DlistGetData(test_iter)) != 5);
		assert(*((int*)DlistGetData(test_iter)) != 6);
		assert(*((int*)DlistGetData(test_iter)) != 7);
		test_iter = DlistNext(test_iter);
	}
	
	DlistDestroy(dlist1);
	DlistDestroy(dlist2);
	
}




void DlistAppendTest(void)
{

	dlist_ty *dlist1 = DlistCreate();
	dlist_ty *dlist2 = DlistCreate();
	dlist_ty *dlist3 = DlistCreate();
	dlist_ty *dlist4 = DlistCreate();
	int i = 0;
	dlist_iterator_ty iterator = NULL;

	int arr1[10] = {10,9,8,7,6,5,4,3,2,1};
	int arr2[10] = {20,19,18,17,16,15,14,13,12,11};
	
	for (i = 0 ; i < 10 ; ++i)
	{
		DlistInsertBefore(DlistBegin(dlist1) , (void*)(arr1 + i));
	}	
	
	for (i = 0 ; i < 10 ; ++i)
	{
		DlistInsertBefore(DlistBegin(dlist2) , (void*)(arr2 + i));
	}	
	
	DlistSplice(DlistEnd(dlist1) , DlistBegin(dlist2) , DlistEnd(dlist2));
	iterator = DlistBegin(dlist1);
	
	for (i = 1 ; i < 13 ; ++i)
	{
		iterator = DlistNext(iterator);
	}
	
	assert(*((int*)DlistGetData(iterator)) == 13);

	DlistInsertBefore(DlistBegin(dlist4) , (void*)(arr1 + 4));
	DlistSplice(DlistEnd(dlist3) , DlistBegin(dlist4) , DlistEnd(dlist4));
	assert(*((int*)DlistGetData(DlistBegin(dlist3))) == 6);

	DlistDestroy(dlist1);
	DlistDestroy(dlist2);
	DlistDestroy(dlist3);
	DlistDestroy(dlist4);
	
}




void DlistMultiFindTest(void)
{
	
	dlist_ty *dlist = DlistCreate();
	dlist_ty *dlist_result = DlistCreate();
	dlist_iterator_ty test_iter = NULL;
	is_match_ty match_func = &FindEvenNumbers;
	int count = 0;
	int i = 0;
	int arr[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	for (i = 0 ; i < 15 ; ++i)
	{
		DlistInsertBefore(DlistEnd(dlist) , (void*)(arr + i));
	}
	
	count = DlistMultiFind(DlistBegin(dlist), DlistEnd(dlist) , dlist_result , match_func , NULL);
	
	test_iter = DlistBegin(dlist_result);
	for(i = 1 ; i <= 7 ; ++i)
	{
		assert(*((int*)DlistGetData(test_iter)) == i * 2);
		test_iter = DlistNext(test_iter);
	}
	
	assert(count == 7);
	
	DlistDestroy(dlist);
	DlistDestroy(dlist_result);
	
}




int SumList(void* num , void* result)
{
	*((int*)result) += *((int*)num);
	return 0;
}

int MultList(void* num , void* result)
{
	*((int*)result) *= *((int*)num);
	return 0;
}

int FindNumInList(const void* num , void* value)
{
	return (*((int*)num) == *((int*)value)) ? 1 : 0;
}

int FindEvenNumbers(const void* num , void *value)
{
	UNUSED(value);
	return (*((int*)num) % 2 == 0);
}















