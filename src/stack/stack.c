/*********************************
 * Reviewer: Israel				
 * Author: Yohai Azoulai			
 * File: DSStack.c					
 * ******************************/

#define STACK_POSITION ((0==(s->size)?s->size:s->size-1)*s->element_size)
#define EFFECTIVE_SIZE ((stackstruct->capacity * stackstruct->element_size))
#define STACK_SIZE 

#include "stack.h"

struct stackstruct
{
    char *stack;
    size_t element_size;
    size_t capacity;
    int size;
};



stack_t *StackCreate(size_t Num_Of_Elements, size_t  element_size)
{
    stack_t *stackstruct = (stack_t *)malloc(sizeof(stack_t));
    if(NULL == stackstruct)
    {
        printf("stackstruct malloc failed\n");
        return NULL;
    }
    stackstruct->stack = (char *)malloc(element_size * Num_Of_Elements);
    if(NULL == stackstruct->stack)
    {
        printf("stack malloc failed\n");
        free(stackstruct);
        return NULL;
    }
    stackstruct->element_size = element_size;
    stackstruct->capacity = Num_Of_Elements;
    stackstruct->size = 0; 
    return stackstruct;
}

void StackPush(stack_t *s, void *element_to_push) 
{
    assert(s);
    /* We differ here, daniel gives sizeof element_size and i give value as is*/
    memcpy(s->stack + (s->size * s->element_size),element_to_push, 
                                                        s->element_size);
    ++(s->size);
}
void StackPop(stack_t *s)
{
    assert(s);
    --(s->size);
}

void StackPeek(stack_t *s, void *store_element)
{
    assert(s);
    memcpy(store_element, (s->stack + (s->size - 1) * s->element_size), 
                                                s->element_size);
}

int StackIsEmpty(stack_t *s)
{
    assert(s);
    return !(s->size);
}

void StackDestroy(stack_t *s)
{
    assert(s);
    free(s->stack);
    free(s);
}

size_t StackCapacity(stack_t *s)
{
    assert(s);
    return s->capacity;
}

size_t StackSize(stack_t *s)
{
    assert(s);
    return s->size;
}

