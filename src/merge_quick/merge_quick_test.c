/*********************************
 * Reviewer: Shani Horden				
 * Author: Yohai Azoulai			
 * File: merge_quick_test.c				
 * ******************************/

#include <stdio.h>
#include <time.h> /*time*/

#include "merge_quick.h" 

#define DIGITSCAP 100000

void Initializer(int *arr, size_t size, int ranodom_level);
int WhereDoILookInConstVoid(const void * data_a, const void * data_c);
void ArrayPrinter(void *ptr_2_prnt,size_t size);

void TestMergeSearch();
void TestQuickSearch();
void TestBinSearch();


    /*Lazy Static*/
    int array_smol[8];
    int array_chubby[60];
    int array_chubby2[60];
    int array_ypparc[3500];
    int array_mid[20] = {
                        87,4,8,105,15,16,12,20,
                        0,94,5,7,8,9,54,23
                        };


int main(int argc, char *argv[])
{

    TestBinSearch();
 
    TestMergeSearch();
 
    TestQuickSearch();
     
    
    (void)argc;
    (void)argv;

    return 0;
}

void TestBinSearch()
{
    printf("this should return 10 - %d\n",IterBinarySearch(array_mid, 20 ,5));

    printf("this should return -1 - %d\n",IterBinarySearch(array_mid, 20 ,1));

    printf("this should return 10 - %d\n",RecurBinarySearch(array_mid, 20 ,5));

    printf("this should return -1 - %d\n",RecurBinarySearch(array_mid, 20 ,1));
}


void TestMergeSearch()
{
     

    Initializer(array_smol,8,1);
    ArrayPrinter(array_smol,8);
    printf("PreSort\n");
    printf ("*******MergeSort************\n");
    printf ("*******Odd Size************\n");
    MergeSort(array_smol,8,sizeof(int),WhereDoILookInConstVoid);
    ArrayPrinter(array_smol,8);
    printf("\n\n\n");
    printf ("*******End Of Odd MergeSort************\n");


    Initializer(array_chubby,61,1);
    ArrayPrinter(array_chubby,61);
    printf("PreSort\n");
    printf("\n\n\n");
    printf ("*******MergeSort************\n");
    printf ("*******Odd Size************\n");
    MergeSort(array_chubby,61,sizeof(int),WhereDoILookInConstVoid);
    ArrayPrinter(array_chubby,61);
    printf ("\n");
    printf ("*******End Of Odd MergeSort************\n");

    printf ("\n\n\n");

    printf ("*******MergeSort************\n");
    printf ("*******Even Size************\n");
    Initializer(array_chubby2,60,0);
    ArrayPrinter(array_chubby2,60);
    printf("PreSort\n");

    MergeSort(array_chubby2,60,sizeof(int),WhereDoILookInConstVoid);
    ArrayPrinter(array_chubby2,60);
    printf ("\n");
    printf ("*******End Of Even MergeSort************\n");
 
    printf ("*******MergeSort************\n");
    printf ("*******Big Bite************\n");
    Initializer(array_ypparc,3500,0);
    ArrayPrinter(array_ypparc,3500);
    printf("PreSort\n");

    MergeSort(array_ypparc,3500,sizeof(int),WhereDoILookInConstVoid);
    ArrayPrinter(array_ypparc,3500);
    printf ("\n");
    printf ("*******End Of Big Bite MergeSort************\n");

    
    printf ("\n\n\n");
    

}

void TestQuickSearch()
{
     
    Initializer(array_chubby,59,0);

    printf ("*******QuickSort************\n");
    printf ("*******Odd Size************\n");
    ArrayPrinter(array_chubby,59);
    printf("PreSort\n");
    QuickSort(array_chubby,59,sizeof(int),WhereDoILookInConstVoid);
    ArrayPrinter(array_chubby,59);
    printf ("\n");
    printf ("*******End Of Odd QuickSort************\n");

    printf ("\n\n\n");

    printf ("*******QuickSort************\n");
    printf ("*******Even Size************\n");
    Initializer(array_chubby2,60,0);
    ArrayPrinter(array_chubby2,60);
    printf("PreSort\n");
    QuickSort(array_chubby,60,sizeof(int),WhereDoILookInConstVoid);
    ArrayPrinter(array_chubby,60);
    printf ("\n");
    printf ("*******End Of Even QuickSort************\n"); 

    printf ("*******QuickSort************\n");
    printf ("*******Big Bite************\n");
    Initializer(array_ypparc,3500,0);
    ArrayPrinter(array_ypparc,3500);
    printf("PreSort\n");

    QuickSort(array_ypparc,3500,sizeof(int),WhereDoILookInConstVoid);
    ArrayPrinter(array_ypparc,3500);
    printf ("\n");
    printf ("*******End Of Big Bite QuickSort************\n");

    printf ("\n\n\n"); 
}






void Initializer(int *arr, size_t size, int ranodom_level)
{
    size_t i = 0;

    for(i = 0; i < size; i++)
    {
        switch (ranodom_level)
        {
        case 0:
            srand(clock());
            arr[i] = (rand() % DIGITSCAP);
            break;
        
        case 1:
            arr[i] = rand()%(100 - 1) + 1;
            break;
        
        default:
            break;
        }
    }
}
        


void ArrayPrinter(void *ptr_2_prnt,size_t size)
{
    size_t i = 0;
    
    for(i = 0; i < size; i++)
    {
        printf("%d ", (*(int *)((char *)ptr_2_prnt + i*sizeof(int))));
        if(!(i%5))
        {
            printf("\n");
        }
    }
    printf("\n");
}

int WhereDoILookInConstVoid(const void * data_a, const void * data_b)
{
    return (*(int *)data_a < *(int *)data_b);
}
