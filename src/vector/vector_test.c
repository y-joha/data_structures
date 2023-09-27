/*********************************
 * Reviewer: Shani_Horden				
 * Author: Yohai Azoulai			
 * File: vector_test.c				
 * ******************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vector.h" 



int VectorTests(void);


int main()
{
    VectorTests();
    

    return 0;
}

int VectorTests(void)
{
    int i = 5;
    int *ptr_peek_int;
    float f = 6.022;
    float *ptr_peek_float;
    char *str = "Mas Shevah";
    char *str1 = "Shevah Mas";
    char *str2 = "Lo Toee   ";

    char *peek_the_string = NULL;
    


    vector_t *v_ptr = VectorCreate(6,sizeof(int));



    VectorPush(v_ptr,&i);
    i = 6;
    VectorPush(v_ptr,&i);
    i = 7;
    VectorPush(v_ptr,&i);
   
    /*expecting to see 8 on the peek*/
    ptr_peek_int = (int *)VectorGetAccess(v_ptr, 0);
    if(*ptr_peek_int != 5)
    {
        printf("Vector get access failed for 0 index int\n");
        return 1;
    }
    ptr_peek_int = NULL;
    ptr_peek_int = (int *)VectorGetAccess(v_ptr, 2);
    if(*ptr_peek_int != 7)
    {
        printf("Vector get access befor the pop for 2 index int\n ");
        return 1;
    }

    /*expecting to see 7 on the peek
    or the fault happend prior to both Push*/
    VectorPop(v_ptr);
    ptr_peek_int = NULL;
    ptr_peek_int = (int *)VectorGetAccess(v_ptr, 1);
    if(*ptr_peek_int != 6)
    {
        printf("Vector get access failed after pop 1 index int\n ");
        return 1;
    }
    
    if(VectorSize(v_ptr) != 2)
    {
        printf("test failed in StackSize\n");
        return 1;
    }
    
    if(VectorCapacity(v_ptr) != 6)
    {
        printf("test failed in StackCapacity\n");
        return 1;
    }

    VectorDestroy(v_ptr);

    printf("test succsed for int's\n ");


    v_ptr = VectorCreate(6,sizeof(float));
    


    VectorPush(v_ptr,&f);
    f = 6.12;
    VectorPush(v_ptr,&f);
    f = 7.45;
    VectorPush(v_ptr,&f);

    /*expecting to see 8 on the peek*/
    ptr_peek_float = (float *)VectorGetAccess(v_ptr, 0);
    if(0.2<(*ptr_peek_float-6.02))
    {
        printf("Vector get access failed 0 index float\n");
        return 1;
    }
    
    ptr_peek_float = NULL;
    ptr_peek_float = (float *)VectorGetAccess(v_ptr, 2);
    if(0.2<(*ptr_peek_float-7.45))
    {
        printf("Vector get access befor the pop 2 index float\n ");
        return 1;
    }

    /*expecting to see 7 on the peek
    or the fault happend prior to both Push*/
    VectorPop(v_ptr);
    ptr_peek_float = NULL;
    ptr_peek_float = (float *)VectorGetAccess(v_ptr, 1);
    if(0.2<(*ptr_peek_float-6.12))
    {
        printf("Vector get access failed after pop 1 index float\n ");
        return 1;
    }
    
    if(VectorSize(v_ptr) != 2)
    {
        printf("test failed in StackSize for floats\n");
        return 1;
    }
    
    if(VectorCapacity(v_ptr) != 6)
    {
        printf("test failed in StackCapacity for floats\n");
        return 1;
    }

    VectorDestroy(v_ptr);

    printf("test succsed for floats's\n ");

    

    v_ptr = VectorCreate(6,(strlen(str) + 1)*sizeof(char));
    



    printf("strlen of str is - %ld\n",strlen(str));
    printf("sizeof of str is - %ld\n",sizeof(str));
    printf("strlen of str1 is - %ld\n",strlen(str1));
    printf("sizeof of str1 is - %ld\n",sizeof(str1));
    printf("strlen of str2 is - %ld\n",strlen(str2));
    printf("sizeof of str2 is - %ld\n",sizeof(str2));
    VectorPush(v_ptr,str);
    VectorPush(v_ptr,str1);
    VectorPush(v_ptr,str2);
    /*expecting to see 8 on the peek*/
    peek_the_string = (char *)VectorGetAccess(v_ptr,2);
    if(0 != (strcmp(peek_the_string,str2)))
    {
        printf("%s",(char *)v_ptr);
        printf("%s",peek_the_string);
        printf("test failed on str 2\n");
        return 1;
    }
    

    /*expecting to see 7 on the peek
    or the fault happend prior to both Push*/
    VectorPop(v_ptr);
    peek_the_string = NULL;
    peek_the_string = VectorGetAccess(v_ptr,1);
    if(0 != (strcmp(peek_the_string,str1)))
    {
        printf("%s",(char *)v_ptr);
        printf("%s",peek_the_string);
        printf("test failed on str 1\n");
        return 1;
    }
    
    if(VectorSize(v_ptr) != 2)
    {
        printf("test failed in StackSize for strings\n");
        return 1;
    }
    
    if(VectorCapacity(v_ptr) != 6)
    {
        printf("test failed in StackCapacity for strings\n");
        return 1;
    }

    VectorDestroy(v_ptr);

    printf("test succsed for strings\n");

    printf("Your vector is Excellent (lo bemet) check vlg\n");  

    str = NULL;
    str1 = NULL;
    str2 = NULL;

    return 0;
}
