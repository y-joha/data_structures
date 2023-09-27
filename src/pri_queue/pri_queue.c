/*********************************
 * Reviewer: 				
 * Author: Yohai Azoulai			
 * File: pri_queue.c					
 * ******************************/
 
 /**/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc & free*/
#include "pri_queue.h"
#include "sorted_list.h"
/*******Structs******/

struct p_queue
{
    sorted_list_t *slist;
    compare_t comp_func; /* users regular compare function*/
    void *u_param;       /* this hold user parameter*/
};

struct pqueue_member    /*this is the struct that will be in the 
                            data pointer of the sorted list node*/
{
  ilrd_uid_t uid;
  void *data;
};

/*
typedef struct pqueue_member pq_node_t;  <----

typedef struct p_queue pri_queue_t;   <----
*/


static int PQMatchingMachine(const void *n1,const void *n2)
{
    return UIDIsSame(((pq_node_t *)(n1))->uid,*(ilrd_uid_t *)n2);
}

/*******Service Funcs******/
static int PQCompareFunc(const void *n1, const void * n2, void *pq)
{
    return ((pri_queue_t *)pq)->comp_func(((pq_node_t *)n1)->data, 
                                          ((pq_node_t *)n2)->data, 
                                           (pri_queue_t *)pq);
}


/*static int pq_compare(const void *data1, const void *data2, void *pq)
{
    pri_queue_t temp_pqueue = (pri_queue_t*)pq;
    pq_node_t n1 = *(pq_node_t*)data1;
    pq_node_t n2 = *(pq_node_t*)data2;

    return temp_pqueue->compare_func(n1.data, 
                                     n2.data, 
                                     temp_pqueue->user_param);
}
*/

/*******Funcs Funcs******/

pri_queue_t *PQueueCreate(compare_t priority_func, void *userparam)
{
    pri_queue_t *pq = NULL;
    assert(priority_func);
    
    pq = (pri_queue_t *)malloc(sizeof(pri_queue_t));
    if(NULL == pq)
    {
        return NULL;
    }
    pq->slist = NULL;

    pq->slist = SortedListCreate(PQCompareFunc,pq);
    if(NULL == pq->slist)
    {
        free(pq);   /*Review: pq = NULL after free, 
                                coding convention || Corrected*/
        pq = NULL;
        return NULL;
    }
    pq->comp_func = priority_func;
    pq->u_param = userparam;
    
    return pq;
}

void PQueueDestroy(pri_queue_t *pq)
{
    assert(pq);
    PQueueClear(pq);
    SortedListDestroy(pq->slist);
    free(pq);
    pq = NULL;
}

ilrd_uid_t PQueueEnQueue(pri_queue_t *pq, void *data)
{
    
    pq_node_t *nod_id = NULL;

    assert(pq);

    nod_id = (pq_node_t *)malloc(sizeof(pq_node_t));
    if(!nod_id)
    {
        return g_bad_uid;
    }
    nod_id->uid = UIDGet();
    nod_id->data = data;
    if(SortedListIsSameIter(
                            SortedListInsert(pq->slist, nod_id),
                            SortedListEnd(pq->slist)))
    {
        return g_bad_uid;
    }
    

    return nod_id->uid;
}

int PQueueReEnQueue(pri_queue_t *pq, void *data,ilrd_uid_t old_uid)
{
    
    pq_node_t *nod_id = NULL;

    assert(pq);

    nod_id = (pq_node_t *)malloc(sizeof(pq_node_t));
    if(!nod_id)
    {
        return -1;
    }
    nod_id->uid = old_uid;
    nod_id->data = data;
    if(SortedListIsSameIter(
                            SortedListInsert(pq->slist, nod_id),
                            SortedListEnd(pq->slist)))
    {
        return -1;
    }
    

    return 0;
}

ilrd_uid_t PQueueDeQueue(pri_queue_t *pq)
{
    ilrd_uid_t tmp = UIDGetNull();
    pq_node_t *tmp_ptr = NULL;
    
    assert(pq);
    
    tmp_ptr = SortedListPopFront(pq->slist);
    
    tmp = tmp_ptr->uid;

    free(tmp_ptr);
        
    return tmp;
}

void *PQueuePeek(pri_queue_t *pq)
{
    assert(pq);
    return ((pq_node_t*)SortedListGetData(
                        SortedListBegin(pq->slist)))->data;
}

int PQueueIsEmpty(pri_queue_t *pq)
{
    
    assert(pq);
    return SortedListIsEmpty(pq->slist);
}

size_t PQueueSize(pri_queue_t *pq)
{
    
    assert(pq);
    return SortedListSize(pq->slist);
}

void PQueueClear(pri_queue_t *pq)
{
    
    assert(pq);
    while(!PQueueIsEmpty(pq))
    {
        PQueueDeQueue(pq);
    }
}

void *PQueueErase(pri_queue_t *pq, ilrd_uid_t uid)
{
    pq_node_t *handler = NULL;
    void * return_val = NULL;
    sorted_list_iterator_t iter = SortedListIterInit();

    assert(pq);

    iter = SortedListFindIf(SortedListBegin(pq->slist),
                                    SortedListEnd(pq->slist),&uid, 
                                    PQMatchingMachine);

    if(SortedListIsSameIter(iter, SortedListEnd(pq -> slist)))
    {
        return NULL;
    }


    handler = (pq_node_t *)SortedListGetData(iter);
    SortedListRemove(iter);
    return_val = handler->data;
    free(handler);
    return return_val;
}




























/*
int comparefunc(void *, void *)
{
    person_t* p1 = (person_t*)data1;
    person_t* p2 = (person_t*)data2;

    if(p1->idNum)
    if(strcmp(p1->name, p2->name))
}

priority queue will hold a node
which points to data & to UID,
with malloc -> like node which wrappes 

the user provides a compare function which looks at the data.

we will need to create a wrapper for the warpper

static pqcomparefunc which recives 2 data values
*/
