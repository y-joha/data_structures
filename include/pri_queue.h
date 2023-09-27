/*********************************
 * Reviewer: 				
 * Author: Yohai Azoulai			
 * File: pri_queue.c					
 * ******************************/

#ifndef __PRI_QUEUE_H__
#define __PRI_QUEUE_H__

#include "UID.h"


typedef struct p_queue pri_queue_t;

typedef int(*compare_t)(const void *n1, const void * n2, void *pq);

pri_queue_t *PQueueCreate(compare_t priority_func, void *user_param);

void PQueueDestroy(pri_queue_t *pq);

ilrd_uid_t PQueueEnQueue(pri_queue_t *pq, void *data); 

int PQueueReEnQueue(pri_queue_t *pq, void *data,ilrd_uid_t old_uid);

ilrd_uid_t PQueueDeQueue(pri_queue_t *pq);

void *PQueuePeek(pri_queue_t *pq); /* data, or null if empty */

int PQueueIsEmpty(pri_queue_t *pq); /* non-zero if empty */

size_t PQueueSize(pri_queue_t *pq);

void PQueueClear(pri_queue_t *pq);

void *PQueueErase(pri_queue_t *pq, ilrd_uid_t uid);
  /*Gives the option to cancel an element within the PQueue*/

#endif 
