/*********************************
 * Reviewer: Daniel_N				
 * Author: Yohai Azoulai			
 * File: queue_test.c				
 * ******************************/



#include "queue.h" 
#include <stdio.h>

void TestQueueAppend();
void TestQueueEnDeQueue();
void TestQueueCreateDestroy();



int main(int argc, char *argv[])
{
    TestQueueCreateDestroy();
    
    TestQueueEnDeQueue();
    
    TestQueueAppend();
    
    (void)argc;
    (void)argv;

    return 0;
}

void TestQueueAppend()
{
    

    queue_t *q1 = QueueCreate();
    queue_t *q2 = QueueCreate();
    char i = '2',j = '9',k ='9';
    char x = 'K',x1 = 'A', x2 = 'V', x3 = 'O', 
                    x4 = 'D';
    int p = 0;


    QueueEnQueue(q1,&i);
    printf("%d\n",p);
    printf("\n");
    QueueEnQueue(q1,&j);
    QueueEnQueue(q1,&k);

    if(3 != QueueSize(q1))
    {
        puts("QueueEnQueue failed via QueueSize - Apend 3");
    }
    
    QueueEnQueue(q2,&x);
    QueueEnQueue(q2,&x1);
    QueueEnQueue(q2,&x2);
    QueueEnQueue(q2,&x3);
    QueueEnQueue(q2,&x4);

    QueueAppend(q1,q2);

    if (8 != QueueSize(q1))
    {
        puts("QueueEnQueue failed via QueueSize - Apend 8");
    }

    while(!QueueIsEmpty(q1))
    {
        printf("%c ", *(char *)QueuePeek(q1));
        QueueDeQueue(q1);
    }
    printf("\n");

    QueueDestroy(q1);
    q1 = NULL;
    q2 = NULL;


}

void TestQueueEnDeQueue()
{

    queue_t *q1 = QueueCreate();
    int i = 1, j = 4, k = 8;

        if(0 != QueueSize(q1))
        {
            puts("QueueEnQueue failed via QueueSize - 0");
        }

    QueueEnQueue(q1,&i);
        if(1 != QueueSize(q1))
        {
            puts("QueueEnQueue failed via QueueSize - 1");
        }
        
        if(1 != *(int *)QueuePeek(q1))
        {
            puts("Problem with Enqueue Via Peek - 1");
        }

    QueueEnQueue(q1,&j); /*  peek still  == 1*/
    QueueEnQueue(q1,&k); /*  peek still  == 1*/

        if(1 != *(int *)QueuePeek(q1))
        {
            puts("Problem with Enqueue Via Peek - 1");
            printf("value of queue peek - %d\n",*(int *)QueuePeek(q1));
        }
        if(3 != QueueSize(q1))
        {
            puts("QueueEnQueue failed via QueueSize - 3");
        }
    QueueDeQueue(q1);
    
        if(2 != QueueSize(q1))
        {
            puts("QueueEnQueue failed via QueueSize - 2");
        }
        if(4 != *(int *)QueuePeek(q1))
        {
            puts("Problem with Enqueue Via Peek - 4");
            printf("value of queue peek - %d\n",*(int *)QueuePeek(q1));
        }

        /*  peek still  == 4*/
        /*  peek still  == 8*/
    QueueDeQueue(q1);
        if(8 != *(int *)QueuePeek(q1))
        {
            puts("Problem with Enqueue Via Peek - 8");
            printf("value of queue peek - %d\n",*(int *)QueuePeek(q1));
        }

    
        if(1 != QueueSize(q1))
        {
            puts("QueueEnQueue failed via QueueSize - 1");
        }
        
    QueueDestroy(q1);

    q1 = NULL;
}


void TestQueueCreateDestroy()
{
    queue_t *q = QueueCreate();

    if(1 != QueueIsEmpty(q))
    {
        puts("QueueCreate faled via QueueISEmpty");
    }
    QueueDestroy(q);
}