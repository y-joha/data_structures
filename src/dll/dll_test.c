/*********************************
 * Reviewer:                
 * Author: Shani Horden          
 * File: doubly_lonked_list_test.c                 
 * ******************************/
#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/
#include "dll.h"

int Compare(const void *list_data, const void *data) 
{
    if (*(int*)list_data == *(int*)data)
    {
        return 1;
    }

    return 0;
}

int BigerTen(const void *list_data, const void *data) 
{
    if (*(int*)list_data >= *(int*)data)
    {
        return 1;
    }

    return 0;
}

int PlusTen(void *list_data, void *param)
{
    *(int*)list_data += *(int*)param;
    return 0;
}

void TestAllQuick()
{
    int x=8, y=12, z=10;
    dll_t *list= DListCreate();
    dll_iterator_t start = DListBegin(list);
    assert (list);
    assert (DListEnd(list) == DListBegin(list));
    assert(1 == DListIsEmpty(list));
    assert(0 == DListSize(list) );
    DListInsert(list, start, &x);
    assert(0 ==  DListIsEmpty(list));
    assert(1 == DListSize(list));
    DListInsert(list, start, &x);
    assert(2 == DListSize(list));
    assert(1 == DListIsSameIter(DListBegin(list),DListBegin(list)));
    assert(0 == DListIsSameIter(DListBegin(list),DListNext(DListBegin(list))));
    assert(8 == *(int*)(DListGetData(DListBegin(list))));


    DListRemove(DListBegin(list));
    assert(1 == DListSize(list) );

    DListPushFront(list, &x);
    assert(2 == DListSize(list) );

    DListPushBack(list, &x);
    assert(3 == DListSize(list) );

    DListPopFront(list);
    assert(2 == DListSize(list) );

    DListPopBack(list);
    assert(1 == DListSize(list) );

    assert(0 == DListIsEmpty(list));

    assert (DListEnd(list) == DListFind(DListBegin(list), DListEnd(list), &y, Compare));
    assert (DListBegin(list) == DListFind(DListBegin(list), DListEnd(list), &x, Compare));

    DListPushBack(list, &y);
    DListForEach(DListBegin(list), DListNext(DListBegin(list)), &z, 
                                        PlusTen);
    
    assert (*(int*)DListGetData(DListBegin(list)) == 18);
    assert (*(int*)DListGetData(DListNext(DListBegin(list))) == 12);

     DListForEach(DListBegin(list), DListEnd(list), &z, 
                                        PlusTen);
     assert (*(int*)DListGetData(DListBegin(list)) == 28);
    assert (*(int*)DListGetData(DListNext(DListBegin(list))) == 22);

        DListDestroy(list);

}


void TestFinds ()
{
    int x=8, y=12, z=137, a = 5, b=10;
    dll_t *list= DListCreate();
    dll_t *list2= DListCreate();
    
    DListInsert(list, DListEnd(list), &x);
    DListInsert(list, DListEnd(list), &y);
    DListInsert(list, DListEnd(list), &z);
    DListInsert(list, DListEnd(list), &a);

    assert (137 == *(int*)DListGetData(DListFind(DListBegin(list), DListEnd(list), &z,Compare)));
    
    DListMultiFind(DListBegin(list), DListEnd(list), list2, &b, BigerTen);

    assert (2 == DListSize(list2));
    assert (4 == DListSize(list));
    assert (12 == *(int*)DListGetData(DListBegin(list2)));
    assert (137 == *(int*)DListGetData(DListNext(DListBegin(list2))));

    DListDestroy(list);
    DListDestroy(list2);

}

void TestSplice()
{
    int x=8, y=12, z=137, a = 5, b=10;
    int s=90, h = 28;
    dll_t *list= DListCreate();
    dll_t *list2= DListCreate();
    
    DListInsert(list, DListEnd(list), &x);
    DListInsert(list, DListEnd(list), &y);
    DListInsert(list, DListEnd(list), &z);
    DListInsert(list, DListEnd(list), &a);
    DListInsert(list, DListEnd(list), &b);

    DListInsert(list2, DListEnd(list2), &s);
    DListInsert(list2, DListEnd(list2), &h);

    DListSplice(DListPrev(DListPrev(DListEnd(list))), DListBegin(list2), DListEnd(list2));
    assert (0 == DListSize(list2));
    assert (7 == DListSize(list));

    assert (90 == *(int*)DListGetData(DListNext(DListNext(DListNext(DListBegin(list))))));

    DListDestroy(list);
    DListDestroy(list2);


}

int main ()
{
        TestAllQuick();
        TestFinds ();
        TestSplice();
        return 0;
}
