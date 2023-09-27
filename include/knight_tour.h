/*********************************
 * Reviewer: Aretha Franklin
 * Author: Whitney Houston
 * File Name: knight_tour.h
 * ******************************/

#ifndef __KNIGHT_TOUR_H__
#define __KNIGHT_TOUR_H__

typedef struct position
{
	int x;	/* horizontal axis */
	int y;	/* vertical axis */
} position_t;
/* (0,0) = top left of the chess board */

void KnightTour(position_t position, int *path);

#endif /* __KNIGHT_TOUR_H__ */