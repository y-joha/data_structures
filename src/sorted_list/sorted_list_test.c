/*********************************
 * Reviewer: Daniel B               
 * Author:  Shani Horden    
 * File: sorted_list.c                  
 * ******************************/
#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/
#include "sorted_list.h"

int CompareInt (const void *data1, const void *data2, void *);
int CompareIntDown (const void *data1, const void *data2, void *);
int PlusTen(void *list_data, void *param);
void TestAll ();
void TestForEach();
void TestMerge();
void TestFind();

int main()
{
	
	TestAll();
	TestForEach();
	TestMerge();
	TestFind();



	return 0;
}

int CompareInt (const void *data1, const void *data2, void *user_param)
{
	(void)user_param;
	return (*(int*)data2 - *(int*)data1);
}

int CompareIntDown (const void *data1, const void *data2, void *user_param)
{
	(void)user_param;
	return (*(int*)data1 - *(int*)data2);
}

int PlusParam(void *list_data, void *param)
{
    *(int*)list_data += *(int*)param;
    return 0;
}

int Compare(const void *list_data, const void *data) 
{
    if (*(int*)list_data == *(int*)data)
    {
        return 1;
    }

    return 0;
}


void TestAll()
{
	int x = 8 , y = 2, z =4; 
	sorted_list_t *list = SortedListCreate(CompareInt, NULL);
	sorted_list_iterator_t iter1 = SortedListIterInit(), iter2 = SortedListIterInit();
	assert(0 ==  SortedListSize(list));
	assert (1 == SortedListIsEmpty(list));
	iter1  =  SortedListBegin(list);
	iter2 = SortedListEnd(list);
	assert (1 == SortedListIsSameIter(iter1, iter2));
	
	SortedListInsert(list, &x);
	SortedListInsert(list, &y);
	assert(2 == SortedListSize(list));
	assert(0 == SortedListIsEmpty(list));
	iter1  =  SortedListBegin(list);
	assert(0 == SortedListIsSameIter(iter1, iter2));

	SortedListInsert(list, &z);

	while (!SortedListIsSameIter(iter1, iter2))
	{
		printf("%d,", *(int*)SortedListGetData(iter1));
		iter1= SortedListNext(iter1);
	}
	printf("\n");

	SortedListPopFront(list);
	assert(2 == SortedListSize(list));
	SortedListPopBack(list);
	assert(1 == SortedListSize(list));

	iter1  =  SortedListBegin(list);
	while (!SortedListIsSameIter(iter1, iter2))
	{
		printf("%d", *(int*)SortedListGetData(iter1));
		iter1= SortedListNext(iter1);
	}
	printf("\n");
	SortedListRemove(SortedListBegin(list));
	assert(0 == SortedListSize(list));
	
	SortedListDestroy(list);
}


void TestForEach()
{
	int x = 8 , y = 2, z =4, a=10; 
	sorted_list_t *list = SortedListCreate(CompareIntDown, NULL);
	sorted_list_iterator_t curr = SortedListIterInit();
	SortedListInsert(list, &x);
	SortedListInsert(list, &y);
	SortedListInsert(list, &z);

	for (curr = SortedListBegin(list); !SortedListIsSameIter(curr, SortedListEnd(list)); curr = SortedListNext(curr))
	{
		printf ("%d,", *(int*)SortedListGetData(curr));
	}
	printf("\n");

	SortedListForEach(SortedListBegin(list), SortedListEnd(list), &a,PlusParam );
	for (curr = SortedListBegin(list); !SortedListIsSameIter(curr, SortedListEnd(list)); curr = SortedListNext(curr))
	{
		printf ("%d,", *(int*)SortedListGetData(curr));
	}
	printf("\n");


	SortedListDestroy(list);

}


void TestMerge()
{
	int x = 1 , y = 8, z =12 , o = 15, m = 200;
	int a = 2 , b = 4, c = 6, d = 10, e = 17, f= 43, g=55, k = 400;
	sorted_list_t *list1 = SortedListCreate(CompareInt,NULL);
	sorted_list_t *list2 = SortedListCreate(CompareInt, NULL);
	sorted_list_iterator_t iter ;

	SortedListInsert(list1, &x);
	SortedListInsert(list1, &y);
	SortedListInsert(list1, &z);
	SortedListInsert(list1, &o);
	SortedListInsert(list1, &m);
	
	SortedListInsert(list2, &a);
	SortedListInsert(list2, &b);
	SortedListInsert(list2, &c);
	SortedListInsert(list2, &d);
	SortedListInsert(list2, &e);
	SortedListInsert(list2, &f);
	SortedListInsert(list2, &g);
	SortedListInsert(list2, &k);

	SortedListMerge (list1, list2);
	
	iter = SortedListBegin (list1);
	while (!SortedListIsSameIter(iter, SortedListEnd(list1)))
	{
		printf("%d, ", *(int*)SortedListGetData(iter));
		iter= SortedListNext(iter);
	}
	printf("\n");

	SortedListDestroy(list1);
	SortedListDestroy(list2);

}


void TestFind()
{
	int x = 1 , y = 8, z =12 , o = 15;
	int s=8;
	sorted_list_t *list = SortedListCreate(CompareInt, NULL);
	sorted_list_iterator_t iter = SortedListIterInit();

	SortedListInsert(list, &x);
	SortedListInsert(list, &y);
	SortedListInsert(list, &z);
	SortedListInsert(list, &o);

	iter = SortedListFindIf(SortedListBegin(list), SortedListEnd(list), &s, Compare);

	assert (8 == *(int*)SortedListGetData(iter));


	SortedListDestroy(list);

}
