/*********************************
 * Reviewer: 				
 * Author: Yohai Azoulai			
 * File: bit_array.c					
 * ******************************/

#include <assert.h> /* Assert in .c */
#include <stdint.h>
#include "bit_array.h"
/*#include <limits.h>  CHAR_BIT -> requested by reviewer but
i used definitions in both H & C so i added define's to the H*/


#define R2(n) n, n + 2 * 64, n + 1 * 64, n + 3 * 64
#define R4(n) R2(n), R2(n + 2 * 16), R2(n + 1 * 16), R2(n + 3 * 16)
#define R6(n) R4(n), R4(n + 2 * 4), R4(n + 1 * 4), R4(n + 3 * 4)

#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)

static const unsigned char mirrored_bits_LUT[256] = {R6(0), R6(2), R6(1), R6(3)};
static const unsigned char  counted_bits_LUT[256] = {B6(0), B6(1), B6(1), B6(2)};

/* description: set all bits to 1 
   params: bit_array_t 
   return value: bit_array_t ba
   undefined behavior: in case of invalid element type */   
bit_array_t BitArraySetAll(bit_array_t ba)
{
	return (ba | ~(bit_array_t)0);
}

/* description: set all bits to 0 
   params: bit_array_t 
   return value: bit_array_t
   undefined behavior: in case of invalid element type */ 
bit_array_t BitArrayResetAll(bit_array_t ba)
{
	return (ba & (bit_array_t)0);
}
/* description: set a bit to 1 in recived index
   params: bit_array_t and an index
   return value: bit_array_t
   undefined behavior: in case of invalid element type or index out of bounds */ 
bit_array_t BitArraySetOn(bit_array_t ba, u_int64_t index)
{
	/*If not working check here*/
	return (ba|((bit_array_t)1<<index));	
}

/* description: set a bit to 0 in recived index
   params: bit_array_t and an index
   return value: bit_array_t
   undefined behavior: in case of invalid element type or index out of bounds */ 
bit_array_t BitArraySetOff(bit_array_t ba, u_int64_t index)
{
	return (ba & ~((bit_array_t)1<<index));
} 

/* description: set a bit to 1 or 0 via recived set in place of index
   params: bit_array_t , set, and an index
   return value: bit_array_t
   undefined behavior: in case of invalid element type, index out of bounds or invalid char */ 
bit_array_t BitArraySetBit(bit_array_t ba, char set, u_int64_t index)
{
	ba &= ~((u_int64_t)1 << index);
	return (ba | ((bit_array_t)set << index)); 
}

/* description: mirror the bits of the recived bit_array_t
   params: bit_array_t 
   return value: bit_array_t
   undefined behavior: in case of invalid element type */ 
bit_array_t BitArrayMirror(bit_array_t ba)
{
    bit_array_t mirror_bit = 0;
    u_int64_t i = 0;

    for(i = 0; i < u_int64_t_BITS; ++i)
    {
        mirror_bit <<= 1;
        mirror_bit |= (ba & (bit_array_t)1);
        ba >>= 1;
    }

    return mirror_bit;
}


bit_array_t BitArrayMirrorMask(bit_array_t ba)
{
	ba = (ba & 0xFFFFFFFF00000000) >> 32 | (ba & 0x00000000FFFFFFFF) << 32;

	ba = (ba & 0xFFFF0000FFFF0000) >> 16 | (ba & 0x0000FFFF0000FFFF) << 16;

	ba = (ba & 0xFF00FF00FF00FF00) >> 8  | (ba & 0x00FF00FF00FF00FF) << 8;

	ba = (ba & 0xF0F0F0F0F0F0F0F0) >> 4  | (ba & 0x0F0F0F0F0F0F0F0F) << 4;
	
	ba = (ba & 0xCCCCCCCCCCCCCCCC) >> 2  | (ba & 0x3333333333333333) << 2;

	ba = (ba & 0xAAAAAAAAAAAAAAAA) >> 1  | (ba & 0x5555555555555555) << 1;
	
	return ba;	
}

bit_array_t BitArrayMirrorLUT(bit_array_t ba)
{
    return  (bit_array_t)mirrored_bits_LUT[ba & 0xFF] << 56 |
    (bit_array_t)mirrored_bits_LUT[(ba >> 8) & 0xFF]  << 48 |
    (bit_array_t)mirrored_bits_LUT[(ba >> 16) & 0xFF] << 40 |
    (bit_array_t)mirrored_bits_LUT[(ba >> 24) & 0xFF] << 32 |
    (bit_array_t)mirrored_bits_LUT[(ba >> 32) & 0xFF] << 24 |
    (bit_array_t)mirrored_bits_LUT[(ba >> 40) & 0xFF] << 16 |
    (bit_array_t)mirrored_bits_LUT[(ba >> 48) & 0xFF] <<  8 |
    (bit_array_t)mirrored_bits_LUT[(ba >> 56) & 0xFF];
}

