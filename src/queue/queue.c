/*********************************
 * Reviewer: Daniel_N				
 * Author: Yohai Azoulai			
 * File: queue.c					
 * ******************************/

#include <stdlib.h> /*Malloc*/
#include <stdio.h>  /*printf*/
#include <assert.h> /*assert*/
#include "queue.h" 

struct queue
{
    sll_t *slist;
};

queue_t *QueueCreate()
{
    queue_t *q = (queue_t *)malloc(sizeof(queue_t));
    if(NULL == q)
    {
        printf("Couldnt allocated memory for Queue\n");
        return NULL;
    }

    q->slist = SLLCreate();
    if(NULL == q->slist)
    {
        printf("Couldnt allocated memory for Queue->slist\n");
        free(q);
        return NULL;
    }

    return q;
}


void QueueDestroy(queue_t *q)
{
    assert(q);
    SLLDestroy(q->slist);
    q->slist = NULL;

    free(q);

    q = NULL; /* i think slist need to get NULL, because q is just a copy ||| Corrected*/
}

int QueueEnQueue(queue_t *q, void *element_add)
{
    assert(q);
    assert(element_add); /* each statment needs to get a line */
    return (SLLIteratorsIsEqual(SLLInsert(SLLEnd(q->slist),element_add),
        SLLEnd(q->slist))); /* nice use of SLLIteratorIsEqual */
}

void QueueDeQueue(queue_t *q)
{
    assert(q);
    SLLRemove(SLLBegin(q->slist));
}

void *QueuePeek(const queue_t *q)
{
    assert(q);
    return SLLGet(SLLBegin(q->slist));
}

queue_t *QueueAppend(queue_t *q1, queue_t *q2)
{
    assert(q1); /* what happens if q1 and q2 are empty queues? 
    		basically im asking where is the case of faliure ||| case of failiure is inside 
    		is checked in SLLAppend*/
    assert(q2);
    q1->slist = SLLAppend(q1->slist,q2->slist);
    free(q2);
    q2 = NULL;
    
    return q1;
}

size_t QueueSize(const queue_t *q)
{
    return (size_t)SLLCount(q->slist);
}

int QueueIsEmpty(const queue_t *q)
{
    assert(q);
    return ((0 == QueueSize(q))?1:0); /* new statment in new line ||| corrected*/
}

