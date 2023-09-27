/*********************************
 * Reviewer: Sigal Tal				
 * Author: Yohai Azoulai			
 * File: scheduler.c					
 * ******************************/
 
 /**/

#include <assert.h> /* assert */
#include <unistd.h> /* sleep */
#include <stdlib.h> /* malloc & free*/

#include "pri_queue.h"

#include "task.h"

#include "scheduler.h"

/*******Structs&ENUMS******/
struct scheduler
{
    pri_queue_t *pq;
    char keep_run;/*can be char and takes less space || Corrected*/
};

enum {STOP = 0,GO = 1};

/*******Service Funcs******/

static int TimeCompare(const void *list_data,
                       const void *new,
                       void *user_param);


/*******Funcs Funcs******/

scheduler_t *SchedulerCreate(void)
{
    scheduler_t *scdlr = NULL;
    scdlr = (scheduler_t *)malloc(sizeof(scheduler_t));
    
    if(!scdlr)
    {
        return NULL;
    }

    scdlr->pq = PQueueCreate(TimeCompare,scdlr);
    scdlr->keep_run = STOP;

    if(!(scdlr->pq))
    {
        free(scdlr);
        scdlr = NULL;
        return NULL;
    }

    return scdlr;

} 

void SchedulerDestroy(scheduler_t *scdlr)
{
    assert(scdlr);
    
    SchedulerClearAll(scdlr);
    
    PQueueDestroy(scdlr->pq);
    
    free(scdlr);
    
    scdlr = NULL;
}


ilrd_uid_t SchedulerAddTask(scheduler_t *scdlr,
            scheduler_action_t action_func,
            void *arg,
            size_t time_interval)
{
    ilrd_uid_t uid;
    task_t *new_task = NULL;
    
    assert(scdlr);
    /*assert(action_func) || Corrected */

    new_task = TaskCreate(arg,action_func,time_interval);
    if(!new_task)
    {
        return g_bad_uid;
    }

    uid = PQueueEnQueue(scdlr->pq,new_task);
    if(UIDIsSame(uid, g_bad_uid))
    {
        SchedulerRemoveTask(scdlr,uid);
        return g_bad_uid;
    }

    return uid;
    /*if EnQueue fails we need to remove task and only then return
                || Corrected*/
}

int SchedulerRemoveTask(scheduler_t *scdlr, ilrd_uid_t uid)
{
    task_t *task = NULL;/**task=NULL || Corrected*/

    assert(scdlr);
    /* task=PQueueErase(scdlr->pq,uid) || Corrected;*/
    task = PQueueErase(scdlr->pq,uid);
    if(!task)
    {
        return 1;
    }

    TaskDestory(task);
    task = NULL;

    return STOP;/*we agreed that succsess is 0 || Corrrected*/
}

void SchedulerClearAll(scheduler_t *scdlr)
{
    task_t *task = NULL;
    
    assert(scdlr);
    
    while(!SchedulerIsEmpty(scdlr))
    {
        task = PQueuePeek(scdlr->pq);
        
        PQueueDeQueue(scdlr->pq);
        
        TaskDestory(task);
        
        task = NULL;
    }
}

int SchedulerIsEmpty(scheduler_t *scdlr)
{
    assert(scdlr);
    
    return PQueueIsEmpty(scdlr->pq);
}

size_t SchedulerSize(scheduler_t *scdlr)
{
    assert(scdlr);
    return PQueueSize(scdlr->pq);
}

int SchedulerRun(scheduler_t *scdlr)
{
    task_t *task =NULL;
    ilrd_uid_t uid = UIDGetNull();
    int ret_val = 0 , requeuemal = 0;

    assert(scdlr);

    scdlr->keep_run = GO;

    while(scdlr->keep_run && !SchedulerIsEmpty(scdlr) && 0 == requeuemal)
    {
        task = PQueuePeek(scdlr->pq);

        if(TaskGetTime(task) > time(NULL))
        {
            sleep(TaskGetTime(task) - time(NULL));
        }

        uid = PQueueDeQueue(scdlr->pq);
        ret_val = TaskExec(task);
        
        if (ret_val)
        {
            TaskDestory(task);
        }
        
        else
        {
            TaskSetTime(task, TaskGetTime(task) + TaskGetIntervalTime(task));
            requeuemal = PQueueReEnQueue(scdlr->pq, task, uid);
                /*we have new name PQueueReEnQueue*//*check for failure || Corrected*/
        }
    }
    return 0; /*should return 0 for sucsess || Corrected*/
}

void SchedulerStop(scheduler_t *scdlr)
{
    scdlr->keep_run = STOP;
}


static int TimeCompare(const void *list_data, 
                       const void *new,
                       void *user_param)
{
    assert(list_data);
    assert(new);
    assert(user_param);
    (void)user_param;

    return TaskGetTime((task_t *)list_data) < TaskGetTime((task_t *)new);
    /*return TaskGetTime((task_t *)list_data) < TaskGetTime((task_t *)new)?-1:1 
                        || Corrected*/
}
