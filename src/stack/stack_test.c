/*********************************
 * Reviewer: Israel Ficsh				
 * Author: Yohai Azoulai			
 * File: DSStack_test.c				
 * ******************************/

#include "stack.h"

int main()
{
    /*  */
    int i = 0;
    char *a = "asjh";
    float g = 4.2;
    stack_t *strc_ptr;
    strc_ptr = StackCreate(5,sizeof(int));
    StackPush(strc_ptr,&i);
    StackPush(strc_ptr,&i);
    StackPush(strc_ptr,&i);
    StackDestroy(strc_ptr);
    strc_ptr= StackCreate(5,sizeof(char));
    StackPush(strc_ptr,a);
    StackPush(strc_ptr,a);
    StackPush(strc_ptr,a);
    StackDestroy(strc_ptr);
    strc_ptr= StackCreate(5,sizeof(float));
    StackPush(strc_ptr,&g);
    StackPush(strc_ptr,&g);
    StackPush(strc_ptr,&g);
    StackPop(strc_ptr);
    StackPop(strc_ptr);
    i = StackIsEmpty(strc_ptr);
    printf("%d\n",i);
    printf("%ld\n",StackCapacity(strc_ptr));
    printf("%ld\n",StackSize(strc_ptr));

    StackDestroy(strc_ptr);


    

    return 0;
}
