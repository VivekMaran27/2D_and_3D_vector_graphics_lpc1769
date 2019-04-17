/*
 ===============================================================================
 Name        : shrinking_squares.c
 Author      : Vivek Maran
 Version     : 1
 Description : Shrinking squares display
 ===============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "lcd_utils.h"
#include "coord.h"
#include "ssp.h"

// defining color values
//#define LIGHTBLUE 0xE0FF00
#define GREEN 0x00FF00
//#define DARKBLUE 0x330000
#define BLACK 0x000000
//#define BLUE 0xFF0000
//#define RED 0x0000FF
//#define MAGENTA 0x1FF800
//#define WHITE 0xFFFFFF
#define PURPLE 0xFF33CC

/** Maximum number of shrinking squares */
#define MAX_NUM_SHRINK_SQUARES (15)
#define PORT_NUM            0

int num_squares = 0, square_side = 50, check = 0;
float lambda = 0.2;	// 0.8 = Clockwise, 0.2 = counterclockwise
char ch;

int hex_colour[9] = {0xE0FF00, 0x00FF00, 0x330000, 0x00D7FF, 0xFF0000, 0x0000FF, 0x1FF800, 0xFFFFFF, 0xFF33CC};

/**
 * Funtion to initialize a point.
 * @param p -[IN] Point to initialize
 * @return - None
 */
void initPoint(point* p) {
	/* Validate the input arguments */
	if (NULL == p) {
		printf("clear_point: Invalid arguments\n");
	}
	(void) memset(p, 0, sizeof(*p));
}

/**
 * Computes offset between point p0 and p1.
 * @param p0 -[IN] Starting point of the line segment
 * @param p1 -[IN] End point of the line segment
 * @return point in between p1 and p2, offset from p1 by 0.2
 */
point getOffsetPoint(point* p0, point *p1) {

	point ret_val;

	/* Validate the input arguments */
	if ((NULL == p0) || (NULL == p1)) {
		printf("divideLineSeg: Invalid arguments\n");
	}
	ret_val.x = (p1->x) - lambda * ((p1->x) - (p0->x));
	ret_val.y = (p1->y) - lambda * ((p1->y) - (p0->y));

	return ret_val;
}

/**
 * Draw shrinking squares at the given co-ordinate.
 * @param p0    -[IN] First point of the square
 * @param p1    -[IN] Second point of the square
 * @param p2    -[IN] Third point of the square
 * @param p3    -[IN] Four point of the square
 */
void drawShrinkingSquares(point *p0, point *p1, point *p2, point *p3,
		uint32_t colour) {
	point p0_curr, p1_curr, p2_curr, p3_curr;
	point p0_prev, p1_prev, p2_prev, p3_prev;

	if ((NULL == p0) || (NULL == p1) || (NULL == p2) || (NULL == p3)) {
		printf("Invalid arguments\n");
		return;
	}

	/* Initialize the point structures */
	initPoint(&p0_curr);
	initPoint(&p1_curr);
	initPoint(&p2_curr);
	initPoint(&p3_curr);
	initPoint(&p0_prev);
	initPoint(&p1_prev);
	initPoint(&p2_prev);
	initPoint(&p3_prev);

	// For loop controlling the number of parent squares generated
	for (int j = 0; j < 20; j++) {
		lambda = 0.8;
		colour = hex_colour[(j % 8)];

		if (num_squares == 0) {
			num_squares = num_squares + 1;
			p0_prev = virtualToNativeCoord(p0);
			p1_prev = virtualToNativeCoord(p1);
			p2_prev = virtualToNativeCoord(p2);
			p3_prev = virtualToNativeCoord(p3);
		} else {
			square_side = (rand() % 50) + 20;
			p0_prev.x = rand() % 127;
			p0_prev.y = rand() % 159;
			p1_prev.x = p0_prev.x + square_side;	//50;
			p1_prev.y = p0_prev.y + 0;
			p2_prev.x = p1_prev.x + 0;
			p2_prev.y = p1_prev.y + square_side;	//50;
			p3_prev.x = p2_prev.x - square_side;	//50;
			p3_prev.y = p2_prev.y + 0;
		}

		for (int i = 0; i < MAX_NUM_SHRINK_SQUARES; i++) {
			if (i == 0) { /* Use points as such for first iteration */
				p0_curr = p0_prev;
				p1_curr = p1_prev;
				p2_curr = p2_prev;
				p3_curr = p3_prev;
			} else {
				p0_curr = getOffsetPoint(&p0_prev, &p1_prev);
				p1_curr = getOffsetPoint(&p1_prev, &p2_prev);
				p2_curr = getOffsetPoint(&p2_prev, &p3_prev);
				p3_curr = getOffsetPoint(&p3_prev, &p0_prev);
			}

			drawSquare(&p0_curr, &p1_curr, &p2_curr, &p3_curr, colour);
			lcddelay(10);	// Delay after every side is generated.
			p0_prev = p0_curr;
			p1_prev = p1_curr;
			p2_prev = p2_curr;
			p3_prev = p3_curr;
		}
		lcddelay(10);
	}
}

/**
 * Function to fill the LCD screen with shrinking squares.
 * @param  - None
 * @return - None
 */
void shrinkingSquaresScreenSaver() {
	point p0, p1, p2, p3;

	/* Initialize the point structures */
	initPoint(&p0);
	initPoint(&p1);
	initPoint(&p2);
	initPoint(&p3);

	// The first square's centre is at the origin.
	p0.x = -25;
	p0.y = -25;
	p1.x = 25;
	p1.y = -25;
	p2.x = 25;
	p2.y = 25;
	p3.x = -25;
	p3.y = 25;

	drawShrinkingSquares(&p0, &p1, &p2, &p3, RED);
}
