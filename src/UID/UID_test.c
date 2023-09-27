/*********************************
 * Reviewer: 				
 * Author: Yohai Azoulai			
 * File: UID_test.c				
 * ******************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "UID.h" 

static void PrintUID(ilrd_uid_t uid);

int main(int argc, char *argv[])
{
    ilrd_uid_t UID1 = UIDGet();
    ilrd_uid_t UID2 = UIDGetNull();
    ilrd_uid_t UID3 = UIDGetNull();
    ilrd_uid_t UID5 = UIDGet();
    ilrd_uid_t UID6 = UIDGet();
    ilrd_uid_t UID7;
    

    if(0 != UID1.count)
    {
        printf("count is messed up on 1st");
    }
    if(1 != UID5.count)
    {
        printf("count is messed up on 2nd");
    }
    if(2 != UID6.count)
    {
        printf("count is messed up on 3rd");
    }
    

    PrintUID(UID1);
    PrintUID(UID5);
    PrintUID(UID2);
    printf("\n");
    printf("cheking is UID6 & 7 are the same\n");

    UID7.count = UID6.count;
    UID7.time = UID6.time;
    UID7.pid = UID6.pid;
    


    PrintUID(UID6);
    PrintUID(UID7);

    printf("\n");
    if(!UIDIsSame(UID1,UID2))
    {
        printf("Test 1 !IsSame (returns 0)==> which is true in the test\n");
        printf("HEEEEEY first(regular) to second(NULL), are not same!!\n");
    }

    printf("\n");

    if(UIDIsSame(UID6,UID7))
    {
        printf("Test 2 IsSame (returns 1)==> which is true in the test\n");
        printf("function is working proper UID 6 & 7 are the same\n");
    }

    printf("\n");

    if(UIDIsSame(UID3,UID2))
    {
        printf("Test 3 is Same on 2 NULLs recived\n");
        printf("Both Issame and Getnull are working\n");
    }

    sleep(5);

    UID7 = UIDGet();
    PrintUID(UID7);


    
    (void)argc;
    (void)argv;

    return 0;
}


static void PrintUID(ilrd_uid_t uid)
{
    printf("this is the UID - count (how many proccessies)- %ld\n",
     uid.count);
    printf("this is the UID - timestamp recived at creation - %s\n",
     ctime(&uid.time));
    printf("this is the UID - pid recived from the running proccess - %d\n",
     uid.pid);
}


