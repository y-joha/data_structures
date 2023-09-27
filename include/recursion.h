/*********************************
 * Reviewer: Nofar Melamed				
 * Author: Yohai Azoulai			
 * File: recursion.c					
 * ******************************/

#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <string.h> /*Lib string funcs for testing*/
#include <stdlib.h> /*malloc*/

typedef struct node
{
    int data;
    struct node *next;
} node_t;

#define RLY_BIG 4096

int FibonacciIter(int element_index);
void CheckFibonacciIter();

void CheckRecFibonacci();
int FibonacciRec(int element_index);

size_t RecStrLen (const char *s);
void CheckRecStrLen(void);

int RecStrCmp(const char *s1, const char *s2);
void CheckRecStrCmp(void);

char *RecStrCpy(char *dest, const char *src);
void CheckRecStrCpy();

char *RecStrCat(char *dest, const char *src);
void CheckRecStrCat();

char *RecStrStr(const char *haystack, const char *needle);
void CheckRecStrStr();

node_t* RecFlipList(node_t* new_head);
void CheckRecFlipList();









#endif 
