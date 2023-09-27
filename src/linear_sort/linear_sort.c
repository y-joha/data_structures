/*********************************
 * Reviewer: Avigail
 * Author: Yohai Azoulai			
 * File: liniar_sort.c					
 * ******************************/
 
 /**/

#include <assert.h> /*assert*/

#include "linear_sort.h"

/*******Defines******/

#define DIGITS 10

/*******Structs******/



/*******Service Funcs******/

static int FindMaxKeyRange(int *array,size_t size_of_array);
static void RadCountingSort(int *array, size_t length, int digit);

/*******Funcs Funcs******/

void CountingSort(int *array,size_t length)
{
    int *return_array = NULL;
    int *occurrenc = NULL;
    size_t key_range = 0, i = 0;

    assert(array);
    if(!occurrenc)
    {   
        exit(-1);
    }
    
    if(!return_array)
    {
        exit(-1);
    }

    key_range = FindMaxKeyRange(array,length);
    /*ABBI: did reasearch to understand.maybe call the func-find maximum, and k-max?*/
    
    occurrenc = (int *)calloc((key_range + 1),sizeof(int));
    return_array = (int *)calloc(length,sizeof(int));

    /*ABBI: if malloc fails || Corrected*/
    
    while(i < length)
    {
        ++occurrenc[array[i]];/*ABBI: u can write ++ || Corrected*/
        ++i;
    }
    
    i = 1;/*ABBI: mind ur enters. this line should be adjacent to the while || Corrected*/
    while(i < key_range + 1)
    {
        occurrenc[i] += occurrenc[i - 1];
        ++i;
    }
    
    /*ABBI: mind ur enters. this line should be adjacent to the while || Corrected*/
    i = length - 1;
    while((int)i >= 0)
    {
        return_array[occurrenc[array[i]] - 1] = array[i];
        --occurrenc[array[i]];
        --i;
    }/*ABBI: mind ur enters. || Corrected*/
    
    i = 0;
    while(i<length)
    {
        array[i] = return_array[i];
        ++i;
    }

    free(occurrenc);
    free(return_array);
    occurrenc = NULL;
    return_array = NULL;

}

void RadixSort(int *array, size_t length) 
{
    size_t outer_loop_counter = 0; 
    size_t key_range = 0;
    /* size_t i = 0;*/
    size_t digit = 1;

    assert(array);
    
    key_range = FindMaxKeyRange(array,length);

    /*ABBI: u can erase this and change the next loop as shown || Tried*/
     while(key_range)
    {
        key_range /= 10;
        ++outer_loop_counter;
    }
    /*ABBI: use meaningful name like digits or total_digits || Corrected (k)*/
    /*ABBI: k/outer_loop_counter || when i tried to do it in one while
    like you suggested i recived a div by 0 in the while condition, 
    so i reverted back*/
    
    while(outer_loop_counter)
    {
        RadCountingSort(array,length,digit);
        digit *= 10;
        --outer_loop_counter;
    }
}

static void RadCountingSort(int *array, size_t length, int digit)
{
    int *return_array = NULL;
    int *occurrenc = NULL;
    size_t i = 0;

    assert(array);
    
    occurrenc = (int *)calloc(DIGITS,sizeof(int));
    return_array = (int *)calloc(length,sizeof(int));
    if(!occurrenc)
    {   
        exit(-1);
    }
    
    if(!return_array)
    {
        exit(-1);
    }
    /*ABBI: if malloc fails || Corrected*/
    /*ABBI: u hard coded DIGITS so if u change radix u need to 
    change DIGITS too || as long as its a numeric value it will be 
    0 - 9 i dont understand
    
    Due to my use of Digit if i use a diffrent base i'll have to change
    vhange this for each diffrent varietions!!
    


    */

    while(i < length)
    {
        occurrenc[(array[i] / digit) % DIGITS] += 1;
        ++i;
    }
    i = 1;
    
    while(i < DIGITS)
    {
        occurrenc[i] += occurrenc[i - 1];
        ++i;
    }
    
    
    i = length - 1;

    while((long)i >= 0)
    /*ABBI: notice this cast can overflow || Corrected */
    {
        return_array[occurrenc[(array[i] / digit) % 10] - 1] = array[i];
        --occurrenc[(array[i] / digit) % 10];
        --i;
    }
    i = 0;
    while(i<length)
    {
        array[i] = return_array[i];
        ++i;
    }

    free(occurrenc);
    free(return_array);
    occurrenc = NULL;
    return_array = NULL;

}


static int FindMaxKeyRange(int *array,size_t size_of_array)
{
    int my_k = 0;
    size_t i = 0;
    

    for (i = 0; i < size_of_array; ++i)
    {
        if(array[i] > my_k)
        {
            my_k = array[i];
        }
    }
    return my_k;
}

