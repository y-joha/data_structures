/*********************************
 * Reviewer: Avigail Millatiner
 * Author: Irit Ofir
 * File: scheduler_test.c
 * ******************************/

#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc, free*/
#include "scheduler.h"


typedef struct args
{
    void *arg;
    scheduler_t *sch;
} args_t;

int FuncBoom(void *arg)
{
    static int count;
    printf("%s!\n", (char *)arg);
    ++count;
    count = count % 5;

    return (!count);
}

int Again(void *arg)
{
    int again = 1;
    scheduler_t *sch = (scheduler_t *)arg;

    printf("Run again? 1 for YES, 0 for NO: ");
    scanf("%d", &again);

    if (!again)
    {
        SchedulerStop(sch);
        return again;
    }

    SchedulerAddTask(sch, FuncBoom, "BOOM", 2);

    return again;
}

int Action1PrintStr(void *arg) 
{
    char arr[] = {'U', 'T', '!'};
    static int count;
    
    printf("%c\n", arr[count % sizeof(arr)]);
    ++count;

    (void)arg;

    
    return 0;
}

int Action2PrintStr(void *arg) 
{
    char arr[] = {'T', 'C', 'H', 'E', '!', '!'};
    static int count;
    printf("%c\n", arr[count % sizeof(arr)]);
    ++count;

    (void)arg;

    return 0;
}

int Action3PrintStr(void *arg) 
{
    char arr[] = {'E', 'S', 'E', 'W', ' ', 'S', '!'};
    static int count;
    printf("%c\n", arr[count % sizeof(arr)]);
    ++count;

    (void)arg;

    return 0;
}

int Action4PrintStr(void *arg) 
{
    char arr[] = {'T', 'S', ' ', 'C', 'S', 'S', 'A', 'A', 'M', 'S', '!', ';'};
    static int count;
    printf("%c\n", arr[count % sizeof(arr)]);
    ++count;

    if (0 == count % 6)
    {
        printf("\n");
        SchedulerAddTask(((args_t *)arg)->sch, Again, ((args_t *)arg)->sch, 0);
    }


    return 0;
}

scheduler_t *TestStart()
{
    scheduler_t *sch = SchedulerCreate();
    return sch;
    
} 

void TestDestroy(scheduler_t *sch)
{
    SchedulerDestroy(sch);
}

void TestCreateTask()
{
    scheduler_t *sch = TestStart();
    ilrd_uid_t task1 = SchedulerAddTask(sch, Action1PrintStr, "test 1", 10);
    ilrd_uid_t task2 = SchedulerAddTask(sch, Action1PrintStr, "test 2", 20);

    if (SchedulerIsEmpty(sch))
    {
        printf("TestCreateTask failed (not empty)\n");
    }

    if (2 != SchedulerSize(sch))
    {
        printf("TestCreateTask failed (size)\n");
    }

    SchedulerRemoveTask(sch, task1);
    SchedulerRemoveTask(sch, task2);

    if (!SchedulerIsEmpty(sch))
    {
        printf("TestCreateTask failed (is empty)\n");
    }

    TestDestroy(sch);
}


void TestClearAll()
{
    scheduler_t *sch = TestStart();
    ilrd_uid_t task1 = SchedulerAddTask(sch, Action1PrintStr, "test 1", 10);
    ilrd_uid_t task2 = SchedulerAddTask(sch, Action1PrintStr, "test 2", 20);

    SchedulerClearAll(sch);

    if (!SchedulerIsEmpty(sch))
    {
        printf("TestClearAll failed (is empty)\n");
    }

    TestDestroy(sch);

    (void)task1;
    (void)task2;
}

args_t *CreateArgs(scheduler_t *sch, void *data)
{
    args_t *arg = (args_t *) malloc(sizeof(args_t));
    if (!arg)
    {
        return NULL;
    }
    arg->arg = data;
    arg->sch = sch;

    return arg;
}

void DestroyArgs(args_t *arg)
{
    arg->arg = NULL;
    arg->sch = NULL;
    free(arg);
    arg = NULL;
}

void TestExecute()
{
    scheduler_t *sch = TestStart();
    args_t *args1 = CreateArgs(sch, "test 1");
    args_t *args2 = CreateArgs(sch, "test 2");
    args_t *args3 = CreateArgs(sch, "test 3");
    args_t *args4 = CreateArgs(sch, "test 4");

    ilrd_uid_t task1 = SchedulerAddTask(sch, Action1PrintStr, args1, 11);
    ilrd_uid_t task2 = SchedulerAddTask(sch, Action2PrintStr, args2, 7);
    ilrd_uid_t task3 = SchedulerAddTask(sch, Action3PrintStr, args3, 5);
    ilrd_uid_t task4 = SchedulerAddTask(sch, Action4PrintStr, args4, 3);

    SchedulerRun(sch);

    SchedulerRemoveTask(sch, task1);
    SchedulerRemoveTask(sch, task2);

    printf("****************second run*********************\n");
    SchedulerRun(sch);

    TestDestroy(sch);

    DestroyArgs(args1);
    DestroyArgs(args2);
    DestroyArgs(args3);
    DestroyArgs(args4);

    (void)task1;
    (void)task2;
    (void)task3;
    (void)task4;
}

int main()
{
    TestClearAll();
    TestCreateTask();
    TestExecute();
    return 0;
}