/* description: rotate the bit_array_t right num times
   params: bit_array_t and num
   return value: bit_array_t
   undefined behavior: in case of invalid element type */ 
bit_array_t BitArrayRotateRight(bit_array_t ba, u_int64_t num)
{
	return((ba >> num)|(ba << (u_int64_t_BITS - num)));
}

/* description: rotate the bit_array_t left num times
   params: bit_array_t and num
   return value: bit_array_t
   undefined behavior: in case of invalid element type */ 
bit_array_t BitArrayRotateLeft(bit_array_t ba, u_int64_t num)
{
	return((ba << num)|(ba >> (u_int64_t_BITS - num)));
}

/* description: flip the bits in a bit array
   params: bit_array_t
   return value: bit_array_t
   undefined behavior: in case of invalid element type */ 
bit_array_t BitArrayFlip(bit_array_t ba)
{
	return (~ba);
}

/* description: flips the bit in a bit array specified by the index
   params: bit_array_t, index
   return value: bit_array_t
   undefined behavior: in case of invalid element type */ 
bit_array_t BitArrayFlipBit(bit_array_t ba, u_int64_t index)
{
	return (ba^((bit_array_t)1<<index));
}

/* description: count the number of on bits
   params: bit_array_t
   return value: bit_array_t
   undefined behavior: in case of invalid element type */ 
u_int64_t BitArrayCountOn(bit_array_t ba)
{
	u_int64_t count_set_on = 0; 
	while(ba)
	{
		ba = ba & (ba-1);
		++count_set_on;
	}
	return count_set_on;
}

/* description: count the number of off bits
   params: bit_array_t
   return value: bit_array_t
   undefined behavior: in case of invalid element type */ 
u_int64_t BitArrayCountOnMask(bit_array_t ba)
{
	ba = (ba & 0x5555555555555555) + ((ba >> 1) & 0x5555555555555555);
	
	ba = (ba & 0x3333333333333333) + ((ba >> 2) & 0x3333333333333333);
	
	ba = (ba & 0x0F0F0F0F0F0F0F0F) + ((ba >> 4) & 0x0F0F0F0F0F0F0F0F);
	
	ba = (ba & 0x00FF00FF00FF00FF) + ((ba >> 8) & 0x00FF00FF00FF00FF);
	
	ba = (ba & 0x0000FFFF0000FFFF) + ((ba >> 16) & 0x0000FFFF0000FFFF);
	
	ba = (ba & 0x00000000FFFFFFFF) + ((ba >> 32) & 0x00000000FFFFFFFF);
	
	return ba;
}



u_int64_t BitArrayCountOnLUT(bit_array_t ba)
{
    return counted_bits_LUT[ba  & 0xFF] +
    counted_bits_LUT[(ba >> 8)  & 0xFF] +         
    counted_bits_LUT[(ba >> 16) & 0xFF] +
    counted_bits_LUT[(ba >> 24) & 0xFF] +       
    counted_bits_LUT[(ba >> 32) & 0xFF] +
    counted_bits_LUT[(ba >> 40) & 0xFF] +
    counted_bits_LUT[(ba >> 48) & 0xFF] +           
    counted_bits_LUT[(ba >> 56) & 0xFF];
}

u_int64_t BitArrayCountOff(bit_array_t ba)
{
	u_int64_t count_set_off = 0; 
	ba = ~ba;
	while(ba)
	{
		ba = ba & (ba-1);
		count_set_off++;
	}
	return count_set_off;
}


u_int64_t BitArrayCountOffOneLine(bit_array_t ba)
{
	return BitArrayCountOn(~ba);
}

/* description: return the value of an index bit
   params: bit_array_t and index
   return value: u_int64_t
   undefined behavior: in case of invalid element type or index out of bounds */ 
u_int64_t BitArrayGetVal(bit_array_t ba, u_int64_t index)
{
	return (ba&((bit_array_t)1<<index));
}

/* description: convert a bit array to string
   params: bit_array_t, pointer to string
   return value: pointer to string
   undefined behavior: in case of invalid element type, buffer not big enough */ 
char *BitArrayToString(bit_array_t ba, char *str)
{
	u_int64_t i;
	assert(str);
	i = u_int64_t_BITS;
	*(str + u_int64_t_BITS) = '\0';
	
	while(i)
	{
		*(str + --i) = (ba & 1)? '1' : '0';
		ba >>= 1;
	}
	
	return str;
}
