/*
 * 2d_graphics.c
 *
 *  Created on: Dec 6, 2018
 *      Author: vivek
 */

#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "coord.h"
#include "math.h"
#include "3d_utils.h"
#include "lcd_utils.h"
#include "3d_conv.h"

point3D arr[81] = {0};

uint32_t get_leaf_colour(int k)
{
	uint32_t color;
	switch (k) {
	case 0:
		color = GREEN4;
		break;
	case 1:
		color = GREEN3;
		break;
	case 2:
		color = GREEN2;
		break;
	case 3:
		color = GREEN1;
		break;
	case 4:
		color = GREEN4;
		break;
	case 5:
		color = GREEN3;
		break;
	case 6:
		color = GREEN2;
		break;
	case 7:
		color = GREEN1;
		break;
	case 8:
		color = GREEN4;
		break;
	case 9:
		color = GREEN3;
		break;
	}
	return color;

}
void draw_trees(point3D trunk_start_3d, int cube_num)
{
	float x0, x1, y0, y1;
	float a0 = 64, b0 = 80; //source coordinate
	float len;
	float xdelta, zdelta;
	float lambda = 1.8;
	float alpha = 0.5236;
	int alpha_deg = 0;
	srand(time(NULL));
	point3D trunk_end_3d = {0};
	point p1 = {0};
	point p2 = {0};
	point p3 = {0};
	point p4 = {0};

	if (1 == cube_num) {
		len = 20;
	} else if (2 == cube_num) {
		len = 15;
	} else {
		len = 10;
	}


	for (int k = 0; k < 1; k++) {
		uint32_t color = get_leaf_colour(k);

		trunk_end_3d.x = trunk_start_3d.x;
		trunk_end_3d.z= trunk_start_3d.z + len;
		trunk_end_3d.y=trunk_start_3d.y;

		arr[0].x = trunk_start_3d.x;
		arr[0].y = trunk_start_3d.y;
		arr[0].z = trunk_start_3d.z;

		arr[1].x = trunk_end_3d.x;
		arr[1].y = trunk_end_3d.y;
		arr[1].z = trunk_end_3d.z;

		get_2d_from_3d(&arr[0].x, &p1);
//		get_2d_from_3d(&arr[0], &p1);
		p1 = virtualToNativeCoord(&p1);

		get_2d_from_3d(&arr[1].x, &p2);
//		get_2d_from_3d(&arr[1], &p1);
		p2 = virtualToNativeCoord(&p2);

		drawLine(p1.x, p1.y, p2.x, p2.y, BROWN_1);
		drawLine(p1.x+1, p1.y, p2.x+1, p2.y, BROWN_1);
		drawLine(p1.x-1, p1.y, p2.x-1, p2.y, BROWN_1);

		for (int i = 1; i <= 81; i++) {

			alpha_deg = generate_random_in_range(15, 60);
			alpha = (alpha_deg * 3.1417) / 180;

			arr[3 * i].x =arr[(int) floor((i + 1.0) / 3)].x
						 + lambda
						 *(arr[i].x
						 - arr[(int) floor((i + 1.0) / 3)].x);
			arr[3 * i].z = arr[(int) floor((i + 1.0) / 3)].z
						   + lambda
						   *(arr[i].z
						   - arr[(int) floor((i + 1.0) / 3)].z);

			xdelta = -arr[i].x;
			zdelta = -arr[i].z;

			float counter_cw[3][3] = { { cos(alpha), -sin(alpha), (cos(alpha)
					* xdelta - sin(alpha) * zdelta) - xdelta }, { sin(
					alpha), cos(alpha), (sin(alpha) * xdelta
					+ cos(alpha) * zdelta) - zdelta }, { 0, 0, 1 } };

			arr[3 * i - 1].x = (counter_cw[0][0] * arr[3 * i].x
					+ counter_cw[0][1] * arr[3 * i].z + counter_cw[0][2]);
			arr[3 * i - 1].z = counter_cw[1][0] * arr[3 * i].x
					+ counter_cw[1][1] * arr[3 * i].z + counter_cw[1][2];

			alpha = -alpha;
			float cw[3][3] = { { cos(alpha), -sin(alpha), (cos(alpha)
					* xdelta - sin(alpha) * zdelta) - xdelta }, { sin(
					alpha), cos(alpha), (sin(alpha) * xdelta
					+ cos(alpha) * zdelta) - zdelta }, { 0, 0, 1 } };
			arr[3 * i + 1].x = (cw[0][0] * arr[3 * i].x
					+ cw[0][1] * arr[3 * i].z + cw[0][2]);
			arr[3 * i + 1].z = cw[1][0] * arr[3 * i].x
					+ cw[1][1] * arr[3 * i].z + cw[1][2];
			alpha = -alpha;


			arr[i].y = trunk_start_3d.y;
			get_2d_from_3d(&arr[i], &p1);
			p1 = virtualToNativeCoord(&p1);

			arr[3*i].y = trunk_start_3d.y;
			get_2d_from_3d(&arr[3*i], &p2);
			p2 = virtualToNativeCoord(&p2);

			arr[3*i+1].y = trunk_start_3d.y;
			get_2d_from_3d(&arr[3*i+1], &p3);
			p3 = virtualToNativeCoord(&p3);

			arr[3*i-1].y = trunk_start_3d.y;
			get_2d_from_3d(&arr[3*i-1], &p4);
			p4 = virtualToNativeCoord(&p4);
			if ((3 * i - 1) <= 30) {
				drawLine(p1.x, p1.y, p2.x, p2.y, BROWN_1);
				drawLine(p1.x, p1.y, p3.x, p3.y, BROWN_1);
				drawLine(p1.x, p1.y, p4.x, p4.y, BROWN_1);
			} else {
				drawLine(p1.x, p1.y, p2.x, p2.y, color);
				drawLine(p1.x, p1.y, p3.x, p3.y, color);
				drawLine(p1.x, p1.y, p4.x, p4.y, color);			}
		}
		x0 = generate_random_in_range(-64, 64);
		y0 = generate_random_in_range(-80, 20);
		len = rand() % 20 + 20;
	}
}

