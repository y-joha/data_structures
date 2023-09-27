/*********************************
 * Reviewer: Place name				
 * Author: Yohai Azoulai			
 * File: comparison_sorts.c					
 * ******************************/

#ifndef __COMPARISON_SORTS_H__
#define __COMPARISON_SORTS_H__

#include <stdio.h> /*printf*/
#include <stdlib.h> /*rand & qsort*/
#include <time.h> /*time*/
#include <ctype.h> /*isdigit*/






void BubbleSort(int *array, int length);

void SelectionSort(int *array, int length);

void InsertionSort(int *array, int length);

int ArrayChecker(int *array, int length);

int Compare(const void *a, const void *b);

void Initializer(int *arr, int size);

void ArrayPrinter(int *arr, int size);


#endif 
