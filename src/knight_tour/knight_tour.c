/*********************************
 * Reviewer: Yaakov Touitou				
 * Author: Yohai Azoulai			
 * File: knight_tour.c					
 * ******************************/
 
 /**/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc & free*/
#include <stdio.h>

#include "bit_array.h"
#include "knight_tour.h"


/*******Defines******/

#define BIT_SIZE 8

/*******Structs******/



/*******Service Funcs******/

static int CalcIndex(position_t pos);


static int IsTheMoveSafe(position_t pos);

static int WayToJerusalem(
                bit_array_t board,
                position_t arthur_start, 
                int *path);
static int WayToJerusalemHueri(
                bit_array_t board, 
                position_t arthur_start, 
                int *path);



static int Move1(bit_array_t board, position_t curr, int *path);
static int Move2(bit_array_t board, position_t curr, int *path);
static int Move3(bit_array_t board, position_t curr, int *path);
static int Move4(bit_array_t board, position_t curr, int *path);
static int Move5(bit_array_t board, position_t curr, int *path);
static int Move6(bit_array_t board, position_t curr, int *path);
static int Move7(bit_array_t board, position_t curr, int *path);
static int Move8(bit_array_t board, position_t curr, int *path);

static int IsVisited(bit_array_t board, position_t position);
static int NumOfAvailMoves(bit_array_t board,position_t pos);
static int GuessingMoves(bit_array_t board,position_t pos);

typedef int (*Moves_t)(bit_array_t board, position_t curr, int *path);

Moves_t MOVES[]=
{
    Move1, Move2, Move3, Move4, Move5, Move6, Move7, Move8
};

int move_coords[BIT_SIZE][2]={
                                {-1,-2},
                                { 1,-2},
                                {-2,-1},
                                { 2,-1},
                                {-2, 1},
                                { 2, 1},
                                {-1, 2},
                                { 1, 2}
                                };



/*******Funcs Funcs******/

void KnightTour(position_t position, int *path)
{

    bit_array_t board = 0;

    /* board = BitArraySetOn(board,CalcIndex(position));
    *path = CalcIndex(position); */
    WayToJerusalem(board,position,path); 

/*     WayToJerusalemHueri(board,position,path);
 */}

static int IsTheMoveSafe(position_t pos)
{
    return ((pos.x >= 0 && pos.x < 8) 
                    && (pos.y >= 0 && pos.y < 8));
}

static int WayToJerusalem(bit_array_t board, position_t arthur_start, int *path)
{
    position_t tmp_move = {0,0};
    int i = 0, index = 0;

    index = CalcIndex(arthur_start);


    if(64 == BitArrayCountOn(board))
    {
        puts ("success");
        return 0;
    }
    
    board = BitArraySetOn(board,index);
    *path = index;
    
    for (i = 0; i < 8; i++)
    {
        tmp_move.x = arthur_start.x + move_coords[i][0];
        tmp_move.y = arthur_start.y + move_coords[i][1];
        
        if(IsTheMoveSafe(tmp_move) && IsVisited(board,tmp_move))
        {
            return WayToJerusalem(board,tmp_move,path + 1);
        }
    }

    return 1;
}


static int WayToJerusalemHueri(bit_array_t board, position_t arthur_start, int *path)
{
    position_t best_guess = {0}, hueri_guess = {0}, tmp_move = {0};
    int i = 0, min_guess_count = 9, guess_count = 9, temp_count = 0;
    int index = CalcIndex(arthur_start);

    if(64 == BitArrayCountOn(board))
    {
        return 0;
    }

    board = BitArraySetOn(board,index);
    *path = index;

    for (i = 0 ; i < 8 ; ++i)
    {
        tmp_move.x = arthur_start.x + move_coords[i][0];
        tmp_move.y = arthur_start.y + move_coords[i][1];
        temp_count = NumOfAvailMoves(board,tmp_move);

        if (IsTheMoveSafe(tmp_move) && IsVisited(board,tmp_move) 
                                    && temp_count <= min_guess_count)
        {
            hueri_guess = best_guess;
            best_guess = tmp_move;
            guess_count = min_guess_count;
            min_guess_count = temp_count;
        }
        
    }
    
    if (min_guess_count == guess_count)
    {
        min_guess_count = GuessingMoves(board,best_guess);
        guess_count = GuessingMoves(board,hueri_guess);
        best_guess = min_guess_count < guess_count ? best_guess : hueri_guess;
    }

    return WayToJerusalemHueri(board,best_guess,++path);
    
}


