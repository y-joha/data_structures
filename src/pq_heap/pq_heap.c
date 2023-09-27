/*********************************
 * Reviewer: Sigal				
 * Author: Yohai Azoulai			
 * File: pq_heap.c					
 * ******************************/
 
 /**/


#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc & free*/

#include "pri_queue.h"
#include "heap.h"

/*******Structs******/

struct p_queue
{
    heap_t *heap;
    compare_t comp_func; /* users regular compare function*/
    void *u_param;       /* this hold user parameter*/
};

struct pqueue_member    /*this is the struct that will be in the 
                            data pointer of the sorted list node*/
{
  ilrd_uid_t uid;
  void *data;
};

typedef struct pqueue_member pq_node_t;


/*
typedef struct pqueue_member pq_node_t;  <----

typedef struct p_queue pri_queue_t;   <----
*/


static int PQMatchingMachine(const void *n1,const void *n2,void *user_param)
{
    (void)user_param;
    return UIDIsSame( ((pq_node_t *)(n1))->uid,*(ilrd_uid_t *)n2);
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
    pq->heap = NULL;

    pq->heap = HeapCreate(PQCompareFunc,pq);
    if(NULL == pq->heap)
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
    HeapDestroy(pq->heap);
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
    
    
    if(HeapPush(pq->heap,nod_id))
    {
        free(nod_id);
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
        return 1;
    }
    nod_id->uid = old_uid;
    nod_id->data = data;
    if(HeapPush(pq->heap,nod_id))
    {
        free(nod_id);
        return 1;
    }
    return 0;
}

ilrd_uid_t PQueueDeQueue(pri_queue_t *pq)
{
    ilrd_uid_t tmp = UIDGetNull();
    pq_node_t *tmp_ptr = NULL;
    
    assert(pq);

    tmp_ptr = (pq_node_t*)HeapPeek(pq->heap);

    tmp = tmp_ptr->uid;
    
    HeapPop(pq->heap);
    free(tmp_ptr);
    
    tmp_ptr = NULL;
        
    return tmp;
}

void *PQueuePeek(pri_queue_t *pq)
{
    void *tmp_ptr = NULL;
    
    assert(pq);

    tmp_ptr = ((pq_node_t*)HeapPeek(pq->heap))->data;
    return tmp_ptr;
}

int PQueueIsEmpty(pri_queue_t *pq)
{
    
    assert(pq);
    return HeapIsEmpty(pq->heap);
}

size_t PQueueSize(pri_queue_t *pq)
{
    
    assert(pq);
    return HeapSize(pq->heap);
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
    void *return_val = NULL;

    assert(pq);
    
    handler = (pq_node_t*)HeapRemove(pq->heap,&uid,PQMatchingMachine,NULL);
    
    if (!handler)
    {
        return NULL;
    }

    return_val = handler->data;
    free(handler);
    return (return_val);
}

