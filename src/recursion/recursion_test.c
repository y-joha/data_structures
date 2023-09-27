/*********************************
 * Reviewer: Nofar Melamed
 * Author: Yohai Azoulai
 * File: recursion_test.c
 * ******************************/
#include <stdio.h>

#include "recursion.h"

int main(int argc, char *argv[])
{

    
    CheckFibonacciIter();
    CheckRecStrLen();
    CheckRecStrCmp();
    CheckRecStrCpy();
    CheckRecStrCat(); 
    CheckRecStrStr();
    CheckRecFibonacci();
    CheckFibonacciIter();

    

    (void)argc;
    (void)argv;

    return 0;
}

void CheckFibonacciIter()
{
    int i = 0;

    for (i = 5; i < 10; ++i)
    {
        printf("%d - result of fibonacci \n result of index - %d\n", 
                        FibonacciIter(i), i);
    }
}

void CheckRecFibonacci()
{
    int i = 0;

    for (i = 5; i < 10; ++i)
    {
        printf("%d - result of fibonacci \n result of index - %d\n", 
                        FibonacciRec(i), i);
    }
}


void CheckRecStrLen(void)
{

    char *string = "Nu Ma Yeheya";

    printf("the length of string is %ld\n my func returns - %ld\n", strlen(string), RecStrLen(string));
}

void CheckRecStrCmp(void)
{
    char *string1 = "Nu Ma Yeheya";
    char *string2 = "Nu Ma Yehbya";
    char *string3 = "Nu Ma Yeheya";

    printf("lib str returns this %d\n my func returns - %d\n", strcmp(string1, string2), RecStrCmp(string1, string2));

    printf("lib str returns this %d\n my func returns - %d\n", strcmp(string1, string3), RecStrCmp(string1, string3));

    RecStrCmp(string1, string2);
}

void CheckRecStrCpy()
{
    char *string = (char *)malloc(sizeof(char) * RLY_BIG / 2);
    char *string2 = (char *)malloc(sizeof(char) * RLY_BIG / 2);
    char *string3 = (char *)malloc(sizeof(char) * RLY_BIG / 2);
    char *stringOG = "i want you to get mad";
    char *stringOG2 = "i dont want you to protest";

    RecStrCpy(string, stringOG);
    strcpy(string2, stringOG2);
    RecStrCpy(string3, stringOG2);

    printf("this is my RecStrCpy result \nhere - %s \n", string);
    printf("this is lib Recstrcpy result \nhere - %s \n", string2);
    printf("this is my RecStrCpy result \nhere - %s \n", string3);
}

void CheckRecStrCat()
{
    char *string = (char *)malloc(sizeof(char) * RLY_BIG / 2);
    char *string2 = (char *)malloc(sizeof(char) * RLY_BIG / 2);
    char *stringOG = "i want you to get mad";
    char *stringOG2 = "i dont want you to protest";

    RecStrCat(string, stringOG);
    printf("my in between \nhere - %s END1\n", (string));
    RecStrCat(string, stringOG2);
    strcat(string2, stringOG);
    strcat(string2, stringOG2);

    printf("mine func - \n%s END1\n", string);
    printf("lib func - \n%s ENDog2\n", string2);
}

void CheckRecStrStr()
{
    char *stringOG = "Molibdinum";
    char *stringOG2 = "din";
    char *Bentayim = NULL;

    Bentayim = RecStrStr(stringOG, stringOG2);
    /* Bentayim = Recstrstr(stringOG,stringOG2); */

    printf("mine func - \n%s END1\n", Bentayim);
    /* printf("lib func - \n%s ENDog2\n",Bentayim); */
}