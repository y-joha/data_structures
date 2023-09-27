/*********************************
 * Reviewer: Place name				
 * Author: Yohai Azoulai			
 * File: comparison_sorts.c					
 * ******************************/
 
 /**/


#include "comparison_sorts.h"

/*******Structs******/


/*******Service Funcs******/

int Compare(const void *a, const void *b);
static void Swapper(int *a, int *b);


/*******Funcs Funcs******/


void BubbleSort(int *array, int length) 
{
    int i = 0 , j = 0;
    
    for (i = 0; i < length - 1; i++)
    {
        for (j = 0; j < length - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                /* Swap the elements at indices j and j + 1 */
                Swapper(array + j + 1,array + j);
            }
        }
    }
}


void SelectionSort(int *array, int length)
{
    int sorted_position = 0, arr_sift = 0;
    int min_index = 0;

    for (sorted_position = 0; sorted_position < length - 1; sorted_position++)
    {
        min_index = sorted_position;

        for (arr_sift = sorted_position + 1; arr_sift < length; arr_sift++)
        {
            if (array[arr_sift] < array[min_index])
            {
                min_index = arr_sift;
            }
        }

        /* Swap the elements at indices i and min_index */
        Swapper(array + sorted_position,array + min_index);
    }
}


void InsertionSort(int *array, int length) 
{
    int i = 0 , j = 0;
    int key = 0;


    for (i = 1; i < length; i++)
    {
        key = array[i];
        j = i - 1;

        while (j >= 0 && array[j] > key)
        {
            Swapper(array + j + 1, array + j);
        }
        array[j + 1] = key;
    }
}

int ArrayChecker(int *array, int length)
{
    int i = 0;

    for(i = 0 ; i < length - 1; ++i)
    {
        if(array[i] > array[i + 1])
        {
            return 0;
        }
    }
    return 1;
}

int Compare(const void *a, const void *b) 
{
    int x = 0 , y = 0;
    /* Cast the pointers to the correct type and dereference them */
    x = *((int *) a);
    y = *((int *) b);

    /* Return a value indicating the order of the elements */
    if (x < y) 
    {
        return -1;
    } 
    else if (x > y)
    {
        return 1;
    } 
    else
    {
        return 0;
    }
}

void Initializer(int *arr, int size)
{
    int i = 0;

    for(i = 0; i < size; i++)
    {
        srand(16);
        arr[i] = rand();
    }
}


void ArrayPrinter(int *arr, int size)
{
    int i = 0;

    for(i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
        if(!(i%20))
        {
            printf("\n");
        }
    }
}

static void Swapper(int *a, int *b)
{
    int *tmp = b;
    *a = *b;
    *b = *tmp;

}