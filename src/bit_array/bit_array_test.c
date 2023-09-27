/*********************************
 * Reviewer: 				
 * Author: Yohai Azoulai			
 * File: bit_array_test.c				
 * ******************************/

#include <stdlib.h> /* malloc */
#include "bit_array.h" 

void SetAllBitTest(bit_array_t bit_a);
void ResetAllBitsTest(bit_array_t bit_a);
void SetSpecificBitTest(bit_array_t bit_a, size_t index);
void ResetSpecificBitTest(bit_array_t bit_a, size_t index);
void OverWriteBitTest(bit_array_t bit_a, char set, size_t index);
void MirrorBitTest(bit_array_t bit_a);
void RotateRightLeftTest(bit_array_t bit_a,size_t shift);
void FlipArrayTest(bit_array_t bit_a);
void FlipSpecificTest(bit_array_t bit_a,size_t index);
void CountOnBitsTest(bit_array_t bit_a);
void CountOffBitsTest(bit_array_t bit_a);
void PrintInBinary(bit_array_t bit_a);
void GetValuebit_ackTest(bit_array_t bit_a, size_t index);
void GetValueAsString(bit_array_t bit_a, char *buffer);


int main(int argc, char *argv[])
{
    char *buffer = (char *)malloc(SIZE_T_BITS+1);
    /*1100 1110 1001 1001 1101 1000 1111 0111
       12   14   9    9    13    8   15    7 

    */
    bit_array_t bit_a = 0xFF00B0;
    size_t shift = 8;
    size_t index = 4;
    char set = 0;
    if(NULL == buffer)
    {
        printf("buffer malloc failed buddy");
        return 1;
    }

    SetAllBitTest(bit_a);
    ResetAllBitsTest(bit_a);
    SetSpecificBitTest(bit_a, index);
    ResetSpecificBitTest(bit_a, index);
    OverWriteBitTest(bit_a, set, index);
    MirrorBitTest(bit_a);
    RotateRightLeftTest(bit_a, shift);
    FlipArrayTest(bit_a);
    FlipSpecificTest(bit_a, index);
    CountOnBitsTest(bit_a);
    CountOffBitsTest(bit_a);
    GetValuebit_ackTest(bit_a, index);
    GetValueAsString(bit_a, buffer);

    free(buffer);
    (void)argc;
    (void)argv;
    
    return 0;
}

void PrintInBinary(bit_array_t bit_a)
{
    char a = ' ';

    for(a = SIZE_T_BITS - 1 ; a >= 0 ; --a)
    {
        (bit_a & (1 << a))? printf("1"): printf("0");
    }
    printf("\n"); 
}



void SetAllBitTest(bit_array_t bit_a)
{
    if(BitArraySetAll(bit_a) != (~((bit_array_t)0)))
    {
        puts("Set all to 1 failed L.c - 20\n");
    }
}

void ResetAllBitsTest(bit_array_t bit_a)
{
    if(BitArrayResetAll(bit_a) != ((bit_array_t)0))
    {
        puts("Reset all as 0 failed L.c - 29\n");
    }
}

void SetSpecificBitTest(bit_array_t bit_a, size_t index)
{
    if((BitArraySetOn(bit_a,index) & (1<<index))== 0)
    {
        puts("SetSpecific bit failed L.c - 38\n");
    }
}

void ResetSpecificBitTest(bit_array_t bit_a, size_t index)
{
    if((BitArraySetOff(bit_a,index) & (1<<index)) != 0)
    {
        puts("ResetSpecific bit failed L.c - 47\n");
    }
}

void OverWriteBitTest(bit_array_t bit_a, char set, size_t index)
{
    if((BitArraySetBit(bit_a, set, index) & ((bit_array_t) set << index)) != (bit_array_t) set)
    {
        puts("Overwrite bit failed L.c - 57\n");
    }
}

void MirrorBitTest(bit_array_t bit_a)
{
    if(BitArrayMirror(bit_a) != BitArrayMirrorMask(bit_a))
    {
        puts("Mirror bit failed func Vs. funcLUT L.c - 64/80\n");
    }
}

void RotateRightLeftTest(bit_array_t bit_a, size_t shift)
{
    if((BitArrayRotateRight(BitArrayRotateLeft(bit_a,shift),shift)) != bit_a)
    {
        puts("Rotation Checks bit failed L.c - 103/112\n");
    }
}

void FlipArrayTest(bit_array_t bit_a)
{
    if(BitArrayFlip(bit_a) != ~bit_a)
    {
        puts("Flip array check failed L.c - 121\n");

    }
}

void FlipSpecificTest(bit_array_t bit_a,size_t index)
{
    if((BitArrayFlipBit(BitArrayFlipBit(bit_a,index),index)) != bit_a)
    {
        puts("Flip specific check failed L.c - 130\n");
    }
}

void CountOnBitsTest(bit_array_t bit_a)
{
    if(BitArrayCountOn(bit_a) != BitArrayCountOnMask(bit_a))
    {
        puts("Count on bits failed func (L.c - 139) Vs funcMask(L.c - 152)\n");
    }
    if(BitArrayCountOn(0x0000000F0F0F0F0F) != 20 && BitArrayCountOnMask(0x0000000F0F0F0F0F) != 20)
    {
        puts("Should be 20 failed count bit on(test both func results)\n");
    }
    if(BitArrayCountOn(0x0000000000000000) != 0 && BitArrayCountOnMask(0x0000000000000000) != 0)
    {
        puts("Should be 0 failed count bit on(test both func results)\n");
    }
    if(BitArrayCountOn(0xFFFFFFFFFFFFFFFF) != 64 && BitArrayCountOnMask(0xFFFFFFFFFFFFFFFF) != 64)
    {
        puts("Should be 64 failed count bit on(test both func results)\n");
    }
}

void CountOffBitsTest(bit_array_t bit_a)
{
    if(BitArrayCountOff(bit_a) != BitArrayCountOffOneLine(bit_a))
    {
        puts("Count on bits failed func(bitwise - 169) Vs func (give count on ~bit_a - 182)\n");
    }
    if(BitArrayCountOff(0x0000000F0F0F0F0F) != 44)
    {
        puts("Should be 44 failed count bit on\n");
    }
    if(BitArrayCountOff(0x0000000000000000) != 64)
    {
        puts("Should be 64 failed count bit on\n");
    }
    if(BitArrayCountOff(0xFFFFFFFFFFFFFFFF) != 0)
    {
        puts("Should be 0 failed count bit on\n");
    }
}

void GetValuebit_ackTest(bit_array_t bit_a, size_t index)
{
    if(BitArrayGetVal(BitArraySetOff(bit_a,index),index) != 0)
    {
        puts("Get Value failed on the Reset(#1) test L.c - 193(47)\n");
    }

    if(BitArrayGetVal(BitArraySetOn(bit_a,index),index) == 0)
    {
        puts("Get Value failed on the Set(#2) test L.c - 193(38)\n");
    }
}

void GetValueAsString(bit_array_t bit_a,char *buffer)
{
    printf("*****************bit_a = 0xFF00B0********************\n");
    printf("\n");
    buffer = BitArrayToString(bit_a,buffer);
    printf("\nThis is the printed string from the function\n%s\n\n",buffer);
}