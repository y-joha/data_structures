/*********************************
 * Reviewer: Irit Ofir				
 * Author: Yohai Azoulai			
 * File: calculator_test.c				
 * ******************************/


#include <stdio.h>
#include "calculator.h" 

int main(int argc, char *argv[])
{
    int i = 0;
    char *Haper[8];

    Haper[0] = "3 + 2 + 1";
    Haper[1] = "3 * 2 + 1";
    Haper[2] = "(3 + 2.2) + 1";
    Haper[3] = "3 + (2 - 1)";
    Haper[4] = "(3 + 2 + 1) * 4";
    Haper[5] = "(3 + (2 + 8)) * 4";
    Haper[6] = "((3 / 2) + 1) * 4";
    Haper[7] = "((10 + 10) - (5 + 4) * 3) / 15";
    for (i = 0; i < 8; i++)
    {
        printf("%.2f\n",Calculate(Haper[i]));
    }
    
    (void)argc;
    (void)argv;

    return 0;
}
