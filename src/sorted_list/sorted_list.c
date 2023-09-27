/*********************************
 * Reviewer: Roy Mantel             
 * Author: Yohai Azoulai            
 * File: sorted_list.c                  
 * ******************************/
 
 /**/

#include <stdlib.h> /*malloc & free*/
#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/
#include "sorted_list.h"


/*******Structs******/

struct sorted_list 
{
    dll_t *list;
    sorted_list_compare_func_t comp_func;
    void *user_param;
};


/*Service functions*/



/*************/

sorted_list_iterator_t SortedListIterInit(void)
{
	sorted_list_iterator_t iter;
	iter.the_iter=NULL;
	#ifndef NDEBUG
	iter.the_list = NULL;
	#endif
	return iter;
}


sorted_list_t *SortedListCreate(sorted_list_compare_func_t compare_func,void *user_param)
{
	sorted_list_t *sort_l = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	if(NULL == sort_l)
	{
		return NULL;
	}
	sort_l->list = DListCreate();
	if(NULL == sort_l->list)
	{
		free(sort_l);	/*Review: sort_l = NULL after free, coding convention || Corrected*/
		sort_l = NULL;
		return NULL;
	}
	sort_l->comp_func = compare_func;
	sort_l->user_param = user_param;

	return sort_l;
}


void SortedListDestroy(sorted_list_t *list)
{
	assert(list);
	DListDestroy(list->list);
	list->list = NULL;
	free(list);
	list = NULL;
}


size_t SortedListSize(const sorted_list_t *list)
{
	assert(list);
	return DListSize(list->list);	/*Review: this is a bit confusing, maybe use different names || Per API*/
}


int SortedListIsEmpty(const sorted_list_t *list)
{
	assert(list);
	return DListIsEmpty(list->list);	/*Review: same names || Per API*/
}


sorted_list_iterator_t SortedListBegin(const sorted_list_t *list)
{
	sorted_list_iterator_t iter;
	assert(list);

	iter.the_iter = DListBegin(list->list);	/*Review: same names || Per API*/
	#ifndef NDEBUG
	iter.the_list = (sorted_list_t *)list;
	#endif
	return iter;
}


sorted_list_iterator_t SortedListEnd(const sorted_list_t *list)
{
	sorted_list_iterator_t iter;
	assert(list);

	iter.the_iter = DListEnd(list->list);	/*Review: same names || Per API*/
	#ifndef NDEBUG
	iter.the_list = (sorted_list_t *)list;
	#endif
	return iter;
}


sorted_list_iterator_t SortedListNext(sorted_list_iterator_t iter)
{
	iter.the_iter = DListNext(iter.the_iter);
	return iter;
}


sorted_list_iterator_t SortedListPrev(sorted_list_iterator_t iter)
{
	iter.the_iter = DListPrev(iter.the_iter);
	return iter;
}


int SortedListIsSameIter(sorted_list_iterator_t iter1, sorted_list_iterator_t iter2)
{
	/*Review: the above test isn't necessary, there is no situation that
				dlliter is the same but not on the same list || Corrected*/
	return (DListIsSameIter(iter1.the_iter,iter2.the_iter));
}


void *SortedListGetData(sorted_list_iterator_t iter)
{
	return DListGetData(iter.the_iter);
}


sorted_list_iterator_t SortedListInsert(sorted_list_t *list, 
										void *data)
{
	sorted_list_iterator_t iter = SortedListIterInit();	/*Review: don't leave it uninitialized,
															use SortedListIterInit || Corrected*/
	assert(list);

	iter = SortedListFind(list,SortedListBegin(list),
							   SortedListEnd(list),data);
	iter.the_iter = DListInsert(list->list,iter.the_iter,data);
    	
    						  /*Review: only when #ifndef, but unnecessary -
    									iter already got this value
    									when you used SortedListFind || Corrected*/

	return iter;
}


void *SortedListPopFront(sorted_list_t *list) /* O(1) */
{
    return DListPopFront(list->list);	/*Review: same names || Per API*/
}

void *SortedListPopBack(sorted_list_t *list) /* O(1) */
{
    return DListPopBack(list->list);	/*Review: same names || Per API*/
}

sorted_list_iterator_t SortedListRemove(sorted_list_iterator_t curr) /* O(1), returns the removed iterator (now invalid) */ /*Review: this description was changed after SU*/
{
    curr.the_iter = DListRemove(curr.the_iter);
    return curr;
}


int SortedListForEach(sorted_list_iterator_t from, 
					  sorted_list_iterator_t to,
					  void *param,
					  sorted_list_action_func_t action_func)
/*Review: LONG line, longer then 80 characters || Corrected*/
{
    assert(from.the_list == to.the_list);
    return DListForEach(from.the_iter,to.the_iter,param,action_func);
    /*Review: return value should be 0 on success,
    			if failed should return number of successes until failure || Changed dll to return param, on failiure*/
	/*Review: remove examples and unused code || Corrected*/
}

void SortedListMerge(sorted_list_t *dest_list, sorted_list_t *src_list)
{
	sorted_list_iterator_t where = SortedListBegin(dest_list);
	sorted_list_iterator_t begin = SortedListBegin(src_list);
	sorted_list_iterator_t end = SortedListBegin(src_list);

	assert(dest_list);
	assert(src_list);

	while(!SortedListIsEmpty(src_list))
	{
		where = SortedListFind(dest_list, where, SortedListEnd(dest_list), SortedListGetData(begin));
		
		if(SortedListIsSameIter(where, SortedListEnd(dest_list)))
		{
			end = SortedListEnd(src_list);
		}

		else
		{
			end = SortedListFind(src_list, begin, SortedListEnd(src_list), SortedListGetData(where));
		}

		DListSplice(where.the_iter, begin.the_iter ,end.the_iter);

		begin = end;
	}

}



sorted_list_iterator_t SortedListFind(sorted_list_t *list, 
										sorted_list_iterator_t from,
									  	sorted_list_iterator_t to,
									  	const void *data) 
									  	/* O(n), end of list if not found */
/*Review: LONG line, longer then 80 characters || Corrected*/
{
    assert(list);
    assert(data);

    assert(from.the_list == to.the_list);
    
    while(!SortedListIsSameIter(from,to))
    {
        if(0 >  list->comp_func(SortedListGetData(from),
        						data,
        						list->user_param))
        {
            return from;
        }
        from = SortedListNext(from);
    }

    return from;	/*Review: need to return End of the list if not found (from=to) || Corrected*/
}


sorted_list_iterator_t SortedListFindIf(sorted_list_iterator_t from,
									    sorted_list_iterator_t to, 
									    const void *data, 
									    sorted_list_is_match_func_t is_match_func)
/*Review: LONG line, longer then 80 characters || Corrected*/
{
    assert(data);
    	/*Review: assert is already used only on debug, this #ifndef is redundant || Corrected*/
    assert(from.the_list == to.the_list);
    
   
    while(!SortedListIsSameIter(from,to))
    {
        if(is_match_func(SortedListGetData(from),data))
        {
            return from;
        }
        from = SortedListNext(from);
    }

    return to;
}

