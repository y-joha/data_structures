/*********************************
 * Reviewer: Avigail	
 * Author: Yohai Azoulai			
 * File: liniar_sort_test.c				
 * ******************************/

#include "linear_sort.h" 

#define DIGITSCAP 1000000

void ArrayPrinter(int *arr, size_t size);
void Initializer(int *arr, size_t size);
size_t ArrayChecker(int *array, size_t length);



int main(int argc, char **argv)
{
    int *arr = NULL;
    size_t size_of_array = 0;
    

    if(argc < 3)
    {
        fprintf(stderr, "a.out <size> <sorting alg>\n");
        exit(1);
    }

    size_of_array = atoi(argv[1]);

    arr = (int *)malloc(size_of_array * sizeof(int));

    if(argc < 2)
    {
        fprintf(stderr, "please enter a.out <sorting algo>\n");
        exit(1);        
    }
    
    Initializer(arr, size_of_array);
    printf("\n");
    switch(argv[2][0])
    {
        case 'c':
            printf("CountingSort - seed (time(NULL))\n");
            CountingSort(arr,size_of_array);
            printf("\n");
            ArrayPrinter(arr,size_of_array);
            printf("\n end of print \n");
            if(!(ArrayChecker(arr,size_of_array)))
            {
                printf("\n");
                printf("array not sorted ,line - %d  \n",__LINE__);
                break; 
            }

            break;

        
        case 'r':
            printf("Radix sort - seed (time(NULL))\n");
            RadixSort(arr,size_of_array);
            printf("\n");
            ArrayPrinter(arr,size_of_array);
            printf("\n end of print \n");
            if(!(ArrayChecker(arr,size_of_array)))
            {
                printf("array not sorted ,line - %d \n",__LINE__);
                break; 
            }
            break;
        
        
        default:
        printf("c or r those are the options");
        }

    free(arr);

    return 0;
}

size_t ArrayChecker(int *array, size_t length)
{
    size_t i = 0;

    for(i = 0 ; i < length - 1; ++i)
    {
        if(array[i] > array[i + 1])
        {
            return 0;
        }
    }
    return 1;
}

/*ABBI: these should be in the test || Corrected*/
void Initializer(int *arr, size_t size)
{
    size_t i = 0;

    for(i = 0; i < size; i++)
    {
        /* arr[i] = rand()%(100 - 1) + 1;*/
        
        srand(clock());
        arr[i] = (rand() % DIGITSCAP);
    }
}


void ArrayPrinter(int *arr, size_t size)
{
    size_t i = 0;

    for(i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
        if(!(i%20))
        {
            printf("\n");
        }
    }
}
