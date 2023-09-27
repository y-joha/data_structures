/*********************************
 * Reviewer: Shani Horden				
 * Author: Yohai Azoulai			
 * File: merge_quick.c					
 * ******************************/
 
 /**/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc & free*/
#include <string.h> /*memncpy*/
#include <stdio.h> /***********************/

#include "merge_quick.h"
/*******Defines******/


/*******Structs******/



/*******Service Funcs******/
static int WhereDoILook(int data_to_find, int data_currently);
void ArrayPrinter(void *ptr_2_prnt,size_t size);


static void *MallocFunc(
                void *malloc_auxilary,
                size_t number_of_elements, 
                size_t sizeof_element);


static void SwappingFunc(void *a_data, void *b_data, void *buffer, size_t elem_size);

/*******Funcs Funcs******/

int IterBinarySearch(int *array, 
                        size_t arr_size ,
                        int data_to_find)
{
    int mid = 0;
    int front_index = 0, back_index = (int)arr_size;


    mid = back_index/2;

    if (*array == data_to_find)
    {
        return 0;
    }

    if (*(array + (arr_size - 1)) == data_to_find)
    {
        return (arr_size - 1);
    }
    
    while(front_index <= back_index && !(front_index == mid))
    {
        mid = (front_index + back_index)/2;
        
        if (*(array + (mid)) == data_to_find)
        {
            return mid;
        }
        
        if(WhereDoILook(data_to_find,*(array + (mid))))
        {
            front_index = mid + 1;
            break;
        }
        else
        {
            back_index = mid - 1;
        }
    }
    if (*(array + (front_index)) == data_to_find)
    {
                return front_index;
    }
    return -1;
}

int RecurBinarySearch(int *array, 
                        size_t arr_size ,
                        int data_to_find)
{
    int mid = 0 ;
    int front_index = 0, back_index = (arr_size - 1);
    int offset = 0;




    mid = back_index/2;

    if (*array == data_to_find)
    {
        return 0;
    }

    if (*(array + (arr_size - 1)) == data_to_find)
    {
        return (arr_size - 1);
    }
    
    while(front_index <= back_index && !(front_index == mid))
    {
        
        if (*(array + (mid)) == data_to_find)
        {
            return mid;
        }
        
        if (*array == data_to_find)
        {
            return 0;
        }

        if (*(array + (arr_size - 1)) == data_to_find)
        {
            return (arr_size - 1);
        }

        switch (WhereDoILook(data_to_find,*(array + (mid))))
        {
        case 1:
            
            if(1 == mid)
            {
                mid += 1;
                break;
            }

            offset = mid;
            arr_size -= mid;
            
            break;
        
        case 0:
            offset = 0;
            arr_size -= mid;
            
            break;
        
        default:
            
            break;
        }
        

        return RecurBinarySearch((array + offset),arr_size,data_to_find);

    }
    
    return -1;
}


 void *MallocFunc(void *malloc_auxilary ,
                    size_t number_of_elements, 
                    size_t sizeof_element)
{
    malloc_auxilary = malloc(number_of_elements * sizeof_element);
    if (!malloc_auxilary)
    {
        return NULL;
    }
    
    return malloc_auxilary;
} 

static int WhereDoILook(int data_to_find, int data_currently)
{
    if (!(data_to_find - data_currently))
    {
        return -1;
    }
    
    return (data_to_find > data_currently);
}





static int MergeArrays(
                void *arr_to_sort, 
                int begin, int end,
                size_t elem_size, 
                int(*is_before)(const void *elem1, const void *elem2))
{
    int i = 0, j = 0, k = 0;
    int mid = (begin + end) / 2;
    int left_end = mid - begin + 1;
    int right_start = end - mid;

    void *left_array = NULL;
    void *right_array = NULL;

    left_array = malloc(left_end * elem_size);

    if(!left_array)
    {
        return 1;
    }

    right_array = malloc(right_start * elem_size);

    if(!right_array)
    {
        return 1;
    }

    /*Left Chunk copy*/
    memcpy(
        (left_array), 
        ((char*)arr_to_sort + (begin * elem_size)), 
        elem_size * left_end);

    /*Right Chunk copy*/
    memcpy(
        (right_array), 
        ((char*)arr_to_sort + (mid + 1) * elem_size), 
        elem_size * right_start);

    i = 0;
    j = 0;
    k = begin;

    /*Comparison and sorting of each 2 chunks - if either one of sides finish
    copy remainder*/
    while(i < left_end && j < right_start)
    {
        if(is_before(
                (((char*)(right_array) + j * elem_size)), 
                (((char*)(left_array) + i * elem_size))))
        {
            memcpy(
                ((char*)arr_to_sort + k * elem_size), 
                ((char*)left_array + i * elem_size), 
                elem_size);
            ++i;
        }

        else
        {
            memcpy(
                ((char*)arr_to_sort + k *elem_size), 
                ((char*)right_array + j * elem_size), 
                elem_size);
            ++j;
        }

        ++k;
    }
    /*while there is still somthing to copy promote remainder and k for correct 
        placment*/
    while(i < left_end)
    {
        memcpy(
            ((char*)arr_to_sort) + k * elem_size, 
            ((char*)left_array + i * elem_size), 
            elem_size);
        ++i;
        ++k;
    }

    while(j < right_start)
    {
        memcpy(
            ((char*)arr_to_sort) + k * elem_size, 
            ((char*)right_array + j * elem_size), 
            elem_size);
        ++j;
        ++k;
    }


    free(right_array);
    free(left_array);

    return 0;
}

