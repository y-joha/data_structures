/*********************************
 * Reviewer: 				
 * Author:		
 * File: sorted_list.c					
 * ******************************/

#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__


#include <stddef.h> /* size_t */
#include "dll.h"

typedef struct sorted_list sorted_list_t;
typedef struct sorted_list_iterator sorted_list_iterator_t;

typedef int(*sorted_list_compare_func_t)(const void *old_data,
                                         const void *new_data, void* userparam); /* O(1) */
typedef int(*sorted_list_is_match_func_t)(const void *list_data, 
                                          const void *data); 
                                          /* O(1), non_zero if match, zero otherwise */
typedef int(*sorted_list_action_func_t)(void *list_data, 
                                        void *data); 
                                        /* O(1), non_zero if failed, zero otherwise */


sorted_list_iterator_t SortedListIterInit(void);
/* description : This function initialized the iterator.
   params : 
   return : sorted list iteratod initialized to 0/NULL.
   undefined behavior:
   O(1) */ 

sorted_list_t *SortedListCreate(sorted_list_compare_func_t compare_func, void *userparam);
/* description : creates a list based on set value to compare to
   params : compare_function for Rule
   return : iterator to newly created sort list.
   undefined behavior:
   O(1) */ 

void SortedListDestroy(sorted_list_t *list);
/* description : recives list, and destroys the nodes, free malloced space.
   params : list address in order to demolish the list.
   return : 
   undefined behavior:
   O(n) */ 

size_t SortedListSize(const sorted_list_t *list);
/* description : counts the number of nodes in the sorted list.
   params : list address.
   return : return the number of nodes on the list
   undefined behavior:
   O(n) */  

int SortedListIsEmpty(const sorted_list_t *list);
/* description : Checks wether the list is empty or not.
   params : list address to check.
   return : returns 1 on empty, 0 on fail.
   undefined behavior:
   O(1) */ 

sorted_list_iterator_t SortedListBegin(const sorted_list_t *list);
/* description : function recives list and point to its head.
   params : sorted_list_t list.
   return : iterator to head node
   undefined behavior:
   O(1) */ 

sorted_list_iterator_t SortedListEnd(const sorted_list_t *list);
/* description : function recives list and point to its tail.
   params : sorted_list_t list.
   return : iterator to tail
   undefined behavior:
   O(1) */  

sorted_list_iterator_t SortedListNext(sorted_list_iterator_t iter);
/* description : function recives iterator to list 
                  and give next
   params : iterator_t iter.
   return : iterator to next node inline.
   undefined behavior:
   O(1) */  

sorted_list_iterator_t SortedListPrev(sorted_list_iterator_t iter); 
/* description : function recives iterator to list 
                  and give prev
   params : iterator_t iter.
   return : iterator to prev node inline.
   undefined behavior: 
   O(1) */  

int SortedListIsSameIter(sorted_list_iterator_t iter1, 
                         sorted_list_iterator_t iter2);
/* description : function recives 2 iterators and checks if they
                  are equal.
   params : iterator_t iter1 , iterator_t iter2.
   return : 0 on success, non zero value on fail.
   undefined behavior:
   O(1) */  

void *SortedListGetData(sorted_list_iterator_t iter); 
/* description : function recives iterator to iter, and 
                  pulls the data held in that node.
   params : iterator_t iter.
   return : returns void *ptr to data. 
            Review: return pointer to data || Corrected
   undefined behavior:
   O(1) */  

sorted_list_iterator_t SortedListInsert(sorted_list_t *list, 
                                        void *data);
/* description : function inserts a node in the correct location.
                  in relation to our condition.
   params : recives address to list, and void *data.
   return : returns iterator to inserted node.
   undefined behavior:
   O(n) */ 

void *SortedListPopFront(sorted_list_t *list); 
/* description : recives list and removes it first value
   params : list address to remove head->next.
   return : return the data fetched from the list.
   undefined behavior:
   O(1) */ 

void *SortedListPopBack(sorted_list_t *list);
/* description : -----------------------------
   params : list address to remove tail->prev
   return : returns the data fetched from the list.
   undefined behavior:
   O(1) */  

sorted_list_iterator_t SortedListRemove(sorted_list_iterator_t curr); 
/* description : removes a node for iter position sent to func.
   params : iter
   return : the removed node from the list.
   undefined behavior:
   O(1) */  

int SortedListForEach(sorted_list_iterator_t from, 
                      sorted_list_iterator_t to, 
                      void *param, 
                      sorted_list_action_func_t action_func); 
                      /* stop when failed and return non-zero, 
                              return zero if success */  
/* description: recives starting location from and run on the nodes 
                untill to (not included),
                performing the action of the func, using param. 
   params :  iterator_t from iterator_t to void* param, action_func ptr.
   return : int value 0 on success and non-0 value as successes so far.
   Review: on failure should return non-zero value that tells how many times 
   it did succeeded and 0 if success|| Corrected
   undefined behavior:
   O(n) */ 

void SortedListMerge(sorted_list_t *dest_list, sorted_list_t *src_list); 
/* description: this func recives the addresses of 2 lists	
                  Review: why tell the user that you use splice? || Corrected
                  and joins them together to one another.
   params : address to sorted list dest_list, and src_list.
   return : 
   undefined behavior:
   O(n+m) */ 

sorted_list_iterator_t SortedListFind(sorted_list_t *list, 
                                      sorted_list_iterator_t from, 
                                      sorted_list_iterator_t to, 
                                      const void *data); 
                                      /*  end of list if not found */
/* description : finds the node which upholds the condition of the list.
   params : sorted_list_t list iterator_t from iterator_t to void* data.
   return value : returnes iterator to node which insert 
                  enters before him.else return : end of list
   undefined behavior : 
   complexity : O(n) */

sorted_list_iterator_t 
            SortedListFindIf(sorted_list_iterator_t from, 
                             sorted_list_iterator_t to, 
                             const void *data, 
                             sorted_list_is_match_func_t is_match_func); 
/* description : finds the node which upholds the condition of the list.
   params : iterator_t from iterator_t to void* param, is_match_func ptr.
   return value : returns iterator to node in which the data is found. 
   undefined behavior : 
   complexity: O(n) */ 

/*Review: need to add here a comment that tells the user not to mess with 
            the struct || Corrected*/


/*
   you see this here?
   dont touch this
   its got 
   baaaaad
   jo-jo
   

   Please do not change struct
   for Proccess Integrity 
*/
struct sorted_list_iterator
{
    dll_iterator_t the_iter;
    
    #ifndef NDEBUG
    sorted_list_t *the_list;
    #endif
};

#endif /* __SORTED_LIST_H__ */
