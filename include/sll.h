/*********************************
 * Reviewer: Avigail				
 * Author: Yohai Azoulai			
 * File: sll.c					
 * ******************************/

#ifndef __SLL_H__
#define __SLL_H__

#include <stddef.h> /*size_t*/


typedef struct node node_t;

typedef struct sll sll_t;

typedef node_t *sll_iterator_t;


/* description: returns the head 
   params: sll
   return value: sll_iterator_t with head node in case the list is empty returns Dummy
   undefined behavior:
   O(1)  */ 
sll_iterator_t SLLBegin(sll_t *slist);

/* description: returns the tail
   params: sll
   return value: sll_iterator_t with tail node (Dummy)
   undefined behavior: 
   O(1) */ 
sll_iterator_t SLLEnd(sll_t *slist);

/* description: returns the next node 
   params: sll
   return value: sll_iterator_t with next node
   undefined behavior: if it is the End node
   O(1)  */ 
sll_iterator_t SLLNext(sll_iterator_t curr);

/* description: returns the value of the curr node
   params: 
   return value: value of the curr node
   undefined behavior: if it the End
   O(1) */ 
void *SLLGet(sll_iterator_t curr);

/* description: sets the data in curr node 
   params: 
   return value: 
   undefined behavior: if it is the end
   O(1)  */ 
void SLLSetData(sll_iterator_t curr, void *data);

/* description: compers bitween 2 iterators  
   params:sll_iterator_t  
   return value: 1 if equal 0 if not
   undefined behavior: if it is the end
   O(1)  */ 
int SLLIteratorsIsEqual(sll_iterator_t iter1, sll_iterator_t iter2);

/* description: creates new singly linked list 
   params: 
   return value: ptr to head node or NULL if failed
   undefined behavior:
   O(1)  */  
sll_t *SLLCreate();

/* description: creates new node in the list before the current 
   params: iterator, void *new_data of the new node
   return value: sll_iterator_t to inserted node if sucsses, end node if fails
   undefined behavior: 
   complexity: O(1) in case of success, O(n) in case of failure
*/  
sll_iterator_t SLLInsert(sll_iterator_t curr, void *new_data);

/* description: remove the curr element 
   params: ptr to node_t
   return value: next elemnt if sucsses, End node if fails
   undefined behavior: 
   complexity: O(1) in case of success, O(n) in case of failure */  
sll_iterator_t SLLRemove(sll_iterator_t curr);

/* description: count number of nodes 
   params: ptr to sll
   return value: number of nodes
   undefined behavior: 
   O(n) */  
size_t SLLCount(const sll_t *slist);

/* description:stops when findes the node. Start at from till to (not included)
   params: sll_iterator_t from, sll_iterator_t to , ptr to comper function
   return value: sll_iterator_t of the found node in case of success and sll_iterator_t to if fails. 
   Match func returns 0 if matches and 1 otherwise
   undefined behavior: if the end node does not exict
   O(n) */  
sll_iterator_t SLLFind(sll_iterator_t from, sll_iterator_t to,void *param, int (*match)(sll_iterator_t curr,void *param));

/* description: implements the func on node from till to (not included)
   params: ptr to the start node,ptr to the end node, and ptr to the function
   return value: 0 in case of success, none-zero in case of failure 
   action function returns 0 in case of success and none-zero in case of failure
   undefined behavior: if you cant implement the function on the nodes, if the end node does not exist
   O(n)*/  
int SLLForEach(sll_iterator_t from, sll_iterator_t to, void *param, int (*action)(sll_iterator_t curr,void *param));

/* description: destroys singly linked list 
   params: ptr to sll
   undefined behavior:
   O(n) */  
void SLLDestroy(sll_t *slist);

/* description: Append 2 lists into 1 & deletes sll1 dummy.
   params: ptr to sll1 & ptr to sll2
   return : pointer to sll1 head.
   undefined behavior : 
   O(1) */ 
sll_t *SLLAppend(sll_t *slist1, sll_t *slist2);

/* description: Gives back iterator to the Nth value.
   params: iterator to curr & n of skips.
   return : iterator to .
   undefined behavior : 
   O(1) */ 
sll_iterator_t GetNthNext(sll_iterator_t curr, size_t n);

/* description: Append 2 lists into 1 & deletes sll1 dummy.
   params: ptr to sll1 & ptr to sll2
   return : pointer to sll1 head.
   undefined behavior : 
   O(1) */ 
sll_iterator_t FindNthNumFromTail(sll_t *slist,size_t n);


#endif /* __SLL_H__ */