static int RecurseMergeSort(
                        void *arr_to_sort, 
                        size_t num_elements, 
                        size_t elem_size, 
                        int start, int end,
                        int(*is_before)(const void *elem1, const void *elem2))
{
    int mid = 0;

    if(start < end)
    {
        mid = (start + end) / 2;

        RecurseMergeSort(
                        arr_to_sort, 
                        num_elements / 2, 
                        elem_size, 
                        start, mid, 
                        is_before);
        RecurseMergeSort(
                        arr_to_sort, 
                        num_elements / 2, 
                        elem_size, 
                        mid + 1, end, 
                        is_before);

        return MergeArrays(arr_to_sort, start, end, elem_size, is_before);
    }

    return 0;

    
}

int MergeSort(
                void *arr_to_sort, 
                size_t num_elements, 
                size_t elem_size, 
                int(*is_before)(const void *elem1, const void *elem2))
{
    return RecurseMergeSort(
                arr_to_sort, 
                    num_elements, 
                        elem_size, 
                        0, num_elements-1, 
                is_before);
}
 
static void SwappingFunc(
                    void *a_data, 
                    void *b_data, 
                    void *buffer, 
                    size_t elem_size)
{
	memcpy(buffer, a_data, elem_size);
	memcpy(a_data, b_data, elem_size);
	memcpy(b_data, buffer, elem_size);
}



int SplitingFunc(
            void *arr, 
            int left_start, int right_end, 
            void *buffer_array, 
            size_t elem_size,
            int(*is_before)(const void *elem1, const void *elem2)
            )
{
    void *pivot = (char*)arr + right_end*elem_size;
    int i = left_start - 1;
    int j = 0;

    for ( j=left_start; j <= right_end-1; ++j)
    {
        if(is_before((char*)arr + j*elem_size, pivot))
        {
            ++i;
            SwappingFunc(
                    (char*)arr + i*elem_size, 
                    (char*)arr + j*elem_size,
                    buffer_array, 
                    elem_size);        
        }
    }
    SwappingFunc(
            (char*)arr + (i+1)*elem_size, 
            pivot, 
            buffer_array, 
            elem_size);   
    return (i+1);
}

void RecursiveQuickSort(
                    void *arr, 
                    int left_start, int right_end, 
                    size_t elem_size, 
                    void *buffer_array,
                    int(*is_before)(const void *elem1, const void *elem2)) 
{
    int pivot = 0;

    if(left_start < right_end)
    {
        pivot = SplitingFunc(
                        arr, 
                        left_start, right_end, 
                        buffer_array, 
                        elem_size,
                        is_before);
        RecursiveQuickSort(
                        arr, 
                        left_start, pivot-1, 
                        elem_size, 
                        buffer_array,
                        is_before); 
        RecursiveQuickSort(
                        arr, 
                        pivot+1, right_end, 
                        elem_size, 
                        buffer_array,
                        is_before);
    }

}

int QuickSort(  
                void *arr,
                size_t num_of_elem,
                size_t elem_size,
                int(*is_before)(const void *elem1, const void *elem2)
                )
{
    void *buffer_array = NULL;
    
    buffer_array = MallocFunc(buffer_array,elem_size,elem_size);
    if(NULL == buffer_array)
    {
        return -1;
    }
    /* First Pivot i choose is Back of list
        num_of_elemnts - 1*/
    RecursiveQuickSort(
                        arr, 
                        0, num_of_elem - 1, 
                        elem_size, 
                        buffer_array,
                        is_before 
                        );


    free(buffer_array); 
    return 0;    

}


