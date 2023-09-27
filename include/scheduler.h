/*********************************
 * Reviewer: 				
 * Author: Yohai Azoulai			
 * File: scheduler.h					
 * ******************************/

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stddef.h> /* size_t */

#include "UID.h"

typedef struct scheduler scheduler_t;

typedef int (*scheduler_action_t)(void *arg);

/*policy: zero in success, any other number for user func fails except -1 */

scheduler_t *SchedulerCreate(void); 

void SchedulerDestroy(scheduler_t *scdlr);

ilrd_uid_t SchedulerAddTask(scheduler_t *scdlr,  
            scheduler_action_t action_func,
            void *arg,
            size_t time_interval);/*absolute time in seconds (relative to epoch)*/
/*
Descreption:
Return val: new task uid, returns bad uid if fails 
Complexity:
*/

int SchedulerRemoveTask(scheduler_t *scdlr, ilrd_uid_t uid);

void SchedulerClearAll(scheduler_t *scdlr);

int SchedulerIsEmpty(scheduler_t *scdlr);

size_t SchedulerSize(scheduler_t *scdlr);

int SchedulerRun(scheduler_t *scdlr);
/*policy: -1 in fail, zero in success, any other number for user func fails */

void SchedulerStop(scheduler_t *scdlr);

#endif 
