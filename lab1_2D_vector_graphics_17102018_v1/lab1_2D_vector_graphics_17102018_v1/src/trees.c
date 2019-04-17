/*
===============================================================================
 Name        : Trees.c
 Author      : Vivek Maran
 Description : main definition
 ===============================================================================
 */

#include <cr_section_macros.h>
#include <NXP/crp.h>
#include "LPC17xx.h"                        /* LPC17xx definitions */
#include "ssp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "coord.h"
#include "lcd_utils.h"


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

void draw_trees()
{
	float x0, x1, y0, y1;
	float a0 = 64, b0 = 80; //source coordinate
	point arr[3281];
	float len;
	float xdelta, ydelta;
	float lambda = 1.8;
	float alpha = 0.5236;
	int alpha_deg = 0;
	srand(time(NULL));

	x0 = 0;
	y0 = -64;
	len = 20;

	for (int k = 0; k < 10; k++) {
		uint32_t color = get_leaf_colour(k);
		x1 = x0;
		y1 = y0 + len;

		arr[0].x = -x0 + a0;
		arr[0].y = y0 + b0;

		arr[1].x = -x1 + a0;
		arr[1].y = y1 + b0;

		drawLine(arr[0].x, arr[0].y, arr[1].x, arr[1].y + 1, BROWN);
		drawLine(arr[0].x + 1, arr[0].y, arr[1].x + 1, arr[1].y + 1, BROWN);
		drawLine(arr[0].x - 1, arr[0].y, arr[1].x - 1, arr[1].y + 1, BROWN);

		for (int i = 1; i <= 1093; i++) {

			alpha_deg = generate_random_in_range(15, 60);
			alpha = (alpha_deg * 3.1417) / 180;

			arr[3 * i].x =arr[(int) floor((i + 1.0) / 3)].x
						 + lambda
						 *(arr[i].x
						 - arr[(int) floor((i + 1.0) / 3)].x);
			arr[3 * i].y = arr[(int) floor((i + 1.0) / 3)].y
						   + lambda
						   *(arr[i].y
						   - arr[(int) floor((i + 1.0) / 3)].y);

			xdelta = -arr[i].x;
			ydelta = -arr[i].y;

			float counter_cw[3][3] = { { cos(alpha), -sin(alpha), (cos(alpha)
					* xdelta - sin(alpha) * ydelta) - xdelta }, { sin(
					alpha), cos(alpha), (sin(alpha) * xdelta
					+ cos(alpha) * ydelta) - ydelta }, { 0, 0, 1 } };

			arr[3 * i - 1].x = (counter_cw[0][0] * arr[3 * i].x
					+ counter_cw[0][1] * arr[3 * i].y + counter_cw[0][2]);
			arr[3 * i - 1].y = counter_cw[1][0] * arr[3 * i].x
					+ counter_cw[1][1] * arr[3 * i].y + counter_cw[1][2];

			alpha = -alpha;
			float cw[3][3] = { { cos(alpha), -sin(alpha), (cos(alpha)
					* xdelta - sin(alpha) * ydelta) - xdelta }, { sin(
					alpha), cos(alpha), (sin(alpha) * xdelta
					+ cos(alpha) * ydelta) - ydelta }, { 0, 0, 1 } };
			arr[3 * i + 1].x = (cw[0][0] * arr[3 * i].x
					+ cw[0][1] * arr[3 * i].y + cw[0][2]);
			arr[3 * i + 1].y = cw[1][0] * arr[3 * i].x
					+ cw[1][1] * arr[3 * i].y + cw[1][2];
			alpha = -alpha;
			if ((3 * i - 1) <= 40) {
				drawLine(arr[i].x, arr[i].y, arr[3 * i].x, arr[3 * i].y,
						BROWN);
				drawLine(arr[i].x, arr[i].y, arr[3 * i - 1].x,
						arr[3 * i - 1].y, BROWN);
				drawLine(arr[i].x, arr[i].y, arr[3 * i + 1].x,
						arr[3 * i + 1].y, BROWN);
			} else {
				drawLine(arr[i].x, arr[i].y, arr[3 * i].x, arr[3 * i].y,
						color);
				drawLine(arr[i].x, arr[i].y, arr[3 * i - 1].x,
						arr[3 * i - 1].y, color);
				drawLine(arr[i].x, arr[i].y, arr[3 * i + 1].x,
						arr[3 * i + 1].y, color);
			}
		}
		x0 = generate_random_in_range(-64, 64);
		y0 = generate_random_in_range(-80, 20);
		len = rand() % 20 + 20;
	}
}


