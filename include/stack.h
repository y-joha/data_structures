/*********************************
 * Reviewer: Israel Ficsh           
 * Author: Yohai Azoulai         
 * File: DSStack_test.c          
 * ******************************/

#ifndef __STACK__
#define __STACK__

#include <stddef.h>  /*for size_t*/
#include <stdlib.h>  /*malloc*/
#include <stdio.h>   /*printf need to remove after*/
#include <string.h>  /*memcompr*/
#include <assert.h>  
 


typedef struct stackstruct stack_t;


/* description: creates a new stack 
   params: stack capacity, and element size
   return value: In case of success pointer to the new struct, Null in case of failure
   undefined behavior: in case of invalid element size */    
stack_t *StackCreate(size_t Num_Of_Elements, size_t  element_size);


/* description: push an new element to the top of the stack
   params: pointer to stack and element to push
   undefined behavior: null pointer, push to a full stack */    
void StackPush(stack_t *s, void *element_to_push);


/* description: pops the last element
   params: pointer to the stack
   undefined behavior: pop on an empty stack, null pointer */
void StackPop(stack_t *s);


/* description: copies the value of the last element to the strore_element
   params: pointer to the stack, pointer to the store_element
   undefined behavior: empty stack, in case of not enough space in store_element, null pointer */


void StackPeek(stack_t*s, void *store_element);


/* description: checks if the stack is empty
   params: pointer to the stack
   return value: 1 if stack is empty 0 otherwise
   undefined behavior: null pointer */
int StackIsEmpty(stack_t *s);


/* description: frees all allocations
   params: pointer to the stack
   undefined behavior: null pointer  */
void StackDestroy(stack_t *s);


/*  
   params: pointer to the stack
   return value: stack capacity
   undefined behavior: null pointer */
size_t StackCapacity(stack_t *s);


/* 
   params: pointer to the stack
   return value: stack size - number of elements currently in the stack
   undefined behavior: null pointer */
size_t StackSize(stack_t *s);

#endif 
/*__STACK_H__*/