void drawSquare(point p0, point p1, point p2, point p3, uint32_t color) {
	drawLineWithPoint(p0,p1, color);
	lcddelay(10);
	drawLineWithPoint(p1, p2, color);
	lcddelay(10);
	drawLineWithPoint(p2, p3, color);
	lcddelay(10);
	drawLineWithPoint(p3, p0, color);
	lcddelay(10);
}

void drawShrinkingSquares(point sqr_0_2Dnative, point sqr_1_2Dnative, point sqr_2_2Dnative, point sqr_3_2Dnative,
		uint32_t colour)
{
	point p0_curr, p1_curr, p2_curr, p3_curr;
	point p0_prev, p1_prev, p2_prev, p3_prev;

	p0_prev = sqr_0_2Dnative;
	p1_prev = sqr_1_2Dnative;
	p2_prev = sqr_2_2Dnative;
	p3_prev = sqr_3_2Dnative;
	for (int i = 0; i < 7; i++)
	{
		if (i == 0)
		{ /* Use points as such for first iteration */
			p0_curr = p0_prev;
			p1_curr = p1_prev;
			p2_curr = p2_prev;
			p3_curr = p3_prev;
		}
		else
		{
			float lambda = 0.2;
			p0_curr.x = (p1_prev.x) - lambda * ((p1_prev.x) - (p0_prev.x));
			p0_curr.y = (p1_prev.y) - lambda * ((p1_prev.y) - (p0_prev.y));
			p1_curr.x = (p2_prev.x) - lambda * ((p2_prev.x) - (p1_prev.x));
			p1_curr.y = (p2_prev.y) - lambda * ((p2_prev.y) - (p1_prev.y));
			p2_curr.x = (p3_prev.x) - lambda * ((p3_prev.x) - (p2_prev.x));
			p2_curr.y = (p3_prev.y) - lambda * ((p3_prev.y) - (p2_prev.y));
			p3_curr.x = (p0_prev.x) - lambda * ((p0_prev.x) - (p3_prev.x));
			p3_curr.y = (p0_prev.y) - lambda * ((p0_prev.y) - (p3_prev.y));

		}
		drawSquare(p0_curr, p1_curr, p2_curr, p3_curr, colour);
		lcddelay(10);
		p0_prev = p0_curr;
		p1_prev = p1_curr;
		p2_prev = p2_curr;
		p3_prev = p3_curr;
	}
	lcddelay(10);
}

void FillshrinkingSquares(point3D sqr_0, point3D sqr_1, point3D sqr_2, point3D sqr_3)
{
	point sqr_0_2D = {0,0};
	point sqr_1_2D = {0,0};
	point sqr_2_2D = {0,0};
	point sqr_3_2D = {0,0};

	point sqr_0_2Dnative = {0,0};
	point sqr_1_2Dnative = {0,0};
	point sqr_2_2Dnative = {0,0};
	point sqr_3_2Dnative = {0,0};

	get_2d_from_3d(&sqr_0, &sqr_0_2D);
	get_2d_from_3d(&sqr_1, &sqr_1_2D);
	get_2d_from_3d(&sqr_2, &sqr_2_2D);
	get_2d_from_3d(&sqr_3, &sqr_3_2D);

	sqr_0_2Dnative = virtualToNativeCoord(&sqr_0_2D);
	sqr_1_2Dnative = virtualToNativeCoord(&sqr_1_2D);
	sqr_2_2Dnative = virtualToNativeCoord(&sqr_2_2D);
	sqr_3_2Dnative = virtualToNativeCoord(&sqr_3_2D);

	drawShrinkingSquares(sqr_0_2Dnative, sqr_1_2Dnative, sqr_2_2Dnative, sqr_3_2Dnative, PINK_2);
}
