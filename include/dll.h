/*********************************
 * Reviewer: Nofar				
 * Author: Yohai Azoulai			
 * File: dll.c					
 * ******************************/

#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h> /* size_t */

typedef struct dll dll_t;
typedef struct dll_node *dll_iterator_t;

typedef int (*action_func_t)(void *list_data, void *param);
typedef int (*is_match_t)(const void *list_data, const void *data);





dll_t *DListCreate(void);
/* description: creates new doubly linked list  + Creates 2 dummies
   params: 
   return value: ptr to head node or NULL if failed
   undefined behavior:
   O(1)  */  

void DListDestroy(dll_t *dlist);
/* description: destroys doubly linked list 
   params: ptr to dll
   undefined behavior:
   O(n) */  

size_t DListSize(const dll_t *dlist);
/* description: count number of nodes in dll
   params: ptr to dll
   return value: number of nodes
   undefined behavior: 
   O(n) */  

int DListIsEmpty(const dll_t *dlist);
/* description: count number of nodes in dll
   params: ptr to dll
   return value: number of nodes
   undefined behavior: 
   O(1) */ 

dll_iterator_t DListBegin(const dll_t *dlist);
/* description: returns the head 
   params: dll
   return value: dll_iterator_t with head node in case the list is empty returns Dummy
   undefined behavior:
   O(1)  */ 

dll_iterator_t DListEnd(const dll_t *dlist);
/* description: returns the tail 
   params: dll
   return value: dll_iterator_t with tail node (Dummy)
   undefined behavior: 
   O(1) */ 

dll_iterator_t DListNext(const dll_iterator_t curr);
/* description: returns the next node 
   params: dll_iterator_t
   return value: dll_iterator_t with next node
   undefined behavior: if it is the End node
   O(1)  */ 

dll_iterator_t DListPrev(const dll_iterator_t curr);
/* description: returns the previous node 
   params: dll_iterator_t
   return value: dll_iterator_t with previous node
   undefined behavior: if it is the begining node
   O(1)  */ 

int DListIsSameIter(dll_iterator_t iter1, dll_iterator_t iter2);
/* description: compers bitween 2 iterators  
   params:dll_iterator_t  
   return value: 1 if equal 0 if not
   undefined behavior: if it is the end
   O(1)  */ 

void *DListGetData(dll_iterator_t curr);
/* description: returns the data of the curr node
   params: 
   return value: data of the curr node
   undefined behavior: if it the End
   O(1) */ 

dll_iterator_t DListPushFront(dll_t *dlist, void *data);
/*  description: return int on inserting at front instead of head
    params: dll_t , void*
    return value: iterator created.
    undefined behavior:
    complexity: O(1)*/

dll_iterator_t DListPushBack(dll_t *dlist, void *data);
/*  description: return int on inserting at back before tail
    params: dll_t , void*
    return value: iterator created.  ** nof :  return iterator || Corrected **
    undefined behavior:
    complexity: O(1)*/

void *DListPopFront(dll_t *dlist);
/*  description: return int on extrecting at front & reassigning head
    params: dll_t , void*
    return value: value stored in ->data.
    undefined behavior:
    complexity: O(1)*/

void *DListPopBack(dll_t *dlist);
/*  description: return int on extrecting at back before tail
    params: dll_t , void*
    return value: value stored in ->data.
    undefined behavior:
    complexity: O(1)*/

dll_iterator_t DListInsert(dll_t *dlist, dll_iterator_t curr, void *data);
/* description: creates new node in the list before the curr 
   params: iterator, void *new_data of the new node
   return value: dll_iterator_t to inserted node if sucsses, end node if fails
   undefined behavior: 
   complexity: O(1) in case of success, O(n) in case of failure*/  

dll_iterator_t DListRemove(dll_iterator_t curr);
/* description: remove the curr element 
   params: ptr to node_t
   return value: next elemnt if sucsses, End node if fails
   undefined behavior: 
   complexity: O(1) in case of success, O(n) in case of failure */  

dll_iterator_t DListSplice(dll_iterator_t where,
                             dll_iterator_t begin, dll_iterator_t end); 
/* description: joins 2 lists together from ->begin till end (not included)
               before where
   params: iters where of list a and  begin & end of list b
   return : returns the previous node to where, at the begining of 
   new splised data.
   ... nof : it returns the node after the concatnation || Corrected... 

   undefined behavior : 
   O(1) */ 

int DListForEach(dll_iterator_t from, dll_iterator_t to, 
    void *param, action_func_t func);
/* description: implements the func on node from till to (not included)
   params: ptr to the start node,ptr to the end node, and ptr to the function
   return value: 0 in case of success, none-zero in case of failure 
   action function returns 0 in case of success and none-zero in case of failure
   undefined behavior: if you cant implement the function on the nodes, if the end node does not exist
   O(n)*/  

dll_iterator_t DListFind(dll_iterator_t from, dll_iterator_t to, const void *data, is_match_t func); 
/* description:stops when findes the node. Start at from till to (not included)
   params: dll_iterator from, dll_iterator to , ptr to comper function
   return value: dll_iterator of the found node in case of success and dll_iterator to if fails. 
   Match func returns 0 if matches and 1 otherwise
   undefined behavior: if the end node does not exict
   O(n) */  

int DListMultiFind(dll_iterator_t from, dll_iterator_t to, dll_t *dlist_dest, const void *data, is_match_t func);
/* description:copies data in nodes (data refrences) and provide an out-param list argument(a refrence to the refrences?)
   params: dll_iterator_t from, dll_iterator_t to
   return value: 0 on success, Non-0 Value on failiure.
   undefined behavior: 
   O(n) 
....nof : it return int value - so 0
 for success and nonzero val for fail..Corrected..
   */  

#endif



