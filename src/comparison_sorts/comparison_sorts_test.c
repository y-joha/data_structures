/*********************************
 * Reviewer: Place name				
 * Author: Yohai Azoulai			
 * File: comparison_sorts_test.c				
 * ******************************/




#include "comparison_sorts.h" 


/*
    void BubbleSort(int *array, int size_of_array) 

    void SelectionSort(int *array, int size_of_array) 
    
    void InsertionSort(int *array, int size_of_array) 

    int ArrayChecker(int *array, int size_of_array)
    int Compare(const void *a, const void *b);
*/

int main(int argc, char **argv)
{
    int *arr = NULL;
    int size_of_array = 0;

    size_of_array = atoi(argv[1]);

    if(argc < 3)
    {
        fprintf(stderr, "a.out <size> <sorting alg>\n");
    }

    arr = (int *)malloc(size_of_array * sizeof(int));

    if(argc < 2)
    {
        fprintf(stderr, "please enter a.out <sorting algo>\n");
        exit(1);        
    }
    
    Initializer(arr, size_of_array);
    switch(argv[2][0])
    {
        case 'q':
            printf("Linux Qsort - seed (16)\n");
            qsort(arr,size_of_array,sizeof(int),Compare);
            if(!(ArrayChecker(arr,size_of_array)))
            {
                printf("array not sorted ,%d \n",__LINE__);
                exit(1); 
            }

            break;

        case 'b':
            printf("Bubble sort - seed (16)\n");
            BubbleSort(arr,size_of_array);
            if(!(ArrayChecker(arr,size_of_array)))
            {
                printf("array not sorted ,%d \n",__LINE__);
                exit(1); 
            }
                break;

        case 's':
            printf("Selection sort/Comparing sort - seed (16)\n");
            SelectionSort(arr,size_of_array);
            if(!(ArrayChecker(arr,size_of_array)))
            {
                printf("array not sorted ,%d \n",__LINE__);
                exit(1); 
            }
            break;

        case 'i':
            printf("Insertion sort - seed (16)\n");
            InsertionSort(arr,size_of_array);
            if(!(ArrayChecker(arr,size_of_array)))
            {
                printf("array not sorted ,%d \n",__LINE__);
                exit(1); 
            }
            break;
        default:
        printf("q b s or i those are the options");
        }

    free(arr);

    return 0;
}

