/*********************************
 * Reviewer: 				
 * Author: Yohai Azoulai			
 * File: task.c					
 * ******************************/
 
 /**/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc & free*/
#include "task.h"

/*******Structs******/

struct task                    
{
    time_t exe_time;
    void *arg;
    task_action_t action_func;
    size_t interval_time;
};

/*******Service Funcs******/


/*******Funcs Funcs******/

task_t *TaskCreate(void *arg, task_action_t action_func, size_t interval_time)
{
    task_t *a_task = NULL;

    assert(action_func);
    /*assert(interval_time);*//*not pointer- you dont need assert || Corrected*/

    a_task = (task_t *)malloc(sizeof(task_t));
    if(!a_task)
    {
        return NULL;
    }

    a_task->arg = arg;
    a_task->exe_time = time(NULL) + interval_time;
    a_task->action_func = action_func;
    a_task->interval_time = interval_time;

    return a_task;


}

void TaskDestory(task_t *task)
{
    assert(task);

    task->arg=NULL;
    task->exe_time=0;
    task->action_func=NULL;
    task->interval_time= 0;
    
    free(task);
    task = NULL;
}

time_t TaskGetTime(task_t *task)
{
    assert(task);

    return task->exe_time;
}

size_t TaskGetIntervalTime(task_t *task)
{
    assert(task);

    return task->interval_time;
}

void TaskSetTime(task_t *task, time_t exec_time_in_sec)
{
    assert(task);
    assert(exec_time_in_sec);

    task->exe_time = exec_time_in_sec;
}

int TaskExec(task_t *task)
{
    assert(task);
    
    return (task->action_func(task->arg));
}


