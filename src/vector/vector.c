/*********************************
 * Reviewer: Shani_Horden				
 * Author: Yohai Azoulai			
 * File: vector.c					
 * ******************************/

#include <assert.h> /*CD- why*/ /*Corection : assert*/
#include <stdlib.h> /*Malloc & Realloc&Free*/
#include <stdio.h>/*CD- why*/ /*Corection : printf on aborts*/
#include <string.h>/*CD- why*/ /*Corection : memcpy*/
#include "vector.h"

#define VECTOR_POSITION ((vector->size * vector->element_size))
#define USER_SPECIFIC ((index * vector->element_size))
#define EFFECTIVE_SIZE ((vector->capacity * vector->element_size))
#define EFFECTIVE_CAPACITY ((new_capacity * vector->element_size))
#define FACTOR vector->capacity*2

/*CD ask question- we dont prefer to write less DEFINE?
Answer : These are just text substitutions, not MACROS , so i use these to keep 
unneccecery clutter from the code lines 
*/

struct vector
{
    size_t element_size;
    size_t capacity;
    size_t size;
    char *vector;
};

vector_t *VectorCreate(size_t capacity, size_t element_size)
{
    vector_t *v = (vector_t *)malloc(sizeof(vector_t));
    if(NULL == v)
    {
        printf("Couldnt allocated memory for VectorStack\n");
        return NULL;
    }
    v->vector = (char *)malloc(element_size * capacity);
    if(NULL == v->vector)
    {
        printf("Couldnt allocated memory for vector inside\n");
        free(v);
        return NULL;
    }

    v->element_size = element_size;
    v->capacity = capacity;
    v->size = 0;
    return v;
}

void VectorDestroy(vector_t *vector)
{
    assert(vector);
    free(vector->vector);
    free(vector);
}

int VectorPush(vector_t *vector, void *element_to_push)
{
    int flag = 0;
    assert(vector);
    assert(element_to_push);
    if(vector->size == vector->capacity)
    {
        flag = VectorReserve(vector,FACTOR);
    }
    memcpy(vector->vector + VECTOR_POSITION,element_to_push,vector->element_size);
    ++(vector->size);
    return flag;
}

void VectorPop(vector_t *vector)
{
    assert(vector);
    --(vector->size);
}

int VectorIsEmpty(vector_t *vector)
{
    assert(vector);
    return (!vector->size);    /*CR- you did it good
    the fun return 0 if its full,
     just notice to change the H file*/
    /*Answer : Changed*/
}

size_t VectorSize(vector_t *vector)
{
    assert(vector);
    return vector->size;
}

size_t VectorCapacity(vector_t *vector)
{
    assert(vector);
    return vector->capacity;
}

void *VectorGetAccess(vector_t *vector, int index)
{
    assert(vector);
    return (vector->vector + USER_SPECIFIC);
}

int VectorShrinkToFit(vector_t *vector)
{
    assert(vector);
    vector->capacity = vector->size;   /*CD- im not sure, but maybe put this after you check thats tour realloc succssed
    ****Answer : This is needed here because of the define(it needs updated Capacity)
    i prefer defines to keep code "clean" reletivly instead of rewriting the same lines again****/
    vector->vector = (char *)realloc(vector->vector,EFFECTIVE_SIZE);
    if(NULL == vector->vector)
    {
        printf("Pointer memory ReAlloc failed");
        return 1;

    }
    return 0;
}

int VectorReserve(vector_t *vector, size_t new_capacity)    
{
    assert(vector);
    vector->vector = (char *)realloc(vector->vector,EFFECTIVE_CAPACITY);
    if(NULL == vector->vector)
    {
        printf("Pointer memory ReAlloc failed on Vector Reserve");
        return 1;
    }
    vector->capacity = new_capacity;
    return 0;
}
