/*********************************
 * Reviewer: Irit				
 * Author: Yohai Azoulai			
 * File: circular_buffer_test.c				
 * ******************************/

#include <assert.h>
#include <stdio.h>
#include "circular_buffer.h" 



void BuffCreateEmptyDestroy(size_t buffer_given);
void BuffVacancy();


int main(int argc, char *argv[])
{
    size_t buffy = 10, buffolomiu = 4096;
    


    printf("value of BUFISZ on my comp is - %d\n",BUFSIZ);
    BuffCreateEmptyDestroy(BUFSIZ);
    BuffCreateEmptyDestroy(buffy);
    BuffCreateEmptyDestroy(buffolomiu);
    BuffVacancy();

    (void)argc;
    (void)argv;

    return 0;
}


void BuffCreateEmptyDestroy(size_t buffer_given)
{
    circ_buff_t *buffer;
    
    printf("BuffCreateEmptyDestroy\n");
    assert(buffer_given);
    buffer = CircBuffCreate(buffer_given);
    if (NULL == buffer)
    {
        printf("Man.Struct malloc failed\n");
    }
    CircBuffFreeSpace(buffer);
    CircBuffDestroy(buffer);
}

void BuffVacancy()
{
    circ_buff_t *buffer;

    buffer = CircBuffCreate(BUFSIZ);
    if (NULL == buffer)
    {
        printf("Man.Struct malloc failed\n");
    }

    assert(BUFSIZ == CircBuffFreeSpace(buffer));
    assert(BUFSIZ == CircBuffBufSiz(buffer));

    assert(1 == CircBuffIsEmpty(buffer));

    CircBuffDestroy(buffer);

}





