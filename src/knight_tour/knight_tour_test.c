/*********************************
 * Reviewer: Daniel	Benjamin			
 * Author: Daniel Natan			
 * File: knight_tour_test.c				
 * ******************************/
#include <stdio.h> 
#include <assert.h>
#include <stdlib.h>
#include "knight_tour.h"

static void PrintMoves(int arr[], size_t size);

static void PrintBoard(int *res);


int main(int argc, char *argv[])
{
    
    position_t start_pos = {0};
    int *arr = NULL;
    size_t size = 0;
    
    assert(argc == 3);
    
    arr = (int*)malloc(sizeof(int) * 64);
    if (!arr)
    {
        return -1;
    }

    start_pos.x = atoi(argv[1]);
    start_pos.y = atoi(argv[2]);
    
    
    size = 64;
    KnightTour(start_pos, arr);

    PrintMoves(arr,size);
    return 0;
}

static void PrintMoves(int arr[], size_t size)
{
    size_t i = 0;
    while(i < size - 1)
    {
        printf(" %d goes to --> %d", arr[i], arr[i + 1]);
        ++i;
        if (0 == i%2)
        {
            printf("\n");
        }
        
    }
    printf("\n");
}

/* 
static void PrintBoard(int *res)
{
    int i = 0;
    printf("the path of the mighty knight is:\n");
    for(i=0;i<64;i++)
    {
        if(i % 8 == 0)
        {
            printf("\n");
        }
        printf("%d\t", *(res+i));
    }
    printf("\n");
} */