static int CalcIndex(position_t pos)
{
    return (pos.x + pos.y * BIT_SIZE);
}

static int Move8(bit_array_t board, position_t curr, int *path)
{
    position_t next = {0};
    
    next.x = curr.x + 2;
    next.y = curr.y - 1;

    if(!IsVisited(board,next))
    {
        return 1; 
    }
    
    if(IsTheMoveSafe(next))
    {
        return WayToJerusalem(board, next, path);
    }

    return 1;

}

static int Move2(bit_array_t board, position_t curr, int *path)
{
    position_t next = {0};
    
    next.x = curr.x + 2;
    next.y = curr.y + 1;

    if(!IsVisited(board,next))
    {
        return 1; 
    }
    
    if(IsTheMoveSafe(next))
    {
        return WayToJerusalem(board, next, path);
    }

    return 1;

}

static int Move4(bit_array_t board, position_t curr, int *path)
{
    position_t next = {0};
    
    next.x = curr.x - 2;
    next.y = curr.y + 1;

    if(!IsVisited(board,next))
    {
        return 1; 
    }
    

    if(IsTheMoveSafe(next))
    {
        return WayToJerusalem(board, next, path);
    }

    return 1;

}

static int Move6(bit_array_t board, position_t curr, int *path)
{
    position_t next = {0};
    
    next.x = curr.x - 2;
    next.y = curr.y - 1;

    if(!IsVisited(board,next))
    {
        return 1; 
    }
    

    if(IsTheMoveSafe(next))
    {
        return WayToJerusalem(board, next, path);
    }

    return 1;

}

static int Move7(bit_array_t board, position_t curr, int *path)
{
    position_t next = {0};
    
    next.x = curr.x + 1;
    next.y = curr.y - 2;

    if(!IsVisited(board,next))
    {
        return 1; 
    }
    

    if(IsTheMoveSafe(next))
    {
        return WayToJerusalem(board, next, path);
    }

    return 1;

}

static int Move5(bit_array_t board, position_t curr, int *path)
{
    position_t next = {0};
    
    next.x = curr.x - 1;
    next.y = curr.y - 2;

    if(!IsVisited(board,next))
    {
        return 1; 
    }
    

    if(IsTheMoveSafe(next))
    {
        return WayToJerusalem(board, next, path);
    }

    return 1;


}

static int Move1(bit_array_t board, position_t curr, int *path)
{
    position_t next = {0};
    
    next.x = curr.x + 1;
    next.y = curr.y + 2;

    if(!IsVisited(board,next))
    {
        return 1; 
    }
    

    if(IsTheMoveSafe(next))
    {
        return WayToJerusalem(board, next, path);
    }

    return 1;

}

static int Move3(bit_array_t board, position_t curr, int *path)
{
    position_t next = {0};
    
    next.x = curr.x - 1;
    next.y = curr.y + 2;

    if(!IsVisited(board,next))
    {
        return 1; 
    }
    

    if(IsTheMoveSafe(next))
    {
        return WayToJerusalem(board, next, path);
    }

    return 1;

}

static int IsVisited(bit_array_t board, position_t position)
{
    int index_board = CalcIndex(position);
    return !BitArrayGetVal(board, index_board);
}

static int NumOfAvailMoves(bit_array_t board, position_t pos)
{
    int heriu_guess = 0, i = 0;
    position_t tmp_move = {0};

    for (i = 0 ; i < 8 ; ++i)
    {
        tmp_move.x = pos.x + move_coords[i][0];
        tmp_move.y = pos.y + move_coords[i][1];

        if (IsTheMoveSafe(tmp_move))
        {
            heriu_guess += IsVisited(board,tmp_move);
        }
    }
    
    return heriu_guess;
}

static int GuessingMoves(bit_array_t board, position_t pos)
{
    position_t tmp_move = {0};
    int i = 0, min = 9, temp = 0;

    for (i = 0 ; i < 8 ; ++i)
    {
        tmp_move.x = pos.x + move_coords[i][0];
        tmp_move.y = pos.y + move_coords[i][1];

        temp = NumOfAvailMoves(board, tmp_move);
        
        if (IsTheMoveSafe(tmp_move) && IsVisited(board,tmp_move) && temp < min)
        {
            min = temp;
        }
    }
    
    return min;
}
