/*********************************
 * Reviewer: 				
 * Author: Yohai Azoulai			
 * File: task.h					
 * ******************************/

#ifndef __TASK_H__
#define __TASK_H__



#include <time.h>

typedef int (*task_action_t)(void *arg);
typedef struct task task_t;

task_t *TaskCreate(void *arg, task_action_t action_func, size_t interval_time);
/*
Descreption: create a new task
param: time_t exe_time(absolut time since epoch in seconds), void *arg(arg for parameters),
task_action_t action_func 
Return val: pointer to task, if fails NULL ptr/
Complexity:
*/

void TaskDestory(task_t *task);
/*
Descreption: destroy a task
param: ptr to task
Return val: non
Complexity:
*/

time_t TaskGetTime(task_t *task);
/*
Descreption: gives the exe time of the task
param: ptr to task
Return val: time_t exe_time
Complexity:
*/

size_t TaskGetIntervalTime(task_t *task);
/*
Descreption: gives the interval time of the task
param: ptr to task
Return val: time_t exe_time
Complexity:
*/

void TaskSetTime(task_t *task, time_t exec_time_in_sec);
/*
Descreption: change the exe time of the task
param: ptr to task
Return val: non
Complexity:
*/

int TaskExec(task_t *task);
/*
Descreption: execute task func
param: ptr to task
Return val: zero if success, non-zero integer when fails.
Complexity:
*/

#endif /* __TASK_H__ */
