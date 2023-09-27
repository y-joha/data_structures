/*********************************
 * Reviewer: Nofar Melamed				
 * Author: Yohai Azoulai			
 * File: recursion.c					
 * ******************************/
 
 /**/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc & free*/
#include <ctype.h> /*isspace*/

#include "recursion.h"


/*******Defines******/
#define RLY_BIG 4096


/*******Structs******/



/*******Service Funcs******/



/*******Funcs Funcs******/

/**
 * 
 * a series which each number is the sum of privioues 2 nunmbers
 * 
 * start from 0 & 1
 * i have created the sequence till requested element
 * index is the decreacing number for recurtion
 * 
 * 
 * i return its result 
 * 
*/

int FibonacciIter(int element_index)
{
    int num1 = 0 , num2 = 1 , temp = 0, i = 0;

    switch (element_index)
    {
    case 0:
        return num1;
        break;
    
    case 1:
    return num2;
    break;

    default:
    for (i = 0; i < element_index - 1; i++)
    {
        temp = num1;
        num1 = num2;
        num2 += temp;
    }
        break;
    }
    return num2;
}

int FibonacciRec(int element_index)
{
    int num1 = 0 , num2 = 1;
    switch (element_index)
    {
    case 0:
        return num1;
        break;
    
    case 1:
    return num2;
    break;

    default:
    return (FibonacciRec(element_index - 1) +
                        FibonacciRec(element_index - 2));
    break; 
    }
}


/********************************************************/

/**
 * 
 * 
 * while(result != '\0')
 * {
 *      ++count;
 *      return Recstrlen(++s);
 *
 * }
 * 
 * return 0;
 * 
 * 
 * 
*/

size_t RecStrLen (const char *s)
{
    if(*s == '\0')
    {
        return 0;
    }
    else{return 1 + RecStrLen(++s);}
}
/********************************************************/

int RecStrCmp(const char *s1, const char *s2)
{
    if(*s2 != *s1 || *s1 == '\0')
    {
        return *s1 - *s2;
    }

    return RecStrCmp(++s1,++s2);
    
}

/*******************************************************/

char *RecStrCpy(char *dest, const char *src)
{
    *dest = *src;
    
    if(*dest != '\0')
    {
        RecStrCpy(dest + 1,src + 1);
    }
    else
    {
        return dest;
    }
    return 0;
}

/*******************************************************/

char *RecStrCat(char *dest, const char *src)
{
    
    (*dest)? RecStrCat(dest + 1, src): ((*dest++ = *src++)? RecStrCat(dest, src): 0);
    return 0;

}  


/*******************************************************/
char *RecStrStr(const char *haystack, const char *needle)
{
    if('\0' == *haystack && '\0' == *needle)
    {
        return NULL;
    }
    
    if(!strncmp(needle,haystack,RecStrLen(needle)))
    {
        return(char *)haystack;
    }
    return RecStrStr(haystack + 1,needle);
}
/********************************************************/
node_t *RecFlipList(node_t *head)
{
    node_t *new_head = NULL;
    assert (new_head);

    if(NULL == new_head->next || NULL == new_head)    
    {
        return new_head;
    }

    new_head = RecFlipList(new_head->next);
    new_head->next->next = head;
    new_head->next = NULL;

    return new_head;
}
