/*********************************
 * Reviewer: Irit				
 * Author: Yohai Azoulai			
 * File: circular_buffer.c					
 * ******************************/
 
 /**/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "circular_buffer.h"

struct circular_buffer
{
    size_t capacity;
    size_t size;
    ssize_t flag;
    char buffer[1];
};

#define RESET 0


circ_buff_t *CircBuffCreate(size_t capacity)
{
    circ_buff_t *c_buff = (circ_buff_t *)malloc((sizeof(circ_buff_t) - sizeof(size_t)) + capacity );
    
    if(!c_buff)
    {
        printf("Couldnt allocated memory for Circular buffer\n");
        return NULL;
    }

    c_buff->capacity = capacity;
    c_buff->size = RESET;
    c_buff->flag = RESET;

    return c_buff;
}

void CircBuffDestroy(circ_buff_t *c_buff)
{
    assert(c_buff);
    
    c_buff->capacity = RESET;
    c_buff->flag = RESET;
    free(c_buff);
    c_buff = NULL;
}

size_t CircBuffFreeSpace(const circ_buff_t *c_buff)
{
    assert(c_buff);
    return c_buff->capacity-c_buff->size;
}

size_t CircBuffBufSiz(const circ_buff_t *c_buff)
{
    assert(c_buff);
    return c_buff->capacity;
}

int CircBuffIsEmpty(const circ_buff_t *c_buff)
{
    assert(c_buff);
    return(!c_buff->size);
}


ssize_t CircBuffRead(circ_buff_t *c_buff, void *stream, size_t count)
{
    size_t i = 0;
    

    assert(c_buff);
    assert(stream);
    
    if(count > c_buff->size)
    {
        count = c_buff->size;
    }
    while(count && count <= c_buff->size)
    {
        *((char*)stream + i) = *(c_buff->buffer + c_buff->flag);
        c_buff->flag = (c_buff->flag + 1) % c_buff->capacity;
        --c_buff->size;
        ++i;
        --count;
    }
        
    return i;   
}   


ssize_t CircBuffWrite(circ_buff_t *c_buff, const void *stream, size_t count)
{
    size_t i = 0;
    size_t tail = (c_buff->flag + c_buff->size) % c_buff->capacity;
    size_t empty_spc = CircBuffFreeSpace(c_buff);

    assert(c_buff);
    assert(stream);
    
    if(count > empty_spc)
    {
        count = empty_spc;
    }
    while(count && c_buff->size != c_buff->capacity)
    {
        *(c_buff->buffer + tail) = *((char*)stream + i);
        ++i;
        --count;
        ++c_buff->size; 
        tail = (tail + 1) % c_buff->capacity;
    }
    
    return i;
}
